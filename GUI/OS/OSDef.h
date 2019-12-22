#ifndef __OSDEF_H__
#define __OSDEF_H__
#include "OSInclude.h"
//include Os Definitions
//the definitions included to Os Files folder
#ifdef OS_FREERTOS
	#include "OSDef_FREERTOS.h"
#else 
	#warning "art"
#endif

#endif
