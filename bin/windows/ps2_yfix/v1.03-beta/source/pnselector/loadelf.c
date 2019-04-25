/*  Modified by Jayteemaster for inclusion in ps2_pal2ntsc_yfix */

/*      
  _____     ___ ____ 
   ____|   |    ____|      PSX2 OpenSource Project
  |     ___|   |____       (C)2001, Gustavo Scotti (gustavo@scotti.com)
  ------------------------------------------------------------------------
  loadelf.c
			ELF FILE Manipulation
                        Simple ELF file manipulation based on elf.pdf
*/

#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "tamtypes.h"
#include "loadelf.h"

int elf_load( u8 *name, struct elf_file *elf)
{
   int				fd, i, j, n;
   struct elf_section_header	*section;
   
   bzero( elf, sizeof( *elf));
   fd = open( name, _O_RDONLY|_O_BINARY);
   if (fd < 0)
      return -1;
   
   if (read( fd, &elf->hdr, sizeof(elf->hdr)) < 0)
      return -2;
      
   /* allocate program memory */
   if (elf->hdr.e_phnum)
      {
      elf->program = malloc( elf->hdr.e_phnum * sizeof( *elf->program));
      for (i = 0; i < elf->hdr.e_phnum; i++)
         {
         struct elf_prog_header		*program;
         /* position it to its section position */
         lseek( fd, elf->hdr.e_phoff + (i * elf->hdr.e_phentsize), 0);
      
         /* load each program entry */
         elf->program[i] = program = malloc( sizeof( *program));
         bzero( program, sizeof( *program));
         read( fd, program, elf->hdr.e_phentsize);
		 if (!elf->hdr.e_shnum)
			{
			lseek( fd, program->p_offset, 0);
			program->data = (u8 *)malloc( program->p_filesz);
			read( fd, program->data, program->p_filesz);
			}
		 else program->data=0;
         }
      }
   /* allocate section memory -- 128 pre-select section */
   //elf->section = malloc( 128 * sizeof( *elf->section));
   elf->section = malloc( elf->hdr.e_shnum * sizeof( *elf->section));
   for (i = 0; i < elf->hdr.e_shnum; i++)
      {
      struct elf_section_header		*section;
      
      /* position it to its section position */
      lseek( fd, elf->hdr.e_shoff + (i * elf->hdr.e_shentsize), 0);
      
      /* load each session entry */
      elf->section[i] = section = malloc( sizeof( *section));
      bzero( section, sizeof( *section));
      read( fd, section, elf->hdr.e_shentsize);
      if (section->sh_type != SHT_NOBITS)
         {
         lseek( fd, section->sh_offset, 0);
         section->data = (u8 *)malloc( section->sh_size);
         read( fd, section->data, section->sh_size);
         }
      }
   close(fd);


   /* FIXUP section names */
   elf->strtable = elf->section[ elf->hdr.e_shstrndx];
   for (i = 0; i < elf->hdr.e_shnum; i++)
      {
      
      section = elf->section[i];
      if (!section)
         continue;
         
      section->name = strdup( &elf->strtable->data[ section->sh_name]);
      if (section->sh_link)
         section->link = elf->section[ section->sh_link];
      if (section->sh_info)
         section->info = elf->section[ section->sh_info];
         
      switch (section->sh_type)
         {
         case	SHT_REL:	/* relocations */
            			{
                                struct elf_relocation	*relocation;

                                n = section->sh_size / SIZE_REL;
                                section->relocation_table = (struct elf_relocation **)
                                   		malloc( n * sizeof( struct elf_relocation *));
                                section->relocation_count = n;
                                for (j = 0; j < n; j++)
                                   section->relocation_table[ j] = (struct elf_relocation *)
                                      		&section->data[ j * SIZE_REL];
                                }
                break;
         case	SHT_DYNSYM:
         case	SHT_SYMTAB:	/* symbols */
            			{
                                struct elf_symbol	*symbol;
                                   

                                n = section->sh_size / SIZE_SYMBOL;
                                section->symbol_table = (struct elf_symbol **)
                                   		malloc( n * sizeof( struct elf_symbol *));
                                section->symbol_count = n;
                                for (j = 0; j < n; j++)
                                   section->symbol_table[ j] = (struct elf_symbol *)
                                      		&section->data[ j * SIZE_SYMBOL];
                                }
                break;
                                
                                
         }
      }

   return 0;
}

