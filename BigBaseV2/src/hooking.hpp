#pragma once
#include "common.hpp"
#include "detour_hook.hpp"
#include "gta/fwddec.hpp"
#include "gta/script_thread.hpp"
#include "script_hook.hpp"
#include "vmt_hook.hpp"

namespace big
{
	struct hooks
	{
		static bool run_script_threads(std::uint32_t ops_to_execute);
		static void *convert_thread_to_fiber(void *param);
		static bool send_net_info_to_lobby(rage::netPlayerData* local_player, __int64 a2, __int64 a3, DWORD* a4);
		static int censor_chat_text(__int64 chat_menu, const char* user_text, const char** output_text);
		static const char* get_label_text(void* unk, const char* label);
		static void player_join(CNetworkObjectMgr* _this, CNetGamePlayer* net_player);
		static void player_leave(CNetworkObjectMgr* _this, CNetGamePlayer* net_player);
		static bool rid_crash(__int64 a1);
		static bool received_message(void* netConnectionManager, void* a2, rage::netConnection::InFrame* frame);
		
		static bool received_event(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint16_t event_id, int event_index, int event_handled_bitset, int64_t bit_buffer_size, rage::datBitBuffer* buffer);

		static __int64* chat_receive(__int64 chat_pointer, __int64 unk2, __int64 peerId, const char* msg, char IsTeam);
		static bool clone_create(rage::CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, int32_t _object_type, int32_t _object_id, int32_t _object_flag, rage::datBitBuffer* buffer, int32_t timestamp);
		static bool sync_can_apply(rage::netSyncTree* netSyncTree, rage::netObject* netObject);
		static bool sync_read_buffer(rage::netSyncTree* netSyncTree, int32_t sync_type, int32_t _sync_flag, rage::datBitBuffer* buffer, void* netLogStub);
		
		static void disable_error_screen(char* entryHeader, char* entryLine1, int instructionalKey, char* entryLine2, BOOL p4, Any p5, Any* p6, Any* p7, BOOL background);
		static bool net_array_handler(int64_t netArrayHandlerBaseMgr, uint8_t* a2, rage::datBitBuffer* datbitbuffer, uint32_t bytes_to_read, int16_t a5);
		static rage::eThreadState gta_thread_tick(GtaThread* a1, unsigned int a2);
		static rage::eThreadState gta_thread_kill(GtaThread* thread);
		
		static constexpr auto swapchain_num_funcs = 19;
		static constexpr auto swapchain_present_index = 8;
		static constexpr auto swapchain_resizebuffers_index = 13;
		static HRESULT swapchain_present(IDXGISwapChain *this_, UINT sync_interval, UINT flags);
		static HRESULT swapchain_resizebuffers(IDXGISwapChain *this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags);

		static LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		static BOOL set_cursor_pos(int x, int y);
	};

	struct minhook_keepalive
	{
		minhook_keepalive();
		~minhook_keepalive();
	};

	class hooking
	{
		friend hooks;
	public:
		explicit hooking();
		~hooking();

		void enable();
		void disable();
	private:
		bool m_enabled{};
		minhook_keepalive m_minhook_keepalive;

		vmt_hook m_swapchain_hook;
		WNDPROC m_og_wndproc;
		detour_hook m_set_cursor_pos_hook;

		detour_hook m_run_script_threads_hook;
		detour_hook m_convert_thread_to_fiber_hook;
		detour_hook m_get_label_text;
		detour_hook m_player_has_joined_hook;
		detour_hook m_player_has_left_hook;
		//detour_hook m_received_message_hook;
		
		detour_hook m_net_array_handler_hook;
		//detour_hook m_send_net_info_to_lobby_hook;
		detour_hook m_censor_chat_text_hook;

		detour_hook m_chat_receive_hook;
		detour_hook m_received_event_hook;
		detour_hook m_clone_create_hook;
		detour_hook m_sync_can_apply_hook;
		detour_hook m_sync_read_buffer_hook;
		detour_hook m_rid_crash;

		//detour_hook m_error_screen_hook;

		detour_hook m_gta_thread_tick_hook;
		detour_hook m_gta_thread_kill_hook;
	};

	inline hooking *g_hooking{};
}
