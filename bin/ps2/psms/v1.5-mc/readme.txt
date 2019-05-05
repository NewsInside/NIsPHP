PSMS v1.5 - SMS Emulator for the PS2
------------------------------------

PS2 specific code By Nick Van Veen (aka Sjeep)
More PS2 specifc code by Jeffrey Soldan (aka Drakonite)
SMS emulation core coded by Charles Mac Donald

History:
--------
1.5 - Numerous misc changes, created release build for
      booting from exploit.  Might be using new sjpcm
      might not be yet, I can't remember ;)

1.3 - Updated to actually build with a modern/standard
      ps2dev environment.

1.2 - Fixed bug in sound driver that prevented PSMS
      from booting with AR/GS swap. Improved FILES.TXT
      parsing code, changed key mapping.

1.1 - Fixed bug in rapid fire code.

1.0 - First release (preview).


Introduction:
-------------

PSMS is a Sega Mastersystem emulator that run's on the
Sony Playstation 2. It is a port of SMSPlus, the excellent
SMS emulator by Charles Mac Donald. Since the emulation
core was taken from an already very complete emulator, PSMS
inherits all the great features of SMSPlus, such as:

- Accurate emulation. Compatability rate is around 95%.
- Game Gear support.
- Accurate rendering - all graphics features of the SMS
  and GG are emulated and rendered properly.

PSMS is freeware. You may copy and distribute it as much
as you like. Please do not contact me regarding where to
find ROM's - I can not give out that kind of information.

Current Features:
-----------------

- Full frame rate (easily!!)
- Audio output
- PAL/NTSC auto-detection
- Loads games from the cdrom
- GUI for selecting roms and changing emulation options
- Game Gear Support
- Ability to save/load game states (not to memory card)
- Easy to create your own game compilation cd's
- Analog stick support

If you would like a feature implimented that is not listed above,
please contact me with your idea. See the contact section below.

MC Usage:
---------
(NOTE: v1.5 release only contains MC version.)
I hacked this into the README pretty quickly so I appoligize if it
isn't the best instructions.

MC version of PSMS is designed to boot from PS2-Indpendence exploit.
For information about the exploit visit www.0xd6.org

Most of the normal psms rules apply.  Create a FILES.TXT listing roms
and filenames as normal. Roms cannot be zipped.  Put all ROMS, 
FILES.TXT, and the psms.elf file (rename to BOOT.ELF for use with the
standard exploit) in the Your System Configuration save (Your System 
Configuration is BADATA-SYSTEM for US, and BEDATA-SYSTEM for EU).

(SJPCM.IRX is not needed for this release)

Usage:
------

First you need to create a cd that includes the emulator, your
SMS/GG roms and a rom database file. See cdinfo.txt for details on
how to get this all set up. Once you've created the cd, boot it
with your favourite method (for most people this will involve a
swap with an Action Replay/Gameshark disk). If your cd has been
created properly, you should see the rom selection screen with a
scroll-box listing all your games. From here you can choose the
game you want to play. Once you've started playing a game, you can
press SELECT to enter the in-game menu where you can save/load the
game state or return to the rom selection screen to choose another
game.


Rom selection screen controls:

Up/Down    - Hold to scroll up/down.
Left/Right - Hold to scroll up/down a page at a time.
X          - Press to start emulation of selected game.

You may also use the left analog stick to scroll.

In-game controls:

PS2         -         SMS
-------------------------
Arrows      =       D-Pad
Left stick  =       D-Pad
Square      =    Button 1
Circle      =    Button 2
Start       =    PAUSE (START for GameGear)
L1          =    Button 1 Rapid fire
R1          =    Button 2 Rapid fire

Pressing select will bring up the ingame menu.

NOTE: Input is taken from both controller ports, so 2 player gaming
is supported. The in-game controls are the same for both controllers.
Only the 1st controller can be used in the rom selection screen.


Ingame menu:

From the ingame menu you can...

- Load/Save game state
- Change SMS region
- Toggle sound output on/off
- Reposition the display
- Return to the main menu

To reposition the display, hold down SELECT and use the arrow
buttons to move the display to the correct position on the screen.

State saving:

At any time during gameplay the state of the game may be
saved, and restored when desired (ie, if you loose a life).
Currently the state is stored in PS2 memory, you cannot store it on
a memory card. The state is valid until you leave the current game.
Once you return to the rom selection screen the state is destroyed.
This is to prevent loading an invalid state (ie, loading a state
saved in a different game to the one currently been emulated).

Contact:
--------

PSMS Homepage: http://psms.gamebase.ca


Jeffrey Soldan (aka Drakonite)
 - e-mail: drakonite@123mail.org

Nick Van Veen (aka Sjeep)
 - e-mail: sjeep@gamebase.ca
 - IRC: Sjeep, on EFNet

Charles Mac Donald
 - e-mail: cgfm2@hooked.net
 - WWW: http://cgfm2.emuviews.com

Thanks go to:
-------------

Sjeep     - for the original PSMS releases.

Vzzrzzn   - for releasing src to his demo's, which I learnt
            a lot from, and for writing the origional sound
			driver (which is no longer used).

Pukko     - for releasing padlib and for the many fixes to
            the sif code in psx2lib he has released.

Gustavo   - for the origional psx2lib.

Oobles    - for his IOP tutorial and example code.

Justice7  - for writing the FILES.TXT util.

Naplink Team - for Naplink. All development has been done
               using naplink.

Charles Mac Donald - for writing SMSPlus, the excellent
                   SMS emulator on which PSMS is based.

				   Contact him: cgfm2@hooked.net
                   SMSPlus website: http://cgfm2.emuviews.com.


Thanks also to the beta testers: Phex_X, Sykopieces, struct2,
                                 justice7 and Sparcky.


Sjeep sends Greets to:
----------------------
           Nagra, Stryder Hiryu, Now3d, Dreamtime, Vzzrzzn, Oobles,
           Gustavo, Pukko, Justice7, Jules, Karmix, Phed_X, Duke,
		   Adk, struct2, Sparcky, dayta, Sykopieces, adresd and
		   anybody that I've missed out.

Drakonite sends Greets to:
--------------------------
           Hmm.. I'll think of someone ;) There are lots of ppl who
           deserve it!


LEGAL:
------

The emulator source code (including origional SMSPlus code and PSMS
code) is distributed under the terms of the GNU General Public License.
A copy of the GNU General Public License can be found in the "license"
file included in the PSMS archive.

Some PS2 specific src code such as pukko's padlib and vzzrzzn's gfxpipe is
NOT distributed under the terms of the GNU General Public License. Details
are included in the src archive.

The Z80 CPU emulator, SN76489 and YM3812 sound chip emulation are taken from
the MAME project, and terms of their use are covered under the MAME license.
(http://www.mame.net)

The YM2413 instrument parameter table is also taken from MAME.

SMSPlus is (c) Charles Mac Donald.
