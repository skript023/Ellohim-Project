#include "hooking.hpp"
#include "gui/helper_function.hpp"

namespace big
{
	void hooks::player_join(CNetworkObjectMgr* _this, CNetGamePlayer* net_player)
	{
		std::string info = "~g~Player " + std::string(net_player->get_name()) + "' joined taking slot #" + std::to_string(net_player->player_id);
		message::notification(info.c_str(), "~bold~~g~Player Joined");

		return g_hooking->m_player_has_joined_hook.get_original<decltype(&hooks::player_join)>()(_this, net_player);
	}

	void hooks::player_leave(CNetworkObjectMgr* _this, CNetGamePlayer* net_player)
	{
		std::string info = "~g~Player " + std::string(net_player->get_name()) + " left freeing slot #" + std::to_string(net_player->player_id);
		message::notification(info.c_str(), "~bold~~g~Player Joined");

		return g_hooking->m_player_has_left_hook.get_original<decltype(&hooks::player_leave)>()(_this, net_player);
	}
}