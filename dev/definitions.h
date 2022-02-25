// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// definitions.h
// Main definitions

struct sp_UDK keys;
void *joyfunc;				

unsigned char *gen_pt;
 
void *my_malloc(uint bytes) 
{
   return sp_BlockAlloc(0);
}

void *u_malloc = my_malloc;
void *u_free = sp_FreeBlock;

// Gigaglobals

struct sp_SS *sp_player;
struct sp_SS *sp_moviles [MAX_ENEMS];
struct sp_Rect spritesClipValues;
struct sp_Rect *spritesClip;

unsigned char enoffs;

// Aux

extern unsigned int asm_int [1];
extern unsigned int asm_int_2 [1];
unsigned char half_life = 0;

#asm
._asm_int
	defw 0
._asm_int_2
	defw 0
#endasm

#define EST_NORMAL 		0
#define EST_PARP 		2
#define EST_MUR 		4
#define sgni(n)			(n < 0 ? -1 : 1)
#define saturate(n)		(n < 0 ? 0 : n)
#define WTOP 1
#define WBOTTOM 2
#define WLEFT 3
#define WRIGHT 4

unsigned char muted = 1; // permite parar la música. Salva (03/11/18)

// Player
int p_x, p_y, p_cx;
int p_x_ini, p_y_ini; // posiciones XY en pantalla tras reentrada al morir. Salva (05/09/18)
int p_vx, p_vy, ptgmx, ptgmy;
unsigned char p_saltando, p_cont_salto;
unsigned char *p_current_frame, *p_next_frame;
unsigned char p_frame, p_subframe, p_facing;
unsigned char p_estado;
unsigned char p_ct_estado;
unsigned char p_gotten;
unsigned char p_life;
unsigned char p_facing_v, p_facing_h;

// Make some player values variable. Preliminary, just the maximum jump speed...

#define FACING_RIGHT 0
#define FACING_LEFT 2
#define FACING_UP 4
#define FACING_DOWN 6

#define SENG_JUMP 0
#define SENG_SWIM 1
#define SENG_COPT 2
#define SENG_JETP 3
#define SENG_BOOT 4

// Enems on screen
unsigned char en_an_base_frame [MAX_ENEMS];
unsigned char en_an_frame [MAX_ENEMS];
unsigned char en_an_count [MAX_ENEMS];
unsigned char *en_an_current_frame [MAX_ENEMS], *en_an_next_frame [MAX_ENEMS];
unsigned char en_an_state [MAX_ENEMS];
unsigned char en_an_last_x[MAX_ENEMS]; // Salva (27/09/18)

// guarda el sentido del movimiento original de los enemigos para restaurarlos al comenzar otra partida
unsigned char en_an_mx_base[MAX_ENEMS * MAP_W * MAP_H];
unsigned char en_an_my_base[MAX_ENEMS * MAP_W * MAP_H];

#define GENERAL_DYING		4

// Current screen buffers
//unsigned char map_attr [150] @ 23296;
unsigned char map_attr [150];

//unsigned char map_buff [150] @ FREEPOOL;
// There's XXX bytes free at FREEPOOL according to splib2's doc.
// (240 if in 128K mode, 512 - stack size (do not risk!) in 48K mode)
// Why not use them?
unsigned char *map_buff = FREEPOOL;

// Current screen hotspot
unsigned char hotspot_x = 0;
unsigned char hotspot_y = 0;
unsigned char do_respawn; 
unsigned char no_draw;

// Flags para scripting
#if defined(ACTIVATE_SCRIPTING) || defined(TILE_GET) || defined(ENABLE_SIM)
#define MAX_FLAGS 3 // Salva (04/09/18)
unsigned char flags[MAX_FLAGS];
#endif

// Globalized
unsigned char n_pant, o_pant;
unsigned char maincounter;
unsigned char mainloop1_ct, mainloop2_ct; // controla la presentación inicial. Salva (06/12/18)

#ifdef ACTIVATE_SCRIPTING
void __FASTCALL__ draw_scr_background (void);
void __FASTCALL__ draw_scr (void);
#endif
void espera_activa (int espera);

#ifdef MODE_128K
void get_resource (unsigned char res, unsigned int dest);
#endif

unsigned char do_gravity = 1;

