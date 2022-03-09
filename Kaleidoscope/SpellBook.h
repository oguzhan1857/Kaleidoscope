#pragma once
#include "SpellSlot.h"
#include "SpellInstanceClient.h"

class SpellBook
{
public:
	int                  get_spell_state(int slot);
	SpellSlot*           get_spell_slot(int slot);
	SpellInstanceClient* get_active_spell();
};