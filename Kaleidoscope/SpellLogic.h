#pragma once
#include "SpellInfo.h"
#include "SpellSlot.h"
#include "Vector3.h"

enum ISSUE_SPELL_CAST_TYPE
{
	CAST_NORMAL = 1,
	CAST_SMART,
	CAST_SELF,
	CAST_INDICATOR,
	CAST_SMART_SELF,
};

class SpellLogic
{
public:
	int  issue_spell(int slot_index, int type, SpellSlot* spell_slot);
	void send_spell_cast_packet(SpellInfo* spell_info);
	bool cast_charged_spell(SpellInfo* spell_info);
};