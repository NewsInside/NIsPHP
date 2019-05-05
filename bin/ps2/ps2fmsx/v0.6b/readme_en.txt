                            PS2fMSX v0.6b (Nov-2009)
                            ------------------------
                            
Introduction
------------
This is the PS2 port of fMSX emulator v3.5. This emulator brings to PS2 those
games that years ago we enjoyed in those 8bits MSX computers.

This is a beta version and as such, some functionalities present in the original
emulator have not been implemented yet. Some of the most relevant are:  

- More emulation parameters (memory, etc...)
- Support for other pad than the one connected to port 0 (the pad must be
connected to port 0)
- Button asignment customization
- NTSC support (currently, PS2fMSX has been adapted only for PAL PS2)

Usage
-----
PS2fMSX includes support for USB devices (all those that are compatibles with
usbd.irx and usbhdfsd.irx) and also support for memory cards.
The emulator should be started as any other homebrew ELF (I personally use
uLauncher) from the folder where the distribution .zip has been uncompressed.

The contents of this folder should be:

ps2fmsx.elf
mainwindow.jpg
fMSX.html
LEEME.TXT
README.TXT
*.ROM (some ROMS from the 8bits systems)
*.FNT (some fonts)
            
Once started, there will be a user interface that allows to navigate to the
folder where the program images (DSK or ROM) are.

Using pad connected to port 0, controls are:                
- D-PAD navigates through menus (UP & DOWN, in the same screen, 
LEFT & RIGHT changes to configuration menu).
- X - Select active option
- START - Start emulation
- SELECT y O - Continue emulation if we are in in-emu menu mode

While emulator running, pad buttons are configured as follows:
- R1 (keep pressed) shows virtual keyboard.
- R2 (keep pressed) allows fast CTRL MSX key press. For some DSK loading
- L1 go back to main user interface menu.
- D-PAD - MSX Joystick
- X - MSX Joystick button 1
- O - MSX Joystick button 2
- ^ - MSX "1" key
- SQR - MSX "Space" key
- START - MSX F1 key
- SELECT - Brings back the emulation menu but without losing emulation state (very
usefull for usign in emulator options like savestates).

Savestates (snapshots)
----------------------
Load and save state of emulation allow that, once in the in-emu menu (SELECT inside
emulation), we can save and load emulator status.
This means that, even if we turn off the emulator, when we run it again, we will
be able to load previous status and continue where we previously saved.
Load and save is in the options menu and you should note that:
- Maximum savestate number is 8
- Savestates can be deleted and overwritten
- Each combination of MSX model and loaded ROMS has its own savestates. This means
that, for loading a savestate, you must first put back the emulator with the emulator
parameters and ROMs/DSK that you saved the savestate with.
This also means that, each .ROM will have its own 8 savestates but all .DSK will share
the same 8 savestate slots.
- Each savestate has an .sta and .png file. The PNG file contains a screenshot from  the
moment the savestate was written.

Credits
-------
PS2fMSX, ported to PS2 by Francisco Mayoral (ps2devel at wisecoding dot es)
from original fMSX code programmed by Marat Fayzulllin (http://fms.komkon.org/)

This port has been completely compiled using PS2SDK and gsKit. Thanx to all 
those hackers and programmers that worked in creating these SDKs 
(http://www.ps2dev.org). 

Special thanks to Ayadsign and El_Patas for all their tests and suggestions.

Official ps2fmsx thread:
http://www.elotrolado.net/hilo_nuevo-port-emulador-msx-para-ps2_1308844

official MSX ROMs and DSKs testing threads:
http://www.elotrolado.net/hilo_lista-de-juegos-msx-comprobados-con-el-emulador-ps2fmsx_1312075

Hope you enjoy as much as I do replaying those 8bits games.
