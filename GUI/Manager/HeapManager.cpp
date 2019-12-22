#include "HeapManager.h"
#include "OSFunc.h"
void * manager_HeapAlloc(unsigned int NeededSize)
{
	#if (OS_ManagesHeap==1)
		return OS_HeapAlloc(NeededSize);
	#else
		return malloc(NeededSize);
	#endif
}
void manager_HeapFree(void * address)
{
	#if (OS_ManagesHeap==1)
		OS_HeapFree(address);
	#else
		free(address);
	#endif
}
