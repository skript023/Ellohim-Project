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
		static inline std::map<std::string, int> personal_vehicle_order;
		static inline const char* find_vehicle_name(Hash hash)
		{
			if (hash == 0)
			{
				return "Not Found";
			}
			for (auto vehicle : game_variable::vehicle_hash_list)
			{
				if (hash == rage::joaat(vehicle))
				{
					return vehicle;
				}
			}
			return "Not Found";
		}

		static inline const char* get_personal_vehicle(int vehicle_index)
		{
			auto hash = *script_global(g_global.garage).at(vehicle_index, 142).at(66).as<uint32_t*>();
			return find_vehicle_name(hash);
		}

		static inline int get_max_slots()
		{
			return *script_global(g_global.garage).as<int*>();
		}

		static inline char nama_mobil[32];
		static inline int total_ped = 0;
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