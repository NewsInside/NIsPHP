ESR beta r9b coded by ffgriever.

Changes:

ESR public beta, revision 9b
* halved memory usage on IOP side (some new games should work, like Melty Blood: Act Cadenza)
* changed once again EE streams (Ape Escape 2, Gitaroo Man, maybe more)
* it doesn't matter anymore if ESR is launched directly from FMCB or through uLE (KYA: Dark Lineage, V-Rally 3, maybe some more games)
* corrected some stack pointer problems on EE side
* added synchronous mode and media type spoofing for EE (accessible only by GUI version)
* some minor changes to make future compiling and management easier (also necessary to simplify GUI version a lot)

ESR public beta, revision 9a
* changed stream handling to make some old games working (Onimusha: Warlords) - but for some games it will need additional IOP memory
* fixed a bug that caused read callbacks to be called more times that they should (thus making the game think, some data is ready, while the read operation wasn't even issued - GT3 PAL)
* rewrote IOP code to use a little bit less memory
* now it should work with any other valid media than PS2DVD and DVDV - though, I can't find use for that
* replaced some temporary solutions by real ones, thus increasing stability, I guess ;)
* some small changes to get the games that lost compatibility in r9 working again (ie. KYA: Dark Lineage, V-Rally 3/PAL)

ESR public beta, revision 9
* lower memory usage on EE side and (what's more important) on IOP side (~6.5kB less right now) - might make some incompatible or freezing games working
* yet again new method of handling streams - sound and FMVs should work fine in another few games (well, "Chulip" being one of them ;) )
* automatic sceCdMmode patching... so for some CD->DVD converted games there will be no need to use DVDScan to do the patching (mediachecks still have to be patched... see release post for details)
* fixed a problem that made some absolutely properly converted/patched CD->DVD games not working with ESR, now they should work just fine
* many small fixes on IOP side, everything should be much more realiable (there is at least one game that benefits of it)
* fixed timing issues and error passing for "CD style" DVD reads - N06, mostly used in older games
* small fix to the "off" version of ESR
* simple splash screen for all versions (some people are selling it: read release post and earlier discussion for details)

ESR public beta, revision 8a
* changes in IOP reset procedure - should help with some games
* fixed IOP side initialization for dvdv - should help with some games (SSX:OT should work again)
* fixed LoadExecPS2 - more games should work fine (mostly capcom's "anthologies" and "collections")
* fixed some timing issues for streaming reads

ESR public beta, revision 8
* changed LoadExecPS2 implementation. It should be now much more compatible (games that were hanging at red screen or after red screen should work fine now)
* restructurized code placement for better (I hope) compatibility
* fixed some bugs on EE side, that caused some games to not load at all (black screen)
* changed IOP code to wait untill all init/patching is done (no more white screens at beginning I hope)
* added additional file "dvd direct off" - it has similar feature that hdloader "mode 3", will disable ESR after first IOP reset (might be necessary for some games)
* changed SYSTEM.CNF parser once again
* updated imagedrv module with corrected version
* lots of other minor fixes, mainly on EE side

ESR public beta, revision 7b
* changed SYSTEM.CNF parser, so it will also work with names without ISO ver suffix
* replaced imagedrv module with my own (thanks neme for pointing it out, I didn't know it might have been coded by sony)

ESR public beta, revision 7a
* fixed a bug in new stream method

ESR public beta, revision 7
* new basic method for all reads "app-esr hybrid"
* ICO has the sound back (hopefully other old games too)
* fixed a bug in stream handling, some games that had problems getting data from discs, should work fine now

ESR public beta, revision 6b
* initial public release.



--------------------------
IMPORTANT NOTE: The ESR application requires my cdvdinit fix to be loaded first, so either use FMCB with default launcher (it will contain my fix) or launch it manually (using RUNME1.1a). If you cannot access cdvd after applying cdvdinit fix, then you're out of luck, sorry (you'll have to wait until I will find a way to fix the init procedure). It's been tested mostly with first versions of FMCB (that used crosslinking - easier to test on whole variety of consoles) and using my RUNME1.1a (but should work with any others as long as cdvdinit fix is used).

Take a note, that current releases will not work with mrbrown's ps1 exploit.

Short background: ESR is an application that gives you the possibility to launch DVD discs patched to DVDV format on unmodded consoles.

I'm attaching set of three applications. One is intended for launching games directly from dvd (but can also launch homebrew apps from DVDV discs, just SYSTEM.CNF and proper elf is needed) - "dvd direct" version . The other is to launch elf files in either mcx:/BOOT/BOOT.ELF or mcx:/B?DATA-SYSTEM/BOOT.ELF - "mcard" version. The third is "dvd direct off" version, which is almost the same as the "dvd direct" but will disable ESR after first full successful IOP reset (think about it as "mode 3" in hdloader. All should have similar compatibility (with obvious limitations for "off" version).

All will let you access dvdv patched, burned games (and not only games). You can use it to launch uLE with DVDV support, as well as HDLoader to install such games (then, the games will work under hdl without any problems - but you'll have to poweroff console and run hdloader again. It's because main program of hdloader uses the same memory space that my launcher, so running a game in hdl while ESR is active would cause freeze. In GUI version there will be option "Disable ESR after first IOP reset" that will solve also this problem).

The game's compatibility should be quite nice. ESR has been tested internally with ~100 games (and many more by other users).

The homebrew compatibility is worse. It's because some homebrew applications will try to use the same memory that ESR uses.

All versions are placed at 0xf0800. Additional stack is placed at 0xf07d0. Intermediate iop replacement images are written (if needed) to 0x88000. All versions should have the same compatibility.

DNAS protected games can be played, but you'll have to patch them with proper number first (windip and co.).

DVD9 games can be played. You have two choices. You can patch it with toxic patcher then dvdpatch and burn... or simply make image, patch it and burn it (this part is under testing - patching might not be excellent, though it works with GOW2).

CD games can be played only after converting to DVD (not all are easy to do... due to absolute LBA addressing - just use some tuts available on the net).

Take a note, that some console versions will require the dvd disc to have DVD-ROM book type for DVD+R/+RW media. Make sure you've changed it manually or selected it to set the booktype automatically in your burning software. DVD-R should also work fine. As for DVD+/-RW... it really depends on your laser unit quality, they're just much harder to read.

Use good quality media, so you won't have to submit nonexistent bugs!

Take a note, that all versions require DVD/DVDV in drive before launching them... else they'll freeze on black screen and wait for you to put the disc in (then they'll resume the work).

