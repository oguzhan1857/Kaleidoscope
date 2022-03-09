#include "pch.h"

int SpellBook::get_spell_state(int slot)
{
	bool junk;
	return call_virtual<2, int>(this, slot, &junk);
	//bool junk;
	//return reinterpret_cast<int(__thiscall*)(SpellBook*, int, bool*)>(M_RVA(0x4e1780))(this, slot, &junk);
}

SpellSlot* SpellBook::get_spell_slot(int slot)
{
	return *reinterpret_cast<SpellSlot**>(this + (__INT(Offsets::SpellBook::spell_slot) + (0x4 * slot)));
}

SpellInstanceClient* SpellBook::get_active_spell()
{
	return *reinterpret_cast<SpellInstanceClient**>(this + 0x20);
}