#pragma once
#include <string>

namespace PyLauncher
{
	void initiliaze();
	void remove();
	std::string traceback();
	PyObject* load_module(const char* file_name);
	void      reload_module(PyObject** instance);

	inline boost::python::object m_poModule;
	inline boost::python::object m_poDict;
}