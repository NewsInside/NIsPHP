InLink 1.3.2 
____________



1) WHAT IS InLink ?
___________________
InLink has been developed to ease homebrew coding on PlayStation 2 and make the most of the PS2 Ethernet adapter available from Sony.

It is a Win32 client which allows you to download PS2 executables (.ELF & .IRX) from your PC box to the PS2 through Ethernet (the same kind of feature as provided by napLink through USB).

It works with Pukklink PS2 server side software which you can freely download from :
	http://ps2dev.livemedia.com.au

We would like to thank especially :

	- |pukko| who made a very nice work with Pukklink.
	- adresd who is still the perfect Beta Tester.
	- napalm crew who paved the way with wonderful napLink tool.
	- All The EFNET #ps2dev crew for their support, including Jules^.


2) FEATURES
___________
- InLink allows you to send files to the PS2 when Pukklink v 1.0.0 runs on the PS2 side. (NOTICE : wont work with Pukklink v0.9.4 due to protocol changes).
- Auto Reset feature to reset PS2 before sending a new ELF file when console is already running an ELF
- associate .ELF and .IRX file extensions with InLink, so that when you double click a .ELF / .IRX, it gets automagically sent to the PS2 (after auto-reset when required). This feature is available in Setting within the application : click the "Assign ELF & IRX to In-Link" button.
- Network settings to specify both PS2 & PC IP addresses.
- InLink can be DDE driven by itself, so that only one instance of Inlink runs and handles all user ELF execution requests. This feature allows you to invoke InLink from your makefile or build tool as a post link step, while InLink is already running. The new instance will ask the old one to execute the ELF and will stop.
- Video preview integration with DirectShow thru WDM video source on PC (eg : VIVO-equipped video boards, or PCTV boards)
- Video Snapshot / Capture of the preview to grab nice demo screenshots/videos
- Full video settings controls integrated in the application.
- Full Log Display thru printf/nprintf support from PS2 side.
- Full File IO Support thru standard file routines on "host:". This allows PS2 executables to load IRXes, files etc. in the very same way as napLink.
- Auto bring to front Inlink window when executing elf files
	



3) BUG REPORTING / SUGGESTIONS 
______________________________

Bug Fixes from InLink 1.1.1 :

1) File Open/Create/Exclusive modes fix. 
	=> Done in 1.3.0 (sg2 & Long Apr 18, 2003)


2) when using the 'run' command, have the file open dialog remember the last executed filename and supply it in the filename edit box without having to select it again (similar to how naplink does it)

	=> Done in 1.3.0 (sg2 Apr 18, 2003)

3) Auto conversion of CRLF. if i do a printf("test\n") it will not goto the next line. it just prints a block character. atm u have to do printf("test\r\n") to make it goto the next line properly.

	=> Done in 1.3.0 (long Apr 22, 2003)

4) When having huge logs logbox will stop logging when filled. Log Textbox has been replaced by another control able to support up to 4 Gb of logs.

	=> Done in 1.3.0 (long Apr 22, 2003)

5) Wont crash when running video version without a video capture

	=> Done in 1.3.1 (sg Apr 20, 2003)	


If you have any bug report / suggestion, feel free to send a mail to LongChair@hotmail.com
We will try to maintain this tool as much as possible and adapt it to your needs.


Have nice c0ding using In-Link !


5) CONTACTS
___________

-======== InPulse Team ========- 
    Featuring LongChair & sg2

Visit us at http://inpulse.kicks-ass.org

