/*  Modified by Jayteemaster for inclusion in ps2_pal2ntsc_yfix */

/*  Pcsx2 - Pc Ps2 Emulator
 *  Copyright (C) 2002-2003  Pcsx2 Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/stat.h>
#include "Elfheader.h"

#ifdef GUI
extern void SysPrintf(char *fmt, ...);
#define SysMessage(m) {SysPrintf(m);}
#else
#define SysMessage(m) {fprintf(stderr,m);}
#endif

void ELF_LOG(char *fmt, ...) {
	va_list list;

	va_start(list, fmt);
	vprintf(fmt, list);
	va_end(list);
}


char *sections_names=0;
	
ELF_HEADER elfHeader;	
ELF_PHR	*elfProgH=0;
ELF_SHR	*elfSectH=0;



int readFile(char *Exepath, char *ptr, int offset, int size) {
	FILE *f;
	int ret;
	
	f = fopen(Exepath,"rb");
	if (f == NULL) return -1;
	fseek(f, offset, SEEK_SET);
	ret = fread(ptr, 1, size, f);
	fclose(f);

	return ret;
}


int loadHeaders(char *Exepath) {

	readFile(Exepath, (char *)&elfHeader, 0, sizeof(ELF_HEADER));

	if (elfHeader.e_shentsize != sizeof(ELF_SHR) && elfHeader.e_shnum > 0)
		SysMessage("size of section header not standard\n");
	
	if((elfHeader.e_shnum * elfHeader.e_shentsize) != 0)
		elfSectH = (ELF_SHR *) malloc(elfHeader.e_shnum * elfHeader.e_shentsize);
	else
		elfSectH = NULL;

	if((elfHeader.e_phnum * elfHeader.e_phentsize) != 0)
		elfProgH = (ELF_PHR *) malloc(elfHeader.e_phnum * elfHeader.e_phentsize);
	else
		elfProgH = NULL;
#ifdef Debug
    ELF_LOG("type:      ");
	switch(elfHeader.e_type) {
		default:
		    ELF_LOG("unknown %x",elfHeader.e_type);
			break;
		case 0x0:
			ELF_LOG("no file type");
			break;
		case 0x1:
		    ELF_LOG("relocatable");
			break;
		case 0x2:
		    ELF_LOG("executable");
			break;
	}
	ELF_LOG("\n");
	ELF_LOG("machine:   ");
	switch (elfHeader.e_machine) {
		default:
			ELF_LOG("unknown");
			break;
		case 0x8:
			ELF_LOG("mips_rs3000");
			break;
	}
	ELF_LOG("\n");
	ELF_LOG("version:   %d\n",elfHeader.e_version);
	ELF_LOG("entry:     %08x\n",elfHeader.e_entry);
	ELF_LOG("flags:     %08x\n",elfHeader.e_flags);
	ELF_LOG("eh size:   %08x\n",elfHeader.e_ehsize);
	ELF_LOG("ph off:    %08x\n",elfHeader.e_phoff);
	ELF_LOG("ph entsiz: %08x\n",elfHeader.e_phentsize);
	ELF_LOG("ph num:    %08x\n",elfHeader.e_phnum);
	ELF_LOG("sh off:    %08x\n",elfHeader.e_shoff);
	ELF_LOG("sh entsiz: %08x\n",elfHeader.e_shentsize);
	ELF_LOG("sh num:    %08x\n",elfHeader.e_shnum);
	ELF_LOG("sh strndx: %08x\n",elfHeader.e_shstrndx);
	
	ELF_LOG("\n");
#endif
	return TRUE;
}


BOOL loadProgramHeaders(char *Exepath) {
	int i;

	if (elfHeader.e_phnum == 0) return TRUE;

	// is this critical, or warning?
	if ( elfHeader.e_phentsize != sizeof(ELF_PHR) )
		SysMessage("size of program header not standard\n");
	
	readFile(Exepath,(char *)&elfProgH[0], elfHeader.e_phoff, elfHeader.e_phentsize * elfHeader.e_phnum);
#ifdef Debug		
	for (i = 0 ; i < elfHeader.e_phnum ; i++) {
        ELF_LOG("Elf32 Program Header\n");	
		ELF_LOG("type:      ");
		switch (elfProgH[i].p_type) {
			default:
	            ELF_LOG("unknown %x", (int)elfProgH[i].p_type);
				break;
			case 0x1:
	            ELF_LOG("load");
				/*
				if (elfHeader.e_shnum == 0) {
					readFile(Exepath,(char*)(&psM[elfProgH[i].p_paddr &0x1ffffff]), elfProgH[i].p_offset, elfProgH[i].p_filesz);
					ELF_LOG("\t*LOADED*");
				}
				*/
				break;
		}
        ELF_LOG("\n");
		ELF_LOG("offset:    %08x\n",(int)elfProgH[i].p_offset);
		ELF_LOG("vaddr:     %08x\n",(int)elfProgH[i].p_vaddr);
		ELF_LOG("paddr:     %08x\n",elfProgH[i].p_paddr);
		ELF_LOG("file size: %08x\n",elfProgH[i].p_filesz);
		ELF_LOG("mem size:  %08x\n",elfProgH[i].p_memsz);
		ELF_LOG("flags:     %08x\n",elfProgH[i].p_flags);
		ELF_LOG("palign:    %08x\n",elfProgH[i].p_align);
		ELF_LOG("\n");
	}
#endif
	return TRUE;
}

int signal_secth_prob=0;

