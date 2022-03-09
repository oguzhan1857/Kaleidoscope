#pragma once

class NavMesh
{
public:
	static NavMesh* instance();
	bool build_navigation_path(NavigationPath* output, Vector3* from, Vector3* to, AiManager* ai);
};