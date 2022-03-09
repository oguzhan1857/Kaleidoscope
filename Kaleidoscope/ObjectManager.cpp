#include "pch.h"

ObjectManager* ObjectManager::instance()
{
	return *reinterpret_cast<ObjectManager**>(Patchables::objectManager);
}

std::map<int, GameObject*> ObjectManager::get_object_map()
{
	return *reinterpret_cast<std::map<int, GameObject*>*>(this + __INT(Offsets::ObjectManager::object_map));
}

ManagerTemplate<GameObject>* ObjectManager::get_hero_manager()
{
	return *reinterpret_cast<ManagerTemplate<GameObject>**>(Patchables::heroManager);
}

ManagerTemplate<GameObject>* ObjectManager::get_minion_manager()
{
	return *reinterpret_cast<ManagerTemplate<GameObject>**>(Patchables::minionManager);
}