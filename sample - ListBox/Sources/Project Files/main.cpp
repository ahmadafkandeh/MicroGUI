#include <LPC17xx.H>
#include "CWinMan.h"
#include "CButton.h"
#include "CForm.h"
#include "cListBox.h"
#include "CTextBox.h"
#include "CLabel.h"
#include "Type.h"

class Window:public CForm
{

	public:	Window()
	{
		InitializeComponnents();
	}
	private:	virtual void InitializeComponnents()
	{
		SetPosition(0,0);
		SetBackColor(Red);
		SetSize(239,340);
		m_Style=FORM_STYLE_NONE;
		SetText("Window");
		//----------------------
		List.SetPosition(10,20);

		for (int i=0;i<15;i++)
		{
		char c[1]={'0'+i};
		List.AddItem(c);	
		}
		List.AddMouseClickHandler(this);
		//------------------------
		txt.SetPosition(10,145);
		//------------------------
		AddControl(&txt);
		AddControl(&List);
	}
	public: virtual void GlobalEventHandler(CWnd* sender,MessageType message,void* param)
	{
		if(sender==(CWnd*)&List)
			if (message==WM_MouseClick)
			{	
				txt.SetText(List.GetText());
			}
	}
	CListBox List;
	CTextBox txt;
	
};
static void Win1Task(void *pvParameters);
Window* win1=new Window();
int main(void)
{
	
	OS_CreateTask(&win1->m_HWnd,Win1Task,(signed char*)"w1",1);
	Winman_Start();
	while(1);
};
static void Win1Task(void *pvParameters)
	{
		Winman_AddForm(win1);
		while(1)
		{
		if (win1->m_Zorder==1){
			win1->WndProc();
		}
		OS_DelayTask(1);
		}
	};
