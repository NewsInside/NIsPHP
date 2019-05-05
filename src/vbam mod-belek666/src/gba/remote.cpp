#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef _EE
#ifndef _WIN32
# include <unistd.h>
# include <sys/socket.h>
# include <netdb.h>
# ifdef HAVE_NETINET_IN_H
#  include <netinet/in.h>
# endif // HAVE_NETINET_IN_H
# ifdef HAVE_ARPA_INET_H
#  include <arpa/inet.h>
# else // ! HAVE_ARPA_INET_H
#  define socklen_t int
# endif // ! HAVE_ARPA_INET_H
# define SOCKET int
#else // _WIN32
# include <winsock.h>
# include <io.h>
# define socklen_t int
# define close closesocket
# define read _read
# define write _write
#endif // _WIN32
#endif // _EE

#include "GBA.h"

#ifndef _EE
extern bool debugger;
extern void CPUUpdateCPSR();
#ifdef SDL
extern void (*dbgMain)();
extern void debuggerMain();
extern void debuggerSignal(int,int);
#endif

int remotePort = 55555;
int remoteSignal = 5;
SOCKET remoteSocket = -1;
SOCKET remoteListenSocket = -1;
bool remoteConnected = false;
bool remoteResumed = false;

int (*remoteSendFnc)(char *, int) = NULL;
int (*remoteRecvFnc)(char *, int) = NULL;
bool (*remoteInitFnc)() = NULL;
void (*remoteCleanUpFnc)() = NULL;

#ifndef SDL
void remoteSetSockets(SOCKET l, SOCKET r)
{
  remoteSocket = r;
  remoteListenSocket = l;
}
#endif
#endif // _EE

int remoteTcpSend(char *data, int len)
{
   #ifndef _EE
      return send(remoteSocket, data, len, 0);
   #else
      return -1;
   #endif // _EE
}

int remoteTcpRecv(char *data, int len)
{
   #ifndef _EE
      return recv(remoteSocket, data, len, 0);
   #else
      return -1;
   #endif // _EE
}

bool remoteTcpInit()
{
#ifndef _EE
  if(remoteSocket == -1) {
#ifdef _WIN32
    WSADATA wsaData;
    int error = WSAStartup(MAKEWORD(1,1),&wsaData);
#endif // _WIN32
    SOCKET s = socket(PF_INET, SOCK_STREAM, 0);

    remoteListenSocket = s;

    if(s < 0) {
      fprintf(stderr,"Error opening socket\n");
      exit(-1);
    }
    int tmp = 1;
    setsockopt (s, SOL_SOCKET, SO_REUSEADDR, (char *) &tmp, sizeof (tmp));

    //    char hostname[256];
    //    gethostname(hostname, 256);

    //    hostent *ent = gethostbyname(hostname);
    //    unsigned long a = *((unsigned long *)ent->h_addr);

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(remotePort);
    addr.sin_addr.s_addr = htonl(0);
    int count = 0;
    while(count < 3) {
      if(bind(s, (sockaddr *)&addr, sizeof(addr))) {
        addr.sin_port = htons(ntohs(addr.sin_port)+1);
      } else
        break;
    }
    if(count == 3) {
      fprintf(stderr,"Error binding \n");
      exit(-1);
    }

    fprintf(stderr,"Listening for a connection at port %d\n",
            ntohs(addr.sin_port));

    if(listen(s, 1)) {
      fprintf(stderr, "Error listening\n");
      exit(-1);
    }
    socklen_t len = sizeof(addr);

#ifdef _WIN32
    int flag = 0;
    ioctlsocket(s, FIONBIO, (unsigned long *)&flag);
#endif // _WIN32
    SOCKET s2 = accept(s, (sockaddr *)&addr, &len);
    if(s2 > 0) {
      fprintf(stderr, "Got a connection from %s %d\n",
              inet_ntoa((in_addr)addr.sin_addr),
              ntohs(addr.sin_port));
    } else {
#ifdef _WIN32
      int error = WSAGetLastError();
#endif // _WIN32
    }
    char dummy;
    recv(s2, &dummy, 1, 0);
    if(dummy != '+') {
      fprintf(stderr, "ACK not received\n");
      exit(-1);
    }
    remoteSocket = s2;
    //    close(s);
  }
  return true;
#else
  return false;
#endif // _EE
}

void remoteTcpCleanUp()
{
#ifndef _EE
  if(remoteSocket > 0) {
    fprintf(stderr, "Closing remote socket\n");
    close(remoteSocket);
    remoteSocket = -1;
  }
  if(remoteListenSocket > 0) {
    fprintf(stderr, "Closing listen socket\n");
    close(remoteListenSocket);
    remoteListenSocket = -1;
  }
#endif // _EE
}

