#include "CWinMan.h"
CList<CForm*> FormsList;
int Last_Zorder=0;
CForm* Winman_GetHighZorder(void)
{
	int count=FormsList.Count();
	//find the onTop form.
	for (int i=0;i<count;i++)
	{
	 if (FormsList.GetObject(i)->m_Zorder==1)
		 return FormsList.GetObject(i);
	}
	return 0;
}
//The Main Thread
static void Winman_MainThread(void *pvParameters)
{
	CForm* FirstForm=0;
	MSG m;
		coordinate priority=0;
		int FormsCount;
	//the main Thread
	while(1)
	{ 
		{
			//Get The Forms Count
			FormsCount=FormsList.Count();
			if (FirstForm!=0) priority=FirstForm->m_Zorder;
			//check if Last Form is not HighPriority anymore,get new High Prioritty form and Draw it.
			if(priority!=1 && FormsCount!=0)
			{
				FirstForm=Winman_GetHighZorder();
				m.msg=WM_Paint;
				//send a Paint message to the Higher Priority Form.
				OS_PostQueue((FirstForm->MSGProcHandle()),&m,10);
			}
	  }
		OS_DelayTask(1);
	}
}
void Winman_Start(void)
 {
		Display_Init();
		Mouse_Init(&Winman_MouseHook);
		if(OS_CreateTask(NULL,Winman_MainThread,(signed char*)"Main",1))
		{
			//start the os
			OS_Run();
		}
		else 
			Display_PutString(10,10,"Hard Fault",0,10,Yellow);
 }
void Winman_AddForm(CForm *objptr)
{
	if (FormsList.ADD(objptr))
	{
		objptr->m_Zorder=++Last_Zorder;
		
	}
}

void Winman_RemoveForm(CForm *objptr)
{
	if (FormsList.RemoveByref(objptr))
	{
		//Remove the object's prioritty, for the main Thread.
		if (objptr->m_Zorder==1)objptr->m_Zorder=0;
		
		int Count=FormsList.Count();
		if (objptr->m_Zorder==0)
		{
			for (int i=0;i<Count;i++)
				FormsList.GetObject(i)->m_Zorder--;
		}
		else
		{
			CForm* frm;
			for (int i=0;i<Count;i++)
			{
				frm=FormsList.GetObject(i);
				if (frm->m_Zorder > objptr->m_Zorder)
					frm->m_Zorder--;
			}
		}
		if (Count==0)
		{
			LCD_Clear(White);
			for(;;);
		}
		Last_Zorder--;
	}
}

void Winman_SetFormOnTop(CForm* objptr)
{
	if (objptr->m_Zorder!=1)
	{
		int Count=FormsList.Count();
		CForm* frm;
		for (int i=0;i<Count;i++)
		{
			frm=FormsList.GetObject(i);
			if (frm->m_Zorder>objptr->m_Zorder)
				frm->m_Zorder--;
		}
		objptr->m_Zorder=0;
		for (int i=0;i<Count;i++)
			FormsList.GetObject(i)->m_Zorder++;
	}
}

void Winman_MouseHook(Point* position)
{
	MSG msg;
	if (position->x!=0xA5A5A5 && position->y!=0xA5A5A5 )
	{
		msg.msg=WM_MouseClick;
		msg.LParam=(void*)position;
		OS_PostQueueFromISR(Winman_GetHighZorder()->MSGProcHandle(),&msg);
	}
	else
	{
		msg.msg=WM_Paint;
		OS_PostQueueFromISR(Winman_GetHighZorder()->MSGProcHandle(),&msg);
	}
}
void Winman_KeyBoardHook(char* key)
{
	MSG msg;
	msg.msg=WM_KeyPress;
	msg.LParam=(void*)key;
	OS_PostQueueFromISR(Winman_GetHighZorder()->MSGProcHandle(),&msg);
}
