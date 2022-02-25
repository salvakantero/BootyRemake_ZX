// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// playermove.h
// Player movement v5.0 : half-box/point collision
// Copyleft 2013 by The Mojon Twins

// Predefine button detection
// se añade botón arrriba/abajo para escaleras. Salva (10/08/18)
#define BUTTON_FIRE	((gpit & sp_FIRE) == 0)
#define BUTTON_UP	((gpit & sp_UP) == 0)
#define BUTTON_DOWN	((gpit & sp_DOWN) == 0)

// pone a cero una posición del vector de llaves
// y actualiza el marcador. Salva (22/08/18)
void update_keys_vector(unsigned char x, unsigned char y)
{
	unsigned char i, j;
	for(i = 0; i < 9; i++)
	{
		j = n_pant * 9 + i;
		if (num_keys_y[j] == y && num_keys_x[j] == x)
		{
			// guarda la posición anterior (aprovechamos las variables sin uso hotspot_xy)
			hotspot_x = num_keys_x[j];
			hotspot_y = num_keys_y[j];
			// pone la posición a cero (llave en uso)
			num_keys_x[j] = 0;
			num_keys_y[j] = 0;
			// guarda el nº de llave actual
			flags [TILE_GET_KEY_FLAG] = j - (n_pant * 9);
			// pinta en el marcador el nº de llave
			sp_PrintAtInv ( 4, 25, WHITE, 16 + ((flags [TILE_GET_KEY_FLAG] + 1) % 10));
			break;
		}
	}
}


// pone de nuevo activa la llave anterior, al coger una nueva
// restaurando las coordenadas XY. Salva (29/08/18)
void restore_keys_vector(unsigned char key_number)
{
	unsigned int j = n_pant * 9 + key_number;
	num_keys_x[j] = hotspot_x;
	num_keys_y[j] = hotspot_y;
}


// pone a cero una posición del vector de puertas
// y actualiza el marcador de llaves. Salva (22/08/18)
void update_doors_vector(unsigned char x, unsigned char y)
{
	unsigned char i, j;
	for(i = 0; i < 9; i++)
	{
		j = n_pant * 9 + i;			// left				   // right
		if (num_doors_y[j] == y && (num_doors_x[j] == x || num_doors_x[j] == x + 1))
		{
			num_doors_y[j] = 0;
			num_doors_x[j] = 0;
			flags [TILE_GET_KEY_FLAG] = 99;
			sp_PrintAtInv ( 4, 25, WHITE, 16 + (0 % 10));
			break;
		}
	}
}


// devuelve el nº de puerta a partir de su posición XY. Salva (22/08/18)
unsigned char door_number(unsigned char x, unsigned char y)
{
	unsigned char i, j;
	for(i = 0; i < 9; i++)
	{
		j = n_pant * 9 + i;			// left				   // right
		if (num_doors_y[j] == y && (num_doors_x[j] == x || num_doors_x[j] == x + 1))
			break;
	}
	return j - (n_pant * 9);
}


// pone a cero una posición del vector de objetos
// y actualiza el marcador. Salva (25/08/18)
void update_obj_vector(unsigned char x, unsigned char y)
{
	unsigned char i, j;
	for(i = 0; i < 10; i++)
	{
		j = n_pant * 10 + i;
		if (obj_y[j] == y && obj_x[j] == x)
		{
			obj_y[j] = 0;
			obj_x[j] = 0;

			print_number3 ( 6, 23, WHITE+BRIGHT+FLASH, ++flags [TILE_GET_OBJ_FLAG]);
			mainloop1_ct = 22;
			
			print_number3 (19, 23, RED+BRIGHT, 125 - flags [TILE_GET_OBJ_FLAG]);
			break;
		}
	}
}


unsigned char ptx1, ptx2, pty1, pty2, pty3, pt1, pt2, last_gpy;
unsigned char stair_step, slammed_shut, breath_ct, bomb_ct, bomb_x, bomb_y; 
unsigned char anim_tile_get_ct, anim_tile_get_x, anim_tile_get_y, isAnObject;


