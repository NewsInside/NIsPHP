                                                     _ __ ___ ____ ______
- -- --- ---- --------------------------------------\ \\\_\\__\\___\\_____\
          /\___ ___  /\________/\______  /\______/\___ /\____ _____
         \\    \   \_\  _  \\_    _    \_\  _    \    \\     \     \
         /         /    /    /    /    /    /    /    /            /
        /         /         /         /         /    /            /
       /   _     /         /     ____/         /    /            /
       \\___\___/\___/____/     /-DzG\___/____/    \\___/___/___/
______ ____ ___ __ _    _/     /            \\___________/
\_____\\___\\__\\_\\\ \-\_____/--[ Presents ]---------------- ---- --- -- -
                        (__)                   (__)
[ Information ]---------------------------------------------- ---- --- -- -
  [ Title ............................................ napClient v1.0.2 ]
  [ Date ................................................... 2002-03-27 ]
  [ What ........ Software to execute code on PS2 using a USB-USB cable ]
  [ Platform .................................................... Win32 ]
  [ Code ......................................................... wiRe ]
  [ Gfx ........................................................... N/A ]
  [ Muzak ......................................................... N/A ]
  [ Homepage .................................. http://www.napalm-x.com ]
  [ Contact ......................................... wiRe@napalm-x.com ]
                                                       _ __ ___ ____ ______
- -- --- ---- --------------------------------------/ ///_//__//___//_____/
                        (__)                   (__)
                        (__)                   (__)
[ Notes ]---------------------------------------------------- ---- --- -- -

  NapLink is a program which allows you to upload code from a PC and
  execute it on a PS2 using a Prolific PL-2301 or PL-2302 USB to USB cable.
  It also provides host filesystem access (and printf) and an exception
  handler for when your code inevitably goes horribly wrong.
 
  What you have here is the Win32 NapLink client. You will need to get the
  NapLink target too (the part that runs on the PS2). There is a Linux
  NapLink client also, in case you need or want that. 

  NapLink is free for commercial or non-commercial use. You may copy and
  distribute NapLink in unmodified form provided that the entire package,
  including - but not restricted to - copyright, trademark notices, 
  disclaimers, .nfo and .diz files, as released by Napalm, is distributed.
  You may not charge a fee for NapLink.

  Please read the following documentation as well as our disclaimer included 
  in this archive.
                                                       _ __ ___ ____ ______
- -- --- ---- --------------------------------------/ ///_//__//___//_____/
                        (__)                   (__)
                        (__)                   (__)
[ History ]-------------------------------------------------- ---- --- -- -

  v1.0.1  - 2002-03-22 - Initial release.
  v1.0.2  - 2002-03-27 - Now works with Windows 98/ME
                                                       _ __ ___ ____ ______
- -- --- ---- --------------------------------------/ ///_//__//___//_____/
                        (__)                   (__)
                        (__)                   (__)
[ Usage ]---------------------------------------------------- ---- --- -- -

 Installation:

  Plug in your cable and direct windows to the folder where you extracted 
  the inf and sys file. If windows doesn't bring up the "New Hardware"
  dialog when you plug in the cable, you may have to go into your System
  Properties and find the pl2301 in the device list, then "Update driver".


 Use:

  Start the NapLink client on your PC. Start the NapLink target on the PS2.
  Ever when a PL-2301 or 2302 USB cable is inserted, the client adds a
  new tab with several controls. If it detects any device connected to its
  other side, it displays "Peer exist". "Ps2 connected" is displayed when
  connection is established (means a first packet was sucessfully sent).
  Now u could upload/execute Files from your pc, reset the ps2 and the log,
  or even save the log to file.

  Here a brief description of the settings u have:
  "Priority" of napClients communication thread, setting this one to high
    increases speed of transmission (usefull if u connect more than one ps2)
  "Disable sound" if u are bored of this windows default music
  "Colors" are better than black'n'white
  "Disable sharing" doesnt allow the ps2 accessing any file on the pc
    (adk: except the one u execute, but only read-only is allowed :)
  "Read only" protects files on your pc to be written to
  "Always share folder of executed file" means the shared folder is identical
    to the folder where the last executed file was located
  "Shared folder" is usefull if u dont like the last option


 Notes:
 
  Files accessed by PS2 always have to be path-relative.
  Example: u execute the file "c:\myprojects\demo1\demo1.elf" and want to
  load "c:\myprojects\demo1\gfx\demo1.001" with setting "Always share folder
  of executed file" checked or "Shared folder" set to "c:\myprojects\demo1\",
  try to open "\gfx\demo1.001" or "gfx\demo1.001". Using '/' instead '\' is
  possible.

  Known to work with Windows 2000, Windows XP, Windows 98, and Windows ME.

                                                      _ __ ___ ____ ______
- -- --- ---- --------------------------------------/ ///_//__//___//_____/
                        (__)                   (__)
                        (__)                   (__)
[ Greets ]--------------------------------------------------- ---- --- -- -

                                   You !
                                                       _ __ ___ ____ ______
- -- --- ---- --------------------------------------/ ///_//__//___//_____/
