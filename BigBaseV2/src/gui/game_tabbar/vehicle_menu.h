#pragma once
#include "common.hpp"
#include "natives.hpp"
#include "gui/helper_function.hpp"

namespace big
{
	class vehicle_tab
	{
	public:
		static void render_vehicle_tab(const char* tab_name);
	private:
		static inline const char* FindVehicleName(Hash hash)
		{
			if (!hash || hash == 0)
			{
				return "none";
			}
			for (auto vehicle : var::VechicleList)
			{
				if (hash == rage::joaat(vehicle))
				{
					return vehicle;
				}
			}
			return "none";
		}
		static inline const char* PersonalName[191];
		static inline void GetVehicleSlots()
		{
			int max_slots = *script_global(1323678).as<int*>();
			for (int i = 0; i <= max_slots; i++)
			{
				uint32_t hash = *script_global(1323678).at(i, 141).at(66).as<uint32_t*>();
				PersonalName[i] = FindVehicleName(hash);;
			}
		}

		static inline int selected_category = 0;
		static inline int SelectedVehicle = 0;
		static inline int SelectedPersonal{};
		static inline bool BoostFlag = false;
		static inline bool JumpFlag = false;
		static inline bool ParachuteFlag = false;
		static inline bool OppressorFlag = false;
	};

	static class vehicle_handling
	{
		public:
			static inline float acceleration{};
			static inline float f_acceleration{};
			static inline float traction_curve_min{};
			static inline float traction_curve_max{};
			static inline float top_speed{};
			static inline int selected_flag{};
			static inline bool Flag_1[30];
			static inline bool Flag_2[30];
			static inline bool Flag_3[30];
			static inline bool Flag_4[30];
			static inline bool Flag_5[30];
			static inline bool Flag_6[30];
			static inline bool Flag_7[30];
	} g_handling;
}