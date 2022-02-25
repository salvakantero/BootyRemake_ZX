// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// engine.h
// Well, self explanatory innit?

#ifndef PLAYER_MIN_KILLABLE
#define PLAYER_MIN_KILLABLE 0
#endif

// Animation frames
#include "engine/frames.h"

// Prepare level (compressed levels)
#if defined (SIMPLE_LEVEL_MANAGER)
#include "engine/clevels-s.h"
#elif defined (COMPRESSED_LEVELS)
#include "engine/clevels.h"
#endif

// Init player
#include "engine/initplayer.h"

// Collision
#include "engine/collision.h"

// Random
#include "engine/random.h"

// Messages
#include "engine/messages.h"

#ifdef PLAYER_STEP_SOUND
void step (void) 
{
	if (!muted) // solo cuando no suena música. Salva (03/11/18)
	{
		#asm
			ld a, 16
			out (254), a
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			nop
			xor 16
			out (254), a
		#endasm
	}
}
#endif

void cortina (void) 
{
	#asm
		;; Antes que nada vamos a limpiar el PAPER de toda la pantalla
		;; para que no queden artefactos feos
		
		ld	de, 22528			; Apuntamos con DE a la zona de atributos
		ld	b,	3				; Procesamos 3 tercios
	.clearb1
		push bc
		
		ld	b, 0				; Procesamos los 256 atributos de cada tercio
	.clearb2
	
		ld	a, (de)				; Nos traemos un atributo
		and	199					; Le hacemos la m�scara 11000111 y dejamos PAPER a 0
		ld	(de), a				; Y lo volvemos a poner
		
		inc de					; Siguiente atributo
	
		djnz clearb2
		
		pop bc
		djnz clearb1
		
		;; Y ahora el c�digo original que escrib� para UWOL:	
	
		ld	a,	8
	.repitatodo
		ld	c,	a			; Salvamos el contador de "repitatodo" en 'c'
	
		ld	hl, 16384
		ld	a,	12
	
	.bucle
		ld	b,	a			; Salvamos el contador de "bucle" en 'b'
		ld	a,	0
	
	.bucle1
		sla (hl)
		inc hl
		dec a
		jr	nz, bucle1
			
		ld	a,	0
	.bucle2
		srl (hl)
		inc hl
		dec a
		jr	nz, bucle2
			
		ld	a,	b			; Restituimos el contador de "bucle" a 'a'
		dec a
		jr	nz, bucle
	
		ld	a,	c			; Restituimos el contador de "repitatodo" a 'a'
		dec a
		jr	nz, repitatodo
	#endasm
}

/*
signed int addsign (signed int n, signed int value) 
{
	return n == 0 ? 0 : n > 0 ? value : -value;
}

unsigned int abs (int n) 
{
	if (n < 0)
		return (unsigned int) (-n);
	else
		return (unsigned int) n;
}*/

// Engine globals (for speed) & size!
unsigned char gpx, gpy, gpd, gpc, gpt, gps;
unsigned char gpxx, gpyy, gpcx, gpcy;
unsigned char possee, hit_v, hit_h, hit, wall_h, wall_v;
unsigned char gpen_x, gpen_y, gpen_cx, gpen_cy, gpen_xx, gpen_yy, gpaux;
unsigned char tocado, active, killable, animate;
unsigned char gpit, gpjt;
unsigned char *map_pointer;
unsigned char falling_ct;

void kill_player (unsigned char sound) 
{
	p_next_frame = sprite_17_a; // tocado, animación de choque. Salva (15/10/18)
	p_life --;
	falling_ct = 0;
	_AY_PL_SND (sound);
#ifdef PLAYER_FLICKERS
	p_estado = EST_PARP;
	p_ct_estado = 50;
#endif
}

// Animated tiles
#ifdef ENABLE_TILANIMS
#include "tilanim.h"
#endif

// Initialization functions
#include "engine/inits.h"

// Main player movement
#include "engine/playermove.h"

