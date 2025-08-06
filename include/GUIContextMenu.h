#pragma once
#include <GUI/BaseWindow.h>

namespace GUI
{
    class ContextMenu : public BaseWindow
    {
    public:
        ContextMenu() : BaseWindow("Context Menu") {
            visible = false;
        }
        void Draw(SP_Circuit circuit) override;
        void Update(std::shared_ptr<CircuitController> circuitController) override;
        
    };
}

