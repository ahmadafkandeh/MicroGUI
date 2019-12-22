#include "CListBox.H"
#include <Cstring>
using std::strlen;
using std::strcpy;
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//default constructor
//arg: None
//m_ReferenceMode==>False
//if m_ReferenceMode==true then listbox saves the address of items and any changes
//on the original data will change the item value,otherwise saves a copy of items.
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
CListBox::CListBox()
{
	m_SelectedIndex=0;
	m_StartIndex=0;
	m_ReferenceMode=false;
	m_V_ScrollBar.VerticalOrHorizental(SCROLLBAR_VERTICAL);
	SetSize(200,100);
	m_ID=LISTBOX_ID;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//constructor
//arg: _referencemode: gets a boolian and sets the m_ReferenceMode
//if refrencemode==true then listbox saves the address of items and any changes
//on the original data will change the item value,otherwise saves a copy of items.
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
CListBox::CListBox(bool _referencemode)
{
	m_SelectedIndex=0;
	m_StartIndex=0;
	m_ReferenceMode=_referencemode;
	m_V_ScrollBar.VerticalOrHorizental(SCROLLBAR_VERTICAL);
	SetSize(200,100);
	m_ID=LISTBOX_ID;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Destructor
//if m_ReferenceMode==False it will delete all Items and release
//all the allocated memory, because in this mode we save a copy of every
//items on Heap, then we must remove this copies from Heap when Destructor calls.
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
CListBox::~CListBox()
{
	int Count=m_Items.Count();
	for (int index=0;index<Count;index++)
	{
		if(!m_ReferenceMode)
		{
			manager_HeapFree(m_Items.GetObject(index));
		}
		m_Items.RemoveByindex(index);
	}
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Set Size Function
//this Func sets the size of ListBox
//
//args:
//_width: the width of ListBox
//_height: the height of ListBox
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CListBox::	SetSize(coordinate _width,coordinate _height)
{
	m_Size.width=_width;
	m_Size.height=_height;
	
	//calculate how many of Items can Show
	HowManyItemCanShow=m_Size.height/CHAR_H;
	
	//claculate how many characters of each can show
	m_LenthOfShownText=(m_Size.width-SCROLL_WIDTH)/(CHAR_W+2);
	
	m_V_ScrollBar.SetPosition((m_Position.x+m_Size.width-SCROLL_WIDTH),(m_Position.y+BACKCOLOR_MARGIN));
	m_V_ScrollBar.SetSize(SCROLL_WIDTH,(m_Size.height-BACKCOLOR_MARGIN));
	CheckSizeWithParent();
	if(m_Parent!=0)Draw();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Set Position Func
//this Func Sets the position of ListBox
//args:
//_top: the Distance of top of Display
//_left: the Distance of left of Display
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CListBox::	SetPosition(coordinate _top , coordinate _left)
{
	m_Position.x=_top;
	m_Position.y=_left;
	
	m_V_ScrollBar.SetPosition((m_Position.x+m_Size.width-SCROLL_WIDTH),(m_Position.y+BACKCOLOR_MARGIN));
	m_V_ScrollBar.SetSize(SCROLL_WIDTH,(m_Size.height-BACKCOLOR_MARGIN));	
	
	CheckSizeWithParent();
	if(m_Parent!=0)Draw();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//if scrollbar exists and click position was on scrollbar position
//this function will be call(only calls in the Click Function).
//args:
//point: the posiotion of mouse pointer.
//in this function the point will send to ScrollBar's DoScroll Function and 
//takes back an integer, this integer will change the m_StartIndex value.
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CListBox::ListBox_ScrollbarEventHandler(Point* point)
 {
	 int value=m_V_ScrollBar.DoScroll(point);
	 if (value==SCROLLED_UP)
		 if (m_StartIndex>0)m_StartIndex--;
	 if (value==SCROLLED_DOWN) 
	 {
		 if ((HowManyItemCanShow+m_StartIndex)<m_Items.Count())
		 {
			 m_StartIndex++;
		 }
	 }
 }
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//this function will add the items into the listBox
//args:
//item: gives an array or a pointer of characters.
//if m_ReferenceMode==true then only the address of item will save.
//otherwise a copy of item will be created and this copy will save.
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CListBox::AddItem(char* item)
{
	if (m_ReferenceMode)
		m_Items.ADD(item);
	else
	{	
		char* temp=(char*)manager_HeapAlloc(strlen(item));
		strcpy(temp,item);
		m_Items.ADD(temp);
	}
	m_V_ScrollBar.SetCount(m_Items.Count());
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//this item will remove the items by their index.
//args:
//index: the index of item
//if m_ReferenceMode==true only the saved address of items will be delete.
//if m_ReferenceMode==false at first the copy of item will be delete and
//then the saved address of item will be delete.
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CListBox::RemoveItem(int index)
{
	if (index<=m_Items.Count() && index>=0)
	{
		char* objptr=m_Items.GetObject(index);
		m_Items.RemoveByindex(index);
		if(!m_ReferenceMode)
		{
			manager_HeapFree(objptr);
		}
		int Count=m_Items.Count();
		if (m_SelectedIndex>=Count)m_SelectedIndex=Count-1;
		m_V_ScrollBar.SetCount(Count);
		if(m_Parent!=0)Draw();
	}
	
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to Set SelectedIndex
//it will change m_SelectedIndex
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CListBox::SetSelectedIndex(int index)
{
	if (index<0)m_SelectedIndex=0;
	m_SelectedIndex=( index >= m_Items.Count() ? m_Items.Count()-1: index );
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to get Selected index
//it will return the value of m_SelectedIndex
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
int CListBox::GetSelectedIndex()
{
	return m_SelectedIndex;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//this Function will Draw the ListBox
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CListBox::Draw()
{
	if (m_Visible)
	{
		//Draw the body of ListBox
		Display_DrawRectangle(m_Position.x,m_Position.y,m_Size.width,m_Size.height,m_BackColor);
		//Draw Items
		DrawItems();
		//Draw the ScrollBar
		m_V_ScrollBar.Draw();
	}
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Darw the items
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CListBox::DrawItems()
{	
	int ss=0;
	//count of items
	int Count=m_Items.Count();
	//draw the items one by one
	for (int i=m_StartIndex;i<Count;i++)
	{
		//highlight the selected item
		if (ss==(m_SelectedIndex-m_StartIndex))Display_Fill(m_Position.x+BACKCOLOR_MARGIN,((m_Position.y)+ss*CHAR_H+BACKCOLOR_MARGIN),(m_Size.width-SCROLL_WIDTH),CHAR_H-BACKCOLOR_MARGIN,LightGrey);
		//Put Item to Display
		Display_PutString(m_Position.x,(m_Position.y)+(ss*CHAR_H),m_Items.GetObject(i),0,m_LenthOfShownText,( ss == ( m_SelectedIndex - m_StartIndex )? White : m_TextColor ));
		ss++;
		if (HowManyItemCanShow==ss)break;
	}
	//Draw ScrollBars if needed
	if (HowManyItemCanShow<m_Items.Count()){ m_contains_scroll=true;}
	else m_contains_scroll=false;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Mouse Click Handler Function
//this function will check the mouse click position,if position was the 
//ScrollBar's position then the "ListBox_ScrollbarEventHandler" will call 
//otherwise "CheckClickOnItems" will call. and when returns it will redraw the ListBox
//to update changes on Display.
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
 void CListBox::Click(Point* position)
 {
	 if (m_V_ScrollBar.IsContainedPoint(position)&& m_contains_scroll) 
		 ListBox_ScrollbarEventHandler(position);
	 else CheckClickOnItems(position);
 }
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//this function will check the position of mouse, and looks for items position
//if these two positions was equal together the m_selectedIndex will be sets to that item's index.
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CListBox::CheckClickOnItems(const Point* position)
{
	 	int Count=m_Items.Count();
	for (int i=0;i<HowManyItemCanShow;i++)
	 {
			int pos1=(m_Position.y)+(i*CHAR_H);
			int pos2=pos1+CHAR_H;
			if (pos1<=position->y & pos2>=position->y)
			{
				if((m_StartIndex+i)<Count)
					m_SelectedIndex=m_StartIndex+i;
				else
					m_SelectedIndex=Count-1;
				SetText(m_Items.GetObject(m_SelectedIndex));
				break;
			}
	 }
} 
