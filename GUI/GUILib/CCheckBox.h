#ifndef _CCheckBox_H
#define _CCheckBox_H
#include "CWnd.h"
//------------------------------------------------------------
//margins:
#define CheckBox_Check_Margin_2 2
class CCheckBox:public CWnd
{
//functions:
public:
	CCheckBox();
	virtual void 	Draw();
	virtual void 	Click(Point*);
	void 					SetChecked(bool);
	bool 					GetChecked();
//variables:
private:
	bool 					m_Checked	; //saves the checked state.
	
};
#endif
