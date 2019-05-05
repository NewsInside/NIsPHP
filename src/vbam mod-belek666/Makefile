# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2004, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
#
# $Id: Makefile.sample 1150 2005-06-12 11:42:08Z pixel $

IRX_DIR = ./ps2/irx

EE_PACKER = ps2-packer
EE_BIN2S = bin2s

EE_BIN = ./bin/vbam.elf

EE_CXXFLAGS += -DNO_ASM -DC_CORE -DNO_GL -DNO_D3D -DNO_OAL -DFINAL_VERSION -DSDL -DNO_XAUDIO2
EE_INCS += -I./src -I./src/gb -I./src/sdl -I./ps2/include -I./ps2/include/zlib -I./ps2/include/SDL -I./ps2/include/png

EE_LDFLAGS += -L./ps2/lib
EE_LIBS += -lpng -lsdl -lsdlmain -lz -lpatches -lpad -lfileXio -lm -lmc

# ** sources **
GBA_SRC =\
	src/gba/agbprint.cpp\
	src/gba/armdis.cpp\
	src/gba/bios.cpp\
	src/gba/Cheats.cpp\
	src/gba/CheatSearch.cpp\
	src/gba/EEprom.cpp\
	src/gba/elf.cpp\
	src/gba/Flash.cpp\
	src/gba/GBA.cpp\
	src/gba/GBA-arm.cpp\
	src/gba/GBAGfx.cpp\
	src/gba/GBA-thumb.cpp\
	src/gba/Globals.cpp\
	src/gba/Mode0.cpp\
	src/gba/Mode1.cpp\
	src/gba/Mode2.cpp\
	src/gba/Mode3.cpp\
	src/gba/Mode4.cpp\
	src/gba/Mode5.cpp\
	src/gba/remote.cpp\
	src/gba/RTC.cpp\
	src/gba/Sound.cpp\
	src/gba/Sram.cpp

GBC_SRC =\
	src/gb/gbCheats.cpp\
	src/gb/GB.cpp\
	src/gb/gbDis.cpp\
	src/gb/gbGfx.cpp\
	src/gb/gbGlobals.cpp\
	src/gb/gbMemory.cpp\
	src/gb/gbPrinter.cpp\
	src/gb/gbSGB.cpp\
	src/gb/gbSound.cpp

APU_SRC =\
	src/apu/Gb_Oscs.cpp\
	src/apu/Multi_Buffer.cpp\
	src/apu/Blip_Buffer.cpp\
	src/apu/Effects_Buffer.cpp\
	src/apu/Gb_Apu.cpp\
	src/apu/Gb_Apu_State.cpp

FILTERS_SRC =\
	src/filters/bilinear.cpp\
	src/filters/pixel.cpp\
	src/filters/simpleFilter.cpp\
	src/filters/2xSaI.cpp\
	src/filters/admame.cpp\
	src/filters/hq2x.cpp\
	src/filters/interframe.cpp\
	src/filters/scanline.cpp\
	src/filters/hq/c/hq_implementation.cpp

COMMON_SRC =\
	src/common/fex_mini.cpp\
	src/common/SoundSDL.cpp

REST_SRC =\
	src/Util.cpp\

# Source code of aplication
APP_SDL =\
	src/sdl/dummy.cpp\
	src/sdl/filters.cpp\
	src/sdl/inputSDL.cpp\
	src/sdl/SDL.cpp\
	src/sdl/text.cpp\
	src/sdl/ps2time.cpp

APP_SDL_C =\
	src/common/memgzio.c\
	src/sdl/PS2_Init.c

# IRX modules - modules have to be in IRX_DIR
EE_IRX = usbd.irx usbhdfsd.irx
EE_IRX_OBJ = $(EE_IRX:.irx=.o)

# ** objects **

# Objects for GBA and GBC
OBJ_GBA = $(GBA_SRC:.cpp=.o)
OBJ_GBC = $(GBC_SRC:.cpp=.o)
OBJ_APU = $(APU_SRC:.cpp=.o)
OBJ_REST = $(REST_SRC:.cpp=.o)

OBJ_COMMON = $(COMMON_SRC:.cpp=.o)
OBJ_FILTERS = $(FILTERS_SRC:.cpp=.o)

# Objects for SDL part
OBJ_APP_SDL = $(APP_SDL:.cpp=.o)
OBJ_APP_SDL_C = $(APP_SDL_C:.c=.o)

# ELF objects together
OBJ_ELF_SDL = $(OBJ_GBC) $(OBJ_APU) $(OBJ_FILTERS) $(OBJ_GBA) $(OBJ_APP_SDL) $(OBJ_APP_SDL_C)\
	        $(OBJ_COMMON) $(OBJ_REST)

OBJ_ELF_PS2 = usbd.o usbhdfsd.o

# main obj
EE_OBJS = $(OBJ_ELF_SDL) $(OBJ_ELF_PS2)

all: $(EE_BIN) pack
	ee-strip $(EE_BIN)

$(EE_IRX_OBJ:.o=.s):
	$(EE_BIN2S) $(IRX_DIR)/$(@:.s=.irx) $@ $(@:.s=_irx)

clean:
	@rm -f src/*.o src/apu/*.o src/gba/*.o src/gb/*.o src/sdl/*.o src/common/*.o \
		 src/filters/*.o src/filters/hq/c/*.o bin/*.elf *.s *.o
	@echo Removed everything!
run:
	ps2client -h 10.0.0.10 execee host:bin/vbam.elf
reset:
	ps2client -h 10.0.0.10 reset
test:
	ee-addr2line -e bin/vbam.elf 001caae0
pack:
	$(EE_PACKER) $(EE_BIN) $(EE_BIN:.elf=-packed.elf)

include ps2/Makefile.pref
include ps2/Makefile.eeglobal_cpp