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
#include "gui/game_tabbar/player_list.h"
#include "gui/helper_function.hpp"
#include "gui/game_tabbar/player_menu.h"
#include "gui/window/game_window.hpp"

    // auto vehicle = *(std::uintptr_t*)(local_ped + 0xD28);
    // auto offset2 = *(std::uintptr_t*)(vehicle + 0x8A8);
    // auto& offset3 = *(float*)(offset2 + 0x4C);
    // offset3 = 12.f;

namespace big::features
{	
	uint64_t OriginalRID = *g_pointers->m_player_rid;
	bool FirstLoad = true;

	
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
        int JoinStatus = *script_global(2689156).at(PLAYER::PLAYER_ID(),g_global.radar_size).as<int*>();
		auto CheckScriptTransition = script_helper::is_script_active(RAGE_JOAAT("fm_maintain_transition_players"));
		auto MainTransition = script_helper::is_script_active(RAGE_JOAAT("maintransition"));
		auto freemode = script_helper::is_script_active(RAGE_JOAAT("freemode"));
        if (CheckScriptTransition || MainTransition && JoinStatus == 10 || JoinStatus == 0 && !freemode)
		{
			return  true;
		} 
        return false;
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
	
	void chrono_loop(std::chrono::high_resolution_clock::duration delay)
	{
		static std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
		if ((std::chrono::high_resolution_clock::now() - start).count() >= delay.count())
		{
			if (systems::is_script_active(RAGE_JOAAT("fm_mission_controller")) && g_heist_option->all_take_heist)
			{
				casino_heist::all_heist_take(g_variable->casino_take);
			}
			player::player_health_regeneration(g_settings.options["Fast Regen"]);
			controller::TimeSpam(g_misc_option->time_spam);
			systems::auto_click(g_player_option.auto_click);
			start = std::chrono::high_resolution_clock::now();
		}
	}

	void HotkeyAttach()
	{
		if (GetAsyncKeyState(g_settings.options["Teleport Waypoint"].get<int>()) & 0x8000)
		{
			teleport::teleport_to_marker(PLAYER::PLAYER_ID());
		}
		if (GetAsyncKeyState(g_settings.options["Teleport Objective"].get<int>()) & 0x8000)
		{
			teleport::teleport_to_objective(PLAYER::PLAYER_ID());
		}
		if (GetAsyncKeyState(g_settings.options["Clear Wanted Level"].get<int>()) & 0x8000)
		{
			rage_helper::execute_as_script(RAGE_JOAAT("shop_controller"), [] {
				PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
			});
		}
		if (GetAsyncKeyState(VK_F4) & 0x8000)
		{
			memset(&g_player_option.auto_click, false, 1);
			LOG(INFO) << g_player_option.auto_click;
		}
	}
	
	void run_tick()
	{
		g_local.Transition = TransitionCheck() && *g_pointers->m_is_session_started;
		g_local.is_male = ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) == RAGE_JOAAT("mp_m_freemode_01");
		g_local.transition = TransitionCheck() && *g_pointers->m_is_session_started;
		HotkeyAttach();
		controller::variable_attach();
		if (!systems::is_script_active(RAGE_JOAAT("fm_mission_controller")))
		{
			g_heist_option->all_take_heist = false;
		}
		chrono_loop(200ms);
		player::set_player_waterproof(g_local.player, g_player_option.waterproof);
		player::self_noclip(g_player_option.no_clip);
		player::ghost_organization(g_player_option.ghost_organizations);
		player::reveal_player(g_player_option.reveal_players);
		player::blind_cops(g_player_option.blinds_cops);
		player::ultra_run(g_player_option.ultra_run_bool);
		player::never_wanted(g_settings.options["Never Wanted"]);
		player::mission_lives(g_player_option.all_mission_lives);
		player::set_player_seatbelt(g_settings.options["Seatbelt"]);
		player::set_player_invincible(PLAYER::PLAYER_ID(), g_settings.options["Player Godmode"]);
		player::give_all_heal(g_player_option.send_heal);
		player::auto_heal(g_settings.options["Auto Heal"]);
		player::set_player_no_collision(g_player_option.pass_through_wall);
		player::no_idle_kick(g_settings.options["No Idle Kick"]);
		player::set_player_infinite_oxygen(PLAYER::PLAYER_ID(), g_player_option.is_infinite_oxygen);
		
