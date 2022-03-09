#include "pch.h"

bool TacticalMap::world_to_minimap(Vector3* world, float* minimap_x, float* minimap_y)
{
	return reinterpret_cast<bool(__thiscall*)(TacticalMap*, Vector3*, float*, float*)>
		(Patchables::worldToMinimap)(this, world, minimap_x, minimap_y);
}