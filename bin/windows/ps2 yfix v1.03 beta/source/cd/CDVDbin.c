/*  Modified by Jayteemaster for inclusion in ps2_pal2ntsc_yfix */

 /****************************************************************************\
 * CDVDbin v0.63 PLUGIN for PS2 emus (PCSX2) based on 
 * CDiso PLUGIN for FPSE
 *
 *
 * AUTHOR: Xobro, mail: _xobro_@tin.it 
 *
 * WHAT'S NEW: It compiles and it seems to work! ;-)
 *
 * TO DO: cue/ccd reading; tracks stuff;
 *        subchannel reading
 *		  registry or ini save of iso/bin name
 *
 * PORTED BY FLORIN
 *
\****************************************************************************/

#include <windows.h>
#include <stdio.h>
#include "CDVDbin.h"

//#define DEBUG

/////////////////////////////////////////////////////////////////
// Internal variables & defines
/////////////////////////////////////////////////////////////////

static HANDLE hinstance = (HANDLE)-1;

#define RAW_SECTOR_SIZE     2352
#define DATA_SECTOR_SIZE	2048	// not used at the moment

#define MSF2SECT(m,s,f)	(((m)*60+(s)-2)*75+(f)) 

#define	INT2BCD(a)	((a)/10*16+(a)%10)

static HANDLE hISOFile = NULL;

#define MAXFILENAMELENGHT 512
char ISOFileName[MAXFILENAMELENGHT] = {0};

static int iso=FALSE;	//FALSE==bin; TRUE==iso
static int CDVDmode=-1;

static int error = 0;

static unsigned char  readBuffer[RAW_SECTOR_SIZE];
static unsigned int LastSector = -1;

#define MODE0			1
#define MODE1			2
#define MODE2_FORM1		3
#define MODE2_FORM2		4

int CDautodetect(char *ISOFileName) {
	HANDLE hISOFile = NULL;
	unsigned char buf[30];
	unsigned int numread, aux;

	CDVDmode=-1;
	//open the selected file
	hISOFile = CreateFile(ISOFileName,				// FILE to open  
						  GENERIC_READ,             // open for reading 
						  FILE_SHARE_READ|FILE_SHARE_WRITE,	//? would be better 0 (do not share)? 
						  NULL,                     // no security 
						  OPEN_EXISTING,            // existing file only 
						  FILE_FLAG_SEQUENTIAL_SCAN,// flags 
						  NULL);                    // no attr. template 
	if (hISOFile == INVALID_HANDLE_VALUE){
		return -1;
	}
	

	aux=0;
	SetFilePointer(hISOFile, 16*2048, &aux, FILE_BEGIN);
	ReadFile(hISOFile, buf, 6, &numread, 0);
	if (strncmp(buf+1, "CD001", 5)==0)
	{
		CloseHandle(hISOFile);
		CDVDmode=0;
		//return MODE0;
		return 1;
	}
	aux=0;
	SetFilePointer(hISOFile, 16*2352, &aux, FILE_BEGIN);
	ReadFile(hISOFile, buf, 22, &numread, 0);
	if (strncmp(buf+17, "CD001", 5)==0)
	{
		CloseHandle(hISOFile);
		//return MODE1;
		return 0;
	}
	aux=0;
	SetFilePointer(hISOFile, 16*2352, &aux, FILE_BEGIN);
	ReadFile(hISOFile, buf, 30, &numread, 0);
	if (strncmp(buf+25, "CD001", 5)==0)
	{
		CloseHandle(hISOFile);
		if ((buf[18]>>5)==0)
		{
			CDVDmode=2;
			//return MODE2_FORM1;
			return 1;
		}
		else
		{
			//return MODE2_FORM2;
			return 0;
		}
	}

	CloseHandle(hISOFile);
	return 0;
}



