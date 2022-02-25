@echo off
echo BUILDING LEVELS!
echo ================
echo LEVEL 0
..\utils\buildlevel.exe ..\map\map0.map 4 5 99 ..\gfx\font.png ..\gfx\work0.png ..\gfx\sprites0.png ..\enems\enems0.ene 0 9 1 99 1 behs0.txt level0.bin decorations0.spt
..\utils\apack.exe level0.bin ..\bin\level0c.bin
move decorations0.spt ..\script
echo DONE!
