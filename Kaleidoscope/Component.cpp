#include "pch.h"

Component::Component()
{
	this->parent  = nullptr;
	this->handler = nullptr;
	this->label   = "noname";
}

Component::Component(PyObject* handler, std::string label)
{
	this->parent  = nullptr;
	this->handler = handler;
	this->label   = label;
}

void Component::on_update()
{
	remove_reserved_child();
	py_update();
	for (auto& child_comp : child_list)
		child_comp->on_update();
}

void Component::on_render()
{
	remove_reserved_child();
	py_render();
	for (auto& component : child_list)
		component->on_update();
}

void Component::remove_reserved_child()
{
	if (reserve_list.empty())
		return;
	
	for (auto it = reserve_list.begin(); it != reserve_list.end(); ++it)
	{
		reserve_list.remove(*it);
	}

	reserve_list.clear();
}

void Component::remove_child(Component* component)
{
	reserve_list.push_back(component);
}

void Component::add_child(Component* component)
{
	component->parent = this;
	child_list.push_back(component);
	Console::instance()->AddLog("[Core] Parent Component: (%s) | Child Component: (%s)", this->label.c_str(), component->label.c_str());
}

void Component::clear()
{
	std::for_each(child_list.begin(), child_list.end(), [](Component* child) {
		child->clear();
		});
	child_list.clear();
	handler  = nullptr;
}

void Component::py_update()
{
	if (!handler)
		return;

	try {
		boost::python::call<void>(PyObject_GetAttrString(handler, "OnUpdate"));
	}
	catch (boost::python::error_already_set const&) {
		std::string perror_str = PyLauncher::traceback();
		Console::instance()->AddLog("%s", perror_str.c_str());
	}
}

void Component::py_render()
{
	if (!handler)
		return;

	try {
		boost::python::call<void>(PyObject_GetAttrString(handler, "OnRender"));
	}
	catch (boost::python::error_already_set const&) {
		std::string perror_str = PyLauncher::traceback();
		Console::instance()->AddLog("%s", perror_str.c_str());
	}
}

void Component::on_key_up(WPARAM key)
{

}

void Component::on_key_down(WPARAM key)
{

}

void Component::py_on_double_click()
{
	if (!handler)
		return;

	try {
		boost::python::call<void>(PyObject_GetAttrString(handler, "OnDoubleClick"));
	}
	catch (boost::python::error_already_set const&) {
		std::string perror_str = PyLauncher::traceback();
		Console::instance()->AddLog("%s", perror_str.c_str());
	}
}

void Component::on_double_click()
{
	py_on_double_click();
	for (auto& component : child_list)
		component->on_double_click();
}

Window::Window(PyObject* handler, std::string label)
{
	this->label        = label;
	this->handler      = handler;
	this->window_title = label;
}

void Window::on_update()
{
	py_update();
	for (auto& component : child_list)
		component->on_update();
}

void Window::on_render()
{
	py_render();
	ImGui::PushFont(DxHook::get_title_font());
	ImGui::Begin(window_title.c_str());
	ImGui::Separator();
	ImGui::PushFont(DxHook::get_main_font());
	
	for (auto& component : child_list)
		component->on_render();
	
	ImGui::PopFont();
	ImGui::End();
	ImGui::PopFont();
}



Menu::Menu(PyObject* handler, std::string label)
{
	this->handler    = handler;
	this->label      = label;
	this->menu_title = label;
}

void Menu::on_update()
{
	py_update();
}

void Menu::on_render()
{	
	py_render();
	if (ImGui::CollapsingHeader(menu_title.c_str()))
	{
		for (auto& component : child_list)
			component->on_render();
	}
}

void Menu::set_title(std::string title)
{
	this->menu_title = title;
}



Text::Text()
{
	this->handler = nullptr;
	this->label   = "noname_text";
	this->text    = "";
}

Text::Text(PyObject* handler, std::string label)
{
	this->handler = handler;
	this->label   = label;
	this->text    = label;
}

void Text::on_render()
{
	ImGui::Text(text.c_str());
}

std::string Text::get_text()
{
	return text;
}

void Text::set_text(std::string text)
{
	this->text = text;
}



SliderInt::SliderInt()
{
	this->handler = nullptr;
	this->label   = "noname_slider_int";
}

SliderInt::SliderInt(PyObject* handler, std::string label)
{
	this->handler = handler;
	this->label   = label;
}

void SliderInt::on_render()
{
	ImGui::SliderInt(label.c_str(), &value, min_range, max_range);
}

void SliderInt::set_value(int value)
{
	this->value = value;
}

int SliderInt::get_value()
{
	return this->value;
}

void SliderInt::set_range(int min, int max)
{
	this->min_range = min;
	this->max_range = max;
}



SliderFloat::SliderFloat()
{
	this->handler = nullptr;
	this->label   = "noname_slider_float";
}

SliderFloat::SliderFloat(PyObject* handler, std::string label)
{
	this->handler = handler;
	this->label   = label;
}

void SliderFloat::on_render()
{
	ImGui::SliderFloat(label.c_str(), &value, min_range, max_range);
}

void SliderFloat::set_value(float value)
{
	this->value = value;
}

float SliderFloat::get_value()
{
	return this->value;
}

void SliderFloat::set_range(float min, float max)
{
	this->min_range = min;
	this->max_range = max;
}



Checkbox::Checkbox()
{
	this->handler = nullptr;
	this->label   = "noname_checkbox";
	this->info    = "no_info";
}

Checkbox::Checkbox(PyObject* handler, std::string label)
{
	this->handler = handler;
	this->label   = label;
	this->info    = label;
}

void Checkbox::set_value(bool value)
{
	this->value = value;
}

bool Checkbox::get_value()
{
	return this->value;
}

void Checkbox::on_render()
{
	if (ImGui::Checkbox(label.c_str(), &value)) {
		py_on_value_change();
	}
}

void Checkbox::py_on_value_change()
{
	try {
		boost::python::object object(boost::python::handle<>(boost::python::borrowed(handler)));
		object.attr("OnValueChange")(value);	
	}
	catch (boost::python::error_already_set const&) {
		std::string error_str = PyLauncher::traceback();
		Console::instance()->AddLog("%s", error_str.c_str());
	}
}


ComboBox::ComboBox()
{
	this->handler = nullptr;
	this->label   = "noname_combobox";
}

ComboBox::ComboBox(PyObject* handler, std::string label)
{
	this->handler = handler;
	this->label   = label;
}

void ComboBox::set_selected_index(int index)
{
	this->selected_index = index;
	this->current_item   = data[index].c_str();
}

int ComboBox::get_selected_index()
{
	return this->selected_index;
}

void ComboBox::py_on_value_change()
{
	try {
		boost::python::object object(boost::python::handle<>(boost::python::borrowed(handler)));
		object.attr("OnValueChange")(selected_index);
	}
	catch (boost::python::error_already_set const&) {
		std::string error_str = PyLauncher::traceback();
		Console::instance()->AddLog("%s", error_str.c_str());
	}
}

void ComboBox::on_render()
{
	if (ImGui::BeginCombo(label.c_str(), current_item.c_str()))
	{
		for (size_t idx = 0; idx < data.size(); idx++)
		{
			const bool is_selected = (current_item == data[idx]);
			if (ImGui::Selectable(data[idx].c_str(), is_selected)) {
				current_item   = data[idx];
				selected_index = idx;
				py_on_value_change();
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
}

void ComboBox::set_data(boost::python::list list)
{
	for (int i = 0; i < boost::python::len(list); i++)
	{
		data.push_back(boost::python::extract<std::string>(list[i]));
	}
}