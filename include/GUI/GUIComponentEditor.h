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

        void Draw(std::shared_ptr<CircuitController> circuit) override;
        void Update(std::shared_ptr<CircuitController> circuit) override;
    };
}