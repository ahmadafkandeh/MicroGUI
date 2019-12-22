#ifndef CContainer_H
#define CContainer_H
#include "CWnd.h"
#include "CList.h"
#include "CListBox.h"
//-----------------------------------------------------
//margins:
#define CONTAINER_H_MARGIN				4

class CContainer: public CWnd
{
//functions
public:
	CContainer();
	~CContainer();
	void 						AddControl(CWnd*);
	void 						RemoveControl(CWnd*);
	void						ReDrawChilds();
	virtual void 		Draw();
	virtual void 		Click(Point*);
	virtual void 		KeyPressed(char*);
	
//variables
private:
	CList<CWnd*> 		m_Childs; //saves the address of childs
	CWnd* 					Last_Child_Focused; //saves the address of focused child
};
#endif
