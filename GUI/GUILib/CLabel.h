#ifndef _CLabel_H
#define _CLabel_H
#include "CWnd.h"
//-------------------------------------------------------
//margins
#define LABEL_H_MARGIN				4
//-------------------------------------------------------
class CLabel : public CWnd
{
//functions:
public:
	CLabel();
	void 					SetAutoSize(bool flag);
	bool 					GetAutoSize();
	virtual void 	Draw();
};
#endif
