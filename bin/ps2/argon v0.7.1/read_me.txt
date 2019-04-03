
v. 0.7.1
- Minor fixes.

v. 0.7.0
- Radio - Metadata;
- Radio - Tags, check the example - <categories>/<tag>;
- Radio - fixed freezing due to a lost connection;
- Music - fixed OSD;
- Photos - speedup, smoothing and rotation (Square);
- XML - some changes;
- Menu - more additions.

v. 0.6.0
- Menu - redesigned (unfinished);
- XML - some changes.

v. 0.5.2
- Alternative path for the configuration file - <xml_path> (for example <xml_path>mc0:/BOOT</xml_path>);
- Settings - probably fixed;
- Fixed ISO MPEG-4 decoder (by EEUG);
- Loading icon;
- Logging - use with the supplied ps2link (other versions may have incompatible network drivers);
- Semaphores are broken as usual - so wait for the loading icon to stop.

v. 0.5.1
- AAC decoder - audio (.m4a) and video (.mov, .mp4, .m4v) files (using Melo AAC Decoder - http://sourceforge.net/projects/melo/);
- <server_record> renamed to <login_info>;
- <shortcut> renamed to <ule_path>;
- Videos - grouped by folders;
- Semaphores are still broken - so don't start movie playback until all folders are loaded or while thumbnails are being created, etc.

v. 0.5.0
- Multiserver support:
  - <cifs> - <server_record> - login infos (as much entries as you want);
  - <paths> - actual paths, using //server/share/folder format (//server/share to access all folders is supported, //server to access all shares is not);
- For cdfs use //localhost/cdfs (no mass and no subfolders - until I'll find the cause of these nasty freezes);
- TCP/IP settings moved to Argon.xml - edit <tcpip>;
- Updated SMS part (MPEG playback - .mpg and .m2p only);
- QuickTime/MP4 demuxer (that doesn't mean H.264/AAC/etc. decoders);
- Settings - connect with a browser:
  - WARNING: Argon.xml is sent in a clear form - including passwords - if you don't like that, port some SSL library (like http://www.matrixssl.org/);
  - it's possible to add some flash/java based configuration menu instead - contact me if you are interested;
- Much faster loading;
- Semaphores are still broken - so don't start movie playback until all folders are loaded or while thumbnails are being created, etc.;
- HDD support (launching only, untested).

v. 0.4.0
- SMB support - define up to 2 shares (smb1: and smb2:) in Argon.xml, everything else like in SMS (enable NetBIOS over TCP/IP, etc.);
- Almost fixed Radio - most stations should work;
- Much faster folder parsing;
- Most playback controls should be fixed;
- Semaphores are broken again - so don't start movie playback until all folders are loaded or while thumbnails are being created, etc.;
- Even if your PS2 is not network connected you still have to create mc0:/sys-conf/ipconfig.dat file;
- host: support is dropped and mass: is untested and it doesn't support HDD.

v. 0.3.5
- Radio is working, but pretty much everything else is broken (like playback controls, etc.);
- Added semaphores so there should be no crashes anymore, although there could be freezes;
- Photos - grouped by folders, should be more usable;
- Weather - support for Fahrenheit degrees, change <units> to us.

v. 0.3.3
- Radio support, although very preliminary - no GUI and lots of crashing (edit Argon.xml to add stations - ip addresses only);
- Updated SMS part to v.1.8(rev.2);
- START - refresh folders, SELECT - stop;
- RC support - only for consoles with the IR sensor;
- Supported devices: host, mass, cdfs, mc;
- Some fixes here and there, and likely some bugs.

v. 0.3.0
- Many overall improvements - it's now almost usable (shorter loading times, multithreaded folder parser, etc.);
- Music – partially working (GUI is unfinished and don't press START or SELECT);
- Movies - fixed NTSC playback;
- Photos - thumbnails (may hang on large files);
- Weather - added XOAP server IP address to Argon.xml.

v. 0.2.4
- Movies - partially working (uses settings from SMS config file) - edit <movies> in Argon.xml;
- Music – hangs (after showing the SMS GUI);
- Weather - added support for different weather maps (there is a sample in Argon.xml);
- Preliminary NTSC support - edit Argon.xml.

v. 0.2
- Requires an internet connection;
- Edit Argon.xml to define folders to be parsed - <music> and <photo> (you can add several entries), and the path to uLaunchELF;
- Weather (using the service provided by The Weather Channel) - working. Edit Argon.xml to set you location (here is an explanation on how to obtain your location ID: http://www.xml.com/pub/a/2004/09/29/weather.html). Pressing X on the weather screen will display a satellite image;
- Radio – categories list implemented;
- Photo - working, but libjpeg is damn slow. Thumbnails are shown for only the first five JPEGs (to speedup loading). Left/right - previous/next;
- Music – thumbnails implemented (folder.jpg or AlbumArtSmall.jpg);
- Still single threaded - takes ages to load...

v. 0.1
- Nothing, except the menu itself, is working, not even thumbnails;
- No support for CD/DVD and HDD, only host: and USB (so, you can only start it from there);
- No media change notifications.


Controls
X - confirm, O - cancel
START - refresh, SELECT - back to top


Not licensed for commercial distribution and use.
