// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// extrasprites.h
// Extra sprite frames (explosion, fist, shoots...)

//#if defined(PLAYER_CAN_FIRE) || defined(PLAYER_KILLS_ENEMIES) || defined(ENABLE_PURSUERS) || defined(MODE_128K) || defined(PLAYER_CAN_PUNCH) || defined(CARRIABLE_BOXES_THROWABLE) || defined(PLAYER_HAZ_SWORD) || defined(PLAYER_HAZ_WHIP)
extern unsigned char sprite_17_a []; 
//#endif
extern unsigned char sprite_18_a []; 
// sprites para animar la respiración de Jim estando parado. Salva (10/11/12)
extern unsigned char sprite_22_a [];
extern unsigned char sprite_23_a [];
// sprite cayendo
extern unsigned char sprite_24_a [];

#if defined(PLAYER_CAN_FIRE) || defined (MODE_128K) || defined (ENABLE_SHOOTERS)
extern unsigned char sprite_19_a [];
extern unsigned char sprite_19_b [];
#endif
#if defined(PLAYER_CAN_PUNCH)
extern unsigned char sprite_20_a [];
extern unsigned char sprite_21_a [];
#elif defined(PLAYER_HAZ_SWORD)
extern unsigned char sprite_sword_l [];
extern unsigned char sprite_sword_r [];
extern unsigned char sprite_sword_u [];
#elif defined(PLAYER_HAZ_WHIP)
extern unsigned char sprite_whip [];
#endif 

// Extra sprites (probably needed) for the floating objects
#ifdef ENABLE_FLOATING_OBJECTS
#ifdef ENABLE_FO_CARRIABLE_BOXES
extern unsigned char carriable_a [];
extern unsigned char carriable_b [];
extern unsigned char carriable_c [];
#endif
#endif

// Habilita el sprite de golpe tipo comic. Salva (14/10/18)
//#if defined(PLAYER_CAN_FIRE) || defined(PLAYER_KILLS_ENEMIES) || defined(ENABLE_PURSUERS) || defined(MODE_128K) || defined(PLAYER_CAN_PUNCH) || defined(CARRIABLE_BOXES_THROWABLE) || defined(PLAYER_HAZ_SWORD) || defined(PLAYER_HAZ_WHIP)
#asm
/*
    ._sprite_17_a
        defb 0, 128, 56, 0, 117, 0, 123, 0, 127, 0, 57, 0, 0, 0, 96, 0, 238, 0, 95, 0, 31, 0, 62, 0, 53, 128, 42, 128, 20, 128, 0, 192, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255 
    ._sprite_17_b
        defb 0, 3, 240, 1, 248, 0, 236, 0, 212, 0, 248, 0, 224, 1, 24, 0, 124, 0, 120, 0, 244, 0, 168, 0, 0, 1, 0, 3, 0, 63, 0, 127, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255 
    ._sprite_17_c
        defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
*/		
    ._sprite_17_a
        defb 0, 254
        defb 0, 12
        defb 225, 0
        defb 127, 0
        defb 63, 0
        defb 31, 128
        defb 15, 192
        defb 15, 192
        defb 31, 0
        defb 127, 0
        defb 255, 0
        defb 31, 0
        defb 15, 192
        defb 14, 224
        defb 12, 192
        defb 24, 193
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 
    ._sprite_17_b
        defb 129, 24
        defb 195, 0
        defb 206, 0
        defb 252, 0
        defb 248, 1
        defb 248, 1
        defb 252, 0
        defb 255, 0
        defb 252, 0
        defb 248, 1
        defb 240, 3
        defb 248, 1
        defb 60, 1
        defb 12, 0
        defb 6, 224
        defb 1, 240
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 
    ._sprite_17_c
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255

    ._sprite_22_a
        defb 0, 240
        defb 7, 224
        defb 9, 224
        defb 14, 224
        defb 10, 192
        defb 27, 192
        defb 31, 192
        defb 13, 192
        defb 3, 224
        defb 1, 248
        defb 3, 240
        defb 6, 240
        defb 6, 240
        defb 3, 240
        defb 1, 240
        defb 7, 240
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 
    ._sprite_22_b
        defb 0, 31
        defb 192, 15
        defb 96, 7
        defb 240, 7
        defb 176, 7
        defb 80, 7
        defb 48, 7
        defb 208, 1
        defb 156, 1
        defb 200, 1
        defb 32, 3
        defb 224, 15
        defb 192, 15
        defb 0, 31
        defb 192, 31
        defb 64, 31
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 
    ._sprite_22_c
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255

    ._sprite_23_a
        defb 0, 248
        defb 3, 240
        defb 6, 224
        defb 15, 224
        defb 13, 224
        defb 10, 224
        defb 12, 224
        defb 11, 128
        defb 57, 128
        defb 19, 128
        defb 4, 192
        defb 7, 240
        defb 3, 240
        defb 0, 248
        defb 3, 248
        defb 2, 248
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 
    ._sprite_23_b
        defb 0, 15
        defb 224, 7
        defb 144, 7
        defb 112, 7
        defb 80, 3
        defb 216, 3
        defb 248, 3
        defb 176, 3
        defb 192, 7
        defb 128, 31
        defb 192, 15
        defb 96, 15
        defb 96, 15
        defb 192, 15
        defb 128, 15
        defb 224, 15
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 
    ._sprite_23_c
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255

