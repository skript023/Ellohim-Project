#pragma once
#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class game_window
	{
	public:
		static bool check_license(uint64_t license);
		static void render_base_window(const char* window_name);

	public:
		static inline char temp_username[255];
		static inline char temp_password[255];
		static inline char username[255] = "None";
		static inline char password[255] = "None";
		static inline HW_PROFILE_INFO profile_info;
		static inline bool logger{};
	};

	inline static game_window* g_game_window{};
}