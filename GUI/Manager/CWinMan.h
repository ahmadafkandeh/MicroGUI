#ifndef CWinMan_H
#define CWinMan_H

#include "Type.h"
#include "CList.h"
#include "CForm.h"
#include "MouseDriver.h"
#include "DisplayDriver.h"
#include "OSAL.h"

//Functions
extern  CForm* 	Winman_GetHighZorder(void);
extern  void 		Winman_AddForm(CForm *objptr);
extern	void 		Winman_RemoveForm(CForm *objptr);
extern	void		Winman_Start(void);
extern	void 		Winman_MouseHook(Point*);
extern  void 		Winman_KeyBoardHook(char*);
extern  void 		Winman_SetFormOnTop(CForm*);

#endif
