PS2 dumper v2.0   by Florin (2006-2007)
=======================================


Intro
--------
This is a tool for dumping information from Playstation2, including bios,
 dvdplayer rom, non-volatile memory, etc. The ELF program has to run on a
 Playstation2 over a 'host'-enabled connection like Naplink or PS2link or
 from CD and it will write to a mass-storage usb device. It will create on PC
 or USB drive a couple of files and a batch script (*.bat). If you used USB,
 copy them to a PC folder along with 7z.exe from cd and run the .bat file
 to pack them into a p2b file. Make sure 7z.exe is in the same directory
 as the dumped files. The next version of PCSX2 will use *.p2b files instead
 of the old bios format. There'll be also a converter for older bios files
 to the p2b format, for backward compatibility.
 You won't need to throw away your old bios files, but it is recommended to
 use the new dumper to get complete information about a PS2. This will help
 the efforts to emulate PS2 as much accurate as possible.


Disclaimer
--------
Use this tool on YOUR OWN RISK. No warranties nor responsability taken.
 If you are unsure to use this tool, please DON'T use it.
 In case of using an USB mass storage drive, remember that the driver has
 experimental write support, so be sure to use a drive that does not contain
 important stuff. You've been warned!!!
 Also, the information dumped can be used only by the owner of the console.
 This tool is to be used with a PS2 emulator, so don't look for support on
 Sony sites, as there is no connection to Sony, SCEA, SCEI, SCEE, etc.


Usage
--------
0. Command line params:
	-noinf -norom0 -nofrom -norom1 -nodiff -norom2 -nonvm
	   each param is optional and if present makes the tool to skip the
	   creation of the corresponding file. default is to create all files
	-forceusb
	   also optional, the tool tries to detect if a 'host' device is
	   available. If specified, the tool will dump to an USB mass drive
           (ie. USB pendrive, USB stick, camera or mobile phone in USB storage mode)


1. Connect to your PS2 using Naplink, Ps2link or whatever method you like. The
 tool was tested to work over USB, Eth and Fw. It's best to use the latest
 Naplink (1.1.0) or the latest PS2link (1.46 or up). With some console models and
 older Naplink or Ps2link the program might crash. You can still get a full set of
 files by using command-line params, to dump missing files.
 Make sure you have enough space on destination drive (host or usb-mass),
 you'll need about 18 megs free.

2. Run ps2dumper.elf (with parameters if needed). Wait till it displays on
 the screen -= DONE =- message. If it hungs see the note (a.) on Modchips and
 try again, using -noxxxx command-line parameters to skip already dumped files.

3. When you got all the files (see note b.) make sure that 7z.exe is in the
 same directory as the bat file and run the last one. The dumped files should
 be replaced by a p2b file.

4. Look on the back of the console on Sony product label and get the
 Serial Number (under the voltage specification). Rename the file to include
 the serial number. Example: if you have Serial Number FB0123456 and
(fresh file)   SCPH-39003_UK_Con_0160_20020319_v7.P2b
 rename it to
(renamed file) SCPH-39003_UK_Con_0160_20020319_v7_FB0123456.P2b

5. You will be able to use it with the next version of PCSX2 (v0.94 or up)


Notes
--------
a. Modchips
   If possible it is best to dump the information from a non-chiped console.
   Also, if you can and know how to disable the modchip while dumping, do so.
   Sometimes the modchips make more difficult to run the program. For instance,
   some Messiah modchip versions makes the MG decryption to fail. To prevent
   that, turn the console off, hold reset button 1 second till the blue light
   comes on, etc (refer to modchip docs)

b. "Do I have all the files?"
   Depending on your console model, you will get more or less files. As a
   generic rule, if you get the message -= DONE =- on the screen, it means
   that you got everything that the program was supposed to dump. It is OK :)
   Only on chinese (SCPH-XXX09) consoles you'll get rom2 file. Erom is inside
   rom1 file, so don't expect a separate file. SCPH-10000 and SCPH-15000 don't
   have dvdplayer rom, so no rom1 and diff files. You should always have inf,
   nvm and rom0 (or from - FlashROM) files.

c. The diff file
   If the console has a dvdplayer encrypted code, the tool will atempt to
   decrypt it and will create a difference file that will be used by PCSX2.

d. Naplink has a problem: it is creating files with read-only attribute on.
   If you run the tool several times, with the old files in place, it will
   not be able to erase and create them again, getting stucked.

e. Speed: the fastest transfer is over Fw, than Ethernet(Ps2link), USB(Naplink)
   and the slowest (depending on your drive) to USB mass storage drive.

f. Some USB storage drives might not be recognised; I tested with my PSP in
   USB mode. If you can use 'host' connection, try -forceusb parameter.


Credits and versions
--------
   - Pukko, he's the author of the first bios dumper (using syscall install)
   - auMatt, created the dumper that got more stuff from ps2 like rom1, erom,
	nvm, etc. and formated the names
   - Loser, added the mec and bba files
   - Sjeep, spoted that rom0 is dumped properly only from iop side on PStwo
   Thanks to all for their work and support and also big thanks to PS2DEV
   dev's for ps2sdk.
   Thanks to PCSX2 team that made this tool possible ;))


License
--------
   You can use this tool freely. Please keep the credits and the original
   distribution source www.pcsx2.net and sf.net/projects/pcsx2
   I'll make available shortly the source code on sf.net


Todo
--------
   1. hw version is unsure for ver 1, 2, 3; for some 4,5; also for v11;
      and there's currently no method to tell ver 12 from 13
   2. detect/print serial number of the console (consoleid/2; +0x1F0 in non-fw)
   3. add log file + loader detection


========
Florin
14jun2006
