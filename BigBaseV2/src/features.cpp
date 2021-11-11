#include "common.hpp"
#include "features.hpp"
#include "logger.hpp"
#include "natives.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include "gta_util.hpp"
#include "script_local.hpp"
#include "hooking.hpp"
#include "gui.hpp"
#include "gui/player_list.h"
#include "gui/helper_function.hpp"
#include <gui\player_menu.h>

    // auto vehicle = *(std::uintptr_t*)(local_ped + 0xD28);
    // auto offset2 = *(std::uintptr_t*)(vehicle + 0x8A8);
    // auto& offset3 = *(float*)(offset2 + 0x4C);
    // offset3 = 12.f;

namespace big::features
{	
	bool ExplosiveAmmoBool = false;
	bool FlamingAmmo = false;
	bool SuperJump = false;
	bool ExplosiveFist = false;
	bool AutomaticHeistCut = false;
	bool CrewHeistBool = false;
	bool PlayerSeatBelt = false;
	bool PlayerTembus = false;
	bool AllMissionLLivesToggle = false;
	bool RemoveCrew = false;
	bool send_heal = false;
	bool AllTakeHeist = false;
	const char* PlayerNames[32];
	bool test_frame = false;
	bool remoteOTR = false;
	bool LevelSpoofer = false;
	bool HeadshotPed = false;
	bool RapidFireBool = false;
	bool KillNPCBool = false;
	bool NoCollisionGunBool = false;
	bool MoneyGunBool = false;
	bool MaxLvSpoof = false;
	bool NormalLevelSpoof = false;
	bool InfiniteBoostOnKey = false;
	bool HornBoost = false;
	bool TimeScale = false;
	bool TimeSpammer = false;
	bool Revenge = false;
	bool BlackjackRig = false;
	bool RigSlotBool = false;
	bool InfiniteVehicleAmmo = false;
	bool UltraRun = false;
	bool AutoHeadShot = false;
	bool RemoteBribeToggle = false;
	bool Ghost = false;
	bool RevealPlayer = false;
	bool BribeAuthority = false;
	bool OTR = false;
	int LevelForSpoof = 0;
	int fake_money = 0;
	bool money_spoofer = false;
	bool RevengeKick = false;
	bool RemoveObjects = false;
	static bool FirstLoad = true;
	bool zero_heat = false;
	uint64_t OriginalRID = *g_pointers->m_player_rid;

	
	int local_player_id()
	{
		return *script_global(2441237).as<int*>();
	}

	int network_time()
	{
		return *script_global(1312603).at(11).as<int*>();
	}

	int LevelData(int Level)
	{
		auto GetExpLevel = *script_global(293362).at(1, Level).as<int*>();
		return GetExpLevel;
	}

	
	bool TransitionCheck()
	{
        int JoinStatus = *script_global(2426865).at(PLAYER::PLAYER_ID(),443).as<int*>();
		auto CheckScriptTransition = script_helper::is_script_active(RAGE_JOAAT("fm_maintain_transition_players"));
		auto MainTransition = script_helper::is_script_active(RAGE_JOAAT("maintransition"));
		auto freemode = script_helper::is_script_active(RAGE_JOAAT("freemode"));
        if (CheckScriptTransition || MainTransition && JoinStatus == 10 || JoinStatus == 0 && !freemode)
		{
			return  true;
		} 
        return false;
    }

	bool IsPlayerInsideVehicle()
	{
		return Memory::get_value<bool>(g_ptr.WorldPTR, {0x8, 0xE52}); //*(bool*)((DWORD64)WorldPTR->m_local_ped + 0xE52);
	}

	Vector3 GetCoordsInfrontOfCam(float distance)
	{
		Vector3 GameplayCamRot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3 GameplayCamCoord = CAM::GET_GAMEPLAY_CAM_COORD();

		float tan = GameplayCamRot.y * distance;
		float xPlane = (GameplayCamRot.z * tan) + GameplayCamCoord.y;
		float yPlane = (GameplayCamRot.z * tan) + GameplayCamCoord.y;
		float zPlane = (GameplayCamRot.y * distance) + GameplayCamCoord.z;

		return Vector3(xPlane, yPlane, zPlane);
	}
	
	void WhenMenuLoaded()
	{
		if (FirstLoad)
		{
			HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("~bold~~y~Ellohim ~g~Menu Connected With The Game~w~");
			HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", FALSE, 0, "~bold~~y~Ellohim", "~y~~a~Private Mod Menu");
			HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(true, true);
			FirstLoad = false;
		}
	}

