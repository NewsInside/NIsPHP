#ifndef _PS2_INIT_H_
#define _PS2_INIT_H_

#include <tamtypes.h>
#include <kernel.h>
#include <fileio.h>
#include <malloc.h>
#include <sifrpc.h>
#include <stdio.h>
#include <sbv_patches.h>

extern void PS2_Init();
extern void PS2_Load_Modules();
extern void PS2_Delay(int count);

#endif
