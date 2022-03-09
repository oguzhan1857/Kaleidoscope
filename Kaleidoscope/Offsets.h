#pragma once

class Offsets
{
public:
	enum class Gui
	{
		materialRegistry = 0xa83f50,
		riotWindow       = 0x31168dc,
		device           = 0x210,
		swapChain        = 0x114,
	};

	enum class GameClient
	{
		instance = 0x310AA08,
		state    = 0x8,
	};

	enum class GameObject
	{
		name					= 0x2BE4,
		index					= 0x20,
		team_id				    = 0x4C,
		network_id			    = 0xCC,
		visible				    = 0x28C,
		position				= 0x1F4,
		health				    = 0xDB4,
		max_health			    = 0xDC4,
		mana					= 0x2B4,
		max_mana				= 0x2C4,
		armor					= 0x12E4,
		bonus_armor			    = 0x12E8,
		magic_resist			= 0x12EC,
		bonus_magic_resist	    = 0x12F0,
		crit_change			    = 0x12E0,
		crit_multiplex		    = 0x12D0, 
		ability_haste			= 0x110C,
		magic_pen				= 0x11DC,
		magic_pen_percent		= 0x11E4,
		life_steal			    = 0x0,   
		attack_speed			= 0x12B8,
		attack_range			= 0x1304,
		base_attack_damage	    = 0x12BC,
		bonus_attack_damage	    = 0x1234,
		armor_pen_percent		= 0x1978,
		lethality				= 0x11F8,
		health_regen			= 0x12F8,
		level					= 0x33A4,
		duration                = 0x2B4,
		missile_spell_info	    = 0x278,
		missile_source_index	= 0x2DC,
		missile_start_pos		= 0x2F4,
		missile_end_pos		    = 0x300,
		missile_current_pos	    = 0x0,
		missile_index			= 0x330,
		buff_manager			= 0x21B8,
		spell_book			    = 0x2370,
		character_data_stack    = 0x2BD8,
	};

	enum class SpellBook
	{
		spell_state  = 0x0,
		spell_slot   = 0x488,
	};

	enum class SpellSlot
	{
		level            = 0x20,
		cooldown_expire  = 0x28,
		cooldown         = 0x78,
		remaining_charge = 0x58,
		spell_info       = 0x13C,
		target_info      = 0x138,
	};

	enum class SpellData
	{
		name        = 0x6C,
		range       = 0x0,
		cast_radius = 0x0,
		speed       = 0x0,
		width       = 0x0,
		mana_cost   = 0x0
	};

	enum class SpellEntry
	{
		spell_info = 0x0,
		start_pos = 0x0,
		end_pos = 0x0,
		slot = 0x0,
		basic = 0x0,
		windup_time = 0x0,
		cast_start_time = 0x0
	};
	
	enum class SpellInfo
	{
		name        = 0x18,
		name_length = 0x28,
		spell_data  = 0x44,
	};

	enum class Globals
	{
		game_time       = 0x310DF84,
		world_to_screen = 0x0,
		local_player    = 0x31168D4,
		wind_up         = 0x276d60,
		attack_delay    = 0x276e60,
		is_alive        = 0x13f8d0,
		is_targetable   = 0x6E71F0,
	};

	enum class AiManager
	{
		moving_status  = 0x1C0,
		dashing_status = 0x214,
		waypoint_index = 0x1C4,
		dash_speed     = 0x1F8,
		velocity       = 0x2F0,
		move_speed	   = 0x1BC,
		nav_mesh       = 0x1B0,
		nav_path       = 0x1C4,
		waypoint_end   = 0x1E8,
	};

	enum class Buff
	{
		name = 0x8,
	};

	enum class BuffEntry
	{
		alt_buff    = 0x8,
		start_time  = 0xC,
		end         = 0x10,
		buff_count1 = 0x20,
		buff_count2 = 0x24,
	};

	enum class BuffManager
	{
		buff_vector = 0x10,
	};

	enum class Renderer
	{
		instance          = 0x3143DE0,
		window_width      = 0xC,
		window_height     = 0x10,
		view_matrix       = 0x58,
		projection_matrix = 0x98
	};

	enum class HudManager
	{
		instance     = 0x1879860,
		world_cursor = 0x14,
		input_logic  = 0x24,
		spell_logic  = 0x34,
	};

	enum class WorldCursor
	{
		x = 0x10,
		y = 0x14,
		z = 0x18,
	};

	enum class InputLogic
	{
		issue_order_click = 0x5ed0c0,
	};

	enum class SpellLogic
	{
		issue_spell       = 0x5E2D10,
		send_skill_packet = 0x5E27B0,
	};

	enum class ObjectManager
	{
		instance       = 0x1879830,
		object_map     = 0x28,
		hero_manager   = 0x1877334,
		minion_manager = 0x18798C4,
	};

	enum class MenuGUI
	{
		instance       = 0x310F288,
		tactical_map = 0x110,
	};

	enum class TacticalMap
	{
		world_to_minimap = 0x61cd40,
	};

	enum class ChampionManager
	{
		instance = 0x310F4B0,
		champ_vector = 0x18,
	};

	enum class NetClient
	{
		instance = 0x311E868,
		get_ping = 0x336750,
	};
};