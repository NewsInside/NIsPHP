
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <memory.h>
#include <stdarg.h>
#include "regs.h"
#include "Elfheader.h"

#ifdef GUI
CEdit *p_m_edit;
void SysPrintf(char *fmt, ...) {
	va_list list;
	char msg[512];

	va_start(list,fmt);
	vsprintf(msg,fmt,list);
	va_end(list);

	if (msg[strlen(msg)] == '\n')
	{
		int len = strlen(msg);
		msg[len] = '\r';
		msg[len+1] = '\n';
	}

	p_m_edit->ReplaceSel(msg);
}
#else
void SysPrintf(char *fmt, ...) {
	va_list list;
	char msg[512];

	va_start(list,fmt);
	vsprintf(msg,fmt,list);
	va_end(list);

	if (msg[strlen(msg)] == '\n')
	{
		int len = strlen(msg);
		msg[len] = '\r';
		msg[len+1] = '\n';
	}

	printf(msg);
}
#endif


unsigned int next2power(unsigned int n);
unsigned int calledby(FILE *fid, unsigned int offset);

unsigned int fcalls[12][2];


typedef struct {
	unsigned int offset;
	unsigned int address;

	unsigned int saved_reg;	//reg1
	unsigned int base_reg;

	unsigned int instr[2];
	unsigned int spare_reg;	//reg2

	int can_use_jr;

	int has2return;
} FIX_RECORD;

FIX_RECORD Y_fixes[12];
int n2fix=0;


unsigned int sub1[16] =		// without spare_reg and can not use jr ra
//daddiu saved_reg,saved_reg,xxxx; ...; daddiu saved_reg,saved_reg,0000; instr[0]; j address+8; nop
{0x64007000,0x64007000,0x64007000,0x64007000,0x64007000,0x64007000,0x64006000,0x64000000,0x00000000,0x08000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000};
unsigned int sub2[16] =		// without spare_reg and can use jr ra
//daddiu saved_reg,saved_reg,xxxx; ...; daddiu saved_reg,saved_reg,0000; instr[0]; jr ra; nop
{0x64007000,0x64007000,0x64007000,0x64007000,0x64007000,0x64007000,0x64006000,0x64000000,0x00000000,0x03E00008,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000};

unsigned int sub3[8] =		// with spare_reg and can not use jr ra
//lui reg2,3; daddu reg1,reg1,reg2; daddiu reg1,reg1,0; instr[0]; instr[1]; j address+8; nop
{0x3C000003, 0x0000002D, 0x64000000, 0x00000000, 0x00000000, 0x08000000, 0x00000000, 0x00000000};
unsigned int sub4[8] =		// with spare_reg and can use jr ra
//lui reg2,3; daddu reg1,reg1,reg2; daddiu reg1,reg1,0; instr[0]; instr[1]; jr ra; nop
{0x3C000003, 0x0000002D, 0x64000000, 0x00000000, 0x00000000, 0x03E00008, 0x00000000, 0x00000000};


unsigned int set_v2NTSC[4] = {0x24030002,0x0000000C,0x03E00008,0x00000000};
unsigned int set_v2PAL[4] =  {0x34050003,0x24030002,0x0000000C,0x03E00008};


unsigned int SIGNATURE = 0x5459414A;


unsigned int buf[1024], nextval;


