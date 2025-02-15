#include "GUI/GUIMenuBar.h"
#include <imgui.h>

GUIMenuBar guiMenuBar;

GUIMenuBar::GUIMenuBar()
{
	GUIMenu fileMenu;
	fileMenu.title = "File";

	auto barItem = std::make_unique<GUIBarItem>("Open", []()
												{
		//std::cout << "Open Clicked!" << std::endl;
		; });

	fileMenu.items.push_back(std::move(barItem)); // FIX: Move unique_ptr

	this->menuList.push_back(std::move(fileMenu));
}
void GUIMenu::display()
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
void GUIBarItem::display()
{
	if (ImGui::MenuItem(this->title.c_str()))
	{
		// call func
	}
}
void GUIMenuBar::Draw()
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
