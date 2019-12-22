#include "CWnd.h"
#include "OSAL.h"
#include "HeapManager.h"
#include <cstring>
using std::strcpy;
using std::strchr;
using std::strlen;
using std::memcpy;
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Constructor Of CWnd Class
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
CWnd::CWnd()
{
	m_TextCurrentLenth=TEXT_DEFAULT_LENTH;
	m_Text=(char*)manager_HeapAlloc(m_TextCurrentLenth);
	m_Visible=true;
	m_AutoSize=false;
	m_Enabled=true;
	SetText("CWnd");
	m_TextAlign=ALIGN_LEFT_CENTER;
	SetBackColor(White);
	m_TextColor=Black;
	SetPosition(10,10);
	SetSize(20,50);
	m_BGptr=POINTERS_POINT_TO_ZERO;
	m_Parent=POINTERS_POINT_TO_ZERO;
	MouseClickHandler=POINTERS_POINT_TO_ZERO;
	KeyPressHandler=POINTERS_POINT_TO_ZERO;
	m_ID=CWND_ID;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Destructor of CWnd Class
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
CWnd::~CWnd()
{
	manager_HeapFree((void*) m_Text);
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CWnd::Dispose()
{
	
};
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//this Func Sets the object text
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CWnd::SetText(char *text)
{
	int textlen=strlen(text);
	if (textlen>m_TextCurrentLenth & m_TextCurrentLenth<TEXT_MAX_CHARS){
		if ((m_TextCurrentLenth+10)>TEXT_MAX_CHARS)m_TextCurrentLenth+=(TEXT_MAX_CHARS-m_TextCurrentLenth);
		else m_TextCurrentLenth+=10;
		manager_HeapFree((void*) m_Text);
		m_Text=(char*)manager_HeapAlloc(m_TextCurrentLenth);
	}
	memcpy(m_Text,text,textlen);
	m_Text[textlen]=0;
	CheckTextSize();
	CheckTextAlign();
	if(m_Parent!=0)Draw();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to set TextAlignment
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CWnd::SetTextAlign(char align)
{
	m_TextAlign=align;
	CheckTextAlign();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to change Object's size
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CWnd::SetSize(coordinate _width,coordinate _height)
{
	m_Size.width=_width;
	m_Size.height=_height;
	CheckSizeWithParent();
	CheckTextSize();
	CheckTextAlign();
	if(m_Parent!=0)Draw();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Property to Change Object's Position
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CWnd::SetPosition(coordinate _top,coordinate _left)
{
	m_Position.x=_top;
	m_Position.y=_left;
	CheckSizeWithParent();
	CheckTextAlign();
	if(m_Parent!=0)Draw();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to enable or disable object
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CWnd::SetEnabled(bool enable)
{
	m_Enabled=enable;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to change object's visibility
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CWnd::SetVisible(bool flag)
{
	m_Visible=flag;
	if(m_Parent!=0)Draw();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to set backcolor of obj
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CWnd::SetBackColor(ColorRef backcolor)
{
	m_BackColor=backcolor;
	if(m_Parent!=0)Draw();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to set textcolor of obj
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CWnd::SetTextColor(ColorRef color)
{
	m_TextColor =color;
	if(m_Parent!=0)Draw();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to set an image for BackGround
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CWnd::SetBackGroundImage(unsigned char *bmp)
{
	m_BGptr=bmp;
	if(m_Parent!=0)Draw();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//set or reset the focus on object
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CWnd::SetFocus(bool value)
{
	if (m_Focus!=value)
	{
		m_Focus=value;
		(m_Focus==true)?GotFocus():LostFocus();
		if(m_Parent!=0)Draw();
	}
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//sets the objects parrent
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
 bool CWnd::SetParent(CWnd* parent)
 {
		if (m_Parent==0){m_Parent=parent;CheckSizeWithParent();return true;};
		return false; 
 }
 //&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Remove the parrent of Object
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
 void CWnd::RemoveParent(CWnd* parent)
 {
		if (m_Parent==parent)m_Parent=0;
 }
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to Get the ID of Object 
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
int CWnd::ID()
{
	return m_ID;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Returns the Focus
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
 bool CWnd::GetFocus()
{
	return m_Focus;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to get Backcolor of obj
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
ColorRef CWnd::GetBackColor()
{
	return m_BackColor;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to Get visibility of obj
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
bool CWnd::GetVisible()
{
	return m_Visible;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to get enabled flag of obj
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
bool CWnd::GetEnabled()
{
	return m_Enabled;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to get object's Text
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
char* CWnd::GetText()
{
	return m_Text;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to get object's size
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
Size CWnd::GetSize(){
	return m_Size;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to get object's Position
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
Point CWnd::GetPosition(){
	return m_Position;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to get Object's handle
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
hwnd_type CWnd::GetHandle(){
	return m_HWnd;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to set a Handle to object
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CWnd::SetHandle(hwnd_type hwnd){
	m_HWnd=hwnd;
}
/*--------------------------------------------------------------------------//
//if TextSize goes Bigger than ObjSize this Function will Resize the        //
//Obj If the AutoSize Flag sets true.                                       //
//--------------------------------------------------------------------------*/
void CWnd::CheckTextSize()
{
	int Char_W;
	int x=m_Size.width-TEXT_CURSSOR_SIZE,y=m_Size.width;
	Char_W=strlen(m_Text)*(CHAR_W+2);
	if(m_AutoSize){
		m_LenthOfShownText=strlen(m_Text);
		if(y<(CHAR_H) || y>(CHAR_H))m_Size.height=CHAR_H;
		if(x<Char_W || x>Char_W)m_Size.width=Char_W;
		CheckSizeWithParent();
		x=m_Size.width-TEXT_CURSSOR_SIZE;y=m_Size.height;
	}
		if(y<CHAR_H)
			m_LenthOfShownText=0;
		else if(x>Char_W)
		{
			m_LenthOfShownText=x/CHAR_W;
			if (m_LenthOfShownText>3)m_LenthOfShownText-=3;
		}
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//calculate the text position in the object area
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CWnd::CheckTextAlign()
{	
	coordinate text_W=(strlen(m_Text)) * (CHAR_W);
	switch (m_TextAlign)
	{
		case ALIGN_LEFT_TOP:
			m_TextPosition.x=m_Position.x;
			m_TextPosition.y=m_Position.y;
			break;
		case ALIGN_LEFT_DOWN:
			m_TextPosition.x=m_Position.x;
			m_TextPosition.y=m_Position.y+m_Size.height-CHAR_H;
			break;
		case ALIGN_LEFT_CENTER:
			m_TextPosition.x=m_Position.x;
			m_TextPosition.y=m_Position.y+((m_Size.height-CHAR_H)>>1);
			break;
		case ALIGN_RIGHT_TOP:
			m_TextPosition.x=(m_Position.x+m_Size.width)-(text_W);
			m_TextPosition.y=m_Position.y;
			break;
		case ALIGN_RIGHT_DOWN:
			m_TextPosition.x=(m_Position.x+m_Size.width)-(text_W);
			m_TextPosition.y=(m_Position.y+m_Size.height)-(CHAR_H);
			break;
		case ALIGN_RIGHT_CENTER:
			m_TextPosition.x=(m_Position.x+m_Size.width)-(text_W);
			m_TextPosition.y=m_Position.y+((m_Size.height-CHAR_H)>>1);
			break;
		case ALIGN_MIDDLE_TOP:
			m_TextPosition.x=m_Position.x+((m_Size.width-text_W)>>1);
			m_TextPosition.y=m_Position.y;
			break;
		case ALIGN_MIDDLE_DOWN:
			m_TextPosition.x=m_Position.x+((m_Size.width-text_W)>>1);
			m_TextPosition.y=m_Position.y+(m_Size.height)-(CHAR_H);
			break;
		case ALIGN_MIDDLE_CENTER:
			m_TextPosition.x=m_Position.x+((m_Size.width-text_W)>>1);
			m_TextPosition.y=m_Position.y+((m_Size.height-CHAR_H)>>1);
			break;
		default:
			m_TextPosition.x=m_Position.x;
			m_TextPosition.y=m_Position.y;			
			break;
	}
	m_TextPosition.x=(m_TextPosition.x>0?m_TextPosition.x:0);
	m_TextPosition.y=(m_TextPosition.y>0?m_TextPosition.y:4);
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//check the objects Size & Position with Its Parrent
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CWnd::CheckSizeWithParent()
{
	if (m_Parent!=POINTERS_POINT_TO_ZERO)
	{
		Point pos=m_Parent->GetPosition();
		if (m_Parent->ID()==FORM_ID)pos.y+=TITLEBAR_SIZE;
		Size size=m_Parent->GetSize();
		if (m_Position.x<pos.x)m_Position.x=pos.x;
		if (m_Size.width>size.width)m_Size.width=size.width;
		if (m_Position.y<pos.y)m_Position.y=pos.y;
		if (m_Size.height>size.height)m_Size.height=size.height;
		if (m_Parent->ID()==CONTAINER_ID) 
		{
		if (m_Position.y<(pos.y+4))m_Position.y+=(7+CHAR_H);
		}
		while((m_Position.x+m_Size.width)>(pos.x+size.width))m_Size.width--;
		while((m_Position.y+m_Size.height)>(pos.y+size.height))m_Size.height--;
		CheckTextAlign();
		CheckTextSize();
	}
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//check the Mouse Clicked Position with objects Position
//Returns True If position was on the Object, otherwise False
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
bool CWnd::IsContainedPoint(const Point* point)
{
	Point len;
	len.x=m_Size.width + m_Position.x;
	len.y=m_Size.height + m_Position.y;
	if ((m_Position.x<=point->x && len.x>=point->x) &&
		 (m_Position.y<=point->y && len.y>=point->y))
			return true;
	return false;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Function to Draw The Object
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CWnd::Draw(){}
//---------------------------------------------------------------------------------
//ADD events
//---------------------------------------------------------------------------------
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Adds a new Click EventHandler routine
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
 	void CWnd::AddMouseClickHandler(CWnd* Receiver)
 {
		MouseClickHandler=Receiver;
 }
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Adds a new Key EventsHandlers routine
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
 void CWnd::AddKeyPressHandler(CWnd* Receiver)
 {
	 KeyPressHandler=Receiver;
 }

//---------------------------------------------------------------------------------
//call events:
//---------------------------------------------------------------------------------
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//call Mouse Click Handlers Function
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CWnd::DoClick(Point* position)
 {
	 SetFocus(true);
	 Click(position);
	 if(m_Parent!=0)Draw();
	 if (MouseClickHandler!=POINTERS_POINT_TO_ZERO)Event(MouseClickHandler,WM_MouseClick,(void*)position);
 }
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
 void CWnd::Click(Point* position){}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
 void CWnd::GotFocus(){if(m_Parent!=0)Draw();}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CWnd::LostFocus(){if(m_Parent!=0)Draw();}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//call KeyPress Handler's Function
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CWnd::KeyPressed(char* key)
{
	if(m_Parent!=0)Draw();
	if (KeyPressHandler!=POINTERS_POINT_TO_ZERO)Event(KeyPressHandler,WM_KeyPress,(void*)key);
}
void CWnd::GlobalEventHandler(CWnd* sender,MessageType message,void* param){}
