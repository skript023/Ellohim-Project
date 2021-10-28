#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class player
	{
	public:
		static void global_exp_correction();
		static bool get_player_infinite_ammo(Player player);
		static bool get_player_infinite_clip(Player player);
		static bool is_player_in_any_vehicle(Player player);
		static bool does_player_exist(Player player);
		static bool is_player_driver(Entity Ped);
		static bool is_ped_enemy(Entity Ped);
		static int get_ped_type(Entity Ped);
		static std::string get_player_ip(Player SelectedPlayer);
		static bool is_player_model_valid(rage::netSyncTree* netSyncTree, rage::netObject* netObject);
		static std::string get_ped_name_from_hash(Hash hash);
		static void set_player_no_clip(bool toggle);
		static Vehicle get_player_vehicle(Ped ped, bool last_vehicle);
		static void set_player_health(Player player, int HealthValue);
		static void set_player_armour(Player player, int ArmourValue);
		static void disable_player_ragdoll(Player player, bool activation);
		static Ped get_player_ped(Player player);
		static void no_idle_kick(bool Trigger);
		static void PlayerHealthRegen(bool Activation);
		static void AutoHeal(bool Activation);
		static void NeverWanted(bool Activation);
		static void set_player_wanted_level(Player player, int Wantedlevel);
		static void AllMissionLives(bool Activation);
		static void set_player_waterproof(Player player, bool Activation);
		static void SetPlayerSeatBelt(bool Activation);
		static void set_player_invincible(Player player, bool Activation);
		static void BlindCops(bool Activation);
		static void RevealRadar(bool Activation);
		static void OffTheRadar(bool Activation);
		static void GhostOrganization(bool Activation);
		static void SetPlayerNoCollision(bool Activation);

		static int get_player_health(Player player);
		static int get_player_max_health(Player player);
		static int get_player_armour(Player player);
		static int get_player_max_amour(Player player);

		static void local_name(char* Name);
		static void RunSpeed(float speed);
		static void SwimSpeed(float speed);
		static void UltraRun(bool Activation);
		static uint64_t get_player_scid(Player player);
		static void GiveHealAll(bool Activation);
		static void SetPlayerLevel(int PlayerLevel);
		static bool is_ped_shooting(Ped ped);
		static void change_name(const std::string& name, rage::netPlayerData* data);
		static bool get_player_invincible(Player player);
		static std::string get_player_weapon(Player player);
		static std::string get_player_vehicle_name(Player player);
		static int get_player_wanted_level(Player player);
		static const char* get_player_name(Player player);
		static Vector3 get_player_coords(Player player);
		static bool get_player_vehicle_invincible(Entity entity);
		static bool get_player_waterproof(Player player);
	};
	class outfit
	{
	public:
		static void StealOutfit(Player player);
		static void changeAppearance(char* family, int model, int texture);
		static void ResetAppearance();
	};
	class spoofer
	{
	public:
		static void player_crew(char* Tag);
		static void player_scid(uint64_t FakeRID);
		static void player_level(bool Activation, int level);
		static void player_money(bool activation, int money);
	};

}