#pragma once
#include "SpellInfo.h"
#include "Vector3.h"

class SpellCastInfo
{
public:
	SpellInfo* get_spell_info();
	float      get_cast_time();
	int        get_slot_index();
	int        get_level();
	int        get_owner_index();
	int		   get_missile_index();
	Vector3    get_start_pos();
	Vector3    get_end_pos();
	int        get_target_index();
};