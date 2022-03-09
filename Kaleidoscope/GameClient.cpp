#include "pch.h"

GameClient* GameClient::instance()
{
	return *reinterpret_cast<GameClient**>(Patchables::gameClient);
}

GAME_CLIENT_STATUS GameClient::get_state()
{
	return *reinterpret_cast<GAME_CLIENT_STATUS*>(this + static_cast<__int32>(Offsets::GameClient::state));
}