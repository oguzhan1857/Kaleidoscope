#include "pch.h"

MenuGUI* MenuGUI::instance()
{
	return *reinterpret_cast<MenuGUI**>(Patchables::menuGui);
}