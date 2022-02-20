#include "hooking.hpp"
#include "gui/helper_function.hpp"
#include "gta_util.hpp"

namespace big
{
	void hooks::player_join(CNetworkObjectMgr* _this, CNetGamePlayer* net_player)
	{
		if (g_settings.options["Player Join Log"])
		{
			ImGui::InsertNotification({ ImGuiToastType_Ellohim, 5000, "%s joined", net_player->get_name() });
		}

		return g_hooking->m_player_has_joined_hook.get_original<decltype(&hooks::player_join)>()(_this, net_player);
	}

	void hooks::player_leave(CNetworkObjectMgr* _this, CNetGamePlayer* net_player)
	{
		if (g_settings.options["Player Join Log"])
		{
			ImGui::InsertNotification({ ImGuiToastType_Ellohim, 5000, "%s left", net_player->get_name() });
		}

		return g_hooking->m_player_has_left_hook.get_original<decltype(&hooks::player_leave)>()(_this, net_player);
	}
}