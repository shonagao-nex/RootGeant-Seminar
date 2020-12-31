#ifndef GetRandomSeed_h 
#define GetRandomSeed_h 1 

#ifdef __cplusplus
extern "C" {
#endif

  int   GetIntFromKernelEntropyPool( void );
  short GetShortFromKernelEntropyPool( void );
  long  GetLongFromKernelEntropyPool( void ); 

#ifdef __cplusplus
}
#endif

#endif
