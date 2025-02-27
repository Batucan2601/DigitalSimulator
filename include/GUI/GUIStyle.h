#ifndef GUI_STYLE_H
#define GUI_STYLE_H
#include "appSettings.h"

#include <imgui.h>
namespace GUIStyle
{
    void init();
    extern ImFont* font;
    void ApplyDarkTheme();
    void ApplyLightTheme();
}  // namespace GUIStyle
#endif