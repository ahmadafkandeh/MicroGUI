#include "DisplayDriver.h"
#include <Cstring>
using std::memcpy;
using std::strcpy;
using std::strlen;
void Display_Init(void)
{
	LCD_Init();
	LCD_Clear(White);
}

void Display_DrawRectangle(const u16 &x1,const u16 &y1,const u16 &x2,const u16 &y2,u16 backcolor)
{
	LCD_SetPointColor(Black);
	LCD_DrawRectangle(x1,y1,x2+x1,y2+y1);
	if (backcolor!=TransParent)LCD_Fill(x1+BACKCOLOR_MARGIN,y1+BACKCOLOR_MARGIN,x2-BACKCOLOR_MARGIN,y2-BACKCOLOR_MARGIN,backcolor);
}

void Display_PutString(const u16 x,const u16 y,char *text,int Start,int Size,u16 color)
{
	if (color!=TransParent){
		LCD_SetTextColor(color);
		LCD_PutStringInBox(x,y,text,Start,Size);
	}
}

void Display_DrawImage(const u16 &x1,const u16 &y1,const u16 &x2,const u16 &y2,unsigned char *bmp)
{
	LCD_Bmp (x1,y1,x2,y2,bmp);
}

void Display_Fill(const u16 &x1,const u16 &y1,const u16 &x2,const u16 &y2,u16 color)
{
	if (color!=TransParent)LCD_Fill(x1,y1,x2,y2,color);
}

void Display_DrawLine(const u16 &x1,const u16 &y1,const u16 &x2,const u16 &y2,u16 color)
{
	LCD_SetPointColor(color);
	LCD_DrawLine(x1,y1,x2,y2);
}

void Display_PutPixel(const u16 &x,const u16 &y,u16 color)
{
	LCD_SetTextColor(color);
	LCD_PutPixel(x,y);
}
