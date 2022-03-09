#pragma once
#include <string>
#include "Vector3.h"
#include "SpellInfo.h"
#include "AiManager.h"
#include "SpellBook.h"
#include "BuffManager.h"
#include "CharacterDataStack.h"

class GameObject
{
public:
	std::string	get_name();
	float		get_bounding_radius();
	AiManager*  get_ai_manager();
	UINT        get_action_state();
	bool		can_attack();

	bool		is_alive();
	bool		is_targetable();
	float       get_windup();
	float		get_attack_delay();

	CharacterDataStack* get_character_data_stack();
	
	void change_skin(std::int32_t skin);
	uint32_t get_model_hash();
	
	MAKE_GET_PTR(buff_manager, BuffManager*, GameObject)
	MAKE_GET_PTR(spell_book, SpellBook*, GameObject)

	MAKE_GET(index, int, GameObject)
	MAKE_GET(team_id, int, GameObject)
	MAKE_GET(network_id, short, GameObject)
	MAKE_GET(visible, bool, GameObject)
	MAKE_GET(position, Vector3, GameObject)
	MAKE_GET(health, float, GameObject)
	MAKE_GET(max_health, float, GameObject)
	MAKE_GET(mana, float, GameObject)
	MAKE_GET(max_mana, float, GameObject)
	MAKE_GET(armor, float, GameObject)
	MAKE_GET(bonus_armor, float, GameObject)
	MAKE_GET(magic_resist, float, GameObject)
	MAKE_GET(bonus_magic_resist, float, GameObject)
	MAKE_GET(crit_change, float, GameObject)
	MAKE_GET(crit_multiplex, float, GameObject)
	MAKE_GET(ability_haste, float, GameObject)
	MAKE_GET(magic_pen, float, GameObject)
	MAKE_GET(magic_pen_percent, float, GameObject)
	MAKE_GET(life_steal, float, GameObject)
	MAKE_GET(attack_speed, float, GameObject)
	MAKE_GET(attack_range, float, GameObject)
	MAKE_GET(base_attack_damage, float, GameObject)
	MAKE_GET(bonus_attack_damage, float, GameObject)
	MAKE_GET(armor_pen_percent, float, GameObject)
	MAKE_GET(lethality, float, GameObject)
	MAKE_GET(health_regen, float, GameObject)
	MAKE_GET(level, int, GameObject)
	MAKE_GET(duration, float, GameObject)
	MAKE_GET(missile_spell_info, SpellInfo*, GameObject)
	MAKE_GET(missile_source_index, short, GameObject)
	MAKE_GET(missile_start_pos, Vector3, GameObject)
	MAKE_GET(missile_end_pos, Vector3, GameObject)
	MAKE_GET(missile_current_pos, Vector3, GameObject)
	MAKE_GET(missile_index, short, GameObject)

};