#include "pch.h"

using namespace boost::python;

void CPyConsole_AddLog(const char* text)
{
	Console::instance()->AddLog(text);
}

Component* CPyWindowManager_RegisterComponent(PyObject* handler, const char* title)
{
	return WindowManager::instance()->register_component(handler, title);
}

Component* CPyWindowManager_RegisterMenu(PyObject* handler, const char* title)
{
	return WindowManager::instance()->register_menu(handler, title);
}

Component* CPyWindowManager_RegisterText(PyObject* handler, const char* title)
{
	return WindowManager::instance()->register_text(handler, title);
}

Component* CPyWindowManager_RegisterSliderInt(PyObject* handler, const char* title)
{
	return WindowManager::instance()->register_slider_int(handler, title);
}

Component* CPyWindowManager_RegisterSliderFloat(PyObject* handler, const char* title)
{
	return WindowManager::instance()->register_slider_float(handler, title);
}

Component* CPyWindowManager_RegisterCheckbox(PyObject* handler, const char* title)
{
	return WindowManager::instance()->register_checkbox(handler, title);
}

Component* CPyWindowManager_RegisterComboBox(PyObject* handler, const char* title)
{
	return WindowManager::instance()->register_combobox(handler, title);
}

void CPyDrawManager_DrawCircle3D(Vector3 world_pos, float radius, Vector4 color, float thickness)
{
	float step  = 6.2831f / 100;
	float theta = 0.f;
	ImVec2 points[200];

	for (int i = 0; i < 200; i++, theta += step) {
		auto world_space = Vector3(world_pos.x + radius * cos(theta), world_pos.y, world_pos.z - radius * sin(theta));

		Vector2 screen_space = Renderer::instance()->world_to_screen(world_space);
		points[i].x = screen_space.x;
		points[i].y = screen_space.y;
	}

	ImGui::GetBackgroundDrawList()->AddPolyline(points, 200, ImColor(color.x, color.y, color.z, color.w), true, thickness);
}

void CPyDrawManager_DrawCircle2D(Vector2 world_pos, float radius, Vector4 color, float thickness)
{
	ImGui::GetBackgroundDrawList()->AddCircle(world_pos.to_imvec(), radius, ImColor(color.x, color.y, color.z, color.w), 0, thickness);
}

void CPyDrawManager_DrawBar2D(Vector2 _pos, Vector2 _size, float percent, Vector4 color, std::string text)
{
	auto pos  = _pos.to_imvec(); 
	auto size = _size.to_imvec();
	ImGui::GetBackgroundDrawList()->AddRect(pos, ImVec2(size.x + pos.x, size.y + pos.y), ImColor(0, 0, 0), 0, 0, 8);
	ImGui::GetBackgroundDrawList()->AddRectFilled(pos, ImVec2(size.x + pos.x, size.y + pos.y), ImColor(57, 62, 70));
	ImGui::GetBackgroundDrawList()->AddRectFilled(pos, ImVec2(size.x + pos.x - (size.x / 100 * percent), size.y + pos.y), ImColor(color.x, color.y, color.z, color.w));
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x, pos.y + 11.0f), ImColor(255, 255, 255), text.c_str());
}

boost::python::list CPyObjectManager_GetHeroes()
{
	boost::python::list plist;
	auto hero_manager = ObjectManager::get_hero_manager();
	for (std::size_t i = 0; i < hero_manager->length; i++) {
		auto hero = hero_manager->list[i];
		if (hero != nullptr) {
			plist.append(boost::ref(hero));
		}
	}
	return plist;
}

boost::python::list CPyObjectManager_GetAllyHeroes()
{
	boost::python::list plist;
	auto hero_manager = ObjectManager::get_hero_manager();
	auto player       = Globals::get_local_player();

	for (std::size_t i = 0; i < hero_manager->length; i++) {
		auto hero = hero_manager->list[i];
		if (hero != nullptr && hero != player) {
			if (hero->get_team_id() == player->get_team_id()) {
				plist.append(boost::ref(hero));
			}
		}
	}
	return plist;
}

boost::python::list CPyObjectManager_GetEnemyHeroes()
{
	boost::python::list plist;
	auto hero_manager = ObjectManager::get_hero_manager();
	auto player       = Globals::get_local_player();

	for (std::size_t i = 0; i < hero_manager->length; i++) {
		auto hero = hero_manager->list[i];
		if (hero != nullptr) {
			if (hero->get_team_id() != player->get_team_id()) {
				plist.append(boost::ref(hero));
			}
		}
	}
	return plist;
}