	struct nearbyEnts {
		int size;//still 32 bit integer
		Entity entities[100];
	};

	void Unusable(int player)
	{
		nearbyEnts arr;
		arr.size = 100;
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		int size = PED::GET_PED_NEARBY_PEDS(ped, (int*)&arr, ped);
		for (int i = 0; i < size; i++)
		{
			//LOG(INFO) << "You Got The Control";
			auto pos = ENTITY::GET_ENTITY_COORDS(arr.entities[i], TRUE);
			*(PWORD)g_pointers->m_add_owned_explosion_bypass_1 = 0xE990;
			*(PWORD)g_pointers->m_add_owned_explosion_bypass_2 = 0x9090;
			FIRE::ADD_OWNED_EXPLOSION(g_selected.ped, pos.x, pos.y, pos.z, EXPLOSION_TANKER, 1000.0f, FALSE, TRUE, 0.0f);
			*(PWORD)g_pointers->m_add_owned_explosion_bypass_1 = 0x850F;
			*(PWORD)g_pointers->m_add_owned_explosion_bypass_2 = 0x0F74;
		}
	}
	
	void LogginPlayerData()
	{

	}
	
	/*
	*script_global(2515430).at(3).as<float*>() = gun_coords.x;
				*script_global(2515430).at(4).as<float*>() = gun_coords.y;
				*script_global(2515430).at(5).as<float*>() = gun_coords.z;
				*script_global(2515430).at(1).as<float*>() = 10000;
				int iparam = *script_global(2515430).as<int*>();
				if (!iparam)
					return;

				if (iparam != 0)
				{
					iparam = 0;
					*script_global(2515430).as<int*>() = iparam;
				}

				*script_global(4264051).at(iparam, 85).at(66).at(2).as<int*>() = 2;
				*script_global(2515436).as<int*>() = 1;
	*/
	
