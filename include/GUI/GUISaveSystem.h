#ifndef GUISAVESYSTEM_H
#define GUISAVESYSTEM_H
#include <string>
#include "ImGuiFileDialog.h"
#include "LogicElements.h"
namespace GUISaveSystem
{
	extern std::string saveFilePath;
	extern bool is_on_save; 
	bool loadFile(std::shared_ptr<CircuitElements::Circuit> circuit);
	bool saveFile(std::shared_ptr<CircuitElements::Circuit> circuit);
	void draw();
}
#endif 