#include "OSFunc.H"
void vApplicationTickHook( void );
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
OS_CreateQueue Function
*used for create a queue
*Args:
*ptrToQueueHandle: this is the pointer of Queue's Handler.
*QueueLenth: The maximum number of items that the queue can contain.
*ItemSize: The number of bytes each item in the queue will require.
*					 Each item on the queue must be the same size.
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
void OS_CreateQueue (OS_QueueHandle * ptrToQueueHandle,
											OS_QueueSize queuelenth,
											OS_QueueSize itemsize)
{
	*ptrToQueueHandle=xQueueCreate(queuelenth,itemsize);
}

/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
OS_DeleteQueue Function
*used for Delete a queue
*Args:
*Handle: Handle of queue.
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
void OS_DeleteQueue (OS_QueueHandle Handle)
{
	vQueueDelete( Handle );
}

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
OS_QueueReturnType OS_PostQueue( 
														OS_QueueHandle Handle ,
														OS_QueueItemToPost Item ,
														OS_TickType TimeToWait )
{
		return xQueueSend( Handle, Item, TimeToWait );
}
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
OS_PostQueueFromISR Function
*Post an item on a queue From a ISR. The item is queued by copy, not by reference.
*Rturnes OS_QueueTrue if the item was successfully posted, otherwise OS_QueueERR_Full.
*Args:
*Handle: Handle of queue.
*Item: A pointer to the item that is to be placed on the queue.
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
void OS_PostQueueFromISR( OS_QueueHandle Handle ,
														OS_QueueItemToPost Item)
{
	OS_QueueReturnType x=OS_True;
	int i;
	xQueueSendFromISR( Handle, Item, &x );
	for (i=0;i<2450000;i++);
}
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
OS_QueueReturnType OS_ReadQueue( 
														OS_QueueHandle Handle , 
														OS_QueueItemToReceive Item ,
														OS_TickType TimeToWait )
{
	return xQueueReceive( Handle, Item, TimeToWait);
}
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
OS_ReadQueueFromISR Function
*Receive an item from a queue From An ISR . The item is received by copy so a buffer of adequate size must be provided.
*			The number of bytes copied into the buffer was defined when the queue was created.
*Args:
*Handle: The handle to the queue from which the item is to be received.
*Item: Pointer to the buffer into which the received item will be copied.
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
OS_QueueReturnType OS_ReadQueueFromISR(OS_QueueHandle Handle , 
														OS_QueueItemToReceive Item)
{
	OS_QueueReturnType xTaskWokenByReceive = pdFALSE;
	return xQueueReceiveFromISR( Handle, Item, &xTaskWokenByReceive);
}
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
*OS_TaskCreate Function
*Create a new task and add it to the list of tasks that are ready to run.
*Args:
*ptrToTaskHandle: this is the Handle Of Task
*TaskFunc: Pointer to the task entry function.
*TaskName: A descriptive name for the task.
*TaskPriority: The priority at which the task should run.
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
OS_TaskReturnType OS_CreateTask(OS_TaskHandle ptrToTaskHandle ,
																	OS_TaskFunc TaskFunc ,
																	signed char* TaskName ,
																	OS_TaskPriority TaskPriority)
{
	return xTaskCreate(TaskFunc, TaskName, configMINIMAL_STACK_SIZE,
											(void*)NULL, TaskPriority, &ptrToTaskHandle);
}
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
*OS_DeleteTask Function
*Remove a task
*Args:
*TaskHandle: The handle of the task to be deleted. 
							Passing NULL will cause the calling task to be deleted.
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/		
void OS_DeleteTask(OS_TaskHandle TaskHandle)
{
	vTaskDelete( TaskHandle );
}

/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
*OS_TaskDelay Function
*Delay a task for a given number of ticks
*Args:
*Delay: The amount of time, in tick periods, that the calling task should block
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/	
void OS_DelayTask(OS_TickType Delay)
{
	vTaskDelay( Delay );
}
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
*OS_Run Function
*Start the OS
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
void OS_Run()
{
		/* Start the scheduler. */
		vTaskStartScheduler();
}
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
*OS_DisableInterrupts Function
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
void OS_DisableInterrupts()
{
	vPortEnterCritical();
}
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
*OS_EnableInterrupts Function
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
void OS_EnableInterrupts()
{
	vPortExitCritical();
}
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
*vApplicationTickHook Function
*internal timer tick Handler For FreeRTOS
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
#define mainCHECK_DELAY						( ( portTickType ) 5000 / portTICK_RATE_MS )
void vApplicationTickHook( void )
{
	
static unsigned long ulTicksSinceLastDisplay = 0;

	/* Called from every tick interrupt as described in the comments at the top
	of this file.

	Have enough ticks passed to make it	time to perform our health status
	check again? */
	ulTicksSinceLastDisplay++;
	if( ulTicksSinceLastDisplay >= mainCHECK_DELAY )
	{
		/* Reset the counter so these checks run again in mainCHECK_DELAY
		ticks time. */
		ulTicksSinceLastDisplay = 0;		
	}
}
void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	/* This function will get called if a task overflows its stack. */

	( void ) pxTask;
	( void ) pcTaskName;

	//for( ;; );
}
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
*
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
#if(OS_ManagesHeap==1)
void * OS_HeapAlloc(OS_Size neededSize)
{
	return pvPortMalloc(neededSize);
}
#endif
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
*
*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
#if(OS_ManagesHeap==1)
void OS_HeapFree(void * address)
{
	vPortFree(address);
}
#endif
