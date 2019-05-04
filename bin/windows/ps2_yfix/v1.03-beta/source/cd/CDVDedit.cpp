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

// CD support

#include <afxwin.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <memory.h>
#include <stdarg.h>
#include "CDVD.h"
#include "CDVDbin.h"
//#include "Misc.h"
#include "CDVDiso.h"
#include "CDVDisodrv.h"

#ifdef GUI

extern CEdit *p_m_edit;
static void SysPrintf(char *fmt, ...) {
	va_list list;
	char msg[512];

	va_start(list,fmt);
	vsprintf(msg,fmt,list);
	va_end(list);

	p_m_edit->ReplaceSel(msg);
}

#define Exit(code) return

#else

static void SysPrintf(char *fmt, ...) {
	va_list list;
	char msg[512];

	va_start(list,fmt);
	vsprintf(msg,fmt,list);
	va_end(list);

	printf(msg);
}

#define Exit(code) exit(code)

#endif



extern unsigned char buf_2[4*1024];
char Editmsg[1024];
BOOL show_Editmsg;


static unsigned int local_file_toc_lba, local_file_toc_offset, local_filesize;


void extract(char *image, char *file, char *temp_filename)
{
	int fd, numread;
	FILE *temp;
	char temp_path[MAX_PATH];
	char backup[MAX_PATH];
	char aux[MAX_PATH];
	//char temp_filename[MAX_PATH];


	if (!GetTempPath(MAX_PATH, temp_path))
	{
		SysPrintf("Can not get temp path.\r\n");
		return;
	}
	if (!GetTempFileName(temp_path, "elf", 0, temp_filename))
	{
		SysPrintf("Can not get temp filename.\r\n");
		return;
	}
	temp=fopen(temp_filename, "wb");
	if (temp==NULL)
	{
		SysPrintf("Can not create temp file.\r\n");
		return;
	}

	CDVDopen(image);
	CDVDFS_init();
	fd=CDVDFS_open(file, 1);

	local_file_toc_lba = file_toc_lba;
	local_file_toc_offset = file_toc_offset;
	local_filesize = CDVDFS_filesize(fd);

	while ((numread=CDVDFS_read(fd, (char*)buf_2, 4*1024))>0)
		fwrite(buf_2, 1, numread, temp);

	CDVDFS_close(fd);
	CDVDclose();
	fclose(temp);

	strcpy(aux, file);
	aux[strlen(file)-2]=0;
	_makepath(backup, 0, temp_path, aux, ".bak");
	show_Editmsg=CopyFile(temp_filename, backup, TRUE);
	sprintf(Editmsg, "File %s was backuped to %s\r\n\r\n", aux, backup);
}


void insert(char *image, char *file, char *temp_filename)
{
	int fd, numread;
	FILE *temp;
	//char temp_path[MAX_PATH];
	//char temp_filename[MAX_PATH];
	unsigned int filesize, max_filesize;
	CdRMode cdReadMode;
	char toc[2048];
	unsigned int aux1, aux2;

	temp=fopen(temp_filename, "rb");
	if (temp==NULL)
	{
		SysPrintf("Can not open temp file.\r\n");
		return;
	}
	fseek(temp, 0, SEEK_END);
	filesize = ftell(temp);
	fseek(temp, 0, SEEK_SET);

	CDVDopen(image);

	if (filesize != local_filesize)
	{
		if (filesize < local_filesize)
		{
			SysPrintf("File size too small.\r\n");
			CDVDclose();
			fclose(temp);
			return;
		}
		if ((local_filesize%2048)==0)
			max_filesize = local_filesize;
		else
			max_filesize = ((local_filesize/2048)+1)*2048;
		if (filesize > max_filesize)
		{
			SysPrintf("File size too big.\r\n");
			CDVDclose();
			fclose(temp);
			return;
		}
		//make sure we have good cdReadMode
		cdReadMode.trycount = 0;
		cdReadMode.spindlctrl = CdSpinStm;
		cdReadMode.datapattern = CdSecS2048;
		CdRead(local_file_toc_lba, 1, toc, &cdReadMode);
		//
		aux1 = *((unsigned int*)(toc+local_file_toc_offset+10));
		aux2 = *((unsigned int*)(toc+local_file_toc_offset+14));
		aux2 = (aux2>>24) | (((aux2>>16)&255)<<8) | (((aux2>>8)&255)<<16) | (((aux2)&255)<<24);
		if ((aux1!=aux2)||(aux1!=local_filesize))
		{
			SysPrintf("File size do not match.\r\n");
			CDVDclose();
			fclose(temp);
			return;
		}
		aux1 = filesize;
		aux2 = filesize;
		aux2 = (aux2>>24) | (((aux2>>16)&255)<<8) | (((aux2>>8)&255)<<16) | (((aux2)&255)<<24);
		memcpy(toc+local_file_toc_offset+10, &aux1, 4);
		memcpy(toc+local_file_toc_offset+14, &aux2, 4);
		CdWrite(local_file_toc_lba, 1, toc, &cdReadMode);
	}

	CDVDFS_init();
	fd=CDVDFS_open(file, 1);

	while ((numread=fread(buf_2, 1, 4*1024, temp))>0)
		CDVDFS_write(fd, (char*)buf_2, numread);

	CDVDFS_close(fd);
	CDVDclose();
	fclose(temp);
}


