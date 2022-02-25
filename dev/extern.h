// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// extern.h
// External custom code to be run from a script

// =======[CUSTOM MODIFICATION]=======
unsigned char *textbuff = 23458;
unsigned char *extaddress;
unsigned char exti, extx, exty, stepbystep, keyp;
unsigned char is_cutscene = 0;
extern unsigned char textos_load [0];

// Leovigildo B needs 2 compressed images for the endings...
/*
extern const unsigned char im1 [0], im2 [0], imintro [0];
const unsigned char *ims [] = {
	im1, im2
};

#asm
	._im1
		BINARY "f1.bin"
	._im2
		BINARY "f2.bin"
	._imintro
		BINARY "fintro.bin"		
#endasm
*/
//
void cutsc_img (const unsigned char *ptr) {
	cortina ();
	#asm
		ld hl, 16384
		ld de, 16385
		ld bc, 6143
		ld (hl), 0
		ldir
		ld hl, 22528
		ld de, 22529
		ld bc, 767
		ld (hl), 71
		ldir
	#endasm
	unpack ((unsigned int) (ptr), 16384);
}

void do_extern_action (unsigned char n) {
	// Add custom code here.
	// Leovigildo: like Ninjajar plus some extra stuff, but for 48K
	
	if (n == 0) {
		saca_a_todo_el_mundo_de_aqui (0);
		for (exti = 0; exti < 10; exti ++) {
			for (extx = exti; extx < 30 - exti; extx ++) {
				sp_PrintAtInv (VIEWPORT_Y + exti, VIEWPORT_X + extx, 0, 0);
				sp_PrintAtInv (VIEWPORT_Y + 19 - exti, VIEWPORT_X + extx, 0, 0);
				if (extx < 19 - exti) {
					sp_PrintAtInv (VIEWPORT_Y + extx, VIEWPORT_X + exti, 0, 0);
					sp_PrintAtInv (VIEWPORT_Y + extx, VIEWPORT_X + 29 - exti, 0, 0);
				}
			}
#ifdef MODE_128K
			#asm
				halt                    ; esperamos retrazo. 
			#endasm
#endif
			sp_UpdateNow ();
		}
	} else if (n < 250) {
		
		// Show text n
		stepbystep = 1;
		
		asm_int [0] = (n - 1) << 1;
		#asm
			; First we get where to look for the packed string
		
			ld a, (_asm_int)
			ld e, a
			ld a, (_asm_int + 1)
			ld d, a
			
			ld hl, _textos_load
			add hl, de
			ld c, (hl)
			inc hl
			ld b, (hl)
			push bc
			pop de
			ld hl, _textos_load
			add hl, de
			
			ld de, 23458
	
			; 5-bit scaped depacker by na_th_an
			; Contains code by Antonio Villena
			
			ld a, $80
	
		.fbsd_mainb
	        call fbsd_unpackc
	        ld c, a
	        ld a, b
	        and a
	        jr z, fbsd_fin
	        call fbsd_stor
	        ld a, c
	        jr fbsd_mainb	
	
		.fbsd_stor
	        cp 31
	        jr z, fbsd_escaped
	        add a, 64
	        jr fbsd_stor2
		.fbsd_escaped
	        ld a, c
	        call fbsd_unpackc
	        ld c, a
	        ld a, b
	        add a, 32
		.fbsd_stor2
	        ld (de), a
	        inc de
	        ret
	
		.fbsd_unpackc
	        ld      b, 0x08
		.fbsd_bucle
	        call    fbsd_getbit
	        rl      b
	        jr      nc, fbsd_bucle
	        ret
	
		.fbsd_getbit
	        add     a, a
	        ret     nz
	        ld      a, (hl)
	        inc     hl
	        rla
	        ret        
	        
		.fbsd_fin
			ld (de), a	
			;
			;		
			
		#endasm	
		if (is_cutscene == 0) {
			// Show
			exti = textbuff [0] - 64;
			
			// Draw empty frame
			extx = 3 + exti + exti;
			exti = !((VIEWPORT_Y + (p_y >> 9)) < extx);	
			saca_a_todo_el_mundo_de_aqui (exti);
	
			print_str (3, 3, 6, "#$$$$$$$$$$$$$$$$$$$$$$$$%");
			for (exty = 4; exty < extx; exty ++) print_str (3, exty, 6, "&                        '");
			print_str (3, extx, 6, "())))))))))))))))))))))))*");
			
			exty = 4;
		} else {
			saca_a_todo_el_mundo_de_aqui (0);
			exty = 13;
		}
		
		espera_activa (10);
		
		// Draw text
		extx = 4; 
		extaddress = textbuff + 1;
		keyp = 1;
		while (exti = *extaddress ++) {
			if (exti == '%') {
				extx = 4; exty += 2;
			} else {
				sp_PrintAtInv (exty, extx, 71, exti - 32);
				extx ++;
			}
			if (stepbystep) {
#ifdef MODE_128K
	#asm
				halt
	#endasm
				if (exti != 32 && is_cutscene == 0) _AY_PL_SND (10);
	#asm
				halt
				halt
	#endasm
#endif
				peta_el_beeper (6);
				sp_UpdateNow ();
			}
			
			if (button_pressed ()) {
				if (keyp == 0) {
					stepbystep = 0;
				} 
			} else {
				keyp = 0;
			}
		}
		sp_UpdateNow ();
		sp_WaitForNoKey ();
		while (button_pressed ());
		espera_activa (5000);
		
		if (is_cutscene) {
			for (exti = 11; exti < 24; exti ++) {
				print_str (3, exti, 71, "                          ");
				sp_UpdateNow ();
			}
		}
	} else if (n == 251) {
		is_cutscene = 1;
		saca_a_todo_el_mundo_de_aqui (0);
		sp_UpdateNow ();
	} else if (n == 250) {
		is_cutscene = 0;
	} else {
		//cutsc_img (ims [n - 252]);
	}
}

#asm
	._textos_load
		BINARY "texts.bin"
#endasm