// pintamos las llaves y puertas disponibles recorriendo los vectores X,Y. Salva (24/08/18)
void print_keys_and_doors(void)
{
	unsigned char i, j;
	for(i = 0; i < 9; i++)
	{
		// llaves
		j = n_pant * 9 + i;
		if (num_keys_y[j] != 0)
		{
			update_tile(num_keys_x[j]/2, num_keys_y[j]/2, 0, TILE_GET_KEY);
			sp_PrintAtInv(num_keys_y[j] + VIEWPORT_Y, num_keys_x[j], 
						  WHITE + BRIGHT, 16 + ((i + 1) % 10));
		}
		// puertas
		if (num_doors_y[j] != 0)
		{
			update_tile(num_doors_x[j]/2, num_doors_y[j]/2, 4, TILE_GET_DOOR_UP);
			update_tile(num_doors_x[j]/2, (num_doors_y[j]/2)+1, 8, TILE_GET_DOOR_DOWN);
			sp_PrintAtInv (	num_doors_y[j] + VIEWPORT_Y, num_doors_x[j], 
							RED, 16 + ((i + 1) % 10));
		}
		else if (num_doors_y_base[j] != 0) // puerta abierta, solo número
		{
			sp_PrintAtInv (	num_doors_y_base[j] + VIEWPORT_Y, num_doors_x_base[j], 
							RED, 16 + ((i + 1) % 10));
		}
	}
}


// pintamos los objetos disponibles recorriendo los vectores X,Y. Salva (25/08/18)
void print_objects(void)
{
	unsigned char i, j;
	for(i = 0; i < 10; i++)
	{
		j = n_pant * 10 + i;
		if (obj_y[j] != 0)
			update_tile(obj_x[j], obj_y[j], 0, obj_tn[j]);
	}
}


// chequeamos si todas las puertas del pasillo están abiertas. Salva (02/12/18)
unsigned char open_doors(unsigned char y)
{
	unsigned char i, j, result = 1; // 1 = doors open (default)

	// converting pixels to doors Y positions
	if (y == 16) y = 1;
	else if (y == 48) y = 5;
	else if (y == 80) y = 9;
	else if (y == 112) y = 13;

	for(i = 0; i < 9; i++)
	{
		j = n_pant * 9 + i;
		if (num_doors_y[j] == y)
		{
			result = 0;
			break;
		}
	}
	return result;
}

#ifdef ACTIVATE_SCRIPTING

void run_entering_script (void) 
{
	// Ejecutamos los scripts de entrar en pantalla:
	run_script (2 * MAP_W * MAP_H + 1);
	flags[3] = 0; // permite pasar de nuevo por las puertas frontales. Salva (12/09/18)
	run_script (n_pant + n_pant);

	// Salva 29/07/18
	print_keys_and_doors();
	print_objects();
	// memoriza la posición al reentrar por si Jim es tocado
	p_x_ini = p_x;
	p_y_ini = p_y;
}
#endif

// Screen drawing
#include "engine/drawscr.h"

// Enemies
#include "engine/enems.h"

void espera_activa (int espera) 
{
	do {
		#asm
			halt
		#endasm
	} while (--espera);
	sp_Border (0);
}

#ifdef ACTIVATE_SCRIPTING
void run_fire_script (void) 
{
	// si ya teníamos una llave, la deja en esa pantalla. Salva (29/08/18)
	if (flags[TILE_GET_KEY_FLAG] != 99)
	{
		restore_keys_vector(flags[TILE_GET_KEY_FLAG]);
		flags [TILE_GET_KEY_FLAG] = 99;
		sp_PrintAtInv ( 4, 25, WHITE, 16 + (0 % 10));
	}
	run_script (2 * MAP_W * MAP_H + 2);
	flags[3] = 0; // permite pasar de nuevo por las puertas frontales. Salva (12/09/18)
	run_script (n_pant + n_pant + 1);
}
#endif
