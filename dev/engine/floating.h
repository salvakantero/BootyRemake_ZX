// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// Floating objects
// Preliminary version 0.2
// This only works for side-view with bounding box 8 bottom by now.

// TODO: When this is working, cleanup, refactor and optimize!

// Let's go!
// Use a power of 2!
#define MAX_FLOATING_OBJECTS 	8

unsigned char f_o_t [MAX_FLOATING_OBJECTS];
unsigned char f_o_x [MAX_FLOATING_OBJECTS];
unsigned char f_o_y [MAX_FLOATING_OBJECTS];
unsigned char f_o_s [MAX_FLOATING_OBJECTS];

unsigned char fo_it, fo_gp, fo_au, d_prs = 0;
unsigned char fo_idx;
unsigned char fo_x, fo_y, fo_st;
#ifdef CARRIABLE_BOXES_THROWABLE
unsigned char fo_fly = 99, f_o_xp, f_o_yp;
signed char f_o_mx;

void draw_box_sprite (void) {
	sp_MoveSprAbs (sp_carriable, spritesClip, 0, VIEWPORT_Y + (f_o_yp >> 3), VIEWPORT_X + (f_o_xp >> 3), f_o_xp, f_o_yp);
}
#endif

#ifdef ENABLE_FO_CARRIABLE_BOXES
void delete_box_sprite (void) {
	sp_MoveSprAbs (sp_carriable, spritesClip, 0, -2, -2, 0, 0);
}
#endif

void FO_clear (void) {
	fo_it = 0;
	while (fo_it < MAX_FLOATING_OBJECTS) f_o_t [fo_it ++] = 0;
	fo_idx = 0;
#ifdef ENABLE_FO_CARRIABLE_BOXES
	p_hasbox = 99;
#ifdef CARRIABLE_BOXES_ALTER_JUMP
	player_max_vy_saltando = PLAYER_MAX_VY_SALTANDO;
#endif
#ifdef CARRIABLE_BOXES_THROWABLE
	fo_fly = 0;
#endif
#endif
#ifdef CARRIABLE_BOXES_THROWABLE
	delete_box_sprite ();
#endif
#ifdef ENABLE_FO_SCRIPTING
	flags [FO_T_FLAG] = 0;
#endif
}

unsigned char FO_add (unsigned char x, unsigned char y, unsigned char t) {
	f_o_t [fo_idx] = t;
	f_o_x [fo_idx] = x;
	f_o_y [fo_idx] = y;
	f_o_s [fo_idx] = 0;
	fo_idx ++;
	return fo_idx - 1;
}

void FO_paint (unsigned char idx) {
	fo_au = f_o_t [idx];
#ifdef ENABLE_FO_OBJECT_CONTAINERS
	if (fo_au & 128) fo_au = flags [fo_au & 127];
#endif
#ifndef SHOW_EMPTY_CONTAINER
	if (fo_au == 0) return;
#endif
	
#if FT_FIREZONES == 48
	if (fo_au == FT_FIREZONES) return;
#endif

#ifdef SHOW_EMPTY_CONTAINER
	draw_coloured_tile_gamearea (f_o_x [idx], f_o_y [idx], fo_au ? fo_au : ITEM_EMPTY);
#else
	draw_coloured_tile_gamearea (f_o_x [idx], f_o_y [idx], fo_au);
#endif
	
	// Bit 7 marks this block as "floating". That way the player movement routine can identify it
	// and will never store this location as a "safe" one.
	map_attr [BUFFER_IDX (f_o_x [idx], f_o_y [idx])] = behs [fo_au] | 128;
}

void FO_unpaint (unsigned char idx) {
	fo_au = BUFFER_IDX (f_o_x [idx], f_o_y [idx]);
	draw_coloured_tile_gamearea (f_o_x [idx], f_o_y [idx], map_buff [fo_au]);
	map_attr [fo_au] = behs [map_buff [fo_au]];
}

void FO_paint_all (void) {
	fo_it = 0;
	while (fo_it < MAX_FLOATING_OBJECTS) {
#ifdef ENABLE_FO_CARRIABLE_BOXES
		if (f_o_t [fo_it] && fo_it != p_hasbox) FO_paint (fo_it);
#else
		if (f_o_t [fo_it]) FO_paint (fo_it);
#endif
		fo_it ++;
	}
}

