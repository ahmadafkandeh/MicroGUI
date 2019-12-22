#ifndef __HEAP_MANAGER_H__
#define __HEAP_MANAGER_H__
#include "OSAL.h"
#include <stdlib.h>
extern  void * 	manager_HeapAlloc(unsigned int NeededSize);
extern  void		manager_HeapFree(void * address);
//-----------------------------------------------------------
#endif
