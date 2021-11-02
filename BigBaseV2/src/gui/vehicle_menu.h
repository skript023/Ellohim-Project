#pragma once
#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class vehicle_tab
	{
	public:
		static void render_vehicle_tab(const char* tab_name);
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