#ifdef ENABLE_SIM
void sim_check (void);
#endif

void FO_do (void) {

#ifdef FO_GRAVITY
		// Make fall
		fo_it = maincounter & (MAX_FLOATING_OBJECTS - 1);
		
		if (
			f_o_t [fo_it] && attr (f_o_x [fo_it], f_o_y [fo_it] + 1) < 4
#ifdef ENABLE_FO_FIREZONES
			&& f_o_t [fo_it] != FT_FIREZONES
#endif
#ifdef ENABLE_FO_CARRIABLE_BOXES
			&& fo_it != p_hasbox
#endif
#ifdef FO_SOLID_FLOOR
			&& f_o_y [fo_it] < 9
#endif
		) {
			FO_unpaint (fo_it);
			f_o_y [fo_it] ++;
			if (f_o_y [fo_it] == 10) f_o_t [fo_it] = 0; else FO_paint (fo_it);
#ifdef ENABLE_FO_SCRIPTING
			flags [FO_X_FLAG] = f_o_x [fo_it];
			flags [FO_Y_FLAG] = f_o_y [fo_it];
			flags [FO_T_FLAG] = f_o_t [fo_it];
			run_fire_script ();
#endif
		}
#endif

		// Make drain!
#if defined(ENABLE_FO_CARRIABLE_BOXES) && defined(CARRIABLE_BOXES_DRAIN)
		if (0 == (maincounter & CARRIABLE_BOXES_DRAIN) && 99 != p_hasbox) {
			p_life --;
#ifdef MODE_128K
			_AY_PL_SND (8);
#else
			peta_el_beeper (4);
#endif
		}
#endif
		// I don't think this is usable anywhere else. Good job, Leovigildo III.

#if defined(ENABLE_FO_CARRIABLE_BOXES) || defined(ENABLE_FO_OBJECT_CONTAINERS)
#ifdef CARRIABLE_BOXES_CORCHONETA
		fo_y = (gpy + 8) >> 4;
#else
		fo_y = (gpy >> 4) + 1;
#endif
		fo_x = (gpx + 8) >> 4;

		// Read keys / controller
		fo_gp = (joyfunc) (&keys);

#ifdef ENABLE_FO_CARRIABLE_BOXES
#ifdef CARRIABLE_BOXES_THROWABLE
		if ((fo_gp & sp_FIRE) == 0) {
			if (99 != p_hasbox && fo_fly == 0) {
				fo_fly = 1;
				if (p_facing) f_o_mx = 16; else f_o_mx = -16;
				f_o_xp = gpx;
				f_o_yp = gpy - 8;
				f_o_t [p_hasbox] = 0;
				p_hasbox = 99;
#ifdef CARRIABLE_BOXES_ALTER_JUMP
				// Restore jump
				player_max_vy_saltando = PLAYER_MAX_VY_SALTANDO;
#endif
			}
		}

		if (fo_fly) {
			f_o_xp += f_o_mx;

			// Kill enemy? -> Moved to enems.h!!

			// Check if we should kill the box...
			if (f_o_xp > 239 || (attr ((f_o_xp + 8) >> 4, (f_o_yp + 8) >> 4) & 8)) {
				fo_fly = 0;
#ifdef MODE_128K
#else
				peta_el_beeper (5);
#endif
				delete_box_sprite ();
			} else {
				draw_box_sprite ();
			}
		}
#endif
#endif

#if defined(SCRIPTING_DOWN)
		if ((fo_gp & sp_DOWN) == 0) {
#elif defined(SCRIPTING_KEY_FIRE)
		if ((fo_gp & sp_FIRE) == 0) {
#elif defined(SCRIPTING_KEY_M) {
		if (sp_KeyPressed (key_m)) {
#endif
			if (0 == d_prs) {
				d_prs = 1;
#ifdef ENABLE_FO_CARRIABLE_BOXES
				if (99 != p_hasbox) {
					// Drop box?
					if ((attr (fo_x, fo_y - 2) & 8) == 0) {
						// revisa esto...
						if (attr (fo_x, fo_y - 1) & 8) {
							if (p_facing) fo_x --; else fo_x ++;
						}
						f_o_y [p_hasbox] = fo_y - 1;
						p_y = (fo_y - 2) << 10;
						f_o_x [p_hasbox] = fo_x;
						FO_paint (p_hasbox);
						p_hasbox = 99;
#ifdef MODE_128K
#else
						peta_el_beeper (2);
#endif
#ifdef SCRIPTING_KEY_FIRE
						invalidate_fire = 1;
#endif
#ifdef CARRIABLE_BOXES_ALTER_JUMP
						// Restore jump
						player_max_vy_saltando = PLAYER_MAX_VY_SALTANDO;
#endif
						delete_box_sprite ();
					}
				} else
#endif
				{
					
#ifdef FO_DETECT_INTERACTION_CENTER
					fo_x = (gpx + 8) >> 4;
#else				
					// Calculate interactuable cell - it depends where the player is facing	
					if (0 == p_facing) fo_x = (gpx + 4) >> 4; else fo_x = (gpx + 12) >> 4;
#endif					

					fo_it = 0;
					while (fo_it < MAX_FLOATING_OBJECTS) {
#ifdef ENABLE_FO_CARRIABLE_BOXES
						if (f_o_y [fo_it] == fo_y && f_o_x [fo_it] == fo_x) {
							if (f_o_t [fo_it] == FT_CARRIABLE_BOXES) {
								p_hasbox = fo_it;
								FO_unpaint (fo_it);
#ifdef MODE_128K
#else
								peta_el_beeper (2);
#endif
#ifdef SCRIPTING_KEY_FIRE
								invalidate_fire = 1;
#endif
#ifdef CARRIABLE_BOXES_ALTER_JUMP
								// Alter jump
								player_max_vy_saltando = CARRIABLE_BOXES_ALTER_JUMP;
#endif
							}
						}
#endif

#if defined (ENABLE_FO_OBJECT_CONTAINERS) || defined (ENABLE_FO_FIREZONES)
						if (f_o_x [fo_it] == fo_x
#ifndef CARRIABLE_BOXES_CORCHONETA
							&& f_o_y [fo_it] == fo_y - 1
#else
							&& f_o_y [fo_it] == fo_y
#endif
						) {
#ifdef ENABLE_FO_OBJECT_CONTAINERS
							if (f_o_t [fo_it] & 128) {
								// Tengo que cambiar lo que haya en items [flags [FLAG_ITEM_SELECTED]]
								// por lo que haya en flags [f_o_t [fo_it] & 127]
								fo_st = f_o_t [fo_it] & 127;
								fo_au = flags [fo_st];
								flags [fo_st] = items [flags [FLAG_SLOT_SELECTED]];
								items [flags [FLAG_SLOT_SELECTED]] = fo_au;
								display_items ();
								
#ifdef SHOW_EMPTY_CONTAINER
								FO_paint (fo_it);
#else								
								if (flags [fo_st]) FO_paint (fo_it); else FO_unpaint (fo_it);
#endif
#ifdef MODE_128K
								_AY_PL_SND (11);
#else								
								peta_el_beeper (6);
#endif								
#ifdef SCRIPTING_KEY_FIRE
								invalidate_fire = 1;
#endif
#ifdef ENABLE_SIM
								// If all objects are in place, FLAG 29 is set...
								sim_check ();
#endif
							}
#endif
#ifdef ENABLE_FO_FIREZONES
							if (f_o_t [fo_it] == FT_FIREZONES) {
								run_fire_script ();
							}
#endif
						}
#endif
						fo_it ++;
					}
				}
			}
		} else {
			d_prs = 0;
		}

#ifdef ENABLE_FO_CARRIABLE_BOXES
		// Update sprite?
		if (p_hasbox != 99) sp_MoveSprAbs (sp_carriable, spritesClip, 0, VIEWPORT_Y + (gpy >> 3) - 1, VIEWPORT_X + (gpx >> 3), gpx & 7, gpy & 7);
#endif

#endif
}
