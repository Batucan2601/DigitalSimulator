#include <GUI/GUIMenuBar.h>
#include <GUI/include.h>
#include <appSettings.h>
#include <imgui.h>
#include <sstream>
#include "../ImGuiFileDialog/ImGuiFileDialog.h"
namespace GUI
{

    void GUIMenuBar::createMenuItem(std::string path, bool is_menu, std::function<void()> action)
    {
        std::vector<std::string> tokens;
        std::stringstream ss(path);
        std::string token;
        while (std::getline(ss, token, '/'))
        {
            if (!token.empty())
                tokens.push_back(token);
        }

        if (tokens.empty())
            return;

        // Start with the top-level menu bar.
        auto* currentItems = &menuList;

        for (size_t i = 0; i < tokens.size(); ++i)
        {
            const std::string& name = tokens[i];
            // Find the item in the current vector.
            auto it = std::find_if(currentItems->begin(), currentItems->end(),
                                   [&name](const auto& pair)
                                   {
                                       return pair.first == name;
                                   });

            // Last token: create the final item.
            if (i == tokens.size() - 1)
            {
                if (it == currentItems->end())
                {
                    if (!is_menu)
                    {
                        auto barItem = std::make_unique<GUIBarItem>(name, action);
                        currentItems->push_back({name, std::move(barItem)});
                    }
                    else
                    {
                        currentItems->push_back({name, std::make_unique<GUIMenu>(name)});
                    }
                }
                // Optionally, update an existing item if needed.
            }
            else
            {
                // For intermediate tokens, ensure there's a GUIMenu.
                if (it == currentItems->end())
                {
                    // Create a new submenu if it doesn't exist.
                    currentItems->push_back({name, std::make_unique<GUIMenu>(name)});
                    // Now find it.
                    it = std::find_if(currentItems->begin(), currentItems->end(),
                                      [&name](const auto& pair)
                                      {
                                          return pair.first == name;
                                      });
                }
                // Move currentItems pointer to the submenu's items.
                GUIBaseMenu* base = it->second.get();
                currentItems = &(base->items);
            }
        }
    }
    GUIBarItem::GUIBarItem(const std::string& title, std::function<void()> action)
    {
        this->title = title;
        this->action = action;
        this->is_menu = false;
    }

    void GUIMenuBar::Init()
    {
        createMenuItem("File", true, nullptr);
        createMenuItem("File/Open", false,
                       []()
                       {
                           ;
                       });
        createMenuItem("File/Save", false,
                       [this]()  // Capture 'this' here
                       {
                            if (auto* saveWindow = dynamic_cast<GUI::SaveLoad*>(windows["Save/Load"])) {
                                saveWindow->state = GUI::SaveLoad::State::STATE_SAVE;
                            }


                       });
        createMenuItem("File/Load", false,
                       [this]()  // Capture 'this' here
                       {
                            if (auto* saveWindow = dynamic_cast<GUI::SaveLoad*>(windows["Save/Load"])) {
                                saveWindow->state = GUI::SaveLoad::State::STATE_LOAD;
                            }
                       });
        createMenuItem("File/Exit", false,
                       []()
                       {
                           exit(1);
                       });
        createMenuItem("Editor", false,
                       [this]()
                       {
                           windows["Editor"]->ToggleVisibility();
                       });

        createMenuItem("Tools", true, nullptr);
        createMenuItem("Tools/Component List", false,
                       [this]()
                       {
                           windows["Tools"]->ToggleVisibility();
                       });
        createMenuItem("Settings/System Settings", false,
                       [this]()
                       {
                           windows["Settings"]->ToggleVisibility();
                       });
        createMenuItem("View/Theme/Dark Mode", false,
                       []()
                       {
                           AppSettings::appSettings.theme = AppSettings::Theme::DarkMode;
                           GUIStyle::ApplyDarkTheme();
                       });
        createMenuItem("View/Theme/Light Mode", false,
                       []()
                       {
                           AppSettings::appSettings.theme = AppSettings::Theme::LightMode;
                           GUIStyle::ApplyLightTheme();
                       });
        createMenuItem("View/Appearance/Default Layout", false, []() {});
    }
    void GUIMenuBar::SetWindowList(std::vector<std::unique_ptr<GUI::BaseWindow>>& localWindows)
    {
        this->windows.clear();
        for (auto& window : localWindows)
        {
            this->windows[window->GetTitle()] = window.get();
        }
    }
    void GUIMenu::display()
    {
        if (ImGui::BeginMenu(this->title.c_str()))
        {
            for (auto& item : this->items)
            {
                item.second->display();
            }
            ImGui::EndMenu();
        }
    }
    void GUIBarItem::display()
    {
        if (ImGui::MenuItem(this->title.c_str()))
        {
            this->action();
        }
    }
    void GUIMenuBar::Draw(SP_Circuit circuit)
    {
        if (ImGui::BeginMainMenuBar())
        {
            for (auto& item : this->menuList)
            {
                item.second->display();
            }
            ImGui::EndMainMenuBar();
        }
        this->circuit = circuit;
    }
    void GUIMenuBar::Update(SP_Circuit circuit)
    {
        (void)circuit;
    }
}  // namespace GUI
