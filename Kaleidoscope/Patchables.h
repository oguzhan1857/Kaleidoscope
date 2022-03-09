#pragma once
#include "framework.h"

#define g_offset inline DWORD
#define M_RVA(ADDR) ((__int32)GetModuleHandle(NULL) + static_cast<__int32>(ADDR))

namespace Patchables
{
	g_offset materialRegistry;
	g_offset riotWindow;
	g_offset gameClient;

	g_offset spellState;

	g_offset gameTime;
	g_offset worldToScreen;
	g_offset localPlayer;
	g_offset windUp;
	g_offset attackDelay;
	g_offset isAlive;
	g_offset isTargetable;

	g_offset renderer;
	g_offset hudManager;
	g_offset issueClick;
	g_offset issueSpell;
	g_offset objectManager;
	g_offset heroManager;
	g_offset castSpell;
	
	g_offset menuGui;
	g_offset worldToMinimap;

	g_offset minionManager;

	g_offset sendSpellCastPacket;
	g_offset sendSpecialSpell;
	g_offset castChargedSpell;

	g_offset netClient;
	g_offset getPing;

	g_offset onStartSpellCast;

	g_offset onStartSpellCastHook;
	g_offset onStartSpellCastOver;
	g_offset onStartSpellCastJmp;


	g_offset onRightClickMove;

	g_offset championManager;

	void initialize();
}