// MT Engine MK2 v0.89
// Copyleft 2014 the Mojon Twins

// mtemk2.c
// Main file

#include <spritepack.h>

// FOR 128K GAMES:
#pragma output STACKPTR=24199
#define FREEPOOL 61697

// FOR 48K GAMES:
//#pragma output STACKPTR=61952
//#define FREEPOOL 61440

// Define where to store and how many sprite descriptors are needed.
#define NUMBLOCKS			52
#define AD_FREE				61440 - NUMBLOCKS * 15
// Note the 15: blocks are 14 bytes, but there's an overhead of 1 byte per block

// For each sprite you need 1+R*C blocks, where R = rows, C = columns.
// For example, a 16x16 sprite needs 1+3*3 = 10 blocks.
// For games with just 4 16x16 sprites (no shoots/hitter/etc) you need 40 blocks.
// For each shoot/hiter/coco you need 1+2*2 = 5 extra blocks.
// Special: whe whip, which is 1 + 3*2 = 7 extra blocks.

// For example: shoots activated need 4 * 10 + 3 * 5 = 55 blocks.
// hitter and no shoots need 4 * 10 + 1 * 5 = 45 blocks.
// hitter and cocos need 4 * 10 + 4 * 5 = 60 blocks.
// carriable plus nothing else 5 * 10 = 50 blocks
// carriable and cocos 5 * 10 + 3 * 5 = 65 blocks
// Just a whip: 4 * 10 + 7 ? 47 blocks.
// Just a whip plus 1 shoot = 4*10 + 7 + 5 = 52 blocks.
// Just do the math.

// Optimal place to compile if using 48K and standard COMPRESSED_LEVELS:
// 23296 + MAP_W * MAP_H * (108) + MAX_BOLTS * 4 + 49
// Check "Journey to the centre of the Nose" for some insight.

#include "config.h"

// Cosas del juego:

#include "definitions.h"

#ifdef ACTIVATE_SCRIPTING
	#include "msc-config.h"
#endif

#ifdef MODE_128K
	#include "128k.h"
#endif

#include "aplib.h"
#include "pantallas.h"
#include "librarian.h"
#include "mapa.h"
#include "tileset.h"
#include "sprites.h"
#include "extrasprites.h"
#include "enems.h"
#include "addons/arrows/sprites.h"
#include "wyzplayer.h"
#include "printer.h"
#include "msc.h"
#include "engine.h"
#include "engine/flickscreen.h"
#include "mainloop.h"

