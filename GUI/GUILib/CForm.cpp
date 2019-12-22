#include "CForm.h"
#include "CListBox.h"
#include "CWinman.h"
#include "Cstring"
#include "OSAL.h"
using std::strlen;
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//constructor of Form class
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
CForm::CForm()
{
	m_ChildCount=0;
	m_btn_Close.SetSize(25,TITLEBAR_SIZE);
	m_btn_Close.SetBackColor(Red);
	m_btn_Close.SetPosition((m_Position.x+m_Size.width-m_btn_Close.GetSize().width),m_Position.y);
	m_btn_Close.SetTextAlign(ALIGN_MIDDLE_TOP);
	m_btn_Close.SetTextColor(White);
	m_btn_Close.SetText("X");
	m_Style=FORM_STYLE_FIXED;
	m_ID=FORM_ID;
	//create Queue for WndQueue.
	OS_CreateQueue(&m_FormQueueHandle,MAX_QUEUE_SIZE,sizeof(MSG));
	InitializeComponnent();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Destructor of Form Class
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
CForm::~CForm()
{
	Dispose();

}
void CForm::Dispose()
{
		for(int i=m_Childs.Count();i>=0;i--)
	{
		CWnd* child= m_Childs.GetObject(i);
		child->RemoveParent(this);
 		m_Childs.RemoveByindex(i);
		if(child->ID()==LISTBOX_ID)	manager_HeapFree((void*) ((CListBox**)child));
		else manager_HeapFree((void*)child);
	}
	//Remove the WndProc Queue.
	OS_DeleteQueue(m_FormQueueHandle);
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CForm::InitializeComponnent(){}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//the Main Message Proc Handler
//this function must be called from a thread.
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CForm::WndProc(void)
{
	Point mousepos;
	char key;
	MessageType m;
	while(OS_ReadQueue(m_FormQueueHandle,&message,1))
		{
			m=message.msg;
			switch (m)
			{
				case WM_Paint:
					Draw();
					break;
				case WM_Close:
					Winman_RemoveForm(this);
					break;
				case WM_MouseClick:
					mousepos.x=((Point*)(message.LParam))->x;
					mousepos.y=((Point*)(message.LParam))->y;
					DoClick(&mousepos);
					break;
				case WM_KeyPress:
					key=*((char *)message.LParam);
					KeyPressed(&key);
					break;
			}
			OS_DelayTask(1);
		}
	}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//AddControl Function
//this Func takes a CWnd address and saves it in Children List.
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CForm::AddControl(CWnd *childptr)
{
	//set a internal handle on objects
	childptr->SetHandle(m_Childs.ADD(childptr));
	//remove the last object's focus
	if (Last_Child_Focused!=POINTERS_POINT_TO_ZERO)Last_Child_Focused->SetFocus(false);
	//set focus on the current object
	childptr->SetFocus(true);
	//set the current object's Parrent
	childptr->SetParent(this);
	//set current object as the Focused object
	Last_Child_Focused=childptr;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//this Func takes a child's address and removes it from Children List
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CForm::RemoveControl(CWnd *childptr)
{
	//remove the object from container's List
	m_Childs.RemoveByref(childptr);
	//remove the objects parrent
	childptr->RemoveParent(this);
	//check if this object Gots focus, give focus to last item in container
	if (childptr->GetFocus()){
		Last_Child_Focused=m_Childs.GetObject(m_Childs.Count()-1);
		Last_Child_Focused->SetFocus(true);
	}
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
////Set Size Function
//this Func sets the size of Form
//
//args:
//_width: the width of Form
//_height: the height of Form
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CForm::SetSize(coordinate _width,coordinate _height)
{
	m_Size.width=_width;
	m_Size.height=_height;
	m_btn_Close.SetPosition((m_Position.x+m_Size.width-m_btn_Close.GetSize().width),m_Position.y);
	CheckSizeWithParent();
	CheckTextSize();
	CheckTextAlign();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Set Position Func
//this Func Sets the position of Form
//args:
//_top: the Distance of top of Display
//_left: the Distance of left of Display
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CForm::SetPosition(coordinate _top,coordinate _left)
{
	m_Position.x=_top;
	m_Position.y=_left;
	m_btn_Close.SetPosition((m_Position.x+m_Size.height-m_btn_Close.GetSize().width),m_Position.y);
	CheckSizeWithParent();
	CheckTextAlign();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Draw the Form
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CForm::Draw()
{
	if (m_Visible)
	{
		//draw the body
		Display_DrawRectangle(m_Position.x,m_Position.y,m_Size.width,m_Size.height,m_BackColor);
		//Draw BG if Exists
		if (m_BGptr!=POINTERS_POINT_TO_ZERO) Display_DrawImage((m_Position.x+BACKCOLOR_MARGIN),(m_Position.y+BACKCOLOR_MARGIN),(m_Size.width-BACKCOLOR_MARGIN),(m_Size.height-BACKCOLOR_MARGIN),m_BGptr);
		if (m_Style==FORM_STYLE_FIXED)
		{
			Display_Fill(m_Position.x,m_Position.y,m_Size.width,TITLEBAR_SIZE,Blue);
			//draw the title of from
			Display_PutString(m_Position.x,m_Position.y,m_Text,0,strlen(m_Text),White);
			//draw the close button
			m_btn_Close.Draw();
		}
		ReDrawChilds();
	}
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Draw the Children
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CForm::ReDrawChilds()
{
	int count=m_Childs.Count();
	for (int i=0;i<count;i++)
		m_Childs.GetObject(i)->Draw();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//keypress event Handler
//send the key to the Focused child's keypress event handler.
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CForm::KeyPressed(char* key)
{
	//send the key to the Focused child's keypress event handler.
	if(Last_Child_Focused!=POINTERS_POINT_TO_ZERO)Last_Child_Focused->KeyPressed(key);
	if (KeyPressHandler!=POINTERS_POINT_TO_ZERO)Event(KeyPressHandler,WM_KeyPress,(void*)key);
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//mouse click event handler
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CForm::Click(Point* position)
{
		MSG m;
		m.msg=WM_Close;
	if (m_btn_Close.IsContainedPoint(position) && m_Style==FORM_STYLE_FIXED)
		//post a close message to the forms queue.
		OS_PostQueue( m_FormQueueHandle , &m , 10 );
	else
	{
		//get the count of childs
		int Count=m_Childs.Count();
		//check for which child has the position of mouse position
		for (int i=0;i<Count;i++)
		{
			//get the child by its index
			CWnd* child=m_Childs.GetObject(i);
			//check for position
			if (child->IsContainedPoint(position))
			{
				////remove the last child focus
				Last_Child_Focused->SetFocus(false);
				//call the current child's mouse click handler
				child->DoClick(position);
				//set current child as Focused
				Last_Child_Focused=child;
				break;
			}
		}
	}
}


