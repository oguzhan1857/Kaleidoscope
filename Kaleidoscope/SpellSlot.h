#pragma once
#include "macros.h"
#include "SpellInfo.h"
#include "Vector3.h"

class SpellSlot
{
public:
	MAKE_GET(level, int, SpellSlot)
	MAKE_GET(cooldown_expire, float, SpellSlot)
	MAKE_GET(cooldown, float, SpellSlot)
	MAKE_GET(remaining_charge, float, SpellSlot)
	MAKE_GET(spell_info, SpellInfo*, SpellSlot)
	MAKE_GET(target_info, SpellTargetingData*, SpellSlot)

};