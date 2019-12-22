#include "Mousedriver.h"
#include "Type.h"
void Mouse_Init(MouseClickProc mouseproc)
{
	EINTInit();
	Touch_Init(mouseproc);
//	Touch_Adjust();
//	Get_Adjdata();
}
