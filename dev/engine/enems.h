// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// enems.h
// Enemy management, new style

// Ninjajar Clouds not supported, sorry!
// Type 5 "random respawn" not supported sorry! (but easily punchable!)

// There are new, more suitable defines now.
// ENABLE_FLYING_ENEMIES
// ENABLE_LINEAR_ENEMIES
// ENABLE_PURSUE_ENEMIES
// ENABLE_SHOOTERS

#include "engine/enemmods/helper_funcs.h"

#if WAYS_TO_DIE == 1
#include "engine/enemmods/kill_enemy.h"
#elif WAYS_TO_DIE == 2
#include "engine/enemmods/kill_enemy_multiple.h"
#endif

unsigned char pregotten;
#if defined (ENABLE_SHOOTERS) || defined (ENABLE_ARROWS)
unsigned char enemy_shoots;
unsigned char start_arrow, arrow_frame_ct; // Salva (16/10/18)
#endif
void mueve_bicharracos (void) {

#ifndef PLAYER_MOGGY_STYLE
	p_gotten = 0;
	ptgmx = 0;
	ptgmy = 0;
#endif

	tocado = 0;
	p_gotten = 0;
	for (gpit = 0; gpit < MAX_ENEMS; gpit ++) {
		active = killable = animate = 0;
		enoffsmasi = enoffs + gpit;
		gpen_x = baddies [enoffsmasi].x;
		gpen_y = baddies [enoffsmasi].y;

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

#if defined (ENABLE_SHOOTERS) || defined (ENABLE_ARROWS)
		if (baddies [enoffsmasi].t & 4) {
			enemy_shoots = 1;
		} else enemy_shoots = 0;
#endif
		gpt = baddies [enoffsmasi].t >> 3;

		switch (gpt) {
#ifdef ENABLE_PATROLLERS
			case 1:			// linear
				killable = 1;
			case 8:			// moving platforms
				#include "engine/enemmods/move_linear.h"
				break;
#endif
#ifdef ENABLE_FLYING_ENEMIES
			case 2:			// flying
				#include "engine/enemmods/move_fanty.h"
				break;
#endif
#ifdef ENABLE_PURSUERS
			case 3:			// pursuers
				#include "engine/enemmods/move_pursuers.h"
				break;
#endif
#ifdef ENABLE_DROPS
			case 9:			// drops
				#include "addons/drops/move.h"
				break;
#endif
#ifdef ENABLE_ARROWS
			case 10:		// arrows
				#include "addons/arrows/move.h"
				break;
#endif
#ifdef ENABLE_HANNA_MONSTERS_11
			case 11:		// Hanna monsters type 11
				#include "engine/enemmods/move_hanna_11.h"
				break;
#endif
			default:
				if (gpt > 15 && en_an_state [gpit] != GENERAL_DYING) en_an_next_frame [gpit] = sprite_18_a;
		}

		if (active) {
			if (animate) {
				#include "engine/enemmods/animate.h"
			}

			// Carriable box launched and hit...
#ifdef ENABLE_FO_CARRIABLE_BOXES
#ifdef CARRIABLE_BOXES_THROWABLE
			#include "engine/enemmods/throwable.h"
#endif
#endif

#if defined(PLAYER_CAN_PUNCH) || defined(PLAYER_HAZ_SWORD) || defined(PLAYER_HAZ_WHIP)
			#include "engine/enemmods/hitter.h"
#endif

#if defined(PLAYER_SIMPLE_BOMBS)
			#include "engine/enemmods/bombs.h"
#endif

			// Collide with player
#if !defined (PLAYER_MOGGY_STYLE) && !defined (DISABLE_PLATFORMS)
			// Platforms: 2013 rewrite!
			// This time coded in a SMARTER way...!
			if (gpt == 8) {
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
				if (
#ifdef PLAYER_CAN_KILL_FLAG
					flags [PLAYER_CAN_KILL_FLAG] &&
#endif
#if defined (PLAYER_HAS_SWIM) && defined (SWITCHABLE_ENGINES)
					p_engine != SENG_SWIM &&
#endif
					gpy < gpen_cy - 2 && p_vy >= 0 && baddies [enoffsmasi].t >= PLAYER_MIN_KILLABLE && killable) {

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
					baddies [enoffsmasi].t |= 128;			// Mark as dead
#ifdef BODY_COUNT_ON
					flags [BODY_COUNT_ON] ++;
#else
					p_killed ++;
#endif					
#ifdef ACTIVATE_SCRIPTING
#ifdef RUN_SCRIPT_ON_KILL
#ifdef EXTENDED_LEVELS
					if (level_data->activate_scripting) {
#endif
						run_script (2 * MAP_W * MAP_H + 5);
#ifdef EXTENDED_LEVELS
					}
#endif
#endif
#endif
					continue;
				} else if (p_life > 0) {
#else
				if (p_life > 0) {
#endif
					tocado = 1;
#if defined(SLOW_DRAIN) && defined(PLAYER_BOUNCES)
					if ((lasttimehit == 0) || ((maincounter & 3) == 0)) {
#ifdef MODE_128K
						kill_player (6);
#else
						kill_player (4);
#endif
					}
#else
#ifdef MODE_128K
					kill_player (6);
#else
					kill_player (5);
#endif
#endif
#ifdef TYPE_6_KILL_ON_TOUCH
					if (gpt == 2) {
						en_an_next_frame [gpit] = sprite_18_a;
						baddies [enoffsmasi].t |= 128;
					}
#endif
#ifdef PLAYER_BOUNCES
#ifndef PLAYER_MOGGY_STYLE

					p_vx = addsign (baddies [enoffsmasi].mx, PLAYER_MAX_VX << 1);
					p_vy = addsign (baddies [enoffsmasi].my, PLAYER_MAX_VX << 1);

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
			#include "engine\enemmods\bullets.h"
#endif

		}
	}
#if defined(SLOW_DRAIN) && defined(PLAYER_BOUNCES)
	lasttimehit = tocado;
#endif
}
