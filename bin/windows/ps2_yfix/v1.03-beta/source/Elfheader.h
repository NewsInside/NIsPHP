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

#define BOOL int

#undef TRUE
#define TRUE  1
#undef FALSE
#define FALSE 0


typedef struct {
    unsigned char	e_ident[16];    //0x7f,"ELF"  (ELF file identifier)
    unsigned short int	e_type;         //ELF type: 0=NONE, 1=REL, 2=EXEC, 3=SHARED, 4=CORE
	unsigned short int	e_machine;      //Processor: 8=MIPS R3000
	unsigned int	e_version;      //Version: 1=current
	unsigned int	e_entry;        //Entry point address
	unsigned int	e_phoff;        //Start of program headers (offset from file start)
	unsigned int	e_shoff;        //Start of section headers (offset from file start)
	unsigned int	e_flags;        //Processor specific flags = 0x20924001 noreorder, mips
	unsigned short int	e_ehsize;       //ELF header size (0x34 = 52 bytes)
	unsigned short int	e_phentsize;    //Program headers entry size 
	unsigned short int	e_phnum;        //Number of program headers
	unsigned short int	e_shentsize;    //Section headers entry size
	unsigned short int	e_shnum;        //Number of section headers
	unsigned short int	e_shstrndx;     //Section header stringtable index	
} ELF_HEADER;

typedef struct {
	unsigned int p_type;         //see notes1
	unsigned int p_offset;       //Offset from file start to program segment.
	unsigned int p_vaddr;        //Virtual address of the segment
	unsigned int p_paddr;        //Physical address of the segment
	unsigned int p_filesz;       //Number of bytes in the file image of the segment
	unsigned int p_memsz;        //Number of bytes in the memory image of the segment
	unsigned int p_flags;        //Flags for segment
	unsigned int p_align;        //Alignment. The address of 0x08 and 0x0C must fit this alignment. 0=no alignment
} ELF_PHR;

/*
notes1
------
0=Inactive
1=Load the segment into memory, no. of bytes specified by 0x10 and 0x14
2=Dynamic linking
3=Interpreter. The array element must specify a path name
4=Note. The array element must specify the location and size of aux. info
5=reserved
6=The array element must specify location and size of the program header table.
*/

typedef struct {
	unsigned int	sh_name;        //No. to the index of the Section header stringtable index
    unsigned int	sh_type;        //See notes2
	unsigned int	sh_flags;       //see notes3
	unsigned int	sh_addr;        //Section start address
	unsigned int	sh_offset;      //Offset from start of file to section
	unsigned int	sh_size;        //Size of section
	unsigned int	sh_link;        //Section header table index link
	unsigned int	sh_info;        //Info
	unsigned int	sh_addralign;   //Alignment. The adress of 0x0C must fit this alignment. 0=no alignment.
	unsigned int	sh_entsize;     //Fixed size entries.
} ELF_SHR;
/*
notes 2
-------
Type:
0=Inactive
1=PROGBITS
2=SYMTAB symbol table
3=STRTAB string table
4=RELA relocation entries
5=HASH hash table
6=DYNAMIC dynamic linking information
7=NOTE
8=NOBITS 
9=REL relocation entries
10=SHLIB
0x70000000=LOPROC processor specifc
0x7fffffff=HIPROC
0x80000000=LOUSER lower bound
0xffffffff=HIUSER upper bound

notes 3
-------
Section Flags:  (1 bit, you may combine them like 3 = alloc & write permission)
1=Write section contains data the is be writeable during execution.
2=Alloc section occupies memory during execution
4=Exec section contains executable instructions
0xf0000000=Mask bits processor-specific
*/

typedef struct {
	unsigned int	st_name;
	unsigned int	st_value;
	unsigned int	st_size;
	unsigned char	st_info;
	unsigned char	st_other;
	unsigned short int	st_shndx;
} Elf32_Sym;

#define ELF32_ST_TYPE(i) ((i)&0xf)

typedef struct {
	unsigned int	r_offset;
	unsigned int	r_info;
} Elf32_Rel;

//unfinished!!!!



extern char *sections_names;
	
extern ELF_HEADER elfHeader;	
extern ELF_PHR	*elfProgH;
extern ELF_SHR	*elfSectH;


int loadElfFile(char *filename);
int saveElfFile(char *filename);
void ClearHeaders();