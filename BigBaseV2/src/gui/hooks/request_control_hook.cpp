#include "hooking.hpp"
#include "gta/net_game_event.hpp"
#include "gui/helper_function.hpp"

namespace big
{
	bool hooks::RequestControlEvent(int64_t thisptr, CNetGamePlayer* sender, CNetGamePlayer* receiver)
	{
		const char* sender_name = sender->get_name();
		auto sender_rid = sender->get_net_data()->m_rockstar_id;
		auto sender_id = sender->player_id;

		char sender_info[100];
		strcpy(sender_info, "~bold~~g~Blocked Request Control From ");
		strcat(sender_info, sender_name);

		if (g_settings.options["Request Control Block"] && player::is_player_driver(player::get_player_ped(g_local.player)))
		{
			message::notification(sender_name, sender_info, "~bold~~g~Ellohim Menu Protection");
			return true;
		}
		return g_hooking->m_request_control_event_hook.get_original<functions::CNetworkRequestEvent>()(thisptr, sender, receiver);
	}

}