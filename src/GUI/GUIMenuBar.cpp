#include "GUI/GUIMenuBar.h"
#include <imgui.h>

MenuBar menuBar;


MenuBar::MenuBar()
{
	Menu fileMenu;
	fileMenu.title = "File";

	auto barItem = std::make_unique<MenuBarItem>();
	barItem->title = "Open";

	fileMenu.items.push_back(std::move(barItem)); // FIX: Move unique_ptr

	this->menuList.push_back(std::move(fileMenu));
}
void Menu::display()
{
	if (ImGui::BeginMenu(this->title.c_str()))
	{
		for (size_t i = 0; i < this->items.size(); i++)
		{
			this->items[i]->display();
		}
		ImGui::EndMenu();
	}
	
}
void MenuBarItem::display()
{
	if (ImGui::MenuItem(this->title.c_str()))
	{
		//call func
	}
}
void MenuBar::draw()
{
	if (ImGui::BeginMainMenuBar())
	{
		for (size_t i = 0; i < this->menuList.size(); i++)
		{
			this->menuList[i].display();
		}
		ImGui::EndMainMenuBar();
	}
	
}
