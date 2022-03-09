#include "pch.h"

#define PYTHON_LIB_PATH L"C:\\Users\\Admin\\AppData\\Local\\Programs\\Python\\Python310-32\\Lib"

namespace py = boost::python;


void PyLauncher::initiliaze()
{
	Py_SetPath(PYTHON_LIB_PATH);
	init_kaleidoscope();
	Py_Initialize();
}

void PyLauncher::remove()
{
	Py_Finalize();
}

std::string PyLauncher::traceback()
{
	PyObject* type_ptr = NULL, * value_ptr = NULL, * traceback_ptr = NULL;
	PyErr_Fetch(&type_ptr, &value_ptr, &traceback_ptr);
    
    std::string ret("[Error] ");
    
    if (type_ptr != NULL)
    {
        py::handle<> h_type(type_ptr);
        py::str type_pstr(h_type);
        py::extract<std::string> e_type_pstr(type_pstr);
        if (e_type_pstr.check())
            ret += e_type_pstr();
        else
            ret += "Unknown exception type";
    }

    if (value_ptr != NULL) {
        py::handle<> h_val(value_ptr);
        py::str a(h_val);
        py::extract<std::string> returned(a);
        if (returned.check())
            ret += ": " + returned();
        else
            ret += std::string(": Unparseable Python error: ");
    }

    if (traceback_ptr != NULL) {
        py::handle<> h_tb(traceback_ptr);
        py::object tb(py::import("traceback"));
        py::object fmt_tb(tb.attr("format_tb"));
        py::object tb_list(fmt_tb(h_tb));
        py::object tb_str(py::str("\n").join(tb_list));
        py::extract<std::string> returned(tb_str);
        if (returned.check())
            ret += ": " + returned();
        else
            ret += std::string(": Unparseable Python traceback");
    }
    return ret;
}

PyObject* PyLauncher::load_module(const char* file_name)
{
    PyObject* script_instance = nullptr;

    try {
        script_instance = py::import(file_name).ptr();
    }
    catch (py::error_already_set const&) {
        std::string perror_str = traceback();
        Console::instance()->AddLog("%s", perror_str.c_str());
    }

    return script_instance;
}

void PyLauncher::reload_module(PyObject** instance)
{
    try {
        *instance = PyImport_ReloadModule(*instance);
    }
    catch (py::error_already_set const&) {
        std::string perror_str = traceback();
        Console::instance()->AddLog("%s", perror_str.c_str());
    }
}
