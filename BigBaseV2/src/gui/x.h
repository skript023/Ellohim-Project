#pragma once

#include "common.hpp"
#include "natives.hpp"
#include "gta\player.hpp"
#include "gui\EventJson.h"

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
	
	class controller
	{
		public:
			static std::string char_to_string(char* a, int size);
			
			static std::filesystem::path get_locals_config();
			static nlohmann::json get_locals_json();
			static void load_local_menu(const std::string& selected_local, local_test_json::local_test_json& local_obj);
			static void save_local(char* local_name, local_test_json::local_test_json& local_obj);
			static void delete_local(std::string name);
			static int32_t* get_local_ptr(GtaThread* scriptThread, local_test_json::local_test_json& local_test);

			static bool cstrcmp(const char* s1, const char* s2);
			static Hash load(const char* name);
			
			static void changeAppearance(char* family, int model, int texture);
			static void spawn_object(const char* name, Entity entity);
			static void CreatePickup(const char* pickup, const char* prop, int amount, Entity entity);
			static void AttacthObject(const char* name, Entity entity);
			
			static void teleport_to_coords(Entity e, Vector3 coords);
			static void teleport_to_marker();
			static void teleport_to_objective();
			static float GetPlayerHP();
			static void RequestControlOfid(Entity netid);
			static void RequestControlOfEnt(Entity entity);
			static Ped ClonePed(Ped ped);
			static void CreatePed(Hash PedHash, Vector3 SpawnCoordinates, int ped_type, bool network_handle);
			
			static void SetPlayerLevel(int PlayerLevel);
			static void GiveHealAll(bool Activation);
			static void SpectatePlayer(Ped playerped);
			static void ResetAppearance();

			static Vector3 get_mission_blip();
			static Vector3 get_blip_marker();
			static Vector3 GetGroundCoords(Vector3 coords, int tries);
			
			static void set_clipboard(const char* message);

			static std::filesystem::path get_events_config();
			static nlohmann::json get_events_json();
			static std::vector<std::string> list_events();
			static void load_event_menu(std::string& selected_event, event_json::event_json& event_obj);
			static void save_event(char* event_name, event_json::event_json& event_obj);
			static void delete_event(std::string name);

			static void ChangeCrewTag(char* Tag);
			static void FasterTimeScale(bool Activation);
			static void TimeSpam(bool Activation);
			static void RIDSpoofer(uint64_t FakeRID);
			static void Revenge(Hash Weapon, bool Activation);
			static void RevengeKick(bool Activation);
			static void StealOutfit(Player player);
			
			static std::filesystem::path get_globals_config();
			static nlohmann::json get_globals_json();
			static void load_global_menu(const std::string& selected_global, global_test_json::global_test_json& global_obj);
			static void save_global(char* global_name, global_test_json::global_test_json& global_obj);
			static void delete_global(std::string name);
			static int64_t* get_global_ptr(global_test_json::global_test_json& global_test);

			
			static void RunSpeed(float speed);
			static void SwimSpeed(float speed);
			static void UltraRun(bool Activation);
			static void HeadShotNPC(bool Activation);
			static void InvalidModelProtection(bool Activation);
			static Ped CrashPlayer(Entity target, Vector3 SpawnCoordinates);
			static void ShowMessage(const char* Message, bool InPauseMenu);
			static void RemoveInsuranceClaims();
			static void CheckInvalidPed();
			static void NightclubTriggerProduction();
			static void AttachPed(Hash PedHash, Ped Target);
			
			
			static void variable_attach();
			static void DumpEntryBoi();
			static uint64_t GetPlayerRid(Player player);

			static bool HasSpecialCharacters(const char* str);
			static void AntiGriefVehicle(bool Activation);
			static bool IsNotANumber(const char* str);
	};
	class Script
	{
		public:
			static bool DoesScriptExist(rage::joaat_t Hash);
	};

	static class local_player_info_class
	{
	public:
		static inline Player player{};
		static inline Ped ped{};
		static inline Player SelectedPlayer{};
		static inline Ped SelectedPed{};
		static inline Player ScriptHost{};
		static inline Vehicle PlayerVehicle{};
		static inline bool InVehicle{};
		static inline bool Transition{};
		static inline int character{};
		static inline int connected_player{};
		static inline GtaThread* mission{};
		static inline GtaThread* mission_2020{};
		static inline GtaThread* arcade{};
		static inline bool invalid_protection = false;
		static inline bool transition{};
		static inline bool is_male{};
	} g_local;

	static class event_tester
	{
	public: 
		static inline Player event_player{};
		static inline Ped event_ped{};
	}g_event_tester;

	static class base_address
	{
		public:
			static inline uintptr_t WorldPTR{};
	} g_ptr;

	static class fitur
	{
		public:
			static inline int weapon_hash{};
			static inline int rid{};
	} g_item;

	static class toggle_bool
	{
	public:
		static inline bool godmode = false;
	} g_toggle;

	static class diamondheistinfo
	{
	public:
		static inline int approach{}, target{}, last_approach{}, hard_approach{};
		static inline int disrupt{}, keylevels{}, crewweap{}, crewdriver{}, crewhacker{}, vehs{}, weaps{}, masks{}, bodyarmorlvl{}, bitset{}, bitsetone{};
	} diamond_heist_info;

	extern std::map<std::string, global_test_json::global_test_json> list_globals();
	extern std::map<std::string, local_test_json::local_test_json> list_locals();
	extern bool isSpectatingMe(Player player);
	extern void set_stat(Hash stat, int value);
	extern void set_bitset(int value);
	extern void set_bitset_one(int value);
	extern void Notification(const char* Meesage);
}
/*
ImGui::InputScalar("##Get hour", ImGuiDataType_U32, &date[6], get_step ? &step_one : NULL, NULL, "%u", ImGuiInputTextFlags_ReadOnly);
ImGui::InputScalar("##Get minute", ImGuiDataType_U32, &date[8], get_step ? &step_one : NULL, NULL, "%u", ImGuiInputTextFlags_ReadOnly);
ImGui::InputScalar("##Get second", ImGuiDataType_U32, &date[10], get_step ? &step_one : NULL, NULL, "%u", ImGuiInputTextFlags_ReadOnly);
ImGui::InputScalar("##Get mili", ImGuiDataType_U32, &date[12], get_step ? &step_one : NULL, NULL, "%u", ImGuiInputTextFlags_ReadOnly);
*/