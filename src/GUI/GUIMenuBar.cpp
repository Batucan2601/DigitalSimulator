#include "GUI/GUIMenuBar.h"
#include <imgui.h>
#include <sstream>

GUIMenuBar guiMenuBar;

static void createMenuItem(std::string name, bool is_menu , std::function<void()> action)
{
	if( name.find("/") == std::string::npos ) // at root
	{
		auto menu = std::make_unique<GUIMenu>(); 
		menu->title = name;
		guiMenuBar.menuList[name] = std::move(menu);
		return; 
	}
	//else
	std::vector<std::string> tokens;
	std::stringstream ss(name);
	std::string token;
	// Split string by '/' delimiter.
	while (std::getline(ss, token, '/')) {
		tokens.push_back(token);
	}
	std::map<std::string, std::unique_ptr<GUIBaseMenu>>* currentMap = &guiMenuBar.menuList;
	// Iterate through tokens.
	// For each token except the last, ensure a GUIMenu exists.
	for (size_t i = 0; i < tokens.size(); ++i) {
		const std::string& name = tokens[i];
		// Last token: create the final item.
		if (i == tokens.size() - 1) {
			// If an item with this name does not already exist, create it.
			if (currentMap->find(name) == currentMap->end()) {
				if (!is_menu) {
					// Create a GUIBarItem.
					auto barItem = std::make_unique<GUIBarItem>(name);
					barItem->action = action;
					(*currentMap)[name] = std::move(barItem);
				}
				else {
					// Create a GUIMenu.
					(*currentMap)[name] = std::make_unique<GUIMenu>(name);
				}
			}
			else {
				// Optionally update the existing item if needed.
				// For this example, we do nothing.
			}
		}
		else {
			// For intermediate tokens, we need to ensure there's a GUIMenu.
			if (currentMap->find(name) == currentMap->end()) {
				// Create a new submenu (GUIMenu) if it doesn't exist.
				(*currentMap)[name] = std::make_unique<GUIMenu>(name);
			}
			// Move the current map pointer to the items of the submenu.
			GUIBaseMenu* base = (*currentMap)[name].get();
			// Make sure that base is actually a menu (it should be).
			currentMap = &(base->items);
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
	createMenuItem("File/Exit", false, []()
		{
			exit(1);
	; });
	
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
