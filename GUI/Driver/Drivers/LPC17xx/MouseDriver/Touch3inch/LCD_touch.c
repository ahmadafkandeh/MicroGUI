#include "lpc17xx.h"
#include "stdint.h"
#include "touch.h" 
#include "Drivers/LPC17xx/DisplayDriver/TFT3inc/lcd.h"
#include "stdlib.h"
#include "math.h"
#include "sys.h"
#include "exti.h"
#include "i2c.h"
#include "string.h"
#include "type.h"

Pen_Holder Pen_Point;
MouseClickProc mousehookproc=0;
Point touchpos;
typedef signed long  s32;

u16 x,y;

u8 Calibration;
struct TouchPanelCalibration
{
	int XVector;
	int YVector;
	
	int XOffset;
	int YOffset;
	int DeltaX;
	int DeltaY;
}TP_Calibration;

///////////////// Delay Functions /////////////////

void Delay_us(unsigned int count_u)							//100 M-hz Xtal
{
	int i=15;
	while(i--)
	{
		int num = count_u;
		while(num--);		
	}
}
void Delay_ms(unsigned int count_m)
{
  while(count_m--)
	{
		Delay_us(1000);					
	}
}

/////////////////I2C Save function inorder to save 4 values of x.off, y.off, x.fac and y.fac on EEPROM////////////////

void Save_Adjdata(void)
{
	s32 temp_data;
	u8  temp[8];
	temp_data=Pen_Point.xfac*100000000;//保存x校正因素
	temp[0]=(u8)(temp_data & 0xff);//保存x校正因素
	temp[1]=(u8)((temp_data >> 8) & 0xff);//保存x校正因素	
	temp[2]=(u8)((temp_data >> 16) & 0xff);//保存x校正因素	
	temp[3]=(u8)((temp_data >> 24) & 0xff);//保存x校正因素			      
    I2C_WriteNByte(0xA0,1,0X00,temp,8);
	 
	temp_data=Pen_Point.yfac*100000000;//保存y校正因素
	temp[0]=(u8)(temp_data & 0xff);//保存x校正因素
	temp[1]=(u8)((temp_data >> 8) & 0xff);//保存x校正因素	
	temp[2]=(u8)((temp_data >> 16) & 0xff);//保存x校正因素	
	temp[3]=(u8)((temp_data >> 24) & 0xff);//保存x校正因素			       	      
    I2C_WriteNByte(0xA0,1,0X08,temp,8);

	temp_data=Pen_Point.xoff;
	temp[0]=(u8)(temp_data &0xff);
	temp[1]=(u8)((temp_data >>8)&0xff);
    I2C_WriteNByte(0xA0,1,0X10,temp,8);

	temp_data=Pen_Point.yoff;
	temp[0]=(u8)(temp_data &0xff);
	temp[1]=(u8)((temp_data >>8)&0xff);
    I2C_WriteNByte(0xA0,1,0X18,temp,8);

	temp[0]=0xff;
    I2C_WriteNByte(0xA0,1,0X20,temp,1);//校准过了
}

/////////////////I2C Get function inorder to get 4 values of x.off, y.off, x.fac and y.fac from EEPROM////////////////

u8 Get_Adjdata(void)
{
	s32 temp_data;
	u8  temp[8],i;
	temp_data = I2C_ReadNByte(0xA0,1,0X20,temp,8); 
   if(temp[0] == 0xff)
   {
		for(i=0;i<8;i++)
		{
			temp[i] = 0;
		}
	   I2C_ReadNByte(0xA0,1,0X00,temp,8);
	   temp_data = (s32)((temp[3]<<24)|(temp[2]<<16)|(temp[1]<<8)|temp[0]);
	   Pen_Point.xfac = (float)temp_data /100000000;
	
	   I2C_ReadNByte(0xA0,1,0X08,temp,8);
	   temp_data = (s32)((temp[3]<<24)|(temp[2]<<16)|(temp[1]<<8)|temp[0]);
	   Pen_Point.yfac = (float)temp_data /100000000;
	
	   I2C_ReadNByte(0xA0,1,0X10,temp,8);
	   temp_data = (s32)((temp[1]<<8)|temp[0]);
	   Pen_Point.xoff = temp_data;
	
	   I2C_ReadNByte(0xA0,1,0X18,temp,8);
	   temp_data = (s32)((temp[1]<<8)|temp[0]);
	   Pen_Point.yoff = temp_data;
	   return 1;
   }
   return 0;
} 

