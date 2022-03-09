#include "pch.h"

HudManager* HudManager::instance()
{
	return *reinterpret_cast<HudManager**>(Patchables::hudManager);
}
