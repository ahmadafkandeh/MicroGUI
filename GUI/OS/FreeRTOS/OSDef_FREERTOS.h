#ifndef __OSDEF_FREERTOS_H__
#define __OSDEF_FREERTOS_H__

	#include "freertos.h"
	#include "task.h"
	#include "queue.h"
	#include "semphr.h"

//global Definitions
#define OS_TickType			portTickType
#define OS_False				pdFALSE
#define OS_True					pdTRUE
#define OS_Size					unsigned int

//Queue:
#define OS_QueueHandle 				xQueueHandle
#define OS_QueueLenth					portBASE_TYPE
#define OS_QueueSize					portBASE_TYPE
#define OS_QueueItemToPost		const void *
#define OS_QueueItemToReceive void *
#define OS_QueueReturnType 		portBASE_TYPE
#define OS_QueueTrue					pd_True
#define OS_QueueERR_Full			errQUEUE_FULL


//Task:
#define OS_TaskHandle			xTaskHandle
#define OS_TaskFunc				pdTASK_CODE
#define OS_TaskPriority		portBASE_TYPE
#define OS_TaskReturnType	portBASE_TYPE

#endif
