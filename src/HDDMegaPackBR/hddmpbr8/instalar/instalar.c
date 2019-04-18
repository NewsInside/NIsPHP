/*
# PS2 HDD MegaPack BR - Programa de Instalacao
#----------------------------------------------------------
# Copyright 04/2006, Bruno Freitas - bootsector@ig.com.br
# PS2 HDD MegaPack BR Copyright by Thiago Ataide (thataide)
# Licenced under Academic Free License version 2.0
# Review LICENSE file for further details.
*/

#include <kernel.h>
#include <sifrpc.h>
#include <libhdd.h>
#include <debug.h>
#include <malloc.h>
#include <fileXio_rpc.h>
#include <loadfile.h>
#include <fileio.h>
#include <string.h>
#include <libmc.h>
#include "cdvd_rpc.h"

#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

// Modos de Instalacao:
#define DEV1    0 // "DEV1"
#define DEV2    1 // "DEV2/CDBOOT"
#define EXPLOIT 2 // "EXPLOIT"

// Sistema do PS2 (para modo EXPLOIT)
#define EUR 0
#define USA 1
#define JPN 2

// Dados a serem modificados para cada versao/sistema:
#define MODO_INSTALACAO EXPLOIT
#define SISTEMA_PS2 JPN // Sem efeito caso MODO_INSTALACAO != EXPLOIT
const char *versao_megapack = "8 - EXPLOIT JPN";
const char *versao_instalador = "1.21";

int fileMode =  FIO_S_IRUSR | FIO_S_IWUSR | FIO_S_IXUSR | FIO_S_IRGRP | FIO_S_IWGRP | FIO_S_IXGRP | FIO_S_IROTH | FIO_S_IWOTH | FIO_S_IXOTH;

void carregaModulos(void);
int formataBoot(void);
int criaDiretorio(char *diretorio);
int copiaArquivo(char *origem, char *destino);
int verificaMC(void);
int instalaBootLoader(void);
int instalaExploit(void);

#include "modulos.h"
#include "instalar.h"

int main()
{   
   SifInitRpc(0); 
   
   init_scr();

   scr_printf("PS2 HDD MegaPack BR %s - Programa de Instalacao v%s\n", versao_megapack, versao_instalador);
   scr_printf("(C)06/2006 por: Thiago Ataide (thataide)\n");
   scr_printf("                Bruno Freitas (bootsector)\n\n");
   
   scr_printf("O MEGAPACK BR EH GRATUITO! SE VOCE PAGOU POR ISSO, VOCE FOI ENGANADO!\n\n");
   
   scr_printf("Carregando modulos... ");
   carregaModulos();
   scr_printf("OK\n\n");
   
   scr_printf("Detectando o HDD do PS2... ");
   
   if(hddCheckPresent() == 0)
      scr_printf("OK\n\n");
   else {
      scr_printf("\nErro! HDD nao encontrado. Instalacao abortada!\n\n");
      SleepThread();
   }
   
   if(MODO_INSTALACAO != DEV2) {
      scr_printf("Detectando o Memory Card... ");
      if (verificaMC() == 0)
         scr_printf("OK\n\n");
      else {
         scr_printf("\nErro! Memory Card nao detectado. Instalacao abortada!\n\n");
         SleepThread();
      }   
   }
   
   scr_printf("Verificando formatacao existente no HDD...\n");
   
   if(hddCheckFormatted() < 0) {
      scr_printf("HDD nao formatado. Aguarde! Formatando HDD do PS2... ");
      
      if(hddFormat() == 0) {
         scr_printf("OK\n\n");
      } else {
         scr_printf("\nErro! Nao foi possivel formatar o HDD. Instalacao abortada!\n\n");
         SleepThread();
      }
   } else {
      scr_printf("HDD ja formatado! Formatando a particao __boot... ");
      
      if(formataBoot() < 0) {
         scr_printf("\nErro! Nao foi possivel formatar a particao __boot. Instalacao abortada!\n\n");
         SleepThread();
      } else
         scr_printf("OK\n\n");
   }   
         
   scr_printf("Acessando particao __boot para iniciar copia de arquivos... ");
   
   if(fileXioMount("pfs0:", "hdd0:__boot", FIO_MT_RDWR) < 0) {
      scr_printf("\nErro! Nao foi possivel acessar  __boot. Instalacao abortada!\n\n");
      SleepThread();
   } else
      scr_printf("OK\n\n");
   
   scr_printf("Instalando o PS2 HDD MegaPack BR %s! Aguarde...\n", versao_megapack);

   instalaMegaPack();
   
   //scr_printf("OK\n\n");
   
   if(MODO_INSTALACAO == DEV1) {
      scr_printf("Instalando Boot Loader no Memory Card (DEV1)... ");

      if(instalaBootLoader() >= 0)
         scr_printf("OK\n\n");
      else {
         scr_printf("\nErro! Nao foi possivel instalar o Boot Loader no Memory Card. Verifique\n");
         scr_printf("se o Memory Card esta conectado e se o mesmo possui espaco suficiente!\n");
         scr_printf("Instalacao abortada!\n");
         SleepThread();
      }
   } else if(MODO_INSTALACAO == EXPLOIT) {
      scr_printf("Instalando EXPLOIT no Memory Card... ");
      
      if(instalaExploit() >= 0)
         scr_printf("OK\n\n");
      else {
         scr_printf("\nErro! Nao foi possivel instalar o Exploit no Memory Card. Verifique se\n");
         scr_printf("o Memory Card esta conectado e se o mesmo possui espaco suficiente!\n");
         scr_printf("Instalacao abortada!\n");
         SleepThread();
      }
   } else {
      // Como nao eh possivel para o LaunchElf carregar o arquivo de confi-
      // guracao do HD se o metodo de boot for o DEV2, tentamos a copia do
      // LAUNCHELF.CNF para o Memory Card
      
      //criaDiretorio("mc0:/SYS-CONF");
      //copiaArquivo("cdfs:/APPS/LAUNCHELF.CNF", "mc0:/SYS-CONF/LAUNCHELF.CNF");
   }

   scr_printf("Instalacao concluida com sucesso! Retire o CD de instalacao e reinicie o PS2\n");

   fileXioUmount("pfs0:");
   
   SleepThread();
   
   return 0;
}