/*
*********************************************************************************************************
* Description: 	Dealy function of us.
* Arguments  : 	nus : the data of us
* Returns    : 	None
*********************************************************************************************************
*/
void delay_us(u32 nus)
{
	while(nus--);
}
/*
*********************************************************************************************************
* Description: 	Dealy function of ms.
* Arguments  : 	nms : the data of ms
* Returns    : 	None
*********************************************************************************************************
*/
void delay_ms(u32 nms)
{
	while(nms--)
	delay_us(245);
}
/*
*********************************************************************************************************
* Description: 	Write data.
* Arguments  : 	num : the data value
* Returns    : 	None
*********************************************************************************************************
*/	   
void ADS_Write_Byte(u8 num)    
{  
	u8 count=0;
	
	for(count=0;count<8;count++)  
	{ 	  
		if(num&0x80)
		{
			TDIN(1);
		}  
		else 
		{
			TDIN(0);
		}   
		num<<=1;    
		TCLK(0);
		delay_us(1);	   	 
		TCLK(1);	
	} 			    
} 
/*
*********************************************************************************************************
* Description: 	Reading the value of ADC from 7846/7843/XPT2046/UH7843/UH7846.
* Arguments  : 	CMD  the Command value
* Returns    : 	None
*********************************************************************************************************
*/		   
u16 ADS_Read_AD(u8 CMD)	  
{ 	 
	u8 count=0; 	  
	u16 Num=0;
 
	TCLK(0);	 
	TCS(0); 
	TCLK(0);
	delay_us(10);		 
	ADS_Write_Byte(CMD);
	delay_us(13);		   	    
	TCLK(0);
	delay_us(1);		 
	for(count=0;count<16;count++)  
	{ 				  
		Num<<=1; 	 
		TCLK(0);
		delay_us(1);  	    	   
		TCLK(1);
		if(DOUT)
		Num++; 		 
	}		 	
	Num>>=4;
	TCS(1);	 
	return(Num);   
}
/*
*********************************************************************************************************
* Description: 	Take an order for the value value.
* Arguments  : 	xy  the Command value
* Returns    : 	None
*********************************************************************************************************
*/	 
#define READ_TIMES 15 
#define LOST_VAL 5	 
u16 ADS_Read_XY(u8 xy)
{
	u16 i, j;
	u16 buf[READ_TIMES];
	u16 sum=0;
	u16 temp;
	for(i=0;i<READ_TIMES;i++)
	{				 
		buf[i]=ADS_Read_AD(xy);	    
	}				    
	for(i=0;i<READ_TIMES-1; i++)
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;   
} 
/*
*********************************************************************************************************
* Description: 	Getting the real value of AD function.
* Arguments  : 	*x ,*y   the cale of AD value
* Returns    : 	None
*********************************************************************************************************
*/	
u8 Read_ADS(u16 *x,u16 *y)
{
	u16 xtemp,ytemp;			 	 		  
	xtemp=ADS_Read_XY(CMD_RDX);
	ytemp=ADS_Read_XY(CMD_RDY);	  												   
	if(xtemp<100||ytemp<100)return 0;							//fail
	*x=xtemp;
	*y=ytemp;
	return 1;																			//success
}

