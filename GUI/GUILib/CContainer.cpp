#include "CContainer.h"
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//constructor of Container class
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
CContainer::CContainer()
{
	SetText("Container");
	SetTextAlign(ALIGN_LEFT_TOP);
	SetSize(100,100);
	SetPosition(10,10);
	m_ID=CONTAINER_ID;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Destructor of Container class
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
CContainer::~CContainer()
{
	for(int i=m_Childs.Count();i>=0;i--)
	{
		//get the childs by their index
		CWnd* child= m_Childs.GetObject(i);
		//remove the parrent of object
		child->RemoveParent(this);
		//remove child from conatiner list
 		m_Childs.RemoveByindex(i);
		
		if(child->ID()==LISTBOX_ID)	manager_HeapFree ((CListBox**)child);
		else manager_HeapFree( child);
	}
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//add control function
//this function will get the objects address and adds them to Container
//args:
//childptr: the object's address
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CContainer::AddControl(CWnd* childptr)
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
	if(m_Parent!=0)Draw();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//this Function removes the objects from container with thier address
//args:
//childptr: the address of object
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CContainer::RemoveControl(CWnd* childptr)
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
	if(m_Parent!=0)Draw();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Function to Draw The Object
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CContainer::Draw()
{
	if (m_Visible)
	{
		//draw the body
		Display_DrawRectangle(m_Position.x,m_Position.y,m_Size.width,m_Size.height,m_BackColor);
		//Draw BG if Exists
		if (m_BGptr!=POINTERS_POINT_TO_ZERO) Display_DrawImage((m_Position.x+BACKCOLOR_MARGIN),(m_Position.y+BACKCOLOR_MARGIN),(m_Size.width-BACKCOLOR_MARGIN),(m_Size.height-BACKCOLOR_MARGIN),m_BGptr);
		//draw the title of conatiner
		Display_PutString(m_TextPosition.x,m_TextPosition.y-CONTAINER_H_MARGIN,m_Text,0,m_LenthOfShownText,m_TextColor);
		//draw childs
		ReDrawChilds();
	}
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Function to draw the childs
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CContainer::ReDrawChilds()
{
	//get the count of childs
	int count=m_Childs.Count();
	//get the objects by their index and call their Draw Functions
	for (int i=0;i<count;i++)
		(*m_Childs.GetObject(i)).Draw();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//keypress event Handler
//send the key to the Focused child's keypress event handler.
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CContainer::KeyPressed(char* key)
{
	//send the key to the Focused child's keypress event handler.
	if(Last_Child_Focused!=POINTERS_POINT_TO_ZERO)Last_Child_Focused->KeyPressed(key);
	if (KeyPressHandler!=POINTERS_POINT_TO_ZERO)Event(KeyPressHandler,WM_KeyPress,(void*)key);
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//mouse click event handler
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CContainer::Click(Point* position)
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
