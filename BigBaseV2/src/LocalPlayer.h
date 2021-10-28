#pragma once
#include "natives.hpp"
#include "gta\player.hpp"

namespace big
{
	static class local_player_info_class
	{
	public:
		static inline Player player{};
		static inline Ped ped{};
	} g_local;
};