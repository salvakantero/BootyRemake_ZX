// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// mainloop.h
// This is, the main game loop (plus initializations, plus menu, plus level screen...

void saca_a_todo_el_mundo_de_aqui (unsigned char which_ones) 
{
	if (which_ones == 0) 
		sp_MoveSprAbs (sp_player, spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);
	for (gpit = 0; gpit < MAX_ENEMS; gpit ++)
		sp_MoveSprAbs (sp_moviles [gpit], spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);
}

unsigned char action_pressed;
unsigned char life_old;

#ifdef PAUSE_ABORT
int key_x;
int key_m;
#endif

unsigned char success, playing;
unsigned char loop_ct, song = 3; // Salva (25/10/18)

void print_str_rebonico(unsigned char x, unsigned char y, unsigned char *s)
{
	unsigned char i;
	for(i=0; i < 8; i++)
	{	
		print_str(x, y, i, s);
		sp_UpdateNow();
		#asm
			halt
			halt
		#endasm
	}
}


// se reinician los valores XY de todas las puerta, objetos y llaves. Salva (01/11/18)
void init_screen_items()
{			
	for(loop_ct = 0; loop_ct < 180; loop_ct++) // puertas y llaves
	{
		num_doors_x[loop_ct] = num_doors_x_base[loop_ct];
		num_doors_y[loop_ct] = num_doors_y_base[loop_ct];
		num_keys_x [loop_ct] = num_keys_x_base[loop_ct];
		num_keys_y [loop_ct] = num_keys_y_base[loop_ct];			
	}
	for(loop_ct = 0; loop_ct < 200; loop_ct++) // objetos
	{
		obj_x [loop_ct] = obj_x_base[loop_ct];
		obj_y [loop_ct] = obj_y_base[loop_ct];			
	}
	for(loop_ct = 0; loop_ct < (MAP_W * MAP_H * MAX_ENEMS); loop_ct++) // enemigos
	{
		baddies[loop_ct].x = baddies[loop_ct].x1;
		baddies[loop_ct].y = baddies[loop_ct].y1;
		baddies[loop_ct].mx = en_an_mx_base[loop_ct];
		baddies[loop_ct].my = en_an_my_base[loop_ct];
	}
}


// Plataformas que aparecen y desaparecen en determinadas pantallas. Salva (25/10/18)
void plataformas_quitapon(void)
{
	if (o_pant == 4 || o_pant == 13 || o_pant == 14 || o_pant == 19)
	{
		unsigned char x, y;

		if (o_pant == 19)
		{
			x = 8;
			y = 6;
		}
		else if (o_pant == 14)
		{
			x = 10;
			y = 2;
		}
		else if (o_pant == 4)
		{
			x = 2;
			y = 6;
		}
		else
		{
			x = 2;
			y = 2;	
		}

		if (o_pant != 13)
		{
			if (loop_ct == 40 || loop_ct == 120 || loop_ct == 210)
			{
				update_tile(x,   y, 4, 2);
				update_tile(x+1, y, 4, 2);
				if (o_pant == 4)
				{
					update_tile(x+3, y, 4, 2);
					update_tile(x+4, y, 4, 2);
					update_tile(x+6, y, 4, 2);
					update_tile(x+7, y, 4, 2);
				}
			}
			else if (loop_ct == 70 || loop_ct == 150 || loop_ct == 240)
			{
				update_tile(x,   y, 0, 0);
				update_tile(x+1, y, 0, 0);
				if (o_pant == 4)
				{
					update_tile(x+3, y, 0, 0);
					update_tile(x+4, y, 0, 0);
					update_tile(x+6, y, 0, 0);
					update_tile(x+7, y, 0, 0);
				}
			}
		}
		else
		{
			if (loop_ct == 128)
			{
				update_tile(x, y,   0, 0);
				update_tile(x, y+2, 4, 2);						
			}
			else if (loop_ct == 254)
			{
				update_tile(x, y,   4, 2);
				update_tile(x, y+2, 0, 0);
			}
		}
	}
}


