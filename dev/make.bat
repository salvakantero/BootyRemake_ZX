@echo off
rem set here the game name (used in filenames)
SET game=booty

echo ------------------------------------------------------------------------------
echo    BUILDING %game%
echo ------------------------------------------------------------------------------

rem ###########################################################################
rem ## LEVELS
rem ###########################################################################

echo .
echo .
echo .
rem for 48K/single level games... 
echo ### MAKING MAPS ###
rem the "Force" parameter is to force 16 tiles maps even if the actual map data
rem has more tan 16 tiles. Extra tiles are written to extra.spt. Me have to move
rem that file to the script folder.
..\utils\map2bin.exe ..\map\map0.map 4 5 99 map.bin bolts.bin force
move map.bin.spt ..\script
echo .
echo .
echo .
echo ### MAKING ENEMS ###
rem ..\utils\ene2bin.exe 4 5 1 ..\enems\enems0.ene enems.bin hotspots.bin
..\utils\xene2bin.exe 4 5 1 ..\enems\enems0.ene enems.bin hotspots.bin 4
echo .
echo .
echo .
echo ### MAKING TILESET ###
..\utils\ts2bin.exe ..\gfx\font.png ..\gfx\work0.png ts.bin
echo .
echo .
echo .
echo ### MAKING SPRITESET ###
..\utils\sprcnv.exe ..\gfx\sprites0.png sprites.h
rem If you use arrows and/or drops this will make the sprites binary:
rem ..\utils\spg2bin.exe ..\gfx\drop.png spdrop.bin
rem ..\utils\spg2bin.exe ..\gfx\arrow.png sparrow.bin
..\utils\spg2bin.exe ..\gfx\rat.png sprat.bin
..\utils\spg2bin.exe ..\gfx\parrot.png spparrot.bin

rem ###########################################################################
rem ## GAME TEXT
rem ###########################################################################

rem Each line in text.txt contains a text string for the game.
rem textstuffer.exe will compress and pack all text strings in
rem a binary file called texts.bin. The parameter "24" define how
rem many chars per line. Word wrapping is automatic.
echo .
echo .
echo .
echo ### MAKING TEXTS ###
cd ..\texts
..\utils\textstuffer.exe texts.txt texts.bin 12
copy texts.bin ..\bin

rem ###########################################################################
rem ## GAME SCRIPT
rem ###########################################################################

rem The game script is compiled by msc3.exe. For 128K games use "rampage" at
rem the end so the script compiler generates code to stuff everything in
rem extra pages; the second parameter is the # of screens in your game.
rem i.e. "msc3.exe ninjajar.spt 21 rampage
echo .
echo .
echo .
echo ### MAKING SCRIPT ###
cd ..\script
..\utils\msc3.exe %game%.spt 20 rampage
rem If scripts and texts are going to share the same RAM page, use this line
rem (for 128K games)
rem This calculates an offset for the scripts binary automaticly.
rem ..\utils\sizeof.exe ..\bin\texts.bin 49152 "#define SCRIPT_INIT" >> msc-config.h
echo #define SCRIPT_INIT 49152 >> msc-config.h
copy msc.h ..\dev
copy msc-config.h ..\dev
copy scripts.bin ..\bin\preload7.bin
cd ..\dev

rem For 128K games with text + script sharing the same page, use this to
rem bundle both binaries...
rem echo ### BUNDLING TEXT + SCRIPT ###
rem copy /b ..\texts\texts.bin + ..\script\scripts.bin ..\bin\preload3.bin

rem ###########################################################################
rem ## FIXED SCREENS
rem ###########################################################################
echo .
echo .
echo .
echo ### MAKING FIXED SCREENS ###
..\utils\png2scr.exe ..\gfx\title.png ..\gfx\title.scr
..\utils\apack.exe ..\gfx\title.scr ..\dev\title.bin
copy ..\dev\title.bin ..\bin\title.bin

..\utils\png2scr.exe ..\gfx\title2.png ..\gfx\title2.scr
..\utils\apack.exe ..\gfx\title2.scr ..\dev\title2.bin
copy ..\dev\title2.bin ..\bin\title2.bin