/*
*********************************************************************************************************
* Description: 	Getting the real value of AD function.
* Arguments  : 	x ,y  the coordinate value
* Returns    : 	None
*********************************************************************************************************
*/	
#define ERR_RANGE 50 				
u8 Read_ADS2(u16 *x,u16 *y) 
{
	u16 x1,y1;
 	u16 x2,y2;
	u16 xtemp,ytemp;
	
 	u8 flag;    
    flag=Read_ADS(&x1,&y1);   
    if(flag==0)return(0);
    flag=Read_ADS(&x2,&y2);	   
    if(flag==0)return(0);   
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
			xtemp=(x1+x2)/2;
      ytemp=(y1+y2)/2;

			*x=(( (xtemp - TP_Calibration.XOffset)*(LCD_WIDTH - (2*TOUCH_CALIBRATION_CIRCLE)) )/TP_Calibration.DeltaX )+ TOUCH_CALIBRATION_CIRCLE;					// X_pixel=(((X-x_offset)*220)/delta_X)+10
			*y=(( (ytemp - TP_Calibration.YOffset)*(LCD_HEIGHT - (2*TOUCH_CALIBRATION_CIRCLE)) )/TP_Calibration.DeltaY )+ TOUCH_CALIBRATION_CIRCLE;					// Y_pixel=(((Y-y_offset)*300)/delta_Y)+10
      
		return 1;
    }
		else return 0;	  
} 
/*
*********************************************************************************************************
* Description: 	Getting the touch value of coordinate function.
* Arguments  :  None
* Returns    : 	None
*********************************************************************************************************
*/				   
u8 Read_TP_Once(void)
{
	u8 t=0;	    
	Pen_Int_Set(0);
	Pen_Point.Key_Sta=Key_Up;
	Read_ADS2(&Pen_Point.X,&Pen_Point.Y);
	while(PEN==0&&t<=250)
	{
		t++;
		delay_ms(10);
	};
	Pen_Int_Set(1);		 
	if(t>=250)return 0;
	else return 1;	
}

/*
*********************************************************************************************************
* Description: 	Draw a touch point function.
* Arguments  : 	x ,y  the coordinate value
* Returns    : 	None
*********************************************************************************************************
*/
void Drow_Touch_Point(u8 x,u16 y)
{
	LCD_DrawLine(x-12,y,x+13,y);
	LCD_DrawLine(x,y-12,x,y+13);
	LCD_DrawPoint(x+1,y+1,Black);
	LCD_DrawPoint(x-1,y+1,Black);
	LCD_DrawPoint(x+1,y-1,Black);
	LCD_DrawPoint(x-1,y-1,Black);
	Draw_Circle(x,y,6);
}
/*
*********************************************************************************************************
* Description: 	Draw a big point function.
* Arguments  : 	x ,y  the coordinate value
* Returns    : 	None
*********************************************************************************************************
*/			   
void Draw_Big_Point(u8 x,u16 y)
{	    
	LCD_DrawPoint(x,y,Black);
	LCD_DrawPoint(x+1,y,Black);
	LCD_DrawPoint(x,y+1,Black);
	LCD_DrawPoint(x+1,y+1,Black);	 	  	
}
/*
*********************************************************************************************************
* Description: 	Getting the value of coordinate function.
* Arguments  : 	None
* Returns    : 	None
*********************************************************************************************************
*/
void Convert_Pos(void)
{		 	  
	if(Read_ADS2(&Pen_Point.X,&Pen_Point.Y))
	{
		Pen_Point.X0=Pen_Point.xfac*Pen_Point.X+Pen_Point.xoff;
		Pen_Point.Y0=Pen_Point.yfac*Pen_Point.Y+Pen_Point.yoff;  
	}
}
/*
*********************************************************************************************************
* Description: 	Touch screen External interrupt initialize function.
* Arguments  : 	None
* Returns    : 	None
*********************************************************************************************************
*/
uint32_t EINTInit( void )
{

  LPC_PINCON->PINSEL4 = 1 << 26;	// set P2.13 as EINT0 and
																	// P2.0~7 GPIO output

  LPC_SC->EXTMODE = EINT3_EDGE;		// INT3 edge trigger
  LPC_SC->EXTPOLAR = 0;						// INT3 is falling edge by default

  NVIC_EnableIRQ(EINT3_IRQn);
  return( 1 );
}
/*
*********************************************************************************************************
* Description: 	Touch screen External interrupt function.
* Arguments  : 	None
* Returns    : 	None
*********************************************************************************************************
*/

void EINT3_IRQHandler (void) 
{
	
	delay_us(10);
	
	if(!PEN)
	{
		if (Calibration == OK)
		{
			Read_ADS2(&x,&y);
			touchpos.x=x;
			touchpos.y=y;
		}
		else
		{
			touchpos.x=0xA5A5A5;
			touchpos.y=0xA5A5A5;
			Touch_Adjust();
		}
		mousehookproc(&touchpos);
  }
LPC_SC->EXTINT = EINT3;																			// clear interrupt 
}

