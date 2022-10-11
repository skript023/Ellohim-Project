#include "hooking.hpp"

namespace big
{
	void hooks::write_player_gamer_data_node(rage::netObject* player, CPlayerGamerDataNode* node)
	{
		g_hooking->m_write_player_gamer_data_node_hook.get_original<decltype(&write_player_gamer_data_node)>()(player, node);
		/*
		if (g.spoofing.spoof_crew_data)
		{
			strcpy(node->m_clan_tag, g.spoofing.crew_tag.c_str());
			node->m_is_system_clan = g.spoofing.rockstar_crew;
			node->m_is_clan_open = g.spoofing.square_crew_tag;

			if (g.spoofing.rockstar_crew)
			{
				strcpy(node->m_clan_name, "Rockstar");
			}
		}

		node->m_is_cheater = g.spoofing.spoof_cheater;
		node->m_is_rockstar_dev = g.spoofing.spoof_rockstar_dev;
		node->m_is_rockstar_qa = g.spoofing.spoof_rockstar_qa;
		*/
	}
}