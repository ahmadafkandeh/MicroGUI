#include "CMemo.h"
#include <cstring>
using std::strlen;
using std::memcpy;
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//constructor of Memo
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
CMemo::CMemo()
{
	m_MemoText=(char*)manager_HeapAlloc(MEMO_MAX_CHARS);
	m_MemoIndexOfLines=(char*)manager_HeapAlloc(MEMO_MAX_LINES);
	m_Max_Line_Char_Len=0;
	m_MemoText[0]=13;
	for (int i=0;i<MEMO_MAX_LINES;i++) m_MemoIndexOfLines[i]=0;
	m_MemoIndexOfLines[0]=1;
	SetSize(50,90);
	SetPosition(10,10);
	m_CurrentLine=0;
	m_CurrentCurssorPos=1;
	m_StartIndex=0;
	m_StartCharIndex=0;	
	//vertical scrollbar 
 	m_Vertical_ScrollBar.VerticalOrHorizental(SCROLLBAR_VERTICAL);
	//horizental scrollbar
	m_Horizental_ScrollBar.VerticalOrHorizental(SCROLLBAR_HORIZENTAL);
	m_contains_Vscroll=false;
	m_contains_Hscroll=false;
	m_ID=MEMO_ID;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to change Object's size
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CMemo::SetSize(coordinate _width,coordinate _height)
{
	m_Size.width=_width;
	m_Size.height=_height;
	CheckSizeWithParent();
	
	m_Vertical_ScrollBar.SetPosition((m_Position.x+m_Size.width-SCROLL_WIDTH),m_Position.y);
	m_Vertical_ScrollBar.SetSize(SCROLL_WIDTH,m_Size.height-SCROLL_HEIGHT);
	m_Horizental_ScrollBar.SetPosition(m_Position.x,(m_Position.y+m_Size.height-SCROLL_HEIGHT));
	m_Horizental_ScrollBar.SetSize(m_Size.width-SCROLL_WIDTH,SCROLL_HEIGHT);
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Property to Change Object's Position
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CMemo::SetPosition(coordinate _top,coordinate _left)
{
	m_Position.x=_top;
	m_Position.y=_left;
	CheckSizeWithParent();
	
	m_Vertical_ScrollBar.SetPosition((m_Position.x+m_Size.width-SCROLL_WIDTH),m_Position.y);
	m_Vertical_ScrollBar.SetSize(SCROLL_WIDTH,m_Size.height-SCROLL_HEIGHT);
	m_Horizental_ScrollBar.SetPosition(m_Position.x,(m_Position.y+m_Size.height-SCROLL_HEIGHT));
	m_Horizental_ScrollBar.SetSize(m_Size.width-SCROLL_WIDTH,SCROLL_HEIGHT);
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Destructor of class
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
CMemo::~CMemo()
{
	manager_HeapFree((void*) m_MemoText);
	manager_HeapFree((void*)m_MemoIndexOfLines);
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//adds a character to current Line
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CMemo::AddCharToLine(char key)
{
	int len=strlen(m_MemoText);
	if (len<100)
	{
		for (int i=len;i>=m_CurrentCurssorPos;i--)
		{
			m_MemoText[i+1]=m_MemoText[i];
		}
		m_MemoText[m_CurrentCurssorPos]=key;
		m_CurrentCurssorPos++;
		m_MemoText[len+2]=0;
		GetMaxLineLen();
	}
}
void CMemo::AddTextToLine(const char* p)
{
	while(*p)
	{
		AddCharToLine(*p++);
	}
	if(m_Parent!=0)Draw();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Removes a Character From CurrentLine
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CMemo::RemoveCharFromLine()
{
	int len=strlen(m_MemoText);
	for (int i=m_CurrentCurssorPos;i<=len;i++)
	{
		m_MemoText[i]=m_MemoText[i+1];
	}
	m_MemoText[len-1]=0;
	m_CurrentCurssorPos--;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Adds a new Line
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CMemo::AddLine()
{
	int len=strlen(m_MemoText);
	char* p=m_MemoIndexOfLines;
	if (len<MEMO_MAX_CHARS)
	{
		m_MemoText[len]=13;
		m_MemoText[len+1]=0;
		{//save index of line into m_MemoIndexOfLines
		while(*p!=0)p++;
		*p=len+1;
		}
		GetMaxLineLen();
		m_StartCharIndex=0;
		m_CurrentLine++;
		m_CurrentCurssorPos++;
	}
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CMemo::GetMaxLineLen()
{
	//get maximum line len
	char* p=m_MemoIndexOfLines;
	
	if (m_MemoIndexOfLines[1]!=0)
	{
		while(*p!=0 & *(p+1)!=0)
		{
			char linelen= (*(p+1)-*p);
			if (linelen>m_Max_Line_Char_Len)
				m_Max_Line_Char_Len=linelen;
			p++;
		}
	}
	else
	{
		m_Max_Line_Char_Len=strlen(m_MemoText);
	}
	m_Horizental_ScrollBar.SetCount(m_Max_Line_Char_Len);
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CMemo::Vertical_ScrollBarEventHandler(Point* point)
{
	int value=m_Vertical_ScrollBar.DoScroll(point);
	if (value==SCROLLED_UP){if (m_StartIndex>0) m_StartIndex--;}
	else if (value==SCROLLED_DOWN) 
	{
		//calculate How Many Items can Show
	 int HowManyItem=(m_Size.height-SCROLL_HEIGHT)/(CHAR_H);
		if (HowManyItem<m_LinesCount && (HowManyItem+m_StartIndex)<m_LinesCount)
			m_StartIndex++;
	}
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CMemo::Horizental_ScrollBarEventHandler(Point* point)
{
	int value=m_Horizental_ScrollBar.DoScroll(point);
	if (value==SCROLLED_LEFT){if (m_StartCharIndex>0)m_StartCharIndex--;}
	else if (value==SCROLLED_RIGHT)
	{
		//claculate how many char can show
		m_LenthOfShownText=(m_Size.width-5)/(CHAR_W+2);
		if ((m_LenthOfShownText<m_Max_Line_Char_Len) && (m_LenthOfShownText+m_StartCharIndex)<m_Max_Line_Char_Len)
			m_StartCharIndex++;
	}
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CMemo::CheckClickOnItems(Point* point)
{
	int Count=m_LinesCount;
	//calculate How Many Items can Show
	int HowManyItem=(m_Size.height-SCROLL_HEIGHT)/(CHAR_H);
	for (int i=0;i<HowManyItem;i++)
	 {
			int pos1=(m_Position.y)+(i*CHAR_H);
			int pos2=pos1+CHAR_H;
			if (pos1<=point->y& pos2>=point->y)
				if((m_StartIndex+i)<=Count)
				{
					m_CurrentLine=m_StartIndex+i;
					break;
				}
	 }
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Click event handler
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CMemo::Click(Point* position)
{
	if (m_Vertical_ScrollBar.IsContainedPoint(position) & m_contains_Vscroll)Vertical_ScrollBarEventHandler(position);
	else if (m_Horizental_ScrollBar.IsContainedPoint(position) & m_contains_Hscroll)Horizental_ScrollBarEventHandler(position);
	else CheckClickOnItems(position);
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//key press Event handler
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CMemo::KeyPressed(char* key)
{
	if (*key>=33 && *key<=126) //if alphanumeric
		AddCharToLine(*key);
	else if(*key==KEYS_SPACE)
		AddCharToLine(' ');
	else if (*key==KEYS_ENTER)
		AddLine();
	else if (*key==KEYS_DELETE)
		RemoveCharFromLine();
	if(m_Parent!=0)Draw();
	if (KeyPressHandler!=POINTERS_POINT_TO_ZERO)Event(KeyPressHandler,WM_KeyPress,(void*)key);
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Draw the Memo
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CMemo::Draw()
{
	if (m_Visible)
	{
	//Body
	Display_DrawRectangle(m_Position.x,m_Position.y,m_Size.width,m_Size.height,m_BackColor);
	//Draw Items
	DrawItems();
	}
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Draw The Items
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CMemo::DrawItems()
{
	int Count;
	//calculate How Many Items can Show
	int HowManyItem=(m_Size.height-SCROLL_HEIGHT)/(CHAR_H);
	//claculate how many char can show
	m_LenthOfShownText=(m_Size.width-5)/(CHAR_W+2);
	int ss=0;
	//--------------------------------
	//draw items
	int line_len=0;
	int indexoflines=strlen(m_MemoIndexOfLines);
	int firstitemtoshow=0;
	m_LinesCount=indexoflines;
	Count=indexoflines;
	if (Count>HowManyItem)
		firstitemtoshow=Count-HowManyItem;
	else
		firstitemtoshow=0;
	int index=m_CurrentLine;
	ss=m_CurrentLine-firstitemtoshow;
	while(HowManyItem--)
	{
		int tempindex=((m_MemoIndexOfLines[index]-1)==0?1:m_MemoIndexOfLines[index]);
			if (tempindex==1)
				line_len=strlen(m_MemoText);
			else
				line_len=m_MemoIndexOfLines[index]-m_MemoIndexOfLines[index+1];
			if ( line_len != 0 )
			{
				//drawing Currsor
				if (m_Focus && ss==(m_CurrentLine-firstitemtoshow))
					{
						int templinelen=line_len;
						while(templinelen>m_LenthOfShownText)templinelen--;
						int tempx=m_Position.x+(templinelen*(CHAR_W+2));
						int tempy=m_Position.y+(ss*CHAR_H)+CHAR_H+3;
						Display_DrawLine(tempx,(m_Position.y)+(ss*CHAR_H),tempx,tempy,Black);
					}
				//Draw Text
				int len=m_LenthOfShownText-(line_len>=m_LenthOfShownText?0:(m_LenthOfShownText-line_len));
				Display_PutString(m_Position.x,(m_Position.y)+(ss*CHAR_H),m_MemoText,(m_StartCharIndex+m_MemoIndexOfLines[index]),len,m_TextColor);
			}
		ss++;
		index++;
			if(m_CurrentLine!=0&&index==(m_CurrentLine+1))
				{index=firstitemtoshow; ss=0;}
			if (index==m_CurrentLine)
				{index++;ss++;}
	}
// 		
	//----------------------------------
	//draw Scrolls if needed
	//check for Vertical ScrollBar
	HowManyItem=(m_Size.height-SCROLL_HEIGHT)/CHAR_H;
	if (HowManyItem<Count)
	{ 
		m_Vertical_ScrollBar.Draw(); 
		m_contains_Vscroll=true;
		m_Horizental_ScrollBar.SetSize(m_Size.width-SCROLL_WIDTH,SCROLL_HEIGHT);
	}
	else 
	{
		m_contains_Vscroll=false;
		m_Horizental_ScrollBar.SetSize(m_Size.width,SCROLL_HEIGHT);
	}
	//check For Horizental ScrollBar
	if (m_Max_Line_Char_Len>m_LenthOfShownText)
	{
		m_Horizental_ScrollBar.Draw(); 
		m_Vertical_ScrollBar.SetSize(SCROLL_WIDTH,m_Size.height-SCROLL_HEIGHT);
		m_contains_Hscroll=true;
	}
	else
	{
		m_contains_Hscroll=false;
		m_Vertical_ScrollBar.SetSize(SCROLL_WIDTH,m_Size.height);
	}
}
