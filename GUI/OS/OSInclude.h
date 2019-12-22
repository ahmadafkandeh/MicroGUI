//include OS Files
#ifndef __OSINCLUDE_H__
#define __OSINCLUDE_H__
#include "OSAL.h"

#ifdef OS_FREERTOS
	#include "freertos.h"
	#include "task.h"
	#include "queue.h"
	#include "semphr.h"
#endif

#endif
