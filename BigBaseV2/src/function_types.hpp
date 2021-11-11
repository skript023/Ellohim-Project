#pragma once
#include "common.hpp"
#include "gta/fwddec.hpp"
#include "gta/natives.hpp"

namespace big::functions
{
	using run_script_threads_t = bool(*)(std::uint32_t ops_to_execute);
	using get_native_handler_t = rage::scrNativeHandler(*)(rage::scrNativeRegistrationTable*, rage::scrNativeHash);
	using fix_vectors_t = void(*)(rage::scrNativeCallContext*);
	using m_weather_change = void(*)(int a1, int weather_id, int a3, __int64 a4);
	using set_lobby_time_t = bool(*)(int32_t, uint64_t);
	using ptr_to_handle_t = Entity(__fastcall*)(PVOID pointer);
	using handle_to_ptr_t = uintptr_t*(__fastcall*)(Entity entity);
	using player_pointer = CPed*(__fastcall*)(Player player);
	using get_player_name_t = const char*(__fastcall*)(Player player);
	using GetEventData = bool(*)(std::int32_t eventGroup, std::int32_t eventIndex, std::uint64_t* argStruct, std::int32_t argCount);

	using IncrementEvent = bool(*)(CNetworkIncrementStatEvent* net_event_struct, CNetGamePlayer* sender, CNetGamePlayer* receiver);
	using ClearPedTask = bool(*)(int64_t thisptr, CNetGamePlayer* sender, CNetGamePlayer* receiver);
	using CNetworkRequestEvent = bool(*)(int64_t thisptr, CNetGamePlayer* sender, CNetGamePlayer* receiver);
	using CRemoveWeaponEvent = void(*)(int64_t thisptr, rage::datBitBuffer* buffer, CNetGamePlayer* sender, CNetGamePlayer* receiver);
	using CSendKickVoteEvent = void(*)(int64_t thisptr, rage::datBitBuffer* buffer, CNetGamePlayer* sender, CNetGamePlayer* receiver);
	using CExplosionEvent = bool(*)(int64_t thisptr, CNetGamePlayer* sender, CNetGamePlayer* receiver);
	using ScriptGameEvent = bool(*)(CScriptedGameEvent* NetEventStruct, CNetGamePlayer* sender);
	using PTFXEvent = bool(*)(int64_t thisptr, CNetGamePlayer* sender, CNetGamePlayer* receiver);

	using ReadDword = bool(*)(rage::datBitBuffer* ptr, uint32_t* integer, int bits);
	using read_bitbuf_array = bool(rage::datBitBuffer* buffer, PVOID read, int bits, int);

	using clone_create_t = bool (*) (rage::CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, int32_t object_type, int32_t object_id, int32_t object_flag, rage::datBitBuffer* buffer, int32_t timestamp);
	using sync_can_apply_t = bool (*)(rage::netSyncTree* netSyncTree, rage::netObject* netObject);
	using sync_read_t = bool (*)(rage::netSyncTree* self, int32_t sync_type, int32_t sync_flag, rage::datBitBuffer* buffer, void* netLogStub);
	
	using get_network_object_t = rage::netObject* (*) (rage::CNetworkObjectMgr* mgr, int16_t id, bool is_true);
	using GetModelInfo = int64_t(*)(unsigned int model_hash, DWORD* a2);
	using SendNetInfoToLobby = bool(*)(rage::netPlayerData* local_player, __int64 a2, __int64 a3, DWORD* a4);
	using GetNetGamePlayer = CNetGamePlayer*(__fastcall*)(Player player);

	using error_screen = void(char* entryHeader, char* entryLine1, int instructionalKey, char* entryLine2, BOOL p4, Any p5, Any* p6, Any* p7, BOOL background);
	using gta_thread_tick = __int64(GtaThread* a1, unsigned int a2);
	using gta_thread_kill = __int64(GtaThread* a1);
	using send_event_ack = void(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, int event_index, int event_handled_bitset);
	using report_cash_spawn = bool(__int64 creport_cash_spawn_event, CNetGamePlayer* source_player);
	using report_myself_event_sender = void(__int64 a1, unsigned int a2, unsigned int a3, unsigned int a4);
	using GetLabelText = const char* (void* unk, const char* label);
	using received_event = bool(rage::netEventMgr* event_manager,CNetGamePlayer* source_player,CNetGamePlayer* target_player,uint16_t event_id,int event_index,int event_handled_bitset,int64_t bit_buffer_size, rage::datBitBuffer* bit_buffer);
}

