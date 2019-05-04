                         PVCS version 1.3

                   Atari 2600 emu for the ps2


Thanks to Dan Boris and Alex Hornby for the original emu code.
I added Ron Fries sound code and Star Path (AR banking).
Major change to TIA code. The stella TIA code was pilfered (after converting 
it from c++ to C).  Now games like Centipede and Defender 2 work.
The most Star Path games are now playable.

FILES.TXT lists the available ROMS.
Format is:
Game Name,ROM.BIN

If you are making a cdrom make a subdir "ROMS", so this can be selected.

Keys
=======================
R1        Reset (Start game)
R2        Exit game emulation
L1        P0 Difficulty Toggle
L2        P1 Difficulty Toggle
Select    Select game mode
X or O    Fire

Scene comments
==========================================================================
Long live 7not6! Thanks for the Christmas pack. :)


Changes v1.3
===========================================================================
Added 3F banking (River Patrol, Miner 2049er)
Bug fixes to Starpath code load (Party Mix)
Bug fixes to TIA to do DataBusState.
Uses Stella color palette. (better colors)
Compiled with ps2sdk 1.2, now uses padlib.
Now scans ROMS from mc or cdrom (Thanks 7not6).
Smaller font used to display ROMS (helps when you have MANY ROMS).
Added Difficulty Toggle. Hit L1 and L2 during game.
Fixed paddle control bugs.
Tested from cdrom.

Changes v1.2
===========================================================================
New TIA code from stella version 1.4.1. (This fixes many games)
Better RIOT timer code (might still need some tweeks).
Bug fixes for AR banking (fixes problems with Starpath games).
Added CDVD.irx init (To fix limitations when burned to a cd - UNTESTED)


Changes v1.1
===========================================================================
Added F8SC (Denfender II) and FASC (Tunnel Runner) bankswitching.
Added better error message display.
Fixed problems whem launched from keylauncher.
Added untested CD rom support. (put ROMS in the main dir (cdrom:) with the prg)

Notes
===========================================================================
Source code available at http://pvcs.ps2-scene.org

BUGS/TODO:
- Add hdd support.
- Add buttons color/bw
- Fix sound bugs in certain games. (Pitfall)
- Fix clk count increment for certain cmds? (Bowling)
- Pause needs to be added.
- Option to center the screen
- Will not play Burgertime.  (This uses a strange banking scheme (E7))
- Game save state
- Zip file support
