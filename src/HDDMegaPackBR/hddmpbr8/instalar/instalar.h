void instalaMegaPack(void) {
   int total = 0, ok = 0;
   total++;
   if(copiaArquivo("cdfs:/APPS/APPLIST.DAT", "pfs0:/APPLIST.DAT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/BOOT.ELF", "pfs0:/boot.elf") >= 0)
      ok++;
   criaDiretorio("pfs0:/AHDL08B");
   total++;
   if(copiaArquivo("cdfs:/APPS/AHDL08B/PATCH08B.TXT", "pfs0:/AHDL08B/PATCH08B.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/AHDL08B/LEIAME.TXT", "pfs0:/AHDL08B/LEIAME.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/AHDL08B/AHDL08B.ELF", "pfs0:/AHDL08B/AHDL08B.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/AHDL08B/UNINSTALL.CNF", "pfs0:/AHDL08B/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/ZLCD");
   total++;
   if(copiaArquivo("cdfs:/APPS/ZLCD/ZLCD.ELF", "pfs0:/ZLCD/ZLCD.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/ZLCD/UNINSTALL.CNF", "pfs0:/ZLCD/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/ZLDVD");
   total++;
   if(copiaArquivo("cdfs:/APPS/ZLDVD/ZLDVD.ELF", "pfs0:/ZLDVD/ZLDVD.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/ZLDVD/UNINSTALL.CNF", "pfs0:/ZLDVD/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/BTB");
   total++;
   if(copiaArquivo("cdfs:/APPS/BTB/BTB.ELF", "pfs0:/BTB/BTB.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/BTB/README.TXT", "pfs0:/BTB/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/BTB/UNINSTALL.CNF", "pfs0:/BTB/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/CBREAK92");
   total++;
   if(copiaArquivo("cdfs:/APPS/CBREAK92/CBREAK92.ELF", "pfs0:/CBREAK92/CBREAK92.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/CBREAK92/README.TXT", "pfs0:/CBREAK92/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/CBREAK92/UNINSTALL.CNF", "pfs0:/CBREAK92/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/DUMP");
   total++;
   if(copiaArquivo("cdfs:/APPS/DUMP/HDDDUMP.ELF", "pfs0:/DUMP/HDDDUMP.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/DUMP/README.TXT", "pfs0:/DUMP/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/DUMP/UNINSTALL.CNF", "pfs0:/DUMP/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/FORMAT");
   total++;
   if(copiaArquivo("cdfs:/APPS/FORMAT/HDDFORMAT.ELF", "pfs0:/FORMAT/HDDFORMAT.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/FORMAT/README.TXT", "pfs0:/FORMAT/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/FORMAT/UNINSTALL.CNF", "pfs0:/FORMAT/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/EXECFTPS");
   total++;
   if(copiaArquivo("cdfs:/APPS/EXECFTPS/CONFIG.DAT", "pfs0:/EXECFTPS/CONFIG.DAT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/EXECFTPS/EXECFTPS.ELF", "pfs0:/EXECFTPS/EXECFTPS.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/EXECFTPS/INFO.TXT", "pfs0:/EXECFTPS/INFO.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/EXECFTPS/README.TXT", "pfs0:/EXECFTPS/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/EXECFTPS/_EXECFTPS.ELF", "pfs0:/EXECFTPS/_EXECFTPS.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/EXECFTPS/UNINSTALL.CNF", "pfs0:/EXECFTPS/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/FAPLINK");
   total++;
   if(copiaArquivo("cdfs:/APPS/FAPLINK/FAPLINK.ELF", "pfs0:/FAPLINK/FAPLINK.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/FAPLINK/README.TXT", "pfs0:/FAPLINK/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/FAPLINK/UNINSTALL.CNF", "pfs0:/FAPLINK/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/HDLDSVR");
   total++;
   if(copiaArquivo("cdfs:/APPS/HDLDSVR/HDLD_SVR.ELF", "pfs0:/HDLDSVR/HDLD_SVR.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/HDLDSVR/UNINSTALL.CNF", "pfs0:/HDLDSVR/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/HDLOADER");
   total++;
   if(copiaArquivo("cdfs:/APPS/HDLOADER/HDLOADER.ELF", "pfs0:/HDLOADER/HDLOADER.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/HDLOADER/UNINSTALL.CNF", "pfs0:/HDLOADER/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/HDL08B");
   total++;
   if(copiaArquivo("cdfs:/APPS/HDL08B/PATCH08B.TXT", "pfs0:/HDL08B/PATCH08B.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/HDL08B/LEIAME.TXT", "pfs0:/HDL08B/LEIAME.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/HDL08B/HDL08B.ELF", "pfs0:/HDL08B/HDL08B.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/HDL08B/UNINSTALL.CNF", "pfs0:/HDL08B/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/LAUNCHER");
   total++;
   if(copiaArquivo("cdfs:/APPS/LAUNCHER/CHANGES.TXT", "pfs0:/LAUNCHER/CHANGES.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/LAUNCHER/LAUNCHER.ELF", "pfs0:/LAUNCHER/LAUNCHER.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/LAUNCHER/UNINSTALL.CNF", "pfs0:/LAUNCHER/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/MCLOADER135");
   total++;
   if(copiaArquivo("cdfs:/APPS/MCLOADER135/MCLOADER.ELF", "pfs0:/MCLOADER135/MCLOADER.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MCLOADER135/UNRAR.IRX", "pfs0:/MCLOADER135/UNRAR.IRX") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MCLOADER135/UNINSTALL.CNF", "pfs0:/MCLOADER135/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/MCMAN");
   total++;
   if(copiaArquivo("cdfs:/APPS/MCMAN/MCMAN.ELF", "pfs0:/MCMAN/MCMAN.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MCMAN/README.TXT", "pfs0:/MCMAN/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MCMAN/UNINSTALL.CNF", "pfs0:/MCMAN/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/MP3STT");
   total++;
   if(copiaArquivo("cdfs:/APPS/MP3STT/MP3STT.ELF", "pfs0:/MP3STT/MP3STT.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MP3STT/README.TXT", "pfs0:/MP3STT/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MP3STT/UNINSTALL.CNF", "pfs0:/MP3STT/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/NAPLINK");
   total++;
   if(copiaArquivo("cdfs:/APPS/NAPLINK/NAPLINK.ELF", "pfs0:/NAPLINK/NAPLINK.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/NAPLINK/README.TXT", "pfs0:/NAPLINK/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/NAPLINK/UNINSTALL.CNF", "pfs0:/NAPLINK/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/NEOCD");
   total++;
   if(copiaArquivo("cdfs:/APPS/NEOCD/NEOCD.BIN", "pfs0:/NEOCD/NEOCD.BIN") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/NEOCD/RUN.PBT", "pfs0:/NEOCD/RUN.PBT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/NEOCD/INSTALL.PBT", "pfs0:/NEOCD/INSTALL.PBT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/NEOCD/INSTLIST.PBT", "pfs0:/NEOCD/INSTLIST.PBT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/NEOCD/NEOCD.ELF", "pfs0:/NEOCD/NEOCD.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/NEOCD/NEOCDPS2.TXT", "pfs0:/NEOCD/NEOCDPS2.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/NEOCD/REMOVE.PBT", "pfs0:/NEOCD/REMOVE.PBT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/NEOCD/_NEOCD.ELF", "pfs0:/NEOCD/_NEOCD.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/NEOCD/UNINSTALL.CNF", "pfs0:/NEOCD/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/NEOPOP");
   total++;
   if(copiaArquivo("cdfs:/APPS/NEOPOP/NEOPOP.ELF", "pfs0:/NEOPOP/NEOPOP.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/NEOPOP/README.TXT", "pfs0:/NEOPOP/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/NEOPOP/UNINSTALL.CNF", "pfs0:/NEOPOP/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/PGENCJ");
   total++;
   if(copiaArquivo("cdfs:/APPS/PGENCJ/PGENCJ.ELF", "pfs0:/PGENCJ/PGENCJ.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/PGENCJ/UNINSTALL.CNF", "pfs0:/PGENCJ/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/PS2INFOGB");
   total++;
   if(copiaArquivo("cdfs:/APPS/PS2INFOGB/PS2INFOGB.ELF", "pfs0:/PS2INFOGB/PS2INFOGB.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/PS2INFOGB/README.TXT", "pfs0:/PS2INFOGB/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/PS2INFOGB/UNINSTALL.CNF", "pfs0:/PS2INFOGB/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/PS2INFONES");
   total++;
   if(copiaArquivo("cdfs:/APPS/PS2INFONES/PS2INFONES.ELF", "pfs0:/PS2INFONES/PS2INFONES.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/PS2INFONES/README.TXT", "pfs0:/PS2INFONES/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/PS2INFONES/UNINSTALL.CNF", "pfs0:/PS2INFONES/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/PS2LINK");
   total++;
   if(copiaArquivo("cdfs:/APPS/PS2LINK/PS2LINK.ELF", "pfs0:/PS2LINK/PS2LINK.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/PS2LINK/README.TXT", "pfs0:/PS2LINK/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/PS2LINK/UNINSTALL.CNF", "pfs0:/PS2LINK/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/PS2MENU");
   total++;
   if(copiaArquivo("cdfs:/APPS/PS2MENU/PS2MENU.ELF", "pfs0:/PS2MENU/PS2MENU.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/PS2MENU/README.TXT", "pfs0:/PS2MENU/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/PS2MENU/UNINSTALL.CNF", "pfs0:/PS2MENU/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/MP3");
   total++;
   if(copiaArquivo("cdfs:/APPS/MP3/MP3.ELF", "pfs0:/MP3/MP3.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MP3/README.TXT", "pfs0:/MP3/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MP3/UNINSTALL.CNF", "pfs0:/MP3/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/PS2OS");
   total++;
   if(copiaArquivo("cdfs:/APPS/PS2OS/PS2OS.ELF", "pfs0:/PS2OS/PS2OS.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/PS2OS/README.TXT", "pfs0:/PS2OS/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/PS2OS/UNINSTALL.CNF", "pfs0:/PS2OS/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/PS2PCE");
   total++;
   if(copiaArquivo("cdfs:/APPS/PS2PCE/PS2PCE.ELF", "pfs0:/PS2PCE/PS2PCE.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/PS2PCE/README.TXT", "pfs0:/PS2PCE/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/PS2PCE/UNINSTALL.CNF", "pfs0:/PS2PCE/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/REALPRO");
   total++;
   if(copiaArquivo("cdfs:/APPS/REALPRO/README.TXT", "pfs0:/REALPRO/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/REALPRO/REALPRO.ELF", "pfs0:/REALPRO/REALPRO.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/REALPRO/UNINSTALL.CNF", "pfs0:/REALPRO/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/PSMS");
   total++;
   if(copiaArquivo("cdfs:/APPS/PSMS/PSMS.ELF", "pfs0:/PSMS/PSMS.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/PSMS/README.TXT", "pfs0:/PSMS/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/PSMS/UNINSTALL.CNF", "pfs0:/PSMS/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/PVCS");
   total++;
   if(copiaArquivo("cdfs:/APPS/PVCS/PVCS.ELF", "pfs0:/PVCS/PVCS.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/PVCS/README.TXT", "pfs0:/PVCS/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/PVCS/UNINSTALL.CNF", "pfs0:/PVCS/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/SMS");
   total++;
   if(copiaArquivo("cdfs:/APPS/SMS/SMS.ELF", "pfs0:/SMS/SMS.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/SMS/USBD.IRX", "pfs0:/SMS/USBD.IRX") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/SMS/SMS.PDF", "pfs0:/SMS/SMS.PDF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/SMS/UNINSTALL.CNF", "pfs0:/SMS/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/SNES");
   total++;
   if(copiaArquivo("cdfs:/APPS/SNES/README.TXT", "pfs0:/SNES/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/SNES/SNES.ELF", "pfs0:/SNES/SNES.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/SNES/UNINSTALL.CNF", "pfs0:/SNES/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/WS");
   total++;
   if(copiaArquivo("cdfs:/APPS/WS/README.TXT", "pfs0:/WS/README.TXT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/WS/WS.ELF", "pfs0:/WS/WS.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/WS/UNINSTALL.CNF", "pfs0:/WS/uninstall.cnf") >= 0)
      ok++;
   criaDiretorio("pfs0:/MYPS2");
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/_MYPS2.ELF", "pfs0:/MYPS2/_MYPS2.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/UNINSTALL.CNF", "pfs0:/MYPS2/uninstall.cnf") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/CONFIG.DAT", "pfs0:/MYPS2/CONFIG.DAT") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/MYPS2.ELF", "pfs0:/MYPS2/MYPS2.ELF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SAMBA.XML", "pfs0:/MYPS2/samba.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SYSTEM.CNF", "pfs0:/MYPS2/SYSTEM.CNF") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/USBD.IRX", "pfs0:/MYPS2/USBD.IRX") >= 0)
      ok++;
   criaDiretorio("pfs0:/MYPS2/skins");
   criaDiretorio("pfs0:/MYPS2/skins/default");
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/SKIN.XML", "pfs0:/MYPS2/skins/default/skin.xml") >= 0)
      ok++;
   criaDiretorio("pfs0:/MYPS2/skins/default/pal");
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/DLG_COPY.XML", "pfs0:/MYPS2/skins/default/pal/dlg_copy.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/DLG_KEYBOARD.XML", "pfs0:/MYPS2/skins/default/pal/dlg_keyboard.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/DLG_MSGBOX.XML", "pfs0:/MYPS2/skins/default/pal/dlg_msgbox.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/DLG_PARTITION1.XML", "pfs0:/MYPS2/skins/default/pal/dlg_partition1.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/DLG_PARTITION2.XML", "pfs0:/MYPS2/skins/default/pal/dlg_partition2.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/DLG_THUMB.XML", "pfs0:/MYPS2/skins/default/pal/dlg_thumb.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/DLG_YESNO.XML", "pfs0:/MYPS2/skins/default/pal/dlg_yesno.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/FONT.XML", "pfs0:/MYPS2/skins/default/pal/font.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/LANGUAGE.XML", "pfs0:/MYPS2/skins/default/pal/language.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/MAIN.XML", "pfs0:/MYPS2/skins/default/pal/main.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/MYFILES.XML", "pfs0:/MYPS2/skins/default/pal/myfiles.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/MYMUSIC.XML", "pfs0:/MYPS2/skins/default/pal/mymusic.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/MYPICTURES.XML", "pfs0:/MYPS2/skins/default/pal/mypictures.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/MYPROGRAMS.XML", "pfs0:/MYPS2/skins/default/pal/myprograms.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/NETWORK.XML", "pfs0:/MYPS2/skins/default/pal/network.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/PARTITIONS.XML", "pfs0:/MYPS2/skins/default/pal/partitions.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/RADIO.XML", "pfs0:/MYPS2/skins/default/pal/radio.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/SAMBA.XML", "pfs0:/MYPS2/skins/default/pal/samba.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/SETTINGS.XML", "pfs0:/MYPS2/skins/default/pal/settings.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/SKINS.XML", "pfs0:/MYPS2/skins/default/pal/skins.xml") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/PAL/VIEW.XML", "pfs0:/MYPS2/skins/default/pal/view.xml") >= 0)
      ok++;
   criaDiretorio("pfs0:/MYPS2/skins/default/media");
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/BACKGROUND.PNG", "pfs0:/MYPS2/skins/default/media/background.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/BACKGROUND_.PNG", "pfs0:/MYPS2/skins/default/media/background_.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/BLANK.PNG", "pfs0:/MYPS2/skins/default/media/blank.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/DATE.PNG", "pfs0:/MYPS2/skins/default/media/date.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/DIALOG_BACKGROUND.PNG", "pfs0:/MYPS2/skins/default/media/dialog_background.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/DIRTHUMB.PNG", "pfs0:/MYPS2/skins/default/media/dirthumb.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/ERRORTHUMB.PNG", "pfs0:/MYPS2/skins/default/media/errorthumb.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/EXIT.PNG", "pfs0:/MYPS2/skins/default/media/exit.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/EXIT_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/exit_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/INFO.PNG", "pfs0:/MYPS2/skins/default/media/info.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/ITEMTEXTURE.PNG", "pfs0:/MYPS2/skins/default/media/itemtexture.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/ITEMTEXTUREFOCUS.PNG", "pfs0:/MYPS2/skins/default/media/itemtexturefocus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/KBBTN_SHIFT_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/kbbtn_shift_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/KBBTN_SHIFT_ON.PNG", "pfs0:/MYPS2/skins/default/media/kbbtn_shift_on.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/KBBTN_SPACE_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/kbbtn_space_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/KBOARD_BTN.PNG", "pfs0:/MYPS2/skins/default/media/kboard_btn.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/KBOARD_BTN_DEL.PNG", "pfs0:/MYPS2/skins/default/media/kboard_btn_del.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/KBOARD_BTN_DEL_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/kboard_btn_del_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/KBOARD_BTN_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/kboard_btn_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/KBOARD_BTN_LEFT.PNG", "pfs0:/MYPS2/skins/default/media/kboard_btn_left.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/KBOARD_BTN_LEFT_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/kboard_btn_left_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/KBOARD_BTN_RIGHT.PNG", "pfs0:/MYPS2/skins/default/media/kboard_btn_right.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/KBOARD_BTN_RIGHT_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/kboard_btn_right_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/LANGUAGE.PNG", "pfs0:/MYPS2/skins/default/media/language.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/LIST_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/list_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/LIST_MARKED.PNG", "pfs0:/MYPS2/skins/default/media/list_marked.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/LIST_NOFOCUS.PNG", "pfs0:/MYPS2/skins/default/media/list_nofocus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/LOOP_OFF.PNG", "pfs0:/MYPS2/skins/default/media/loop_off.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/LOOP_OFF_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/loop_off_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/LOOP_ON.PNG", "pfs0:/MYPS2/skins/default/media/loop_on.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/LOOP_ON_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/loop_on_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/MUSIC.PNG", "pfs0:/MYPS2/skins/default/media/music.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/MYFILES.PNG", "pfs0:/MYPS2/skins/default/media/myfiles.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/MYFILES_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/myfiles_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/MYMUSIC.PNG", "pfs0:/MYPS2/skins/default/media/mymusic.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/MYMUSIC_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/mymusic_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/MYPICTURES.PNG", "pfs0:/MYPS2/skins/default/media/mypictures.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/MYPICTURES_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/mypictures_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/MYPROGRAMS.PNG", "pfs0:/MYPS2/skins/default/media/myprograms.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/MYPROGRAMS_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/myprograms_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/NETWORK.PNG", "pfs0:/MYPS2/skins/default/media/network.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/NEXT_TRACK.PNG", "pfs0:/MYPS2/skins/default/media/next_track.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/NEXT_TRACK_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/next_track_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/NIB.PNG", "pfs0:/MYPS2/skins/default/media/nib.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/NIB_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/nib_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/OPTIONS.PNG", "pfs0:/MYPS2/skins/default/media/options.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/OPTIONS_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/options_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/PARTITIONS.PNG", "pfs0:/MYPS2/skins/default/media/partitions.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/PAUSE_OFF.PNG", "pfs0:/MYPS2/skins/default/media/pause_off.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/PAUSE_OFF_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/pause_off_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/PAUSE_ON.PNG", "pfs0:/MYPS2/skins/default/media/pause_on.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/PAUSE_ON_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/pause_on_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/PLAY.PNG", "pfs0:/MYPS2/skins/default/media/play.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/PLAY_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/play_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/PREV_TRACK.PNG", "pfs0:/MYPS2/skins/default/media/prev_track.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/PREV_TRACK_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/prev_track_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/PROGRESS_BACK.PNG", "pfs0:/MYPS2/skins/default/media/progress_back.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/PROGRESS_LEFT.PNG", "pfs0:/MYPS2/skins/default/media/progress_left.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/PROGRESS_MID.PNG", "pfs0:/MYPS2/skins/default/media/progress_mid.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/PROGRESS_RIGHT.PNG", "pfs0:/MYPS2/skins/default/media/progress_right.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/RADIO.PNG", "pfs0:/MYPS2/skins/default/media/radio.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/SAMBA.PNG", "pfs0:/MYPS2/skins/default/media/samba.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/SCROLLDOWN.PNG", "pfs0:/MYPS2/skins/default/media/scrolldown.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/SCROLLUP.PNG", "pfs0:/MYPS2/skins/default/media/scrollup.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/SELECT.PNG", "pfs0:/MYPS2/skins/default/media/select.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/SETTING_OFF.PNG", "pfs0:/MYPS2/skins/default/media/setting_off.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/SETTING_OFF_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/setting_off_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/SETTING_ON.PNG", "pfs0:/MYPS2/skins/default/media/setting_on.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/SETTING_ON_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/setting_on_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/SKINS.PNG", "pfs0:/MYPS2/skins/default/media/skins.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/SLIDER.PNG", "pfs0:/MYPS2/skins/default/media/slider.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/STOP.PNG", "pfs0:/MYPS2/skins/default/media/stop.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/STOP_FOCUS.PNG", "pfs0:/MYPS2/skins/default/media/stop_focus.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/SKINS/DEFAULT/MEDIA/TOGGLED_ON.PNG", "pfs0:/MYPS2/skins/default/media/toggled_on.png") >= 0)
      ok++;
   criaDiretorio("pfs0:/MYPS2/skins/default/fonts");
   criaDiretorio("pfs0:/MYPS2/shoutcast");
   criaDiretorio("pfs0:/MYPS2/logs");
   criaDiretorio("pfs0:/MYPS2/language");
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/LANGUAGE/ENGLISH.XML", "pfs0:/MYPS2/language/english.xml") >= 0)
      ok++;
   criaDiretorio("pfs0:/MYPS2/fonts");
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/FONTS/ARIAL_10.DAT", "pfs0:/MYPS2/fonts/arial_10.dat") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/FONTS/ARIAL_10.PNG", "pfs0:/MYPS2/fonts/arial_10.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/FONTS/ARIAL_10_CENTRAL_EUROPEAN.DAT", "pfs0:/MYPS2/fonts/arial_10_central_european.dat") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/FONTS/ARIAL_10_CENTRAL_EUROPEAN.PNG", "pfs0:/MYPS2/fonts/arial_10_central_european.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/FONTS/ARIAL_10_CYRILLIC.DAT", "pfs0:/MYPS2/fonts/arial_10_cyrillic.dat") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/FONTS/ARIAL_10_CYRILLIC.PNG", "pfs0:/MYPS2/fonts/arial_10_cyrillic.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/FONTS/ARIAL_10_GREEK.DAT", "pfs0:/MYPS2/fonts/arial_10_greek.dat") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/FONTS/ARIAL_10_GREEK.PNG", "pfs0:/MYPS2/fonts/arial_10_greek.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/FONTS/ARIAL_20.DAT", "pfs0:/MYPS2/fonts/arial_20.dat") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/FONTS/ARIAL_20.PNG", "pfs0:/MYPS2/fonts/arial_20.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/FONTS/ARIAL_20_CENTRAL_EUROPEAN.DAT", "pfs0:/MYPS2/fonts/arial_20_central_european.dat") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/FONTS/ARIAL_20_CENTRAL_EUROPEAN.PNG", "pfs0:/MYPS2/fonts/arial_20_central_european.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/FONTS/ARIAL_20_CYRILLIC.DAT", "pfs0:/MYPS2/fonts/arial_20_cyrillic.dat") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/FONTS/ARIAL_20_CYRILLIC.PNG", "pfs0:/MYPS2/fonts/arial_20_cyrillic.png") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/FONTS/ARIAL_20_GREEK.DAT", "pfs0:/MYPS2/fonts/arial_20_greek.dat") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/FONTS/ARIAL_20_GREEK.PNG", "pfs0:/MYPS2/fonts/arial_20_greek.png") >= 0)
      ok++;
   criaDiretorio("pfs0:/MYPS2/docs");
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/LICENSE.GPL", "pfs0:/MYPS2/docs/LICENSE.GPL") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/README.HTML", "pfs0:/MYPS2/docs/Readme.html") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/SKINNING.HTML", "pfs0:/MYPS2/docs/Skinning.html") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/TRANSLATING.HTML", "pfs0:/MYPS2/docs/Translating.html") >= 0)
      ok++;
   criaDiretorio("pfs0:/MYPS2/docs/images");
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/COPY_1.JPG", "pfs0:/MYPS2/docs/images/copy_1.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/COPY_1_SM.JPG", "pfs0:/MYPS2/docs/images/copy_1_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/COPY_2.JPG", "pfs0:/MYPS2/docs/images/copy_2.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/COPY_2_SM.JPG", "pfs0:/MYPS2/docs/images/copy_2_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/DELETE_1.JPG", "pfs0:/MYPS2/docs/images/delete_1.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/DELETE_1_SM.JPG", "pfs0:/MYPS2/docs/images/delete_1_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/DELETE_2.JPG", "pfs0:/MYPS2/docs/images/delete_2.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/DELETE_2_SM.JPG", "pfs0:/MYPS2/docs/images/delete_2_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/LANGUAGE_1.JPG", "pfs0:/MYPS2/docs/images/language_1.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/LANGUAGE_1_SM.JPG", "pfs0:/MYPS2/docs/images/language_1_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/MYFILES_1.JPG", "pfs0:/MYPS2/docs/images/myfiles_1.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/MYFILES_1_SM.JPG", "pfs0:/MYPS2/docs/images/myfiles_1_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/MYMUSIC_1.JPG", "pfs0:/MYPS2/docs/images/mymusic_1.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/MYMUSIC_1_SM.JPG", "pfs0:/MYPS2/docs/images/mymusic_1_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/MYMUSIC_2.JPG", "pfs0:/MYPS2/docs/images/mymusic_2.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/MYMUSIC_2_SM.JPG", "pfs0:/MYPS2/docs/images/mymusic_2_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/MYPICTURES_1.JPG", "pfs0:/MYPS2/docs/images/mypictures_1.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/MYPICTURES_1_SM.JPG", "pfs0:/MYPS2/docs/images/mypictures_1_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/MYPICTURES_2.JPG", "pfs0:/MYPS2/docs/images/mypictures_2.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/MYPICTURES_2_SM.JPG", "pfs0:/MYPS2/docs/images/mypictures_2_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/MYPROGRAMS_1.JPG", "pfs0:/MYPS2/docs/images/myprograms_1.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/MYPROGRAMS_1_SM.JPG", "pfs0:/MYPS2/docs/images/myprograms_1_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/MYPROGRAMS_2.JPG", "pfs0:/MYPS2/docs/images/myprograms_2.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/MYPROGRAMS_2_SM.JPG", "pfs0:/MYPS2/docs/images/myprograms_2_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/NETWORK_1.JPG", "pfs0:/MYPS2/docs/images/network_1.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/NETWORK_1_SM.JPG", "pfs0:/MYPS2/docs/images/network_1_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/NEWFOLDER_1.JPG", "pfs0:/MYPS2/docs/images/newfolder_1.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/NEWFOLDER_1_SM.JPG", "pfs0:/MYPS2/docs/images/newfolder_1_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/NEWFOLDER_2.JPG", "pfs0:/MYPS2/docs/images/newfolder_2.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/NEWFOLDER_2_SM.JPG", "pfs0:/MYPS2/docs/images/newfolder_2_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/PARTITIONS_1.JPG", "pfs0:/MYPS2/docs/images/partitions_1.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/PARTITIONS_1_SM.JPG", "pfs0:/MYPS2/docs/images/partitions_1_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/PARTITION_1.JPG", "pfs0:/MYPS2/docs/images/partition_1.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/PARTITION_1_SM.JPG", "pfs0:/MYPS2/docs/images/partition_1_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/PARTITION_2.JPG", "pfs0:/MYPS2/docs/images/partition_2.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/PARTITION_2_SM.JPG", "pfs0:/MYPS2/docs/images/partition_2_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/RADIO_1.JPG", "pfs0:/MYPS2/docs/images/radio_1.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/RADIO_1_SM.JPG", "pfs0:/MYPS2/docs/images/radio_1_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/RADIO_2.JPG", "pfs0:/MYPS2/docs/images/radio_2.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/RADIO_2_SM.JPG", "pfs0:/MYPS2/docs/images/radio_2_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/SETTINGS_1.JPG", "pfs0:/MYPS2/docs/images/settings_1.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/SETTINGS_1_SM.JPG", "pfs0:/MYPS2/docs/images/settings_1_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/SKINS_1.JPG", "pfs0:/MYPS2/docs/images/skins_1.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/SKINS_1_SM.JPG", "pfs0:/MYPS2/docs/images/skins_1_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/SMB_1.JPG", "pfs0:/MYPS2/docs/images/smb_1.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/SMB_1_SM.JPG", "pfs0:/MYPS2/docs/images/smb_1_sm.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/SMB_2.JPG", "pfs0:/MYPS2/docs/images/smb_2.jpg") >= 0)
      ok++;
   total++;
   if(copiaArquivo("cdfs:/APPS/MYPS2/DOCS/IMAGES/SMB_2_SM.JPG", "pfs0:/MYPS2/docs/images/smb_2_sm.jpg") >= 0)
      ok++;
   criaDiretorio("pfs0:/MYPS2/boot");
   scr_printf("%d de %d arquivo(s) copiado(s) com sucesso!\n\n", ok, total);
}
