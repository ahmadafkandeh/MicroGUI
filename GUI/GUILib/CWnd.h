#ifndef _CWnd_H
#define _CWnd_H
#include "CObject.h"
#include "Messages.h"
//#include "EventHandler.h"
//-----------------------------------------------------------------
//TextAlignment definitions
#define ALIGN_LEFT_TOP 				0
#define	ALIGN_LEFT_DOWN				1
#define	ALIGN_LEFT_CENTER 		2
#define	ALIGN_RIGHT_TOP 			3
#define	ALIGN_RIGHT_DOWN 			4
#define	ALIGN_RIGHT_CENTER 		5
#define	ALIGN_MIDDLE_TOP 			6
#define	ALIGN_MIDDLE_DOWN 		7
#define	ALIGN_MIDDLE_CENTER 	8
//other def
#define TEXT_MAX_CHARS			100
#define TEXT_DEFAULT_LENTH	20
#define TITLEBAR_SIZE	20

//margins
#define TEXT_MARGIN_OF_SIDES	2
#define TEXT_CURSSOR_SIZE			8

//define MSG
typedef struct TagMSG{
	MessageType msg;
	void* 			WParam;
	void* 			LParam;
}MSG;
class CWnd : public CObject //, public EventHandler
{
//functions:
public:
	CWnd();
	~CWnd();
	int 					ID();
	virtual void	Dispose();
	Size	 				GetSize();
	virtual void 	SetSize(coordinate,coordinate);
	Point 				GetPosition();
	virtual void 	SetPosition(coordinate _top , coordinate _left);
	char*					GetText();
	void 					RemoveParent(CWnd*);
	bool 					SetParent(CWnd*);
	void 					SetText(char *text);
	void 					SetTextColor(ColorRef color);
	void					SetTextAlign(char align);
	bool 					GetEnabled();
	void 					SetEnabled(bool);
	bool 					GetVisible();
	void 					SetVisible(bool);
	void 					SetBackColor(ColorRef color);
	ColorRef			GetBackColor();
	bool					GetFocus();
	virtual void 	SetFocus(bool);
	void 					SetBackGroundImage(unsigned char *bmp); 
	virtual void 	Draw();
	hwnd_type 		GetHandle(); //property to get Handle
	void 					SetHandle(hwnd_type); //property to set handle
	bool 					IsContainedPoint(const Point*);
	virtual void  GlobalEventHandler(CWnd* sender,MessageType message,void* param);
	void  				Event(CWnd* Receiver,MessageType message,void* param)
	{
		if(Receiver!=0)
			(Receiver)->GlobalEventHandler(this,message,param);
	}
protected:
	void 					CheckTextSize();
	void 					CheckTextAlign();
	void					CheckSizeWithParent();
//--------------------------------------------------------------------------------
//mouse events:
public:
	void 						AddMouseClickHandler(CWnd* Receiver);
	void 						DoClick(Point*);
	protected:
	virtual void 		Click(Point*);
//KeyBoard Events:
public:
	void 						AddKeyPressHandler(CWnd*Receiver);
	virtual void 		KeyPressed(char*);
//other Events:
	virtual void 		GotFocus();
	virtual void		LostFocus();
//-------------------------------------------------------------------------------
//variables
public :
	hwnd_type 			m_HWnd; //keeps the handler Number of object
protected:
	Size 						m_Size; //Size Of Object
	Point 					m_Position; //Object's Position
	Point 					m_TextPosition; //Internal value, used for draw the Text of objects: Text Position
	char 						m_TextAlign; //Internal value, used for used for draw the Text of objects
  char 					* m_Text; //internal value to Save the object's text
	ColorRef 				m_TextColor;

	bool 						m_Enabled;
	bool 						m_Visible;
	bool 						m_AutoSize;
	bool 						m_Focus;
	unsigned char	* m_BGptr; //saves the backGround's Address
	ColorRef 				m_BackColor;
	int 						m_LenthOfShownText; //
	int 						m_TextCurrentLenth; 
	int 						m_ID;//to get type of Cwnd,CWnd's Types defines in "CWndID.h" header file.
protected:
  CWnd 				  * m_Parent;//to set parent window or container to an object, if the object adds to a form(or container) this pointer will /////////..../////....////
//events:
protected:
	CWnd *	MouseClickHandler;
	CWnd *	KeyPressHandler;
//create MSGProc
	MSG message;
};
#endif
