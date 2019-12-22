#ifndef _CMemo_H
#define _CMemo_H
#include "CWnd.h"
#include "CList.h"
#include "CScrollBar.h"
//-------------------------------------------------------------------
#define MEMO_MAX_LINES				100
#define MEMO_MAX_CHARS				100
//-------------------------------------------------------------------
class CMemo : public CWnd
{
//functions
 public:
 	CMemo();
	~CMemo();
	virtual void 		Click(Point*);
	virtual void 		KeyPressed(char*);
	virtual void		Draw();
  void 						AddTextToLine(const char*);
	virtual void  	SetSize(coordinate,coordinate);
	virtual void 	  SetPosition(coordinate _top , coordinate _left);
private:
	void 						AddLine();
	void					  AddCharToLine(char);
	
	void 						RemoveCharFromLine();
	void 						DrawItems();
	void 						Vertical_ScrollBarEventHandler(Point*);
	void						Horizental_ScrollBarEventHandler(Point*);
	void 						CheckClickOnItems(Point*);
  void						GetMaxLineLen();
//variables
private:
	char					* m_MemoText;
	char 					* m_MemoIndexOfLines;
	int 						m_LinesCount;
 	int 						m_CurrentLine;
 	int 						m_StartIndex;
 	int							m_StartCharIndex;
 	int 						m_Max_Line_Char_Len;
	int 						m_CurrentCurssorPos;
	bool 						m_contains_Vscroll;
	bool 						m_contains_Hscroll;
	CScrollBar 			m_Vertical_ScrollBar;
	CScrollBar 			m_Horizental_ScrollBar;
};
#endif