void restore(char *image, char *file, char *temp_filename)
{
	int fd, numread;
	FILE *temp;
	//char temp_path[MAX_PATH];
	//char temp_filename[MAX_PATH];
	unsigned int filesize, max_filesize;
	CdRMode cdReadMode;
	char toc[2048];
	unsigned int aux1, aux2;
	unsigned int r_local_file_toc_lba, r_local_file_toc_offset, r_local_filesize;

	CDVDopen(image);
	CDVDFS_init();
	fd=CDVDFS_open(file, 1);
	r_local_file_toc_lba = file_toc_lba;
	r_local_file_toc_offset = file_toc_offset;
	r_local_filesize = CDVDFS_filesize(fd);
	CDVDFS_close(fd);
	CDVDclose();

	temp=fopen(temp_filename, "rb");
	if (temp==NULL)
	{
		SysPrintf("Can not open backup file.\r\n");
		return;
	}
	fseek(temp, 0, SEEK_END);
	filesize = ftell(temp);
	fseek(temp, 0, SEEK_SET);

	CDVDopen(image);
	if (filesize != r_local_filesize)
	{
		/*
		if (filesize < r_local_filesize)
		{
			SysPrintf("File size too small.\r\n");
			CDVDclose();
			fclose(temp);
			return;
		}
		*/
		if (filesize > r_local_filesize)
		{
			SysPrintf("File size too big.\r\n");
			CDVDclose();
			fclose(temp);
			return;
		}
		//make sure we have good cdReadMode
		cdReadMode.trycount = 0;
		cdReadMode.spindlctrl = CdSpinStm;
		cdReadMode.datapattern = CdSecS2048;
		CdRead(r_local_file_toc_lba, 1, toc, &cdReadMode);
		//
		aux1 = *((unsigned int*)(toc+r_local_file_toc_offset+10));
		aux2 = *((unsigned int*)(toc+r_local_file_toc_offset+14));
		aux2 = (aux2>>24) | (((aux2>>16)&255)<<8) | (((aux2>>8)&255)<<16) | (((aux2)&255)<<24);
		if ((aux1!=aux2)||(aux1!=r_local_filesize))
		{
			SysPrintf("File size do not match.\r\n");
			CDVDclose();
			fclose(temp);
			return;
		}
		aux1 = filesize;
		aux2 = filesize;
		aux2 = (aux2>>24) | (((aux2>>16)&255)<<8) | (((aux2>>8)&255)<<16) | (((aux2)&255)<<24);
		memcpy(toc+r_local_file_toc_offset+10, &aux1, 4);
		memcpy(toc+r_local_file_toc_offset+14, &aux2, 4);
		CdWrite(r_local_file_toc_lba, 1, toc, &cdReadMode);
	}

	CDVDFS_init();
	fd=CDVDFS_open(file, 1);

	//while ((numread=fread(buf_2, 1, 4*1024, temp))>0)
	//	CDVDFS_write(fd, (char*)buf_2, numread);
	while ((numread=fread(buf_2, 1, 4*1024, temp))>0)
	{
		if (numread<4*1024)
		{
			max_filesize=0;
		}
		CDVDFS_write(fd, (char*)buf_2, numread);
	}
	/*
	memset(buf_2,0,1024);
	while (filesize<r_local_filesize)
	{
		if ((filesize+1024)<=r_local_filesize)
		{
			CDVDFS_write(fd, (char*)buf_2, 1024);
			filesize+=1024;
		}
		else
		{
			CDVDFS_write(fd, (char*)buf_2, r_local_filesize-filesize);
			filesize=r_local_filesize;
		}
	}
	*/

	CDVDFS_close(fd);
	CDVDclose();
	fclose(temp);
}
