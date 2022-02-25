			en_an_count [gpit] ++;
#ifdef ENABLE_FLYING_ENEMIES
			if (gpt != 2) {
#endif
				if (en_an_count [gpit] >= 3)
				{
					en_an_count [gpit] = 0;
					en_an_frame [gpit] = !en_an_frame [gpit];
					
					// cambia la animación según la dirección del sprite. Salva (30/09/18)
					if (en_an_last_x[gpit] <= baddies[enoffsmasi].x)
						en_an_next_frame[gpit] = enem_frames[en_an_base_frame[gpit] + en_an_frame[gpit]];
					else
						en_an_next_frame[gpit] = enem_frames[en_an_base_frame[gpit] + en_an_frame[gpit] + 2];
				}
#ifdef ENABLE_FLYING_ENEMIES 
			} 
			else 
			{
				en_an_next_frame [gpit] = enem_frames [en_an_base_frame [gpit] + (en_an_vx [gpit] > 0)];
			}
#endif