#ifndef GUIEDITOR_H
#define GUIEDITOR_H
#include "Controls.h"
#include "LogicElements.h"
#include "LogicElementsDraw.h"
#include "appSettings.h"
#include "raylib.h"
#include "raylibHelper.h"

#include <GUI/BaseWindow.h>
#include <imgui.h>

extern AppSettings::Settings appSettings;

namespace GUI
{
    class Editor : public BaseWindow
    {

      public:
        struct EditorWindow
        {
            Rectangle window;
            float borderWidth;
            Vector2 ImageMin;
            Vector2 ImageMax;
        };

        struct EditorRender
        {
            RenderTexture renderTexture;
            EditorWindow window;
        };

        Editor() : BaseWindow("Editor") {}

        void Draw(SP_Circuit circuit) override;

        void Init(int width, int height);
        EditorRender m_editor_render;

      private:
        EditorWindow getWindow();
    };

}  // namespace GUI

#endif