void elf_free(struct elf_file *elf)
{
	int i, j, k;

	for(i = 0; i < elf->hdr.e_phnum; i++)
	{
		if (elf->program[i]->data!=0)
			free(elf->program[i]->data);
		free(elf->program[i]);
	}
	free(elf->program);

	for(i = 0; i < elf->hdr.e_shnum; i++)
	{
		free(elf->section[i]->data);
		free(elf->section[i]->relocation_table);
		free(elf->section[i]->symbol_table);
	}
	free(elf->section);
}

struct elf_section_header *elf_newsection( int type, u8 *name)
{
   struct elf_section_header	*section;
   
   section = malloc( sizeof (*section));
   bzero( section, sizeof(*section));
   section->sh_type = type;
   section->name = name;

   return(section);
}

void
elf_deletesection( struct elf_section_header *section)
{

   if (section->name)
      free(section->name);
      
   if (section->data)
      free(section->data);
      
   if (section->symbol_table)
      free(section->symbol_table);

   if (section->relocation_table)
      free(section->relocation_table);
      
   free(section);
}


struct elf_symbol
*elf_findsymbol( struct elf_file *elf, u8 *symbol_name)
{
   int				i;
   struct elf_section_header	*sh_symbol, *sh_strsymbol;
   struct elf_symbol		*symbol;
   
   for (i = 1; i < elf->hdr.e_shnum; i++)
   if  (elf->section[i] && elf->section[i]->sh_type == SHT_SYMTAB)
      {
      sh_symbol = elf->section[i];
      sh_strsymbol = sh_symbol->link;
      }
   /* now, find out symbol name */
   for (i = 0; i < sh_symbol->symbol_count; i++)
      {
      u8			*name;
      symbol = sh_symbol->symbol_table[i];

      if (symbol)
         {
         switch(symbol->st_type)
            {
            case STT_SECTION:
            		  name = elf->section[ symbol->st_shndx]->name;
                          break;
            case STT_NOTYPE:
            case STT_OBJECT:
            case STT_FUNC:
            		  name = SECTION_STR( sh_strsymbol, symbol->st_name);
                          break;
            default:	  name = "";
            }
         if (*name && !strcmp(name, symbol_name))
            return symbol;
         }
      }
   return NULL;
}

u8 	*elf_getsymbol_byaddr( struct elf_file *elf, u32 addr)
{
   int				i, sec, oo, st;
   struct elf_section_header	*sh_symbol, *sh_strsymbol;
   struct elf_symbol		*symbol;
   int				order[] ={ SHT_DYNSYM, SHT_SYMTAB, 0};
   int				s_order[] = { STT_FUNC, STT_OBJECT, STT_SECTION, STT_NOTYPE, -1 };


   for (st=0; s_order[st] >=0; st++)
   for (oo=0; order[oo]; oo++)
   for (sec = 1; sec < elf->hdr.e_shnum; sec++) {
      if  (elf->section[sec] && 
         	(elf->section[sec]->sh_type == order[oo]) ) {
      
                sh_symbol = elf->section[sec];
                sh_strsymbol = sh_symbol->link;
      } else
      continue;
      
      if (sec == elf->hdr.e_shnum)
         return NULL;
      /* now, find out symbol name */
      for (i = 0; i < sh_symbol->symbol_count; i++)
         {
         u8			*name;
         u32			d_addr;
         symbol = sh_symbol->symbol_table[i];

         name = NULL;

         if (symbol->st_addr == addr && symbol->st_type == s_order[st]) 
            {
            switch(symbol->st_type)
               {
               case STT_SECTION:
            		  name = elf->section[ symbol->st_shndx]->name; 
                          break;
               case STT_NOTYPE:
               case STT_OBJECT:
               case STT_FUNC:
            		  name = SECTION_STR( sh_strsymbol, symbol->st_name);
                          break;
               default:	  name = "";
               }
            return name;
            }
         }
   }
   return NULL;
}

int
elf_setsymbol_addr( struct elf_file *elf, u8 *symbol_name, u32 addr)
{
   struct elf_symbol	*symbol;

   symbol = elf_findsymbol( elf, symbol_name);
   if (!symbol)
      return -1;
   symbol->st_addr = addr;
   return 0;
}

u32
elf_getsymbol_addr( struct elf_file *elf, u8 *symbol_name)
{
   struct elf_symbol	*symbol;

   symbol = elf_findsymbol( elf, symbol_name);
   if (!symbol)
      return 0;
   else
      return symbol->st_addr;
}

u8
*elf_getsymbol_name( struct elf_file *elf, 
   	struct elf_section_header *symtab, int pos)
{
   struct elf_section_header	*sym_str;
   struct elf_symbol		**syms, *symbol;
   int				s_count, n;
   u8				*name;
   
