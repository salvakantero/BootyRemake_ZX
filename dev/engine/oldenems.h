// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// oldenems.h
// Enemy management, classic style (as in Churrera)

#if defined (ENABLE_CUSTOM_TYPE_6) || defined (ENABLE_SHOOTERS) || defined (ENABLE_CLOUDS)
// Funciones auxiliares custom
unsigned char distance (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2) {
	unsigned char dx = abs (x2 - x1);
	unsigned char dy = abs (y2 - y1);
	unsigned char mn = dx < dy ? dx : dy;
	return (dx + dy - (mn >> 1) - (mn >> 2) + (mn >> 4));
}
#endif

#if defined(ENABLE_SHOOTERS) || defined (ENABLE_CLOUDS)
unsigned char coco_x [MAX_COCOS], coco_y [MAX_COCOS], coco_s [MAX_COCOS], ctx, cty;
signed char coco_vx [MAX_COCOS], coco_vy [MAX_COCOS];
void __FASTCALL__ init_cocos (void) {
	for (gpit = 0; gpit < MAX_COCOS;) coco_s [gpit++] = 0;
}
#endif

#if defined(ENABLE_SHOOTERS) || defined (ENABLE_CLOUDS)
unsigned char coco_it, coco_d, coco_x0;
void __FASTCALL__ shoot_coco (void) {
	coco_x0 = gpen_cx + 4;
#ifdef TYPE_8_FIRE_ONE
	coco_it = gpit;
	{
#else
	for (coco_it = 0; coco_it < MAX_COCOS; coco_it ++) {
#endif
		if (coco_s [coco_it] == 0) {
			coco_d = distance (coco_x0, gpen_cy, gpx, gpy);
			if (coco_d >= TYPE_8_SAFE_DISTANCE) {
#ifdef MODE_128K
				_AY_PL_SND (3);
#endif
				coco_s [coco_it] = 1;
				coco_x [coco_it] = coco_x0;
				coco_y [coco_it] = gpen_cy;
#if defined (ENABLE_SHOOTERS) && defined (ENABLE_CLOUDS)
				if (gpt == 8) {
#endif
#ifdef ENABLE_SHOOTERS
					coco_vx [coco_it] = (COCO_SPEED_8 * (gpx - coco_x0) / coco_d);
					coco_vy [coco_it] = (COCO_SPEED_8 * (gpy - gpen_cy) / coco_d);
#endif
#if defined (ENABLE_SHOOTERS) && defined (ENABLE_CLOUDS)
				} else {
#endif
#ifdef ENABLE_CLOUDS
					coco_vx [coco_it] = 0;
					coco_vy [coco_it] = COCO_SPEED_9;
#endif
#if defined (ENABLE_SHOOTERS) && defined (ENABLE_CLOUDS)
				}
#endif
			}
		}
	}
}
#endif

#if defined(ENABLE_SHOOTERS) || defined (ENABLE_CLOUDS)
void __FASTCALL__ move_cocos (void) {
	for (coco_it = 0; coco_it < MAX_COCOS; coco_it ++) {
		if (coco_s [coco_it]) {
			coco_x [coco_it] += coco_vx [coco_it];
			coco_y [coco_it] += coco_vy [coco_it];

			if (coco_x [coco_it] >= 240 || coco_y [coco_it] >= 160) coco_s [coco_it] = 0;
			// Collide player
			ctx = coco_x [coco_it] + 3;
			cty = coco_y [coco_it] + 3;
			if (p_estado == EST_NORMAL) {
				//if (ctx >= gpx + 2 && ctx <= gpx + 13 && cty >= gpy + 2 && cty <= gpy + 13) {
				if (collide_pixel (ctx, cty, gpx, gpy)) {
					coco_s [coco_it] = 0;
#ifdef MODE_128K
						kill_player (7);
#else
						kill_player (4);
#endif
				}
			}
		}
	}
}
#endif

#ifdef ENABLE_RANDOM_RESPAWN
char player_hidden (void) {
	gpxx = gpx >> 4;
	gpyy = gpy >> 4;
	if ( (gpy & 15) == 0 && p_vx == 0 ) {
		if (attr (gpxx, gpyy) == 2 || (attr (1 + gpxx, gpyy) == 2 && (gpx & 15)) ) {
			return 1;
		}
	}
	return 0;
}
#endif

#ifdef WALLS_STOP_ENEMIES
unsigned char __FASTCALL__ mons_col_sc_x (void) {
	gpaux = gpen_xx + (baddies [enoffsmasi].mx > 0);
#ifdef EVERYTHING_IS_A_WALL
	return (attr (gpaux, gpen_yy) || ((baddies [enoffsmasi].y & 15) && attr (gpaux, gpen_yy + 1)));
#else
	return (attr (gpaux, gpen_yy) & 8 || ((baddies [enoffsmasi].y & 15) && attr (gpaux, gpen_yy + 1) & 8));
#endif
}

unsigned char __FASTCALL__ mons_col_sc_y (void) {
	gpaux = gpen_yy + (baddies [enoffsmasi].my > 0);
#ifdef EVERYTHING_IS_A_WALL
	return (attr (gpen_xx, gpaux) || ((baddies [enoffsmasi].x & 15) && attr (gpen_xx + 1, gpaux)));
#else
	return (attr (gpen_xx, gpaux) & 8 || ((baddies [enoffsmasi].x & 15) && attr (gpen_xx + 1, gpaux) & 8));
#endif
}
#endif

#if defined(SLOW_DRAIN) && defined(PLAYER_BOUNCES)
unsigned char lasttimehit;
#endif

#if defined(ENABLE_CUSTOM_TYPE_6) || defined(ENABLE_RANDOM_RESPAWN)
int limit (int val, int min, int max) {
	if (val < min) return min;
	if (val > max) return max;
	return val;
}
#endif

unsigned char pregotten;
#ifdef ENABLE_SHOOTERS
unsigned char enemy_shoots;
#endif
void mueve_bicharracos (void) {
#ifndef PHANTOMAS_ENGINE
	gpx = p_x >> 6;
	gpy = p_y >> 6;
#endif
#ifndef PLAYER_MOGGY_STYLE
	p_gotten = 0;
	ptgmx = 0;
	ptgmy = 0;
#endif

	tocado = 0;
	p_gotten = 0;
	for (gpit = 0; gpit < 3; gpit ++) {
		active = 0;
		enoffsmasi = enoffs + gpit;
		gpen_x = baddies [enoffsmasi].x;
		gpen_y = baddies [enoffsmasi].y;
		gpt = baddies [enoffsmasi].t;

		if (en_an_state [gpit] == GENERAL_DYING) {
			en_an_count [gpit] --;
			if (0 == en_an_count [gpit]) {
				en_an_state [gpit] = 0;
				en_an_next_frame [gpit] = sprite_18_a;
				continue;
			}
		}

#ifndef PLAYER_MOGGY_STYLE
		// Gotten preliminary:
#if defined (BOUNDING_BOX_8_CENTERED) || defined (BOUNDING_BOX_8_BOTTOM)
		pregotten = (gpx + 11 >= baddies [enoffsmasi].x && gpx <= baddies [enoffsmasi].x + 11);
#else
		pregotten = (gpx + 15 >= baddies [enoffsmasi].x && gpx <= baddies [enoffsmasi].x + 15);
#endif
#endif

#ifdef ENABLE_RANDOM_RESPAWN
		if (en_an_fanty_activo [gpit]) gpt = 5;
#endif
#ifdef ENABLE_SHOOTERS
		if (gpt & 8) {
			// Clear bit 3:
			/*
			if (gpt & 16)
				gpt = (gpt & 7) | 16;
			else
				gpt &= 7;
			*/
			gpt &= 0xf7;
			enemy_shoots = 1;
		} else enemy_shoots = 0;
#endif
		switch (gpt) {
			case 1:
			case 2:
			case 3:
			case 4:
#if defined (ENABLE_SHOOTERS) && defined (TYPE_8_LINEAR_BEHAVIOUR)
			case 8:
#endif
				#include "engine/enemmods/move_linear.h"
				break;
#ifdef ENABLE_RANDOM_RESPAWN
			case 5:
				#include "engine/enemmods/move_rr.h"
				break;
#endif
#ifdef ENABLE_CUSTOM_TYPE_6
			case 6:
				#include "engine/enemmods/move_fanty.h"
				break;
#endif
#ifdef ENABLE_PURSUERS
			case 7:
				#include "engine/enemmods/move_pursuers.h"
				break;
#endif
#ifdef ENABLE_CLOUDS
			case 9:
				#include "engine/enemmods/move_clouds.h"
				break;
#endif
#ifdef ENABLE_DROPS
			case 128:
				#include "addons/drops/move.h"
				break;
#endif
			default:
				if (0 == (gpt & 16)) en_an_next_frame [gpit] = sprite_18_a;
		}

		if (active) {
			// Animate
#if defined(ENABLE_DROPS) || defined (ENABLE_ARROWS)
			if (gpt < 128) {
#endif
				en_an_count [gpit] ++;
#ifdef ENABLE_CUSTOM_TYPE_6
				if (gpt != 6) {
#endif
					if (en_an_count [gpit] == 4) {
						en_an_count [gpit] = 0;
						en_an_frame [gpit] = !en_an_frame [gpit];
						en_an_next_frame [gpit] = enem_frames [en_an_base_frame [gpit] + en_an_frame [gpit]];
					}
#ifdef ENABLE_CUSTOM_TYPE_6
				} else {
					en_an_next_frame [gpit] = enem_frames [en_an_base_frame [gpit] + (en_an_vx [gpit] > 0)];
				}
#endif
#if defined(ENABLE_DROPS) || defined (ENABLE_ARROWS)
			}
#endif


			// Carriable box launched and hit...
#ifdef ENABLE_FO_CARRIABLE_BOXES
#ifdef CARRIABLE_BOXES_THROWABLE
			if (fo_fly) {
				//if (collide (f_o_xp, f_o_yp, gpen_cx, gpen_cy)) {
				if (f_o_xp + 15 >= gpen_cx && f_o_xp <= gpen_cx + 15 &&
					f_o_yp + 15 >= gpen_cy && f_o_yp <= gpen_cy + 15) {
					en_an_next_frame [gpit] = sprite_17_a;
					en_an_state [gpit] = GENERAL_DYING;
					en_an_count [gpit] = 8;
#ifdef CARRIABLE_BOXES_COUNT_KILLS
					flags [CARRIABLE_BOXES_COUNT_KILLS] ++;
#endif
					baddies [enoffsmasi].t |= 16;
#ifdef BODY_COUNT_ON
					flags [BODY_COUNT_ON] ++;
#else					
					p_killed ++;
#endif					
#ifdef MODE_128K
#else
					sp_UpdateNow ();
					peta_el_beeper (0);
#endif

#ifdef ACTIVATE_SCRIPTING
					// Fire script (to detect if everybody is DEAD!)
					run_fire_script ();
#endif
					continue;
				}
			}
#endif
#endif

#if defined(PLAYER_CAN_PUNCH) || defined(PLAYER_HAZ_SWORD)
#ifndef DISABLE_PLATFORMS
			if (hitter_on && baddies [enoffsmasi].t != 4) {
#else
			if (hitter_on) {
#endif
#ifdef PLAYER_CAN_PUNCH
				if (hitter_frame <= 3) {
					if (collide_pixel (hitter_x + (p_facing ? 6 : 1), hitter_y + 3, gpen_cx, gpen_cy)) {
#endif
#ifdef PLAYER_HAZ_SWORD
#endif
						// HIT
#ifdef ENABLE_CUSTOM_TYPE_6
						if (baddies [enoffsmasi].t == 6) {
							en_an_vx [gpit] = addsign (gpen_x - gpx, FANTY_MAX_V);
							en_an_x [gpit] += en_an_vx [gpit];
						}
#endif
						baddies [enoffsmasi].x = gpen_x;
						baddies [enoffsmasi].y = gpen_y;
						en_an_next_frame [gpit] = sprite_17_a;
						//en_an_morido [gpit] = 1;

						baddies [enoffsmasi].life --;

						if (baddies [enoffsmasi].life == 0) {

#ifdef MODE_128K
							en_an_state [gpit] = GENERAL_DYING;
							en_an_count [gpit] = 8;

							_AY_PL_SND (6);
#else
							sp_MoveSprAbs (sp_moviles [gpit], spritesClip, en_an_next_frame [gpit] - en_an_current_frame [gpit], VIEWPORT_Y + (gpen_cy >> 3), VIEWPORT_X + (gpen_cx >> 3), gpen_cx & 7, gpen_cy & 7);
							en_an_current_frame [gpit] = en_an_next_frame [gpit];
							sp_UpdateNow ();
							peta_el_beeper (5);
							en_an_next_frame [gpit] = sprite_18_a;
#endif
#ifdef ENABLE_PURSUERS
							if (gpt != 7) baddies [enoffsmasi].t |= 16;
#else
							baddies [enoffsmasi].t |= 16;
#endif
#ifdef BODY_COUNT_ON
							flags [BODY_COUNT_ON] ++;
#else
							p_killed ++;
#endif							
#ifdef RANDOM_RESPAWN
							en_an_fanty_activo [gpit] = 0;
							baddies [enoffsmasi].life = FANTIES_LIFE_GAUGE;
#endif
#ifdef ENABLE_PURSUERS
							en_an_alive [gpit] = 0;
							en_an_dead_row [gpit] = DEATH_COUNT_EXPRESSION;
#endif
						} else {
							baddies [enoffsmasi].mx = -baddies [enoffsmasi].mx;
							baddies [enoffsmasi].my = -baddies [enoffsmasi].my;
						}

						continue;
					}
				}
			}
#endif

			// Collide with player
#if !defined (PLAYER_MOGGY_STYLE) && !defined (DISABLE_PLATFORMS)
			// Platforms: 2013 rewrite!
			// This time coded in a SMARTER way...!
			if (baddies [enoffsmasi].t == 4) {
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
				if (pregotten && (p_gotten == 0) && (p_saltando == 0 || p_cont_salto > 2)) {
#else
				if (pregotten && (p_gotten == 0) && (p_saltando == 0)) {
#endif
					// Horizontal moving platforms
					if (baddies [enoffsmasi].mx) {
						if (gpy + 16 >= baddies [enoffsmasi].y && gpy + 10 <= baddies [enoffsmasi].y) {
							p_gotten = 1;
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
							ptgmx = baddies [enoffsmasi].mx;
							p_x += ptgmx;
							p_y = (baddies [enoffsmasi].y - 16); gpy = p_y;
							p_saltando = 0;
#else
							ptgmx = baddies [enoffsmasi].mx << 6;
							p_y = (baddies [enoffsmasi].y - 16) << 6; gpy = p_y >> 6;
#endif
						}
					}

					// Vertical moving platforms
					if (
						(baddies [enoffsmasi].my < 0 && gpy + 18 >= baddies [enoffsmasi].y && gpy + 10 <= baddies [enoffsmasi].y) ||
						(baddies [enoffsmasi].my > 0 && gpy + 17 + baddies [enoffsmasi].my >= baddies [enoffsmasi].y && gpy + 10 <= baddies [enoffsmasi].y)
					) {
						p_gotten = 1;
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
						ptgmy = baddies [enoffsmasi].my;
						p_y = baddies [enoffsmasi].y - 16; gpy = p_y;
						p_saltando = 0;
#else
						ptgmy = baddies [enoffsmasi].my << 6;
						p_y = (baddies [enoffsmasi].y - 16) << 6; gpy = p_y >> 6;
						p_vy = 0;
#endif
					}
				}
			} else if ((tocado == 0) && collide (gpx, gpy, gpen_cx, gpen_cy) && p_estado == EST_NORMAL) {
#else
			if ((tocado == 0) && collide (gpx, gpy, gpen_cx, gpen_cy) && p_estado == EST_NORMAL) {
#endif
#ifdef PLAYER_KILLS_ENEMIES
				// Step over enemy
#ifdef PLAYER_CAN_KILL_FLAG
				if (flags [PLAYER_CAN_KILL_FLAG] != 0 &&
					gpy < gpen_cy - 2 && p_vy >= 0 && baddies [enoffsmasi].t >= PLAYER_MIN_KILLABLE) {
#else
				if (gpy < gpen_cy - 2 && p_vy >= 0 && baddies [enoffsmasi].t >= PLAYER_MIN_KILLABLE) {
#endif
					en_an_next_frame [gpit] = sprite_17_a;
#ifdef MODE_128K
					_AY_PL_SND (6);
					en_an_state [gpit] = GENERAL_DYING;
					en_an_count [gpit] = 8;
#else
					sp_MoveSprAbs (sp_moviles [gpit], spritesClip, en_an_next_frame [gpit] - en_an_current_frame [gpit], VIEWPORT_Y + (gpen_cy >> 3), VIEWPORT_X + (gpen_cx >> 3), gpen_cx & 7, gpen_cy & 7);
					en_an_current_frame [gpit] = en_an_next_frame [gpit];
					sp_UpdateNow ();
					peta_el_beeper (5);
					en_an_next_frame [gpit] = sprite_18_a;
#endif
					baddies [enoffsmasi].t |= 16;			// Mark as dead
#ifdef BODY_COUNT_ON
					flags [BODY_COUNT_ON] ++;
#else					
					p_killed ++;
#endif					
#ifdef ACTIVATE_SCRIPTING
#ifdef EXTENDED_LEVELS
					if (level_data->activate_scripting) {
#endif
						// Run this screen fire script or "entering any".
						run_script (n_pant + n_pant + 1);
						run_script (2 * MAP_W * MAP_H + 1);
#ifdef EXTENDED_LEVELS
					}
#endif
#endif
				} else if (p_life > 0) {
#else
				if (p_life > 0) {
#endif
					tocado = 1;
#if defined(SLOW_DRAIN) && defined(PLAYER_BOUNCES)
					if ((lasttimehit == 0) || ((maincounter & 3) == 0)) {
#ifdef MODE_128K
						kill_player (7);
#else
						kill_player (4);
#endif
					}
#else
#ifdef MODE_128K
					kill_player (7);
#else
					kill_player (4);
#endif
#endif
#ifdef TYPE_6_KILL_ON_TOUCH
					if (gpt == 6) {
						en_an_next_frame [gpit] = sprite_18_a;
						baddies [enoffsmasi].t |= 16;
					}
#endif
#ifdef PLAYER_BOUNCES
#ifndef PLAYER_MOGGY_STYLE
#ifdef RANDOM_RESPAWN
					if (en_an_fanty_activo [gpit] == 0) {
						p_vx = addsign (baddies [enoffsmasi].mx, PLAYER_MAX_VX);
						p_vy = addsign (baddies [enoffsmasi].my, PLAYER_MAX_VX);
					} else {
						p_vx = en_an_vx [gpit] + en_an_vx [gpit];
						p_vy = en_an_vy [gpit] + en_an_vy [gpit];
					}
#else
					p_vx = addsign (baddies [enoffsmasi].mx, PLAYER_MAX_VX);
					p_vy = addsign (baddies [enoffsmasi].my, PLAYER_MAX_VX);
#endif
#else
					if (baddies [enoffsmasi].mx) {
						p_vx = addsign (gpx - gpen_cx, abs (baddies [enoffsmasi].mx) << 8);
					}
					if (baddies [enoffsmasi].my) {
						p_vy = addsign (gpy - gpen_cy, abs (baddies [enoffsmasi].my) << 8);
					}
#endif
#endif
				}
			}

#ifdef PLAYER_CAN_FIRE
			// Collide with bullets
#ifdef FIRE_MIN_KILLABLE
			if (baddies [enoffsmasi].t >= FIRE_MIN_KILLABLE) {
#endif
				for (gpjt = 0; gpjt < MAX_BULLETS; gpjt ++) {
					if (bullets_estado [gpjt] == 1) {
						if (collide_pixel (bullets_x [gpjt] + 3, bullets_y [gpjt] + 3, gpen_cx, gpen_cy) {
#ifdef RANDOM_RESPAWN
							if (en_an_fanty_activo [gpit]) {
								en_an_vx [gpit] += addsign (bullets_mx [gpjt], 128);
							}
#endif
#ifdef ENABLE_CUSTOM_TYPE_6
							if (baddies [enoffsmasi].t == 6) {
								en_an_vx [gpit] += addsign (bullets_mx [gpjt], 128);
							}
#endif
							baddies [enoffsmasi].x = gpen_x;
							baddies [enoffsmasi].y = gpen_y;
							en_an_next_frame [gpit] = sprite_17_a;
							en_an_morido [gpit] = 1;
							bullets_estado [gpjt] = 0;
#if !defined (PLAYER_MOGGY_STYLE) && !defined (DISABLE_PLATFORMS)
							if (baddies [enoffsmasi].t != 4) baddies [enoffsmasi].life --;
#else
							baddies [enoffsmasi].life --;
#endif
							if (baddies [enoffsmasi].life == 0) {
								sp_MoveSprAbs (sp_moviles [gpit], spritesClip, en_an_next_frame [gpit] - en_an_current_frame [gpit], VIEWPORT_Y + (gpen_cy >> 3), VIEWPORT_X + (gpen_cx >> 3), gpen_cx & 7, gpen_cy & 7);
								en_an_current_frame [gpit] = en_an_next_frame [gpit];
								sp_UpdateNow ();
#ifdef MODE_128K
								#asm
									halt
								#endasm
								_AY_PL_SND (6);
#else
								peta_el_beeper (5);
#endif
								en_an_next_frame [gpit] = sprite_18_a;
								if (gpt != 7) baddies [enoffsmasi].t |= 16;
#ifdef BODY_COUNT_ON
								flags [BODY_COUNT_ON] ++;
#else								
								p_killed ++;
#endif								
#ifdef RANDOM_RESPAWN
								en_an_fanty_activo [gpit] = 0;
								baddies [enoffsmasi].life = FANTIES_LIFE_GAUGE;
#endif
#ifdef ENABLE_PURSUERS
								en_an_alive [gpit] = 0;
								en_an_dead_row [gpit] = DEATH_COUNT_EXPRESSION;
#endif
							}
						}
					}
				}
#ifdef FIRE_MIN_KILLABLE
			}
#endif
#endif

#ifdef RANDOM_RESPAWN
			// Activar fanty

			if (baddies [enoffsmasi].t > 15 && en_an_fanty_activo [gpit] == 0 && (rand () & 31) == 1) {
				en_an_fanty_activo [gpit] = 1;
				if (p_y > 5120) en_an_y [gpit] = -1024; else en_an_y [gpit] = 10240;
				en_an_x [gpit] = (rand () % 240 - 8) << 6;
				en_an_vx [gpit] = en_an_vy [gpit] = 0;
				en_an_base_frame [gpit] = 4;
			}
#endif
		}
	}
#if defined(SLOW_DRAIN) && defined(PLAYER_BOUNCES)
	lasttimehit = tocado;
#endif
}
