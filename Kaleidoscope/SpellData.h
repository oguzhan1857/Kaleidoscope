#pragma once
#include "macros.h"

class SpellData
{
public:
	std::string get_name();
	MAKE_GET(range, float, SpellData)
	MAKE_GET(cast_radius, float, SpellData)
	MAKE_GET(speed, float, SpellData)
	MAKE_GET(width, float, SpellData)
	MAKE_GET(mana_cost, float, SpellData)
};