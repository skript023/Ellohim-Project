#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class teleport
	{
	public:
		static Vector3 get_mission_blip();
		static Vector3 get_blip_marker();
		static bool load_ground(Vector3& coords);

		static void teleport_to_coords(Entity e, Vector3 coords);
		static void teleport_to_marker(Player player);
		static void teleport_to_objective(Player player);
		static void teleport_to_player(Player source_player, Player target_player);
		static void teleport_to_player_vehicle(Player player);
	private:
		static inline bool first_attempt{ false };
	};

	class blip
	{
	public:
		static Vector3 get_blip_coords(int icon_id, int icon_colour = 0);
		//static Vector3 get_blip_colour_coords(int blip_colour);
	};
}