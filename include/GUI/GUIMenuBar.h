#ifndef GUI_MENUBAR_H
#define GUI_MENUBAR_H
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <map>

class GUIBaseMenu
{
public:
	virtual ~GUIBaseMenu() = default;
	virtual void display() = 0;
	std::map<std::string, std::unique_ptr<GUIBaseMenu>> items;
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
		is_menu = true; // this is a menu
	}
	std::string title;
	void display() override;
};
class GUIMenuBar
{
public:
	GUIMenuBar();
	std::map< std::string,std::unique_ptr<GUIBaseMenu>> menuList;
	void Draw();
};
extern GUIMenuBar guiMenuBar;
#endif // GUIMENUBAR_H