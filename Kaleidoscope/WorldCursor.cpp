#include "pch.h"

Vector3 WorldCursor::get_pos()
{
	return *reinterpret_cast<Vector3*>(this + 0x10);
}

bool WorldCursor::on_right_click_move(int screen_x, int screen_y, bool is_attack_cmd, bool is_move_cmd, bool execute)
{
	return reinterpret_cast<bool(__thiscall*)(WorldCursor*, int, int, bool, bool, bool)>(Patchables::onRightClickMove)(this, screen_x, screen_y, is_attack_cmd, is_move_cmd, execute);
}

bool WorldCursor::on_right_click_attack(GameObject* unit, bool u1, bool u2, bool u3, int u4, int u5)
{
	return reinterpret_cast<bool(__thiscall*)(WorldCursor*, GameObject*, bool, bool, bool, int, int)>(M_RVA(0x5ECAF0))(this, unit, u1, u2, u3, u4, u5);
}