// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// flickscreen.h
// Flicking screen logic... REHASH!

	#define SCREEN_LEFT	n_pant - 1
	#define SCREEN_RIGHT n_pant + 1
	#define SCREEN_UP n_pant - MAP_W
	#define SCREEN_DOWN n_pant + MAP_W
	#define MAP_BOUNDARY_LEFT
	#define MAP_BOUNDARY_RIGHT
	#define MAP_BOUNDARY_TOP
	#define MAP_BOUNDARY_BOTTOM


void flick_screen (void) 
{
	gpit = (joyfunc) (&keys);	
	// Momentum engine edge screen detection
	if (p_x == 0 && p_vx < 0 MAP_BOUNDARY_LEFT) {
		n_pant = SCREEN_LEFT; p_x = 14336;
	}
	if (p_x == 14336 && p_vx > 0 MAP_BOUNDARY_RIGHT) {
		n_pant = SCREEN_RIGHT; p_x = 0;
	}
	if (p_y == 0 && p_vy < 0 MAP_BOUNDARY_TOP) {
		n_pant = SCREEN_UP; p_y = 9216;
	}
	if (p_y == 9216 && p_vy > 0 MAP_BOUNDARY_TOP) {
		n_pant = SCREEN_DOWN; p_y = 0;
		if (p_vy > 256) p_vy = 256;
	}	
}