BOOL loadSectionHeaders(char *Exepath) {
	int i;
	int i_st = -1;
	int i_dt = -1;

	if (elfHeader.e_shnum == 0) return TRUE;

	i=readFile(Exepath,(char *)&elfSectH[0], elfHeader.e_shoff, elfHeader.e_shentsize * elfHeader.e_shnum);
	if (i<elfHeader.e_shentsize * elfHeader.e_shnum)
		signal_secth_prob=1;
	
	if (elfHeader.e_shstrndx < elfHeader.e_shnum) {
		sections_names = (char*)malloc(elfSectH[elfHeader.e_shstrndx].sh_size);
		readFile(Exepath, (char *)sections_names, elfSectH[elfHeader.e_shstrndx].sh_offset, elfSectH[elfHeader.e_shstrndx].sh_size);
	}
		
	for (i = 0 ; i < elfHeader.e_shnum ; i++) {
#ifdef Debug
        ELF_LOG("Elf32 Section Header [%x] %s", i, &sections_names[elfSectH[i].sh_name]);
		if (elfSectH[i].sh_flags & 0x2) {
			/*
			//2002-09-19 (Florin)
			args_ptr=min(args_ptr, elfSectH[i].sh_addr &0x1ffffff);
			//---------------
			readFile(Exepath,(char*)(&psM[elfSectH[i].sh_addr &0x1ffffff]), elfSectH[i].sh_offset, elfSectH[i].sh_size);
            ELF_LOG("\t*LOADED*");
			*/
		}
        ELF_LOG("\n");
		ELF_LOG("type:      ");
		switch (elfSectH[i].sh_type) {
			default:
	            ELF_LOG("unknown %08x",elfSectH[i].sh_type);
				break;
			case 0x0:
	             ELF_LOG("null");
				break;
			case 0x1:
	             ELF_LOG("progbits");
				break;
			case 0x2:
	            ELF_LOG("symtab");
				break;
			case 0x3:
	            ELF_LOG("strtab");
				break;
			case 0x4:
	            ELF_LOG("rela");
				break;
			case 0x8:
	            ELF_LOG("no bits");
				break;
			case 0x9:
	            ELF_LOG("rel");
				break;
		}
        ELF_LOG("\n");
		ELF_LOG("flags:     %08x\n", elfSectH[i].sh_flags);
		ELF_LOG("addr:      %08x\n", elfSectH[i].sh_addr);
		ELF_LOG("offset:    %08x\n", elfSectH[i].sh_offset);
		ELF_LOG("size:      %08x\n", elfSectH[i].sh_size);
		ELF_LOG("link:      %08x\n", elfSectH[i].sh_link);
		ELF_LOG("info:      %08x\n", elfSectH[i].sh_info);
		ELF_LOG("addralign: %08x\n", elfSectH[i].sh_addralign);
		ELF_LOG("entsize:   %08x\n", elfSectH[i].sh_entsize);
#endif
		// dump symbol table
	
		if (elfSectH[i].sh_type == 0x02) {
			i_st = i; i_dt = elfSectH[i].sh_link; }
		}

	if (i_st >= 0 && i_dt >= 0)	{
		char *SymNames;
		Elf32_Sym *eS;

		SymNames = (char*)malloc(elfSectH[i_dt].sh_size);
		readFile(Exepath, SymNames, elfSectH[i_dt].sh_offset, elfSectH[i_dt].sh_size);

		eS = (Elf32_Sym*)malloc(elfSectH[i_st].sh_size);
		readFile(Exepath, (char*)eS, elfSectH[i_st].sh_offset, elfSectH[i_st].sh_size);

		for (i=1; i<(int)(elfSectH[i_st].sh_size / sizeof(Elf32_Sym)); i++) {
			if (eS[i].st_value != 0 && ELF32_ST_TYPE(eS[i].st_info) == 2) {
			}
		}
	
		free(SymNames);
		free(eS);
	}

	return TRUE;
}


int loadElfFile(char *filename) {
	struct stat buf;


	if (stat(filename, &buf) != 0)
		return -1;

	//-------------------
	loadHeaders(filename);
   	loadProgramHeaders(filename);
   	loadSectionHeaders(filename);
	//---------------
	return 0;
}


///////////////////////////////////////////////////////////////////////////
int modifyFile(char *Exepath, char *ptr, int offset, int size) {
	FILE *f;
	int ret;
	
	f = fopen(Exepath,"r+b");
	if (f == NULL) return -1;
	fseek(f, offset, SEEK_SET);
	ret = fwrite(ptr, 1, size, f);
	fclose(f);

	return ret;
}


BOOL saveHeaders(char *Exepath) {

	modifyFile(Exepath, (char *)&elfHeader, 0, sizeof(ELF_HEADER));

	return TRUE;
}


BOOL saveProgramHeaders(char *Exepath) {

	if (elfHeader.e_phnum == 0) return TRUE;
	
	modifyFile(Exepath,(char *)&elfProgH[0], elfHeader.e_phoff, elfHeader.e_phentsize * elfHeader.e_phnum);
	
	return TRUE;
}


BOOL saveSectionHeaders(char *Exepath) {

	if (elfHeader.e_shnum == 0) return TRUE;

	modifyFile(Exepath,(char *)&elfSectH[0], elfHeader.e_shoff, elfHeader.e_shentsize * elfHeader.e_shnum);
	
	return TRUE;
}


int saveElfFile(char *filename) {
	struct stat buf;


	if (stat(filename, &buf) != 0)
		return -1;

	//-------------------
	saveHeaders(filename);
   	saveProgramHeaders(filename);
	if (signal_secth_prob==0)
		saveSectionHeaders(filename);
	//---------------
	return 0;
}

///////////////////////////////////////////////////////////////////////////
void ClearHeaders()
{
	signal_secth_prob=0;
	if (sections_names)
		free(sections_names);
	memset(&elfHeader, 0, sizeof(ELF_HEADER));
	if (elfProgH)
		free(elfProgH);
	if (elfSectH)
		free(elfSectH);
}
