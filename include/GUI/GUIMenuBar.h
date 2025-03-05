#ifndef GUI_MENUBAR_H
#define GUI_MENUBAR_H
#include "LogicElements.h"

#include <GUI/BaseWindow.h>
#include <GUI/include.h>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace GUI
{
    class GUIBaseMenu
    {
      public:
        virtual ~GUIBaseMenu() = default;
        virtual void display() = 0;
        std::vector<std::pair<std::string, std::unique_ptr<GUIBaseMenu>>> items;
        bool is_menu;
        std::string title;
    };
    class GUIBarItem : public GUIBaseMenu
    {
      public:
        std::function<void()> action;
        GUIBarItem(const std::string& title, std::function<void()> action = nullptr);
        void display() override;
    };
    class GUIMenu : public GUIBaseMenu
    {
      public:
        GUIMenu(const std::string& title = "") : title(title)
        {
            is_menu = true;  // this is a menu
        }
        std::string title;
        void display() override;
    };
    class GUIMenuBar : public BaseWindow
    {
      public:
        GUIMenuBar() : BaseWindow("Toolbar") {};
        std::vector<std::pair<std::string, std::unique_ptr<GUIBaseMenu>>> menuList;
        void Draw(SP_Circuit circuit);
        SP_Circuit circuit;
        std::unordered_map<std::string, GUI::BaseWindow*> windows;
        void SetWindowList(std::vector<std::unique_ptr<GUI::BaseWindow>>& windows);
        void createMenuItem(std::string path, bool is_menu, std::function<void()> action);
        void Init();
    };

}  // namespace GUI

#endif  // GUIMENUBAR_H