#include "hooking.hpp"
#include "gui/player_list.h"
#include "gta/net_game_event.hpp"
#include "gta/net_object_mgr.hpp"
#include "gui/helper_function.hpp"

namespace big
{
	void hooks::KickVoteEvent(int64_t thisptr, rage::datBitBuffer* buffer, CNetGamePlayer* sender, CNetGamePlayer* receiver)
	{
		const char* sender_name = sender->get_name();
		auto sender_id = sender->player_id;
		uint32_t net_id{};
		buffer->ReadDword(&net_id, 32);
		if (g_settings.options["Log Player"])
			LOG(WARNING) << "Kick Vote Event" << " Sender : " << sender_name << " Receiver : " << receiver->get_name() << " SCID : " << sender->get_net_data()->m_rockstar_id << "Player ID : " << std::to_string(sender_id);//auto sender_id = *reinterpret_cast<uint8_t*>(sender + 0x35);

		char sender_info[100];
		strcpy(sender_info, "~bold~~g~Blocked Kick Vote Event From ");
		strcat(sender_info, sender_name);
		if (g_settings.options["Kick Vote Block"]) {
			message::notification(sender_name, sender_info, "~bold~~g~Ellohim Menu Protection");
			if (g_settings.options["Redirect Network Event"])
			{
				strcpy(sender_info, "~g~Redirect Event To ");
				strcat(sender_info, sender_name);
				message::notification("Event Redirect", sender_info, "~bold~~g~Ellohim Menu Redirect");
				remote_event::bail_player(sender_id);
			}
			buffer->Seek(0);
			return;
		}
		buffer->Seek(0);
		g_hooking->m_kick_vote_hook.get_original<functions::CSendKickVoteEvent>()(thisptr, buffer, sender, receiver);
	}

}