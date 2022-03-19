#include "hooking.hpp"
#include "gta/net_game_event.hpp"
#include "gui/helper_function.hpp"

namespace big
{
	// hook pada bagian ini akan melakukan rebuild sebagaimana game membaca datBitBuffer
	// secara spesifik ini akan menulis ulang agar tidak mengalami NET_ARRAY_ERROR
	// jika hendak dicrashkan oleh player lain maka function ini akan me-return false;
	bool hooks::net_array_handler(int64_t netArrayHandlerBaseMgr, uint8_t* a2, rage::datBitBuffer* datbitbuffer, uint32_t bytes_to_read, int16_t a5)
	{
		if (g_running)
		{
			uint32_t buffer = 0;

			const auto bytes_start = datbitbuffer->m_unkBit;
			for (unsigned int i = datbitbuffer->m_unkBit - bytes_start;
				i < bytes_to_read;
				i = datbitbuffer->m_unkBit - bytes_start)
			{
				const auto bytes_read_before = datbitbuffer->m_unkBit;
				datbitbuffer->ReadDword(&buffer, 1u);

				if (bytes_read_before == datbitbuffer->m_unkBit)
				{
					ImGui::InsertNotification({ ImGuiToastType_Protection, 7000, "NET_ARRAY_ERROR caught, someones probably trying to crash us." });

					return false;
				}
			}

			datbitbuffer->Seek(bytes_start);
		}

		return g_hooking->m_net_array_handler_hook.get_original<decltype(&hooks::net_array_handler)>()(netArrayHandlerBaseMgr, a2, datbitbuffer, bytes_to_read, a5);
	}
}