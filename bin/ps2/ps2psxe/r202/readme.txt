============================================================================
=               PS2PSXe GUI by ffgriever (gfx by berion)                   =
============================================================================

1. Foreword
Well, it's not a real readme. There is really no need to waste time
writing readme for a temporary launcher (which is the subject in this
case, as the PS2PSXe itself can be used in an exact same way that the
previous version.

So, first of all... Did I mention it's just a temporary solution? I did,
didn't I? But there is more, this temporary solution is an unfinished, not
tested application. I'm not sure if I'm going to finish it at all. Wasting
too much time on something that will be scrapped out anyway is illogical
;). But please, do report any bugs related to the GUI itself, I *am* going
to fix them.

Let's get to the point.
The GUI supports only cd/dvd, mass (multiple, of course) and internal hdd.
The host/smb support was planned, but I didn't have time to add it. If you
want these, you'll have to use ps2client.

!NOTICE!
You can get back from emulated game to the GUI by using a combo
L1+L2+R1+R2+UP.


2. ONE BIG, FAT ISSUE
There is a huge bug in initialisation code. If the GUI is launched through
uLE (maybe some other apps), the pad behaves a little bit weird. The mode
button doesn't work at all, which leads to a problem if a PSX game won't
turn the analog mode on by itself (and supports analog pads). The same for
digitize pad option (if it is used, the analog mode is turned off by
default, but can - and should - be enabled by the user). There is a
simple, temporary solution for this issue. While in main menu, just press
select and navigate to the GUI directory, then launch it again. Not the
pad will be fully functional. I'm not sure what causes this problems. It
doesn't happen when launching directly from FMCB or through ps2link.


3. MAIN MENU

a) Start EMulation

It does exactly what it says. If no CD image nor PSX Executable was
selected, the PSX internal card manager/cd player will be launched. If
both CD image and PSX Executable are selected, CD image takes priority. If
bios, CD image or executable cannot be opened, apropriate warrning will be
displayed and emulation won't start.

b) Open cdrom image

A simple explorer window will be displayed. Navigate it and select the cd
image you want to emulate. Only full 2352 bytes per sector images are
supported. By default only ccd, cue and bin files are displayed (case
sensitive!), but pressing R2 will remove the extension mask and display
all files.

c) Open PSX executable

Just as with the above option, an explorer will be launched. By default
only files with PSX and psx extensions are being shown. Pressing R2 will
let you see all the files.

d) Configuration

Opens configuration screen.


4. CONFIGURATION MENU

a) System

Configures system options.

b) Video

Configures display and gfx options.

c) Audio

Configures sound options.

d) Input

Configures controller options.

e) Save default config.

Saves current configuration in "default.cfg" file. If this file is present
in the directory the GUI is launched form, it will load it automatically
at start. It quite helpful if you're launching from hdd. After IOP reset,
the pfs mountpoints are not available anymore and since we have no
information on the real path (partition part is missing), you have to
specify the real path in the system menu. Once saved, the GUI will load
default config at start and will not bug you for the real path anymore ;).

f) Load default config

Loads a configuration file of your choice. The name may be a little bit
misleading, as it can be any configuration you want, not just the default
config.

g) Save game config

If per game config is enabled, this option will save a configuration file
for a currently selected CD image/executable. It will be stored in the
same directory that the image/exe and will have the same name (extension
changed to cfg).

h) Delete game config

Deletes the per game config file, so that the selected game will use
current config instead if the saved one.

5. SYSTEM CONFIGURATION

a) PS2PSXe path

Lets you choose emulator path. Necessary if you're launching from hdd and
the path is obfuscated either by fakehost or pfs mountpoint. Can be left
blank if launching from mass - the path of the GUI will be used by default.

b) Select BIOS

By default the PS2PSXe is using bios/scph7502.bin. If you want to use a
different bios file, this is the option you need to use.

c) Per game config

This option will let you use separate config for every game. If a file
"image_name.cfg" exists in the same directory as the image, it will be
loaded at launch and replace the current config.

The emulator will also use the "image_name_0.mcr" amd "image_name_1.mcr"
for memory cards (in the same directory that the image file itself).

