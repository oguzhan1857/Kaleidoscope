#include "pch.h"

float Globals::get_game_time()
{
	return *reinterpret_cast<float*>(Patchables::gameTime);
}

bool Globals::get_world_to_screen(Vector3* pos, Vector2* screen)
{
	return reinterpret_cast<bool(__cdecl*)(Vector3*, Vector2*)>(Patchables::worldToScreen)(pos, screen);
}

GameObject* Globals::get_local_player()
{
	return *reinterpret_cast<GameObject**>(Patchables::localPlayer);
}

float Globals::get_wind_up(GameObject* instance)
{
	return reinterpret_cast<float(__cdecl*)(GameObject*)>(Patchables::windUp)(instance);
}

float Globals::get_attack_delay(GameObject* instance)
{
	return reinterpret_cast<float(__cdecl*)(GameObject*)>(Patchables::attackDelay)(instance);
}

bool Globals::is_alive(GameObject* instance)
{
	return reinterpret_cast<bool(__thiscall*)(GameObject*)>(Patchables::isAlive)(instance);
}

bool Globals::is_targetable(GameObject* instance)
{
	return reinterpret_cast<bool(__thiscall*)(GameObject*)>(Patchables::isTargetable)(instance);
}
