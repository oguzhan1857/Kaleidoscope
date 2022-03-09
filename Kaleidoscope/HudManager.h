#pragma once
#include "pch.h"
#include "WorldCursor.h"
#include "InputLogic.h"
#include "SpellLogic.h"

class HudManager
{
public:
	static HudManager* instance();
	MAKE_GET(world_cursor, WorldCursor*, HudManager)
	MAKE_GET(input_logic, InputLogic*, HudManager)
	MAKE_GET(spell_logic, SpellLogic*, HudManager)
};