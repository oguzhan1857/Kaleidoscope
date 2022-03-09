#include "pch.h"

int SpellLogic::issue_spell(int slot_index, int type, SpellSlot* spell_slot)
{
	return reinterpret_cast<int(__thiscall*)(SpellLogic*, int, int, SpellSlot*)>(Patchables::issueSpell)(this, slot_index, type, spell_slot);
}

void SpellLogic::send_spell_cast_packet(SpellInfo* spell_info)
{
	reinterpret_cast<void(__thiscall*)(SpellLogic*, SpellInfo*)>(Patchables::sendSpellCastPacket)(this, spell_info);
}

bool SpellLogic::cast_charged_spell(SpellInfo* spell_info)
{
	return reinterpret_cast<bool(__thiscall*)(SpellLogic*, SpellInfo*)>(Patchables::castChargedSpell)(this, spell_info);
}