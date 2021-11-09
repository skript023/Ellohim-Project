#include "hooking.hpp"
#include "gta_util.hpp"
#include "gui/player_list.h"
#include "gui/helper_function.hpp"

namespace big
{
	bool hooks::send_net_info_to_lobby(rage::netPlayerData* local_player, __int64 a2, __int64 a3, DWORD* a4)
	{
		auto ip_address = rage_helper::get_local_playerinfo()->m_online_ip;
		uint8_t out[4];
		*(uint32_t*)&out = ip_address;
		auto ip = fmt::format("IP : {}.{}.{}.{}", out[3], out[2], out[1], out[0]);

		uint8_t in[4] = { g_item.ip_4, g_item.ip_3, g_item.ip_3, g_item.ip_1 };

		auto name = std::string(local_player->m_name);
		std::string name_real = g_pointers->m_real_name;
		auto scid_real = *g_pointers->m_player_rid;
		if (g_settings.options["Log Player"])
			LOG(HACKER) << "scid real: " << scid_real << " scid: " << local_player->m_rockstar_id << " name: " << local_player->m_name << " " << ip << " Address : " << &ip_address;

		if (scid_real == local_player->m_rockstar_id)//
		{
			std::string spoof_name = player_list::NameSpoofer;
			uint64_t spoof_scid = var::DataPlayerRID[g_fitur.rid_spoof];
			uint32_t spoof_ip = *(uint32_t*)&in;
			bool name_diff = !spoof_name.empty() && spoof_name != name;
			bool scid_diff = spoof_scid != 0 && spoof_scid != local_player->m_rockstar_id;
			bool ip_diff = spoof_ip != 0 && spoof_ip != local_player->m_relay_ip;

			if (ip_diff)
				local_player->m_relay_ip = *(uint32_t*)&in; message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~IP Has Been Spoofed {}.{}.{}.{}", in[3], in[2], in[1], in[0]).c_str(), "~bold~~g~Ellohim Spoofer");
			if (name_diff)
				player::change_name(spoof_name, local_player); message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Name Has Been Spoofed {}", local_player->m_name).c_str(), "~bold~~g~Ellohim Spoofer");//player::local_name((char*)spoof_name.c_str());
			if (scid_diff)
			{
				if (g_local.script_transition)
				{
					local_player->m_rockstar_id = scid_real;
					message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~SCID Has Been Restored To {}", local_player->m_rockstar_id).c_str(), "~bold~~g~Ellohim Spoofer");
				}
				else
				{
					local_player->m_rockstar_id = spoof_scid;
					message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~SCID Has Been Spoofed To {}", local_player->m_rockstar_id).c_str(), "~bold~~g~Ellohim Spoofer");
				}
			}

			uint8_t spoofed[4];
			*(uint32_t*)&spoofed = local_player->m_relay_ip;
			auto spoofed_ip = fmt::format("{}.{}.{}.{}", spoofed[3], spoofed[2], spoofed[1], spoofed[0]);

			std::string info_spoofer = fmt::format("~g~Your Nickname : {} SCID : {} IP : {}.{}.{}.{}", local_player->m_name, local_player->m_rockstar_id, spoofed[3], spoofed[2], spoofed[1], spoofed[0]);
			message::notification("~bold~~g~Ellohim Private Menu", info_spoofer.c_str(), "~bold~~g~Ellohim Spoofer");

			if (g_settings.options["Log Player"])
			{
				LOG(HACKER) << "name_diff: " << name_diff << " scid_diff : " << scid_diff << " spoof_name: " << spoof_name << " name: " << local_player->m_name << " SCID Now : " << local_player->m_rockstar_id << " Name Now : " << local_player->m_name;
				LOG(HACKER) << "ip_diff" << ip_diff << "Real " << ip << " Spoofed IP : " << spoofed_ip;
			}

			auto retnvalue = g_hooking->m_send_net_info_to_lobby_hook.get_original<decltype(&send_net_info_to_lobby)>()(local_player, a2, a3, a4);
			if (scid_diff)
				local_player->m_rockstar_id = scid_real;
			if (ip_diff)
				local_player->m_relay_ip = ip_address;
			if (g_settings.options["Log Player"])
				LOG(HACKER) << "name_diff: " << name_diff << " scid_diff : " << scid_diff << " spoof_name: " << spoof_name << " name: " << local_player->m_name << " SCID Now : " << local_player->m_rockstar_id << " Name Now : " << local_player->m_name << " Current IP : " << spoofed_ip;
			return retnvalue;
		}
		return g_hooking->m_send_net_info_to_lobby_hook.get_original<decltype(&send_net_info_to_lobby)>()(local_player, a2, a3, a4);
	}

}