void poweroffHandler(int i)
{
   hddPowerOff();
}

void carregaModulos(void) {
   static char hddarg[] = "-o" "\0" "4" "\0" "-n" "\0" "20";
   static char pfsarg[] = "-m" "\0" "4" "\0" "-o" "\0" "10" "\0" "-n" "\0" "40";
   int ret;
   //int i = 0;
              
   // Modulos para acesso ao Memory Card
   SifLoadModule("rom0:SIO2MAN", 0, NULL);
   SifLoadModule("rom0:MCMAN", 0, NULL);
   SifLoadModule("rom0:MCSERV", 0, NULL);
   mcInit(MC_TYPE_MC);
   
   // Modulos para acesso ao DVD-ROM
   SifExecModuleBuffer(&cdvd_irx, size_cdvd_irx, 0, NULL, &ret);
   CDVD_Init();
   
   // Modulos para acesso ao Disco Rigido
   //hddSetUserPoweroffCallback((void *)poweroffHandler, (void *)i);
   SifExecModuleBuffer(&poweroff_irx, size_poweroff_irx, 0, NULL, &ret);
   SifExecModuleBuffer(&iomanx_irx, size_iomanx_irx, 0, NULL, &ret);
   SifExecModuleBuffer(&filexio_irx, size_filexio_irx, 0, NULL, &ret);
   SifExecModuleBuffer(&ps2dev9_irx, size_ps2dev9_irx, 0, NULL, &ret);
   SifExecModuleBuffer(&ps2atad_irx, size_ps2atad_irx, 0, NULL, &ret);
   SifExecModuleBuffer(&ps2hdd_irx, size_ps2hdd_irx, sizeof(hddarg), hddarg, &ret);
   SifExecModuleBuffer(&ps2fs_irx, size_ps2fs_irx, sizeof(pfsarg), pfsarg, &ret);
   
   hddPreparePoweroff();
}

int formataBoot(void) {
   int zoneSize = 8192;
   return fileXioFormat("pfs:", "hdd0:__boot", (char *)&zoneSize, sizeof(int));
}

int criaDiretorio(char *diretorio) {
   int retorno;
   
   if(!strncmp(diretorio, "mc", 2)) {
      mcSync(0,NULL,NULL);
      mcMkDir(diretorio[2]-'0', 0, diretorio + 4);
      mcSync(0,NULL,&retorno);
   } else {
      retorno = fileXioMkdir(diretorio, O_WRONLY | O_TRUNC | O_CREAT);
   }   
   
   return retorno;
}

