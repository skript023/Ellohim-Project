#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class scenario
	{
	public:
		static const char* const scenario_name[240];
		static void play_scenario(Ped ped, const char* scenario, bool PlayEnterAnim);
		static void play_animation(Ped ped, const char* anim_dictionary, const char* anim_name);
		static void Sexy(Ped ped);
		static void Sex(Ped ped);
		static void Stripper(Ped ped);
		static void Pole(Ped ped);
		static void Push(Ped ped);
		static void Sit(Ped ped);
		static void Celebrate(Ped ped);
		static void Electrocution(Ped ped);
		static void Suicide(Ped ped);
		static void Showering(Ped ped);
		static void Dog(Ped ped);
		static void meditation(Ped ped);
		static void SexTake(Ped ped);
		static void onfire(Ped ped);
		static void Musician(Ped ped);
		static void Welding(Ped ped);
		static void Lifting(Ped ped);
		static void Gardener(Ped ped);
		static void Binoculars(Ped ped);
		static void Bum(Ped ped);
		static void High(Ped ped);
		static void Smoke(Ped ped);
		static void Hammering(Ped ped);
		static void Maid(Ped ped);
		static void Paparazzi(Ped ped);
		static void Strip(Ped ped);
		static void Partying(Ped ped);
		static void Smoking(Ped ped);
		static void Stupor(Ped ped);
		static void Sumbathe(Ped ped);
		static void Tourist(Ped ped);
		static void Statue(Ped ped);
	};
}