Now, the last, but also very important notice:

ESR has been tested quite a lot, but some big changes were made recently. So take a note that the software is still in beta stage. Some unknown erros may ocurr. If you're not willing to help make it better, don't download it. If you're having some problems, give as much details as you can: console model and region, game name and region. Game ID and iop replacement image version it uses, steps that will be helpful to reproduce the bug, what colors flashed on screen and how many times (red, green, blue, cyan, magenta, yellow, white).


Legall stuff (the easy version):

1. The project is written from scratch and homebrew ps2sdk has been used.
2. It doesn't contain any copyrighted materials.
3. It's intended to be used with homebrew applications as well as backups of legally owned games and applications.
4. Author is not responsible for any damage caused by the software.
5. If you like to modify it - ask first. Maybe your changes can make into the official release... it will also make me able to keep everything clear (which is vital during beta stage... it would be hard to gather info on issues caused by many versions if not all were released by me).
6. The ESR application cannot be used for commercial purposes under any circumstances.

If you redistributing ESR, please leave original names and the readme inside. Also, until stable version is made, do not embed ESR in other applications. It's necessary to keep the same nomenclature and version numbers. It will help me keep bug reports clean and understandable.

Source code of both IOP and EE side application will be released with first stable version.



For patching use either bootsector's cmd line version of ESR Patcher, his java GUI version or simple win32 GUI version of ESR Patcher.

Short tutorial for games:

1. Put your original game in drive and make image of it.
2. Patch it.
3. Burn it.
4. Put it in your PS2 and launch ESR (direct DVD version).
5. That's it!

Short tutorial for homebrew apps (launching from DVD):

1. Start new compilation of DVDVideo.
2. Put all necessary DVDV structure files.
3. Put your SYSTEM.CNF in root directory of disc (remember about the ;1 ISO version extension).
4. Put apropriate executable (same as in SYSTEM.CNF)
5. Make sure the DVD will be hybrid udf/iso.
6. Burn it.
7. Put it in your PS2 and launch ESR (direct DVD version).
8. That's it!

... or just put your homebrew app as mcx:/BOOT/BOOT.ELF or mcx:/B?DATA-SYSTEM/BOOT.ELF, whete mcx is either mc0 or mc1 and ? means reagional code. Now run the second file (mcard version). Though, the best choice is to have uLE in one of the paths and launch other apps from it.



Great thanks to all testers that wasted their precious time with this application: dlanor, ebi and krzysio - I can always count on you.
