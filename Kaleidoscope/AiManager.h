#pragma once
#include <vector>
#include "Vector3.h"

class NavigationPath
{
public:
	int get_next_waypoint()
	{
		return *reinterpret_cast<int*>(this);
	}

	std::vector<Vector3> get_waypoints()
	{
		return *reinterpret_cast<std::vector<Vector3>*>(this + 0x20);
	}
};

class AiManager
{
public:
	MAKE_GET(moving_status,  bool,               AiManager)
	MAKE_GET(dashing_status, bool,               AiManager)
	MAKE_GET(waypoint_index, int,                AiManager)
	MAKE_GET(dash_speed,     float,              AiManager)
	MAKE_GET(velocity,       float,              AiManager)
	MAKE_GET(move_speed,     float,              AiManager)
  //MAKE_GET(server_pos,     Vector3,            AiManager)
	MAKE_GET(waypoint_end,   Vector3,            AiManager)
	MAKE_GET_PTR(nav_path,   NavigationPath*,    AiManager)
};

