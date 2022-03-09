#include "pch.h"

int InputLogic::issue_click(int state, int is_attack, int is_attack_command, int screen_x, int screen_y, bool unknown)
{
	return reinterpret_cast<bool(__thiscall*)(InputLogic*, int, int, int, int, int, int)>(Patchables::issueClick)(this, state, is_attack, is_attack_command, screen_x, screen_y, unknown);
}