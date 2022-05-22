#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class systems
	{
	public:
		static double milisecond_to_day(int64_t Milisecond);
		static bool is_number_8_bit(uint8_t number);
		static bool is_number_16_bit(uint16_t number);
		static bool is_number_32_bit(uint32_t number);
		static bool is_number_64_bit(uint64_t number);
		static bool is_script_active(rage::joaat_t Hash);
		static bool wait_script(rage::joaat_t script_hash);
		static void logger(const char* window_name);
		static void auto_click(bool activate);
		static bool is_model_valid(rage::netSyncTree* netSyncTree, rage::netObject* netObject);
		static std::string char_to_string(char* a, int size);
		static int hotkey(char ch);
		static float degree_to_radian(float degs);
		static std::string character_filter(const char* str);
		static bool is_2d_vector_equal(rage::vector2 a, rage::vector2 b, float epsilon = FLT_EPSILON);
		static bool is_3d_vector_equal(Vector3 a, Vector3 b, float epsilon = FLT_EPSILON);
		static bool is_3d_vector_equal(rage::vector3 a, rage::vector3 b, float epsilon = FLT_EPSILON);
		static bool is_3d_vector_zero(Vector3 a, float epsilon = FLT_EPSILON);
		static bool is_3d_vector_zero(rage::vector3 a, float epsilon = FLT_EPSILON);
		static bool is_not_number(const char* str);
		static bool has_special_character(const char* str);
		static bool is_float_equal(float a, float b, float epsilon = FLT_EPSILON);
		static void set_weather_type(const char* WeatherType);
		static Player get_player_id_from_name(const char* player_name);
		static Vector3 to_scr_vector(rage::vector3 vector);
		static rage::vector3 to_rage_vector(Vector3 vector);
		static int float_to_int(const float& num);
		static float int_to_float(int x);
		static float round(float var);
		static std::string title_case(const std::string str);
		static inline bool cstrcmp(const char* s1, const char* s2)
		{
			while (*s1 && (*s1 == *s2))
				s1++, s2++;
			if (*(const unsigned char*)s1 - *(const unsigned char*)s2 == 0)
				return true;
			else
				return false;
		}
		
	public:
		class money_formatter
		{
		public:
			money_formatter(const char* const locale_name = "US") :
				loc(locale_name),
				output(std::use_facet<std::money_put<char> >(loc)),
				iterator(os)
			{
				os.imbue(loc);
				os.setf(std::ios_base::showbase);
			}

			std::string as_string(float value)
			{
				os.str("");  // clear string
				output.put(iterator, false, os, ' ', value);
				return os.str();
			}

			std::string as_string(double value)
			{
				os.str("");  // clear string
				output.put(iterator, false, os, ' ', value * 100.0);
				return os.str();
			}

		private:
			std::locale loc;
			const std::money_put<char>& output;
			std::ostringstream os;
			std::ostreambuf_iterator<char, std::char_traits<char> > iterator;
		};
	};
	class fire
	{
	public:
		static void add_owned_explosion(Ped ped, Vector3 pos, int explosionType, float damageScale, bool isAudible, bool isInvinsible, float ShakeCam);
	};
	class cam
	{
	public:
		static void set_cam_blurry();
	};
}