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
#include <stdarg.h>
#include <string.h>
#include <windows.h>

#include "Misc.h"
#include "CDVDbin.h"
#include "CDVDisodrv.h"




// LOAD STUFF

#define ISODCL(from, to) (to - from + 1)

struct iso_directory_record {
	char length			[ISODCL (1, 1)]; /* 711 */
	char ext_attr_length		[ISODCL (2, 2)]; /* 711 */
	char extent			[ISODCL (3, 10)]; /* 733 */
	char size			[ISODCL (11, 18)]; /* 733 */
	char date			[ISODCL (19, 25)]; /* 7 by 711 */
	char flags			[ISODCL (26, 26)];
	char file_unit_size		[ISODCL (27, 27)]; /* 711 */
	char interleave			[ISODCL (28, 28)]; /* 711 */
	char volume_sequence_number	[ISODCL (29, 32)]; /* 723 */
	unsigned char name_len		[ISODCL (33, 33)]; /* 711 */
	char name			[1];
};

#define btoi(b)		((b)/16*10 + (b)%16)		/* BCD to u_char */
#define itob(i)		((i)/10*16 + (i)%10)		/* u_char to BCD */

void mmssdd( char *b, char *p )
 {
	int m, s, d;
#if defined(__DREAMCAST__)
	int block = (b[0]&0xff) | ((b[1]&0xff)<<8) | ((b[2]&0xff)<<16) | (b[3]<<24);
#else
	int block = *((int*)b);
#endif
	
	block += 150;
	m = block / 4500;			// minuten
	block = block - m * 4500;	// minuten rest
	s = block / 75;				// sekunden
	d = block - s * 75;			// sekunden rest
	
	m = ( ( m / 10 ) << 4 ) | m % 10;
	s = ( ( s / 10 ) << 4 ) | s % 10;
	d = ( ( d / 10 ) << 4 ) | d % 10;	
	
	p[0] = m;
	p[1] = s;
	p[2] = d;
}

#define incTime() \
	time->frame++; \
	if(time->frame == 75) { \
		time->frame = 0; \
		time->second++; \
		if (time->second == 60) { \
			time->second = 0; \
			time->minute++; \
		} \
	}

#define READTRACK() \
	if (CDVDreadTrack(time) == -1) return -1; \
	buf = CDVDgetBuffer() + 12; if (buf == NULL) return -1;

#define READMDIR() \
	READTRACK(); \
	memcpy(mdir, buf+12, 2048); \
 \
	incTime(); \
	READTRACK(); \
	memcpy(mdir+2048, buf+12, 2048);


int GetPS2ElfName(char *name){
	int		f;
	char	buffer[256];//if a file is longer...it should be shorter :D
	char	*pos;
	
	CDVDFS_init();

	if ((f=CDVDFS_open("SYSTEM.CNF;1", 1))<0) {
///		SysPrintf("SYSTEM.CNF not found\n");      ??????????????
		return FALSE;//could not find; not a PS/PS2 cdvd
	}

	CDVDFS_read(f, buffer, 256);

	CDVDFS_close(f);

///	SysPrintf("SYSTEM.CNF:\n",buffer);
///	SysPrintf("%s\n",buffer);
	pos=strstr(buffer, "BOOT2");
	if (pos==NULL)
		return FALSE;
	pos+=strlen("BOOT2");
	while (pos && *pos && pos<=&buffer[255] 
		&& (*pos<'A' || (*pos>'Z' && *pos<'a') || *pos>'z'))
		pos++;
	if (!pos || *pos==0)
		return FALSE;

	sscanf(pos, "%s", name);
//	SysPrintf("name: '%s'\n", name);

	return TRUE;
}
