#include "common.hpp"
#include "logger.hpp"
#include "pointers.hpp"
#include "memory/all.hpp"

namespace big
{
	pointers::pointers()
	{
		memory::pattern_batch main_batch;

		main_batch.add("Game state", "48 85 C9 74 4B 83 3D", [this](memory::handle ptr)
		{
			m_game_state = ptr.add(7).rip().as<eGameState*>();//ptr.add(2).rip().as<eGameState*>();48 8B ? FF 10 83 E8 sub(9).rip()
		});

		main_batch.add("Is session started", "40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE", [this](memory::handle ptr)
		{
			m_is_session_started = ptr.add(3).rip().as<bool*>();
		});

		main_batch.add("Ped factory", "48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81", [this](memory::handle ptr)
		{
			m_ped_factory = ptr.add(3).rip().as<CPedFactory**>();
		});

		main_batch.add("Network player manager", "48 8B 0D ? ? ? ? 8A D3 48 8B 01 FF 50 ? 4C 8B 07 48 8B CF", [this](memory::handle ptr)
		{
			m_network_player_mgr = ptr.add(3).rip().as<CNetworkPlayerMgr**>();
		});

		main_batch.add("Native handlers", "48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A", [this](memory::handle ptr)
		{
			m_native_registration_table = ptr.add(3).rip().as<rage::scrNativeRegistrationTable*>();
			m_get_native_handler = ptr.add(12).rip().as<functions::get_native_handler_t>();
		});

		main_batch.add("Fix vectors", "83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA", [this](memory::handle ptr)
		{
			m_fix_vectors = ptr.as<functions::fix_vectors_t>();
		});

		main_batch.add("Script threads", "45 33 F6 8B E9 85 C9 B8", [this](memory::handle ptr)
		{
			m_script_threads = ptr.sub(4).rip().sub(8).as<decltype(m_script_threads)>();
			m_run_script_threads = ptr.sub(0x1F).as<functions::run_script_threads_t>();
		});

		main_batch.add("Script programs", "44 8B 0D ? ? ? ? 4C 8B 1D ? ? ? ? 48 8B 1D ? ? ? ? 41 83 F8 FF 74 3F 49 63 C0 42 0F B6 0C 18 81 E1", [this](memory::handle ptr)
		{
			m_script_program_table = ptr.add(17).rip().as<decltype(m_script_program_table)>();
		});

		main_batch.add("Script globals", "48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D", [this](memory::handle ptr)
		{
			m_script_globals = ptr.add(3).rip().as<std::int64_t**>();
		});

		main_batch.add("CGameScriptHandlerMgr", "48 8B 0D ? ? ? ? 4C 8B CE E8 ? ? ? ? 48 85 C0 74 05 40 32 FF", [this](memory::handle ptr)
		{
			m_script_handler_mgr = ptr.add(3).rip().as<CGameScriptHandlerMgr**>();
		});

		main_batch.add("Swapchain", "48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8", [this](memory::handle ptr)
		{
			m_swapchain = ptr.add(3).rip().as<IDXGISwapChain**>();
		});

		main_batch.add("Native Return Bypass", "FF E3", [this](memory::handle ptr)
		{
			m_nativeReturn = ptr.as<PVOID>();
		});

		main_batch.add("Blip List", "4C 8D 05 ? ? ? ? 0F B7 C1", [this](memory::handle ptr)
		{
			m_blip_ptr = ptr.add(3).rip().as<rage::BlipList*>();//*(rage::BlipList**)ptr.add(3).rip().as<PVOID>();
		});

		main_batch.add("Cutscene Manager", "48 8B 0D ? ? ? ? 48 8B 01 48 FF 60 28", [this](memory::handle ptr)
		{
			m_cutscene_mgr = ptr.add(3).rip().as<CutsceneManager**>();
		});

		main_batch.add("Friend Pointer", "48 03 0D ? ? ? ? E9 ? ? ? ? 48 8D 05", [this](memory::handle ptr)
		{
			m_friend_list = ptr.add(3).rip().as<FriendList**>();
		});

		main_batch.add("Total Friend", "3B 0D ? ? ? ? 73 13 48 63 C9", [this](memory::handle ptr)
		{
			m_total_friend = ptr.add(2).rip().as<int*>();
		});

		main_batch.add("Pointer To Entity", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B 15 ? ? ? ? 48 8B F9 48 83 C1 10 33 DB", [this](memory::handle ptr)
		{
			m_ptr_to_handle = ptr.as<functions::ptr_to_handle_t>();
		});

		main_batch.add("Entity To Pointer", "75 0D 41 8B 41", [this](memory::handle ptr)
		{
			m_handle_to_ptr = ptr.sub(27).as<functions::handle_to_ptr_t>();
		});

		main_batch.add("Get Player Pointer", "40 53 48 83 EC 20 33 DB 38 1D ? ? ? ? 74 1C 83 F9 1F 77 26", [this](memory::handle ptr)
		{
			m_player_ptr = ptr.as<functions::player_pointer>();//48 89 5C 24 ? 57 48 83 EC 20 33 DB 38 1D ? ? ? ? 74 26
		});

		main_batch.add("Get Player Name", "40 53 48 83 EC 20 80 3D ? ? ? ? ? 8B D9 74 22", [this](memory::handle ptr)
		{
			m_get_player_name = ptr.as<functions::get_player_name_t>();
		});

		main_batch.add("Replay Interface", "48 8D 0D ? ? ? ? 48 8B D7 E8 ? ? ? ? 48 8D 0D ? ? ? ? 8A D8 E8 ? ? ? ? 84 DB 75 13 48 8D 0D ? ? ? ?", [this](memory::handle ptr)
		{
			m_replay_interface = *(rage::CReplayInterface**)ptr.add(3).rip().as<PVOID>();
		});

		main_batch.add("Get Event Data", "48 89 5C 24 ? 57 48 83 EC ? 49 8B F8 4C 8D 05", [this](memory::handle ptr)
		{
			m_get_event_data = ptr.as<functions::GetEventData>();
		});

		main_batch.add("RID Joiner", "48 8D BE ? ? ? ? 48 8B CF 0F 10 ? 41 8B C4", [this](memory::handle ptr)
		{
			m_rid_joiner = ptr.as<PVOID>();
		});

		main_batch.add("Waypoint", "48 8D 05 ? ? ? ? 33 D2 48 89 50 F0 48 89 50 F8 48 89 10 48 89", [this](memory::handle ptr)
		{
			m_waypoint_coords = ptr.add(3).rip().add(0x10).as<rage::vector3*>();
		});
		
		main_batch.add("Get Label Text", "75 ? E8 ? ? ? ? 8B 0D ? ? ? ? 65 48 8B 04 25 ? ? ? ? BA ? ? ? ? 48 8B 04 C8 8B 0C 02 D1 E9", [this](memory::handle ptr)
		{
			m_get_label_text = ptr.sub(19).as<decltype(m_get_label_text)>();
		});
		//48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 30 0F B7 51
		
		main_batch.add("Increment Event", "48 89 5C 24 ? 48 89 74 24 ? 55 57 41 55 41 56 41 57 48 8B EC 48 83 EC 60 8B 79 30", [this](memory::handle ptr)
		{
			m_increment_event = ptr.as<functions::IncrementEvent>();
		});

		main_batch.add("Clear Ped Task Event", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 30 0F B7 51 30", [this](memory::handle ptr)
		{
			m_clear_ped_event = ptr.add(1).as<functions::ClearPedTask>();
		});
		
		main_batch.add("Request Control Event", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B EA 0F B7 51 30 48 8B F9 48 8B", [this](memory::handle ptr)
		{
			m_request_control_event = ptr.as<functions::CNetworkRequestEvent>();
		});
		
		main_batch.add("Remove Weapon Event", "48 89 5C 24 ? 57 48 83 EC 20 48 8B D9 E8 ? ? ? ? 0F B7 53 30 48 8B 0D ? ? ? ? 45 33 C0", [this](memory::handle ptr)
		{
			m_remove_weapon = ptr.as<functions::CRemoveWeaponEvent>();
		});
		
		main_batch.add("Kick Vote Event", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8D 71 30", [this](memory::handle ptr)
		{
			m_kick_vote = ptr.as<functions::CSendKickVoteEvent>();
		});

		main_batch.add("Explosion Event", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8A 42 21", [this](memory::handle ptr)
		{
			m_explosion_event = ptr.as<functions::CExplosionEvent>();
		});

		main_batch.add("PTFX Event", "48 8B ? 48 89 ? ? 48 89 ? ? 48 89 ? ? 55 41 ? 41 ? 48 8D ? ? 48 81 EC ? ? ? ? 0F 29 ? ? 45 33", [this](memory::handle ptr)
		{
			m_ptfx_event = ptr.as<functions::PTFXEvent>();
		});

		main_batch.add("Blackout", "48 8B D7 48 8B CB E8 ? ? ? ? 40 38 35 ? ? ? ? 74 40", [this](memory::handle ptr)
		{
			m_blackout = ptr.add(14).rip().as<bool*>();
		});

		main_batch.add("Hash Table", "48 8B 05 ? ? ? ? 4C 8B 14 D0 EB 09 41 3B 0A 74 54 4D", [this](memory::handle ptr)
		{
			m_hash_table = ptr.add(3).rip().as<CHashTable**>();
		});

		main_batch.add("Money In Business", "48 8D 05 ? ? ? ? 48 C1 E1 ? 48 03 C8 E8 ? ? ? ? 48 8B 5C", [this](memory::handle ptr)
		{
			m_money_in_bunker = ptr.add(3).rip().as<BusinessMoney**>();
		});

		main_batch.add("Get Model Info", "0F B7 05 ? ? ? ? 45 33 C9 4C 8B DA 66 85 C0 0F 84 ? ? ? ? 44 0F B7 C0 33 D2 8B C1 41 F7 F0 48 8B 05 ? ? ? ? 4C 8B 14 D0 EB 09 41 3B 0A 74 54", [this](memory::handle ptr)
		{
			m_get_model_info = ptr.as<functions::GetModelInfo>();
		});

		main_batch.add("Add Owned Explosion Bypass 1", "0F 85 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 48 08 E8", [this](memory::handle ptr)
		{
			m_add_owned_explosion_bypass_1 = ptr.as<DWORD64*>();
		});

		main_batch.add("Add Owned Explosion Bypass 2", "74 0E 48 8D 4D ? 45 33 C0", [this](memory::handle ptr)
		{
			m_add_owned_explosion_bypass_2 = ptr.as<DWORD64*>();
		});

		main_batch.add("Player Name Pointer", "48 8D ? ? ? ? ? E8 ? ? ? ? 48 85 ? 75 ? 48 83 C4 ? C3 CC CC 48 83 EC ? 48 8D", [this](memory::handle ptr)
		{
			m_real_name = ptr.add(3).rip().add(0x24).as<decltype(m_real_name)>();
		});

		main_batch.add("Player Real Name", "48 8D 0D ? ? ? ? E9 ? ? ? ? 48 89 ? ? ? 57 48 83 EC ? BF ? ? ? ? 48 8D ? ? ? ? ? 48 81 EB", [this](memory::handle ptr)
		{
			m_real_name_1 = ptr.add(3).rip().add(0x51F).as<decltype(m_real_name_1)>();
		});

		main_batch.add("Player Name ESP", "48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? 83", [this](memory::handle ptr)
		{
			m_player_name_esp = ptr.add(3).rip().add(0x84).as<decltype(m_player_name_esp)>();
		});
		
		main_batch.add("Send Net Info To Lobby", "E8 ? ? ? ? 84 C0 74 26 8B 96", [this](memory::handle ptr)
		{
			m_send_net_info_to_lobby = ptr.sub(0xC4).as<PVOID>();
		});
		
		main_batch.add("Player Name Pointer 2", "8B 05 ? ? ? ? 40 B7 01 C1 E8 0C 40 84 C7 74 04 0F BA EB 0F", [this](memory::handle ptr)
		{
			m_player_name_2 = ptr.add(2).rip().add(0xBDC).as<decltype(m_player_name_2)>();
		});

		main_batch.add("Player Name Display", "48 8D 05 ? ? ? ? 48 63 CB 48 8B D6 48 69 C9 ? ? ? ? 48 03 C8 E8 ? ? ? ? 84 C0 75 21", [this](memory::handle ptr)
		{
			m_player_name_display = ptr.add(3).rip().add(0x14).as<decltype(m_player_name_display)>();
		});
		
		main_batch.add("Player Rockstar ID", "48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? 83", [this](memory::handle ptr)
		{
			m_player_rid = ptr.add(3).rip().add(8).as<uint64_t*>();
		});

		main_batch.add("Player Crew", "48 8D 05 ? ? ? ? 48 69 C9 ? ? ? ? 48 03 C8 E8 ? ? ? ? 48 83 C4 ? C3 48 89 ? ? ? 48 89 ? ? ? 57", [this](memory::handle ptr)
		{
			m_player_crew = ptr.add(3).rip().as<CPlayerCrew*>();
		});
		
		main_batch.add("Session Weather", "E8 ? ? ? ? EB 08 66 41 0B CD", [this](memory::handle ptr)//48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 40 8A E9
		{
			m_session_weather = ptr.add(1).rip().as<functions::m_weather_change>();
		});

		main_batch.add("Set Lobby Clock", "E8 ? ? ? ? 48 8B 4F 60 48 85 C9 0F 84", [this](memory::handle ptr)//48 89 5C 24 ? 57 48 83 EC 20 8B F9 48 8B 0D ? ? ? ? 48 8B DA 33 D2
		{
			m_set_lobby_time = ptr.add(1).rip().as<functions::set_lobby_time_t>();
		});
		
		main_batch.add("IS DLC PRESENT", "48 89 5C 24 08 57 48 83 EC 20 81 F9", [this](memory::handle ptr)
		{
			m_is_dlc_present = ptr.as<PVOID>();
		});

		main_batch.add("Model Spawn Bypass", "48 8B C8 FF 52 30 84 C0 74 05 48", [this](memory::handle ptr)
		{
			m_model_spawn_bypass = ptr.add(8).as<PVOID>();
		});

		main_batch.add("Request Control Bypass", "48 89 5C 24 ? 57 48 83 EC 20 8B D9 E8 ? ? ? ? 84 C0", [this](memory::handle ptr)
		{
			m_request_control_bypass = ptr.add(19).as<PVOID>();
		});

		main_batch.add("CScriptedGameEvent", "40 53 48 81 EC ? ? ? ? 44 8B 81", [this](memory::handle ptr)
		{
			m_script_event = ptr.as<functions::ScriptGameEvent>();//48 89 44 24 ? 0F 95 C3
		});

		main_batch.add("Game Build", "48 83 EC 60 48 8D 0D ? ? ? ? E8", [this](memory::handle ptr)
		{
			m_game_build = ptr.sub(17).add(265 + 3).as<char*>();//48 89 44 24 ? 0F 95 C3
		});
		
		main_batch.add("Error Screen Handler", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 60 4C 8B F2 48 8B 94 24 ? ? ? ? 33 DB", [this](memory::handle ptr)
		{
			m_error_screen = ptr.as<decltype(m_error_screen)>();
		});

		main_batch.add("Freemode Tick", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 80 B9 ? ? ? ? ? 8B FA 48 8B D9 74 05", [this](memory::handle ptr)
		{
			m_gta_thread_tick = ptr.as<decltype(m_gta_thread_tick)>();
		});

		main_batch.add("Freemode Thread Killed", "48 89 5C 24 ? 57 48 83 EC 20 48 83 B9 ? ? ? ? ? 48 8B D9 74 14", [this](memory::handle ptr)
		{
			m_gta_thread_kill = ptr.as<decltype(m_gta_thread_kill)>();
		});

		main_batch.add("Bit Buffer Array", "48 89 5C 24 ? 57 48 83 EC 30 41 8B F8 4C", [this](memory::handle ptr)
		{
			m_read_bitbuf_array = ptr.as<decltype(m_read_bitbuf_array)>();
		});

		main_batch.add("Send Event Ack", "48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 80 7A", [this](memory::handle ptr)
		{
			m_send_event_ack = ptr.sub(5).as<decltype(m_send_event_ack)>();
		});

		main_batch.add("RECEIVED EVENT", "66 41 83 F9 ? 0F 83 ? ? ? ?", [this](memory::handle ptr)
		{
			m_received_event = ptr.as<decltype(m_received_event)>();
		});

		main_batch.add("Report Cash Spawn Event", "40 53 48 83 EC 20 48 8B D9 48 85 D2 74 29", [this](memory::handle ptr)
		{
			m_report_cash_spawn = ptr.as<decltype(m_report_cash_spawn)>();
		});

		main_batch.add("GetNetGamePlayer", "48 83 EC 28 33 C0 38 05 ? ? ? ? 74 0A", [this](memory::handle ptr)
		{
			m_get_net_game_player = ptr.as<functions::GetNetGamePlayer>();
		});
		
		main_batch.add("m_read_bitbuf_dword", "48 89 5c 24 ? 48 89 74 24 ? 57 48 83 ec ? 48 8b d9 33 c9 41 8b f0 8a 43", [this](memory::handle ptr)
		{
			m_read_bitbuf_dword = ptr.as<functions::ReadDword>(); //E8 ? ? ? ? 84 C0 74 1C 48 8D 96 ? ? ? ? 44 8D 43 08 48 8B CF E8
		});

		main_batch.add("clone_create", "48 8B C4 66 44 89 48", [this](memory::handle ptr)
		{
			m_clone_create = ptr.as<functions::clone_create_t>();
		});

		main_batch.add("netObjectMgrBase__GetNetworkObject", "44 38 33 75 30 66 44", [this](memory::handle ptr)
		{
			m_get_network_object = ptr.sub(0x40).as<functions::get_network_object_t>();
		});

		main_batch.add("netSyncTree::CanApplyToObject", "49 8B CE FF 50 70 84 C0 74 31 33 FF", [this](memory::handle ptr)
		{
			m_sync_can_apply = ptr.sub(0x2C).as<functions::sync_can_apply_t>();
		});

		main_batch.add("netSyncTree::ReadFromBuffer", "45 89 43 18 57 48 83 EC 30 48 83 79 10 00 49", [this](memory::handle ptr)
		{
			m_sync_read = ptr.sub(0xF).as<functions::sync_read_t>();
		});

		main_batch.add("g_objectMgr", "48 8B 0D ? ? ? ? 45 33 C0 E8 ? ? ? ? 33 FF 4C 8B F0", [this](memory::handle ptr)
		{
			m_network_object_manager = ptr.add(3).rip().as<rage::CNetworkObjectMgr**>();
		});

		main_batch.add("Censor Chat Text", "E8 ? ? ? ? 83 F8 FF 75 B9", [this](memory::handle ptr)
		{
			m_censor_chat_text = ptr.add(1).rip().as<PVOID>();
		});

		main_batch.add("Game Setting Pointer", "44 39 0D ? ? ? ? 74 0C", [this](memory::handle ptr)
		{//44 39 ? ? ? ? ? 74 ? 44 89 ? ? ? ? ? 40 8A
			m_game_setting = ptr.add(3).rip().sub(0x99).as<GameSetting*>();
		});
		
		main_batch.add("Camera Base", "48 39 0D ? ? ? ? 75 58 8B 42 20", [this](memory::handle ptr)
		{
			m_camera_base = ptr.add(3).rip().as<uintptr_t*>();
		});

		main_batch.run(memory::module(nullptr));

		m_hwnd = FindWindowW(L"grcWindow", nullptr);
		if (!m_hwnd)
			throw std::runtime_error("Failed to find the game's window.");

		g_pointers = this;
	}

	pointers::~pointers()
	{
		g_pointers = nullptr;
	}
}