		weapon_helper::weapon_blackhole();

		remote_event::revenge_kick(g_remote_option->revenge_event);
		remote_event::remote_blind_cops(g_remote_option->bribe_authority);
		remote_event::remote_off_the_radar(g_remote_option->remote_off_the_radars);

		vehicle_helper::vehicle_blackhole();

		controller::faster_time_scale(g_misc_option->time_scale);
		
		ai::explode_enemies(g_npc_option->explode_ped);
		ai::kill_enemies(g_npc_option->kill_ped);
		
		casino_heist::AutoHeistCut(g_heist_option->auto_heist_cut);
		casino_heist::HeistCrewCutToZero(g_heist_option->casino_heist_crew);
		casino_heist::RemoveCasinoCrew(g_heist_option->casino_heist_remove_crew);
		
		//InfiniteAmmo(g_settings.options["Infinite Ammo"]);
		
		blackjack::AutoPlay(g_blackjack_option->blackjack_rig);
		blackjack::BlackJack(g_blackjack_option->blackjack_rig);
		casino_slot::RigSlotMachine(g_casino_option->casino_rig);
		casino_slot::AlwaysJackpot(g_casino_option->casino_rig);
		casino_slot::AutoPlay(g_casino_option->casino_rig);


		*script_global(g_global.lester_cut).as<int*>() = g_heist_option->remove_lester_cut ? 0 : 5;

		spoofer::player_level(g_spoofer_option->level_spoofer, g_spoofer_option->spoofed_level);
		spoofer::player_money(g_spoofer_option->money_spoofer, g_spoofer_option->spoofed_money);
		cayo_perico::set_heat_to_zero(g_heist_option->zero_heat);

		if (g_spoofer_option->rid != 0)
		{
			spoofer::player_scid(game_variable::player_rid_list[g_spoofer_option->rid]);
		}

		if (g_gui.m_opened) 
		{
			if ((network::network_get_num_connected_player() != g_misc_option->player_names.size()) && *g_pointers->m_is_session_started)
			{
				g_misc_option->player_names.clear();
				for (int i = 0; i < MAX_PLAYERS; ++i)
				{
					if (auto net_player = rage_helper::get_net_player(i))
					{
						auto cstr_name = net_player->get_name();
						std::string name = cstr_name;
						auto is_in_interior = INTERIOR::GET_INTERIOR_FROM_ENTITY(player::get_player_ped(i)) != 0;
						transform(name.begin(), name.end(), name.begin(), ::tolower);
						g_misc_option->player_names[name] = { cstr_name, i, is_in_interior };
					}
				}
			}
			if (!*g_pointers->m_is_session_started)
			{
				if (g_misc_option->player_names.size() >= 1)
					g_misc_option->player_names.clear();

				auto cstr_name = player::get_player_name(g_local.player);
				std::string name = cstr_name;
				auto is_in_interior = INTERIOR::GET_INTERIOR_FROM_ENTITY(player::get_player_ped(g_local.ped)) != 0;
				g_misc_option->player_names[cstr_name] = { cstr_name, g_local.player, is_in_interior };
			}

			if (*g_pointers->m_is_session_started)
				if (g_vehicle_option->personal_vehicle_list.empty() || vehicle_helper::get_max_slots() != g_vehicle_option->personal_vehicle_list.size())
					for (int i = 0; i <= vehicle_helper::get_max_slots(); ++i)
						g_vehicle_option->personal_vehicle_list[vehicle_helper::get_personal_vehicle_hash_key(i)] = i;
		}
	}

	void script_func()
	{
		while (true)
		{
			TRY_CLAUSE
			{
				if (game_window::create_session(g_game_window->login_status))
					run_tick();
			}
			EXCEPT_CLAUSE
			script::get_current()->yield();
		}
	}
}
