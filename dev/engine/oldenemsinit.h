// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// oldenems.h
// Enemy initialization (when entering a new screen), classic style (as in Churrera)

#ifdef COUNT_SCR_ENEMS_ON_FLAG
	flags [COUNT_SCR_ENEMS_ON_FLAG]	= 0;
#endif

	for (gpit = 0; gpit < 3; gpit ++) {
		en_an_frame [gpit] = 0;
		en_an_count [gpit] = 3;
		en_an_state [gpit] = 0;
		enoffsmasi = enoffs + gpit;
#ifdef ENABLE_RANDOM_RESPAWN
		en_an_fanty_activo [gpit] = 0;
#endif
#ifdef RESPAWN_ON_ENTER
		// Back to life!
#ifdef RESPAWN_ON_REENTER
		{
#else
		if (do_respawn) {
#endif
			baddies [enoffsmasi].t &= 0xEF;
			en_an_state [gpit] = 0;
#if defined(PLAYER_CAN_FIRE) || defined(PLAYER_CAN_PUNCH) || defined(PLAYER_HAZ_SWORD)
#ifdef MODE_128K
			baddies [enoffsmasi].life = level_data.enems_life;
#else
			baddies [enoffsmasi].life = ENEMIES_LIFE_GAUGE;
#endif
#endif
		}
#endif

#ifdef COUNT_SCR_ENEMS_ON_FLAG
#if defined(DISABLE_PLATFORMS) || defined(PLAYER_MOGGY_STYLE)
		if (baddies [enoffs + gpit].t) flags [COUNT_SCR_ENEMS_ON_FLAG] ++;
#else
		if (baddies [enoffs + gpit].t && 4 != baddies [enoffs + gpit].t) flags [COUNT_SCR_ENEMS_ON_FLAG] ++;
#endif
#endif

// TODO: Make this better
#ifdef ENABLE_SHOOTERS
		switch (baddies [enoffs + gpit].t & 7) {
#else
		switch (baddies [enoffs + gpit].t) {
#endif
			case 1:
			case 2:
			case 3:
			case 4:
#ifdef ENABLE_SHOOTERS
				en_an_base_frame [gpit] = ((baddies [enoffs + gpit].t & 7) - 1) << 1;
#else
				en_an_base_frame [gpit] = (baddies [enoffs + gpit].t - 1) << 1;
#endif
				break;
#ifdef ENABLE_RANDOM_RESPAWN
			case 5:
				en_an_base_frame [gpit] = 4;
				break;
#endif
#ifdef ENABLE_CUSTOM_TYPE_6
			case 6:
				// Añade aquí tu código custom. Esto es un ejemplo:
				en_an_base_frame [gpit] = TYPE_6_FIXED_SPRITE << 1;
				en_an_x [gpit] = baddies [enoffsmasi].x << 6;
				en_an_y [gpit] = baddies [enoffsmasi].y << 6;
				en_an_vx [gpit] = en_an_vy [gpit] = 0;
				en_an_state [gpit] = TYPE_6_IDLE;
				break;
#endif
#ifdef ENABLE_PURSUERS
			case 7:
				en_an_alive [gpit] = 0;
				en_an_dead_row [gpit] = 0;//DEATH_COUNT_EXPRESSION;
				break;
#endif
#ifdef ENABLE_CLOUDS
			case 9:
				en_an_base_frame [gpit] = TYPE_9_FIXED_SPRITE << 1;
				baddies [enoffsmasi].mx = abs (baddies [enoffsmasi].mx);
				break;
#endif
			default:
				en_an_next_frame [gpit] = sprite_18_a;
		}
	}
