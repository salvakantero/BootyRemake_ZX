// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// pantallas.h
// Fixed, compressed screens

#ifndef MODE_128K
extern unsigned char s_title [];
extern unsigned char s_marco [];
extern unsigned char s_ending [];

#asm
	._s_title
		BINARY "title.bin"
	._s_marco
#endasm
#ifndef DIRECT_TO_PLAY
#asm
		BINARY "marco.bin"
#endasm
#endif
#asm
	._s_ending
		BINARY "ending.bin"
#endasm
#endif
