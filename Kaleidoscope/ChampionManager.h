#pragma once
#include "CharacterDataStack.h"

class Champion
{
public:
	class Skin
	{
	public:
		std::int32_t skin_id;
		AString skin_name;
	};
private:
	PAD(0x4);
public:
	AString champion_name;
	PAD(0x48);
	std::vector<Skin> skins;
	PAD(0x8);
};

class ChampionManager
{
public:
	static ChampionManager* instance();
	std::vector<Champion*> get_champions();
};