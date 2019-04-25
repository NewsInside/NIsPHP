/*  Modified by Jayteemaster for inclusion in ps2_pal2ntsc_yfix */

/*
 *  Original code from libcdvd by Hiryu & Sjeep (C) 2002
 *  Modified by Florin for PCSX2 emu
 */

#ifndef __CDVDISODRV_H__
#define __CDVDISODRV_H__

//#include "Common.h"
#include "CDVD.h"

extern CdRMode cdReadMode;

/* Filing-system exported functions */
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void CDVDFS_init();
int CDVDFS_open(char *name, int mode);
unsigned int CDVDFS_filesize(int fd);
int CDVDFS_lseek(int fd, int offset, int whence);
int CDVDFS_read( int fd, char * buffer, int size );
int CDVDFS_write( int fd, char * buffer, int size );
int CDVDFS_close( int fd);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif//__CDVDISODRV_H__
