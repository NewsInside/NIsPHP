#ifndef __PS2_H
#define __PS2_H

#include "ps2time.h"

extern PS2Time timer;

/*
#define localtime(a)  a=timer.getLocaltime()
#define time(a)   a=timer.getTime()
*/

#define localtime(a) timer.getLocaltime(a)
#define time(a) timer.getTime(a)


#endif