/*
*********************************************************************************************************
* Description: 	Touch screen External interrput Enable function.
* Arguments  : 	1 Enable
*				0 Disable
* Returns    : 	None
*********************************************************************************************************
*/	 
void Pen_Int_Set(u8 en)
{
	if(en)
	NVIC_EnableIRQ(EINT3_IRQn);   //Enable		  	
	else 
	NVIC_DisableIRQ(EINT3_IRQn); 	//Disable 	   
}
/*
*********************************************************************************************************
* Description: 	Touch screen adjust function.Getting four adjust parameter!
* Arguments  : 	None
* Returns    : 	None
*********************************************************************************************************
*/
void Touch_Adjust(void)
{								 	

	char Count=0;
	int XYTemp[4][2];
	
	LCD_Clear(White);
	
	Draw_Circle(TOUCH_CALIBRATION_CIRCLE , (LCD_HEIGHT - TOUCH_CALIBRATION_CIRCLE),5);
	while(1)
	{
		if (!PEN)
		{
			if(Read_ADS(&x,&y))
			{
				XYTemp[Count][0]=x;
				XYTemp[Count][1]=y;
				Count++;
			}
			switch(Count)
			{
				case 0:
					Draw_Circle(TOUCH_CALIBRATION_CIRCLE , (LCD_HEIGHT - TOUCH_CALIBRATION_CIRCLE),5);
				
					Delay_ms(300);
					break;
				case 1:
					Draw_Circle((LCD_WIDTH - TOUCH_CALIBRATION_CIRCLE) , LCD_HEIGHT - TOUCH_CALIBRATION_CIRCLE,5);
					Delay_ms(300);
					break;
				case 2:
					Draw_Circle(TOUCH_CALIBRATION_CIRCLE , TOUCH_CALIBRATION_CIRCLE,5);
					Delay_ms(300);
					break;
				case 3:
					Draw_Circle((LCD_WIDTH - TOUCH_CALIBRATION_CIRCLE) , TOUCH_CALIBRATION_CIRCLE,5);
					Delay_ms(300);
					break;
				case 4:
					TP_Calibration.XOffset = ( XYTemp[0][0] + XYTemp[2][0] )/2;   																			// (X1+X3)/2
					TP_Calibration.YOffset = ( XYTemp[0][1] + XYTemp[1][1] )/2;																					// (Y1+Y2)/2
					TP_Calibration.DeltaX  = ( (XYTemp[0][0] + XYTemp[2][0]) - (XYTemp[1][0]+XYTemp[3][0]) )/(-2); 			// [(X1+X3)-(X2+X4)]/2
					TP_Calibration.DeltaY  = ( (XYTemp[0][1] + XYTemp[1][1]) - (XYTemp[2][1]+XYTemp[3][1]) )/(-2);	  	// [(Y1+Y2)-(Y3+Y4)]/2
					
				
					TP_Calibration.XOffset = ( XYTemp[0][0] + XYTemp[2][0] )/2;   																			// (X1+X3)/2
					TP_Calibration.YOffset = ( XYTemp[2][1] + XYTemp[3][1] )/2;																					// (Y1+Y2)/2
					TP_Calibration.DeltaX  = ( (XYTemp[0][0] + XYTemp[2][0]) - (XYTemp[1][0]+XYTemp[3][0]) )/(-2); 			// [(X1+X3)-(X2+X4)]/2
					TP_Calibration.DeltaY  = ( (XYTemp[2][1] + XYTemp[3][1]) - (XYTemp[0][1]+XYTemp[1][1]) )/(-2);	  	// [(Y1+Y2)-(Y3+Y4)]/2

					Calibration = OK;
					
					return;
				
				default:
					break;
			}
		}
	}
} 

/*
*********************************************************************************************************
* Description: 	Touch screen initialize function.
* Arguments  : 	None
* Returns    : 	None
*********************************************************************************************************
*/
void Touch_Init(MouseClickProc mouse_hook_proc)
{			    		   
	LPC_GPIO0->FIODIR |= 0x00002C0;  			//P0.6 0.7 0.9 Output
	LPC_GPIO2->FIODIR |= 0x0000000;  			//P2.13 input P2.0...P2.7 Output
 	Read_ADS(&Pen_Point.X,&Pen_Point.Y);	//the first Read initialize
	mousehookproc=mouse_hook_proc;
}
