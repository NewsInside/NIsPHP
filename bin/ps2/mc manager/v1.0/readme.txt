MCManager v.1 by KaylaKaze  Nov-12-2004 (http://www.kaylakaze.com)
------------------------------------------------------------------
This is, as the title says, MCManager. It allows you to copy save games to and from your HD (compatible with the PS2MNU-K database). It also allows you to delete saves off your MC. The benefit of this over the PS2 Browser: MCManager shows how big a saved game on you MC is without you haveing to select it. This makes it easy to figure out which game to take off when you need space.

Why is ths better than PS2MNU-K for save storage?
1) the database is sorted alphabetically
2) you can use te USB keyboard for renaming
3) the onscreen keyboard has more characters to choose
4) when you rename, you can add color tags to the save (explained below)
5) lists the MC by save game, not as a directory tree
6) if you don't have a save partition, you can select size of the partition to create

Installation:
--------------
Same way you install everything else: pt it on the MC an point KeyLoader (or equivalent) to it. To use the USB keyboard, you need the USBD.IRX file from a game that has USB support (I can't provide this file for copyright reasons). Using whatever method you want (ExecFTP, PS2Menu, or PS2Menu-K), put the USBD.IRX file in mc0:/SYS-CONF/ If you don't have this directory, create it somehow. Then you cn use the USB keyboard when renaming DB items (ESC=Cancel, Enter=Done, Backspace=L1, Space=R1)

Usage:
-------
General:
use circle to exit menus or cancel message boxes. X to confirm message box selection

MC Mode:
X=copy save game to database
R2=switch to DB mode
R1=Change memory card
L2=Change destination (doesn't do anything yet in MC mode)
Start=Menu
	Menu Commands: Backup=same as X, Delete=Duh!, Update=nothing yet, Exit=Go to PS2 browser

DB Mode:
X=copy save game from DB to destination MC
R2=switch to MC mode
L2=Change destination
Start=Menu
	Menu Commands: Restore=same as X, Delete=Duh!, Rename=Duh, again, Exit Go to PS2 browser

Color Codes:
-------------
When renaming, use these codes to change the color of text:
`1	Blue		`!	Lt. Cyan	`^5	Magenta BG
`2	Green		`@	Lt. Red		`^6	Brown BG
`3	Cyan		`#	Lt. Magenta	`^7	Lt. Gray BG
`4	Red		`$	Yellow		`^*	Black BG
`5	Magenta		`&	White
`6	Brown		`*	Black
`7	Lt. Gray	`^1	Blue BG*
`8	Dk. Gray	`^2	Green BG
`9	Lt. Blue	`^3	Cyan BG
`0	Lt. Green	`^4	Red BG

*BG=background


Disclaimer:
------------
This thing's been tested and whatnot but it's not perfect. Use at your own risk and all that yada yada.

Games known to not work with:
------------------------------
Wizardry	I don't know why. May have been a temporary problem. I haven't checked in a little while.

To Do:
-------
Copy from one MC to the other
Fix dates
Restore dates on extraction
Check to see if game already exists in DB and ask if you want to update
Color profiles
User controlled screen centering

Problems I know about so don't complain about it:
--------------------------------------------------
The font can be a little hard to read. To make it clearer, I'd have to make it bigger which would give me less screen real estate. When I add the screen centering, I'll also allow the user to change the resolution of the text. Currently it's 75x25, as close as I could get it to traditional the 80x25 of the PC text console without losing letter detail or cutting the edges off on my screen.

Warnings:
----------
When renaming a PS1 game, make sure to put -=- PS1 on the end otherwise the program won't recognize it as a PS1 save and won't restore it properly.

Things NOT to do:
------------------
copying to USB devices
change the font

History:
------------
v.1
Initial release

Thanks:
--------
Thanks to all the people who work on PS2SDK, taking care of the low-level stuff so the rest of us don't have to.