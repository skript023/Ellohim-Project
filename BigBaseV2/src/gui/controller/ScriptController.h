#pragma once

#include "common.hpp"
#include "natives.hpp"
#include "gta\player.hpp"

namespace big
{
	class controller
	{
		public:
			static std::string char_to_string(char* a, int size);
			
			static bool cstrcmp(const char* s1, const char* s2);
			static Hash load(const char* name);
			static const char* load_anim(const char* anim);
			
			
			
			static void RequestControlOfid(Entity netid);
			static Ped ClonePed(Ped ped);
			static void CreatePed(Hash PedHash, Vector3 SpawnCoordinates, int ped_type, bool network_handle);
			
			
			static void set_clipboard(const char* message);

			
			static void FasterTimeScale(bool Activation);
			static void TimeSpam(bool Activation);
			
			
			static void InvalidModelProtection(bool Activation);
			static Ped CrashPlayer(Entity target, Vector3 SpawnCoordinates);
			static void ShowMessage(const char* Message, bool InPauseMenu);
			
			static void CheckInvalidPed();
			static void NightclubTriggerProduction();
			static void AttachPed(Hash PedHash, Ped Target);
			
			
			static void variable_attach();
			static void DumpEntryBoi();
			
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

	extern bool isSpectatingMe(Player player);
	
	extern void Notification(const char* Meesage);
}
/*
ImGui::InputScalar("##Get hour", ImGuiDataType_U32, &date[6], get_step ? &step_one : NULL, NULL, "%u", ImGuiInputTextFlags_ReadOnly);
ImGui::InputScalar("##Get minute", ImGuiDataType_U32, &date[8], get_step ? &step_one : NULL, NULL, "%u", ImGuiInputTextFlags_ReadOnly);
ImGui::InputScalar("##Get second", ImGuiDataType_U32, &date[10], get_step ? &step_one : NULL, NULL, "%u", ImGuiInputTextFlags_ReadOnly);
ImGui::InputScalar("##Get mili", ImGuiDataType_U32, &date[12], get_step ? &step_one : NULL, NULL, "%u", ImGuiInputTextFlags_ReadOnly);
*/