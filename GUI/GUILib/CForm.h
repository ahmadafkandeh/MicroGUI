#ifndef _CForm_H
#define _CForm_H
#include "CWnd.h"
#include "Clist.h"
#include "CButton.h"
//------------------------------------------------------
//styles
#define FORM_STYLE_NONE					0
#define FORM_STYLE_FIXED				1
//queues Size
#define MAX_QUEUE_SIZE		15
//------------------------------------------------------

class CForm: public CWnd
{
//functions:
public:
	CForm();
	~CForm();
	virtual void	InitializeComponnent(void);
	void 					AddControl(CWnd *childptr);
	void 					RemoveControl(CWnd *childptr);
	virtual void 	Draw();
	virtual void  SetPosition(coordinate,coordinate);
	virtual void  SetSize(coordinate,coordinate);
	virtual void 	Click(Point* Position);
	virtual void 	KeyPressed(char*);
	virtual void	Dispose();
private:
	void 					ReDrawChilds();
//variables:
protected:
	CList<CWnd*> 	m_Childs; //saves the child's address.
	int 					m_ChildCount; //saves the Num of children
	CWnd* 				Last_Child_Focused; //saves the address of focused child
	CButton 			m_btn_Close; //the Close button.
	u8						m_Style; //saves the style of form.
public:
	int 					m_Zorder;//preority of form

//OS:

public:
//Tasks for os:
void 		WndProc(void);

//queue Handle:
protected:
OS_QueueHandle 	m_FormQueueHandle;
public:
OS_QueueHandle  MSGProcHandle(){return m_FormQueueHandle;};
};
#endif
