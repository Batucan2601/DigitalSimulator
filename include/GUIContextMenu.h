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
        void Draw(std::shared_ptr<CircuitController> circuit) override;
        void Update(std::shared_ptr<CircuitController> circuitController) override;
        
    };
}

