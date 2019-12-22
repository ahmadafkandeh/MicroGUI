#ifndef _OnScreenKeyboard_H
#define _OnScreenKeyboard_H
#include "Cwnd.h"
#include "CButton.h"
#include "CTextBox.h"
#include "CMemo.h"
#include "CIPMasked.h"

class OnScreenKeyboard:public CWnd
{
public:
	OnScreenKeyboard();
	void 			 	  Call(CMemo* caller,CWnd* CallerParent);
	void 			 	  Call(CTextBox* caller,CWnd* CallerParent);
	void 			 	  Call(CIpMasked* caller,CWnd* CallerParent);
private:
	virtual void 	Draw();
	
private:
	CWnd* 				m_CallerPtr;
};
#endif
