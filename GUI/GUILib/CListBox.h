#ifndef _CListBox_H
#define _CListBox_H
#include "CWnd.h"
#include "CList.h"
#include "CScrollBar.h"
class CListBox: public CWnd
{
	//functions:
public:
	CListBox();
	CListBox(bool _referencemode);
	~CListBox();
	void 							AddItem(char* item);
	void 							SetSelectedIndex(int index);
	int 							GetSelectedIndex();
	void							RemoveItem(int Index);
	virtual void 			Draw();
	virtual void 			Click(Point*);
	virtual void 			SetSize(coordinate,coordinate);
	virtual void 			SetPosition(coordinate _top , coordinate _left);

private:
	void 							DrawItems();
	void 							CheckClickOnItems(const Point*);
	void							ListBox_ScrollbarEventHandler(Point*);
//variables:	
private:
	CList<char*> 			m_Items; //keeps the added Items

	int 							m_SelectedIndex; //saves the index of selected item
	
	int 							m_StartIndex; 

	CScrollBar 				m_V_ScrollBar; //the vertically scrollBar

	bool 							m_contains_scroll; //this variable will automatically sets to true or false with any add/remove items.
	
	bool							m_ReferenceMode; /*if true the list box saves the address of items,
																			*otherwise saves a copy of items.
																			*if true, any changes on the original data will change the item value.
																		 */

	int 							HowManyItemCanShow;
};
#endif
