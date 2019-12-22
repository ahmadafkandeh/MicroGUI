#ifndef __Type_H
#define __Type_H
#include "Keys.h"
#include "Colors.h"
#include "CWndID.h"

//Declear proccessor
#define LPC17xx
//Declaer Display
#define TFT3inch
//Declear Mouse
#define Touch3inch

//-----------------------------------------------------------------
//Font Size
#define CHAR_H  16                 /* Character Height (in pixels)       */
#define CHAR_W  6                  /* Character Width (in pixels)        */
//-----------------------------------------------------------------
#define POINTERS_POINT_TO_ZERO	0
//-----------------------------------------------------------------
//used types definition
typedef signed   int 				coordinate;
typedef unsigned char 			hwnd_type;
typedef unsigned char 			u8;
typedef unsigned short int 	u16;
typedef unsigned int 				u32;
typedef unsigned __int64 		u64;

typedef unsigned short ColorRef;
//-----------------------------------------------------------------
//Declare Structs and Delegates
typedef struct{
	coordinate x;
	coordinate y;
}Point;
typedef struct{
	coordinate width;
	coordinate height;
}Size;
//define Event Handlers
typedef void 	(*MouseClickProc)			(Point*);
typedef void 	(*KeyPressProc)				(char*);
typedef void 	(*ScrollEventHandler)	(Point*,int);
#endif
