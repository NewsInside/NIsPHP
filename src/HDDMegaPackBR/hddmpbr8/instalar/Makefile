PS2SDK_PATH = ${PS2SDK}

EE_BIN = INSTALAR.ELF
EE_OBJS = instalar.o poweroff.o iomanx.o filexio.o ps2dev9.o ps2atad.o\
	ps2hdd.o ps2fs.o #cdvd.o
EE_LIBS = -ldebug -lhdd -lpoweroff -lfileXio -lmc -lcdvd

all:	$(EE_BIN)

clean:
	rm -f *.ELF *.o *.a *.s

poweroff.s:
	bin2s $(PS2SDK_PATH)/iop/irx/poweroff.irx poweroff.s poweroff_irx
	
iomanx.s:
	bin2s $(PS2SDK_PATH)/iop/irx/iomanX.irx iomanx.s iomanx_irx
		
filexio.s:
	bin2s $(PS2SDK_PATH)/iop/irx/fileXio.irx filexio.s filexio_irx
			
ps2dev9.s:
	bin2s $(PS2SDK_PATH)/iop/irx/ps2dev9.irx ps2dev9.s ps2dev9_irx
					
ps2atad.s:
	bin2s $(PS2SDK_PATH)/iop/irx/ps2atad.irx ps2atad.s ps2atad_irx
						
ps2hdd.s:
	bin2s $(PS2SDK_PATH)/iop/irx/ps2hdd.irx ps2hdd.s ps2hdd_irx
							
ps2fs.s:
	bin2s $(PS2SDK_PATH)/iop/irx/ps2fs.irx ps2fs.s ps2fs_irx

#cdvd.s:
#	bin2s irx/cdvd.irx cdvd.s cdvd_irx


include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal

