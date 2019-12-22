#ifndef _CIPMASKED_H
#define _CIPMASKED_H
#include "Ctextbox.h"
class CIpMasked: public CTextBox
{
public:
	CIpMasked();
	virtual void KeyPress(char*);
	virtual void SetSize(coordinate,coordinate);
private:
	int 				 ConvertTextToNumber(char*);
	char* 			 ConvertNumberToText(int number);
	void 				 ConvertIpToText();
private:
	short int    m_state;
};
#endif
