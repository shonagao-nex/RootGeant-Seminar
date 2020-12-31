#include "GetRandomSeed.hh"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> 
#include <stdio.h>

const char * const device = "/dev/random";

int GetIntFromKernelEntropyPool( void )
{
  int fd=open(device,O_RDONLY);
  if(fd==-1)
    perror( "Entropy Pool Open" );
  int ret;
  if(read(fd,&ret,sizeof(int))!=sizeof(int))
    perror( "Entropy Pool Read" );
  close(fd);
  return ret;
}

short GetShortFromKernelEntropyPool( void )
{
  int fd=open(device,O_RDONLY);
  if(fd==-1)
    perror( "Entropy Pool Open" );
  short ret;
  if(read(fd,&ret,sizeof(short))!=sizeof(short))
    perror( "Entropy Pool Read" );
  close(fd);
  return ret;
}

long GetLongFromKernelEntropyPool( void )
{
  int fd=open(device,O_RDONLY);
  if(fd==-1)
    perror( "Entropy Pool Open" );
  long ret;
  if(read(fd,&ret,sizeof(long))!=sizeof(long))
    perror( "Entropy Pool Read" );
  close(fd);
  return ret;
}
