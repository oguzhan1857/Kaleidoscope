#include "pch.h"

std::string GameObject::get_name()
{
	auto name = *reinterpret_cast<char**>(this + static_cast<__int32>((Offsets::GameObject::name)));
	return std::string(name);
}

float GameObject::get_bounding_radius()
{
	return call_virtual<35, float>(this);
}

AiManager* GameObject::get_ai_manager()
{
	return call_virtual<149, AiManager*>(this);
}

UINT GameObject::get_action_state()
{
	return *reinterpret_cast<UINT*>(this + 0x1084);
}

bool GameObject::can_attack()
{
	auto action = get_action_state();
	return (action + 0x24) & 1;
}

bool GameObject::is_alive()
{
	return reinterpret_cast<bool(__thiscall*)(GameObject*)>(Patchables::isAlive)(this);
}

bool GameObject::is_targetable()
{
	return reinterpret_cast<bool(__thiscall*)(GameObject*)>(Patchables::isTargetable)(this);
}

float GameObject::get_windup()
{
	return reinterpret_cast<float(__cdecl*)(GameObject*)>(Patchables::windUp)(this);
}

float GameObject::get_attack_delay()
{
	return reinterpret_cast<float(__cdecl*)(GameObject*)>(Patchables::attackDelay)(this);
}

CharacterDataStack* GameObject::get_character_data_stack()
{
	return reinterpret_cast<CharacterDataStack*>(std::uintptr_t(this) + __INT(Offsets::GameObject::character_data_stack));
}

void GameObject::change_skin(std::int32_t skin)
{
	reinterpret_cast<xor_value<std::int32_t>*>(std::uintptr_t(this) + 0x1B60)->encrypt(skin);
	this->get_character_data_stack()->base_skin.skin = skin;
	this->get_character_data_stack()->update(true);
}

uint32_t GameObject::get_model_hash()
{
	return fnv::hash_runtime(this->get_character_data_stack()->base_skin.model.str);
}