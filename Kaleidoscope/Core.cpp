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
		std::this_thread::sleep_for(1s);
	}

	Data::SkinDatabase::load();

	Console::instance()->AddLog("[Core] Loaded");
	PyLauncher::initiliaze();
	DxHook::initiliaze();
	
	PyLauncher::load_module("orbwalker");
	PyLauncher::load_module("skinchanger");
	PyLauncher::load_module("spelltracker");

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