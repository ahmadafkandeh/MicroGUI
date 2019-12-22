#include "CButton.h"
#include <cstring>
using std::strcmp;
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//constructor of CButton class
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
CButton::CButton()
{
	m_AutoSize=false;
	m_TextAlign=ALIGN_MIDDLE_CENTER;
	SetBackColor(Blue);
	SetSize(60,30);
	SetText("Btn");
	m_ID=BUTTON_ID;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Function to Draw The Object
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CButton::Draw()
{
	if (m_Visible)
	{
		//Set BackColor
		Display_Fill(m_Position.x+BACKCOLOR_MARGIN,m_Position.y+BACKCOLOR_MARGIN,m_Size.width-BACKCOLOR_MARGIN,m_Size.height-BACKCOLOR_MARGIN,m_BackColor);
		//Draw BG if Exists
		if (m_BGptr!=POINTERS_POINT_TO_ZERO) Display_DrawImage(m_Position.x+BACKCOLOR_MARGIN,m_Position.y+BACKCOLOR_MARGIN,m_Size.width-BACKCOLOR_MARGIN,m_Size.height-BACKCOLOR_MARGIN,m_BGptr);
		//--------------------------------------------------------
		//body of Button
		//Top
		Display_DrawLine(m_Position.x+BUTTON_BIVEL_MARGIN_1,m_Position.y,(m_Position.x+m_Size.width)-BUTTON_BIVEL_MARGIN_1,m_Position.y,Black);
		//Bottom
		Display_DrawLine(m_Position.x+BUTTON_BIVEL_MARGIN_1,m_Position.y+m_Size.height,(m_Position.x+m_Size.width)-BUTTON_BIVEL_MARGIN_1,m_Position.y+m_Size.height,Black);
		//left
		Display_DrawLine(m_Position.x,m_Position.y+BUTTON_BIVEL_MARGIN_1,m_Position.x,m_Position.y+m_Size.height-BUTTON_BIVEL_MARGIN_1,Black);
		//right
		Display_DrawLine((m_Position.x+m_Size.width),m_Position.y+BUTTON_BIVEL_MARGIN_1,(m_Position.x+m_Size.width),m_Position.y+m_Size.height-BUTTON_BIVEL_MARGIN_1,Black);
		
		//points
		//Top
		Display_DrawLine(m_Position.x+BUTTON_BIVEL_MARGIN_1,m_Position.y+BUTTON_BIVEL_MARGIN_1,m_Position.x+BUTTON_BIVEL_MARGIN_2,m_Position.y+BUTTON_BIVEL_MARGIN_1,Black);
		Display_DrawLine((m_Position.x+m_Size.width-BUTTON_BIVEL_MARGIN_1),(m_Position.y+BUTTON_BIVEL_MARGIN_1),(m_Position.x+m_Size.width),(m_Position.y+BUTTON_BIVEL_MARGIN_1),Black);
		//bottom
		Display_DrawLine(m_Position.x+BUTTON_BIVEL_MARGIN_1,(m_Position.y+m_Size.height)-BUTTON_BIVEL_MARGIN_1,(m_Position.x)+BUTTON_BIVEL_MARGIN_2,(m_Position.y+m_Size.height)-BUTTON_BIVEL_MARGIN_1,Black);
		Display_DrawLine((m_Position.x+m_Size.width-BUTTON_BIVEL_MARGIN_1),(m_Position.y+m_Size.height-BUTTON_BIVEL_MARGIN_1),(m_Position.x+m_Size.width),(m_Position.y+m_Size.height-BUTTON_BIVEL_MARGIN_1),Black);
		//------------------------------------------------------
		//body of button's bevel
		//Top
		Display_DrawLine(m_Position.x+BUTTON_BIVEL_MARGIN_2,m_Position.y+BUTTON_BIVEL_MARGIN_1,(m_Position.x+m_Size.width)-BUTTON_BIVEL_MARGIN_2,m_Position.y+BUTTON_BIVEL_MARGIN_1,LightGrey);
		//bottom
		Display_DrawLine(m_Position.x+BUTTON_BIVEL_MARGIN_2,(m_Position.y+m_Size.height)-BUTTON_BIVEL_MARGIN_1,(m_Position.x+m_Size.width)-BUTTON_BIVEL_MARGIN_2,(m_Position.y+m_Size.height)-BUTTON_BIVEL_MARGIN_1,LightGrey);
		//left
		Display_DrawLine(m_Position.x+BUTTON_BIVEL_MARGIN_1,m_Position.y+BUTTON_BIVEL_MARGIN_2,m_Position.x+BUTTON_BIVEL_MARGIN_1,(m_Position.y+m_Size.height)-BUTTON_BIVEL_MARGIN_2,LightGrey);
		//right
		Display_DrawLine((m_Position.x+m_Size.width)-BUTTON_BIVEL_MARGIN_1,m_Position.y+BUTTON_BIVEL_MARGIN_2,(m_Position.x+m_Size.width)-BUTTON_BIVEL_MARGIN_1,(m_Position.y+m_Size.height)-BUTTON_BIVEL_MARGIN_2,LightGrey);
		
		//Top
		Display_DrawLine(m_Position.x+BUTTON_BIVEL_MARGIN_1,m_Position.y+BUTTON_BIVEL_MARGIN_2,m_Position.x+BUTTON_BIVEL_MARGIN_2,m_Position.y+BUTTON_BIVEL_MARGIN_2,LightGrey);
		Display_DrawLine(m_Position.x+m_Size.width-BUTTON_BIVEL_MARGIN_2,m_Position.y+BUTTON_BIVEL_MARGIN_2,m_Position.x+m_Size.width-BUTTON_BIVEL_MARGIN_1,m_Position.y+BUTTON_BIVEL_MARGIN_2,LightGrey);
		//bottom
		Display_DrawLine(m_Position.x+BUTTON_BIVEL_MARGIN_1,(m_Position.y+m_Size.height)-BUTTON_BIVEL_MARGIN_2,(m_Position.x)+BUTTON_BIVEL_MARGIN_2,(m_Position.y+m_Size.height)-BUTTON_BIVEL_MARGIN_2,LightGrey);
		Display_DrawLine(m_Position.x+m_Size.width-BUTTON_BIVEL_MARGIN_2,(m_Position.y+m_Size.height)-BUTTON_BIVEL_MARGIN_2,m_Position.x+m_Size.width-BUTTON_BIVEL_MARGIN_1,(m_Position.y+m_Size.height)-BUTTON_BIVEL_MARGIN_2,LightGrey);
		//------------------------------------------------------
		//Draw the text of Button
		Display_PutString(m_TextPosition.x,m_TextPosition.y,m_Text,0,m_LenthOfShownText,m_TextColor);
	}
}
