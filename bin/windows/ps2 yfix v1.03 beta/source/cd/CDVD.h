/*  Modified by Jayteemaster for inclusion in ps2_pal2ntsc_yfix */

/*
 *  Original code from libcdvd by Hiryu & Sjeep (C) 2002
 *  Linux kernel headers
 *  Modified by Florin for PCSX2 emu
 */

#ifndef _CDVD_H
#define _CDVD_H

//#include "Common.h"

// Macros for READ Data pattan
#define CdSecS2048		0	// sector size 2048
#define CdSecS2328		1	// sector size 2328	
#define CdSecS2340		2	// sector size 2340

//#define CD_FRAMESIZE_RAW1 (CD_FRAMESIZE_RAW-CD_SYNC_SIZE) /*2340*/
//#define CD_FRAMESIZE_RAW0 (CD_FRAMESIZE_RAW-CD_SYNC_SIZE-CD_HEAD_SIZE) /*2336*/
//#define CD_HEAD_SIZE          4 /* header (address) bytes per raw data frame */
//#define CD_SUBHEAD_SIZE       8 /* subheader bytes per raw XA data frame */
//#define CD_XA_HEAD        (CD_HEAD_SIZE+CD_SUBHEAD_SIZE) /* "before data" part of raw XA frame */

/*
 * A CD-ROM physical sector size is 2048, 2052, 2056, 2324, 2332, 2336, 
 * 2340, or 2352 bytes long.  
 *         Sector types of the standard CD-ROM data formats:
 *
 * format   sector type               user data size (bytes)
 * -----------------------------------------------------------------------------
 *   1     (Red Book)    CD-DA          2352    (CD_FRAMESIZE_RAW)
 *   2     (Yellow Book) Mode1 Form1    2048    (CD_FRAMESIZE)
 *   3     (Yellow Book) Mode1 Form2    2336    (CD_FRAMESIZE_RAW0)
 *   4     (Green Book)  Mode2 Form1    2048    (CD_FRAMESIZE)
 *   5     (Green Book)  Mode2 Form2    2328    (2324+4 spare bytes)
 *
 *
 *       The layout of the standard CD-ROM data formats:
 * -----------------------------------------------------------------------------
 * - audio (red):                  | audio_sample_bytes |
 *                                 |        2352        |
 *
 * - data (yellow, mode1):         | sync - head - data - EDC - zero - ECC |
 *                                 |  12  -   4  - 2048 -  4  -   8  - 276 |
 *
 * - data (yellow, mode2):         | sync - head - data |
 *                                 |  12  -   4  - 2336 |
 *
 * - XA data (green, mode2 form1): | sync - head - sub - data - EDC - ECC |
 *                                 |  12  -   4  -  8  - 2048 -  4  - 276 |
 *
 * - XA data (green, mode2 form2): | sync - head - sub - data - Spare |
 *                                 |  12  -   4  -  8  - 2324 -  4    |
 *
 */

// Macros for Spindle control
#define CdSpinMax		0
#define CdSpinNom		1	// Starts reading data at maximum rotational velocity and if a read error occurs, the rotational velocity is reduced.
#define CdSpinStm		0	// Recommended stream rotation speed.

// Macros for TrayReq
#define CdTrayOpen		0
#define CdTrayClose		1
#define CdTrayCheck		2

/*
 *      Media mode
 */
#define SCECdCD         1
#define SCECdDVD        2

typedef struct {
	unsigned char stat;  			// 0: normal. Any other: error
	unsigned char second; 			// second (BCD value)
	unsigned char minute; 			// minute (BCD value)
	unsigned char hour; 			// hour (BCD value)
	unsigned char week; 			// week (BCD value)
	unsigned char day; 			// day (BCD value)
	unsigned char month; 			// month (BCD value)
	unsigned char year; 			// year (BCD value)
} CdCLOCK;

typedef struct {
	unsigned int lsn; 			// Logical sector number of file
	unsigned int size; 			// File size (in bytes)
	char name[16]; 		// Filename
	unsigned char date[8]; 		// 1th: Seconds
						// 2th: Minutes
						// 3th: Hours
						// 4th: Date
						// 5th: Month
						// 6th 7th: Year (4 digits)
} CdlFILE;

typedef struct {
	unsigned char minute; 			// Minutes
	unsigned char second; 			// Seconds
	unsigned char sector; 			// Sector
	unsigned char track; 			// Track number
} CdlLOCCD;

typedef struct {
	unsigned char trycount; 		// Read try count (No. of error retries + 1) (0 - 255)
	unsigned char spindlctrl; 		// SCECdSpinStm: Recommended stream rotation speed.
						// SCECdSpinNom: Starts reading data at maximum rotational velocity and if a read error occurs, the rotational velocity is reduced.
	unsigned char datapattern; 	// SCECdSecS2048: Data size 2048 bytes
						// SCECdSecS2328: 2328 bytes
						// SCECdSecS2340: 2340 bytes
	unsigned char pad; 			// Padding data produced by alignment.
} CdRMode;

#if defined(WIN32)
#pragma pack(1)
#endif

struct TocEntry
{
	unsigned int	fileLBA;
	unsigned int fileSize;
	unsigned char	fileProperties;
	unsigned char	padding1[3];
	unsigned char	filename[128+1];
	unsigned char	date[7];
#if defined(WIN32)
};
#else
} __attribute__((packed));
#endif

#if defined(WIN32)
#pragma pack()
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int CDVD_findfile(char* fname, struct TocEntry* tocEntry);
/*
int CdBreak(void);
int CdCallback( void (*func)() );
int CdDiskReady(int mode);
int CdGetDiskType(void);
int CdGetError(void);
unsigned int CdGetReadPos(void);
int CdGetToc(unsigned char *toc);
int CdInit(int init_mode);
CdlLOCCD *CdIntToPos(int i, CdlLOCCD *p);
int CdPause(void);
int CdPosToInt(CdlLOCCD *p);*/
int CdRead(unsigned int lsn, unsigned int sectors, void *buf, CdRMode *mode);
int CdWrite(unsigned int lsn, unsigned int sectors, void *buf, CdRMode *mode);
int DvdRead(unsigned int lsn, unsigned int sectors, void *buf, CdRMode *mode);
/*int CdReadClock(CdCLOCK *rtc);
int CdSearchFile (CdlFILE *fp, const char *name);
int CdSeek(unsigned int lsn);
int CdStandby(void);
int CdStatus(void);
int CdStop(void);
int CdSync(int mode);
int CdTrayReq(int mode, unsigned int *traycnt);
*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _CDVD_H
