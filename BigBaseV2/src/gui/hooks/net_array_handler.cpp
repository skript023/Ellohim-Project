#include "hooking.hpp"
#include "gta/net_game_event.hpp"
#include "gui/helper_function.hpp"

namespace big
{
	// hook pada bagian ini akan melakukan rebuild sebagaimana game membaca datBitBuffer
	// secara spesifik ini akan menulis ulang agar tidak mengalami NET_ARRAY_ERROR
	// jika net array buffer dibuat abnormal oleh player lain maka function ini akan me-return false;
	bool hooks::net_array_handler(int64_t netArrayHandlerBaseMgr, uint8_t* a2, rage::datBitBuffer* datbitbuffer, uint32_t bytes_to_read, int16_t a5)
	{
		if (g_running)
		{
			if (g_settings.options["Crash Protection"])
			{
				if (datbitbuffer->m_unkBit + bytes_to_read > datbitbuffer->m_curBit)
				{
					ImGui::InsertNotification({ ImGuiToastType_Protection, 7000, "NET_ARRAY_ERROR caught, someones probably trying to crash us." });

					return false;
				}
			}
		}
		//return g_hooking->m_net_array_handler_hook.get_original<decltype(&hooks::net_array_handler)>()(netArrayHandlerBaseMgr, a2, datbitbuffer, bytes_to_read, a5);
	}
}