int remotePipeSend(char *data, int len)
{
#ifndef _EE
  int res = write(1, data, len);
  return res;
#else
  return -1;
#endif // _EE
}


int remotePipeRecv(char *data, int len)
{
#ifndef _EE
  int res = read(0, data, len);
  return res;
#else
  return -1;
#endif // _EE
}

bool remotePipeInit()
{
#ifndef _EE
  char dummy;
  if (read(0, &dummy, 1) == 1)
  {
    if(dummy != '+') {
      fprintf(stderr, "ACK not received\n");
      exit(-1);
    }
  }

  return true;
#else
  return false;
#endif // _EE
}

void remotePipeCleanUp()
{
}

void remoteSetPort(int port)
{
#ifndef _EE
  remotePort = port;
#endif // _EE
}

void remoteSetProtocol(int p)
{
#ifndef _EE
  if(p == 0) {
    remoteSendFnc = remoteTcpSend;
    remoteRecvFnc = remoteTcpRecv;
    remoteInitFnc = remoteTcpInit;
    remoteCleanUpFnc = remoteTcpCleanUp;
  } else {
    remoteSendFnc = remotePipeSend;
    remoteRecvFnc = remotePipeRecv;
    remoteInitFnc = remotePipeInit;
    remoteCleanUpFnc = remotePipeCleanUp;
  }
#endif // _EE
}

void remoteInit()
{
#ifndef _EE
  if(remoteInitFnc)
    remoteInitFnc();
#endif // _EE
}

void remotePutPacket(const char *packet)
{
#ifndef _EE
  const char *hex = "0123456789abcdef";
  char buffer[1024];

  size_t count = strlen(packet);

  unsigned char csum = 0;

  char *p = buffer;
  *p++ = '$';

  for(size_t i = 0 ;i < count; i++) {
    csum += packet[i];
    *p++ = packet[i];
  }
  *p++ = '#';
  *p++ = hex[csum>>4];
  *p++ = hex[csum & 15];
  *p++ = 0;
  //  printf("Sending %s\n", buffer);
  remoteSendFnc(buffer, (int)count + 4);

  char c = 0;
  remoteRecvFnc(&c, 1);
  /*
  if(c == '+')
    printf("ACK\n");
  else if(c=='-')
    printf("NACK\n");
  */
#endif // _EE
}

#define debuggerReadMemory(addr) \
  (*(u32*)&map[(addr)>>24].address[(addr) & map[(addr)>>24].mask])

#define debuggerReadHalfWord(addr) \
  (*(u16*)&map[(addr)>>24].address[(addr) & map[(addr)>>24].mask])

#define debuggerReadByte(addr) \
  map[(addr)>>24].address[(addr) & map[(addr)>>24].mask]

#define debuggerWriteMemory(addr, value) \
  *(u32*)&map[(addr)>>24].address[(addr) & map[(addr)>>24].mask] = (value)

#define debuggerWriteHalfWord(addr, value) \
  *(u16*)&map[(addr)>>24].address[(addr) & map[(addr)>>24].mask] = (value)

#define debuggerWriteByte(addr, value) \
  map[(addr)>>24].address[(addr) & map[(addr)>>24].mask] = (value)

void remoteOutput(const char *s, u32 addr)
{
#ifndef _EE
  char buffer[16384];

  char *d = buffer;
  *d++ = 'O';

  if(s) {
    char c = *s++;
    while(c) {
      sprintf(d, "%02x", c);
      d += 2;
      c = *s++;
    }
  } else {
    char c= debuggerReadByte(addr);
    addr++;
    while(c) {
      sprintf(d, "%02x", c);
      d += 2;
      c = debuggerReadByte(addr);
      addr++;
    }
  }
  remotePutPacket(buffer);
  //  fprintf(stderr, "Output sent %s\n", buffer);
#endif // _EE
}

void remoteSendSignal()
{
#ifndef _EE
  char buffer[1024];
  sprintf(buffer, "S%02x", remoteSignal);
  remotePutPacket(buffer);
#endif // _EE
}

