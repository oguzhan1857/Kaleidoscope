#pragma once
#include <map>
#include "GameObject.h"

class MissileManager
{
public:
	static MissileManager* instance();
	std::map<int, GameObject*> get_missile_map();
};