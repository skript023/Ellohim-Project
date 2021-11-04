#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class player_information
	{
	public:
		static void render_player_info(const char* tab_name);
		static void render_player_event(const char* tab_name);
		static void render_player_business_info(const char* tab_name);
	};
}