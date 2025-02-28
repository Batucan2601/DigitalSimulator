#ifndef GUIEDITOR_H
#define GUIEDITOR_H
#include "Controls.h"
#include "LogicElements.h"
#include "LogicElementsDraw.h"
#include "appSettings.h"
#include "raylib.h"
#include "raylibHelper.h"

#include <imgui.h>

extern AppSettings::Settings settings;

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
    void Draw(std::shared_ptr<CircuitElements::Circuit> circuit);
    EditorWindow Window();
    void DisplayEditor();

}  // namespace GUIEditor
#endif