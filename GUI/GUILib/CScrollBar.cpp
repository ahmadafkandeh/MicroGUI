#include "CScrollbar.h"
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Constructor Of ScrollBar class
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
CScrollBar::CScrollBar()
{
	m_ScrollbarEventHandler=POINTERS_POINT_TO_ZERO;
	m_VerticalOrHorizental=SCROLLBAR_VERTICAL;
	m_SliderSize.width=SCROLL_WIDTH;
	i=0;
	m_SliderPos.y=m_Position.y+SCROLL_WIDTH;
	m_ID=SCROLLBAR_ID;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CScrollBar::AddScrollEventHandler(CWnd * FuncPtr)
{
	m_ScrollbarEventHandler=FuncPtr;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CScrollBar::SetSize(coordinate _Width,coordinate _Heigth)
{
	m_Size.width=_Width;
	m_Size.height=_Heigth;
	//calculate the maximum items the scrollbar can show in its area
	if (m_VerticalOrHorizental==SCROLLBAR_VERTICAL)
	{
		m_HowManyItem=_Heigth/m_ItemSize;
	}
	else if (m_VerticalOrHorizental==SCROLLBAR_HORIZENTAL)
	{
		m_HowManyItem=_Width/m_ItemSize;
	}
	SetSliderSize();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//set the position of obj
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CScrollBar::SetPosition(coordinate _top,coordinate _left)
{
	m_Position.x=_top;
	m_Position.y=_left;
	//set position of slider
	if (m_VerticalOrHorizental==SCROLLBAR_VERTICAL)
	{
		m_SliderPos.x=m_Position.x;
		m_SliderPos.y=SCROLL_WIDTH + m_Position.y;
	}
	else if (m_VerticalOrHorizental==SCROLLBAR_HORIZENTAL)
	{
		m_SliderPos.x=SCROLL_HEIGHT+m_Position.x;
		m_SliderPos.y=m_Position.y;
	}
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//sets the sum of Items the scroll needs to manage
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CScrollBar::SetCount(coordinate range)
{
	if (range<0)range=0;
	m_Count=range;
	SetSliderSize();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CScrollBar::SetSliderSize()
{
	int temp_SliderSize;
	int ItemsCantShow;
	int ItemsCantShow_SizeInSliderArea;
	if (m_VerticalOrHorizental==SCROLLBAR_VERTICAL)
	{
		if(m_Count>m_HowManyItem)
		{
			ItemsCantShow = m_Count - m_HowManyItem;
			//calculate the slider area size
			temp_SliderSize = m_Size.height - ( 2 * SCROLL_WIDTH );
			
			m_EachItemSizeInSliderArea = ( ( float )temp_SliderSize )/ ( ( float )m_Count );
			
			ItemsCantShow_SizeInSliderArea = ItemsCantShow * m_EachItemSizeInSliderArea;
			
			m_SliderSize.height=temp_SliderSize - ItemsCantShow_SizeInSliderArea;
			
			m_SliderSize.height=( m_SliderSize.height > 5 ? m_SliderSize.height : 5 );
		}
		else 
			m_SliderSize.height = 0;
	}
	else if ( m_VerticalOrHorizental == SCROLLBAR_HORIZENTAL )
	{
		if( m_Count > m_HowManyItem )
		{
			ItemsCantShow = m_Count - m_HowManyItem;
			//calculate the slider area size
			temp_SliderSize = m_Size.width - ( 2 * m_ItemSize );
			
			m_EachItemSizeInSliderArea = ( ( float )temp_SliderSize )/ ( ( float )m_Count );
			
			ItemsCantShow_SizeInSliderArea = ItemsCantShow * m_EachItemSizeInSliderArea;
			
			m_SliderSize.width=temp_SliderSize - ItemsCantShow_SizeInSliderArea;
			
			m_SliderSize.width=( m_SliderSize.width > 5 ? m_SliderSize.width : 5 );
		}
		else m_SliderSize.width = 0;
	}
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CScrollBar::VerticalOrHorizental(bool value)
{
	m_VerticalOrHorizental=value;
	if (value == SCROLLBAR_VERTICAL)
		m_ItemSize=CHAR_H;
	else
		m_ItemSize=CHAR_W;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//calls the scrollbarManager function and returns the direction of movement
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
int CScrollBar::DoScroll(Point* point)
{
	int value=SCROLLED_UP; //the values defined in ScrollBarEvents
	if (m_VerticalOrHorizental==SCROLLBAR_VERTICAL)
	{
		value=VerticalScrollManager(point);
	}
	else if (m_VerticalOrHorizental==SCROLLBAR_HORIZENTAL)
	{
		value=HorizentalScrollManager(point);
	}
	Draw();
	if (m_ScrollbarEventHandler!=POINTERS_POINT_TO_ZERO)Event(m_ScrollbarEventHandler,WM_SCROLLED,(void*)value);
	return value;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Gets the position of mouse click, moves the slider & returns the direction of movement
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
int CScrollBar::VerticalScrollManager(Point* point)
{
	int value=SCROLLED_UP;
	int x=SCROLL_WIDTH + m_Position.x;
	int y1=SCROLL_WIDTH + m_Position.y;
	int y2=(m_Position.y+m_Size.height-SCROLL_WIDTH);
	int y3=y2+SCROLL_WIDTH;
	if (m_Position.x<=point->x && x>=point->x)
	{
		if 	(m_Position.y<=point->y && y1>=point->y)
			value=SCROLLED_UP;
		else if (y2<=point->y && y3>=point->y)
			value=SCROLLED_DOWN;
		else
		{
			if (m_SliderPos.y>point->y)
				value=SCROLLED_UP;
			else if ((m_SliderPos.y+m_SliderSize.height)<point->y)
				value=SCROLLED_DOWN;
		}
		//calculate Slider Position
		int tempy=m_SliderPos.y+m_SliderSize.height;
		if (value==SCROLLED_UP)
		{
			if (m_SliderPos.y>=y1)
			{
				i--;
				if (i<0)i=0;
				m_SliderPos.y-=(int)m_EachItemSizeInSliderArea;
			}
		}
		else if (value==SCROLLED_DOWN)
		{
			if(tempy<=y2)
			{
				i++;
				m_SliderPos.y+=(int)m_EachItemSizeInSliderArea;
			}
		}
		while(m_SliderPos.y<y1)m_SliderPos.y++;	
		while((m_SliderPos.y+m_SliderSize.height)>y2)m_SliderPos.y--;	
	}
	return value;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
////Gets the position of mouse click, moves the slider & returns the direction of movement
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
int CScrollBar::HorizentalScrollManager(Point* point)
{
	int value=SCROLLED_LEFT;
	int x1=SCROLL_HEIGHT+m_Position.x;
	int y=SCROLL_HEIGHT+m_Position.y;
	int x2=m_Size.width + m_Position.x;
	int x3=x2+SCROLL_HEIGHT;
	if (m_Position.y<=point->y && y>=point->y)
	{
		if (m_Position.x<=point->x && x1>=point->x)
			value=SCROLLED_LEFT;
		else if (x2<=point->x && x3>=point->x)
			value=SCROLLED_RIGHT;
		else
		{
			if (m_SliderPos.x>point->x)
				value=SCROLLED_LEFT;
			else if ((m_SliderPos.x+m_SliderSize.width)<point->x)
				value=SCROLLED_RIGHT;
		}
		//calculate Slider Position
		int tempx=m_SliderPos.x+m_SliderSize.width;
		if (value==SCROLLED_LEFT)
		{
			if (m_SliderPos.x>=x1)
			{
				i--;
				if (i<0)i=0;
				m_SliderPos.x-=(int)m_EachItemSizeInSliderArea;
			}
		}
		else if (value==SCROLLED_RIGHT)
		{
			if(tempx<=x2)
			{
				i++;
				m_SliderPos.x+=(int)m_EachItemSizeInSliderArea;
			}
		}
		while(m_SliderPos.x<x1)m_SliderPos.x++;	
		while((m_SliderPos.x+m_SliderSize.width)>(x2-SCROLL_HEIGHT))m_SliderPos.x--;		
	}
	return value;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CScrollBar::Click(Point* point)
{
	DoScroll(point);
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Draw the ScrollBar
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CScrollBar::Draw()
{
	if (m_Visible)
	{
		if (m_VerticalOrHorizental==SCROLLBAR_VERTICAL)
		{
			//body
			Display_Fill(m_Position.x,m_Position.y,SCROLL_WIDTH,m_Size.height,ScrollBar_Color);
			//top
			Display_Fill(m_Position.x,m_Position.y,SCROLL_WIDTH,SCROLL_WIDTH,ScrollBar_Btns_Color);
			//Down
			Display_Fill(m_Position.x,(m_Position.y+m_Size.height-SCROLL_WIDTH),SCROLL_WIDTH,SCROLL_WIDTH,ScrollBar_Btns_Color);
			//slider
			Display_Fill(m_SliderPos.x,m_SliderPos.y,m_SliderSize.width,m_SliderSize.height,Blue);
		}
		else if (m_VerticalOrHorizental==SCROLLBAR_HORIZENTAL)
		{
			//body
			Display_Fill(m_Position.x,m_Position.y,m_Size.width,SCROLL_HEIGHT,ScrollBar_Color);
			//left
			Display_Fill(m_Position.x,m_Position.y,SCROLL_HEIGHT,SCROLL_HEIGHT,ScrollBar_Btns_Color);
			//right
			Display_Fill((m_Position.x+m_Size.width-SCROLL_HEIGHT),m_Position.y,SCROLL_HEIGHT,SCROLL_HEIGHT,ScrollBar_Btns_Color);
			//slider
			Display_Fill(m_SliderPos.x,m_SliderPos.y,m_SliderSize.width,SCROLL_HEIGHT,Blue);
			
		}
	}
}
