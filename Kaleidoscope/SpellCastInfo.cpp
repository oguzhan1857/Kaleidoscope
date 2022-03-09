#include "pch.h"

SpellInfo* SpellCastInfo::get_spell_info()
{
	return *reinterpret_cast<SpellInfo**>(this + 0x0);
}

int SpellCastInfo::get_slot_index()
{
	return *reinterpret_cast<int*>(this + 0x4);
}

float SpellCastInfo::get_cast_time()
{
	return *reinterpret_cast<int*>(this + 0x8);
}

int SpellCastInfo::get_level()
{
	return *reinterpret_cast<int*>(this + 0x5C);
}

int SpellCastInfo::get_owner_index()
{
	return *reinterpret_cast<int*>(this + 0x64);
}

int SpellCastInfo::get_missile_index()
{
	return *reinterpret_cast<int*>(this + 0x70);
}

Vector3 SpellCastInfo::get_start_pos()
{
	return *reinterpret_cast<Vector3*>(this + 0x7C);
}

Vector3 SpellCastInfo::get_end_pos()
{
	return *reinterpret_cast<Vector3*>(this + 0x88);
}

int SpellCastInfo::get_target_index()
{
	DWORD* target_info = *reinterpret_cast<DWORD**>(this + 0xB8);
	if (!target_info) {
		return 0;
	}
	return *reinterpret_cast<int*>(target_info + 0x0);
}