// Main loop
void main (void) 
{
	// *********************
	// SYSTEM INITIALIZATION
	// *********************

	cortina ();

	#asm
		di
	#endasm

#ifdef MODE_128K
	// Install ISR
	sp_InitIM2(0xf1f1);
	sp_CreateGenericISR(0xf1f1);
	sp_RegisterHook(255, ISR);
#endif
	// splib2 initialization
	sp_Initialize (0, 0);
	sp_Border (BLACK);

	// Reserve memory blocks for sprites
	sp_AddMemory(0, NUMBLOCKS, 14, AD_FREE);

#ifdef PAUSE_ABORT
	key_x = 0x04fe;
	key_m = 0x047f;
#endif

	joyfunc = sp_JoyKeyboard;

	// Load tileset
	gen_pt = tileset;
	gpit = 0; 
	do 
	{
		sp_TileArray (gpit, gen_pt);
		gen_pt += 8;
		gpit ++;
	}
	while (gpit);

	// Clipping rectangle
	spritesClipValues.row_coord = VIEWPORT_Y;
	spritesClipValues.col_coord = VIEWPORT_X;
	spritesClipValues.height = 20;
	spritesClipValues.width = 30;
	spritesClip = &spritesClipValues;

	// Sprite creation
	sp_player = sp_CreateSpr (sp_MASK_SPRITE, 3, sprite_2_a, 1, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_2_b, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_2_c, TRANSPARENT);
	p_current_frame = p_next_frame = sprite_2_a;

	for (gpit = 0; gpit < MAX_ENEMS; gpit ++) 
	{
		sp_moviles [gpit] = sp_CreateSpr(sp_MASK_SPRITE, 3, sprite_9_a, 3, TRANSPARENT);
		sp_AddColSpr (sp_moviles [gpit], sprite_9_b, TRANSPARENT);
		sp_AddColSpr (sp_moviles [gpit], sprite_9_c, TRANSPARENT);
		en_an_current_frame [gpit] = en_an_next_frame [gpit] = sprite_9_a;
	}

	#asm
		ei
	#endasm

	// Music player initialization
	wyz_init ();

	// guarda las direcciones iniciales de los enemigos para recuperarlas al inicio
	// de cada partida. Salva (07/11/18)
	for(loop_ct = 0; loop_ct < (MAP_W * MAP_H * MAX_ENEMS); loop_ct++)
	{
		en_an_mx_base[loop_ct] = baddies[loop_ct].mx;
		en_an_my_base[loop_ct] = baddies[loop_ct].my;
	}

	while (1) 
	{
		// ************
		// TITLE SCREEN
		// ************
		sp_UpdateNow();

		while (1) 
		{			
			// actualiza contadores para la presentación de datos
			if (mainloop1_ct++ == 255)
			{
				mainloop1_ct = 0;
				mainloop2_ct++;
			}

			if (mainloop2_ct == 0) // pantalla 1. Menú principal
			{
				get_resource (0, 16384);
				_AY_PL_MUS(1);							
				print_str(8, 7, WHITE, "CHOOSE OPTION:");			
				print_str_rebonico(6, 9, "1 KEYBOARD QAOP/SPC");
				print_str(6, 9, CYAN, "1 KEYBOARD QAOP/SPC");				
				print_str_rebonico(6, 10, "2 KEYBOARD WASD/SPC");
				print_str(6,10, GREEN, "2 KEYBOARD WASD/SPC");
				print_str_rebonico(6, 11, "3 KEMPSTON JOYSTICK");
				print_str(6,11, MAGENTA, "3 KEMPSTON JOYSTICK");
				print_str_rebonico(6, 12, "4 SINCLAIR JOYSTICK");
				print_str(6,12, RED, "4 SINCLAIR JOYSTICK");
				print_str_rebonico(6, 13, "5 DEMO MODE");
				print_str(6,13, BLUE+BRIGHT, "5 DEMO MODE");
				mainloop2_ct++;				
			}			
			else if (mainloop2_ct == 9) // para la música de intro
			{
				_AY_ST_ALL();
			}
			else if (mainloop2_ct == 10) // pantalla 2. Ayuda ingame
			{
				get_resource (3, 16384);				
				mainloop2_ct++;
			}
			else if (mainloop2_ct == 20) // pantalla 3. LLaves
			{
				get_resource (4, 16384);
				mainloop2_ct++;
			}
			else if (mainloop2_ct == 30) // pantalla 4. El botín
			{
				get_resource (5, 16384);
				mainloop2_ct++;
			}
			else if (mainloop2_ct == 40)
				mainloop1_ct = mainloop2_ct = 0;

			sp_UpdateNow();	

			gpit = sp_GetKey ();
		
			if (gpit == '1' || gpit == '2') 
			{
				joyfunc = sp_JoyKeyboard;
				gpjt = (gpit - '1') ? 6 : 0;
				
				/*
				Q = 0x01fb
				A = 0x01fd
				O = 0x02df
				P = 0x01df

				W = 0x02fb
				S = 0x02fd
				D = 0x04fd

				SPACE = 0x017f
				N = 0x087f
				M = 0x047f
				*/

				if (gpit == '1')
				{	
					keys.up = 0x01fb; 		// Q
					keys.down = 0x01fd;		// A
					keys.left = 0x02df;		// O
					keys.right = 0x01df;	// P
					keys.fire = 0x017f;		// SPACE
					break;
				}
				else
				{			
					keys.up = 0x02fb;		// W
					keys.down = 0x02fd;		// S
					keys.left = 0x01fd;		// A
					keys.right = 0x04fd;	// D
					keys.fire = 0x017f;		// SPACE
					break;
				}
			} 
			else if (gpit == '3') 
			{
				joyfunc = sp_JoyKempston;
				break;
			} 
			else if (gpit == '4') 
			{
				joyfunc = sp_JoySinclair1;
				break;
			}
			else if (gpit == '5') // carrusel de pantallas. Salva (11/12/18)
			{
				unsigned char index;
				main_script_offset = (unsigned int) (SCRIPT_INIT);
				_AY_PL_MUS (0);
				init_screen_items();
				for (index = 0; index < 20; index++)
				{
					n_pant = o_pant = index;				
					draw_scr();
					print_str ( 0, 23, BLUE+BRIGHT, "DEMO  (PRESS ANY KEY) ");
					print_number2 (28, 23, CYAN+BRIGHT, n_pant+1);
					loop_ct = 0;
					while(loop_ct < 160)
					{
						mueve_bicharracos ();
						do_tilanims ();

						for (gpit = 0; gpit < MAX_ENEMS; gpit ++) 
						{
							enoffsmasi = enoffs + gpit;
							gpen_x = baddies [enoffsmasi].x;							
							if (baddies[enoffsmasi].y < 127)
								gpen_y = baddies [enoffsmasi].y;
							else
								gpen_y = 127;
							
							sp_MoveSprAbs ( sp_moviles [gpit], spritesClip, 
								en_an_next_frame [gpit] - en_an_current_frame [gpit], 
								VIEWPORT_Y + (gpen_y >> 3), VIEWPORT_X + (gpen_x >> 3),
								gpen_x & 7, gpen_y & 7);
							
							en_an_current_frame [gpit] = en_an_next_frame [gpit];
						}
						plataformas_quitapon();							
					
						if (sp_GetKey() != 0)
						{	
							saca_a_todo_el_mundo_de_aqui(1);
							index=20;
							_AY_ST_ALL();
							break;
						}
						loop_ct++;
						sp_UpdateNow();
					}
				}
				_AY_ST_ALL();
				mainloop1_ct = mainloop2_ct = 0;
				saca_a_todo_el_mundo_de_aqui(1);
				cortina();
				sp_UpdateNow();
			}
			else if (gpit != 0)
			{
				mainloop1_ct = mainloop2_ct = 0;
			}
		}

		mainloop1_ct = mainloop2_ct = 0;

		// *******************
		// GAME INITIALIZATION
		// *******************
		script_result = 0;

		// ********************
		// LEVEL INITIALIZATION
		// ********************

		playing = 1;
		main_script_offset = (unsigned int) (SCRIPT_INIT);	
		n_pant = SCR_INICIO;
		init_player ();
		maincounter = 0;
		script_result = 0;

		// Entering game script
		run_script (MAP_W * MAP_H * 2);

		do_respawn = 1;
		life_old = 0xff;
		success = 0;

		// music ON		
		muted = 1;		
		
		o_pant = 0xff;
		no_draw = 0;

		// valores iniciales para marcadores y variables. Salva (21/08/18)
		print_number3 ( 6, 23, GREEN+BRIGHT, 0); // booty
		print_number3 (19, 23, RED+BRIGHT, 125); // treasure
		sp_PrintAtInv ( 4, 25, WHITE, 16 + (0 % 10)); // nº llave
		
		flags[TILE_GET_KEY_FLAG] = 99; // número de llave en uso
		flags[TILE_GET_OBJ_FLAG] = 0; // nº de objetos recogidos
		anim_tile_get_ct = 0; // animación de recogida de objetos
		bomb_ct = 0; // animación de recogida de bombas
		falling_ct = 0; // altura de la caída
		init_screen_items();

		// *********
		// MAIN LOOP
		// *********

		while (playing) 
		{
			if (n_pant != o_pant) 
			{
				// play song
				if (muted == 1)
				{
					if (song == 6) song = 3;
					_AY_PL_MUS (song++);
				}

				o_pant = n_pant;
				draw_scr ();
				
				// Nº de pantalla. Salva (18/08/18)
				print_number2 (28, 23, CYAN+BRIGHT, n_pant+1);

				// reinicia la posición de los enemigos de la pantalla
				for (gpit = 0; gpit < MAX_ENEMS; gpit ++)
				{
					enoffsmasi = enoffs + gpit;				
					baddies[enoffsmasi].x = baddies[enoffsmasi].x1;
					baddies[enoffsmasi].y = baddies[enoffsmasi].y1;
					baddies[enoffsmasi].mx = en_an_mx_base[enoffsmasi];
					baddies[enoffsmasi].my = en_an_my_base[enoffsmasi];
				}
				// otros reinicios
				stair_step = slammed_shut = breath_ct = bomb_ct = falling_ct = 0;
			}

			if (p_life != life_old) 
			{
				// permite ver la animación del toque al perder una vida. Salva (15/10/18)
				espera_activa(10);
				
				// las siguientes dos líneas hacen que podamos utilizar 
				// player_flickers y que se vea la animación de toque
				p_estado = EST_PARP;
				p_ct_estado = 40;
				
				//print_number2 (LIFE_X, LIFE_Y, p_life); 
				// imprime el nº de vidas con una sola cifra. Salva (05/08/18)
				sp_PrintAtInv (LIFE_Y, LIFE_X, WHITE, 16 + (p_life % 10));
				
				life_old = p_life;
				
				// Pone a Jim en las coordenadas iniciales. Salva (05/09/18)
				p_x = p_x_ini;
				p_y = p_y_ini;		
			}

			maincounter ++;
			half_life = !half_life;

			// para el flash del contador de objetos
			if (mainloop1_ct == 1)
			{
				print_number3 ( 6, 23, GREEN+BRIGHT, flags [TILE_GET_OBJ_FLAG]);
				mainloop1_ct--;
			}
			else if (mainloop1_ct > 0) 
				mainloop1_ct--;
			
			// Move player
			move ();

			// Move enemies
			mueve_bicharracos ();

			do_tilanims ();

			for (gpit = 0; gpit < MAX_ENEMS; gpit ++) 
			{
				enoffsmasi = enoffs + gpit;

				gpen_x = baddies [enoffsmasi].x;
				
				// No bajan de y=127 para no pisar marcadores
				if (baddies[enoffsmasi].y < 127) gpen_y = baddies [enoffsmasi].y; 
				else gpen_y = 127;

				sp_MoveSprAbs ( sp_moviles [gpit], 
								spritesClip, 
								en_an_next_frame [gpit] - en_an_current_frame [gpit], 
								VIEWPORT_Y + (gpen_y >> 3), 
								VIEWPORT_X + (gpen_x >> 3),
								gpen_x & 7, 
								gpen_y & 7);

				en_an_current_frame [gpit] = en_an_next_frame [gpit];
			}

			if ( !(p_estado & EST_PARP) || half_life == 0) 
			{
				sp_MoveSprAbs (sp_player, spritesClip, p_next_frame - p_current_frame, VIEWPORT_Y + (gpy >> 3), VIEWPORT_X + (gpx >> 3), gpx & 7, gpy & 7);
			} 
			else 
			{				
				sp_MoveSprAbs (sp_player, spritesClip, p_next_frame - p_current_frame, -2, -2, 0, 0);
			}

			p_current_frame = p_next_frame;
			plataformas_quitapon();

			// Update to screen
			sp_UpdateNow();

			// Flickering
			if (p_estado == EST_PARP) 
			{
				p_ct_estado --;
				if (p_ct_estado == 0)
					p_estado = EST_NORMAL;
			}

			// Flick screen checks and scripting related stuff
			gpit = (joyfunc) (&keys);

			if ((gpit & sp_FIRE) == 0) 
			{
				if (action_pressed == 0 && qtile (gpxx, gpyy) == 10)  
				{
					action_pressed = 1;
					// Any scripts to run in this screen?
					run_fire_script ();
				}
			} 
			else 
				action_pressed = 0;

#ifdef PAUSE_ABORT
			// Pause/Abort handling
			if (sp_KeyPressed (key_x)) 
			{
				playing = 0;
			}
			if (sp_KeyPressed (key_m)) // aplica MUTED. Salva(01/11/18) 
			{
				sp_WaitForNoKey ();
				if (muted == 0)
				{
					_AY_PL_MUS (song - 1);
					muted = 1;
				}
				else
				{
					_AY_ST_ALL ();
					muted = 0;
				}
			}
#endif

			// Win game condition
			if (flags[TILE_GET_OBJ_FLAG] == 125) // gana al coger los 125 tesoros. Salva (22/12/18)
			{
				success = 1;	// Next
				playing = 0;
			}

			// Game over condition
			if (p_life == 0	|| script_result == 2) 
			{
				playing = 0;
			}

			if (++loop_ct == 255) // Resetea el contador de loops. Salva (25/10/18) 
				loop_ct = 0;
		
			// Main loop is done!
		}

		_AY_ST_ALL ();
		saca_a_todo_el_mundo_de_aqui (0);
		sp_UpdateNow ();

		if (success) 
		{
			_AY_PL_MUS(1);
			game_ending ();

			while(1)
				if (sp_GetKey() == 'x') 
					break;
		} 
		else 
		{
			sp_PrintAtInv (LIFE_Y, LIFE_X, WHITE, 16 + (0 % 10));
			_AY_PL_MUS (2);
			game_over ();
			espera_activa (220);
		}		
		cortina ();
	}
}