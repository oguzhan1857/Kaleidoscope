#pragma once
#include "framework.h"

namespace WndProcEvent
{
	inline bool g_pressedKeys[256]{ 0 };
	void window_procedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	bool is_key_pressed(WPARAM key);
}