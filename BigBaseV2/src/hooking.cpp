#include "common.hpp"
#include "function_types.hpp"
#include "logger.hpp"
#include "gta/array.hpp"
#include "gta/player.hpp"
#include "gta/script_thread.hpp"
#include "gui.hpp"
#include "hooking.hpp"
#include "memory/module.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script_mgr.hpp"

#include "features.hpp"
#include "gta_util.hpp"

#include <MinHook.h>
#include <script_global.hpp>

namespace big
{
	static GtaThread *find_script_thread(rage::joaat_t hash)
	{
		for (auto thread : *g_pointers->m_script_threads)
		{
			if (thread
				&& thread->m_context.m_thread_id
				&& thread->m_handler
				&& thread->m_script_hash == hash)
			{
				return thread;
			}
		}
		return nullptr;
	}

	hooking::hooking() :
		m_swapchain_hook(*g_pointers->m_swapchain, hooks::swapchain_num_funcs),
		m_set_cursor_pos_hook("SetCursorPos", memory::module("user32.dll").get_export("SetCursorPos").as<void*>(), &hooks::set_cursor_pos),
		m_run_script_threads_hook("Script hook", g_pointers->m_run_script_threads, &hooks::run_script_threads),
		m_convert_thread_to_fiber_hook("ConvertThreadToFiber", memory::module("kernel32.dll").get_export("ConvertThreadToFiber").as<void*>(), &hooks::convert_thread_to_fiber),

		m_censor_chat_text_hook("Chat Sensor", g_pointers->m_censor_chat_text, &hooks::censor_chat_text),
		m_write_player_gamer_data_node_hook("Player Gamer Data Node", g_pointers->m_write_player_gamer_data_node, &hooks::write_player_gamer_data_node),
		m_received_message_hook("Chat Message Hook", g_pointers->m_received_message, &hooks::received_message),
		m_get_network_event_data_hook("Desync Kick", g_pointers->m_get_network_event_data, &hooks::get_network_event_data),

		m_chat_receive_hook("Chat Received Hook", g_pointers->m_chat_receive, &hooks::chat_receive),
		m_player_has_joined_hook("Player Joined Hook", g_pointers->m_player_has_joined, &hooks::player_join),
		m_player_has_left_hook("Player Left Hook", g_pointers->m_player_has_left, &hooks::player_leave),
		m_send_net_info_to_lobby_hook("Send Net Info", g_pointers->m_send_net_info_to_lobby, hooks::send_net_info_to_lobby),
		m_sync_can_apply_hook("Sync Can Apply", g_pointers->m_sync_can_apply, &hooks::sync_can_apply),
		m_clone_create_hook("Clone Create", g_pointers->m_clone_create, &hooks::clone_create),

		m_gta_thread_tick_hook("Thread Tick", g_pointers->m_gta_thread_tick, &hooks::gta_thread_tick),
		m_gta_thread_kill_hook("Thread Killed", g_pointers->m_gta_thread_kill, &hooks::gta_thread_kill),

		m_received_event_hook("Received Event", g_pointers->m_received_event, &hooks::received_event),
		m_received_clone_sync_hook("Sync Tree Hook", g_pointers->m_received_clone_sync, &hooks::received_clone_sync),
		m_network_group_override("Network Override", g_pointers->m_network_group_override, &hooks::network_group_override)
	{
		m_swapchain_hook.hook(hooks::swapchain_present_index, &hooks::swapchain_present);
		m_swapchain_hook.hook(hooks::swapchain_resizebuffers_index, &hooks::swapchain_resizebuffers);

		g_hooking = this;
	}

	hooking::~hooking()
	{
		if (m_enabled)
			disable();

		g_hooking = nullptr;
	}

