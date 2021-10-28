#pragma once
#pragma once

#include "common.hpp"
#include "natives.hpp"
#include "gui\event_json.h"

namespace big
{
	namespace local_test_json_inner
	{
		struct local_test_json_inner
		{
			LocalAppendageType type{};
			std::ptrdiff_t index{};
			std::size_t size{};
			std::string local_name{};
		};
		static void to_json(nlohmann::json& j, const local_test_json_inner& inner) {
			j = nlohmann::json{ {"type", inner.type}, {"index", inner.index}, {"size", inner.size}, {"local_name", inner.local_name} };
		}

		static void from_json(const nlohmann::json& j, local_test_json_inner& inner) {
			j.at("type").get_to(inner.type); j.at("index").get_to(inner.index); j.at("size").get_to(inner.size); j.at("local_name").get_to(inner.local_name);
		}
	}
	namespace local_test_json
	{
		struct local_test_json
		{
			std::size_t local_index{};
			std::vector<local_test_json_inner::local_test_json_inner> local_appendages{};
		};
		static void to_json(nlohmann::json& j, const local_test_json& local) {
			j = nlohmann::json{ {"local_index", local.local_index}, {"local_appendages", local.local_appendages} };
		}

		static void from_json(const nlohmann::json& j, local_test_json& local) {
			j.at("local_index").get_to(local.local_index); j.at("local_appendages").get_to(local.local_appendages);
		}
	}
	namespace global_test_json_inner
	{
		struct global_test_json_inner
		{
			GlobalAppendageType type{};
			std::ptrdiff_t index{};
			std::size_t size{};
			std::string global_name{};
		};
		static void to_json(nlohmann::json& j, const global_test_json_inner& inner) {
			j = nlohmann::json{ {"type", inner.type}, {"index", inner.index}, {"size", inner.size}, {"global_name", inner.global_name} };
		}

		static void from_json(const nlohmann::json& j, global_test_json_inner& inner) {
			j.at("type").get_to(inner.type); j.at("index").get_to(inner.index); j.at("size").get_to(inner.size); j.at("global_name").get_to(inner.global_name);
		}
	}
	namespace global_test_json
	{
		struct global_test_json
		{
			std::size_t global_index{};
			std::vector<global_test_json_inner::global_test_json_inner> global_appendages{};
		};
		static void to_json(nlohmann::json& j, const global_test_json& global) {
			j = nlohmann::json{ {"global_index", global.global_index}, {"global_appendages", global.global_appendages} };
		}

		static void from_json(const nlohmann::json& j, global_test_json& global) {
			j.at("global_index").get_to(global.global_index); j.at("global_appendages").get_to(global.global_appendages);
		}
	}

	class script_helper
	{
	public:
		static bool is_script_active(Hash ScriptHash);

	};

	class remote_event
	{
	public:
		static void take_all_cayo(int take);
		static void take_all_casino(int take);
		static void take_casino_partial(int take);
		static void get_name_from_event_hash(int32_t hash);
		static void trigger_event(int64_t* args, int argsCount, int bitset);
		static void RemoteOffRadar(bool toggle);
		static void RemoteBribe(bool toggle);
		static void bail_player(Player player);
		static void revenge_kick(bool Activation);
		static void teleport_player_to_cayo(Player player);
		static void force_invite_apartment(Player player);
		static void ceo_kick(Player player);
		static void ceo_ban(Player player);
		static void rotate_cam(Player player);
		static void vehicle_kick(Player player);
		static void clear_wanted(Player player);
		static void kick_player(Player player);
		static void transaction_fail(Player player);
		static void send_to_mission(Player player);
		static void give_fake_money(Player player, int TotalMoney);
		static void remove_fake_money(Player player, int TotalMoney);
		static void steal_fake_money(Player player, int TotalMoney);
		static void give_wanted_level(Player player);
	};

	class script_tester
	{
	public:
		static std::filesystem::path get_events_config();
		static nlohmann::json get_events_json();
		static std::vector<std::string> list_events();
		static void load_event_menu(std::string& selected_event, event_json::event_json& event_obj);
		static void save_event(char* event_name, event_json::event_json& event_obj);
		static void delete_event(std::string name);
	};

	class global_tester
	{
	public:
		static std::filesystem::path get_globals_config();
		static nlohmann::json get_globals_json();
		static void load_global_menu(const std::string& selected_global, global_test_json::global_test_json& global_obj);
		static void save_global(char* global_name, global_test_json::global_test_json& global_obj);
		static void delete_global(std::string name);
		static int64_t* get_global_ptr(global_test_json::global_test_json& global_test);
	};

	class local_tester
	{
	public:
		static std::filesystem::path get_locals_config();
		static nlohmann::json get_locals_json();
		static void load_local_menu(const std::string& selected_local, local_test_json::local_test_json& local_obj);
		static void save_local(char* local_name, local_test_json::local_test_json& local_obj);
		static void delete_local(std::string name);
		static int32_t* get_local_ptr(GtaThread* scriptThread, local_test_json::local_test_json& local_test);
	};

	extern std::map<std::string, global_test_json::global_test_json> list_globals();
	extern std::map<std::string, local_test_json::local_test_json> list_locals();
}