void cortina (void);
unsigned char rand (void);
void saca_a_todo_el_mundo_de_aqui (unsigned char which_ones);
void draw_coloured_tile (unsigned char x, unsigned char y, unsigned char t, unsigned char half);

#define BUFFER_IDX(x,y) x+(y<<4)-y

unsigned char enoffsmasi;

// Salva (18/08/18)
// colores para las puertas (número), fondos y plataformas  
// screen:								0			1			2			3			4			5			6			7			8			9			10			11			12			13			14			15			16			17			18			19
//const unsigned char screen_color[] = 	{YELLOW,		CYAN,		WHITE,	WHITE,	WHITE,	CYAN,		YELLOW,	CYAN,	GREEN,		WHITE,		YELLOW,		CYAN,		CYAN,		YELLOW,		GREEN,		YELLOW,		WHITE,		WHITE,		CYAN,		WHITE};
//const unsigned char platform_color[] = {RED,	 		RED,		YELLOW,	GREEN,	RED,		BLUE,		RED,		BLUE,		RED,		RED,		RED,		BLUE,		RED,		RED,		RED,		RED,		RED,		GREEN,		RED,		GREEN};
//const unsigned char num_door_color[] =	{GREEN,		YELLOW,	WHITE,	WHITE,	YELLOW,	YELLOW,MAGENTA+BRIGHT,YELLOW, YELLOW+BRIGHT,GREEN,	GREEN,		YELLOW,	WHITE+BRIGHT,GREEN+BRIGHT,YELLOW+BRIGHT,CYAN,		YELLOW,		YELLOW,		YELLOW,		YELLOW};

// posiciones X de las puertas
const unsigned char num_doors_x_base[20*9] =  {11, 22, 9, 22,  9, 22, 11, 22,  0,
												5, 22,  7, 15, 15,  5, 20,  0,  0,
												0,  0,  0,  0,  0,  0,  0,  0,  0,
												0,  0,  0,  0,  0,  0,  0,  0,  0,
												9, 20,  9, 18,  9, 15,  0,  0,  0,
												5, 11,  5, 11,  5, 11,  0,  0,  0,	// 5
											   15, 22, 18, 11, 11, 26,  0,  0,  0,
											   22, 24, 24,  0,  0,  0,  0,  0,  0,
												5, 24,  5, 24,  5, 24,  0,  0,  0,
											   15, 20, 24, 16, 20, 18, 24,  0,  0,
											   18, 24,  7, 18, 24,  0,  0,  0,  0,	// 10
												5, 22, 22, 22,  3, 22,  0,  0,  0,
												5,  7, 24, 16, 16, 22,  0,  0,  0,
											   18, 22, 26, 18, 24,  0,  0,  0,  0,
											   24, 11,  9,  0,  0,  0,  0,  0,  0,
											   11, 22, 11, 11, 18, 18,  0,  0,  0,	// 15												 									 
											   15, 20, 24, 15, 20,  0,  0,  0,  0,
											   24,  5,  9, 24,  9, 13, 24,  5,  9,
												7, 24,  7, 24, 13,  7, 13,  0,  0,
												9, 24,  5, 13, 20, 20,  0,  0,  0};							
// posiciones Y de las puertas
const unsigned char num_doors_y_base[20*9] =  { 1,  1,  5,  5,  9,  9, 13, 13,  0, 
												1,  1,  5,  5,  9, 13, 13,  0,  0,
												0,  0,  0,  0,  0,  0,  0,  0,  0,
												0,  0,  0,  0,  0,  0,  0,  0,  0,
												1,  1,  5,  5, 13, 13,  0,  0,  0,
												1,  1,  9,  9, 13, 13,  0,  0,  0,	// 5
												1,  1,  5,  9, 13, 13,  0,  0,  0,
												1,  9, 13,  0,  0,  0,  0,  0,  0,
												1,  1,  5,  5,  9, 13,  0,  0,  0,
												1,  1,  1,  9,  9, 13, 13,  0,  0,
												5,  5,  9,  9, 13,  0,  0,  0,  0,	// 10
												1,  1,  5,  9, 13, 13,  0,  0,  0,
												1,  5,  5,  9, 13, 13,  0,  0,  0,
												5,  5,  5,  9,  9,  0,  0,  0,  0,
												1,  9, 13,  0,  0,  0,  0,  0,  0,
												1,  1,  5,  9,  9, 13,  0,  0,  0, // 15												 									 
												1,  1,  1, 13, 13,  0,  0,  0,  0,
												1,  5,  5,  5,  9,  9,  9, 13, 13,
												1,  1,  5,  5,  9, 13, 13,  0,  0,
												1,  1,  5,  5,  9, 13,  0,  0,  0};									
