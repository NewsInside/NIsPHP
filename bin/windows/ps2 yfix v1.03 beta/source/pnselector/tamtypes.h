/*      
  _____     ___ ____ 
   ____|   |    ____|      PSX2 OpenSource Project
  |     ___|   |____       (C)2001, Gustavo Scotti (gustavo@scotti.com)
  ------------------------------------------------------------------------
  tamtypes.h
			Common used typedef
*/

#ifndef _TAMTYPES_H_
#define _TAMTYPES_H_ 1


typedef	unsigned char 		u8;
typedef unsigned short 		u16;
typedef unsigned int 		u32;
typedef unsigned long int	u64;

#ifdef _EE
typedef unsigned int		u128 __attribute__(( mode(TI) ));
#endif

typedef signed char 		s8;
typedef signed short 		s16;
typedef	signed int 		s32;
typedef signed long int		s64;

#ifdef _EE
typedef int			s128 __attribute__(( mode(TI) ));
#endif

#ifndef bzero
#define bzero( _str, _n )            memset( _str, '\0', _n )
#endif


#ifndef NULL
#define NULL	(void *)0
#endif

#endif
