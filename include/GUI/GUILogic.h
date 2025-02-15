#ifndef  GUILOGIC_H
#define GUILOGIC_H

#include "LogicElements.h"

//not used yet early prototype
struct GUILogicWindow
{
	std::shared_ptr<LogicElements::LogicGate> selected;
	int no_of_output; 
	int no_of_input; 
};

void GUILogic_draw();

#endif // !define GUILOGIC_H
