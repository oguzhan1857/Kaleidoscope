#pragma once
#include <string>

namespace PyLauncher
{
	void initiliaze();
	void remove();
	std::string traceback();
	PyObject* load_module(const char* file_name);
}