boost::python::list CPyObjectManager_GetMinions()
{
	boost::python::list plist;
	auto minion_manager = ObjectManager::get_minion_manager();
	for (std::size_t i = 0; i < minion_manager->length; i++) {
		auto minion = minion_manager->list[i];
		if (minion != nullptr) {
			plist.append(boost::ref(minion));
		}
	}
	return plist;
}

boost::python::list CPyData_GetSkinList(uint32_t hash)
{
	boost::python::list py_skin_list;
	auto& skins = Data::SkinDatabase::champions_skins[hash];
	for (size_t i = 0; i < skins.size(); i++) {
		py_skin_list.append(skins[i].skin_name.c_str());
	}
	return py_skin_list;
}

BOOST_PYTHON_MODULE(database)
{
	class_<Data::SkinDatabase::skin_info>("SkinInfo")
		.def_readonly("ModelName", &Data::SkinDatabase::skin_info::model_name)
		.def_readonly("SkinName",  &Data::SkinDatabase::skin_info::skin_name)
		.def_readonly("SkinId",    &Data::SkinDatabase::skin_info::skin_id);

	def("GetSkinList", &CPyData_GetSkinList);
}

BOOST_PYTHON_MODULE(windowmanager)
{
	class_<Component>("Component")
		.def("AddChild", &Component::add_child);

	class_<Text, bases<Component>>("Text")
		.def("SetText", &Text::set_text)
		.def("GetText", &Text::get_text);

	class_<Menu, bases<Component>>("Menu")
		.def("SetTitle", &Menu::set_title);

	class_<SliderInt, bases<Component>>("SliderInt")
		.def("GetValue", &SliderInt::get_value)
		.def("SetValue", &SliderInt::set_value)
		.def("SetRange", &SliderInt::set_range);

	class_<SliderFloat, bases<Component>>("SliderFloat")
		.def("GetValue", &SliderFloat::get_value)
		.def("SetValue", &SliderFloat::set_value)
		.def("SetRange", &SliderFloat::set_range);

	class_<Checkbox, bases<Component>>("Checkbox")
		.def("GetValue", &Checkbox::get_value)
		.def("SetValue", &Checkbox::set_value);

	class_<ComboBox, bases<Component>>("ComboBox")
		.def("GetIndex", &ComboBox::get_selected_index)
		.def("SetIndex", &ComboBox::set_selected_index)
		.def("SetData",  &ComboBox::set_data);

	def("Register",            &CPyWindowManager_RegisterComponent,    return_value_policy<reference_existing_object>());
	def("RegisterMenu",        &CPyWindowManager_RegisterMenu,         return_value_policy<reference_existing_object>());
	def("RegisterText",        &CPyWindowManager_RegisterText,         return_value_policy<reference_existing_object>());
	def("RegisterSliderInt",   &CPyWindowManager_RegisterSliderInt,    return_value_policy<reference_existing_object>());
	def("RegisterSliderFloat", &CPyWindowManager_RegisterSliderFloat,  return_value_policy<reference_existing_object>());
	def("RegisterCheckbox",    &CPyWindowManager_RegisterCheckbox,     return_value_policy<reference_existing_object>());
	def("RegisterComboBox",    &CPyWindowManager_RegisterComboBox,     return_value_policy<reference_existing_object>());
}

