#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class weapon_helper
	{
	public:
		uint32_t bit_frame = 0;

		static std::string get_weapon_name_from_hash(Hash weaponHash);
		static void teleport_gun(bool activation);
		static void no_spread(bool activation);
		static void no_recoil(bool activation);
		static void burst_weapon_ammo(bool activation);
		static bool is_model_shotgun(Hash hash);
		static void MoneyGun(bool activation);
		static void RemoveObjectsLoop(bool activation);
		static void CollisionGun(bool Activation);
		static void FrameFlag();
		static void rapid_fire(bool toggle);
		static void infinite_ammo(bool activation);
		static void Revenge(Hash Weapon, bool Activation);
		
		static void HeadShotNPC(bool Activation);
		static void explosive_ammo(bool Activation, Ped Target);

		static void set_fire_ammo_this_frame(Player player, bool activation);
		static void set_explosive_ammo_this_frame(Player player, bool activation);
		static void set_super_jump_this_frame(Player player, bool activation);
		static void set_explosive_melee_this_frame(Player player, bool activation);
	};

	static class weapon_spread_attributes
	{
	public:
		static constexpr inline float assault_rifle_spread = 3.5f;
		static constexpr inline float carbine_rifle_spread = 3.0f;
		static constexpr inline float advanced_rifle_spread = 2.5f;
		static constexpr inline float special_carbine_rifle_spread = 3.0f;
		static constexpr inline float bullpup_rifle_spread = 3.5f;
		static constexpr inline float compact_rifle_spread = 3.5f;
		static constexpr inline float military_rifle_spread = 2.5f;
		static constexpr inline float micro_smg_spread = 4.0f;
		static constexpr inline float machine_pistol_spread = 2.5f;
		static constexpr inline float mini_smg_spread = 3.5f;
		static constexpr inline float smg_spread = 3.5f;
		static constexpr inline float assault_smg_spread = 3.0f;
		static constexpr inline float combat_pdw_spread = 3.0f;
		static constexpr inline float mg_spread = 5.5f;
		static constexpr inline float combat_mg_spread = 5.0f;
		static constexpr inline float thompson_spread = 5.0f;
		static constexpr inline float ray_carbine_spread = 5.0f;
		static constexpr inline float ap_pistol_spread = 3.0f;
		static constexpr inline float revolver_pistol_spread = 0.200000003f;
	} weapon_spread;

	static class weapon_recoil_attributes
	{
	public:
		static constexpr inline float sniper = 0.2800000012f;
		static constexpr inline float shotgun = 1.75f;
		static constexpr inline float rifle = 0.3330000043f;
		static constexpr inline float smg = 0.3330000043f;
		static constexpr inline float mg = 0.8000000119f;
	} weapon_recoil;
}