// posiciones X de las llaves
const unsigned char num_keys_x_base[20*9] =	  {26, 20,  0, 14,  0, 10, 14,  4,  0,
												0, 28, 26, 10, 28,  8,  8,  0,  0,
												0,  0,  0,  0,  0,  0,  0,  0,  0,
												0,  0,  0,  0,  0,  0,  0,  0,  0,
											   28, 10, 24,  0, 10,  6,  0,  0,  0,
												8, 24,  0,  6,  0,  8,  0,  0,  0,	// 5
												0, 26,  0, 18, 28, 26,  0,  0,  0,
											   24, 28, 20,  0,  0,  0,  0,  0,  0,
											   28,  0, 28,  0, 28, 16,  0,  0,  0,
												0, 20,  2, 28,  0, 16, 18,  0,  0,
												0, 28, 16,  2, 22,  0,  0,  0,  0,	// 10
											   28,  0,  4,  0, 24,  0,  0,  0,  0,
												0, 26,  6, 20, 12, 28,  0,  0,  0,
											   20, 24, 28,  0, 16,  0,  0,  0,  0,
												2, 28,  2,  0,  0,  0,  0,  0,  0,												 									 
											   12,  6, 26, 24, 16,  8,  0,  0,  0,	// 15
											   24, 24,  0, 28,  0,  0,  0,  0,  0,
											   10,  0,  6,  4,  6, 28,  4, 28, 28,
												0, 24, 20, 28,  0, 28,  4,  0,  0,
											   14, 26,  2,  0, 28, 28,  0,  0,  0};
// posiciones Y de las llaves
const unsigned char num_keys_y_base[20*9] =   {10, 14, 10,  2, 14, 10,  6,  2,  0, 
											   14,  2, 14,  2,  6,  2, 14,  0,  0,
												0,  0,  0,  0,  0,  0,  0,  0,  0,
												0,  0,  0,  0,  0,  0,  0,  0,  0,
												6,  2, 14, 14,  6,  6,  0,  0,  0,
											   10,  6, 14, 14,  2,  2,  0,  0,  0,	// 5
											   10,  6, 14,  2, 10,  2,  0,  0,  0,
												6, 14, 10,  0,  0,  0,  0,  0,  0,
												2, 10,  6,  2, 14, 10,  0,  0,  0,
											   14, 14,  2,  2,  2,  2, 10,  0,  0,
											   10, 14,  6,  2, 10,  0,  0,  0,  0,	// 10
 												2, 10,  6, 14,  6,  2,  0,  0,  0,
												6, 14,  2, 14, 10, 10,  0,  0,  0,
											   10,  2, 10, 10, 14,  0,  0,  0,  0,
											   10,  6,  6,  0,  0,  0,  0,  0,  0,												 									 
												2,  2,  2, 14, 10, 10,  0,  0,  0,	// 15
											   14, 10, 10,  2,  2,  0,  0,  0,  0,
											   10, 14, 14, 10,  6, 10,  2,  6,  2,
											   14, 10,  2,  2,  2,  6,  6,  0,  0,
												6, 10, 14,  2,  6,  2,  0,  0,  0};
// posiciones X de los objetos
const unsigned char obj_x_base[20*10] =   { 0,  1, 13,  3,  4,  7, 13,  0,  0,  0,
											1,  8, 13,  6, 12,  1,  8,  1,  5,  0,
											0, 13,  1,  1, 13,  0,  0,  0,  0,  0,
										   11,  9,  0,  0,  0,  0,  0,  0,  0,  0,
											3, 13,  6, 10,  1,  5,  0,  0,  0,  0,
											1,  3,  0,  3,  1,  4,  0,  0,  0,  0,	// 5
											4, 12,  1,  6, 12,  1,  6,  3, 10, 14,
										   10, 13,  5, 13, 13,  0,  0,  0,  0,  0,
											1,  6, 13,  0,  9, 13,  1,  6,  5, 13,
											9, 11, 13, 11, 13, 14, 11,  0,  0,  0,
											3, 13,  1, 12,  9, 13,  0,  0,  0,  0,	// 10
											1, 13,  3,  3,  6, 12,  0,  0,  0,  0,
											0,  1, 14, 10, 12,  9, 12,  0,  0,  0,
										   11, 10, 14, 11,  0, 11,  0,  0,  0,  0,
											1, 13, 14,  2,  0,  0,  0,  0,  0,  0,
											2, 14,  0, 14,  7, 12,  3, 10,  0,  0,	// 15
											8, 13, 13,  0,  0,  0,  0,  0,  0,  0,
											1,  3,  1,  0,  0,  0,  0,  0,  0,  0,
											1,  9, 13,  4, 10,  1,  9,  0,  0,  0,
											6, 13,  0,  5,  8,  0, 11,  0,  0,  0};
