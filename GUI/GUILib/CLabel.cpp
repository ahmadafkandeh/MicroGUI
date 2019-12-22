#include "CLabel.h"
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//constructor of CLabel Class
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
CLabel::CLabel()
{
	m_AutoSize=true;
	SetText("Label:");
	m_ID=LABEL_ID;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property for set the value of autosize
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CLabel::SetAutoSize(bool flag)
{
	m_AutoSize=flag;
	
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property for get the value of autosize
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
bool CLabel::GetAutoSize()
{
	return m_AutoSize;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Function to Draw The Object
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CLabel::Draw()
{
	if (m_Visible)
	{
		//draw the body of Label
		Display_Fill(m_TextPosition.x,m_TextPosition.y-BACKCOLOR_MARGIN,m_Size.width,m_Size.height,m_BackColor);
		//Draw BG if Exists
		if (m_BGptr!=0) Display_DrawImage((m_Position.x+BACKCOLOR_MARGIN),(m_Position.y+BACKCOLOR_MARGIN),(m_Size.width-BACKCOLOR_MARGIN),(m_Size.height-BACKCOLOR_MARGIN),m_BGptr);
		//draw the Text
		Display_PutString(m_TextPosition.x,m_TextPosition.y-LABEL_H_MARGIN,m_Text,0,m_LenthOfShownText,m_TextColor);
	}
}
