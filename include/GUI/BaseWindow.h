#ifndef GUI_BASEWINDOW_H
#define GUI_BASEWINDOW_H
#include "LogicElements.h"
#include "appSettings.h"
#include "common_types.h"
#include "imgui.h"
#include "CircuitController.h"
#include <functional>

namespace GUI
{
    class BaseWindow
    {
      public:
        virtual ~BaseWindow() = default;

        virtual void Draw(std::shared_ptr<CircuitController> circuit) = 0;  // Default parameter-less version
        virtual void Update(std::shared_ptr<CircuitController> circuitController) = 0;

        virtual bool IsVisible() const
        {
            return visible;
        }

        virtual void Show()
        {
            visible = true;
        }

        virtual void Hide()
        {
            visible = false;
        }

        virtual void ToggleVisibility()
        {
            visible = !visible;
        }
        std::string GetTitle() const
        {
            return title;
        }

      protected:
        explicit BaseWindow(const std::string& windowTitle) : title(windowTitle) {}

        std::string title;
        bool visible = false;
    };
}  // namespace GUI

#endif  // GUI_BASEWINDOW_H