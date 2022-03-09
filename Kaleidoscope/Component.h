#pragma once
#include <string>
#include <list>

class Component
{
protected:
	Component* parent = nullptr;
	PyObject* handler = nullptr;
	std::string label;

public:
	std::list<Component*> child_list;
	std::list<Component*> reserve_list;

public:
	Component();
	Component(PyObject* handler, std::string label);
	
	virtual void on_update();
	virtual void on_render();

	virtual void py_update();
	virtual void py_render();

	virtual void remove_reserved_child();
	virtual void remove_child(Component* component);
	virtual void add_child(Component* component);
	virtual void clear();

	virtual void on_key_up(WPARAM up);
	virtual void on_key_down(WPARAM key);
	virtual void on_double_click();
	
	Component* get_parent() { return parent; }
	bool       has_parent() { return parent ? true : false; }
};

class Window : public Component
{
protected:
	std::string window_title;

public:
	Window(PyObject* handler, std::string label);
	void on_update();
	void on_render();
};

class Menu : public Component
{
protected:
	std::string menu_title;

public:
	Menu() = default;
	Menu(PyObject* handler, std::string label);
	void on_update();
	void on_render();
	void set_title(std::string title);
};


class Text : public Component
{
protected:
	std::string text;
public:
	Text();
	Text(PyObject* handler, std::string label);
	void on_render();
	std::string get_text();
	void set_text(std::string text);
};



class SliderInt : public Component
{
protected:
	int value     = 0;
	int min_range = 0;
	int max_range = 100;

public:
	SliderInt();
	SliderInt(PyObject* handler, std::string label);

	int  get_value();
	void set_value(int value);
	void set_range(int min, int max);
	
	void on_render();
};

class SliderFloat : public Component
{
protected:
	float value = 0;
	float min_range;
	float max_range;

public:
	SliderFloat();
	SliderFloat(PyObject* handler, std::string label);

	float get_value();
	void  set_value(float value);
	void  set_range(float min, float max);
	void  on_render();
};



class Checkbox : public Component
{
protected:
	bool value;
	std::string info;

public:
	Checkbox();
	Checkbox(PyObject* handler, std::string label);
	
	bool get_value();
	void set_value(bool value);
	void on_render();
	void py_on_value_change();
};


class ComboBox : public Component
{
protected:
	std::vector<std::string> data;
	std::string current_item = "";
	int selected_index       = 0;

public:
	ComboBox();
	ComboBox(PyObject* handler, std::string label);

	void set_data(boost::python::list list);
	void on_render();
	void set_selected_index(int index);
	int  get_selected_index();
	void py_on_value_change();
};