// posiciones Y de los objetos
const unsigned char obj_y_base[20*10] =   { 1,  3,  3,  5,  7,  7,  7,  0,  0,  0,
											1,  1,  1,  3,  3,  5,  5,  7,  7,  0,
											1,  1,  3,  5,  5,  0,  0,  0,  0,  0,
											5,  7,  0,  0,  0,  0,  0,  0,  0,  0,
											1,  1,  3,  3,  7,  7,  0,  0,  0,  0,
											1,  1,  5,  5,  7,  7,  0,  0,  0,  0,	// 5
											1,  1,  3,  3,  3,  5,  5,  7,  7,  7,
											1,  1,  3,  5,  7,  0,  0,  0,  0,  0,
											1,  1,  1,  3,  3,  3,  5,  5,  7,  7,
											1,  1,  1,  3,  5,  7,  7,  0,  0,  0,
											1,  3,  5,  5,  7,  7,  0,  0,  0,  0,	// 10
											1,  1,  3,  5,  7,  7,  0,  0,  0,  0,
											1,  3,  3,  5,  5,  7,  7,  0,  0,  0,
											1,  3,  3,  5,  7,  7,  0,  0,  0,  0,
											1,  1,  5,  7,  0,  0,  0,  0,  0,  0,
											1,  1,  3,  3,  5,  5,  7,  7,  0,  0,	// 15
											1,  1,  5,  7,  0,  0,  0,  0,  0,  0,
											3,  5,  7,  0,  0,  0,  0,  0,  0,  0,
											1,  1,  3,  5,  5,  7,  7,  0,  0,  0,
											1,  1,  3,  3,  3,  5,  7,  0,  0,  0};
// objeto (número de tile)								
const unsigned char obj_tn[20*10] =    {18, 19, 16, 16, 21, 20, 17,  0,  0,  0,
										16, 16, 20, 22, 16, 16, 16, 16, 16,  0,
										17, 20, 23, 24, 16,  0,  0,  0,  0,  0,
										17, 17,  0,  0,  0,  0,  0,  0,  0,  0,
										23, 18, 22, 17, 20, 19,  0,  0,  0,  0,
										17, 25, 26, 21, 23, 16,  0,  0,  0,  0,	// 5
										19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
										17, 17, 22, 23, 25,  0,  0,  0,  0,  0,
										17, 24, 21, 25, 17, 16, 26, 23, 17, 19,
										17, 17, 17, 17, 17, 17, 17,  0,  0,  0,
										26, 23, 24, 17, 25, 21,  0,  0,  0,  0,	// 10
										17, 17, 19, 22, 16, 20,  0,  0,  0,  0,
										25, 16, 16, 16, 20, 26, 19,  0,  0,  0,
										24, 25, 22, 17, 17, 17,  0,  0,  0,  0,
										17, 22, 16, 25,  0,  0,  0,  0,  0,  0,
										26, 26, 26, 26, 26, 26, 26, 26,  0,  0,	// 15
										26, 19, 20, 16,  0,  0,  0,  0,  0,  0,
										21, 19, 25,  0,  0,  0,  0,  0,  0,  0,
										17, 17, 17, 17, 17, 17, 17,  0,  0,  0,
										18, 22, 20, 20, 20, 21, 25,  0,  0,  0};

// Copias de los arrays anteriores para trabajar con ellos sin variar los arrays base
unsigned char num_doors_x[180];
unsigned char num_doors_y[180];
unsigned char num_keys_x[180];
unsigned char num_keys_y[180];
unsigned char obj_x[200];
unsigned char obj_y[200];
