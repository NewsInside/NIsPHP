/*  ps2_pal2ntsc_yfix - PS2 PAL TO NTSC VIDEO MODE CHANGER WITH Y-FIX
 *  Copyright (C) 2003-2004  Jayteemaster <jayteemaster2003@yahoo.com.br>
 *  URL: www.geocities.com/jayteemaster2003
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

#include <afxwin.h>


unsigned int pn_sel1_header[18092] = {	//17868
	#include "pn_sel1.inc"
};

unsigned int pn_sel1_tail[116] = {
	#include "pn_sel2.inc"
};

extern CEdit *p_m_edit;
extern void SysPrintf(char *fmt, ...);
extern int pack(int argc, char *argv[]);
extern unsigned int original_filesize;
extern unsigned char buf_2[4*1024];
// vdata
extern unsigned int u_vmode[4];
extern int u_posv;
extern unsigned int u_yfix[16*3];
extern int n2fix;
// syscall
#ifdef PS2LOADV7
unsigned int u_syscall[2], u_posys;
#endif

static unsigned int PN_SEL1_HSIZE=18092;//17868
static unsigned int sel1_vmode_ofs=17128;//16904
static unsigned int sel1_yfix_ofs=17128+4;//16904+4
#ifdef PS2LOADV7
static unsigned int sel1_syscall_ofs=16928;
#endif
static unsigned int msg_ofs=17180;//16956
static char msg[481],encmsg[481];

int make_pn_selector1(char *filename)
{
	unsigned int *p1;
	unsigned int temp, adr, temp2;
	//
	FILE *file;
	char *ImageBuffer;
	unsigned int CompressedImageSize;
	char *argv[2];
	int ret;
	unsigned int conta;
	//
	int i;


	// Dump ELF and compress image
	argv[1] = filename;
	ret=pack(2, argv);
	if (ret)
	{
		SysPrintf("Failed to compress image!\r\n");
		return(1);
	}

	SysPrintf("Making selector...\r\n");
	// read compressed image
	// Read temp image back in
	file = fopen("temp_image", "rb");	// 170503, r->rb, Jayteemaster
	if(!file) {
		SysPrintf("Failed to open temporary image file for reading\r\n");
		return(1);
	}

	fseek(file, 0, SEEK_END);
	CompressedImageSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	while(CompressedImageSize % 4) CompressedImageSize++;

	// stack size = 4096 (4K) bytes
	// stack (sp) starts 256 bytes below
	// reginfo uses 24 bytes
	// selector code uses  540660-285668 bytes
	if ((254992+CompressedImageSize+24+4096+256)>(5*1024*1024))
	{
		SysPrintf("Image is too big!\r\n");
		fclose(file);
		return(1);
	}

	ImageBuffer = (char*)malloc(CompressedImageSize);
	if(!ImageBuffer) {
		SysPrintf("Failed to allocate memory!\r\n");
		fclose(file);
		return(1);
	}

	memset(ImageBuffer, 0, CompressedImageSize);
	fread(ImageBuffer, 1, CompressedImageSize, file);
	fclose(file);
	remove("temp_image");
	//////////

	// Create selector elf
	file = fopen(filename, "wb");
	if(!file) {
		SysPrintf("Failed to open output file: %s\r\n", filename);
		return(1);
	}


	p1=(unsigned int*)malloc(sizeof(unsigned int)*PN_SEL1_HSIZE);
	if (p1==NULL)
	{
		SysPrintf("Failed to allocate memory!\r\n");
		return(1);
	}
	memcpy(p1, pn_sel1_header, sizeof(unsigned int)*PN_SEL1_HSIZE);

	// section headers offset
	temp=PN_SEL1_HSIZE*4+CompressedImageSize;
	temp += 4+100;
	memcpy(p1+8, &temp, 4);
	// program header 2: bytes in segment file image
	temp=CompressedImageSize;
	temp += 3888+4;
	memcpy(p1+25, &temp, 4);
	// program header 2: bytes in segment memory image
	memcpy(p1+26, &temp, 4);

	// p.3
	adr=CompressedImageSize;
	adr += 0x01b53ab0; //0x01b53730   PackedElf
	temp2 = adr>>16;
	memcpy(p1+13915, &temp2, 2);
	temp2 = adr&0xFFFF;
	memcpy(p1+13915+3, &temp2, 2);
	memcpy(p1+13915+7, &temp2, 2);
	memcpy(p1+13915+11, &temp2, 2);
	memcpy(p1+13915+12, &temp2, 2);

	// patch
#if 1
	memcpy(p1+sel1_vmode_ofs, u_vmode, u_posv*sizeof(unsigned int));
	memcpy(p1+sel1_yfix_ofs, u_yfix, n2fix*3*sizeof(unsigned int));
	p1[1338]=0x34840003;
#ifdef PS2LOADV7
	memcpy(p1+sel1_syscall_ofs, u_syscall, u_posys*sizeof(unsigned int));
#endif
#endif
	// encrypt text
#if 1
	memcpy(msg, p1+msg_ofs, 481);
	//
	memcpy(&msg[402], "CROSS  for NTSC Y-FIX",21);
	memcpy(&msg[436], "CIRCLE for NTSC", 15);
	memcpy(&msg[464], "SQUARE for PAL  ", 16);
	//
	encmsg[0]=msg[0];
	for (i=1;i<481;i++)
		encmsg[i]=msg[i]^msg[i-1]^0x92;
	memcpy(p1+msg_ofs, encmsg, 481);
#endif

	fwrite(p1, 4, PN_SEL1_HSIZE, file);
	fwrite(ImageBuffer, 1, CompressedImageSize, file);
	free(ImageBuffer);


	memcpy(p1, pn_sel1_tail, sizeof(unsigned int)*116);
	// section header 7: size
	memcpy(p1+91, &temp, 4);
	// section header 8: offset in file
	temp=PN_SEL1_HSIZE*4+CompressedImageSize;
	temp+=4;
	memcpy(p1+100, &temp, 4);
	// section header 9: offset in file
	temp+=24;
	memcpy(p1+110, &temp, 4);
	temp-=24;
	// section header 8: start address
	temp=CompressedImageSize;
	temp += 4;
	//temp += 0x01B538B0;
	temp += 0x01b53ab0;//0x01b53730
	memcpy(p1+99, &temp, 4);

	fwrite(p1, 4, 116, file);
#if 1
	conta = (PN_SEL1_HSIZE+116)*4+CompressedImageSize;
	memset(buf_2, 0, 4*1024);
	while (conta<original_filesize)
	{
		if ((conta+4*1024)<original_filesize)
		{
			fwrite(buf_2, 1, 4*1024, file);
			conta += 4*1024;
		}
		else
		{
			fwrite(buf_2, 1, original_filesize-conta, file);
			conta = original_filesize;
		}
	}
#endif
	fclose(file);
	free(p1);
	SysPrintf("\r\nAll done.\r\n");

	return 0;
}
