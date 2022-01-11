#pragma once

#include "common.hpp"
#include "natives.hpp"
#include "gta\VehicleValues.h"
#include "pointers.hpp"

namespace big
{
	class vehicle_helper
	{
	public:
		static void allow_unrelease_vehicle(bool activate);
		static void set_vehicle_collision(Player player, bool activation);
		static void set_vehicle_turn_light(Vehicle vehicle, int TurnLight);
		static void set_vehicle_engine_on(Vehicle vehicle, bool EngineStatus);
		static bool get_vehicle_engine(Vehicle vehicle);
		static Vehicle get_personal_vehicle(Player player);
		static std::string get_vehicle_name_from_hash(Hash vehicle_hash);
		static void infinite_boosts(bool Activation);
		static void attach_vehicle(const char* vehicle_name, Player player);

		static void horn_boosts(bool Activation);

		static void vehicle_godmode(bool Activation);
		static void anti_grief_vehicle(bool Activation);
		static bool check_vehicle_insurance(int vehicle_index);
		static int get_current_personal_vehicle_index();
		static void claim_insurance_for_all_vehicle();
		static void claim_insurance();
		static void set_vehicle_flag(int Flag, uint32_t flagBit);
		static void clear_vehicle_flag(int Flag, uint32_t flagBit);
		static void infinite_vehicle_ammo(bool Activation);
		static void repair_vehicle(Ped player_ped);
		static void add_clan_logo_to_vehicle(Vehicle vehicle, Ped ped);
		static void set_mp_parameters_for_vehicle(Vehicle vehicle);
		static Vehicle create_vehicle(Hash modelHash, float x, float y, float z, float heading);
		static void vehicle(const char* name, Entity entity);
		static void SpawnVehicle(const char* name, bool pegasus, Player player_target);
		static void swam(const char* name, Entity entity);
		
	public:
		static inline bool infinite_ammo{};
		static inline bool infinite_boost{};
		static inline bool horn_boost{};
		static inline int selected_vehicle{};
	};

	static class vehicle_helper_variable
	{
	public:
		static inline Vehicle vehicle{};
	}g_vehicle_variable;

	inline static vehicle_helper *g_vehicle_option{};
}