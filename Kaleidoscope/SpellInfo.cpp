#include "pch.h"

std::string SpellInfo::get_name()
{
	if (this->get_name_length() > 15)
		return std::string(*reinterpret_cast<char**>(this + __INT(Offsets::SpellInfo::name)));
	else
		return std::string(reinterpret_cast<char*>(this   + __INT(Offsets::SpellInfo::name)));
}
