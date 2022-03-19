#pragma once
#include "common.hpp"
#include "gta/fwddec.hpp"
#include "gta/enums.hpp"
#include "function_types.hpp"
#include "gta\replay.hpp"

namespace big
{
	class pointers
	{
	public:
		explicit pointers();
		~pointers();
	public:
		HWND m_hwnd{};

		eGameState *m_game_state{};
		bool *m_is_session_started{};

		CPedFactory **m_ped_factory{};
		CNetworkPlayerMgr **m_network_player_mgr{};

		rage::scrNativeRegistrationTable *m_native_registration_table{};
		functions::get_native_handler_t m_get_native_handler{};
		functions::fix_vectors_t m_fix_vectors{};

		rage::atArray<GtaThread*> *m_script_threads{};
		rage::scrProgramTable *m_script_program_table{};
		functions::run_script_threads_t m_run_script_threads{};
		std::int64_t **m_script_globals{};

		CGameScriptHandlerMgr **m_script_handler_mgr{};

		IDXGISwapChain **m_swapchain{};
		
		int *m_total_friend;
		FriendList** m_friend_list{};
		functions::ptr_to_handle_t m_ptr_to_handle{};
		rage::CReplayInterface* m_replay_interface;
		rage::BlipList* m_blip_ptr;
		rage::CNetworkObjectMgr** m_network_object_manager{};
		rage::ivector2 *m_screen_resolution{};
		CutsceneManager **m_cutscene_mgr;
		PresenceData** m_presence_data;

		DWORD64 *m_add_owned_explosion_bypass_1;
		DWORD64 *m_add_owned_explosion_bypass_2;
		char* m_real_name;
		char* m_real_name_1;
		char *m_player_name_esp;
		char *m_player_name_2;
		char *m_player_name_display;
		char* m_player_name_4;
		char* m_player_name_5;
		char* m_game_build;
		bool* m_blackout;
		int* m_delivery;
		int* m_player_aim;
		bool* m_wep_crash;
		float* m_sky_blue;
		float* m_sky_red;
		CPlayerCrew *m_player_crew;
		BusinessMoney** m_money_in_bunker{};
		uint64_t* m_money_in_bunker_2;
		uint64_t* m_player_rid;
		rage::vector3* m_waypoint_coords;
		functions::GetEventData m_get_event_data{};
		functions::m_weather_change m_session_weather{};
		functions::set_lobby_time_t m_set_lobby_time{};
		functions::IncrementEvent m_increment_event{};
		functions::ClearPedTask m_clear_ped_event{};
		functions::ReadDword m_read_bitbuf_dword{};
		functions::clone_create_t m_clone_create{};
		functions::get_model_info m_get_model_info{};
		functions::CNetworkRequestEvent m_request_control_event{};
		functions::CRemoveWeaponEvent m_remove_weapon{};
		functions::CSendKickVoteEvent m_kick_vote{};
		functions::CExplosionEvent m_explosion_event{};
		functions::PTFXEvent m_ptfx_event{};
		functions::handle_to_ptr_t m_handle_to_ptr{};
		functions::player_pointer m_player_ptr{};
		functions::get_player_name_t m_get_player_name{};

		functions::error_screen* m_error_screen{};
		functions::gta_thread_tick m_gta_thread_tick{};
		functions::gta_thread_kill m_gta_thread_kill{};

		functions::read_bitbuf_array m_read_bitbuf_array{};
		functions::send_event_ack m_send_event_ack{};
		functions::report_cash_spawn m_report_cash_spawn{};
		functions::GetLabelText m_get_label_text{};
		functions::received_event m_received_event{};

		functions::get_network_object_t m_get_network_object{};
		functions::sync_can_apply_t m_sync_can_apply{};
		functions::sync_read_t m_sync_read{};
		functions::clone_sync_t m_clone_sync{};
		functions::clone_remove_t m_clone_remove{};
		functions::clone_pack_t m_clone_pack{};
		functions::clone_sync_ack_t m_clone_sync_ack{};
		functions::clone_create_ack_t m_clone_create_ack{};
		functions::clone_remove_ack_t m_clone_remove_ack{};

		functions::joined_player_t m_player_has_joined{};
		functions::left_player_t m_player_has_left{};

		functions::GetNetGamePlayer m_get_net_game_player{};
		
		rage::datBitBuffer *m_bitbufferclass;
		GameSetting* m_game_setting;
		functions::ScriptGameEvent m_script_event{};
		CHashTable **m_hash_table;
		uintptr_t* m_camera_base;

		PVOID m_send_net_info_to_lobby;
		PVOID m_rid_joiner;
		PVOID m_viewport;

		PVOID m_request_control_bypass;
		PVOID m_nativeReturn;
		PVOID m_is_dlc_present;
		PVOID m_censor_chat_text;
		PVOID m_game_invite;
		PVOID m_net_array_handler;

		PVOID m_model_spawn_bypass;
	};

	inline pointers *g_pointers{};
}
