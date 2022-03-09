#pragma once
#include <string>
#include "SpellData.h"

class SpellTargetingData
{
public:
	void set_caster_handle(int index)
	{
		*reinterpret_cast<int*>(this + 0x8) = index;
	}

	void set_target_handle(int index)
	{
		*reinterpret_cast<int*>(this + 0xC) = index;
	}

	void set_start_pos(Vector3 pos)
	{
		*reinterpret_cast<Vector3*>(this + 0x10) = pos;
	}

	void set_end_pos(Vector3 pos)
	{
		*reinterpret_cast<Vector3*>(this + 0x1C) = pos;
	}

	void set_cast_pos(Vector3 pos)
	{
		*reinterpret_cast<Vector3*>(this + 0x28) = pos;
	}
};

class SpellInfo
{
public:
	std::string get_name();
	MAKE_GET(name_length, int, SpellInfo)
	MAKE_GET(spell_data, SpellData*, SpellInfo)
};