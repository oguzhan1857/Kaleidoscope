#include "pch.h"

NavMesh* NavMesh::instance()
{
	return *reinterpret_cast<NavMesh**>(M_RVA(0x312e1f4));
}

bool NavMesh::build_navigation_path(NavigationPath* output, Vector3* from, Vector3* to, AiManager* ai)
{
    bool u1, u2, u3;
    return reinterpret_cast<bool(__thiscall*)(NavMesh*, NavigationPath*, Vector3*, Vector3*, AiManager*, bool, bool*, bool*, bool*, int, bool)>(M_RVA(0x9A3380))
        (this, output, from, to, ai, 0, &u1, &u3, &u2, 10000, 0);
}