#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class player_list
	{
	public:
		static void render_player_list(const char* tab_name);

	public:
		static int SpoofLevel;
		static bool LevelSpoofer;
		static bool SetPedInCar;
		static int CasinoTake;
		static char NameSpoofer[20];

		static bool AsBodyGuard;
		static bool ApplyForce;
		static bool IsVisible;
		static bool AggressivePed;
		static const int DISTANCE_SPAWN;
		static int fam;
		static const char* StringValue;
		static int SelectedVehicle;
	};

}
