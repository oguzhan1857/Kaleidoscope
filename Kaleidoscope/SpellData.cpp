#include "pch.h"

std::string SpellData::get_name()
{
	char* name_ptr = *reinterpret_cast<char**>(this + __INT(Offsets::SpellData::name));
	return std::string(name_ptr);
}
