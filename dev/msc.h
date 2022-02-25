// msc.h
// Generado por Mojon Script Compiler de la MT Engine MK2
// Copyleft 2014 The Mojon Twins

#ifdef CLEAR_FLAGS
void msc_init_all (void) {
    for (sc_c = 0; sc_c < MAX_FLAGS; sc_c ++)
        flags [sc_c] = 0;
}
#endif

unsigned char read_byte (void) {
    unsigned char sc_b;
#ifdef MODE_128K
    #asm
        di
        ld b, SCRIPT_PAGE
        call SetRAMBank
    #endasm
#endif
    sc_b = *script ++;
#ifdef MODE_128K
    #asm
        ld b, 0
        call SetRAMBank
        ei
    #endasm
#endif
    return sc_b;
}

unsigned char __FASTCALL__ read_vbyte (void) {
    sc_c = read_byte ();
    return (sc_c & 128) ? flags [sc_c & 127] : sc_c;
}

void __FASTCALL__ readxy (void) {
    sc_x = read_vbyte ();
    sc_y = read_vbyte ();
}

#if !(defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE))
void __FASTCALL__ stop_player (void) {
    p_vx = p_vy = 0;
}
#endif

void __FASTCALL__ reloc_player (void) {
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
    p_x = read_vbyte () << 4;
    p_y = read_vbyte () << 4;
#else
    p_x = read_vbyte () << 10;
    p_y = read_vbyte () << 10;
    stop_player ();
#endif
}

void run_script (unsigned char whichs) {
    unsigned char *next_script;

    // main_script_offset contains the address of scripts for current level
    asm_int [0] = main_script_offset + whichs + whichs;

#ifdef MODE_128K
    #asm
        di
        ld b, SCRIPT_PAGE
        call SetRAMBank
    #endasm
#endif
    #asm
        ld hl, (_asm_int)
        ld a, (hl)
        ld (_asm_int_2), a
        inc hl
        ld a, (hl)
        ld (_asm_int_2 + 1), a
    #endasm

    script = (unsigned char *) (asm_int_2 [0]);

#ifdef MODE_128K
    #asm
        ld b, 0
        call SetRAMBank
        ei
    #endasm
#endif

    if (script == 0)
        return;

    script += main_script_offset;


    while ((sc_c = read_byte ()) != 0xFF) {
        next_script = script + sc_c;
        sc_terminado = sc_continuar = 0;
        while (!sc_terminado) {
            switch (read_byte ()) {
                case 0x10:
                    // IF FLAG sc_x = sc_n
                    // Opcode: 10 sc_x sc_n
                    readxy ();
                    sc_terminado = (flags [sc_x] != sc_y);
                    break;
                case 0x20:
                    // IF PLAYER_TOUCHES sc_x, sc_y
                    // Opcode: 20 sc_x sc_y
                    readxy ();
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
                    sc_terminado = (!(p_x >= (sc_x << 4) - 15 && p_x <= (sc_x << 4) + 15 && p_y >= (sc_y << 4) - 15 && p_y <= (sc_y << 4) + 15));
#else
                    sc_terminado = (!((p_x >> 6) >= (sc_x << 4) - 15 && (p_x >> 6) <= (sc_x << 4) + 15 && (p_y >> 6) >= (sc_y << 4) - 15 && (p_y >> 6) <= (sc_y << 4) + 15));
#endif
                    break;
                case 0xF0:
                     // IF TRUE
                     // Opcode: F0
                     break;
                case 0xFF:
                    // THEN
                    // Opcode: FF
                    sc_terminado = 1;
                    sc_continuar = 1;
                    break;
            }
        }
        if (sc_continuar) {
            sc_terminado = 0;
            while (!sc_terminado) {
                switch (read_byte ()) {
                    case 0x01:
                        // SET FLAG sc_x = sc_n
                        // Opcode: 01 sc_x sc_n
                        readxy ();
                        flags [sc_x] = sc_y;
                        break;
                    case 0x6D:
                        // WARP_TO sc_n
                        // Opcode: 6D sc_n
                        n_pant = read_vbyte ();
                        o_pant = 99;
                        reloc_player ();
                        sc_terminado = 1;
                        return;
                    case 0xE0:
                        // SOUND sc_n
                        // Opcode: E0 sc_n
#ifdef MODE_128K
                        wyz_play_sound (read_vbyte ());
#else
                        peta_el_beeper (read_vbyte ());
#endif
                        break;
                    case 0xF4:
                        // DECORATIONS
                        while (0xff != (sc_x = read_byte ())) {
                            sc_n = read_byte ();
                            update_tile (sc_x >> 4, sc_x & 15, behs [sc_n], sc_n);
                        }
                        break;
                    case 0xFF:
                        sc_terminado = 1;
                        break;
                }
            }
        }
        script = next_script;
    }
}
