#ifndef CButton_H
#define CButton_H
#include "CWnd.h"
//-------------------------------------------------------------
//margins:
#define BUTTON_BIVEL_MARGIN_1 1
#define BUTTON_BIVEL_MARGIN_2	2
//-------------------------------------------------------------
class CButton :public CWnd
{
public:
	CButton();
	virtual void 	Draw();
};

#endif