	void hooking::enable()
	{
		m_swapchain_hook.enable();
		m_og_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&hooks::wndproc)));
		m_set_cursor_pos_hook.enable();
		m_censor_chat_text_hook.enable();
		m_received_message_hook.enable();

		m_chat_receive_hook.enable();
		m_player_has_joined_hook.enable();
		m_player_has_left_hook.enable();
		m_received_event_hook.enable();

		m_send_net_info_to_lobby_hook.enable();
		m_sync_can_apply_hook.enable();
		m_clone_create_hook.enable();

		m_gta_thread_kill_hook.enable();
		m_gta_thread_tick_hook.enable();
		m_received_clone_sync_hook.enable();

		m_run_script_threads_hook.enable();
		m_convert_thread_to_fiber_hook.enable();

		m_enabled = true;
	}

	void hooking::disable()
	{
		m_enabled = false;

		m_convert_thread_to_fiber_hook.disable();
		m_run_script_threads_hook.disable();
		m_censor_chat_text_hook.disable();
		m_received_message_hook.disable();

		m_chat_receive_hook.disable();
		m_player_has_joined_hook.disable();
		m_player_has_left_hook.disable();
		m_received_event_hook.disable();

		m_send_net_info_to_lobby_hook.disable();
		m_sync_can_apply_hook.disable();
		m_clone_create_hook.disable();

		m_gta_thread_tick_hook.disable();
		m_gta_thread_kill_hook.disable();

		m_received_clone_sync_hook.disable();

		m_set_cursor_pos_hook.disable();
		SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_og_wndproc));
		m_swapchain_hook.disable();
	}

	minhook_keepalive::minhook_keepalive()
	{
		MH_Initialize();
	}

	minhook_keepalive::~minhook_keepalive()
	{
		MH_Uninitialize();
	}

	bool hooks::run_script_threads(std::uint32_t ops_to_execute)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{
				g_script_mgr.tick();
			}

			return g_hooking->m_run_script_threads_hook.get_original<functions::run_script_threads_t>()(ops_to_execute);
		} EXCEPT_CLAUSE
		return false;
	}

	void *hooks::convert_thread_to_fiber(void *param)
	{
		TRY_CLAUSE
		{
			if (IsThreadAFiber())
			{
				return GetCurrentFiber();
			}

			return g_hooking->m_convert_thread_to_fiber_hook.get_original<decltype(&convert_thread_to_fiber)>()(param);
		} EXCEPT_CLAUSE
		return nullptr;
	}

	HRESULT hooks::swapchain_present(IDXGISwapChain *this_, UINT sync_interval, UINT flags)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{
				g_renderer->on_present();
			}

			return g_hooking->m_swapchain_hook.get_original<decltype(&swapchain_present)>(swapchain_present_index)(this_, sync_interval, flags);
		} EXCEPT_CLAUSE
		return NULL;
	}

	HRESULT hooks::swapchain_resizebuffers(IDXGISwapChain * this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{
				g_renderer->pre_reset();

				auto result = g_hooking->m_swapchain_hook.get_original<decltype(&swapchain_resizebuffers)>(swapchain_resizebuffers_index)
					(this_, buffer_count, width, height, new_format, swapchain_flags);

				if (SUCCEEDED(result))
				{
					g_renderer->post_reset();
				}

				return result;
			}

			return g_hooking->m_swapchain_hook.get_original<decltype(&swapchain_resizebuffers)>(swapchain_resizebuffers_index)
				(this_, buffer_count, width, height, new_format, swapchain_flags);
		} EXCEPT_CLAUSE
		return NULL;
	}

	LRESULT hooks::wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{
				g_renderer->wndproc(hwnd, msg, wparam, lparam);
			}

			return CallWindowProcW(g_hooking->m_og_wndproc, hwnd, msg, wparam, lparam);
		} EXCEPT_CLAUSE
		return NULL;
	}

	BOOL hooks::set_cursor_pos(int x, int y)
	{
		TRY_CLAUSE
		{
			if (g_gui.m_opened)
				return true;

			return g_hooking->m_set_cursor_pos_hook.get_original<decltype(&set_cursor_pos)>()(x, y);
		} EXCEPT_CLAUSE
		return FALSE;
	}
}
