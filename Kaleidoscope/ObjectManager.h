#pragma once
#include <map>
#include "GameObject.h"
#include "macros.h"

template <class T>
class ManagerTemplate
{
	PAD(0x4);
public:
	T** list;
	std::size_t length;
	std::size_t capacity;
};

class ObjectManager
{
public:
	static ObjectManager* instance();
	std::map<int, GameObject*> get_object_map();

	static ManagerTemplate<GameObject>* get_hero_manager();
	static ManagerTemplate<GameObject>* get_minion_manager();
};