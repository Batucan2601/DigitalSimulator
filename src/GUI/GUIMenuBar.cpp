#include "GUI/GUIMenuBar.h"
#include "GUI/GUITools.h"
#include <imgui.h>
#include <sstream>

GUIMenuBar guiMenuBar;

static void createMenuItem(std::string path, bool is_menu , std::function<void()> action)
{
    std::vector<std::string> tokens;
    std::stringstream ss(path);
    std::string token;
    while (std::getline(ss, token, '/')) {
        if (!token.empty())
            tokens.push_back(token);
    }

    if (tokens.empty()) return;

    // Start with the top-level menu bar.
    auto* currentItems = &guiMenuBar.menuList;

    for (size_t i = 0; i < tokens.size(); ++i) {
        const std::string& name = tokens[i];
        // Find the item in the current vector.
        auto it = std::find_if(currentItems->begin(), currentItems->end(),
            [&name](const auto& pair) { return pair.first == name; });

        // Last token: create the final item.
        if (i == tokens.size() - 1) {
            if (it == currentItems->end()) {
                if (!is_menu) {
                    auto barItem = std::make_unique<GUIBarItem>(name, action);
                    currentItems->push_back({ name, std::move(barItem) });
                }
                else {
                    currentItems->push_back({ name, std::make_unique<GUIMenu>(name) });
                }
            }
            // Optionally, update an existing item if needed.
        }
        else {
            // For intermediate tokens, ensure there's a GUIMenu.
            if (it == currentItems->end()) {
                // Create a new submenu if it doesn't exist.
                currentItems->push_back({ name, std::make_unique<GUIMenu>(name) });
                // Now find it.
                it = std::find_if(currentItems->begin(), currentItems->end(),
                    [&name](const auto& pair) { return pair.first == name; });
            }
            // Move currentItems pointer to the submenu's items.
            GUIBaseMenu* base = it->second.get();
            currentItems = &(base->items);
        }
    }
}
static void createBarItem(std::string name)
{

}
GUIBarItem::GUIBarItem(const std::string& title, std::function<void()> action)
{
	this->title = title;
	this->action = action;
	this->is_menu = false; 
}
GUIMenuBar::GUIMenuBar()
{
	createMenuItem("File" , true , nullptr);
	createMenuItem("File/Open" , false , []()
		{
	; });
	createMenuItem("File/Save", false, []()
		{
			; });
	createMenuItem("File/Exit", false, []()
		{
			exit(1);
	; });
    createMenuItem("Tools", true, nullptr);
    createMenuItem("Tools/BasicLogic", false, []()
    {
            GUITools_BasicLogicDisplay();
    });

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
void GUIMenuBar::Draw()
{
	if (ImGui::BeginMainMenuBar())
	{
		for (auto& item : this->menuList)
		{
			item.second->display();
		}
		ImGui::EndMainMenuBar();
	}
}
