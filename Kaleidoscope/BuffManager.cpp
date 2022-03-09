#include "pch.h"

std::string Buff::get_name()
{
	DWORD* name_ptr = reinterpret_cast<DWORD*>(this + __INT(Offsets::Buff::name));
	char* name = reinterpret_cast<char*>(name_ptr);
	return std::string(name);
}

Buff* BuffEntry::get_alt_buff()
{
	auto b = *reinterpret_cast<Buff**>(this + __INT(Offsets::BuffEntry::alt_buff));
	if ((DWORD)b > 0x1000)
		return b;
	return nullptr;
}

bool BuffEntry::get_active()
{
	return get_end_time() > Globals::get_game_time();
}

float BuffEntry::get_start_time()
{
	return *reinterpret_cast<float*>(this + __INT(Offsets::BuffEntry::start_time));
}

float BuffEntry::get_end_time()
{
	return *reinterpret_cast<float*>(this + __INT(Offsets::BuffEntry::end));
}

int BuffEntry::get_buff_count()
{
	return (get_buff_count2() - get_buff_count1()) >> 3;
}

int BuffEntry::get_buff_count1()
{
	return *reinterpret_cast<int*>(this + __INT(Offsets::BuffEntry::buff_count1));
}

int BuffEntry::get_buff_count2()
{
	return *reinterpret_cast<int*>(this + __INT(Offsets::BuffEntry::buff_count2));
}

std::vector<BuffEntry*> BuffManager::get_buff_vector()
{
	return *reinterpret_cast<std::vector<BuffEntry*>*>(this + __INT(Offsets::BuffManager::buff_vector));
}

bool BuffManager::has_buff(const char* name)
{
	for (auto b : this->get_buff_vector()) {
		if (b->get_alt_buff() != NULL) {
			if (b->get_active()) {
				if (b->get_alt_buff()->get_name() == name) {
					return true;
				}
			}
		}
	}
	return false;
}