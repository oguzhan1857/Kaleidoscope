#include "pch.h"

MissileManager* MissileManager::instance()
{
	return *reinterpret_cast<MissileManager**>(M_RVA(0x30F9958));
}

std::map<int, GameObject*> MissileManager::get_missile_map()
{
	return *reinterpret_cast<std::map<int, GameObject*>*>(this + 0x4);
}