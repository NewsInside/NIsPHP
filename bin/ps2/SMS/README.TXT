    ___  _ _      ___
   |    | | |    |
___|    |   | ___|    PS2DEV Open Source Project.
---------------------------------------------------------
 Copyright 2001-2005, ps2dev - http://www.ps2dev.org
 All rights reserved.
 Created by Eugene Plotnikov <e-plotnikov@operamail.com>
-----------------------------------------------------------------------

Introduction
-----------------------------------------------------------------------
Simple Media System (SMS) is a result of my curiosity about Sony's Playstation2,
MIPS, DivX and MP3. My original goal was to create a simplest DivX player able
to play good resolution movies at good frame rate on the unmodded PS2 without
any extra equipment such as HDD and network adapter. Why "system"? Just because
having only a player program is not enough. Since PS2 is forced to ignore "illegal"
disks, I've took an idea of Drakonite with his UMCDR and developed my own "UMCDR".
(I called it CDDAFS). It just stores data on CD audio disk, which can be read on
(I hope) any PS2. So this is a first component of SMS. Second component is a PC
program that makes cue/bin files in order to burn such a disk. And, finally, comes
a player program itself. This system is not complete yet, but it can play DivX movies
with sound at good frame rate already. Player's base is a famous ffmpeg project.
I took just some parts of it (DivX 5XX and MP3) and made some modifications specific
to PS2 hardware. I've tested it with a couple of DivX/XviD movies with different
screen resolutions and encoding methods and it seems to be working. So, I've decided
to put all this stuff to the CVS at ps2dev in hope that it could be interesting for
PS2 enthusiasts who use it as base for their development. This "document" provides
basic info about SMS.


Keys
-----------------------------------------------------------------------
At Startup:
Select-R1 for NTSC
Select-R2 for PAL
Select-R1-Square for non-interlaced NTSC
Select-R2-Square for non-interlaced PAL

Menu:
Triangle- up one directory level
Left or right directional- switch to device menu
Up or down directional- navigate files
Select+Circle- switch PS2 off
Select-R1- move screen right
Select-L1- move screen left
Select R2- move screen down
Select L2- move screen up
Select-Square- save current configuration to mc0:/SMS
Select-Triangle- exit to PS2 Browser

While playing a film:
Triangle- exit to file menu
Select- Pause (hit select again or hold for 200ms and the "Pause" message will disappear)
Start- Resume


 Thanks (in no particular order)
 ----------------------------------------------------------------------
- Sony for PS2 and Linux for it;
- Marcus R. Brown for discovering an exploit (without it I would never begin);
- Drakonite for UMCDR idea;
- Pixel for making an estimation of the code and for helping me out with CVS;
- J.F. for trying this out (btw. I don't know if you succeeded with it or not);
- PS2Reality team for inspiration and timer code;
- ffmpeg contributors;
- Chris "Neovanglist" Gilbert for GS and DMA code;
- gawd for 'audsrv' (virgin version was enough :));
- all others whose posts in the forums helped me in development;