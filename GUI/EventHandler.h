#ifndef __EventHandler_H_
#define __EventHandler_H_
#include "messages.h"
class EventHandler
{
public:
	virtual void Event(void* Sender,MessageType Message, void * Param)
	{}
};
#endif
