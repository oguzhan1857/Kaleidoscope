#pragma once

class NetClient
{
public:
	static NetClient* instance();
	int   get_ping();
	float get_ping_sec();
};