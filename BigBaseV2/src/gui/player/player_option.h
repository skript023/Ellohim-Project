#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class player
	{
	public:
		static void set_playeer_super_punch(bool activate);
		static void set_player_no_damage(bool activate);
		static std::string get_player_city(Player player);
		static std::string get_player_internet_provider(Player player);
		static std::string get_player_country(Player player);
		static const char* get_player_heist_hacker(Player player);
		static const char* get_player_heist_gunman(Player player);
		static const char* get_player_heist_driver(Player player);
		static const char* get_player_heist_target(Player player);
		static const char* get_player_heist_hard_approach(Player player);
		static const char* get_player_heist_last_approach(Player player);
		static const char* get_player_heist_approach(Player player);
		static const char* get_player_heist_secondary_status(Player player);
		static const char* get_player_heist_primary_status(Player player);
		static const char* is_modded_account(Player player);
		static int get_player_banked_money(Player player);
		static int get_player_level(Player player);
		static int get_player_exp(Player player);
		static int get_player_global_exp(Player player);
		static int get_player_cash(Player player);
		static int get_player_total_money(Player player);
		static void get_player_location(Player player);
		static void global_exp_correction();
		static bool get_player_infinite_ammo(Player player);
		static bool is_player_out_of_radar(Player player);
		static Ped player_ped_id();
		static const char* get_player_organization_name(Player player);
		static void self_noclip(bool activate);
		static bool get_player_infinite_clip(Player player);
		static bool is_player_in_any_vehicle(Player player);
		static bool does_player_exist(Player player);
		static void never_wanted(bool Activation);
		static bool is_player_driver(Ped Ped);
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

		static void auto_heal(bool Activation);

		static void player_health_regeneration(bool Activation);

		
		static void set_player_wanted_level(Player player, int Wantedlevel);
		static void mission_lives(bool Activation);
		static void set_player_waterproof(Player player, bool Activation);
		static void set_player_infinite_oxygen(Player player, bool activation);
		static void blind_cops(bool Activation);
		static void set_player_seatbelt(bool Activation);
		static void set_player_invincible(Player player, bool Activation);
		static void reveal_player(bool Activation);
		static void off_the_radar(bool Activation);
		static void ghost_organization(bool Activation);
		static void set_player_no_collision(bool Activation);

		static int get_player_health(Player player);
		static int get_player_max_health(Player player);
		static int get_player_armour(Player player);
		static int get_player_max_amour(Player player);

		static std::string get_player_local_ip(Player player);

		static void local_name(char* Name);
		static uint64_t get_player_scid(Player player);
		static void ultra_run(bool Activation);
		static void give_all_heal(bool Activation);
		static void set_payer_level(int PlayerLevel);
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
	public:
		static inline bool all_mission_lives{};
		static inline bool pass_through_wall{};
		static inline bool send_heal{};
		static inline bool blinds_cops{};
		static inline bool reveal_players{};
		static inline bool ultra_run_bool{};
		static inline bool no_clip{};
		static inline bool no_clip_2{};
		static inline bool night_vision{};
		static inline bool thermal_vision{};
		static inline bool ghost_organizations{};
		static inline bool auto_click{ false };
		static inline bool waterproof{};
		static inline bool is_ped_visible{};
		static inline bool is_ped_aggressive{};
		static inline bool is_ped_bodyguard{};
		static inline bool is_force_applied{};
		static inline bool is_infinite_oxygen{};
		static inline int player_aim{};
		static inline bool no_damage{};
		static inline bool super_punch{};
	private:
		static inline int request_tick = 0;
		static inline const int controls[] = { 21, 32, 33, 34, 35, 36 };
		static inline float speed = 20.f;
		static inline float mult = 0.f;

		static inline bool bLastNoclip = false;

		static inline Entity prev = -1;
		static inline Vector3 rot{};

	};
	class outfit
	{
	public:
		static void set_appearance(char* family, int model, int texture);

		static void reset_appearance();

		static void steal_outfit(Player player);
	private:
		static inline int fam{};
	};
	class spoofer
	{
	public:
		static void player_crew(char* Tag);
		static void player_scid(uint64_t FakeRID);
		static void player_level(bool Activation, int level);
		static void player_money(bool activation, int money);
	public:
		static inline int rid_spoof{};
		static inline int spoofer_type{};
		static inline int stat_spoofer{};
		static inline int rid_spoof_type{};
		static inline char spoofed_name[20];
		static inline bool money_spoofer{};
		static inline bool level_spoofer{};
		static inline bool crew_spoofer{};

		static inline int spoofed_level{};
		static inline int spoofed_money{};
		static inline int rid{};
		static inline uint8_t ip_1{};
		static inline uint8_t ip_2{};
		static inline uint8_t ip_3{};
		static inline uint8_t ip_4{};

	};

	inline static player g_player_option{};
	inline static spoofer* g_spoofer_option{};
}