BOOST_PYTHON_MODULE(kaleidoscope)
{
	using return_exist_obj = return_value_policy<reference_existing_object>;

	class_<Vector2>("Vector2", init<float, float>())
		.def_readwrite("x", &Vector2::x)
		.def_readwrite("y", &Vector2::y);

	class_<Vector3>("Vector3", init<float, float, float>())
		.def_readwrite("x", &Vector3::x)
		.def_readwrite("y", &Vector3::y)
		.def_readwrite("z", &Vector3::z)
		.def("ToScreen",    &Vector3::to_screen)
		.def("ToMinimap",   &Vector3::to_minimap)
		.def("InRange",     &Vector3::in_range)
		.def("DistanceTo",  &Vector3::distance_to)
		.def("__str__",     &Vector3::get_string);

	class_<Vector4>("Vector4", init<float, float, float, float>())
		.def_readwrite("x", &Vector4::x)
		.def_readwrite("y", &Vector4::y)
		.def_readwrite("z", &Vector4::z)
		.def_readwrite("w", &Vector4::w);

	class_<SpellData>("SpellData")
		.def("GetName",     &SpellData::get_name)
		.def("GetRange",    &SpellData::get_speed)
		.def("GetWidth",    &SpellData::get_width)
		.def("GetManaCost", &SpellData::get_mana_cost);

	class_<SpellInfo>("SpellInfo")
		.def("GetName",      &SpellInfo::get_name)
		.def("GetSpellData", &SpellInfo::get_spell_data, return_exist_obj());

	class_<SpellSlot>("SpellSlot")
		.def("GetLevel",           &SpellSlot::get_level)
		.def("GetCooldownExpire",  &SpellSlot::get_cooldown_expire)
		.def("GetCooldown",        &SpellSlot::get_cooldown)
		.def("GetRemainingCharge", &SpellSlot::get_remaining_charge)
		.def("GetSpellInfo",       &SpellSlot::get_spell_info,  return_exist_obj())
		.def("GetSpellTarget",     &SpellSlot::get_target_info, return_exist_obj());

	class_<SpellBook>("SpellBook")
		.def("GetSpellSlot",  &SpellBook::get_spell_slot, return_exist_obj())
		.def("GetSpellState", &SpellBook::get_spell_state);

	class_<Buff>("Buff")
		.def("GetName", &Buff::get_name);
	
	class_<BuffEntry>("BuffEntry")
		.def("GetBuff",      &BuffEntry::get_alt_buff, return_exist_obj())
		.def("IsActive",     &BuffEntry::get_active)
		.def("GetStartTime", &BuffEntry::get_start_time)
		.def("GetEndTime",   &BuffEntry::get_end_time)
		.def("GetCount",     &BuffEntry::get_buff_count);

	class_<std::vector<BuffEntry*>>("BuffList")
		.def(vector_indexing_suite<std::vector<BuffEntry*>>());

	class_<BuffManager>("BuffManager")
		.def("GetBuffList", &BuffManager::get_buff_vector)
		.def("HasBuff",     &BuffManager::has_buff);

	class_<Renderer>("Renderer")
		.def("GetInstance",           &Renderer::instance, return_exist_obj())
		.def_readonly("screenWidth",  &Renderer::get_window_width)
		.def_readonly("screenHeight", &Renderer::get_window_height)
		.def("WorldToScreen",         &Renderer::world_to_screen);

	class_<NetClient>("NetClient")
		.def("GetInstance", &NetClient::instance, return_exist_obj())
		.def("GetPing",     &NetClient::get_ping);

	class_<GameClient>("GameClient")
		.def("GetInstance", &GameClient::instance, return_exist_obj())
		.def("GetState",    &GameClient::get_state);

	class_<TacticalMap>("TacticalMap")
		.def("WorldToMinimap", &TacticalMap::world_to_minimap);

	class_<MenuGUI>("MenuGUI")
		.def("GetInstance",    &MenuGUI::instance,	return_exist_obj())
		.def("GetTacticalMap", &MenuGUI::get_tactical_map, return_exist_obj());

	class_<WorldCursor>("WorldCursor")
		.def("GetPos",             &WorldCursor::get_pos)
		.def("OnRightClickMove",   &WorldCursor::on_right_click_move)
		.def("OnRightClickAttack", &WorldCursor::on_right_click_attack);

	class_<InputLogic>("InputLogic", init<>())
		.def("IssueClick", &InputLogic::issue_click);

	class_<SpellLogic>("SpellLogic")
		.def("SendSpellCastPacket", &SpellLogic::send_spell_cast_packet);

	class_<HudManager>("HudManager")
		.def("GetInstance",	   &HudManager::instance,         return_exist_obj())
		.def("GetWorldCursor", &HudManager::get_world_cursor, return_exist_obj())
		.def("GetInputLogic",  &HudManager::get_input_logic,  return_exist_obj())
		.def("GetSpellLogic",  &HudManager::get_spell_logic,  return_exist_obj());

	class_<NavigationPath>("NavigationPath")
		.def("GetNextWaypoint", &NavigationPath::get_next_waypoint)
		.def("GetWaypoints",    &NavigationPath::get_waypoints);

	class_<AiManager>("AiManager")
		.def("IsMoving",          &AiManager::get_moving_status)
		.def("IsDashing",         &AiManager::get_dashing_status)
		.def("GetDashSpeed",      &AiManager::get_dash_speed)
		.def("GetVelocity",       &AiManager::get_velocity)
		.def("GetDestinationPos", &AiManager::get_waypoint_end)
		.def("GetNavigationPath", &AiManager::get_nav_path, return_exist_obj());

	class_<NetClient>("NetClient")
		.def("GetInstance", &NetClient::instance, return_exist_obj())
		.def("GetPing",     &NetClient::get_ping)
		.def("GetPingSec",  &NetClient::get_ping_sec);

	class_<GameObject, GameObject*>("GameObject")
		.def("GetIndex",				&GameObject::get_index)
		.def("GetName",					&GameObject::get_name)
		.def("GetBound",				&GameObject::get_bounding_radius)
		.def("IsAlive",					&GameObject::is_alive)
		.def("IsTargetable",			&GameObject::is_targetable)
		.def("GetWindup",				&GameObject::get_windup)
		.def("GetAttackDelay",			&GameObject::get_attack_delay)
		.def("GetIndex",				&GameObject::get_index)
		.def("GetNetworkId",			&GameObject::get_network_id)
		.def("IsVisible",				&GameObject::get_visible)
		.def("GetPos",					&GameObject::get_position)
		.def("GetHealth",				&GameObject::get_health)
		.def("GetMaxHealth",			&GameObject::get_max_health)
		.def("GetMana",					&GameObject::get_mana)
		.def("GetMaxMana",				&GameObject::get_max_mana)
		.def("GetArmor",				&GameObject::get_armor)
		.def("GetBonusArmor",			&GameObject::get_bonus_armor)
		.def("GetMagicResist",			&GameObject::get_magic_resist)
		.def("GetBonusMagicResist",		&GameObject::get_bonus_magic_resist)
		.def("GetCritChange",			&GameObject::get_crit_change)
		.def("GetCritMultiplex",		&GameObject::get_crit_multiplex)
		.def("GetAbilityHaste",			&GameObject::get_ability_haste)
		.def("GetMagicPen",				&GameObject::get_magic_pen)
		.def("GetMagicPenPercent",		&GameObject::get_magic_pen_percent)
		.def("GetLifeSteal",			&GameObject::get_life_steal)
		.def("GetAttackSpeed",			&GameObject::get_attack_speed)
		.def("GetAttackRange",			&GameObject::get_attack_range)
		.def("GetBaseAttackDamage",		&GameObject::get_base_attack_damage)
		.def("GetBonusAttackDamage",	&GameObject::get_bonus_attack_damage)
		.def("GetArmorPenPercent",		&GameObject::get_armor_pen_percent)
		.def("GetLethality",			&GameObject::get_lethality)
		.def("GetHealthRegen",			&GameObject::get_health_regen)
		.def("GetLevel",			    &GameObject::get_level)
		.def("GetAiManager",			&GameObject::get_ai_manager,   return_exist_obj())
		.def("GetBuffManager",			&GameObject::get_buff_manager, return_exist_obj())
		.def("GetSpellbook",			&GameObject::get_spell_book,   return_exist_obj())
		.def("GetModelHash",            &GameObject::get_model_hash)
		.def("ChangeSkin",              &GameObject::change_skin)
		.def("CanAttack",               &GameObject::can_attack)
		.def("__str__",                 &GameObject::get_name);

	def("GetPlayer",      &Globals::get_local_player, return_exist_obj());
	def("GetAllHeroes",   &CPyObjectManager_GetHeroes);
	def("GetAllyHeroes",  &CPyObjectManager_GetAllyHeroes);
	def("GetEnemyHeroes", &CPyObjectManager_GetEnemyHeroes);
	def("GetMinios",      &CPyObjectManager_GetMinions);

	def("IsPressed",      &WndProcEvent::is_key_pressed);
	def("GetTime",        &Globals::get_game_time);
	def("AddLog",         &CPyConsole_AddLog);

	def("DrawCircle3D",   &CPyDrawManager_DrawCircle3D);
	def("DrawCircle2D",   &CPyDrawManager_DrawCircle2D);
	def("DrawBar2D",      &CPyDrawManager_DrawBar2D);
}

void init_kaleidoscope()
{
	PyImport_AppendInittab("database",      &PyInit_database);
	PyImport_AppendInittab("windowmanager", &PyInit_windowmanager);
	PyImport_AppendInittab("kaleidoscope",  &PyInit_kaleidoscope);
}