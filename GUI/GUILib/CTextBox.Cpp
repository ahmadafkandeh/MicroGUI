#include "CTextBox.h"
#include <cstring>
using std::strcpy;
using std::strlen;
using std::memcpy;
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Constructor of TextBox
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
CTextBox::CTextBox()
{
	SetTextAlign(ALIGN_LEFT_CENTER);
	SetPosition(10,10);
	SetSize(100,18);
	SetText("Txt");
	m_ID=TEXTBOX_ID;
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CTextBox::ModifyText(char* key)
{
	if (*key>='!' && *key<='z') //if alphanumeric
	{
		int textlen=strlen(m_Text)+1;
		if ( textlen-- >m_TextCurrentLenth & m_TextCurrentLenth<TEXT_MAX_CHARS){
			if ((m_TextCurrentLenth+10)>TEXT_MAX_CHARS)m_TextCurrentLenth+=(TEXT_MAX_CHARS-m_TextCurrentLenth);
			else m_TextCurrentLenth+=10;
			char* text=m_Text;
			m_Text=(char*)manager_HeapAlloc(m_TextCurrentLenth);
			memcpy(m_Text,text,textlen);
			manager_HeapFree((void*) text);
		}
		m_Text[textlen++]=*key;
		m_Text[textlen]=0;
		CheckTextSize();
		CheckTextAlign();
	}
	else
	{
	}
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CTextBox::KeyPressed(char* key)
{
	ModifyText(key);
  if(m_Parent!=0)Draw();
	if (KeyPressHandler!=POINTERS_POINT_TO_ZERO)Event(KeyPressHandler,WM_KeyPress,(void*)key);
	
}
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
//Draw the Text Box
//&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*
void CTextBox::Draw()
{
	if (m_Visible)
	{
		int offset = 0;
		int textlen = strlen( m_Text );
		if ( textlen > m_LenthOfShownText )
			offset = textlen - m_LenthOfShownText;
		//Draw shape of Text Box
		Display_DrawRectangle( m_Position.x , m_Position.y , m_Size.width , m_Size.height , m_BackColor );
		//Draw BG if Exists
		if (m_BGptr!=0) 
			Display_DrawImage(( m_Position.x + BACKCOLOR_MARGIN ),
												( m_Position.y + BACKCOLOR_MARGIN ),
												( m_Size.width - BACKCOLOR_MARGIN ),
		                    ( m_Size.height - BACKCOLOR_MARGIN ),m_BGptr);
		//draw text
		Display_PutString( m_TextPosition.x , m_TextPosition.y , m_Text,offset , m_LenthOfShownText , m_TextColor );
		//draw Curssor if focused on text
		if (m_Focus)	
		{
			int templinelen = textlen;
			while( templinelen > m_LenthOfShownText )templinelen--;
			int tempx = m_TextPosition.x + ( templinelen * ( CHAR_W + 2 ) + 1 );
			int tempy = m_TextPosition.y + CHAR_H;
			Display_DrawLine( tempx , m_TextPosition.y , tempx , tempy , Black );
		}
	}
}
