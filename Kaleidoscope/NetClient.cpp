#include "pch.h"

NetClient* NetClient::instance()
{
	return *reinterpret_cast<NetClient**>(Patchables::netClient);
}

int NetClient::get_ping()
{
	return reinterpret_cast<int(__thiscall*)(NetClient*)>(Patchables::getPing)(this);
}

float NetClient::get_ping_sec()
{
	return this->get_ping() * 0.001f;
}