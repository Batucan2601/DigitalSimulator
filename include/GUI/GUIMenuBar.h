#ifndef GUI_MENUBAR_H
#define GUI_MENUBAR_H
#include <vector>
#include <string>
#include <memory>
#include <functional>

class GUIBaseMenu
{
public:
	virtual ~GUIBaseMenu() = default;
	virtual void display() = 0;
};
class GUIBarItem : public GUIBaseMenu
{
public:
	std::string title;
	std::function<void()> action;
	GUIBarItem(const std::string &title, std::function<void()> action = nullptr)
		: title(title), action(action) {}
	void display() override;
};
class GUIMenu : public GUIBaseMenu
{
public:
	std::string title;
	std::vector<std::unique_ptr<GUIBaseMenu>> items;
	void display() override;
};
class GUIMenuBar
{
public:
	GUIMenuBar();
	std::vector<GUIMenu> menuList;
	void Draw();
};
extern GUIMenuBar guiMenuBar;
#endif // GUIMENUBAR_H