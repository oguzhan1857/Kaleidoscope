#include "pch.h"

void Patchables::initialize()
{
	materialRegistry = M_RVA(Offsets::Gui::materialRegistry);
	riotWindow       = M_RVA(Offsets::Gui::riotWindow);
	
	gameClient       = M_RVA(Offsets::GameClient::instance);

	gameTime         = M_RVA(Offsets::Globals::game_time);
	worldToScreen    = M_RVA(Offsets::Globals::world_to_screen);
	localPlayer      = M_RVA(Offsets::Globals::local_player);
	windUp           = M_RVA(Offsets::Globals::wind_up);
	attackDelay      = M_RVA(Offsets::Globals::attack_delay);
	isAlive          = M_RVA(Offsets::Globals::is_alive);
	isTargetable     = M_RVA(Offsets::Globals::is_targetable);

	renderer         = M_RVA(Offsets::Renderer::instance);
	hudManager       = M_RVA(Offsets::HudManager::instance);
	issueClick       = M_RVA(Offsets::InputLogic::issue_order_click);
	issueSpell       = M_RVA(Offsets::SpellLogic::issue_spell);
	objectManager    = M_RVA(Offsets::ObjectManager::instance);
	heroManager      = M_RVA(Offsets::ObjectManager::hero_manager);

	menuGui          = M_RVA(Offsets::MenuGUI::instance);
	worldToMinimap   = M_RVA(Offsets::TacticalMap::world_to_minimap);
	minionManager    = M_RVA(Offsets::ObjectManager::minion_manager);

	netClient        = M_RVA(Offsets::NetClient::instance);
	getPing          = M_RVA(Offsets::NetClient::get_ping); 

	onRightClickMove = M_RVA(0x5df490);
	championManager  = M_RVA(Offsets::ChampionManager::instance);
}
