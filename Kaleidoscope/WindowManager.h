#pragma once
#include "Singleton.h"
#include <map>
#include <list>
#include "Component.h"

class WindowManager : public Singleton<WindowManager>
{
private:
	Window* root;

	ULONGLONG  tick_per_second;
	ULONGLONG  last_tick;

public:
	WindowManager();
	Component* register_component(PyObject* handler, const char* title);
	Component* register_menu(PyObject* handler, const char* title);
	Component* register_text(PyObject* handler, const char* label);
	Component* register_slider_int(PyObject* handler, const char* label);
	Component* register_slider_float(PyObject* handler, const char* label);
	Component* register_checkbox(PyObject* handler, const char* label);
	Component* register_combobox(PyObject* handler, const char* label);

	void on_key_down(WPARAM key);
	void on_key_up(WPARAM key);
	void on_double_click();

	void destroy(Component* component);
	void update();
	void render();
};