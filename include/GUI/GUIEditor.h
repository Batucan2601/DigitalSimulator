#ifndef GUIEDITOR_H
#define GUIEDITOR_H
#include "raylib.h"
#include <imgui.h>

namespace GUIEditor
{
	struct EditorWindow
	{
		Rectangle window;
		float borderWidth;
		Vector2 ImageMin;
		Vector2 ImageMax;
	};
	void Init(int width, int height);
	void BeginOffscreenDraw();
	void EndOffscreenDraw();
	void Draw();
	EditorWindow Window();
}
#endif