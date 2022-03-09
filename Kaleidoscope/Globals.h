#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include "Vector3.h"

namespace Globals
{
	float get_game_time();
	bool  get_world_to_screen(Vector3* pos, Vector2* screen);
	GameObject* get_local_player();

	float get_wind_up(GameObject* instace);
	float get_attack_delay(GameObject* instance);

	bool is_alive(GameObject* instance);
	bool is_targetable(GameObject* obj);
}