				// Move Fanty

				active = killable = animate = 1;
				gpen_cx = en_an_x [gpit] >> 6;
				gpen_cy = en_an_y [gpit] >> 6;
				switch (en_an_state [gpit]) {
					case TYPE_6_IDLE:
						if (distance (gpx, gpy, gpen_cx, gpen_cy) <= SIGHT_DISTANCE)
							en_an_state [gpit] = TYPE_6_PURSUING;
						break;
					case TYPE_6_PURSUING:
						if (distance (gpx, gpy, gpen_cx, gpen_cy) > SIGHT_DISTANCE) {
							en_an_state [gpit] = TYPE_6_RETREATING;
						} else {
							en_an_vx [gpit] = limit (
								en_an_vx [gpit] + addsign (p_x - en_an_x [gpit], FANTY_A),
								-FANTY_MAX_V, FANTY_MAX_V);
							en_an_vy [gpit] = limit (
								en_an_vy [gpit] + addsign (p_y - en_an_y [gpit], FANTY_A),
								-FANTY_MAX_V, FANTY_MAX_V);

							en_an_x [gpit] = limit (en_an_x [gpit] + en_an_vx [gpit], 0, 14336);
							en_an_y [gpit] = limit (en_an_y [gpit] + en_an_vy [gpit], 0, 9216);
						}
						break;
					case TYPE_6_RETREATING:
						en_an_x [gpit] += addsign (baddies [enoffsmasi].x - gpen_cx, 64);
						en_an_y [gpit] += addsign (baddies [enoffsmasi].y - gpen_cy, 64);

						if (distance (gpx, gpy, gpen_cx, gpen_cy) <= SIGHT_DISTANCE)
							en_an_state [gpit] = TYPE_6_PURSUING;
						break;
				}
				gpen_cx = en_an_x [gpit] >> 6;
				gpen_cy = en_an_y [gpit] >> 6;
				if (en_an_state [gpit] == TYPE_6_RETREATING &&
					gpen_cx == baddies [enoffsmasi].x &&
					gpen_cy == baddies [enoffsmasi].y
					)
					en_an_state [gpit] = TYPE_6_IDLE;