int copiaArquivo(char *origem, char *destino) {
   int tamBuffer = 0x100000;
   char *buffer = NULL;
   int in, out, dummy;
   size_t tamanho, tam_escrito;
   
   // Define tamanho do buffer de copia, de acordo com o tipo de origem/destino
   if(!strncmp(destino, "mc", 2))
      tamBuffer = 125000;
   else if(!strncmp(origem, "mc",2))
      tamBuffer = 200000;
   
   // Abre arquivo de origem
   in = fileXioOpen(origem, O_RDONLY, fileMode);
   if(in >= 0) {
      tamanho = fileXioLseek(in,0,SEEK_END);
      fileXioLseek(in,0,SEEK_SET);
   } else
      return in;

   if(tamanho < tamBuffer)
       tamBuffer = tamanho;   
   
   // Aloca o buffer para copia
   buffer = (char*)malloc(tamBuffer);
   if(buffer == NULL) {
      tamBuffer = 32768;
      buffer = (char*)malloc(tamBuffer);
   }
   
   // Cria arquivo destino
   fileXioRemove(destino);
   out = fileXioOpen(destino, O_WRONLY|O_TRUNC|O_CREAT, fileMode);
   if(out < 0) {
      fileXioClose(in);
      free(buffer);
      return out;
   }   
                        
   while (tamanho > 0) {
      tamBuffer = fileXioRead(in, buffer, tamBuffer);

      tam_escrito = fileXioWrite(out, buffer, tamBuffer);

      if (tamBuffer != tam_escrito) {
         fileXioClose(in);
         fileXioClose(out);
         fileXioRemove(destino);
         free(buffer);
         return -1;
      }
      
      tamanho -= tamBuffer;
   }
   
   if(!strncmp(destino, "mc", 2))
      mcSync(0, NULL, &dummy);
   
   free(buffer); 
   fileXioClose(in);
   fileXioClose(out);
   
   return 0;
}

int verificaMC(void) {
   int tipo, espaco_livre, formato, retorno, dummy;
   retorno = mcGetInfo(0, 0, &tipo, &espaco_livre, &formato);
   mcSync(0, NULL, &dummy);
   return retorno;
}

int instalaBootLoader(void) {
   int ret;
   
   criaDiretorio("mc0:/BOOT");

   ret = copiaArquivo("cdfs:/APPS/BOOT.ELF", "mc0:/BOOT/BOOT.ELF");
   if(ret < 0) return ret;
   ret = copiaArquivo("cdfs:/APPS/BOOT.ICN", "mc0:/BOOT/BOOT.icn");
   if(ret < 0) return ret;
   ret = copiaArquivo("cdfs:/APPS/ICON.SYS", "mc0:/BOOT/icon.sys");
   
   return ret;
}

int instalaExploit(void) {
   int ret;
   
   if(SISTEMA_PS2 == USA)
      criaDiretorio("mc0:/BADATA-SYSTEM");
   else if(SISTEMA_PS2 == EUR)
      criaDiretorio("mc0:/BEDATA-SYSTEM");
   else
      criaDiretorio("mc0:/BIDATA-SYSTEM");

   if(SISTEMA_PS2 == USA) {
      ret = copiaArquivo("cdfs:/EXPLOIT/BOOT.ELF", "mc0:/BADATA-SYSTEM/BOOT.ELF");
      if(ret < 0) return ret;
      ret = copiaArquivo("cdfs:/EXPLOIT/LAUNCHELF.CNF", "mc0:/BADATA-SYSTEM/LAUNCHELF.CNF");
      if(ret < 0) return ret;
      ret = copiaArquivo("cdfs:/EXPLOIT/SKIN.JPG", "mc0:/BADATA-SYSTEM/SKIN.JPG");
      if(ret < 0) return ret;
      ret = copiaArquivo("cdfs:/EXPLOIT/TITLE.DB", "mc0:/BADATA-SYSTEM/TITLE.DB");
      if(ret < 0) return ret;
   } else if(SISTEMA_PS2 == EUR) {
      ret = copiaArquivo("cdfs:/EXPLOIT/BOOT.ELF", "mc0:/BEDATA-SYSTEM/BOOT.ELF");
      if(ret < 0) return ret;
      ret = copiaArquivo("cdfs:/EXPLOIT/LAUNCHELF.CNF", "mc0:/BEDATA-SYSTEM/LAUNCHELF.CNF");
      if(ret < 0) return ret;
      ret = copiaArquivo("cdfs:/EXPLOIT/SKIN.JPG", "mc0:/BEDATA-SYSTEM/SKIN.JPG");
      if(ret < 0) return ret;
      ret = copiaArquivo("cdfs:/EXPLOIT/TITLE.DB", "mc0:/BEDATA-SYSTEM/TITLE.DB");
      if(ret < 0) return ret;
   } else {
      ret = copiaArquivo("cdfs:/EXPLOIT/BOOT.ELF", "mc0:/BIDATA-SYSTEM/BOOT.ELF");
      if(ret < 0) return ret;
      ret = copiaArquivo("cdfs:/EXPLOIT/LAUNCHELF.CNF", "mc0:/BIDATA-SYSTEM/LAUNCHELF.CNF");
      if(ret < 0) return ret;
      ret = copiaArquivo("cdfs:/EXPLOIT/SKIN.JPG", "mc0:/BIDATA-SYSTEM/SKIN.JPG");
      if(ret < 0) return ret;
      ret = copiaArquivo("cdfs:/EXPLOIT/TITLE.DB", "mc0:/BIDATA-SYSTEM/TITLE.DB");
      if(ret < 0) return ret;
   }
 
   return ret;
}
