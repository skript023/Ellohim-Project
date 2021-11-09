#include "hooking.hpp"
#include "gui/player_list.h"
#include "gta/net_game_event.hpp"
#include "gta/net_object_mgr.hpp"
#include "gui/helper_function.hpp"

namespace big
{
	bool hooks::ExplosionEvent(int64_t thisptr, CNetGamePlayer* sender, CNetGamePlayer* receiver)
	{
		const char* sender_name = sender->get_name();
		auto sender_rid = sender->get_net_data()->m_rockstar_id;
		auto sender_id = systems::get_player_id_from_name(sender_name);
		auto sender_info = fmt::format("~bold~~g~Blocked Explosion Event From {} with player id : {}", sender_name, sender_id);

		if (g_settings.options["Explosion Event Block"])
		{
			//LOG(WARNING) << sender_name << " Receiver : " << receiver->get_name() << " SCID : " << sender->get_net_data()->m_rockstar_id << " Player ID : " << std::to_string(sender_id);//auto sender_id = *reinterpret_cast<uint8_t*>(sender + 0x35);
			message::notification(sender_name, sender_info.c_str(), "~bold~~g~Ellohim Menu Protection");
			return true;
		}
		return g_hooking->m_explosion_event_hook.get_original<functions::CExplosionEvent>()(thisptr, sender, receiver);
	}

}