#include "pch.h"

void CharacterDataStack::update(bool change)
{
	static const auto Update = reinterpret_cast<void(__thiscall*)(void*, bool)>(std::uintptr_t(GetModuleHandle(nullptr)) + 0xf4fa0);
	Update(this, change);
}

void CharacterDataStack::push(const char* model, std::int32_t skin)
{
	static const auto Push = reinterpret_cast<int(__thiscall*)(void*, const char* model, std::int32_t skinid, std::int32_t, bool update_spells, bool dont_update_hud, bool, bool, bool change_particle, bool, char, const char*, std::int32_t, const char*, std::int32_t, bool, std::int32_t)>(std::uintptr_t(GetModuleHandle(nullptr)) + 0x100310);
	Push(this, model, skin, 0, false, false, false, false, true, false, -1, "\x00", 0, "\x00", 0, false, 1);
}