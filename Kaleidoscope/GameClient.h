#pragma once

enum GAME_CLIENT_STATUS
{
	GAME_CLIENT_LOAD,
	GAME_CLIENT_CONNECT,
	GAME_CLIENT_RUN,
	GAME_CLIENT_PAUSE,
	GAME_CLIENT_FINISH,
	GAME_CLIENT_EXIT
};

class GameClient
{
public:
	static GameClient* instance();
	GAME_CLIENT_STATUS get_state();
};