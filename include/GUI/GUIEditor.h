#ifndef GUIEDITOR_H
#define GUIEDITOR_H
#include "raylib.h"
#include <imgui.h>

namespace GUIEditor
{
	void Init(int width, int height);
	void BeginOffscreenDraw();
	void EndOffscreenDraw();
	void Draw();
}
#endif