#ifndef _CTextBox_H
#define _CTextBox_H
#include "Type.h"
#include "CWnd.h"
//-------------------------------------------------------------------
//-------------------------------------------------------------------
class CTextBox : public  CWnd
{
//functions:
public:	
	CTextBox();
	virtual void 		Draw();
private:
	void 						ModifyText(char *);
//events
public:
	virtual void 		KeyPressed(char*);
};
#endif
