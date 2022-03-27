#include "pch.h"

using namespace std::chrono_literals;

void Core::initialize()
{
	Patchables::initialize();
}

void Core::load()
{
	Core::initialize();
	
	while (GameClient::instance()->get_state() != GAME_CLIENT_RUN) {
		std::this_thread::sleep_for(500ms);
	}
	
	Console::instance()->AddLog("[Core] Loaded");
	
	Data::SkinDatabase::load();
	PyLauncher::initiliaze();
	DxHook::initiliaze();
	
	PyLauncher::load_module("orbwalker");
	PyLauncher::load_module("skinchanger");

	while (true) {
		if (GetAsyncKeyState(VK_F8) && 1) {
			break;
		}
		std::this_thread::sleep_for(300ms);
	}

	DxHook::remove();
	PyLauncher::remove();
	ExitThread(0);
}