void remoteSendStatus()
{
#ifndef _EE
  char buffer[1024];
  sprintf(buffer, "T%02x", remoteSignal);
  char *s = buffer;
  s += 3;
  for(int i = 0; i < 15; i++) {
    u32 v = reg[i].I;
    sprintf(s, "%02x:%02x%02x%02x%02x;",i,
            (v & 255),
            (v >> 8) & 255,
            (v >> 16) & 255,
            (v >> 24) & 255);
    s += 12;
  }
  u32 v = armNextPC;
  sprintf(s, "0f:%02x%02x%02x%02x;", (v & 255),
          (v >> 8) & 255,
          (v >> 16) & 255,
          (v >> 24) & 255);
  s += 12;
  CPUUpdateCPSR();
  v = reg[16].I;
  sprintf(s, "19:%02x%02x%02x%02x;", (v & 255),
          (v >> 8) & 255,
          (v >> 16) & 255,
          (v >> 24) & 255);
  s += 12;
  *s = 0;
  //  printf("Sending %s\n", buffer);
  remotePutPacket(buffer);
#endif // _EE
}

void remoteBinaryWrite(char *p)
{
#ifndef _EE
  u32 address;
  int count;
  sscanf(p,"%x,%x:", &address, &count);
  //  printf("Binary write for %08x %d\n", address, count);

  p = strchr(p, ':');
  p++;
  for(int i = 0; i < count; i++) {
    u8 b = *p++;
    switch(b) {
    case 0x7d:
      b = *p++;
      debuggerWriteByte(address, (b^0x20));
      address++;
      break;
    default:
      debuggerWriteByte(address, b);
      address++;
      break;
    }
  }
  //  printf("ROM is %08x\n", debuggerReadMemory(0x8000254));
  remotePutPacket("OK");
#endif // _EE
}

void remoteMemoryWrite(char *p)
{
#ifndef _EE
  u32 address;
  int count;
  sscanf(p,"%x,%x:", &address, &count);
  //  printf("Memory write for %08x %d\n", address, count);

  p = strchr(p, ':');
  p++;
  for(int i = 0; i < count; i++) {
    u8 v = 0;
    char c = *p++;
    if(c <= '9')
      v = (c - '0') << 4;
    else
      v = (c + 10 - 'a') << 4;
    c = *p++;
    if(c <= '9')
      v += (c - '0');
    else
      v += (c + 10 - 'a');
    debuggerWriteByte(address, v);
    address++;
  }
  //  printf("ROM is %08x\n", debuggerReadMemory(0x8000254));
  remotePutPacket("OK");
#endif // _EE
}

void remoteMemoryRead(char *p)
{
#ifndef _EE
  u32 address;
  int count;
  sscanf(p,"%x,%x:", &address, &count);
  //  printf("Memory read for %08x %d\n", address, count);

  char buffer[1024];

  char *s = buffer;
  for(int i = 0; i < count; i++) {
    u8 b = debuggerReadByte(address);
    sprintf(s, "%02x", b);
    address++;
    s += 2;
  }
  *s = 0;
  remotePutPacket(buffer);
#endif // _EE
}

void remoteStepOverRange(char *p)
{
#ifndef _EE
  u32 address;
  u32 final;
  sscanf(p, "%x,%x", &address, &final);

  remotePutPacket("OK");

  remoteResumed = true;
  do {
    CPULoop(1);
    if(debugger)
      break;
  } while(armNextPC >= address && armNextPC < final);

  remoteResumed = false;

  remoteSendStatus();
#endif // _EE
}

void remoteWriteWatch(char *p, bool active)
{
#ifndef _EE
  u32 address;
  int count;
  sscanf(p, ",%x,%x#", &address, &count);

  fprintf(stderr, "Write watch for %08x %d\n", address, count);

  if(address < 0x2000000 || address > 0x3007fff) {
    remotePutPacket("E01");
    return;
  }

  if(address > 0x203ffff && address < 0x3000000) {
    remotePutPacket("E01");
    return;
  }

  u32 final = address + count;

  if(address < 0x2040000 && final > 0x2040000) {
    remotePutPacket("E01");
    return;
  } else if(address < 0x3008000 && final > 0x3008000) {
    remotePutPacket("E01");
    return;
  }

#ifdef BKPT_SUPPORT
  for(int i = 0; i < count; i++) {
    if((address >> 24) == 2)
      freezeWorkRAM[address & 0x3ffff] = active;
    else
      freezeInternalRAM[address & 0x7fff] = active;
    address++;
  }
#endif

  remotePutPacket("OK");
#endif // _EE
}

