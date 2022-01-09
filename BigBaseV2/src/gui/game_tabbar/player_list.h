#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class player_list
	{
	public:
		static void render_player_list(const char* tab_name);

	private:
		static inline char players_name[32];
	};

}
