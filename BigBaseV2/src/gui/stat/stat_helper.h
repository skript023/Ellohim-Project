#pragma once
#include "common.hpp"
#include "natives.hpp"

namespace big
{
	namespace stats_json
	{
		struct stats_json
		{
			int stats = 1;
			std::vector<int> stat_type{};
			std::vector<std::string> stat_name{};
			std::vector<int> stat_int_value{};
			std::vector<bool> stat_bool_value{};
			std::vector<float> stat_float_value{};
		};
		static void to_json(nlohmann::json& j, const stats_json& attachment) {
			j = nlohmann::json{ {"stats", attachment.stats},
								{"stat_type", attachment.stat_type},
								{"stat_name", attachment.stat_name},
								{"stat_int_value", attachment.stat_int_value},
								{"stat_bool_value", attachment.stat_bool_value},
								{ "stat_float_value", attachment.stat_float_value },
			};
		}
		static void from_json(const nlohmann::json& j, stats_json& attachment) {
			j.at("stats").get_to(attachment.stats);
			j.at("stat_type").get_to(attachment.stat_type);
			j.at("stat_name").get_to(attachment.stat_name);
			j.at("stat_int_value").get_to(attachment.stat_int_value);
			j.at("stat_bool_value").get_to(attachment.stat_bool_value);
			j.at("stat_float_value").get_to(attachment.stat_float_value);
		}

	};

	class stats
	{
	public:
		static std::string get_packed_stat_name_from_hash(Hash hash);
		static bool is_all_stat_packed(Hash hash);
		static std::string get_stat_name_from_hash(Hash hash);
		static bool is_all_stat(Hash hash);
		static bool set_packed_int(int iParam0, int iParam1, int iParam2, bool bParam3);
		static int get_packed_int(int iParam0, int iParam1, int iParam2);
		static int packed_stat_name(int iParam0, int iParam1);
		static int packed_stat_mask(int iParam0);
		static std::string packed_reversed(uint32_t hash);

		static int packed_bool_stat_mask(int iParam0);
		static int packed_bool_stat_name(int iParam0, int iParam1);
		static bool get_packed_bool(int iParam0, int iParam1, int iParam2);
		static bool set_packed_bool(int iParam0, bool bParam1, int iParam2, int iParam3);

		static std::filesystem::path get_stats_config();
		static nlohmann::json get_stats_json();
		static std::vector<std::string> list_stats();
		static void load_stat_menu(std::string& selected_stat, stats_json::stats_json& stat_obj);
		static void save_stat(char* stat_name, stats_json::stats_json& stat_obj);
		static void delete_stat(std::string name);
	};
	
	extern void set_stat(Hash stat, int value);
	extern void set_bitset(int value);
	extern void set_bitset_one(int value);
}