
#ifndef __OSFUNC_H__
#define __OSFUNC_H__
#include "OSDef.h"
#include "Heapmanager.h"
#ifdef __cplusplus
 extern "C" {
#endif

/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
OS_CreateQueue Function
*used for create a queue
*Args:
*ptrToQueueHandle: this is the pointer of Queue's Handler.
*QueueLenth: The maximum number of items that the queue can contain.
*ItemSize: The number of bytes each item in the queue will require.
*					 Each item on the queue must be the same size.
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
extern void OS_CreateQueue (OS_QueueHandle * ptrToQueueHandle ,
														OS_QueueSize queuelenth ,
														OS_QueueSize itemsize);
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
OS_DeleteQueue Function
*Deletes queues by their Handle.
*Args:
*Handle: Handle of queue.
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
extern void OS_DeleteQueue (OS_QueueHandle Handle);
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
OS_PostQueue Function
*Post an item on a queue. The item is queued by copy, not by reference.
*Rturnes OS_QueueTrue if the item was successfully posted, otherwise OS_QueueERR_Full.
*Args:
*Handle: Handle of queue.
*Item: A pointer to the item that is to be placed on the queue.
*TimeToWait: The maximum amount of time the task should block waiting for space to become
* 						available on the queue, should it already be full. The call will return immediately if this
*							is set to 0.
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
extern OS_QueueReturnType OS_PostQueue(
														OS_QueueHandle Handle ,
														OS_QueueItemToPost Item ,
														OS_TickType TimeToWait );		
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
OS_PostQueueFromISR Function
*Post an item on a queue From a ISR. The item is queued by copy, not by reference.
*Rturnes OS_QueueTrue if the item was successfully posted, otherwise OS_QueueERR_Full.
*Args:
*Handle: Handle of queue.
*Item: A pointer to the item that is to be placed on the queue.
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
extern void OS_PostQueueFromISR(
													OS_QueueHandle Handle ,
													OS_QueueItemToPost Item);											
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
OS_ReadQueue Function
*Receive an item from a queue. The item is received by copy so a buffer of adequate size must be provided.
*			The number of bytes copied into the buffer was defined when the queue was created.
*Args:
*Handle: The handle to the queue from which the item is to be received.
*Item: Pointer to the buffer into which the received item will be copied.
*TimeToWait: The maximum amount of time the task should block waiting for an item to receive
*			should the queue be empty at the time of the call.
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
extern OS_QueueReturnType OS_ReadQueue(OS_QueueHandle Handle , 
														OS_QueueItemToReceive Item ,
														OS_TickType TimeToWait );
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
OS_ReadQueueFromISR Function
*Receive an item from a queue From An ISR . The item is received by copy so a buffer of adequate size must be provided.
*			The number of bytes copied into the buffer was defined when the queue was created.
*Args:
*Handle: The handle to the queue from which the item is to be received.
*Item: Pointer to the buffer into which the received item will be copied.
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
extern OS_QueueReturnType OS_ReadQueueFromISR(OS_QueueHandle Handle , 
														OS_QueueItemToReceive Item );
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
*OS_CreateTask Function
*Create a new task and add it to the list of tasks that are ready to run.
*Args:
*ptrToTaskHandle: this is the Handle Of Task
*TaskFunc: Pointer to the task entry function.
*TaskName: A descriptive name for the task.
*TaskPriority: The priority at which the task should run.
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
extern OS_TaskReturnType OS_CreateTask(OS_TaskHandle ptrToTaskHandle ,
																	OS_TaskFunc TaskFunc ,
																	signed char* TaskName , 
																	OS_TaskPriority TaskPriority);
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
*OS_DeleteTask Function
*Remove a task
*Args:
*TaskHandle: The handle of the task to be deleted. 
							Passing NULL will cause the calling task to be deleted.
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/		
extern void OS_DeleteTask(OS_TaskHandle TaskHandle);
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
*OS_TaskDelay Function
*Delay a task for a given number of ticks
*Args:
*Delay: The amount of time, in tick periods, that the calling task should block
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/	
extern void OS_DelayTask(OS_TickType Delay);
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
*OS_Run Function
*Start the OS
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
extern void OS_Run(void);
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
*OS_DisableInterrupts Function
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
extern void OS_DisableInterrupts(void);
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
*OS_EnableInterrupts Function
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
extern void OS_EnableInterrupts(void);
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
*
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
#if(OS_ManagesHeap==1)
extern void * OS_HeapAlloc(OS_Size neededSize);
#endif
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
*
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
#if(OS_ManagesHeap==1)
extern void OS_HeapFree(void * address);
#endif

#ifdef __cplusplus
}
#endif
#endif
