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
		static int* bullet_batch(Player player);
		static float* bullet_batch_spread(Player player);
		static void no_spread(bool activation);
		static void no_recoil(bool activation);
		static void burst_weapon_ammo(bool activation);
		static bool is_model_shotgun(Hash hash);

		static void object_guns(bool Activation);

		static void ghost_guns(bool Activation);

		static void removal_gun(bool activation);

		static void rapid_fire(bool toggle);
		static void infinite_ammo(bool activation);
		
		static void revenge(Hash Weapon, bool Activation);

		static void headshot_all_npc(bool Activation);

		static void explosive_ammo(bool Activation, Ped Target);

		static Vector3 get_last_impact_coords(Ped Ped);

		static bool get_last_impact_coords(Ped Ped, Vector3* coords);

		static bool get_last_aimed_coords(Ped ped, Vector3* coords);

		static void set_fire_ammo_this_frame(Player player, bool activation);
		static void set_explosive_ammo_this_frame(Player player, bool activation);
		static void set_super_jump_this_frame(Player player, bool activation);
		static void set_explosive_melee_this_frame(Player player, bool activation);

	public:
		static inline bool explosives_ammo{};
		static inline bool fire_ammo{};
		static inline bool super_jump{};
		static inline bool explosive_fist{};
		static inline bool delete_gun{};
		static inline bool rapid_shoot{};
		static inline bool auto_headshot{};
		static inline bool object_gun{};
		static inline bool ghost_gun{};
		static inline bool teleport_gun_bool{};
		static inline bool spread_on{};
		static inline bool recoil_on{};
		static inline int weapon_hash{};
		static inline bool explosive_weapon{};
		static inline bool burst_weapon{};
	public:
		static void weapon_blackhole();
	private:
		static inline Vector3 add_vector(Vector3 vector, Vector3 vector2)
		{
			vector.x += vector2.x;
			vector.y += vector2.y;
			vector.z += vector2.z;
			return vector;
		}

		static inline double degree_to_radiant(double n)
		{
			return n * 0.017453292519943295;
		}

		static inline Vector3 rotation_to_direction(Vector3 rot)
		{
			double num = degree_to_radiant(rot.z);
			double num2 = degree_to_radiant(rot.x);
			double val = cos(num2);
			double num3 = abs(val);
			rot.x = (float)(-(float)sin(num) * num3);
			rot.y = (float)(cos(num) * num3);
			rot.z = (float)sin(num2);
			return rot;
		}

		static inline Vector3 multiply_vector(Vector3 vector, float inc)
		{
			vector.x *= inc;
			vector.y *= inc;
			vector.z *= inc;
			return vector;
		}
	};

	inline static weapon_helper g_weapon_option{};
}