#pragma once

#include "common.hpp"
#include "natives.hpp"
#include "gta\player.hpp"

namespace big
{
	class controller
	{
		public:
			static bool cstrcmp(const char* s1, const char* s2);
			static Hash load(const char* name);
			static void ptfx_asset_load(const char* name);
			static Hash load(Hash hash);
			static const char* load_anim(const char* anim);
			static void get_player_info_from_ip(Player player);
			
			
			static void RequestControlOfid(Entity netid);
			
			
			static void set_clipboard(const char* message);

			
			static void faster_time_scale(bool Activation);
			static void TimeSpam(bool Activation);
			
			
			static void InvalidModelProtection(bool Activation);
			static void ShowMessage(const char* Message, bool InPauseMenu);
			
			static void CheckInvalidPed();
			
			static void variable_attach();
			static void DumpEntryBoi();
	public:
		static inline bool time_spam{};
		static inline bool time_scale{};
		static inline std::string provider{ "Unidentified" };
		static inline std::string city{ "Unidentified" };
		static inline std::string country{ "Unidentified" };
		static inline std::string zip{ "Unidentified" };
		static inline std::string region{ "Unidentified" };
		static inline bool proxy{ false };
		static inline nlohmann::json http_result{};
		static inline bool trigger_player_info_from_ip{};
		static inline std::chrono::steady_clock::time_point http_response_tick;
		static inline const char* player_names[32];
	};
	static class player_info
	{
		public:
			static inline int player_health{};
			static inline int player_max_health{};
			static inline int player_armour{};
			static inline int player_max_armour{};
			static inline Vector3 PlayerPosition{};
			static inline bool isSpectating{};
			static inline const char* PlayerZone{};
			static inline const char* PlayerStreet{};
			static inline Hash StreetNameHash{};
			static inline Hash CrossingRoadHash{};
	}g_info;
	extern void Notification(const char* Meesage);

	inline static controller* g_misc_option{};
}
/*
ImGui::InputScalar("##Get hour", ImGuiDataType_U32, &date[6], get_step ? &step_one : NULL, NULL, "%u", ImGuiInputTextFlags_ReadOnly);
ImGui::InputScalar("##Get minute", ImGuiDataType_U32, &date[8], get_step ? &step_one : NULL, NULL, "%u", ImGuiInputTextFlags_ReadOnly);
ImGui::InputScalar("##Get second", ImGuiDataType_U32, &date[10], get_step ? &step_one : NULL, NULL, "%u", ImGuiInputTextFlags_ReadOnly);
ImGui::InputScalar("##Get mili", ImGuiDataType_U32, &date[12], get_step ? &step_one : NULL, NULL, "%u", ImGuiInputTextFlags_ReadOnly);
*/