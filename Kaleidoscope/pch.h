// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#pragma warning(disable:4244)

// add headers that you want to pre-compile here
#include "framework.h"
#include "macros.h"

#include <mutex>
#include <memory>
#include <cstdio>
#include <cinttypes>
#include <algorithm>
#include <experimental/vector>

#include <d3d11.h>
#include <polyhook2/Virtuals/VFuncSwapHook.hpp>

#include <Python.h>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <boost/format.hpp>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"


#include "FnvHash.h"
#include "Encryption.h"
#include "WndProcEvent.h"

#include "Core.h"
#include "DxHook.h"

#include "Offsets.h"
#include "Patchables.h"

#include "Singleton.h"
#include "Console.h"

#include "PyLauncher.h"
#include "PyExports.h"

#include "Component.h"
#include "WindowManager.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "Globals.h"
#include "GameClient.h"
#include "NetClient.h"
#include "SpellBook.h"
#include "SpellInfo.h"
#include "SpellData.h"
#include "SpellSlot.h"
#include "SpellCastInfo.h"
#include "SpellInstanceClient.h"
#include "BuffManager.h"
#include "AiManager.h"
#include "CharacterDataStack.h"
#include "GameObject.h"
#include "HudManager.h"
#include "Renderer.h"
#include "WorldCursor.h"
#include "InputLogic.h"
#include "SpellLogic.h"
#include "MenuGUI.h"
#include "TacticalMap.h"
#include "MissileManager.h"
#include "ObjectManager.h"
#include "NavMesh.h"

#include "SkinDatabase.h"

#endif //PCH_H
