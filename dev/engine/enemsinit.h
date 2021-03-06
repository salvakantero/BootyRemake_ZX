// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// enems.h
// Enemy initialization (when entering a new screen), new style!

// Enemies' "t" is now slightly more complex:
// XTTTTDNN where
// X = dead
// TTTT = type       1000 = platform
//                   0001 = linear
//                   0010 = flying
//                   0011 = pursuing

// Reserved (addons)
//                   1001 = drops
//                   1010 = arrows
//                   1011 = Hanna Type 11
//                   1100 = Hanna Punchos

#ifdef COUNT_SCR_ENEMS_ON_FLAG
	flags [COUNT_SCR_ENEMS_ON_FLAG]	= 0;
#endif

	for (gpit = 0; gpit < MAX_ENEMS; gpit ++) {
		en_an_frame [gpit] = 0;
		en_an_count [gpit] = MAX_ENEMS;
		en_an_state [gpit] = 0;
		enoffsmasi = enoffs + gpit;
		en_an_last_x [gpit] = 0; // Salva (30/09/18)

#ifdef RESPAWN_ON_ENTER
		// Back to life!
#ifdef RESPAWN_ON_REENTER
		{
#else
		if (do_respawn) {
#endif
			baddies [enoffsmasi].t &= 0x7f;
			en_an_state [gpit] = 0;
#if defined(PLAYER_CAN_FIRE) || defined(PLAYER_CAN_PUNCH) || defined(PLAYER_HAZ_SWORD)
#ifdef COMPRESSED_LEVELS
			baddies [enoffsmasi].life = level_data.enems_life;
#else
			baddies [enoffsmasi].life = ENEMIES_LIFE_GAUGE;
#endif
#endif
		}
#endif

		// Init enems:
		// - Asign "base frame"
		// - Init coordinates for flying people
		// Remember XTTTTDNN, TTTT = type, D = fires balls, NN = sprite number

		gpt = baddies [enoffsmasi].t >> 3;
		if (gpt && gpt < 16) {
			en_an_base_frame [gpit] = (baddies [enoffsmasi].t & 3) << 1;

			switch (gpt) {
#ifdef ENABLE_FLYING_ENEMIES
				case 2:
					// Flying
#ifdef TYPE_6_FIXED_SPRITE
					en_an_base_frame [gpit] = TYPE_6_FIXED_SPRITE << 1;
#endif
					en_an_x [gpit] = baddies [enoffsmasi].x << 6;
					en_an_y [gpit] = baddies [enoffsmasi].y << 6;
					en_an_vx [gpit] = en_an_vy [gpit] = 0;
					en_an_state [gpit] = TYPE_6_IDLE;
					break;
#endif
#ifdef ENABLE_PURSUE_ENEMIES
				case 3:
					// Pursuing
					en_an_alive [gpit] = 0;
					en_an_dead_row [gpit] = 0;//DEATH_COUNT_EXPRESSION;
					break;
#endif
#ifdef ENABLE_HANNA_MONSTERS_11
				case 11:
					en_an_state [gpit] = 0;
					break;
#endif
				default:
					break;
			}

#ifdef COUNT_SCR_ENEMS_ON_FLAG
#if defined(DISABLE_PLATFORMS) || defined(PLAYER_MOGGY_STYLE)
		flags [COUNT_SCR_ENEMS_ON_FLAG] ++;
#else
		if (16 != gpt) flags [COUNT_SCR_ENEMS_ON_FLAG] ++;
#endif
#endif
		} else {
			en_an_next_frame [gpit] = sprite_18_a;
		}
	}
