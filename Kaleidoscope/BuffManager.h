#pragma once
#include <vector>
#include <string>

class Buff
{
public:
	std::string get_name();
};

class BuffEntry
{
public:
	Buff* get_alt_buff();
	bool  get_active();
	float get_start_time();
	float get_end_time();

	int   get_buff_count();
	int   get_buff_count1();
	int   get_buff_count2();
};

class BuffManager
{
public:
	std::vector<BuffEntry*> get_buff_vector();
	bool has_buff(const char* name);
};