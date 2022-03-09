#pragma once
#include "TacticalMap.h"

class MenuGUI
{
public:
	static MenuGUI* instance();
	MAKE_GET(tactical_map, TacticalMap*, MenuGUI)
};