void remoteReadRegisters(char *p)
{
#ifndef _EE
  char buffer[1024];

  char *s = buffer;
  int i;
  // regular registers
  for(i = 0; i < 15; i++) {
    u32 v = reg[i].I;
    sprintf(s, "%02x%02x%02x%02x",  v & 255, (v >> 8) & 255,
            (v >> 16) & 255, (v >> 24) & 255);
    s += 8;
  }
  // PC
  u32 pc = armNextPC;
  sprintf(s, "%02x%02x%02x%02x", pc & 255, (pc >> 8) & 255,
          (pc >> 16) & 255, (pc >> 24) & 255);
  s += 8;

  // floating point registers (24-bit)
  for(i = 0; i < 8; i++) {
    sprintf(s, "000000000000000000000000");
    s += 24;
  }

  // FP status register
  sprintf(s, "00000000");
  s += 8;
  // CPSR
  CPUUpdateCPSR();
  u32 v = reg[16].I;
  sprintf(s, "%02x%02x%02x%02x",  v & 255, (v >> 8) & 255,
          (v >> 16) & 255, (v >> 24) & 255);
  s += 8;
  *s = 0;
  remotePutPacket(buffer);
#endif // _EE
}

void remoteWriteRegister(char *p)
{
#ifndef _EE
  int r;

  sscanf(p, "%x=", &r);

  p = strchr(p, '=');
  p++;

  char c = *p++;

  u32 v = 0;

  u8 data[4] = {0,0,0,0};

  int i = 0;

  while(c != '#') {
    u8 b = 0;
    if(c <= '9')
      b = (c - '0') << 4;
    else
      b = (c + 10 - 'a') << 4;
    c = *p++;
    if(c <= '9')
      b += (c - '0');
    else
      b += (c + 10 - 'a');
    data[i++] = b;
    c = *p++;
  }

  v = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);

  //  printf("Write register %d=%08x\n", r, v);
  reg[r].I = v;
  if(r == 15) {
    armNextPC = v;
    if(armState)
      reg[15].I = v + 4;
    else
      reg[15].I = v + 2;
  }
  remotePutPacket("OK");
#endif // _EE
}

extern int emulating;

void remoteStubMain()
{
#ifndef _EE
  if(!debugger)
    return;

  if(remoteResumed) {
    remoteSendStatus();
    remoteResumed = false;
  }

  while(1) {
    char buffer[1024];
    int res = remoteRecvFnc(buffer, 1024);

    if(res == -1) {
      fprintf(stderr, "GDB connection lost\n");
#ifdef SDL
      dbgMain = debuggerMain;
      dbgSignal = debuggerSignal;
#endif
      debugger = false;
      break;
    }

    //    fprintf(stderr, "Received %s\n", buffer);
    char *p = buffer;
    char c = *p++;
    char pp = '+';
    remoteSendFnc(&pp, 1);

    if(c != '$')
      continue;
    c= *p++;
    switch(c) {
    case '?':
      remoteSendSignal();
      break;
    case 'D':
      remotePutPacket("OK");
#ifdef SDL
      dbgMain = debuggerMain;
      dbgSignal = debuggerSignal;
#endif
      remoteResumed = true;
      debugger = false;
      return;
    case 'e':
      remoteStepOverRange(p);
      break;
    case 'k':
      remotePutPacket("OK");
#ifdef SDL
      dbgMain = debuggerMain;
      dbgSignal = debuggerSignal;
#endif
      debugger = false;
      emulating = false;
      return;
    case 'C':
      remoteResumed = true;
      debugger = false;
      return;
    case 'c':
      remoteResumed = true;
      debugger = false;
      return;
    case 's':
      remoteResumed = true;
      remoteSignal = 5;
      CPULoop(1);
      if(remoteResumed) {
        remoteResumed = false;
        remoteSendStatus();
      }
      break;
    case 'g':
      remoteReadRegisters(p);
      break;
    case 'P':
      remoteWriteRegister(p);
      break;
    case 'M':
      remoteMemoryWrite(p);
      break;
    case 'm':
      remoteMemoryRead(p);
      break;
    case 'X':
      remoteBinaryWrite(p);
      break;
    case 'H':
      remotePutPacket("OK");
      break;
    case 'q':
      remotePutPacket("");
      break;
    case 'Z':
      if(*p++ == '2') {
        remoteWriteWatch(p, true);
      } else
        remotePutPacket("");
      break;
    case 'z':
      if(*p++ == '2') {
	remoteWriteWatch(p, false);
      } else
	remotePutPacket("");
      break;
    default:
      {
        *(strchr(p, '#') + 3) = 0;
        fprintf(stderr, "Unknown packet %s\n", --p);
        remotePutPacket("");
      }
      break;
    }
  }
#endif // _EE
}

void remoteStubSignal(int sig, int number)
{
#ifndef _EE
  remoteSignal = sig;
  remoteResumed = false;
  remoteSendStatus();
  debugger = true;
#endif // _EE
}

void remoteCleanUp()
{
#ifndef _EE
  if(remoteCleanUpFnc)
    remoteCleanUpFnc();
#endif // _EE
}