   /* get syms */
   syms    = symtab->symbol_table;
   s_count = symtab->symbol_count;
   sym_str = symtab->link;
   
   if (pos > s_count)
      return (u8 *)"";

   symbol = syms[ pos];
   switch (symbol->st_type)
            {
            case STT_SECTION:
            		  name = elf->section[ symbol->st_shndx]->name;
                          break;
            case STT_NOTYPE:
            case STT_OBJECT:
            case STT_FUNC:
            		  name = SECTION_STR( sym_str, symbol->st_name);
                          break;
            default:	  name = "";
            }
   return name;
}



int elf_save( struct elf_file *elf, u8 *name)
{
   u8				align[64], *str_tbl;
   int				fd, i, n, offset;
   struct elf_section_header	*section;
   struct elf_prog_header	*program;

   bzero( align, sizeof(align));
   fd = open( name, O_CREAT | O_TRUNC | O_WRONLY, _S_IWRITE/*S_IRWXU*/);
   if (fd < 0)
      return -1;
   offset = 0;
   
   /* REMOUNT STRING TABLE */

   section = elf->strtable;
   if (section)
      {
      if (section->data)
         free(section->data);
      }
   else
      {
      section = elf_newsection( SHT_STRTAB, ".shstrtab");
      elf->section[ elf->hdr.e_shnum++] = section;
      elf->strtable = section;
      }

   for (i = n = 0; i < elf->hdr.e_shnum; i++)
       {
       if (!elf->section[i])
          continue;
       elf->section[i]->sh_name = n; 
       n++;
       if (elf->section[i]->name)
          n += strlen(elf->section[i]->name);
       }
       
      
   str_tbl = section->data = malloc(n);
   section->sh_size = n;
   section->sh_addralign = 16;
   for (i = n = 0; i < elf->hdr.e_shnum; i++)
       {
       if (!elf->section[i])
          continue;
          
       if (elf->section[i]->name)
          {
          strcpy( str_tbl, elf->section[i]->name);
          str_tbl += (1 + strlen( elf->section[i]->name));
          }
       else
          {
          *str_tbl = 0; str_tbl++;
          }
       }
   
   offset += write(fd, &elf->hdr, sizeof(elf->hdr));

   if (elf->hdr.e_phnum)
      elf->hdr.e_phoff = offset;
      
   for (i = 0; i < elf->hdr.e_phnum; i++)
      {
      program = elf->program[i];
      if (!program)
         continue;
      offset += write( fd, program, elf->hdr.e_phentsize);
      }

   for (i = 1; i < elf->hdr.e_shnum; i++)
      {
      section = elf->section[i];
      if (!section)
         continue;
      if (section->sh_type == SHT_PROGBITS ||
          section->sh_type == SHT_NOBITS ||
          (section->sh_type >= SHT_LOPROC && section->sh_type <= SHT_HIPROC) ||
          i == elf->hdr.e_shstrndx)
         {
         n = (section->sh_size % section->sh_addralign);
         section->sh_offset = offset;
         if (section->sh_type != SHT_NOBITS)
            {
            offset += write( fd, section->data, section->sh_size);
            if (n)
               offset += write( fd, align, section->sh_addralign - n);
            }
         }
      }

   /* save sections */

   elf->hdr.e_shoff = offset;
   for (i = 0; i < elf->hdr.e_shnum; i++)
      {
      section = elf->section[i];
      if (!section)
         continue;
      offset += write( fd, elf->section[i], elf->hdr.e_shentsize);
      }
   for (i = 1; i < elf->hdr.e_shnum; i++)
      {
      section = elf->section[i];
      if (!section)
         continue;
      if (
          section->sh_type != SHT_PROGBITS &&
          section->sh_type != SHT_NOBITS &&
          (section->sh_type < SHT_LOPROC || section->sh_type > SHT_HIPROC) &&
          i != elf->hdr.e_shstrndx)
         {
         n = (section->sh_size % section->sh_addralign);
         section->sh_offset = offset;
         if (section->sh_type != SHT_NOBITS)
            {
            if (section->data)
               {
               offset += write( fd, section->data, section->sh_size);
               if (n)
                  offset += write( fd, align, section->sh_addralign - n);
               }
            }
         }
      }
   /* save sections */

   lseek( fd, elf->hdr.e_shoff, 0);
   for (i = 0; i < elf->hdr.e_shnum; i++)
      {
      section = elf->section[i];
      if (!section)
         continue;
      offset += write( fd, elf->section[i], elf->hdr.e_shentsize);
      }
   lseek( fd, 0, 0);
   write(fd, &elf->hdr, sizeof(elf->hdr));

   close(fd);
   return 0;
}


