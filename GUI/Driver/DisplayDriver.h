#ifndef _Display_Driver_H
#define _Display_Driver_H
#include "Type.h"

//----------------------------------------------------------
//margins
#define BACKCOLOR_MARGIN			1
//----------------------------------------------------------
//display size
#define Display_Width  239
#define Display_Height 340
//----------------------------------------------------------
//Choose LCD Functions File
#ifdef LPC17xx
	#ifdef TFT3inch
		#include "Drivers/LPC17xx/DisplayDriver/TFT3inc/lcd.h"
	#else
		#warning "No Display Driver Defines."
	#endif
#endif
//-----------------------------------------------------------
//Functions Definition
extern void Display_Init(void);
extern void Display_DrawRectangle(const u16 &x1,const u16 &y1,const u16 &x2,const u16 &y2,u16 backcolor);
extern void Display_PutString(const u16 x,const u16 y,char *text,int Start,int Size,u16 color);
extern void Display_DrawImage(const u16 &x1,const u16 &y1,const u16 &x2,const u16 &y2,unsigned char *bmp);
extern void Display_Fill(const u16 &x1,const u16 &y1,const u16 &x2,const u16 &y2,u16 color);
extern void Display_DrawLine(const u16 &x1,const u16 &y1,const u16 &x2,const u16 &y2,u16 backcolor);
extern void Display_PutPixel(const u16 &x,const u16 &y,u16 color);
//varibles

#endif
