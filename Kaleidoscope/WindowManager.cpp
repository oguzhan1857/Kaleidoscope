#include "pch.h"

WindowManager::WindowManager()
{
	tick_per_second = 30;
	last_tick       = 00;
	root = new Window(nullptr, "Kaleidoscope 12.5");
}

void WindowManager::update()
{
	//if (GetTickCount64() - last_tick >= 1000 / tick_per_second)
	//{
		last_tick = GetTickCount64();
		root->on_update();
	//}
}

void WindowManager::render()
{
	root->on_render();
}

Component* WindowManager::register_component(PyObject* handler, const char* title)
{
	Component* component = new Component(handler, title);
	Console::instance()->AddLog("[Core] Component Created : handler %p | label : %s | ptr : %p", handler, title, component);
	return component;
}

Component* WindowManager::register_menu(PyObject* handler, const char* title)
{
	Component* menu = new Menu(handler, title);
	Console::instance()->AddLog("[Core] Menu Created : handler %p | label : %s | ptr : %p", handler, title, menu);
	root->add_child(menu);
	Console::instance()->AddLog("[Core] Menu Registered To Root");
	return menu;
}

Component* WindowManager::register_text(PyObject* handler, const char* label)
{
	Component* text = new Text(handler, label);
	Console::instance()->AddLog("[Core] Text Created : handler %p | label : %s | ptr : %p", handler, label, text);
	return text;
}

Component* WindowManager::register_slider_int(PyObject* handler, const char* label)
{
	Component* slider_int = new SliderInt(handler, label);
	Console::instance()->AddLog("[Core] Slider Created : handler %p | label : %s | ptr : %p", handler, label, slider_int);
	return slider_int;
}

Component* WindowManager::register_slider_float(PyObject* handler, const char* label)
{
	Component* slider_float = new SliderFloat(handler, label);
	Console::instance()->AddLog("[Core] SliderFloat Created : handler %p | label : %s | ptr : %p", handler, label, slider_float);
	return slider_float;
}

Component* WindowManager::register_checkbox(PyObject* handler, const char* label)
{
	Component* checkbox = new Checkbox(handler, label);
	Console::instance()->AddLog("[Core] Checkbox Created : handler %p | label : %s | ptr : %p", handler, label, checkbox);
	return checkbox;
}

Component* WindowManager::register_combobox(PyObject* handler, const char* label)
{
	Component* combobox = new ComboBox(handler, label);
	Console::instance()->AddLog("[Core] ComboBox Created : handler %p | label : %s | ptr : %p", handler, label, combobox);
	return combobox;
}

void WindowManager::on_key_down(WPARAM key)
{
	root->on_key_down(key);
}

void WindowManager::on_key_up(WPARAM key)
{
	root->on_key_up(key);
}

void WindowManager::on_double_click()
{
	root->on_double_click();
}

void WindowManager::destroy(Component* component)
{
	if (component->has_parent()) {
		component->get_parent()->remove_child(component);
	}
	component->clear();
}