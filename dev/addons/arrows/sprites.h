// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// arros/sprites.h
// Frame 0: arrow left. Frame 1: arrow right

extern unsigned char rat_sprites [0];
#asm
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
._rat_sprites
	BINARY "sprat.bin"
#endasm

extern unsigned char parrot_sprites [0];
#asm
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
._parrot_sprites
	BINARY "spparrot.bin"
#endasm
