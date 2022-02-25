				// guarda la posición X anterior para compararla con la nueva y así saber la dirección
				// Salva (30/09/18)
				en_an_last_x[gpit] = baddies[enoffsmasi].x;

				// linear movement
				active = animate = 1;
				baddies [enoffsmasi].x += baddies [enoffsmasi].mx;
				baddies [enoffsmasi].y += baddies [enoffsmasi].my;
				gpen_cx = baddies [enoffsmasi].x;
				gpen_cy = baddies [enoffsmasi].y;
				gpen_xx = gpen_cx >> 4;
				gpen_yy = gpen_cy >> 4;
			
#ifdef WALLS_STOP_ENEMIES
				if (gpen_cx == baddies [enoffsmasi].x1 || gpen_cx == baddies [enoffsmasi].x2 || mons_col_sc_x ())
					baddies [enoffsmasi].mx = -baddies [enoffsmasi].mx;
				if (gpen_cy == baddies [enoffsmasi].y1 || gpen_cy == baddies [enoffsmasi].y2 || mons_col_sc_y ())
					baddies [enoffsmasi].my = -baddies [enoffsmasi].my;
#else
				if (gpen_cx == baddies [enoffsmasi].x1 || gpen_cx == baddies [enoffsmasi].x2)
					baddies [enoffsmasi].mx = -baddies [enoffsmasi].mx;
				if (gpen_cy == baddies [enoffsmasi].y1 || gpen_cy == baddies [enoffsmasi].y2)
					baddies [enoffsmasi].my = -baddies [enoffsmasi].my;
#endif

				// En la pantalla 6 los enemigos que no empiezan en la esquina izquierda 
				// cambian a X1=0 cuando ya han empezado a moverse. Salva (02/12/18)
				//if (baddies [enoffsmasi].x1 > 0 && baddies [enoffsmasi].x1 < baddies [enoffsmasi].x2)
				//	if (o_pant == 6) baddies [enoffsmasi].x1 = 0; 

#ifdef ENABLE_SHOOTERS
				// Shoot a coco
				if (enemy_shoots && (rand () & TYPE_8_SHOOT_FREQ) == 1) {
					shoot_coco ();
				}
#endif
