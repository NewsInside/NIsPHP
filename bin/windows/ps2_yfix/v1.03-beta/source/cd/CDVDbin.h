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


/////////////////////////////////////////////////////////////////
// Defines
/////////////////////////////////////////////////////////////////

typedef struct { // NOT bcd coded
	unsigned int minute;
	unsigned int second;
	unsigned int frame;
} cdvdLoc;

typedef struct {
	unsigned char strack;
	unsigned char etrack;
} cdvdTN;


/////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
int CDautodetect(char *ISOFileName);
int CDVDopen(char *ISOFileName);
void CDVDclose();
//int CDVDreadTrack(cdvdLoc *Time);
int CDVDreadTrack(unsigned int lsn);
int CDVDwriteTrack(unsigned int lsn);
unsigned char* CDVDgetBuffer();
int CDVDgetTN(cdvdTN *Buffer);
int CDVDgetTD(unsigned char Track, cdvdLoc *Buffer);
#ifdef __cplusplus
}
#endif // __cplusplus