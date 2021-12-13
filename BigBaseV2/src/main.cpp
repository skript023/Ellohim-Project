#include "common.hpp"
#include "features.hpp"
#include "fiber_pool.hpp"
#include "gui.hpp"
#include "logger.hpp"
#include "hooking.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script_mgr.hpp"
#include "gui/window/game_window.hpp"

BOOL APIENTRY DllMain(HMODULE hmod, DWORD reason, PVOID)
{
	using namespace big;
	if (reason == DLL_PROCESS_ATTACH)
	{

		DisableThreadLibraryCalls(hmod);

		g_hmodule = hmod;
		g_main_thread = CreateThread(nullptr, 0, [](PVOID) -> DWORD
		{
			while (!FindWindow(L"grcWindow", L"Grand Theft Auto V"))
				std::this_thread::sleep_for(1s);

			auto logger_instance = std::make_unique<logger>();
			try
			{
				LOG(RAW_GREEN_TO_CONSOLE) << u8R"kek(
__          __    _                   _  __           _        _ 
\ \        / /   | |                 | |/ /          | |      | |
 \ \  /\  / /   _| |__   __ _ _ __   | ' / ___  _ __ | |_ ___ | |
  \ \/  \/ / | | | '_ \ / _` | '_ \  |  < / _ \| '_ \| __/ _ \| |
   \  /\  /| |_| | | | | (_| | | | | | . \ (_) | | | | || (_) | |
    \/  \/  \__,_|_| |_|\__,_|_| |_| |_|\_\___/|_| |_|\__\___/|_|
 )kek";
				auto pointers_instance = std::make_unique<pointers>();
				LOG(HACKER) << "Pointers initialized.";

				auto renderer_instance = std::make_unique<renderer>();
				LOG(HACKER) << "Renderer initialized.";

				auto fiber_pool_instance = std::make_unique<fiber_pool>(10);
				LOG(HACKER) << "Fiber pool initialized.";

				auto hooking_instance = std::make_unique<hooking>();
				LOG(HACKER) << "Hooking initialized.";

				g_settings.load();
				LOG(HACKER) << "Settings Loaded.";

				g_script_mgr.add_script(std::make_unique<script>(&features::script_func));
				g_script_mgr.add_script(std::make_unique<script>(&gui::script_func));
				LOG(HACKER) << "Scripts registered.";

				g_hooking->enable();
				LOG(HACKER) << "Hooking enabled.";

				while (g_running)
				{
					std::this_thread::sleep_for(500ms);
				}

				g_hooking->disable();
				LOG(HACKER) << "Hooking disabled.";

				std::this_thread::sleep_for(1000ms);

				g_script_mgr.remove_all_scripts();
				LOG(HACKER) << "Scripts unregistered.";

				hooking_instance.reset();
				LOG(HACKER) << "Hooking uninitialized.";

				fiber_pool_instance.reset();
				LOG(HACKER) << "Fiber pool uninitialized.";

				renderer_instance.reset();
				LOG(HACKER) << "Renderer uninitialized.";

				pointers_instance.reset();
				LOG(HACKER) << "Pointers uninitialized.";
			}
			catch (std::exception const &ex)
			{
				LOG(WARNING) << ex.what();
				MessageBoxA(nullptr, ex.what(), nullptr, MB_OK | MB_ICONEXCLAMATION);
			}

			LOG(INFO) << "Farewell!";
			logger_instance.reset();
			game_window::logout();
			LOG(INFO) << "Logout from session.!";
			CloseHandle(g_main_thread);
			FreeLibraryAndExitThread(g_hmodule, 0);
		}, nullptr, 0, &g_main_thread_id);
	}

	return true;
}