void main(int argc, char *argv[])
{
	FILE *fid;
	unsigned int offset, count, i;
	unsigned int reg_values[32], reg, reg2, spare_reg, value;
	int enable_jr = 0, enable_sd = 0;
	int posfnd = 0;
	int have2reset=0;

	int sm1=0, sm2=0;
	unsigned int vmN[10], vmP[10], nN=0, nP=0;

	unsigned int space_av, space_nd, use_short_sub=0;

	unsigned int Sub[16];

	int phnum=-1;
	int shnum=-1;
	unsigned int wbytes=0;

	unsigned int p_align;

	unsigned int num2read, addr1;
	int found;
	int FvF=-1;

	char keycode; int user_option_1;

	printf("PS2 NTSC TO PAL VIDEO MODE CHANGER WITH Y-FIX\n");
	printf("V1.04 - 31 May, 2003\n");
	printf("By Jaytee\n");
	printf("\n");
	printf("Please report any bugs or suggestions to jayteemaster2003@yahoo.com.br\n");
	printf("Also, I would appreciate if you send me some fast FTPs with PS2 rips.\n");
	printf("\n");

	if (argc<2)
	{
		printf("Usage: ps2_ntsc2pal_yfix <elf file>\n");
		exit(0);
	}
	
	loadElfFile(argv[1]);


	fid = fopen(argv[1], "rb");
	if (fid==NULL)
	{
		printf("File %s not found.\n", argv[1]);
		exit(1);
	}

	offset = 0;
	while (!feof(fid))
	{
		count = fread(buf, 4, 1024, fid);
		for (i=0;i<count;i++)
		{
			// search for SetGsCrt
			if (buf[i] ==  set_v2NTSC[sm1])
			{
				sm1++;
				if (sm1 == 4)
				{
					sm1 = 0;
					vmN[nN++] = (offset+i-3)*4;
				}
			}
			else
				sm1=0;
			if (buf[i] ==  set_v2PAL[sm2])
			{
				sm2++;
				if (sm2 == 4)
				{
					sm2 = 0;
					vmP[nP++] = (offset+i-3)*4;
				}
			}
			else
				sm2=0;
			// search lui reg,$1200
			if ((buf[i]&0xFFE0FFFF) ==  0x3C001200)
			{
				reg = (buf[i]>>16) & 31;
				reg_values[reg] = 0x12000000;
				//printf("lui %d,12000 at offset %d\n", reg, offset+i);
				//getchar();
			}
			// search ori reg,reg2,$0080
			// search ori reg,reg2,$00A0
			if (((buf[i]&0xFC00FFFF) ==  0x34000080) || ((buf[i]&0xFC00FFFF) ==  0x340000A0) )
			{
				reg = (buf[i]>>16) & 31;
				reg2 = (buf[i]>>21) & 31;
				value = buf[i] & 0xFFFF;
				reg_values[reg] = reg_values[reg2] | value;
				if ((reg_values[reg] == 0x12000080) || (reg_values[reg] == 0x120000A0))
				{
					//printf("Found Y fix at offset %x\n", offset+i);
					enable_sd = 1;
				}
			}
			// search sd reg2, $0000(reg)
			// search sd reg2, $xxxx(reg)	***** NEW *******
			//if ((enable_sd) & ((buf[i]&0xFC00FFFF) == 0xFC000000))
			if ((buf[i]>>26)==0x3F)
			{
				unsigned int ofs;

				reg = (buf[i]>>21) & 31;
				reg2 = (buf[i]>>16) & 31;
				ofs = buf[i] & 0xFFFF;
				if (((reg_values[reg]+ofs) == 0x12000080) || ((reg_values[reg]+ofs) == 0x120000A0))
				{
					//printf("Found Y fix at offset %x\n", offset+i);
					Y_fixes[n2fix].address = 0x00000000; // ?
					Y_fixes[n2fix].base_reg = reg;
					Y_fixes[n2fix].can_use_jr = 0;
					Y_fixes[n2fix].instr[0] = buf[i];
					Y_fixes[n2fix].offset = (offset+i)*4;
					Y_fixes[n2fix].saved_reg = reg2;
					Y_fixes[n2fix].spare_reg = 0;
					Y_fixes[n2fix].has2return = 0;
					if (have2reset==1)
						Y_fixes[n2fix].has2return = 1;
					// check if follows a ld reg, $xxxx(reg2)
					if ((i+1)==count)
					{
						fread(&nextval, 4, 1, fid);
						fseek(fid, -4, SEEK_CUR);
					}
					else
						nextval = buf[i+1];
					if (Y_fixes[n2fix].has2return ==0)
					// ALTERAR AQUI PARA MAIS INSTRUCOES DE LOAD
					if ( ((nextval&0xFC000000) == 0xDC000000)		// ld
						|| ((nextval&0xFC000000) == 0x8C000000) )	// lw
					{
						spare_reg = (nextval>>16) & 31;
						if ((spare_reg>0) && (spare_reg<26))
						{
							//printf("Can use reg %d\n", spare_reg);
							Y_fixes[n2fix].instr[1] = nextval;
							Y_fixes[n2fix].spare_reg = spare_reg;
						}
					}
					//
					n2fix++;
					posfnd++;
				}
			}
			// search ld ra, $xxxx(reg)
			if ((buf[i]&0xFC1F0000) == 0xDC1F0000)
			{
				enable_jr = 1;
				for (;posfnd>0;posfnd--)
				{
					Y_fixes[n2fix-posfnd].can_use_jr = 1;
				}
				posfnd=0;
			}
			// reset
			if (have2reset==1)
			{
				have2reset=0;
				memset(reg_values, 0, 32*4);
				enable_jr = 0;
				enable_sd = 0;
				posfnd = 0;
			}
			// search jr ra
			if (buf[i] == 0x03e00008)
			{
				have2reset=1;
				/*
				memset(reg_values, 0, 32*4);
				enable_jr = 0;
				enable_sd = 0;
				posfnd = 0;
				*/
			}
		}
		offset += count;
	}

	fclose(fid);
	//exit(0);

#if 0
	if (n2fix==0)
		goto patching;
	////////////////////////////
	// Identify a valid Program Header
	for (i=0;i<elfHeader.e_phnum;i++)
	{
		if (elfProgH[i].p_type == 0x1)
		{
			unsigned int offs1=elfProgH[i].p_offset, offs2=elfProgH[i].p_offset+elfProgH[i].p_filesz;
			if ((n2fix==0)||((offs1<=Y_fixes[0].offset)&&(offs2>=Y_fixes[n2fix-1].offset)))
			//if (1)
			{
				if (nN>0)
				{
					if ((offs1<=vmN[0])&&(offs2>=vmN[nN-1]))
					{
						phnum=i;
						break;
					}
				}
				else if (nP>0)
				{
					if ((offs1<=vmP[0])&&(offs2>=vmP[nP-1]))
					{
						phnum=i;
						break;
					}
				}
				else
				{
					phnum=i;
					break;
				}
			}
		}
	}
	if ((elfHeader.e_phnum == 0)||(phnum==-1))
	{
		printf("Elf program header not found.\n");
		printf("Aborting.\n");
		fclose(fid);
		exit(0);
	}
	// end

	/*
	if (nN > 0)
		offset = vmN[0];
	else if (nP > 0)
		offset = vmP[0];
	else
		offset = 0;
	*/

	fid = fopen(argv[1], "rb");
	
	// search for call to SetGsCrt
	offset = 0;
	found=0;
	while (!feof(fid))
	{
		count = fread(buf, 4, 1024, fid);
		for (i=0;i<count;i++)
		{
			if ( ((buf[i]>>26)==2) || ((buf[i]>>26)==3) )
			{
				unsigned int j;
				value = ((buf[i]&0x03FFFFFF)<<2) - (elfProgH[phnum].p_vaddr-elfProgH[phnum].p_offset);
				for (j=0;j<nN;j++)
					if (vmN[j] == value)
					{
						//printf("Achou ref\n");
						addr1 = (offset+i)*4;
						found=1;
						break;
					}
				for (j=0;j<nP;j++)
					if (vmP[j] == value)
					{
						//printf("Achou ref\n");
						addr1 = (offset+i)*4;
						found=1;
						break;
					}
			}
			if (found)
				break;
		}
		if (found)
			break;
		offset += count;
	}


	// search for the begin of the function where the call is made
	offset = addr1;
	addr1 = addr1-elfProgH[phnum].p_offset+elfProgH[phnum].p_vaddr;
	if (offset >= 4*1024)
	{
		num2read = 4*1024;
		fseek(fid, offset-4*1024, SEEK_SET);
		count = fread(buf, 4, 1024, fid);
		num2read=ftell(fid);
	}
	else
	{
		num2read = offset;
		fseek(fid, 0, SEEK_SET);
		count = fread(buf, 0, offset>>2, fid);
	}
	for (i=0;i<count;i++)
	{
		if (((buf[count-i-1]>>16) == 0x27BD) &&		// ADDIU sp, sp, xxxx
			((buf[count-i-1]&0xFFFF) >= 0x8000) )
		{
			offset = offset-4*(i+1);
			break;
		}
	}
	addr1 = offset-elfProgH[phnum].p_offset+elfProgH[phnum].p_vaddr;


	// search for call to the previous found function
	fseek(fid, 0, SEEK_SET);
	offset = 0;
	found=0;
	while (!feof(fid))
	{
		count = fread(buf, 4, 1024, fid);
		for (i=0;i<count;i++)
		{
			if ( ((buf[i]>>26)==2) || ((buf[i]>>26)==3) )
			{
				value = (buf[i]&0x03FFFFFF)<<2;
				if (value==addr1)
				{
					offset = (offset+i)*4;
					found=1;
					break;
				}
			}
			if (found)
				break;
		}
		if (found)
			break;
		offset += count;
	}
	fseek(fid, offset-4*3, SEEK_SET);
	fread(buf,4, 5, fid);
	reg_values[4]=-1;
	reg_values[5]=-1;
	reg_values[6]=-1;
	reg_values[7]=-1;
	for (i=0;i<5;i++)
	{
		if ((buf[i]>>20)==0x240)		// li reg,value
		{
			reg = (buf[i]>>16)&31;
			value = buf[i]&0xFFFF;
			if ((reg>=4)&&(reg<=7))
			{
				reg_values[reg]=value;
				//printf("li a%d,%d\n", reg-4, value);
			}
		}
		if (((buf[i]>>16)==0x00) && ((buf[i]&0x7FF)==0x2D))		//daddu reg,zero,zero
		{
			reg = (buf[i]>>11)&31;
			if ((reg>=4)&&(reg<=7))
			{
				reg_values[reg]=0;
				//printf("daddu a%d,zero,zero\n", reg-4);
			}
		}
		if ((((buf[i]>>16)&0xFC1F)==0x00) && ((buf[i]&0x7FF)==0x2D))		//daddu reg,reg2,zero
		{
			reg = (buf[i]>>11)&31;
			reg2 = (buf[i]>>21)&31;
			if ((reg>=4)&&(reg<=7)&&(reg2>=4)&&(reg2<=7))
			{
				reg_values[reg]=reg_values[reg2];
				//printf("daddu a%d,a%d,zero\n", reg-4, reg2-4);
			}
		}
	}
	if (reg_values[7]<2)
		FvF=reg_values[7];


	fclose(fid);
	//exit(0);
	////////////////////////////
patching:
#endif


	fid = fopen(argv[1], "r+b");
	if (fid == NULL)
	{
		printf("File %s is read only.\n", argv[1]);
		exit(1);
	}
	if (nN == 0)
	{
		if (nP>0)
			printf("NTSC 2 PAL: already patched.\n");
		else
			printf("NTSC 2 PAL: could not find any patch locations.\n");
	}
	else
	{
		printf("NTSC 2 PAL: found %d patch locations.\n", nN);
		if (nP > 0)
		printf("             Also found %d locations already patched.\n", nP);
		for (i=0;i<nN;i++)
		{
			printf("Patching...");
			fseek(fid, vmN[i], SEEK_SET);
			fwrite(set_v2PAL, 4, 4, fid);
			printf(" Done.\n");
		}
	}

	if (n2fix == 0)
	{
		printf("Y FIX: could not find any patch locations.\n");
		fclose(fid);
	}
	else
	{
		for (i=0;i<elfHeader.e_phnum;i++)
		{
			if (elfProgH[i].p_type == 0x1)
			{
				unsigned int offs1=elfProgH[i].p_offset, offs2=elfProgH[i].p_offset+elfProgH[i].p_filesz;
				if ((offs1<=Y_fixes[0].offset)&&(offs2>=Y_fixes[n2fix-1].offset))
				{
					if (nN>0)
					{
						if ((offs1<=vmN[0])&&(offs2>=vmN[nN-1]))
						{
							phnum=i;
							break;
						}
					}
					else if (nP>0)
					{
						if ((offs1<=vmP[0])&&(offs2>=vmP[nP-1]))
						{
							phnum=i;
							break;
						}
					}
					else
					{
						phnum=i;
						break;
					}
				}
			}
		}
		if ((elfHeader.e_phnum == 0)||(phnum==-1))
		{
			printf("Elf program header not found.\n");
			printf("Aborting.\n");
			fclose(fid);
			exit(0);
		}
		
		printf("\n");
		printf("Y FIX: found %d patch locations.\n", n2fix);


		user_option_1 = 1;
#if 0
		printf("\n");
		printf("Depending on the game there are two possible offsets for screen centering:\n");
		printf("	1: small offset;\n");
		printf("	2: large offset.\n");
		printf("\n");
		if (FvF==0)
		{
			printf("This program has analysed the game code and RECOMMENDS you to use 2 (large offset).\n");
			printf("If the screen is shifted down too much you may run this patch again on the original file and select the small offset instead.\n");
		}
		else if (FvF==1)
		{
			printf("This program has analysed the game code and RECOMMENDS you to use 1 (small offset).\n");
			printf("If the screen is still shifted up you may run this patch again on the original file and select the large offset instead.\n");
		}
		else
		{
			printf("This program has analysed the game code but CAN NOT recommend you the offset to use.\n");
			printf("You may try the small offset first and if the screen is still shifted up you may run this patch again on the original file and select the large offset.\n");
		}
		printf("\n");
		printf("Please choose the offset (1/2): ");
		keycode = 0;
		while ((keycode!='1')&&(keycode!='2'))
		{
			while (!_kbhit());
			keycode = _getch();
		}
		printf("%c\n\n", keycode);
		if (keycode=='1')
			user_option_1 = 1;
		else
			user_option_1 = 2;
#endif


		space_av = elfProgH[phnum].p_offset-(elfHeader.e_phoff + elfHeader.e_phnum * elfHeader.e_phentsize);
		space_nd = 0;
		for (i=0;i<n2fix;i++)
		{
			if ((Y_fixes[i].spare_reg == 0)||(Y_fixes[i].spare_reg == Y_fixes[i].saved_reg)||(Y_fixes[i].has2return == 1))
				space_nd += 16;
			else
				space_nd += 8;
		}
		// Start file offset must be a power of two ?
////////space_nd = next2power(space_nd);
		if (space_av<(space_nd*4))
		{
			printf("Unable to patch Y pos.\n");
			printf("Wait for the next program release or contact the author.\n");
			printf("Aborting.\n");
			fclose(fid);
			exit(0);
		}
		use_short_sub = 1;
		if (space_av>=(n2fix*16*4))
			use_short_sub = 0;
		for (i=0;i<n2fix;i++)
		{
			printf("Patching...");
			Y_fixes[i].address = Y_fixes[i].offset-elfProgH[phnum].p_offset+elfProgH[phnum].p_vaddr;
			fseek(fid, Y_fixes[i].offset, SEEK_SET);
/**********/if ((use_short_sub||(user_option_1==2)) && (Y_fixes[i].spare_reg > 0) && (Y_fixes[i].spare_reg != Y_fixes[i].saved_reg) && (Y_fixes[i].has2return == 0))
				value = (elfProgH[phnum].p_vaddr-8*4-wbytes)>>2;
			else
				value = (elfProgH[phnum].p_vaddr-16*4-wbytes)>>2;
			if (Y_fixes[i].has2return==1)
			{
				value |= 0x08000000; //j
				memcpy(Sub, sub2, 16*4);
			}
			else if (Y_fixes[i].can_use_jr)
			{
				value |= 0x0C000000; //jal
/**************/if ((use_short_sub||(user_option_1==2)) && (Y_fixes[i].spare_reg > 0) && (Y_fixes[i].spare_reg != Y_fixes[i].saved_reg))
					memcpy(Sub, sub4, 8*4);
				else
					memcpy(Sub, sub2, 16*4);
			}
			else
			{
				value |= 0x08000000; //j
/**************/if ((use_short_sub||(user_option_1==2)) && (Y_fixes[i].spare_reg > 0) && (Y_fixes[i].spare_reg != Y_fixes[i].saved_reg))
				{
					memcpy(Sub, sub3, 8*4);
					Sub[5] |= (Y_fixes[i].address+8)>>2;
				}
				else
				{
					memcpy(Sub, sub1, 16*4);
					Sub[9] |= (Y_fixes[i].address+8)>>2;
				}
			}
			if (Y_fixes[i].has2return==1)
			{
				fseek(fid, Y_fixes[i].offset-4, SEEK_SET);
				fwrite(&value, 4, 1, fid);
				fseek(fid, Y_fixes[i].offset, SEEK_SET);
				value=0;
				fwrite(&value, 4, 1, fid);
			}
			else
			{
				fwrite(&value, 4, 1, fid);
				if (Y_fixes[i].spare_reg == Y_fixes[i].saved_reg)
				{
					fseek(fid, Y_fixes[i].offset+4, SEEK_SET);
					value=0;
					fwrite(&value, 4, 1, fid);
				}
			}

/**********/if ((use_short_sub||(user_option_1==2)) && (Y_fixes[i].spare_reg > 0) && (Y_fixes[i].spare_reg != Y_fixes[i].saved_reg) && (Y_fixes[i].has2return == 0))
			{
				if (user_option_1==2)
				{
					Sub[0] = 0x3C000005;
					Sub[0] |= (Y_fixes[i].spare_reg)<<16;
				}
				else
					Sub[0] |= (Y_fixes[i].spare_reg)<<16;
				value = ((Y_fixes[i].saved_reg)<<10) | ((Y_fixes[i].spare_reg)<<5) | (Y_fixes[i].saved_reg);
				Sub[1] |= value<<11;
				value = ((Y_fixes[i].saved_reg)<<5) | (Y_fixes[i].saved_reg);
				if (user_option_1==2)
				{
					Sub[2] |= (value<<16) | 0x801C;
				}
				else
					Sub[2] |= (value<<16) | 0x14;
				Sub[3] = Y_fixes[i].instr[0];
				Sub[4] = Y_fixes[i].instr[1];
				fseek(fid, elfProgH[phnum].p_offset-8*4-wbytes, SEEK_SET);
				fwrite(Sub, 4, 8, fid);
				wbytes += 8*4;
			}
			else
			{
				value = ((Y_fixes[i].saved_reg)<<5) | (Y_fixes[i].saved_reg);
				Sub[0] |= value<<16;
				Sub[1] |= value<<16;
				Sub[2] |= value<<16;
				Sub[3] |= value<<16;
				Sub[4] |= value<<16;
				Sub[5] |= value<<16;
				Sub[6] |= value<<16;
				Sub[7] |= (value<<16) | 0x14;
				Sub[8] = Y_fixes[i].instr[0];
				if (Y_fixes[i].spare_reg == Y_fixes[i].saved_reg)
					Sub[10] = Y_fixes[i].instr[1];
				fseek(fid, elfProgH[phnum].p_offset-16*4-wbytes, SEEK_SET);
				fwrite(Sub, 4, 16, fid);
				wbytes += 16*4;
			}
/**********/if (  (user_option_1==2) && (Y_fixes[i].spare_reg == 0) )
				printf(" WARNING: had to use small offset. ");
			printf(" Done.\n");
		}
		fclose(fid);

		// Change Elf Program Header
		elfProgH[phnum].p_offset -= wbytes;
		elfProgH[phnum].p_vaddr -= wbytes;
		if (elfProgH[phnum].p_paddr>0)
			elfProgH[phnum].p_paddr -= wbytes;
		elfProgH[phnum].p_filesz += wbytes;
		elfProgH[phnum].p_memsz += wbytes;

		value = elfProgH[phnum].p_vaddr;
		p_align=1;
		while ((value%2)==0)
		{
			value = value/2;
			p_align *= 2;
		}
		if (p_align==1)
			p_align=0;
		if ((p_align<elfProgH[phnum].p_align)||((p_align%elfProgH[phnum].p_align)!=0))
			elfProgH[phnum].p_align = p_align;

		// Change Elf Section Header
		for (i=0;i<elfHeader.e_shnum;i++)
		{
			if (elfSectH[i].sh_flags & 0x2)
			{
				unsigned int offs1=elfSectH[i].sh_offset, offs2=elfSectH[i].sh_offset+elfSectH[i].sh_size;
				if ((offs1<=Y_fixes[0].offset)&&(offs2>=Y_fixes[n2fix-1].offset))
				{
					if (nN>0)
					{
						if ((offs1<=vmN[0])&(offs2>=vmN[nN-1]))
						{
							shnum=i;
							break;
						}
					}
					else
					{
						shnum=i;
						break;
					}
				}
			}
		}
		if (elfHeader.e_shnum==0)
			printf("Warning: No section headers.\n");
		else if (shnum==-1)
			printf("Warning: Elf section header not found.\n");
		else
		{
			//printf("%s\n",sections_names);
			//if (strncmp(&sections_names[elfSectH[shnum].sh_name],".text",5)!=0)
			//	printf("Warning: Expected .text section.\n");
			elfSectH[shnum].sh_addr -= wbytes;
			elfSectH[shnum].sh_offset -= wbytes;
			elfSectH[shnum].sh_size += wbytes;
			
			value = elfSectH[shnum].sh_addr;
			p_align=1;
			while ((value%2)==0)
			{
				value = value/2;
				p_align *= 2;
			}
			if (p_align==1)
				p_align=0;
			if ((p_align<elfSectH[shnum].sh_addralign)||((p_align%elfSectH[shnum].sh_addralign)!=0))
				elfSectH[shnum].sh_addralign = p_align;
		}

		saveElfFile(argv[1]);
		printf("\nAll done.\n");
	}
}


unsigned int next2power(unsigned int n)
{
	unsigned int p;

	p=1;
	while (p<n)
		p=p*2;

	return p;
}


// search for the begin of the function where the call is made
unsigned int calledby(FILE *fid, unsigned int offset)
{
	unsigned int i, num2read, count;

	// fill buffer
	if (offset >= 4*1024)
	{
		num2read = 4*1024;
		fseek(fid, offset-4*1024, SEEK_SET);
		count = fread(buf, 4, 1024, fid);
		//num2read=ftell(fid);
	}
	else
	{
		num2read = offset;
		fseek(fid, 0, SEEK_SET);
		count = fread(buf, 0, offset>>2, fid);
	}

	for (i=0;i<count;i++)
	{
		if (((buf[count-i-1]>>16) == 0x27BD) &&		// ADDIU sp, sp, xxxx
			((buf[count-i-1]&0xFFFF) >= 0x8000) )
		{
			offset = offset-4*(i+1);
			break;
		}
	}

	return offset;
}
