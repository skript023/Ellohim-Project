#include "hooking.hpp"
#include "gta/net_game_event.hpp"
#include "gui/helper_function.hpp"

namespace big
{
	bool hooks::clear_ped_task(int64_t thisptr, CNetGamePlayer* sender, CNetGamePlayer* receiver)
	{
		const char* sender_name = sender->get_name();
		auto sender_id = sender->player_id;

		if (g_settings.options["Log Player"])
			LOG(WARNING) << "Clear Ped Task Event" << " Sender : " << sender_name << " SCID : " << sender->get_net_data()->m_rockstar_id << " Player ID : " << std::to_string(sender_id) << " Receiver : " << receiver->get_name();//auto sender_id = *reinterpret_cast<uint8_t*>(sender + 0x35);

		char sender_info[100];
		strcpy(sender_info, "~bold~~g~Blocked Clear Ped Task From ");
		strcat(sender_info, sender_name);
		if (g_settings.options["Clear Ped Task Block"]) {
			message::notification(sender_name, sender_info, "~bold~~g~Ellohim Menu Protection");
			if (g_settings.options["Redirect Network Event"])
			{
				strcpy(sender_info, "~g~Redirect Event To ");
				strcat(sender_info, sender_name);
				message::notification("Event Redirect", sender_info, "~bold~~g~Ellohim Menu Redirect");
				remote_event::bail_player(sender_id);
			}
			return true;
		}
		return g_hooking->m_clear_ped_hook.get_original<functions::ClearPedTask>()(thisptr, sender, receiver);
	}
}