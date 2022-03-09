#pragma once
#include <string>
#include <map>
#include <vector>
#include <cinttypes>

namespace Data
{
	namespace SkinDatabase
	{
		class skin_info 
		{
		public:
			std::string model_name;
			std::string skin_name;
			int32_t     skin_id;

			bool operator==(const skin_info& other)
			{ 
				return skin_name == other.skin_name;
			}
		};

		inline std::map<uint32_t, std::vector<skin_info>> champions_skins;
		void load();
	}
}