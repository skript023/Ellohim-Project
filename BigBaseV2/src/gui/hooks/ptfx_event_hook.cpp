#include "hooking.hpp"
#include "gta/net_game_event.hpp"
#include "gui/helper_function.hpp"

namespace big
{
	bool hooks::PTFXEvent(int64_t thisptr, CNetGamePlayer* sender, CNetGamePlayer* receiver)
	{
		const char* sender_name = sender->get_name();
		auto sender_rid = sender->get_net_data()->m_rockstar_id;
		auto sender_id = sender->player_id;
		char sender_info[100];
		strcpy(sender_info, "~bold~~g~Blocked PTFX Event From ");
		strcat(sender_info, sender_name);

		if (g_settings.options["PTFX Event Block"])
		{
			message::notification(sender_name, sender_info, "~bold~~g~Ellohim Menu Protection");
			return true;
		}
		return g_hooking->m_ptfx_event_hook.get_original<functions::PTFXEvent>()(thisptr, sender, receiver);
	}

}