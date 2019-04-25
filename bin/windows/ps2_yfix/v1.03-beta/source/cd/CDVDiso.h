/*  Modified by Jayteemaster for inclusion in ps2_pal2ntsc_yfix */

/*
 *  Original code from libcdvd by Hiryu & Sjeep (C) 2002
 *  Modified by Florin for PCSX2 emu
 */

#ifndef __CDVDISO_H__
#define __CDVDISO_H__

#include "CDVD.h"

int CDVD_findfile(char* fname, struct TocEntry* tocEntry);
int CDVD_GetDir_RPC_request(char* pathname, char* extensions, unsigned int inc_dirs);
int CDVD_GetDir_RPC_get_entries(struct TocEntry tocEntry[], int req_entries);

#if defined(WIN32)
#pragma pack(1)
#endif

struct rootDirTocHeader
{
	unsigned short int	length;
	unsigned int tocLBA;
	unsigned int tocLBA_bigend;
	unsigned int tocSize;
	unsigned int tocSize_bigend;
	unsigned char	dateStamp[8];
	unsigned char	reserved[6];
	unsigned char	reserved2;
	unsigned char	reserved3;
#if defined(WIN32)
};
#else
} __attribute__((packed));
#endif

struct asciiDate
{
	char	year[4];
	char	month[2];
	char	day[2];
	char	hours[2];
	char	minutes[2];
	char	seconds[2];
	char	hundreths[2];
	char	terminator[1];
#if defined(WIN32)
};
#else
} __attribute__((packed));
#endif

struct cdVolDesc
{
	unsigned char		filesystemType;	// 0x01 = ISO9660, 0x02 = Joliet, 0xFF = NULL
	unsigned char		volID[5];		// "CD001"
	unsigned char		reserved2;
	unsigned char		reserved3;
	unsigned char		sysIdName[32];
	unsigned char		volName[32];	// The ISO9660 Volume Name
	unsigned char		reserved5[8];
	unsigned int		volSize;		// Volume Size
	unsigned int		volSizeBig;		// Volume Size Big-Endian
	unsigned char		reserved6[32];
	unsigned int		unknown1;
	unsigned int		unknown1_bigend;
	unsigned short int		volDescSize;
	unsigned short int		volDescSize_bigend;
	unsigned int		unknown3;
	unsigned int		unknown3_bigend;
	unsigned int		priDirTableLBA;	// LBA of Primary Dir Table
	unsigned int		reserved7;
	unsigned int		secDirTableLBA;	// LBA of Secondary Dir Table
	unsigned int		reserved8;
	struct rootDirTocHeader	rootToc;
	unsigned char		volSetName[128];
	unsigned char		publisherName[128];
	unsigned char		preparerName[128];
	unsigned char		applicationName[128];
	unsigned char		copyrightFileName[37];
	unsigned char		abstractFileName[37];
	unsigned char		bibliographyFileName[37];
	struct	asciiDate	creationDate;
	struct	asciiDate	modificationDate;
	struct	asciiDate	effectiveDate;
	struct	asciiDate	expirationDate;
	unsigned char		reserved10;
	unsigned char		reserved11[1166];
#if defined(WIN32)
};
#else
} __attribute__((packed));
#endif

struct dirTableEntry
{
	unsigned char	dirNameLength;
	unsigned char	reserved;
	unsigned int	dirTOCLBA;
	unsigned short int dirDepth;
	unsigned char	dirName[32];
#if defined(WIN32)
};
#else
} __attribute__((packed));
#endif

struct dirTocEntry
{
	short	length;
	unsigned int	fileLBA;
	unsigned int	fileLBA_bigend;
	unsigned int	fileSize;
	unsigned int	fileSize_bigend;
	unsigned char	dateStamp[6];
	unsigned char	reserved1;
	unsigned char	fileProperties;
	unsigned char	reserved2[6];
	unsigned char	filenameLength;
	unsigned char	filename[128];
#if defined(WIN32)
};
#else
} __attribute__((packed));
#endif	// This is the internal format on the CD
// TocEntry structure contains only the important stuff needed for export

#if defined(WIN32)
#pragma pack()
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
	extern unsigned int file_toc_offset;
	extern unsigned int file_toc_lba;
#ifdef __cplusplus
}
#endif // __cplusplus

#endif//__CDVDISO_H__
