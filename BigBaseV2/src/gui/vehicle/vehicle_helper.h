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
		static void set_vehicle_collision(bool activation);
		static void set_vehicle_turn_light(Vehicle vehicle, int TurnLight);
		static void set_vehicle_engine_on(Vehicle vehicle, bool EngineStatus);
		static bool get_vehicle_engine(Vehicle vehicle);
		static Vehicle get_personal_vehicle(Player player);
		static std::string get_vehicle_name_from_hash(Hash vehicle_hash);
		static void attach_vehicle(const char* vehicle_name, Player player);
		static void InfiniteBoost(bool Activation);
		static void HornBoostFunc(bool Activation);
		static void vehicle_godmode(bool Activation);
		static void add_clan_logo_to_vehicle(Vehicle vehicle, Ped ped);
		static void set_mp_parameters_for_vehicle(Vehicle vehicle);
		static Vehicle create_vehicle(Hash modelHash, float x, float y, float z, float heading);
		static void vehicle(const char* name, Entity entity);
		static void SpawnVehicle(const char* name, bool pegasus, Player player_target);
		static void swam(const char* name, Entity entity);
		static void RepairVehicle(Ped player_ped);
		static void InfiniteVehicleAmmo(bool Activation);
		static void SetVehicleFlag(int Flag, uint32_t flagBit);
		static void ClearVehicleFlag(int Flag, uint32_t FlagBit);
		static void RemoveInsuranceClaims();
		static void AntiGriefVehicle(bool Activation);
	};

	static class vehicle_helper_variable
	{
	public:
		static inline Vehicle vehicle{};
	}g_vehicle_variable;
}