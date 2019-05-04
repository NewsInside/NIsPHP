/*  Modified by Jayteemaster for inclusion in ps2_pal2ntsc_yfix */

/*
  _____     ___ ____ 
   ____|   |    ____|      PSX2 OpenSource Project
  |     ___|   |____       (C)2001, Gustavo Scotti (gustavo@scotti.com)
  ------------------------------------------------------------------------
  loadelf.h
			ELF FILE Manipulation prototypes
*/

#ifndef _LOADELF_H
#define _LOADELF_H

#include "tamtypes.h"

/* ELF HEADER */
struct elf_header
{
   u8				e_ident[ 16];
   u16				e_type,
      				e_machine;
   u32	                        e_version;
   u32				e_entry;
   u32				e_phoff,
      				e_shoff;
   u32	                        e_flags;
   u16				e_ehsize,
      				e_phentsize,
                                e_phnum,
                                e_shentsize,
                                e_shnum,
                                e_shstrndx;
};

/* e_type PROTOTYPES */
#define ET_NONE			0
#define ET_REL			1
#define ET_EXEC			2
#define ET_DYN			3
#define ET_CORE			4
#define ET_LOPROC		0xff00
#define ET_HIPROC		0xffff

/* e_machine PROTOTYPES */
#define EM_NONE			0
#define EM_M32			1
#define EM_SPARC		2
#define EM_386			3
#define EM_68K			4
#define EM_88K			5
#define EM_860			7
#define EM_MIPS			8

/* e_ident INDEXES */
#define EI_MAG0			0
#define EI_MAG1			1
#define EI_MAG2			2
#define EI_MAG3			3
#define EI_CLASS		4
#define EI_DATA 		4
#define EI_VERSION		4
#define EI_PAD			4

/* EI_CLASS */
#define ELFCLASSNONE		0
#define ELFCLASS32		1
#define ELFCLASS64		2

/* EI_DATA */
#define ELFDATANONE		0
#define ELFDATA2LSB		1
#define ELFDATA2MSB		2


/* SYMBOL TABLE HEADER */
struct elf_symbol
{
   u32				st_name,
				st_addr,
				st_size;
   u8                           st_type:4,
      				st_bind:4;
   u8				st_other;
   u16				st_shndx; 
};

#define SIZE_SYMBOL		16
/*
#define ST_BIND(b)		((b) >> 4)
#define ST_TYPE(t)		(t  &  15)
#define ST_INFO(b,t)		( (b << 4) | ( t & 15) ) */

#define STB_LOCAL		0
#define STB_GLOBAL		1
#define STB_WEAK		2
#define STB_LOPROC		13
#define STB_HIPROC		15

#define STT_NOTYPE		0
#define STT_OBJECT		1
#define STT_FUNC		2
#define STT_SECTION		3
#define STT_FILE		4
#define STT_LOPROC		13
#define STT_HIPROC		15

/* SIMPLE RELOCATION HEADER */
struct elf_relocation
{
   u32				r_offset;
   u32 				r_type:8,
      				r_sym:24;
   u32				r_addend;
};

#define	SIZE_REL		8
#define	SIZE_RELA		12
#define R_SYM(i)		( i >> 8 )
#define R_TYPE(i)		( i & 0xff )
#define R_INFO(s,t)		( (s << 8) | (t & 0xff))

#define R_MIPS_32		2
#define R_MIPS_26		4
#define R_MIPS_HI16		5
#define R_MIPS_LO16		6

/* SECTION HEADER */
struct elf_section_header
{
   /* ELF STANDARDS */
   u32				sh_name,
      				sh_type,
                                sh_flags,
                                sh_addr,
                                sh_offset,
                                sh_size,
                                sh_link,
                                sh_info,
                                sh_addralign,
                                sh_entsize;
   /* added to easy my life */
   u8				*data;
   u8				*name;
   struct elf_section_header	*link, *info;
   
   struct elf_relocation	**relocation_table;
   int				relocation_count;

   struct elf_symbol		**symbol_table;
   int				symbol_count;

};

#define SECTION_STR( section, value) \
     (value > section->sh_size || !section->data) ? (u8 *)"" : \
     &section->data[value]

/* sh_type */
#define SHT_NULL		0
#define SHT_PROGBITS		1
#define SHT_SYMTAB		2
#define SHT_STRTAB		3
#define SHT_RELA		4
#define SHT_HASH		5
#define SHT_DYNAMIC		6
#define SHT_NOTE		7
#define SHT_NOBITS		8
#define SHT_REL			9
#define SHT_SHLIB		10
#define SHT_DYNSYM		11
#define SHT_LOPROC		0x70000000
#define SHT_HIPROC		0x7fffffff
#define SHT_LOUSER		0x80000000
#define SHT_HIUSER		0xffffffff

/* sh_flags */
#define SHF_WRITE		1
#define SHF_ALLOC		2
#define SHF_EXECINSTR		4
#define SHF_MASKPROC		0xf0000000

/* SEG TYPES */
#define PROGRAM_SIZE		32
#define	PT_NULL			0
#define PT_LOAD			1
#define PT_DYNAMIC		2
#define PT_INTERP		3
#define PT_NOTE			4
#define PT_SHLIB		5
#define PT_PHDR			6
#define PT_LOPROC		0x70000000
#define PT_HIPROC		0x7fffffff

#define PF_R			4
#define PF_W			2
#define PF_X			1

struct elf_prog_header
{
   u32				p_type;
   u32				p_offset;
   u32				p_vaddr;
   u32				p_paddr;
   u32				p_filesz;
   u32				p_memsz;
   u32				p_flags;
   u32				p_align;
   /* added to easy my life */
   u8				*data;
};

struct elf_file
{
   u8				*elfname;
   struct elf_header		hdr;
   struct elf_section_header	**section, *strtable;
   struct elf_prog_header	**program;
};


/* PROTOTYPES */
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
int 	elf_load(u8 *name, struct elf_file *elf);
struct elf_section_header *elf_newsection( int type, u8 *name);
void 	elf_deletesection( struct elf_section_header *);
struct elf_symbol *elf_findsymbol( struct elf_file *elf, u8 *symbol_name);
int	elf_setsymbol_addr( struct elf_file *elf, u8 *symbol_name, u32 addr);
u32	elf_getsymbol_addr( struct elf_file *elf, u8 *symbol_name);
u8	*elf_getsymbol_name( struct elf_file *elf, struct elf_section_header *symtab, int pos);
int 	elf_save( struct elf_file *elf, u8 *name);
void elf_free(struct elf_file *elf);
#ifdef __cplusplus
}
#endif // __cplusplus


#endif
