// move arrows
/* arrows are as follows:
	baddies [enoffsmasi].x1/x2, y1 = initial position
	mx = Arrow speed
	x, y = position
	my = state (0: off, 1: on)
	y2 = activate me!
	
	Salva (16/10/18)
*/
				baddies [enoffsmasi].y2 = 0;
				if (baddies [enoffsmasi].my) 
				{
					baddies [enoffsmasi].x += baddies [enoffsmasi].mx;

					if (arrow_frame_ct++ == 2)
					{
						if (baddies [enoffsmasi].x2 > baddies [enoffsmasi].x1)
							en_an_next_frame [gpit] = parrot_sprites + 144;
						else
							en_an_next_frame [gpit] = rat_sprites + 144;
						step();
					}
					else if (arrow_frame_ct == 6)
					{
						if (baddies [enoffsmasi].x2 > baddies [enoffsmasi].x1)
							en_an_next_frame [gpit] = parrot_sprites;
						else
							en_an_next_frame [gpit] = rat_sprites;
						arrow_frame_ct = 0;
						step();
					}

					gpen_cx = baddies [enoffsmasi].x;
					gpen_cy = baddies [enoffsmasi].y;
					active = 1;

					if (baddies [enoffsmasi].x == baddies [enoffsmasi].x2)
						baddies [enoffsmasi].my = 0;
				} 
				else 
				{
					en_an_next_frame [gpit] = sprite_18_a;

					start_arrow = rand() & 255;
					if (start_arrow == 255)
						if (open_doors(baddies [enoffsmasi].y1))
							baddies [enoffsmasi].y2 = 1;		
				}
				
				if (baddies [enoffsmasi].y2) 
				{
					baddies [enoffsmasi].my = 1;
					baddies [enoffsmasi].x = baddies [enoffsmasi].x1;
				}
