#ifndef GUI_MENUBAR_H
#define GUI_MENUBAR_H
#include <vector>
#include <string>
#include <memory>
#include <functional>

class MenuBase
{
public:
	virtual ~MenuBase() = default;
	virtual void display() = 0;
};
class MenuBarItem : public MenuBase
{
public:
	std::string title;
	std::function<void()> action;
	MenuBarItem(const std::string& title, std::function<void()> action = nullptr)
	: title(title), action(action){}
	void display() override;
};
class Menu : public MenuBase
{
public:
	std::string title;
	std::vector<std::unique_ptr<MenuBase>> items;
	void display() override;
};
class MenuBar
{
public:
	MenuBar();
	std::vector<Menu> menuList; 
	void draw();
};
extern MenuBar menuBar;
#endif // GUIMENUBAR_H