	void HotkeyAttach()
	{
		if (GetAsyncKeyState(g_settings.options["Teleport Waypoint"].get<int>()) & 0x8000)
		{
			teleport::teleport_to_marker();
		}
		if (GetAsyncKeyState(g_settings.options["Teleport Objective"].get<int>()) & 0x8000)
		{
			teleport::teleport_to_objective();
		}
		if (GetAsyncKeyState(g_settings.options["Clear Wanted Level"].get<int>()) & 0x8000)
		{
			rage_helper::execute_as_script(RAGE_JOAAT("shop_controller"), [] {
				PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
			});
		}
	}
	//HW_PROFILE_INFO hwProfileInfo;
	//GetCurrentHwProfile(&hwProfileInfo);
	//hwProfileInfo.szHwProfileGuid
	void run_tick()
	{
		static ULONGLONG tick_1 = 0;
		static ULONGLONG tick_2 = 0;
		ULONGLONG now = GetTickCount64();
		g_local.Transition = TransitionCheck() && *g_pointers->m_is_session_started;
		g_local.is_male = ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == RAGE_JOAAT("mp_m_freemode_01");
		g_local.transition = TransitionCheck() && *g_pointers->m_is_session_started;
		if (g_fitur.testing)
		{
			VEHICLE::SET_VEHICLE_FIXED(player::get_player_vehicle(PLAYER::PLAYER_PED_ID(), false));
		}
		HotkeyAttach();
		controller::variable_attach();
		if (!systems::is_script_active(RAGE_JOAAT("fm_mission_controller")))
		{
			features::AllTakeHeist = false;
		}

		tick_2++;
		if (tick_2 == 50)
		{
			if (systems::is_script_active(RAGE_JOAAT("fm_mission_controller")) && features::AllTakeHeist)
			{
				casino_heist::all_heist_take(player_list::CasinoTake);
			}
			player::PlayerHealthRegen(g_settings.options["Fast Regen"]);
			controller::TimeSpam(features::TimeSpammer);
			tick_2 = 0;
		}
		tick_1++;
		if (tick_1 == 10)
		{
			
			tick_1 = 0;
		}

		WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), g_settings.options["Infinite Clip"]);
		
		//OffTheRadar(OTR);
		player::set_player_waterproof(g_local.player, g_fitur.waterproof);
		player::set_player_no_clip(g_self.no_clip);
		player::GhostOrganization(Ghost);
		player::RevealRadar(RevealPlayer);
		player::BlindCops(BribeAuthority);
		player::UltraRun(UltraRun);
		player::RunSpeed(g_self.RunSpeed);
		player::SwimSpeed(g_self.SwimSpeed);
		player::NeverWanted(g_settings.options["Never Wanted"]);
		player::AllMissionLives(AllMissionLLivesToggle);
		player::SetPlayerSeatBelt(g_settings.options["Seatbelt"]);
		player::set_player_invincible(PLAYER::PLAYER_ID(), g_settings.options["Player Godmode"]);
		player::GiveHealAll(features::send_heal);
		player::AutoHeal(g_settings.options["Auto Heal"]);
		player::SetPlayerNoCollision(PlayerTembus);
		player::no_idle_kick(g_settings.options["No Idle Kick"]);
		
		weapon_helper::teleport_gun(g_fitur.teleport_gun);
		weapon_helper::no_spread(g_fitur.spread_on);
		weapon_helper::no_recoil(g_fitur.recoil_on);
		weapon_helper::rapid_fire(RapidFireBool);
		weapon_helper::HeadShotNPC(features::AutoHeadShot);
		weapon_helper::Revenge(rage::joaat(var::revenge_list[g_item.weapon_hash]), g_item.weapon_hash != 0);
		
		weapon_helper::infinite_ammo(g_settings.options["Infinite Ammo"]);
		weapon_helper::explosive_ammo(g_fitur.explosive_weapon, player::get_player_ped(g_selected.player));
		weapon_helper::MoneyGun(MoneyGunBool);
		weapon_helper::RemoveObjectsLoop(RemoveObjects);
		weapon_helper::CollisionGun(NoCollisionGunBool);

		weapon_helper::set_explosive_ammo_this_frame(PLAYER::PLAYER_ID(), features::ExplosiveAmmoBool);
		weapon_helper::set_fire_ammo_this_frame(PLAYER::PLAYER_ID(), features::FlamingAmmo);
		weapon_helper::set_super_jump_this_frame(PLAYER::PLAYER_ID(), features::SuperJump);
		weapon_helper::set_explosive_melee_this_frame(PLAYER::PLAYER_ID(), features::ExplosiveFist);
		

		remote_event::revenge_kick(RevengeKick);
		remote_event::RemoteBribe(RemoteBribeToggle);
		remote_event::RemoteOffRadar(big::features::remoteOTR);

		vehicle_helper::AntiGriefVehicle(g_settings.options["PV Revenge"]);
		vehicle_helper::InfiniteVehicleAmmo(InfiniteVehicleAmmo);
		vehicle_helper::InfiniteBoost(InfiniteBoostOnKey);
		vehicle_helper::vehicle_godmode(g_settings.options["Vehicle Godmode"]);
		vehicle_helper::HornBoostFunc(HornBoost);

		controller::FasterTimeScale(features::TimeScale);
		
		ai::explode_enemies(HeadshotPed);
		ai::kill_enemies(KillNPCBool);
		
		casino_heist::AutoHeistCut(big::features::AutomaticHeistCut);
		casino_heist::HeistCrewCutToZero(big::features::CrewHeistBool);
		casino_heist::RemoveCasinoCrew(RemoveCrew);
		
		//InfiniteAmmo(g_settings.options["Infinite Ammo"]);
		
		blackjack::AutoPlay(BlackjackRig);
		blackjack::BlackJack(BlackjackRig);
		casino_slot::RigSlotMachine(RigSlotBool);
		casino_slot::AlwaysJackpot(RigSlotBool);
		casino_slot::AutoPlay(RigSlotBool);

		
		WhenMenuLoaded();

		*script_global(g_global.lester_cut).as<int*>() = g_fitur.remove_lester_cut ? 0 : 5;

		spoofer::player_level(LevelSpoofer, LevelForSpoof);
		spoofer::player_money(money_spoofer, fake_money);
		cayo_perico::set_heat_to_zero(features::zero_heat);

		if (g_item.rid != 0)
		{
			spoofer::player_scid(var::DataPlayerRID[g_item.rid]);
		}

		if (g_gui.m_opened) 
		{
			for (int i = 0; i < 32; ++i) 
			{
				PlayerNames[i] = PLAYER::GET_PLAYER_NAME(i);//player::get_player_name(i);
			}
		}
	}

	void script_func()
	{
		while (true)
		{
			TRY_CLAUSE
			{
				run_tick();
			}
			EXCEPT_CLAUSE
			script::get_current()->yield();
		}
	}
}