..\utils\png2scr.exe ..\gfx\title3.png ..\gfx\title3.scr
..\utils\apack.exe ..\gfx\title3.scr ..\dev\title3.bin
copy ..\dev\title3.bin ..\bin\title3.bin

..\utils\png2scr.exe ..\gfx\title4.png ..\gfx\title4.scr
..\utils\apack.exe ..\gfx\title4.scr ..\dev\title4.bin
copy ..\dev\title4.bin ..\bin\title4.bin

..\utils\png2scr.exe ..\gfx\ending.png ..\gfx\ending.scr
..\utils\apack.exe ..\gfx\ending.scr ..\dev\ending.bin
copy ..\dev\ending.bin ..\bin\ending.bin

del ..\gfx\*.scr
echo .
echo .
echo .
echo ### MAKING LOADING SCREEN ###
..\utils\png2scr.exe ..\gfx\loading.png loading.bin

rem ###########################################################################
rem ## LEVELS
rem ###########################################################################

rem we will delegate on makelevels.bat - if your game supports several levels,etc
echo .
echo .
echo .
rem echo ### BUILDING LEVELS ###
rem cd ..\levels
rem call buildlevels.bat
rem cd ..\dev

rem ###########################################################################
rem ## LIBRARIAN
rem ###########################################################################
echo .
echo .
echo .
echo ### BUILDING REUBICA ###
..\utils\pasmo reubica.asm reubica.bin
echo .
echo .
echo .
echo ### BUILDING RAMS ###
cd ..\bin
..\utils\librarian.exe
copy RAM3.bin ..\dev\ram3.bin
rem copy RAM4.bin ..\dev\ram4.bin
rem copy RAM6.bin ..\dev\ram6.bin
copy RAM7.bin ..\dev\ram7.bin
copy librarian.h ..\dev
cd ..\dev

rem ###########################################################################
rem ## MUSIC
rem ###########################################################################
echo .
echo .
echo .
echo ### BUILDING WYZ PLAYER ###
cd ..\mus
..\utils\pasmo WYZproPlay47aZXc.ASM RAM1.bin
copy RAM1.bin ..\dev
cd ..\dev

rem echo ### BUILDING ARKOS ###
rem cd ..\mus
rem if [%1]==[nomus] goto :nomus
rem ..\utils\build_mus_bin.exe ram1.bin
rem :nomus
rem copy ram1.bin ..\dev
rem copy arkos-addresses.h ..\dev\sound
rem cd ..\dev

rem ###########################################################################
rem ## COMPILATION AND TAPE BUILDING
rem ###########################################################################
echo .
echo .
echo .
echo ### COMPILING ###
zcc +zx -vn %game%.c -o %game%.bin -lsplib2 -zorg=24200
echo .
echo .
echo .
echo ### MAKING TAPS ###
..\utils\bas2tap -a10 -sBOOTY loader\loader.bas loader.tap
..\utils\bin2tap -o reubica.tap -a 25000 reubica.bin
..\utils\bin2tap -o ram1.tap -a 32768 ram1.bin
..\utils\bin2tap -o ram3.tap -a 32768 ram3.bin
rem ..\utils\bin2tap -o ram4.tap -a 32768 ram4.bin
rem ..\utils\bin2tap -o ram6.tap -a 32768 ram6.bin
..\utils\bin2tap -o ram7.tap -a 32768 ram7.bin
..\utils\bin2tap -o screen.tap -a 16384 loading.bin
..\utils\bin2tap -o main.tap -a 24200 %game%.bin
copy /b loader.tap + screen.tap + reubica.tap + ram1.tap + ram3.tap + ram7.tap + main.tap %game%.tap
echo .
echo .
echo .
echo ### MAKING TZXS ###
buildtzx -l 1 -i tzx.txt -o booty.tzx -n Booty
buildtzx -l 3 -i tzx.txt -o booty_turbo.tzx -n Booty
echo .
echo .
echo .
echo ### CLEANING ###
del loader.tap
del screen.tap
del main.tap
del reubica.tap
rem del ram1.bin
rem del ram3.bin
rem del ram4.bin
rem del ram6.bin
rem del ram7.bin
del ram1.tap
del ram3.tap
rem del ram4.tap
rem del ram6.tap
del ram7.tap
rem del %game%.bin
del zcc_opt.def

echo .
echo ### DONE ###
