// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// inits.h
// Initialization functions

/*
#ifndef COMPRESSED_LEVELS
#ifndef DEACTIVATE_KEYS
void init_bolts (void) {
	// Activa todos los bolts
	for (gpit = 0; gpit < MAX_bolts; gpit ++)
		bolts [gpit].st = 1;
}
#endif
#endif

#ifdef PLAYER_CAN_FIRE
void init_bullets (void) {
	// Inicializa las balas
	gpit = 0;
	while (gpit < MAX_BULLETS) {
		bullets_estado [gpit ++] = 0;
	}
}
#endif

#ifndef COMPRESSED_LEVELS
#if defined(PLAYER_KILLS_ENEMIES) || defined (PLAYER_CAN_FIRE) || defined (PLAYER_CAN_PUNCH) || defined (PLAYER_HAZ_SWORD)
void init_baddies (void) {
	gpit = 0;
	while (gpit < MAP_W * MAP_H * 3) {
#ifdef USE_OLD_ENEMS
		baddies [gpit].t = baddies [gpit].t & 0x0f;
#else
		baddies [gpit].t = baddies [gpit].t & 0x7f;
#endif
#ifdef PLAYER_CAN_FIRE
		baddies [gpit].life = ENEMIES_LIFE_GAUGE;
#ifdef USE_OLD_ENEMS
#ifdef ENABLE_RANDOM_RESPAWN
		if (baddies [gpit].t == 5)
			baddies [gpit].t |= 16;
#endif
#endif
#endif
		gpit ++;
	}
}
#endif
#endif

#ifndef COMPRESSED_LEVELS
void init_hotspots (void) {
	gpit = 0;
	while (gpit < MAP_W * MAP_H) {
		hotspots [gpit ++].act = 1;
	}
}
#endif

#ifdef ENEMY_BACKUP
void backup_baddies () {
	for (gpit = 0; gpit < 3 * MAP_W * MAP_H; gpit ++) {
		enemy_backup [gpit] = baddies [gpit].t;
	}
}

#ifdef RESTORE_ON_INIT
void restore_baddies () {
	for (gpit = 0; gpit < 3 * MAP_W * MAP_H; gpit ++) {
		baddies [gpit].t = enemy_backup [gpit];
	}
}
#endif
#endif*/
