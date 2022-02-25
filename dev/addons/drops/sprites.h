// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// drops/sprites.h
// Frame 0: falling drop, frames 1-3: exploding drop.

extern unsigned char drop_sprites [0];
#asm
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
._drop_sprites
	BINARY "spdrop.bin"
#endasm
