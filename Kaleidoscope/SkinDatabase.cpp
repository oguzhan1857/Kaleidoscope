#include "pch.h"
#include "SkinDatabase.h"
#include "ChampionManager.h"

void Data::SkinDatabase::load()
{
	static const auto translateString_UNSAFE_DONOTUSE = reinterpret_cast<const char* (__cdecl*)(const char*)>(M_RVA(0x941330));
	auto champion_data = ChampionManager::instance()->get_champions();
	for (auto& champion : champion_data) {
		std::vector<int32_t> skins_ids;
		for (auto& skin : champion->skins)
			skins_ids.push_back(skin.skin_id);
		std::sort(skins_ids.begin(), skins_ids.end());

		std::map<std::string, int32_t> temp_skin_list;
		for (auto& i : skins_ids) {
			auto skin_display_name = std::string("game_character_skin_displayname_");
			skin_display_name.append(champion->champion_name.str);
			skin_display_name.append("_");
			skin_display_name.append(std::to_string(i));

			auto skin_display_name_translated = i > 0 ? std::string(translateString_UNSAFE_DONOTUSE(skin_display_name.c_str())) : std::string(champion->champion_name.str);

			auto it = temp_skin_list.find(skin_display_name_translated);

			if (it == temp_skin_list.end())
				temp_skin_list[skin_display_name_translated] = 1;
			else {
				skin_display_name_translated.append(" Chroma ");
				skin_display_name_translated.append(std::to_string(it->second));

				it->second = it->second + 1;
			}

			champions_skins[fnv::hash_runtime(champion->champion_name.str)].push_back(skin_info{ std::string(champion->champion_name.str),skin_display_name_translated,i });

			if (i == 7 && fnv::hash_runtime(champion->champion_name.str) == FNV("Lux")) {
				champions_skins[fnv::hash_runtime(champion->champion_name.str)].push_back(skin_info{ "LuxAir", "Elementalist Air Lux", i });
				champions_skins[fnv::hash_runtime(champion->champion_name.str)].push_back(skin_info{ "LuxFire", "Elementalist Fire Lux", i });
				champions_skins[fnv::hash_runtime(champion->champion_name.str)].push_back(skin_info{ "LuxIce", "Elementalist Ice Lux", i });
				champions_skins[fnv::hash_runtime(champion->champion_name.str)].push_back(skin_info{ "LuxMagma", "Elementalist Magma Lux", i });
				champions_skins[fnv::hash_runtime(champion->champion_name.str)].push_back(skin_info{ "LuxMystic", "Elementalist Mystic Lux", i });
				champions_skins[fnv::hash_runtime(champion->champion_name.str)].push_back(skin_info{ "LuxNature", "Elementalist Nature Lux", i });
				champions_skins[fnv::hash_runtime(champion->champion_name.str)].push_back(skin_info{ "LuxStorm", "Elementalist Storm Lux", i });
				champions_skins[fnv::hash_runtime(champion->champion_name.str)].push_back(skin_info{ "LuxWater", "Elementalist Water Lux", i });
			}
		}
	}
}
