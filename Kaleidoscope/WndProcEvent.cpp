#include "pch.h"

void WndProcEvent::window_procedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_KEYDOWN:
			g_pressedKeys[wparam] = true;
			//WindowManager::instance()->on_key_down(wparam);
			break;
		case WM_KEYUP:
			g_pressedKeys[wparam] = false;
			//WindowManager::instance()->on_key_up(wparam);
			break;
		case WM_LBUTTONDBLCLK:
			WindowManager::instance()->on_double_click();
			break;
	}
}

bool WndProcEvent::is_key_pressed(WPARAM key)
{
	return g_pressedKeys[key];
}