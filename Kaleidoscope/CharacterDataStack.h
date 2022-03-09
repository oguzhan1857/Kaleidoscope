#pragma once
#include "macros.h"
#include <cinttypes>
#include <vector>

class AString
{
public:
	const char* str;
	std::size_t length;
	std::size_t capacity;
};

class CharacterStackData
{
public:
	AString model;
	std::int32_t skin;
	PAD(0x20);
	bool update_spells;
	bool dont_update_hud;
	bool change_particle;
	PAD(0x1);
	PAD(0xC);
};

class CharacterDataStack
{
public:
	std::vector<CharacterStackData> stack;
	CharacterStackData          base_skin;

	void update(bool change);
	void push(const char* model, std::int32_t skin);
};