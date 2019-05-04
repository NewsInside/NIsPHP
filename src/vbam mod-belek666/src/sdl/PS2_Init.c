#include <tamtypes.h>
#include <string.h>
#include <kernel.h>
#include <fileio.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <stdlib.h>
#include <stdio.h>
#include <loadfile.h>

#include <sbv_patches.h>

// external IRX modules
extern u8 *usbd_irx;
extern int size_usbd_irx;

extern u8 *usbhdfsd_irx;
extern int size_usbhdfsd_irx;


void PS2_Delay(int count) {
   int i, ret;
   for (i = 0; i < count; i++) {
      ret = 0x01000000;
      while ( ret-- ) {
         asm("nop\nnop\nnop\nnop");
      }
   }
}

void PS2_LoadModules(void)
{
   int ret;
   
   /*ret = SifLoadModule("rom0:SIO2MAN", 0, NULL);
   if (ret < 0) {
      printf("Failed to load module: SIO2MAN\n");
   }*/

   ret = SifLoadModule("rom0:MCMAN", 0, NULL);
	if (ret < 0) {
      printf("Failed to load module: MCMAN\n");
   }
	
   ret = SifLoadModule("rom0:MCSERV", 0, NULL);
   if (ret < 0) {
      printf("Failed to load module: MCSERV\n");
   }

   /*ret = SifLoadModule("rom0:PADMAN", 0, NULL);
	if (ret < 0) {
      printf("Failed to load module: PADMAN\n");
   } */
   
   ret = SifLoadModule("rom0:LIBSD", 0, NULL);
   if (ret < 0) {
      printf("Failed to load module: LIBSD\n");
   }
   
   SifExecModuleBuffer(&usbd_irx, size_usbd_irx, 0, NULL, &ret);
   if (ret < 0) {
      printf("Failed to load module: USBD.IRX :(\n");
   }
   
   SifExecModuleBuffer(&usbhdfsd_irx, size_usbhdfsd_irx, 0, NULL, &ret);
   if (ret < 0) {
      printf("Failed to load module: USBHDFSD.IRX \n");
   }
}

void PS2_Init(void)
{
   // KarasQ: PS2 init
   fioExit();
	SifExitIopHeap();
	SifLoadFileExit();
	SifExitRpc();
		
   SifIopReset("rom0:UDNL rom0:EELOADCNF", 0); 
   while ( SifIopSync() );
   //..
   
   SifInitRpc(0);
   
   sbv_patch_enable_lmb();          // not sure we really need to do this again
   sbv_patch_disable_prefix_check();// here, but will it do any harm?
	
   PS2_LoadModules();
   PS2_Delay(5);       //KarasQ: we have to wait a while
}

