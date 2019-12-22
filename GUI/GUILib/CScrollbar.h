#ifndef _CScrollBar_H
#define _CScrollBar_H
#include "CWnd.h"
//-----------------------------------------------------------------
#define SCROLLBAR_VERTICAL 		true
#define SCROLLBAR_HORIZENTAL 	false
#define SCROLL_WIDTH 					15
#define SCROLL_HEIGHT 				7
enum ScrollBarEvents{
 SCROLLED_UP,
 SCROLLED_DOWN,
 SCROLLED_LEFT,
 SCROLLED_RIGHT
};
//-----------------------------------------------------------------

class CScrollBar : public CWnd
{
//functions:
public:	
	CScrollBar();
	virtual void 				Draw();
	virtual void 				Click(Point*);
	virtual void 				SetSize(coordinate,coordinate);
	virtual void 				SetPosition(coordinate _top , coordinate _left);
	void 								VerticalOrHorizental(bool); //if true vertical else horizental, defines in "Type.h"
	void								SetCount(coordinate count);
private:
	int 								VerticalScrollManager(Point*);
	int 								HorizentalScrollManager(Point*);
	void 								SetSliderSize();
//-------------------------------------------------------------------------------
//events:
public:
	void 								AddScrollEventHandler(CWnd * FuncPtr);
	int 								DoScroll(Point*);
//-------------------------------------------------------------------------------
//Varibles
private:
	bool 								m_VerticalOrHorizental;
	coordinate 					m_Count;
	coordinate 					m_HowManyItem;
	coordinate					m_ItemSize;
	Point 							m_SliderPos;
	Size								m_SliderSize;
	float								m_EachItemSizeInSliderArea;
int i;
	
//events:
private:
	CWnd *	m_ScrollbarEventHandler;
};
#endif
