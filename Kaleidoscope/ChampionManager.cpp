#include "pch.h"
#include "ChampionManager.h"

ChampionManager* ChampionManager::instance()
{
    return *reinterpret_cast<ChampionManager**>(Patchables::championManager);
}

std::vector<Champion*> ChampionManager::get_champions()
{
	return *reinterpret_cast<std::vector<Champion*>*>(this + __INT(Offsets::ChampionManager::champ_vector));
}
