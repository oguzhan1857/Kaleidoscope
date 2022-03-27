#include "pch.h"

void CharacterDataStack::update(bool change)
{
	return reinterpret_cast<void(__thiscall*)(CharacterDataStack*, bool)>(M_RVA(0xf4fa0))(this, change);
}

int CharacterDataStack::push(const char* model, std::int32_t skin)
{
	return reinterpret_cast<int(__thiscall*)(CharacterDataStack*, const char* model, std::int32_t skinid, std::int32_t, bool update_spells, bool dont_update_hud, bool, bool, bool change_particle, bool, char, const char*, std::int32_t, const char*, std::int32_t, bool, std::int32_t)>(M_RVA(0x100310))(this, model, skin, 0, false, false, false, false, true, false, -1, "\x00", 0, "\x00", 0, false, 1);
}