#pragma once
#include "common.hpp"

namespace big::features
{
	extern bool ExplosiveAmmoBool;
	extern bool FlamingAmmo;
	extern bool SuperJump;
	extern bool ExplosiveFist;
	extern bool CrewHeistBool;
	extern bool AutomaticHeistCut;
	extern bool PlayerTembus;
	extern bool AllMissionLLivesToggle;
	extern bool RemoveCrew;
	extern bool send_heal;
	extern bool AllTakeHeist;
	extern bool test_frame;
	extern bool RemoveObjects;
	extern bool remoteOTR;
	extern bool LevelSpoofer;
	extern bool HeadshotPed;
	extern bool RapidFireBool;
	extern bool KillNPCBool;
	extern bool NoCollisionGunBool;
	extern bool MoneyGunBool;
	extern bool MaxLvSpoof;
	extern bool NormalLevelSpoof;
	extern bool InfiniteBoostOnKey;
	extern bool HornBoost;
	extern uint64_t OriginalRID;
	extern int LevelForSpoof;
	extern bool TimeScale;
	extern bool TimeSpammer;
	extern bool Revenge;
	extern bool BlackjackRig;
	extern bool RigSlotBool;
	extern bool InfiniteVehicleAmmo;
	extern bool UltraRun;
	extern bool AutoHeadShot;
	extern bool RemoteBribeToggle;
	extern bool Ghost;
	extern bool RevealPlayer;
	extern bool BribeAuthority;
	extern bool OTR;
	extern int fake_money;
	extern bool money_spoofer;
	extern bool RevengeKick;
	extern bool zero_heat;
	extern const char* PlayerNames[32];
	extern int LevelData(int Level);

	extern bool TransitionCheck();

	extern void run_tick();

	extern void script_func();
}
