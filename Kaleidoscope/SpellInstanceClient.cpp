#include "pch.h"

int SpellInstanceClient::get_target_id()
{
	uint32_t* targetInfo = reinterpret_cast<uint32_t*>(*reinterpret_cast<uint32_t**>(this + 0xBC) + 0x10);
	return *reinterpret_cast<int*>(targetInfo - 0x10);
}

SpellInfo* SpellInstanceClient::get_spell_info()
{
	return *reinterpret_cast<SpellInfo**>(this + 0x8);
}