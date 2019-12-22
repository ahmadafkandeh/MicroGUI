#include <LPC17xx.H>
#include "CWinMan.h"
#include "CForm.h"
#include "cMemo.h"
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
		//--------------------
		btn.SetText("art");
		//--------------------
		memo.SetPosition(10,20);
	  memo.AddTextToLine("Artemis Angel");
		char k=KEYS_ENTER;
		memo.KeyPressed(&k);
		memo.AddTextToLine("Hello World");
		
		//------------------------
		AddControl(&memo);
		AddControl(&btn);
	}
	public: virtual void GlobalEventHandler(CWnd* sender,MessageType message,void* param)
	{
		
	}
	CMemo memo;
	CButton btn;
};
static void Win1Task(void *pvParameters);
Window* win1=new Window();
int main(void)
{
	//
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