unsigned char move (void) 
{
	wall_v = wall_h = 0;

	// animación de portazo en la cara. Salva (14/10/18)
	if (slammed_shut) slammed_shut++;
	if (slammed_shut == 4) slammed_shut = 0;

	gpit = (joyfunc) (&keys); // Leemos del teclado

	// ***************************************************************************
	//  MOVEMENT IN THE VERTICAL AXIS
	// ***************************************************************************

	if (do_gravity) 
	{
		// Gravity
		if (p_vy < PLAYER_MAX_VY_CAYENDO)
			p_vy += PLAYER_G;
		else 
			p_vy = PLAYER_MAX_VY_CAYENDO;
	}
	if (p_gotten) p_vy = 0;

	// Move
	p_y += p_vy;

	// Safe
	if (p_y < 0) p_y = 0;
	if (p_y > 9216) p_y = 9216;

	// Handle collision
	// half-box collision. Check for tile behaviour in two points.
	// Which points? It depends on the type of collision configured:

	last_gpy = gpy; // lo guardo para saber si ha llegado al extremo de la escalera. Salva (14/11/18)

	gpx = p_x >> 6;
	gpy = p_y >> 6;

	ptx1 = (gpx + 4) >> 4;
	ptx2 = (gpx + 11) >> 4;
	pty1 = (gpy + 8) >> 4;
	pty2 = (gpy + 15) >> 4;
	hit_v = 0;
	
	if (p_vy + ptgmy < 0) 
	{
		pt1 = attr (ptx1, pty1);
		pt2 = attr (ptx2, pty1);
		if ((pt1 & 8) || (pt2 & 8)) 
		{
			p_vy = 0;
			p_y = ((pty1 + 1) << 10) - 512;
			wall_v = WTOP;
		} 
		else if ((pt1 & 1) || (pt2 & 1)) 
		{
			hit_v = 1;
		}
	} 
	else if (p_vy + ptgmy > 0) 
	{
		pt1 = attr (ptx1, pty2);
		pt2 = attr (ptx2, pty2);
		
		// Greed Optimization tip! Remove this line and uncomment the next one:
		// (As long as you don't have type 8 blocks over type 4 blocks in your game, the short line is fine)
		//if ((pt1 & 8) || (pt2 & 8) || (((gpy - 1) & 15) < 8 && ((pt1 & 4) || (pt2 & 4)))) {
		//if (((gpy - 1) & 15) < 7 && ((pt1 & 12) || (pt2 & 12))) {
		
		// se cambia la condición para que el player solo caiga por las escaleras
		// al pulsar botón abajo. Salva (15/08/18)
		if  ((pt1 & 8) || (pt2 & 8) || (((gpy - 1) & 15) < 8 && 
			((pt1 == 4) || (pt2 == 4) || ((pt1 == 68 || pt2 == 68) && !BUTTON_DOWN)))) 
		{					
			p_vy = 0;
			p_y = ((pty2 - 1) << 10);
			wall_v = WBOTTOM;
		} 
		else if ((pt1 & 1) || (pt2 & 1)) 
		{
			hit_v = 1;
		}
	}
	
	gpxx = gpx >> 4;
	gpyy = gpy >> 4;
	
	// Possee
	gpy = p_y >> 6;
	pty3 = (gpy + 16) >> 4;
	possee = ((attr (ptx1, pty3) & 12) || (attr (ptx2, pty3) & 12)) && (gpy & 15) < 8;
		
	// contador de ciclos de player cayendo. Salva (01/12/18)
	if (!possee && !p_gotten && p_estado == EST_NORMAL)
	{
		if (pt1!=68) 
			falling_ct++;
	}
	else
	{
		if (falling_ct > 11) // player cae demasiado alto
			hit_v = 1;			
		falling_ct = 0;	
	}
	
	// *************
	// Jumping Jack!
	// *************

// solo sube cuando se encuentra sobre escaleras. Salva (27/07/18)
#ifdef PLAYER_HAS_JUMP
		if (BUTTON_UP)	// Tile number must be 68; 64(stair) + 4(platform)
		{		
			if (p_saltando == 0 && (pt1 == 68 || pt2 == 68) && possee) 
			{
				p_saltando = 1;
				p_cont_salto = 0;
			}
			
			if (p_saltando) 
			{
				p_vy -= (PLAYER_VY_INICIAL_SALTO + PLAYER_INCR_SALTO - (p_cont_salto>>1));
				if (p_vy < -PLAYER_MAX_VY_SALTANDO) 
					p_vy = -PLAYER_MAX_VY_SALTANDO;
				p_cont_salto ++;
				if (pt1 == 0 || pt2 == 0)
					p_saltando = 0;
			}
		}
		else
			if (p_saltando == 1 && pt1 != 68) 
				p_saltando = 0;
#endif

	// ***************************************************************************
	//  MOVEMENT IN THE HORIZONTAL AXIS
	// ***************************************************************************

	// Controller
	if (possee || p_gotten) // Solo se mueve en X si no está cayendo. Salva (06/10/18)
	{
		if (!((gpit & sp_LEFT) == 0 || (gpit & sp_RIGHT) == 0)) 
		{
			if (p_vx > 0) 
			{
				p_vx -= PLAYER_RX; if (p_vx < 0) p_vx = 0;
			}
			else if (p_vx < 0) 
			{
				p_vx += PLAYER_RX; if (p_vx > 0) p_vx = 0;
			}
		}

		if ((gpit & sp_LEFT) == 0) 
		{
			if (p_vx > -PLAYER_MAX_VX) 
			{
				p_facing = 0;
				p_vx -= PLAYER_AX;
			}
		}

		if ((gpit & sp_RIGHT) == 0) 
		{
			if (p_vx < PLAYER_MAX_VX) 
			{
				p_vx += PLAYER_AX;
				p_facing = 1;
			}
		}

		// Move
		if (last_gpy == gpy)
			p_x = p_x + p_vx;
		if (p_gotten) p_x += ptgmx;
		
		// Safe
		if (p_x < 0) p_x = 0;
		if (p_x > 14336) p_x = 14336;
	}

	// Handle collision
	// half-box collision. Check for tile behaviour in two points.
	// Which points? It depends on the type of collision configured:	
	gpx = p_x >> 6;
	gpy = p_y >> 6;

	ptx1 = (gpx + 4) >> 4;
	ptx2 = (gpx + 11) >> 4;
	pty1 = (gpy + 8) >> 4;
	pty2 = (gpy + 15) >> 4;

	hit_h = 0;

	if (p_vx + ptgmx < 0) 
	{
		pt1 = attr (ptx1, pty1);
		pt2 = attr (ptx1, pty2);
		if ((pt1 & 8) || (pt2 & 8)) 
		{
			p_vx++;
			p_x = ((ptx1 + 1) << 10) - 256;
			wall_h = WLEFT;
		} 
		else if ((pt1 & 1) || (pt2 & 1)) 
		{
			hit_h = 1;
		}
	} 
	else if (p_vx + ptgmx > 0) 
	{
		pt1 = attr (ptx2, pty1);
		pt2 = attr (ptx2, pty2);
		if ((pt1 & 8) || (pt2 & 8))
		{
			p_vx++;
			p_x = ((ptx2 - 1) << 10) + 256;
			wall_h = WRIGHT;
		} 
		else if ((pt1 & 1) || (pt2 & 1)) 
		{
			hit_h = 1;
		}
	}

	// **********
	// Evil tiles
	// **********

	// hit_v tiene preferencia sobre hit_h
	hit = 0;

	if (hit_v) 
	{
		hit = 1;
		p_vy = -p_vy;
	} 
	else if (hit_h) 
	{
		hit = 1;
		p_vx = -p_vx;
	}

	if (hit) 
	{
		if (p_life > 0 && p_estado == EST_NORMAL)			
			kill_player (6);
	}

	// ********
	// Tile get 
	// ********		Salva (22/08/18)
	
#ifdef TILE_GET_KEY
	gpxx = (gpx + 8) >> 4;
	gpyy = (gpy + 8) >> 4;
	
	// llaves
	if (qtile (gpxx, gpyy) == TILE_GET_KEY) 
	{
		// si ya teníamos una llave
		if (flags[TILE_GET_KEY_FLAG] != 99)
		{
			if (anim_tile_get_ct > 0) // detiene la animación tile_get anterior
			{	
				update_tile(anim_tile_get_x, anim_tile_get_y, 0, 0); // tile de fondo en la pos.anterior
				anim_tile_get_ct = 0;
			}
			// restaura la llave anterior
			restore_keys_vector(flags[TILE_GET_KEY_FLAG]); // coordenadas XY
			update_tile(hotspot_x/2, hotspot_y/2, 0, TILE_GET_KEY); // llave
			sp_PrintAtInv (hotspot_y + VIEWPORT_Y, hotspot_x, WHITE+BRIGHT, 
						   16 + ((flags[TILE_GET_KEY_FLAG]+1) % 10)); // número
		}		
		
		// coge la nueva llave
		update_keys_vector(gpxx*2, gpyy*2);

		// inicia la animación de recogida de tile
		if (anim_tile_get_ct == 0)
		{
			anim_tile_get_ct = 10;
			anim_tile_get_x = gpxx;
			anim_tile_get_y = gpyy;
			isAnObject = 0;
		}

		if (anim_tile_get_ct == 10)
			wyz_play_sound(0);
	}

	// puertas
	else if (qtile (gpxx, gpyy) == TILE_GET_DOOR_DOWN) 
	{
		if (flags[TILE_GET_KEY_FLAG] == door_number(gpxx*2, ((gpyy-1)*2) + 1))
		{
			update_tile(gpxx, gpyy, 0, 0);
			update_tile(gpxx, gpyy - 1, 4, 2);
			
			// imprime de nuevo el nº de puerta
			sp_PrintAtInv ((gpyy * 2) + VIEWPORT_Y - 1, 
							gpxx * 2 > 14 ? gpxx * 2 : gpxx * 2 + 1, RED, 
							16 + ((flags[TILE_GET_KEY_FLAG] + 1) % 10));
			
			update_doors_vector(gpxx * 2, ((gpyy - 1) * 2) + 1);
			wyz_play_sound(8);
		}
		else
		{
			// rebota en la puerta si no tiene llave.
			p_vx = -p_vx;
			slammed_shut++;
			wyz_play_sound(7);
		}
	}

	// objetos
	else if (qtile (gpxx, gpyy) >= TILE_GET_OBJ_MIN && qtile (gpxx, gpyy) <= TILE_GET_OBJ_MAX) 
	{
		if (anim_tile_get_ct > 0) // detiene la animación tile_get anterior
		{	
			update_tile(anim_tile_get_x, anim_tile_get_y, 0, 0); // tile de fondo en la posición anterior
			anim_tile_get_ct = 0;
		}

		//coge el objeto
		update_obj_vector(gpxx, gpyy);

		//inicia la animación tile_get
		if (anim_tile_get_ct == 0)
		{
			anim_tile_get_ct = 10;
			anim_tile_get_x = gpxx;
			anim_tile_get_y = gpyy;
			isAnObject = 1;
		}
		wyz_play_sound(2);
	}

	// secuencias de animación pendientes al coger llaves u objetos. Salva (20/10/18)
	if (anim_tile_get_ct > 0)
	{
		if (anim_tile_get_ct == 1) 
		{	
			if (!isAnObject) // llave
			{	
				update_tile(anim_tile_get_x, anim_tile_get_y, 0, 0);
			}
			else if (bomb_ct < 2) // objeto
			{
				// posible bomba tras coger objeto?
				bomb_x = rand() & 255;

				if (bomb_x > 170)
				{
					bomb_ct = 25;
					bomb_x = anim_tile_get_x;
					bomb_y = anim_tile_get_y;
					update_tile(bomb_x, bomb_y, 0, 34); // pinta bomba
					wyz_play_sound(9);
				}
				else // no pinta bomba
					update_tile(anim_tile_get_x, anim_tile_get_y, 0, 0);
			}
			else // no pinta bomba porque ha salido otra en otra posición
				update_tile(anim_tile_get_x, anim_tile_get_y, 0, 0);
		}
		else if (anim_tile_get_ct == 4) update_tile(anim_tile_get_x, anim_tile_get_y, 0, 32); // magia 1
		else if (anim_tile_get_ct == 7) update_tile(anim_tile_get_x, anim_tile_get_y, 0, 33); // magia 2
		else if (anim_tile_get_ct == 10) update_tile(anim_tile_get_x, anim_tile_get_y, 0, 32); // magia 1
		anim_tile_get_ct--;
	}

	// explosión de bomba
	if (bomb_ct > 1)
	{
		bomb_ct--;
		if (bomb_ct == 5)
		{
			// ha pillado a Jim?
			if (p_estado == EST_NORMAL && 
			//(ptx1 == bomb_x && pty1 == bomb_y) || (ptx2 == bomb_x && pty2 == bomb_y)) // fácil
			((ptx1 >= bomb_x - 1 && ptx2 <= bomb_x + 1) && 
			 (pty1 >= bomb_y - 1 && pty2 <= bomb_y + 1))) // difícil
				kill_player(6);
			else
				wyz_play_sound(6);

			update_tile(bomb_x , bomb_y, 0, 35); // pinta explosión			
		}
		if (bomb_ct == 1) update_tile(bomb_x, bomb_y, 0, 0);
	}

#endif

	// **********************
	// Select animation frame
	// **********************

	// animación sobre la escalera. Salva (08/10/18) 
	if (((BUTTON_DOWN || BUTTON_UP) && pt1 == 68)) 
	{
		if (gpy != last_gpy) // detiene la animación al llegar al extremo inferior de la escalera
		{
			if (stair_step++ <= 3) p_next_frame = player_frames [8];
			else if (stair_step <= 6) p_next_frame = player_frames [9];
			else stair_step = 0;
		}
	}
	// animación cayendo
	else if (!possee && !p_gotten)
		p_next_frame = sprite_24_a;
	else // otras animaciones
	{
		if (slammed_shut > 0 || hit) // portazo en la cara o choque. Salva (14/10/18)
			p_next_frame = sprite_17_a;
		else
		{
			gpit = p_facing << 2;
			if (p_vx == 0) 
			{
				// animación de Jim respirando. Salva (10/11/18)
				if (breath_ct++ < 6)
				{
					if (gpit) p_next_frame = sprite_23_a;
					else p_next_frame = sprite_22_a;
				}
				else if (breath_ct < 11)
					p_next_frame = player_frames [gpit + 1];
				else
					breath_ct = 0;
			} 
			else 
			{
				p_subframe ++;
				if (p_subframe == 2) //4
				{
					p_subframe = 0;
					p_frame = (p_frame + 1) & 3;
					step ();
				}
				p_next_frame = player_frames [gpit + p_frame];
			}
		}
	}
}