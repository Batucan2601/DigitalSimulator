#ifndef GUITOOLS_H
#define GUITOOLS_H
#include "LogicElements.h"
namespace GUITools
{
	enum class DragDropState
	{
		DRAGGING,
		DROPPED,
		IDLE,
	};
	struct GUIToolsDragDrop
	{
		DragDropState state;
		LogicElements::GateType gateType;
	};
	extern GUIToolsDragDrop dragDrop;
	void GUITools_BasicLogicDisplay();
	void GUITools_Display();
}


#endif 