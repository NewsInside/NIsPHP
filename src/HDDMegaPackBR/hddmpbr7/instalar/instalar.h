void instalaMegaPack(void) {
   copiaArquivo("cdfs:/APPS/APPLIST.DAT", "pfs0:/APPLIST.DAT");
   copiaArquivo("cdfs:/APPS/BOOT.ELF", "pfs0:/boot.elf");
   criaDiretorio("pfs0:/ZLDVD");
   copiaArquivo("cdfs:/APPS/ZLDVD/UNINSTALL.CNF", "pfs0:/ZLDVD/uninstall.cnf");
   copiaArquivo("cdfs:/APPS/ZLDVD/ZLDVD.ELF", "pfs0:/ZLDVD/ZLDVD.ELF");
   criaDiretorio("pfs0:/ZLCD");
   copiaArquivo("cdfs:/APPS/ZLCD/UNINSTALL.CNF", "pfs0:/ZLCD/uninstall.cnf");
   copiaArquivo("cdfs:/APPS/ZLCD/ZLCD.ELF", "pfs0:/ZLCD/ZLCD.ELF");
   criaDiretorio("pfs0:/WS");
   copiaArquivo("cdfs:/APPS/WS/README.TXT", "pfs0:/WS/README.TXT");
   copiaArquivo("cdfs:/APPS/WS/UNINSTALL.CNF", "pfs0:/WS/uninstall.cnf");
   copiaArquivo("cdfs:/APPS/WS/WS.ELF", "pfs0:/WS/WS.ELF");
   criaDiretorio("pfs0:/SNES");
   copiaArquivo("cdfs:/APPS/SNES/README.TXT", "pfs0:/SNES/README.TXT");
   copiaArquivo("cdfs:/APPS/SNES/SNES.ELF", "pfs0:/SNES/SNES.ELF");
   copiaArquivo("cdfs:/APPS/SNES/UNINSTALL.CNF", "pfs0:/SNES/uninstall.cnf");
   criaDiretorio("pfs0:/SMS");
   copiaArquivo("cdfs:/APPS/SMS/SMS.ELF", "pfs0:/SMS/SMS.ELF");
   copiaArquivo("cdfs:/APPS/SMS/SMS.HTML", "pfs0:/SMS/SMS.HTML");
   copiaArquivo("cdfs:/APPS/SMS/UNINSTALL.CNF", "pfs0:/SMS/uninstall.cnf");
   criaDiretorio("pfs0:/REALPRO");
   copiaArquivo("cdfs:/APPS/REALPRO/README.TXT", "pfs0:/REALPRO/README.TXT");
   copiaArquivo("cdfs:/APPS/REALPRO/REALPRO.ELF", "pfs0:/REALPRO/REALPRO.ELF");
   copiaArquivo("cdfs:/APPS/REALPRO/UNINSTALL.CNF", "pfs0:/REALPRO/uninstall.cnf");
   criaDiretorio("pfs0:/PVCS");
   copiaArquivo("cdfs:/APPS/PVCS/PVCS.ELF", "pfs0:/PVCS/PVCS.ELF");
   copiaArquivo("cdfs:/APPS/PVCS/README.TXT", "pfs0:/PVCS/README.TXT");
   copiaArquivo("cdfs:/APPS/PVCS/UNINSTALL.CNF", "pfs0:/PVCS/uninstall.cnf");
   criaDiretorio("pfs0:/PSMS");
   copiaArquivo("cdfs:/APPS/PSMS/PSMS.ELF", "pfs0:/PSMS/PSMS.ELF");
   copiaArquivo("cdfs:/APPS/PSMS/README.TXT", "pfs0:/PSMS/README.TXT");
   copiaArquivo("cdfs:/APPS/PSMS/UNINSTALL.CNF", "pfs0:/PSMS/uninstall.cnf");
   criaDiretorio("pfs0:/PS2PCE");
   copiaArquivo("cdfs:/APPS/PS2PCE/PS2PCE.ELF", "pfs0:/PS2PCE/PS2PCE.ELF");
   copiaArquivo("cdfs:/APPS/PS2PCE/README.TXT", "pfs0:/PS2PCE/README.TXT");
   copiaArquivo("cdfs:/APPS/PS2PCE/UNINSTALL.CNF", "pfs0:/PS2PCE/uninstall.cnf");
   criaDiretorio("pfs0:/PS2OS");
   copiaArquivo("cdfs:/APPS/PS2OS/PS2OS.ELF", "pfs0:/PS2OS/PS2OS.ELF");
   copiaArquivo("cdfs:/APPS/PS2OS/README.TXT", "pfs0:/PS2OS/README.TXT");
   copiaArquivo("cdfs:/APPS/PS2OS/UNINSTALL.CNF", "pfs0:/PS2OS/uninstall.cnf");
   criaDiretorio("pfs0:/PS2MENU");
   copiaArquivo("cdfs:/APPS/PS2MENU/PS2MENU.ELF", "pfs0:/PS2MENU/PS2MENU.ELF");
   copiaArquivo("cdfs:/APPS/PS2MENU/README.TXT", "pfs0:/PS2MENU/README.TXT");
   copiaArquivo("cdfs:/APPS/PS2MENU/UNINSTALL.CNF", "pfs0:/PS2MENU/uninstall.cnf");
   criaDiretorio("pfs0:/PS2LINK");
   copiaArquivo("cdfs:/APPS/PS2LINK/PS2LINK.ELF", "pfs0:/PS2LINK/PS2LINK.ELF");
   copiaArquivo("cdfs:/APPS/PS2LINK/README.TXT", "pfs0:/PS2LINK/README.TXT");
   copiaArquivo("cdfs:/APPS/PS2LINK/UNINSTALL.CNF", "pfs0:/PS2LINK/uninstall.cnf");
   criaDiretorio("pfs0:/PS2INFONES");
   copiaArquivo("cdfs:/APPS/PS2INFONES/PS2INFONES.ELF", "pfs0:/PS2INFONES/PS2INFONES.ELF");
   copiaArquivo("cdfs:/APPS/PS2INFONES/README.TXT", "pfs0:/PS2INFONES/README.TXT");
   copiaArquivo("cdfs:/APPS/PS2INFONES/UNINSTALL.CNF", "pfs0:/PS2INFONES/uninstall.cnf");
   criaDiretorio("pfs0:/PS2INFOGB");
   copiaArquivo("cdfs:/APPS/PS2INFOGB/PS2INFOGB.ELF", "pfs0:/PS2INFOGB/PS2INFOGB.ELF");
   copiaArquivo("cdfs:/APPS/PS2INFOGB/README.TXT", "pfs0:/PS2INFOGB/README.TXT");
   copiaArquivo("cdfs:/APPS/PS2INFOGB/UNINSTALL.CNF", "pfs0:/PS2INFOGB/uninstall.cnf");
   criaDiretorio("pfs0:/PGENCJ");
   copiaArquivo("cdfs:/APPS/PGENCJ/PGENCJ.ELF", "pfs0:/PGENCJ/PGENCJ.ELF");
   copiaArquivo("cdfs:/APPS/PGENCJ/UNINSTALL.CNF", "pfs0:/PGENCJ/uninstall.cnf");
   criaDiretorio("pfs0:/NEOPOP");
   copiaArquivo("cdfs:/APPS/NEOPOP/NEOPOP.ELF", "pfs0:/NEOPOP/NEOPOP.ELF");
   copiaArquivo("cdfs:/APPS/NEOPOP/README.TXT", "pfs0:/NEOPOP/README.TXT");
   copiaArquivo("cdfs:/APPS/NEOPOP/UNINSTALL.CNF", "pfs0:/NEOPOP/uninstall.cnf");
   criaDiretorio("pfs0:/NEOCD");
   copiaArquivo("cdfs:/APPS/NEOCD/NEOCD.BIN", "pfs0:/NEOCD/NEOCD.BIN");
   copiaArquivo("cdfs:/APPS/NEOCD/NEOCD.ELF", "pfs0:/NEOCD/NEOCD.ELF");
   copiaArquivo("cdfs:/APPS/NEOCD/NEOCDPS2.TXT", "pfs0:/NEOCD/NEOCDPS2.TXT");
   copiaArquivo("cdfs:/APPS/NEOCD/README.TXT", "pfs0:/NEOCD/README.TXT");
   copiaArquivo("cdfs:/APPS/NEOCD/UNINSTALL.CNF", "pfs0:/NEOCD/uninstall.cnf");
   criaDiretorio("pfs0:/NAPLINK");
   copiaArquivo("cdfs:/APPS/NAPLINK/NAPLINK.ELF", "pfs0:/NAPLINK/NAPLINK.ELF");
   copiaArquivo("cdfs:/APPS/NAPLINK/README.TXT", "pfs0:/NAPLINK/README.TXT");
   copiaArquivo("cdfs:/APPS/NAPLINK/UNINSTALL.CNF", "pfs0:/NAPLINK/uninstall.cnf");
   criaDiretorio("pfs0:/MYPS2");
   copiaArquivo("cdfs:/APPS/MYPS2/MYPS2.ELF", "pfs0:/MYPS2/MYPS2.ELF");
   copiaArquivo("cdfs:/APPS/MYPS2/README.HTML", "pfs0:/MYPS2/README.HTML");
   copiaArquivo("cdfs:/APPS/MYPS2/UNINSTALL.CNF", "pfs0:/MYPS2/uninstall.cnf");
   criaDiretorio("pfs0:/MP3STT");
   copiaArquivo("cdfs:/APPS/MP3STT/MP3STT.ELF", "pfs0:/MP3STT/MP3STT.ELF");
   copiaArquivo("cdfs:/APPS/MP3STT/README.TXT", "pfs0:/MP3STT/README.TXT");
   copiaArquivo("cdfs:/APPS/MP3STT/UNINSTALL.CNF", "pfs0:/MP3STT/uninstall.cnf");
   criaDiretorio("pfs0:/MP3");
   copiaArquivo("cdfs:/APPS/MP3/MP3.ELF", "pfs0:/MP3/MP3.ELF");
   copiaArquivo("cdfs:/APPS/MP3/README.TXT", "pfs0:/MP3/README.TXT");
   copiaArquivo("cdfs:/APPS/MP3/UNINSTALL.CNF", "pfs0:/MP3/uninstall.cnf");
   criaDiretorio("pfs0:/MCMAN");
   copiaArquivo("cdfs:/APPS/MCMAN/MCMAN.ELF", "pfs0:/MCMAN/MCMAN.ELF");
   copiaArquivo("cdfs:/APPS/MCMAN/README.TXT", "pfs0:/MCMAN/README.TXT");
   copiaArquivo("cdfs:/APPS/MCMAN/UNINSTALL.CNF", "pfs0:/MCMAN/uninstall.cnf");
   criaDiretorio("pfs0:/MCLOADER135");
   copiaArquivo("cdfs:/APPS/MCLOADER135/MCLOADER.ELF", "pfs0:/MCLOADER135/MCLOADER.ELF");
   copiaArquivo("cdfs:/APPS/MCLOADER135/UNINSTALL.CNF", "pfs0:/MCLOADER135/uninstall.cnf");
   copiaArquivo("cdfs:/APPS/MCLOADER135/UNRAR.IRX", "pfs0:/MCLOADER135/UNRAR.IRX");
   criaDiretorio("pfs0:/LAUNCHER");
   copiaArquivo("cdfs:/APPS/LAUNCHER/CHANGES.TXT", "pfs0:/LAUNCHER/CHANGES.TXT");
   copiaArquivo("cdfs:/APPS/LAUNCHER/LAUNCHER.ELF", "pfs0:/LAUNCHER/LAUNCHER.ELF");
   copiaArquivo("cdfs:/APPS/LAUNCHER/UNINSTALL.CNF", "pfs0:/LAUNCHER/uninstall.cnf");
   criaDiretorio("pfs0:/HDLOADER");
   copiaArquivo("cdfs:/APPS/HDLOADER/HDLOADER.ELF", "pfs0:/HDLOADER/HDLOADER.ELF");
   copiaArquivo("cdfs:/APPS/HDLOADER/UNINSTALL.CNF", "pfs0:/HDLOADER/uninstall.cnf");
   criaDiretorio("pfs0:/HDLDSVR");
   copiaArquivo("cdfs:/APPS/HDLDSVR/HDLD_SVR.ELF", "pfs0:/HDLDSVR/HDLD_SVR.ELF");
   copiaArquivo("cdfs:/APPS/HDLDSVR/UNINSTALL.CNF", "pfs0:/HDLDSVR/uninstall.cnf");
   criaDiretorio("pfs0:/HDL08A1");
   copiaArquivo("cdfs:/APPS/HDL08A1/HDL08A1.ELF", "pfs0:/HDL08A1/HDL08A1.ELF");
   copiaArquivo("cdfs:/APPS/HDL08A1/LEIAME.TXT", "pfs0:/HDL08A1/LEIAME.TXT");
   copiaArquivo("cdfs:/APPS/HDL08A1/PATCH08A.TXT", "pfs0:/HDL08A1/PATCH08A.TXT");
   copiaArquivo("cdfs:/APPS/HDL08A1/UNINSTALL.CNF", "pfs0:/HDL08A1/uninstall.cnf");
   criaDiretorio("pfs0:/FORMAT");
   copiaArquivo("cdfs:/APPS/FORMAT/HDDFORMAT.ELF", "pfs0:/FORMAT/HDDFORMAT.ELF");
   copiaArquivo("cdfs:/APPS/FORMAT/README.TXT", "pfs0:/FORMAT/README.TXT");
   copiaArquivo("cdfs:/APPS/FORMAT/UNINSTALL.CNF", "pfs0:/FORMAT/uninstall.cnf");
   criaDiretorio("pfs0:/FAPLINK");
   copiaArquivo("cdfs:/APPS/FAPLINK/FAPLINK.ELF", "pfs0:/FAPLINK/FAPLINK.ELF");
   copiaArquivo("cdfs:/APPS/FAPLINK/README.TXT", "pfs0:/FAPLINK/README.TXT");
   copiaArquivo("cdfs:/APPS/FAPLINK/UNINSTALL.CNF", "pfs0:/FAPLINK/uninstall.cnf");
   criaDiretorio("pfs0:/EXECFTPS");
   copiaArquivo("cdfs:/APPS/EXECFTPS/CONFIG.DAT", "pfs0:/EXECFTPS/CONFIG.DAT");
   copiaArquivo("cdfs:/APPS/EXECFTPS/EXECFTPS.ELF", "pfs0:/EXECFTPS/EXECFTPS.ELF");
   copiaArquivo("cdfs:/APPS/EXECFTPS/INFO.TXT", "pfs0:/EXECFTPS/INFO.TXT");
   copiaArquivo("cdfs:/APPS/EXECFTPS/README.TXT", "pfs0:/EXECFTPS/README.TXT");
   copiaArquivo("cdfs:/APPS/EXECFTPS/UNINSTALL.CNF", "pfs0:/EXECFTPS/uninstall.cnf");
   criaDiretorio("pfs0:/DUMP");
   copiaArquivo("cdfs:/APPS/DUMP/HDDDUMP.ELF", "pfs0:/DUMP/HDDDUMP.ELF");
   copiaArquivo("cdfs:/APPS/DUMP/README.TXT", "pfs0:/DUMP/README.TXT");
   copiaArquivo("cdfs:/APPS/DUMP/UNINSTALL.CNF", "pfs0:/DUMP/uninstall.cnf");
   criaDiretorio("pfs0:/CBREAK92");
   copiaArquivo("cdfs:/APPS/CBREAK92/CBREAK92.ELF", "pfs0:/CBREAK92/CBREAK92.ELF");
   copiaArquivo("cdfs:/APPS/CBREAK92/README.TXT", "pfs0:/CBREAK92/README.TXT");
   copiaArquivo("cdfs:/APPS/CBREAK92/UNINSTALL.CNF", "pfs0:/CBREAK92/uninstall.cnf");
   criaDiretorio("pfs0:/BTB");
   copiaArquivo("cdfs:/APPS/BTB/BTB.ELF", "pfs0:/BTB/BTB.ELF");
   copiaArquivo("cdfs:/APPS/BTB/README.TXT", "pfs0:/BTB/README.TXT");
   copiaArquivo("cdfs:/APPS/BTB/UNINSTALL.CNF", "pfs0:/BTB/uninstall.cnf");
   criaDiretorio("pfs0:/AHDL08A1");
   copiaArquivo("cdfs:/APPS/AHDL08A1/AHDL08A1.ELF", "pfs0:/AHDL08A1/AHDL08A1.ELF");
   copiaArquivo("cdfs:/APPS/AHDL08A1/LEIAME.TXT", "pfs0:/AHDL08A1/LEIAME.TXT");
   copiaArquivo("cdfs:/APPS/AHDL08A1/PATCH08A.TXT", "pfs0:/AHDL08A1/PATCH08A.TXT");
   copiaArquivo("cdfs:/APPS/AHDL08A1/UNINSTALL.CNF", "pfs0:/AHDL08A1/uninstall.cnf");
}