////////////////////////////////////////////////////////////////
// CDVDopen: CD hw init
/////////////////////////////////////////////////////////////////
int CDVDopen(char *ISOFileName) {
	__int64 filesize;
	int ver1, ver2;

	//open the selected file
	hISOFile = CreateFile(ISOFileName,				// FILE to open  
						  GENERIC_READ|GENERIC_WRITE,       // open for reading and writing
						  FILE_SHARE_READ|FILE_SHARE_WRITE,	//? would be better 0 (do not share)? 
						  NULL,                     // no security 
						  OPEN_EXISTING,            // existing file only 
						  FILE_FLAG_SEQUENTIAL_SCAN,// flags 
						  NULL);                    // no attr. template 
	if (hISOFile == INVALID_HANDLE_VALUE){
#ifdef DEBUG
		SysMessage("error opening the file\n");
#endif
		return -1;
	}
	
	(*(unsigned int*)(&filesize))=GetFileSize(hISOFile, ((unsigned int*)(&filesize))+1);
	if ((CDVDmode!=-1)||(1))
	{
		ver1=(filesize % RAW_SECTOR_SIZE)==0;
		ver2=(filesize % DATA_SECTOR_SIZE)==0;

		if (((ver1)&&(ver2)) || ((!ver1)&&(!ver2)))
		{
			if (CDVDmode==0)
				iso=TRUE;
			if (CDVDmode==2)
				iso=FALSE;
		}
		else if (ver1)
			iso=FALSE;
		else if (ver2)
			iso=TRUE;
		else
		{
			CloseHandle(hISOFile);
			hISOFile=NULL;
			return -2;
		}

		/* OLD CODE */
		/*
		if (filesize % RAW_SECTOR_SIZE==0)	iso=FALSE;	else
		if (filesize % DATA_SECTOR_SIZE==0)	iso=TRUE;	else{
#ifdef DEBUG
			SysMessage("not a raw cd/dvd image file\n");
#endif
			CloseHandle(hISOFile);
			hISOFile=NULL;
			return -2;
		}
		*/
	}
	else
	{
		if (CDVDmode==0)
			iso=TRUE;
		if (CDVDmode==2)
			iso=FALSE;
	}
	
	error = 0;
	return 0;
}

/////////////////////////////////////////////////////////////////
// CDVDclose: CD shutdown
/////////////////////////////////////////////////////////////////
void CDVDclose() {
	//CD_Wait();
	CloseHandle(hISOFile);
	CDVDmode=-1;
}

/////////////////////////////////////////////////////////////////
// CDVDreadTrack: read 1(one) sector/frame (2352 bytes)
/////////////////////////////////////////////////////////////////
int CDVDreadTrack(unsigned int lsn) {
	unsigned int nbytesRead;
	int Ret;
	__int64 filepos;

	memset(readBuffer, 0, RAW_SECTOR_SIZE);
	
	//if no iso selected act as a null CD plugin
	if (hISOFile == NULL){
		error = 1;
		return 0;
	}

	// Set the file pointer at the right sector
	// JayteeMaster 21/05/2004: fix to work with filepos>2GB -  added the cast to __int64
	// JayteeMaster 10/06/2004: new fix
	filepos=(__int64)lsn * (iso?DATA_SECTOR_SIZE:RAW_SECTOR_SIZE);
	SetFilePointer (hISOFile,
                    *(unsigned int*)(&filepos),
                    ((unsigned int*)(&filepos))+1,
                    FILE_BEGIN);
	
	Ret = ReadFile(hISOFile, readBuffer+(iso?12+12:0), (iso?DATA_SECTOR_SIZE:RAW_SECTOR_SIZE),
		&nbytesRead, NULL);

#ifdef DEBUG
    SysMessage("Ret = %d - nu = %d\n", Ret, nbytesRead);
    if (!Ret) SysMessage("Error = %08x\n",GetLastError());
#endif

	error = 0;
	
	return 0;
}


/////////////////////////////////////////////////////////////////
// CDVDwriteTrack: write 1(one) sector/frame (2352 bytes)
/////////////////////////////////////////////////////////////////
extern unsigned int build_edc(unsigned char inout[], int from, int upto);
extern int do_encode_L2(unsigned char *inout);