This option is not implemented yet.

d) Stack pointer fix

Fixes some stuff related to stack pointer optimisations (disables some
stuff). Should not be needed anymore, but try it if a game crashes.

e) Alt. exception handling

Uses alternative exception handling method. Should not be needed anymore,
but you might get it a chance if a game crashes.

f) Loop check

Disables most of the automatic libcrypt patching stuff. There is no real
need for this until you want to test subchannel support (it's not really
needed, the auto patcher does a great job, there is a chance that it
handles pretty much every libcrypt implementation). //yup, it an auto
crack, more or less

g) Show FPS

FPS, resolution and mode will be displayed at the top of the screen. Might
ocassionally lead to some additional texture corruption (I was going to
fix that, but I forgot about it ;) )

h) Interpreter mode

Enables interpreter CPU emulation instead of the recompiler. Terribly
slow, but fixes some games. Currently disabled, as some changes in recet
versions prevent it from working (should be quite easy to fix).

6. VIDEO CONFIGURATION

a) Signal type

Let's you choose the video signal type. The options are:
- PAL - obvious, default
- NTSC - obvious
- Auto PS2 - uses the region of your PS2 to choose between PAL and NTSC
- Auto PSX - uses the region of the game to choose between PAL and NTSC.
This setting is not implemented yet.

The recommended settings are NTSC for NTSC games and PAL for PAL games.

b) Fram limiter

Uses frame limiter if turned on. There are games that work at twice the
nominal speed, etc. Might by quite helpful.

c) Depth

Lets you choose the video buffer depth. The default setting is 32bit. Use
it only if you're experiencing a lot of texture corruption or great
slowdown at heavy vram usage.

d) Dithering

Enables dithering in 16 bit mode. Has no effect in 32bit mode.

e) Polygon filter

The filtering of the polygon textures (usually ingame "3D"). Can be set to
bilinear for most games. Should be set to nearest for games that tend to
use polygons as sprites (valkyrie profile, star ocean second story and
similar)

f) Sprite filter

The filtering of the sprite textures (usually ingame "2D"). Many games
look much better if it is set to nearest. IMO a must for final fantasy and
similar games (though nearest filtering works fine only when using PAL
mode for PAL games, NTSC mode for NTSC games and the game's horizontal
resolution is either 320 or 640... If it's 256, 512 and 368, black bars
might be displayed).

g) Screen X offset
h) Screen Y offset

Moves the display on the screen. It's not interactive, so you'll have to
set it and launch the game to test whether the result is pleasing or not.
Use it if your tv is miscalibrated or some menus at edges are being cut
due to too big overscan.

7. AUDIO CONFIGURATION

a) Emulate sound

Enables sound emulation (launches ps2psxe.elf if enabled and ps2psxen.elf
if disabled).

b) Disable threads

Will use psx's hsyncs to transfer the execution to the audio plugin
instead of letting spu be executed constantly in another thread. Threaded
mode is a little bit faster in some games, but usually (not always though)
produces additional cracks in the sound playback. It's really very game
dependant. You'll have to check it for yourself.

Right now threaded mode is a must if you're launching from host/smb
(otherwise the game lags terribly if sound is being played and cdrom image
is being accessed at the same time - IOP thread priority problem ;) )

I personally keep this setting on (threads disabled) for most of the games.

c) Wait for SPU IRQ

You most likely know this option from many other emulators and spu
plugins. Fixes some games like valkyrie profile. It's worth a try if the
game freezes during sound playback, the sounds are played only partially,
the sounds sound weird, etc, etc. There will be some additional slowdown
if this option is enabled (not that big, though).

8. INPUT CONFIGURATION

a) Digitize pad

When enabled, the emulator will always return to the game, that digital
only pad have been connected. But, if you switch the mode button on (the
little on between start and select), it will use left analog stick as if
it was d-pad and right analog stick as if it was R1/L1. Quite useful for
games like FF7 that do not support analog sticks at all. This option might
not worked if GUI have been launched from uLE (see paragraph 2 for a
solution).


And that's pretty much all. Have a nice time testing some games.


ffgriever 2011