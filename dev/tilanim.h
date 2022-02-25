// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// tilanim.h
// Animated tiles routine. 

// Modificado para animar antorchas. Tiles (5/31) Salva (14/10/18)

#define MAX_TILANIMS 5
#define UPDATE_FREQ 4

unsigned char max_tilanims;
unsigned char tacount;
unsigned char tait, t;

typedef struct 
{
	unsigned char x;
	unsigned char y;
} TILANIM;

TILANIM tilanims [MAX_TILANIMS];


void add_tilanim (unsigned char x, unsigned char y) 
{
	tilanims [max_tilanims].x = x;
	tilanims [max_tilanims].y = y;
	max_tilanims ++;
}


void do_tilanims (void) 
{
	if (max_tilanims == 0) return;

	tacount = (tacount + 1) & UPDATE_FREQ;
	if (!tacount) 
	{
		// Select tile number from list
		tait = rand () % max_tilanims;	
		// select frame
		t = rand () % 2;
		if (t == 0) t = 5; else t = 31;
		// Draw tile
		draw_coloured_tile (VIEWPORT_X + tilanims [tait].x, VIEWPORT_Y + tilanims [tait].y, t, 0);
	}
}