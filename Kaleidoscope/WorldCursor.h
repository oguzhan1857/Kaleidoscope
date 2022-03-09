#pragma once

class WorldCursor
{
public:
	MAKE_GET(x, float, WorldCursor)
	MAKE_GET(y, float, WorldCursor)
	MAKE_GET(z, float, WorldCursor)

	Vector3 get_pos();
	bool on_right_click_move(int screen_x, int screen_y, bool is_attack_cmd, bool is_move_cmd, bool execute);
	bool on_right_click_attack(GameObject* unit, bool u1, bool u2, bool u3, int u4, int u5);
};