#include "CCheckBox.h"
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//constructor of CheckBox
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
CCheckBox::CCheckBox()
{
	m_AutoSize=true;
	SetText("CheckBox");
	m_Checked=false;
	m_ID=CHECKBOX_ID;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to SetChecked
//args:
//value: a boolian to change the m_Checked value.
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CCheckBox::SetChecked(bool value)
{
	m_Checked=value;
	if(m_Parent!=0)Draw();
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//property to Get Checked
//it will return the m_Checked value.
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
bool CCheckBox::GetChecked()
{
	return m_Checked;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Function to Draw The Object
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CCheckBox::Draw()
{
	if (m_Visible)
	{
		//draw the body
		Display_Fill(m_Position.x,m_Position.y,m_Size.width+30,m_Size.height,m_BackColor);
		//draw box
		Display_DrawRectangle(m_Position.x+BACKCOLOR_MARGIN,m_Position.y+BACKCOLOR_MARGIN,10,10,White);
		//draw the text
		Display_PutString(m_TextPosition.x+12,m_TextPosition.y,m_Text,0,m_LenthOfShownText,m_TextColor);
		//draw check
		if (m_Checked)Display_Fill(m_Position.x+CheckBox_Check_Margin_2,m_Position.y+CheckBox_Check_Margin_2,10-CheckBox_Check_Margin_2,10-CheckBox_Check_Margin_2,Green);
			
	}
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Click event Handler
//args:
//position: the mouse position
//on click the m_Checked will be change, and calls the Draw to update the 
//checkBox
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CCheckBox::Click(Point* position)
{
	m_Checked=!m_Checked;
}
