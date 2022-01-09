#include "hooking.hpp"
#include "gta_util.hpp"
#include "gui/helper_function.hpp"

namespace big
{
	bool hooks::send_net_info_to_lobby(rage::netPlayerData* local_player, __int64 a2, __int64 a3, DWORD* a4)
	{
		rage::netAddress ip_address = *(rage::netAddress*)&rage_helper::get_local_playerinfo()->m_online_ip;
		auto ip = fmt::format("IP : {}.{}.{}.{}", ip_address.m_field1, ip_address.m_field2, ip_address.m_field3, ip_address.m_field4);

		uint8_t in[4] = { g_spoofer_option->ip_4, g_spoofer_option->ip_3, g_spoofer_option->ip_3, g_spoofer_option->ip_1 };

		auto name = std::string(local_player->m_name);
		std::string name_real = g_pointers->m_real_name;
		auto scid_real = *g_pointers->m_player_rid;
		
		if (scid_real == local_player->m_rockstar_id)//
		{
			std::string spoof_name;
			strcmp((char*)spoof_name.c_str(), g_spoofer_option->spoofed_name);
			uint64_t spoof_scid = var::DataPlayerRID[g_spoofer_option->rid_spoof];
			uint32_t spoof_ip = *(uint32_t*)&in;
			bool name_diff = !spoof_name.empty() && spoof_name != name;
			bool scid_diff = spoof_scid != 0 && spoof_scid != local_player->m_rockstar_id;
			bool ip_diff = spoof_ip != 0 && spoof_ip != local_player->m_relay_ip;

			if (ip_diff)
				local_player->m_relay_ip = *(uint32_t*)&in;
			if (name_diff)
				player::change_name(spoof_name, local_player);
			if (scid_diff)
			{
				if (g_local.script_transition)
				{
					local_player->m_rockstar_id = scid_real;
				}
				else
				{
					local_player->m_rockstar_id = spoof_scid;
				}
			}

			if (!ip_diff || !name_diff || !scid_diff)
				message::notification("~g~Your Information Has Spoofed", "~bold~~g~Ellohim Spoofer");

			rage::netAddress spoofed = *(rage::netAddress*)&local_player->m_relay_ip;
			auto spoofed_ip = fmt::format("{}.{}.{}.{}", spoofed.m_field1, spoofed.m_field2, spoofed.m_field3, spoofed.m_field4);

			auto retnvalue = g_hooking->m_send_net_info_to_lobby_hook.get_original<decltype(&send_net_info_to_lobby)>()(local_player, a2, a3, a4);
			if (scid_diff)
				local_player->m_rockstar_id = scid_real;
			if (ip_diff)
				local_player->m_relay_ip = *(uint32_t*)&ip_address;

			return retnvalue;
		}
		return g_hooking->m_send_net_info_to_lobby_hook.get_original<decltype(&send_net_info_to_lobby)>()(local_player, a2, a3, a4);
	}
}