int CDVDwriteTrack(unsigned int lsn) {
	unsigned int nbytesWritten;
	int Ret;
	__int64 filepos;
	unsigned char edc_buf[4];
	unsigned int result;

	//memset(readBuffer, 0, RAW_SECTOR_SIZE);
	
	//if no iso selected act as a null CD plugin
	if (hISOFile == NULL){
		error = 1;
		return 0;
	}

	// Set the file pointer at the right sector
	// JayteeMaster 21/05/2004: fix to work with filepos>2GB -  added the cast to __int64
	filepos=(__int64)lsn * (iso?DATA_SECTOR_SIZE:RAW_SECTOR_SIZE);
	SetFilePointer (hISOFile,
                    *(unsigned int*)(&filepos),
                    ((unsigned int*)(&filepos))+1,
                    FILE_BEGIN);

	if (iso == FALSE)
	{
		result = build_edc(readBuffer, 16, 16+8+2048-1);
		edc_buf[0] = result;
		edc_buf[1] = result >> 8;
		edc_buf[2] = result >> 16;
		edc_buf[3] = result >> 24;
		if (memcmp(readBuffer+24+2048, edc_buf, 4) != 0)
		{
			memcpy(readBuffer+24+2048, edc_buf, 4);
			do_encode_L2(readBuffer);
		}
	}
	
	Ret = WriteFile(hISOFile, readBuffer+(iso?12+12:0), (iso?DATA_SECTOR_SIZE:RAW_SECTOR_SIZE),
		&nbytesWritten, NULL);  

#ifdef DEBUG
    SysMessage("Ret = %d - nu = %d\n", Ret, nbytesWritten);
    if (!Ret) SysMessage("Error = %08x\n",GetLastError());
#endif

	error = 0;
	
	return 0;
}


/////////////////////////////////////////////////////////////////
// CDVDgetBuffer: address of sector/frame buffer
// not like in ps1 plugins; it is the address of the buffer
// including the sync; CDRgetBuffer()-12 == CDVDgetBuffer()
/////////////////////////////////////////////////////////////////
// return can be NULL (for async modes); no async mode for now...
unsigned char* CDVDgetBuffer() {
	return readBuffer;
}

/////////////////////////////////////////////////////////////////
// CDVDgetTN: tracks number
/////////////////////////////////////////////////////////////////
int CDVDgetTN(cdvdTN *Buffer) {
	//if no iso selected act as a null CD plugin
	if (hISOFile == NULL){
		error = 1;
		Buffer->strack = 1;
		Buffer->etrack = 1;
		return 0;
	}

	//should be read from .cue in case of .bin (iso==0)
    Buffer->strack = 1;//toc.cdth_trk0; // start track
	Buffer->etrack = 1;//toc.cdth_trk1; // end track
	return 0;
}

/////////////////////////////////////////////////////////////////
// CDVDgetTD: track start end addresses
/////////////////////////////////////////////////////////////////
int CDVDgetTD(unsigned char Track, cdvdLoc *Buffer) {
	//if no iso selected act as a null CD plugin
	if (hISOFile == NULL){
		error = 1;
		memset(Buffer, 0, 3);
		return 0;
	}

	//if (Track == 0)
	//	Track = 0xaa;                   // total time
	//entry.cdte_track = Track;
	//entry.cdte_format = CDROM_MSF;

	//if (ioctl(cdHandle, CDROMREADTOCENTRY, &entry) == -1)
	//	return -1;

	//should be read from .cue in case of .bin (iso==0)
	Buffer->minute = 0;//entry.cdte_addr.msf.minute;    /* minute */
	Buffer->second = 0;//entry.cdte_addr.msf.second;    /* second */
	Buffer->frame  = 0;//entry.cdte_addr.msf.frame;     /* frame */

	return 0;
}
