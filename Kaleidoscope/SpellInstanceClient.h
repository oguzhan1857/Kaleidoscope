#pragma once
#include "SpellInfo.h"
#include "Vector3.h"

class SpellInstanceClient
{
public:
	int        get_target_id();
	SpellInfo* get_spell_info();
	
	MAKE_GET_OFFSET(slot,            int,		0xC)
	MAKE_GET_OFFSET(start_time,      float,		0x13C)
	MAKE_GET_OFFSET(windup_end_time, float,		0x140)
	MAKE_GET_OFFSET(start_pos,       Vector3,	0x84)
	MAKE_GET_OFFSET(end_pos,         Vector3,	0x90)
	MAKE_GET_OFFSET(unk_pos,         Vector3,	0x9C)
};