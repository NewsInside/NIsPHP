/*  Modified by Jayteemaster for inclusion in ps2_pal2ntsc_yfix */

#include <afxwin.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "lzo1x.h"	// 170503, < >->" ", Jayteemaster

#include "tamtypes.h"
#include "loadelf.h"

extern CEdit *p_m_edit;
extern void SysPrintf(char *fmt, ...);


//#define DEBUG
#define DEPACK_ELF_START	0x1B00000
//#define DEPACK_ELF_START	0x0703690	// FOR PDX COMPATIBILITY
//#define DEPACK_ELF_START	0x0800000

int Compress(u8 *Input, u32 InSize, FILE *fo);

typedef struct {
	u32 CompressedSize;
	u32 OriginalSize;
	u32 VirtualAddr;
	u32 EntryAddr;
} SjCRUNCH_Header;

char SjCRUNCH_Inentifier[32] = "SjCRUNCH v0.3 - By Sjeep       ";

struct elf_file InputELF;

int get_checksum(const char* buffer, int size)
{
	unsigned int checksum = 0;
	int i;

	for(i=0;i<size;i++)
		checksum += (unsigned char)!buffer[i];

	return checksum;
}

unsigned char elf_ident[0x10] = { 0x7f, 0x45, 0x4c, 0x46, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

int pack(int argc, char *argv[])
{
	int i;
	unsigned int VirtualAddr, EntryAddr;
	unsigned int ImageSize = 0, ImageEnd = 0, ImageStart = 0xffffffff;
	unsigned int CompressedSize;
	float CompRatio;
	FILE *file;
	char *ImageBuffer;
	SjCRUNCH_Header Header;
	unsigned char temp_buff[16];


	SysPrintf("\r\n\r\nSjCRUNCH Packer v0.3 - By Sjeep\r\n\r\n");

	if(argc < 2) {
		SysPrintf("Usage: ./sjcrunch_pack INPUT.ELF\r\n\r\n");
		return(1);
	}

	// Check that input elf is a valid MIPS elf
	file = fopen(argv[1], "rb");	// 170503, r->rb, Jayteemaster
	if(!file) {
		SysPrintf("*** ERROR *** Failed to open input file!\r\n");
		return(1);
	}
	if(fread(temp_buff, 1, 16, file) != 16) {
		SysPrintf("*** ERROR *** Failed to read input file!\r\n");
		return 1;
	}
	fclose(file);

	if(memcmp(temp_buff, elf_ident, 16)) {
		SysPrintf("*** ERROR *** Input file is not a valid MIPS elf file!\r\n");
		return 1;
	}

	// Get elf info
	elf_load((unsigned char*)argv[1], &InputELF);

	//VirtualAddr = InputELF.program[0]->p_vaddr;
	EntryAddr = InputELF.hdr.e_entry;

	// Find virtual address (lowest virtual addr in program headers)
	VirtualAddr = 0xFFFFFFFF;
	for(i = 0; i < InputELF.hdr.e_phnum; i++)
		if((InputELF.program[i]->p_vaddr < VirtualAddr) && (InputELF.program[i]->p_filesz>0)) VirtualAddr = InputELF.program[i]->p_vaddr;

//#ifdef DEBUG
	SysPrintf("Virtual address: 0x%X\r\n",VirtualAddr);
	SysPrintf("Entry address: 0x%X\r\n",EntryAddr);
//#endif

	if(!InputELF.hdr.e_shnum) {
		//SysPrintf("*** ERROR *** Input elf does not contain any sections!\r\n");
		//return 1;
	// Find size of image
	for(i = 0; i < InputELF.hdr.e_phnum; i++) {
		if((!InputELF.program[i]->p_filesz && !InputELF.program[i]->p_memsz) || (InputELF.program[i]->p_type!=PT_LOAD)) continue;

  		if(InputELF.program[i]->p_vaddr < ImageStart) ImageStart = InputELF.program[i]->p_vaddr;
		if((InputELF.program[i]->p_vaddr+InputELF.program[i]->p_memsz) >= ImageEnd) ImageEnd = (InputELF.program[i]->p_vaddr+InputELF.program[i]->p_memsz);
	}
	}
	else {
	// Find size of image
	for(i = 0; i < InputELF.hdr.e_shnum; i++) {
		if(!(InputELF.section[i]->sh_flags & SHF_ALLOC)) continue;

		if ((InputELF.section[i]->sh_addr==0)||(InputELF.section[i]->sh_addr>0x20000000)) continue;

  		if((InputELF.section[i]->sh_addr < ImageStart)&&(InputELF.section[i]->sh_size>0)) ImageStart = InputELF.section[i]->sh_addr;
		if(((InputELF.section[i]->sh_addr+InputELF.section[i]->sh_size) >= ImageEnd)&&(InputELF.section[i]->sh_size>0)) ImageEnd = (InputELF.section[i]->sh_addr + InputELF.section[i]->sh_size);
	}
	//
	}
	ImageSize = (ImageEnd - VirtualAddr) - (ImageStart - VirtualAddr);

#ifdef DEBUG
	SysPrintf("Image size: 0x%X bytes\r\n\r\n", ImageSize);
	SysPrintf("Address  Offset   Size     Name\r\n");
#endif

	// Allocate buffers
	ImageBuffer = (char*)malloc(ImageSize);
	if(!ImageBuffer) {
		SysPrintf("Failed to allocate memory!\r\n");
		return(1);
	}
	memset(ImageBuffer, 0, ImageSize);	// 170503, Jayteemaster

	SysPrintf("Creating image...\r\n");
	if(!InputELF.hdr.e_shnum) {
		//SysPrintf("*** ERROR *** Input elf does not contain any sections!\r\n");
		//return 1;
	// Dump each needed section to buffer (only sections with ALLOC bit set)
	for(i = 0; i < InputELF.hdr.e_phnum; i++) {
		if((!InputELF.program[i]->p_filesz && !InputELF.program[i]->p_memsz) || (InputELF.program[i]->p_type!=PT_LOAD)) continue;

#ifdef DEBUG
		SysPrintf("%8.8lx %8.8lx %8.8lx %s\r\n",InputELF.section[i]->sh_addr, InputELF.section[i]->sh_offset, InputELF.section[i]->sh_size, InputELF.section[i]->name);
#endif


		// Check that section will not overwrite de-packer elf
		//if((InputELF.section[i]->sh_addr + InputELF.section[i]->sh_size) > DEPACK_ELF_START) {
		if((InputELF.program[i]->p_vaddr + InputELF.program[i]->p_memsz) > DEPACK_ELF_START) {	// 070603, Jayteemaster
			SysPrintf("*** ERROR *** program segment %d will overlap depacker elf when decompressed!\r\n",i);
			return(1);
		}

		// If section type == PROGBITS, copy data
		//if(InputELF.section[i]->sh_type & SHT_PROGBITS)
			memcpy(	ImageBuffer + InputELF.program[i]->p_vaddr - VirtualAddr,
					InputELF.program[i]->data,
					InputELF.program[i]->p_filesz );
	}
	}
	else {
	// Dump each needed section to buffer (only sections with ALLOC bit set)
	for(i = 0; i < InputELF.hdr.e_shnum; i++) {
		if(!(InputELF.section[i]->sh_flags & SHF_ALLOC)) continue;

#ifdef DEBUG
		SysPrintf("%8.8lx %8.8lx %8.8lx %s\r\n",InputELF.section[i]->sh_addr, InputELF.section[i]->sh_offset, InputELF.section[i]->sh_size, InputELF.section[i]->name);
#endif


		// Check that section will not overwrite de-packer elf
		//if((InputELF.section[i]->sh_addr + InputELF.section[i]->sh_size) > DEPACK_ELF_START) {
		if(((InputELF.section[i]->sh_addr + InputELF.section[i]->sh_size) > DEPACK_ELF_START) && (InputELF.section[i]->sh_size>0) && (InputELF.section[i]->sh_type!=SHT_NOBITS)) {	// 070603, Jayteemaster
			if ((InputELF.section[i]->sh_addr>=0x70000000)&&(InputELF.section[i]->sh_addr<0x70003fff))
			{
				SysPrintf("Please report this: ignoring Scratch Pad.\r\n");
				continue;
			}
			SysPrintf("*** ERROR *** \'%s\' section will overlap depacker elf when decompressed!\r\n",InputELF.section[i]->name);
			return(1);
		}

		// If section type == PROGBITS, copy data
		if(InputELF.section[i]->sh_type & SHT_PROGBITS)
			memcpy(	ImageBuffer + InputELF.section[i]->sh_addr - VirtualAddr,
					InputELF.section[i]->data,
					InputELF.section[i]->sh_size );

		// Else if section type = NOBITS, zero data
		else if(InputELF.section[i]->sh_type & SHT_NOBITS)
			memset(	ImageBuffer + InputELF.section[i]->sh_addr - VirtualAddr,
					0,
					InputELF.section[i]->sh_size );

		else SysPrintf("*** WARNING *** Dont know what to do with section type: %d\r\n",InputELF.section[i]->sh_type);

	}
	//
	}

#ifdef DEBUG
	SysPrintf("Checksum: 0x%X\r\n",get_checksum((char *)ImageBuffer, ImageSize));
#endif
	
	elf_free(&InputELF);
	/*
	{
		file=fopen("dump0.bin","wb");
		fwrite(ImageBuffer, 1, ImageSize, file);
		fclose(file);
	}
	*/

	// Open temp image file
	file = fopen("temp_image", "wb");	// 170503, w->wb, Jayteemaster
	if(!file) {
		SysPrintf("Failed to open temporary image file for writing\r\n");
		return(1);
	}

	// Compress
	SysPrintf("Compressing image...\r\n");
	fseek(file, sizeof(SjCRUNCH_Header), SEEK_SET);
	CompressedSize = Compress((unsigned char*)ImageBuffer, ImageSize, file);
	if (CompressedSize == -1)
		return(1);
	CompRatio = (float)CompressedSize / (float)ImageSize;
	CompRatio *= 100.0f;

#ifdef DEBUG
	SysPrintf("Done!\r\n\r\nByes in: %10d Bytes out: %10d\r\nCompression ratio: %f\r\n", ImageSize, CompressedSize, CompRatio);
#endif

	// Fill and write header
	Header.CompressedSize = CompressedSize;
	Header.OriginalSize = ImageSize;
	Header.VirtualAddr = VirtualAddr;
	Header.EntryAddr = EntryAddr;

	fseek(file, 0, SEEK_SET);
	fwrite(&Header, 1, sizeof(SjCRUNCH_Header), file);

	fclose(file);
	free(ImageBuffer);

	return 0;
}

#define BLOCK_SIZE		256*1024
// Fixed blocksize of 256kb, level 999 compression. File must be properly positioned before calling this func
int Compress(u8 *Input, u32 InSize, FILE *fo)
{
	int Return;
	u8 *In, *Out, *WrkMem;
	u32 InLen, OutLen;
	u32 TotalSize = 0;
	int i = 0;

	u32 InputPos = 0;

	// Init lib lzo
	if (lzo_init() != LZO_E_OK)
	{
		SysPrintf("*** ERROR *** lzo_init() failed !!!\r\n");
		return(-1);
	}

	// Write identifier
	fwrite(SjCRUNCH_Inentifier, 1, 32, fo);

	// Allocate compression buffers and work memory
	In = (unsigned char*)malloc(BLOCK_SIZE);
	Out = (unsigned char*)malloc(BLOCK_SIZE + BLOCK_SIZE / 64 + 16 + 3);
	WrkMem = (unsigned char*)malloc(LZO1X_999_MEM_COMPRESS);

	if (In == NULL || Out == NULL || WrkMem == NULL)
	{
		SysPrintf("*** ERROR *** Out of memory\r\n");
		return(-1);
	}

	// Process blocks
	for(;;)
	{
/*
		InLen = fread(In, 1, BLOCK_SIZE, fi);
		if(InLen <= 0) break; // EOF
*/
		if((InSize - InputPos) >= BLOCK_SIZE)
		{

			memcpy(In, Input + InputPos, BLOCK_SIZE);
			InputPos += BLOCK_SIZE;
			InLen = BLOCK_SIZE;

		} else {

			u32 Amount;

			Amount = InSize - InputPos;

			if(Amount <= 0) break; // End of data

			memcpy(In, Input + InputPos, Amount);
			InputPos += Amount;
			InLen = Amount;

		}

		// Compress block
		Return = lzo1x_999_compress(In, InLen, Out, &OutLen, WrkMem);

		if (Return != LZO_E_OK || OutLen > InLen + InLen / 64 + 16 + 3)
		{
			/* this should NEVER happen */
			SysPrintf("*** ERROR *** Internal error - compression failed: %d\r\n", Return);
			return(-1);
		}

		// Write uncompressed block size
		fwrite(&InLen, 1, 4, fo);

		// Write compressed block size, then compressed block
		if(OutLen < InLen) {

			fwrite(&OutLen, 1, 4, fo);
			fwrite(Out, 1, OutLen, fo);
			TotalSize += OutLen;

		} else { // uncompressed block

			fwrite(&InLen, 1, 4, fo);
			fwrite(In, 1, InLen, fo);
			TotalSize += InLen;

		}

	}

	// Write EOF marker
	Return = 0;
	fwrite(&Return, 1, 4, fo);

	free(In);
	free(Out);
	free(WrkMem);

	return TotalSize;

}
