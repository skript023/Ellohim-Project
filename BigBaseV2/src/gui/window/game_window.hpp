#pragma once
#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class game_window
	{
	public:

		static void render_base_window(const char* window_name);

	public:
		char temp_username[255];
		char temp_password[255];
		char username[255] = "None";
		char password[255] = "None";
		HW_PROFILE_INFO profile_info;
	};

	inline static game_window g_game_window;
}