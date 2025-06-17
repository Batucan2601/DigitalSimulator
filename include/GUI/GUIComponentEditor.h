#ifndef GUI_COMPONENT_EDITOR_H
#define GUI_COMPONENT_EDITOR_H
#include "GUI/BaseWindow.h"
#endif 

namespace GUI
{
    class ComponentGateWindow : public BaseWindow
    {
         public:
        ComponentGateWindow() : BaseWindow("ComponentEditor") {}

        void Draw(SP_Circuit circuit) override;
        void Update(SP_Circuit circuit) override;
    };
}