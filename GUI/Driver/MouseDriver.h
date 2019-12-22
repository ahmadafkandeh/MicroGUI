
#ifndef _Mouse_Driver_H
#define _Mouse_Driver_H
#include "Type.h"

#ifdef LPC17xx
	#ifdef Touch3inch
		#include "stdint.h"
		#include "sys.h"
		#include "touch.h"
		#include "exti.h"
		#include "i2c.h"
	#else
		#warning "No Mouse Driver included"
	#endif
#endif
extern void Mouse_Init(MouseClickProc keyproc);
#endif
