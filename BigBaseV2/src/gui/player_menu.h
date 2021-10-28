#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class player_menu
	{
	public:
		static void render_player_tab();
	};

	static class self_option
	{
	public:
		static inline float RunSpeed = 1.0;
		static inline float SwimSpeed = 1.0;
		static inline float SneakSpeed = 1.0;
		static inline bool ThermalVision = false;
		static inline bool Nightvision = false;
		static inline bool no_clip = false;
	} g_self;

	static class character_costume
	{
	public:
		static inline int hair{};
		static inline int hat{};
		static inline int mask{};
		static inline int top{};
		static inline int top2{};
		static inline int legs{};
		static inline int shoes{};
		static inline int gloves{};
		static inline int glasses{};
		static inline int special{};
		static inline int special_1{};
		static inline int special_2{};
		static inline int hair_colour{};
		static inline int hat_colour{};
		static inline int mask_colour{};
		static inline int glasses_colour{};
		static inline int top_colour{};
		static inline int top2_colour{};
		static inline int legs_colour{};
		static inline int gloves_colour{};
		static inline int shoes_colour{};
		static inline int special_colour{};
		static inline int special_1_colour{};
		static inline int special_2_colour{};
		static inline int ears{};
		static inline int ears_colour{};
		static inline int bracelet{};
		static inline int bracelet_colour{};
		static inline int badge{};
		static inline int badge_colour{};
	} char_style;
}