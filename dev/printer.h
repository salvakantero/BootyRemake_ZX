// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// printer.h
// Printing functions

#define MESSAGE_COLOUR 56 // 32=negro/verde  79=blanco/azul (Salva 27/07/18)
unsigned char *spacer = "           ";

unsigned char attr (char x, char y) 
{
	// x + 15 * y = x + (16 - 1) * y = x + 16 * y - y = x + (y << 4) - y.
	if (x < 0 || y < 0 || x > 14 || y > 9) return 0;
	return map_attr [x + (y << 4) - y];
}

unsigned char qtile (unsigned char x, unsigned char y) 
{
	// x + 15 * y = x + (16 - 1) * y = x + 16 * y - y = x + (y << 4) - y.
	return map_buff [x + (y << 4) - y];
}

/*
// pinta la pantalla tomando los colores de determinados vectores. Salva (31/08/18)
void draw_coloured_tile (unsigned char x, unsigned char y, unsigned char t, unsigned char half) 
{
	unsigned char xx, yy, color_ti;
	unsigned char tn = t; // nº de tile		
	t = 64 + (t << 2);

	// mitad superior del tile
	if ((tn > 1 && tn < 8) || (tn > 29 && tn < 32)) // tiles plataforma
	{
		sp_PrintAtInv (y, x, platform_color[n_pant], t ++); // 1 de 4
		sp_PrintAtInv (y, x + 1, platform_color[n_pant]+BRIGHT, t ++); // 2 de 4
		color_ti = screen_color[n_pant];
	}
	else // tiles normales
	{
		sp_PrintAtInv (y, x, screen_color[n_pant] + BRIGHT, t ++); // 1 de 4
		sp_PrintAtInv (y, x + 1, screen_color[n_pant] + BRIGHT, t ++); // 2 de 4
		color_ti = screen_color[n_pant] + BRIGHT;
	}

	// mitad inferior del tile
	if (half == 0) 
	{
		if (tn==5 || tn==3) // antorcha o lámpara (+BRIGHT)
		{
			sp_PrintAtInv (y + 1, x, color_ti+BRIGHT, t ++); // 3 de 4
			sp_PrintAtInv (y + 1, x + 1, color_ti+BRIGHT, t); // 4 de 4
		}
		else
		{
			sp_PrintAtInv (y + 1, x, color_ti, t ++); // 3 de 4
			sp_PrintAtInv (y + 1, x + 1, color_ti, t); // 4 de 4
		}
	}
	else
		t ++; // no pinta la parte inferior del tile
}*/

void draw_coloured_tile (unsigned char x, unsigned char y, unsigned char t, unsigned char half) {
	t = 64 + (t << 2);
	gen_pt = tileset + 2048 + t;
	sp_PrintAtInv (y, x, *gen_pt ++, t ++);
	sp_PrintAtInv (y, x + 1, *gen_pt ++, t ++);
	sp_PrintAtInv (y + 1, x, *gen_pt ++, t ++);
	sp_PrintAtInv (y + 1, x + 1, *gen_pt, t);
}


void draw_coloured_tile_gamearea (unsigned char x, unsigned char y, unsigned char tn, unsigned char half) 
{
	draw_coloured_tile (VIEWPORT_X + (x << 1), VIEWPORT_Y + (y << 1), tn, half);
}


// imprime números con tres o dos cifras y color. Salva (01/08/18)
void print_number3 (unsigned char x, unsigned char y, unsigned char c, unsigned char number) 
{
	sp_PrintAtInv (y, x, c, 16 + (number / 100));
	sp_PrintAtInv (y, x + 1, c, 16 + ((number / 10) % 10));
	sp_PrintAtInv (y, x + 2, c, 16 + (number % 10));
}

void print_number2 (unsigned char x, unsigned char y, unsigned char c, unsigned char number) 
{
	sp_PrintAtInv (y, x, c, 16 + (number / 10));
	sp_PrintAtInv (y, x + 1, c, 16 + (number % 10));
}

void print_str (unsigned char x, unsigned char y, unsigned char c, unsigned char *s) 
{
	while (*s) sp_PrintAtInv (y, x ++, c, (*s ++) - 32);
}

unsigned char utaux = 0;

void update_tile (unsigned char x, unsigned char y, unsigned char b, unsigned char t) 
{
	utaux = (y << 4) - y + x;
	map_attr [utaux] = b;
	map_buff [utaux] = t;
	draw_coloured_tile_gamearea (x, y, t, 0);
}

void print_message (unsigned char *s) 
{
	print_str (10, 12, MESSAGE_COLOUR, spacer);
	print_str (10, 13, MESSAGE_COLOUR, s);
	print_str (10, 14, MESSAGE_COLOUR, spacer);
	sp_UpdateNow ();
	sp_WaitForNoKey ();
}