._sprite_24_a
        defb 7, 224
        defb 13, 224
        defb 15, 0
        defb 111, 0
        defb 110, 0
        defb 7, 0
        defb 50, 128
        defb 27, 128
        defb 13, 192
        defb 5, 224
        defb 8, 224
        defb 13, 224
        defb 7, 224
        defb 4, 240
        defb 6, 192
        defb 26, 192
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 
    ._sprite_24_b
        defb 224, 7
        defb 80, 7
        defb 176, 0
        defb 86, 0
        defb 182, 0
        defb 96, 0
        defb 204, 1
        defb 88, 1
        defb 112, 3
        defb 160, 7
        defb 16, 7
        defb 176, 7
        defb 224, 7
        defb 32, 15
        defb 96, 3
        defb 88, 3
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 
    ._sprite_24_c
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255 
#endasm
//#endif

#asm
	._sprite_18_a
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	._sprite_18_b
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	._sprite_18_c
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
#endasm

#if defined(PLAYER_CAN_FIRE) || defined (MODE_128K) || defined (ENABLE_SHOOTERS)
#asm	              	
	._sprite_19_a
		defb 0, 255
		defb 0, 195
		defb 24, 129
		defb 60, 0
		defb 60, 0
		defb 24, 129
		defb 0, 195
		defb 0, 255
		
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	
	._sprite_19_b
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
#endasm
#endif

#ifdef PLAYER_CAN_PUNCH
#asm
	._sprite_20_a
		defb 0, 255
		defb 0, 0
		defb @10111110, 0
		defb @10110111, 0
		defb @10101011, 0
		defb @10101111, 0
		defb @00001110, 0
		defb 0, @11100000
		
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
				
	._sprite_21_a
		defb 0, 255
		defb 0, 0
		defb @01111101, 0
		defb @11101101, 0
		defb @11010101, 0
		defb @11110101, 0
		defb @01110000, 0
		defb 0, @00000111
		
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
#endasm		
#endif

#ifdef PLAYER_HAZ_SWORD
#asm
	._sprite_sword_l
		defb @00000000, @11111111
		defb @00000000, @11110001
		defb @00000100, @10000000
		defb @01111101, @00000000
		defb @10000101, @00000000
		defb @01111101, @00000000
		defb @00000100, @10000000
		defb @00000000, @11110001
		
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	
	._sprite_sword_r
		defb @00000000, @11111111
		defb @00000000, @10001111
		defb @00100000, @00000001
		defb @10111110, @00000000
		defb @10100001, @00000000
		defb @10111110, @00000000
		defb @00100000, @00000001
		defb @00000000, @10001111
		
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	
	._sprite_sword_u
		defb @00001000, @11100011
		defb @00011100, @11000001
		defb @00011100, @11000001
		defb @00010100, @11000001
		defb @00010100, @10000000
		defb @00111110, @10000000
		defb @00000000, @10000000
		defb @00011100, @11000001

		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	
#endasm
#endif

#ifdef PLAYER_HAZ_WHIP
#asm
	._sprite_whip
		defb @00000000, @10000011
		defb @01111100, @00000000
		defb @10000011, @00000000
		defb @10000000, @00111100
		defb @01000000, @00011111
		defb @00000000, @10111111
		defb @00000000, @11111111
		defb @00000000, @11111111
		
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
		
		defb @00000000, @11111101
		defb @00000010, @11111000
		defb @00000001, @00111100
		defb @11000001, @00000000
		defb @00111110, @00000000
		defb @00000000, @11000001
		defb @00000000, @11111111
		defb @00000000, @11111111
		
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
		
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
#endasm		
#endif

#ifdef ENABLE_FLOATING_OBJECTS
#ifdef ENABLE_FO_CARRIABLE_BOXES
#asm
	._carriable_a
		defb @00001111, 0
		defb @01110000, 0
		defb @10000000, 0
		defb @10000000, 0
		defb @10000000, 0
		defb 255, 0
		defb 0, 0
		defb 255, 0
		
		defb @01101101, 0
		defb @01101001, 0
		defb @01101101, 0
		defb 0, 0
		defb @01111111, 0
		defb @01111111, 0
		defb 0, 0
		defb @01101101, 0
        
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
        
	._carriable_b
		defb @11110000, 0
		defb @00001110, 0
		defb @00000001, 0
		defb @00000001, 0
		defb @00000001, 0
		defb 255, 0
		defb 0, 0
		defb 255, 0
		
		defb @10010010, 0
		defb @00100100, 0
		defb @10110010, 0
		defb 0, 0
		defb @11101010, 0
		defb @11111100, 0
		defb 0, 0
		defb @10110110, 0
        
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
        
	._carriable_c
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
#endasm
#endif
#endif
