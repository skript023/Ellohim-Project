#include "common.hpp"
#include "function_types.hpp"
#include "logger.hpp"
#include "gta/array.hpp"
#include "gta/player.hpp"
#include "gta/script_thread.hpp"
#include "gui.hpp"
#include "hooking.hpp"
#include "memory/module.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script_mgr.hpp"
#include "gui/player_list.h"
#include "gta/net_game_event.hpp"
#include "gta/net_object_mgr.hpp"
#include "gui/helper_function.hpp"
#include "features.hpp"
#include "gta_util.hpp"

#include <MinHook.h>
#include <script_global.hpp>

namespace big
{
	bool hooks::IncrementStatEvent(CNetworkIncrementStatEvent* net_event_struct, CNetGamePlayer* sender, CNetGamePlayer* receiver)
	{
		auto hash = net_event_struct->m_stat;//*reinterpret_cast<DWORD*>(net_event_struct + 0x30);
		auto amount = net_event_struct->m_ammount;
		const char* sender_name = sender->get_name();
		auto sender_id = sender->player_id;//*reinterpret_cast<int8_t*>(sender + 0x2D);
		
		if (g_settings.options["Log Player"])
			LOG(HACKER) << fmt::format("~g~Blocked Report From {} with hash {} by value {} player id {}", sender_name, hash, amount, sender->player_id);
		
		if (g_settings.options["Block Report"])
		{
			switch (hash)
			{
				case RAGE_JOAAT("MPPLY_GRIEFING"): //MPPLY_GRIEFING
				case RAGE_JOAAT("MPPLY_VC_ANNOYINGME"): //MPPLY_VC_ANNOYINGME
				case RAGE_JOAAT("MPPLY_VC_HATE"): //MPPLY_VC_HATE
				case RAGE_JOAAT("MPPLY_TC_ANNOYINGME"): //MPPLY_TC_ANNOYINGME
				case RAGE_JOAAT("MPPLY_TC_HATE"): //MPPLY_TC_HATE
				case RAGE_JOAAT("MPPLY_OFFENSIVE_LANGUAGE"): //MPPLY_OFFENSIVE_LANGUAGE
				case RAGE_JOAAT("MPPLY_OFFENSIVE_TAGPLATE"): //MPPLY_OFFENSIVE_TAGPLATE
				case RAGE_JOAAT("MPPLY_OFFENSIVE_UGC"): //MPPLY_OFFENSIVE_UGC
				case RAGE_JOAAT("MPPLY_BAD_CREW_NAME"): //MPPLY_BAD_CREW_NAME
				case RAGE_JOAAT("MPPLY_BAD_CREW_MOTTO"): //MPPLY_BAD_CREW_MOTTO
				case RAGE_JOAAT("MPPLY_BAD_CREW_STATUS"): //MPPLY_BAD_CREW_STATUS
				case RAGE_JOAAT("MPPLY_BAD_CREW_EMBLEM"): //MPPLY_BAD_CREW_EMBLEM
				case RAGE_JOAAT("MPPLY_GAME_EXPLOITS"): //MPPLY_GAME_EXPLOITS
				case RAGE_JOAAT("MPPLY_EXPLOITS"): //MPPLY_EXPLOITS
				case RAGE_JOAAT("MPPLY_FRIENDLY"):
				case RAGE_JOAAT("MPPLY_HELPFUL"):
				
				std::string stat_name = stats::get_stat_name_from_hash(hash);
				std::string sender_info = fmt::format("~g~Blocked Report From {} with stat name {} and hash {} by value {}", sender_name, stat_name, hash, amount);

				LOG(INFO) << fmt::format("Blocked Report From {} with stat name {} and hash {} by value {}", sender_name, stat_name, hash, amount);
				
				message::notification("~bold~~g~Ellohim Private Menu", sender_info.c_str(), "~bold~~g~Ellohim Menu Protection");

				if (g_settings.options["Redirect Report"])
				{
					std::string redirect_event = fmt::format("~g~Redirect Report To {} with stat name {} and hash {} by value {}", sender_name, stat_name, hash, amount);
					message::notification("Event Redirect", redirect_event.c_str(), "~bold~~g~Ellohim Menu Redirect");
					remote_event::bail_player(sender_id);
				}
				return true;
			}
		}
		return g_hooking->m_increment_event_hook.get_original<functions::IncrementEvent>()(net_event_struct, sender, receiver);
	}

	bool hooks::ClearPedTaskEvent(int64_t thisptr, CNetGamePlayer* sender, CNetGamePlayer* receiver)
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

	void hooks::RemoveWeaponEvent(int64_t thisptr, rage::datBitBuffer* buffer, CNetGamePlayer* sender, CNetGamePlayer* receiver)
	{
		const char* sender_name = sender->get_name();
		auto sender_id = sender->player_id;
		uint32_t net_id{};
		buffer->ReadDword(&net_id, 32);
		if (g_settings.options["Log Player"])
			LOG(WARNING) << "Remove Weapon Event" << " Sender : " << sender_name << " Receiver : " << receiver->get_name() << " SCID : " << sender->get_net_data()->m_rockstar_id << "Player ID : " << std::to_string(sender_id);//auto sender_id = *reinterpret_cast<uint8_t*>(sender + 0x35);
		
		char sender_info[100];
		strcpy(sender_info, "~bold~~g~Blocked Remove Weapon From ");
		strcat(sender_info, sender_name);
		if (g_settings.options["Remove Weapon Block"]) {
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
		g_hooking->m_remove_weapon_event_hook.get_original<functions::CRemoveWeaponEvent>()(thisptr, buffer, sender, receiver);
	}

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

	bool hooks::ScriptGameEvent(CScriptedGameEvent* NetEventStruct, CNetGamePlayer* sender)
	{
		auto args = NetEventStruct->m_args;//reinterpret_cast<std::int64_t*>(NetEventStruct + 0x70);
		auto sender_name = sender->get_name();//*reinterpret_cast<std::int8_t*>(CNetGamePlayer + 0x2D);
		auto ip_address = sender->get_net_data()->m_relay_ip;//uint8_t out[4]; //*(uint32_t*)&out = ip_address;
		int args_size = _ARRAYSIZE(args);//sizeof(*args) / sizeof(args[0]); //NetEventStruct->m_args_size;
		
		auto ip = fmt::format(" IP : {}.{}.{}.{}", (ip_address >> 24) & 0xff, (ip_address >> 16) & 0xff, (ip_address >> 8) & 0xff, ip_address & 0xff);
		auto sender_id = sender->player_id;//systems::get_player_id_from_name(sender_name);//CNetGamePlayer->player_id
		auto PlayerRID = sender->get_net_data()->m_rockstar_id;//player::GetPlayerRid((Player)args[1]);//CNetGamePlayer->player_info->m_rockstar_id;
		const auto EventHash = (int)args[0]; //because the event hash is the first arguement
		char sender_info[100];

		if (g_settings.options["Log Player"])
		{
			LOG(HACKER) << "ID : " << std::to_string(sender_id) << " USER SENDER : " << sender_name << " USER ID : " << std::to_string(PlayerRID).c_str() << " EVENT HASH : " << std::to_string(EventHash).c_str();
			//for (uint32_t i = 0; i <= args_size; i++)
				//LOG(HACKER) << "EVENT ARGS : " << (int)args[i] << " TOTAL_ARGS : " << args_size << ip;
		}

		switch (EventHash)
		{
		case TELEPORT_APARTMENT: //Invite
			if (g_settings.options["Block Invite Apartment"])
			{
				strcpy(sender_info, "~g~Blocked Invite Event From ");
				strcat(sender_info, sender_name);

				message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Blocked Invite Event From {} with Hash {} Args Count {}", sender_name, EventHash, args_size).c_str(), "~bold~~g~Ellohim Menu Protection");
				if (g_settings.options["Redirect Event"])
				{
					strcpy(sender_info, "~g~Redirect Event To ");
					strcat(sender_info, sender_name);
					message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Redirect Event To {} with Hash {} Args Count {}", sender_name, EventHash, args_size).c_str(), "~bold~~g~Ellohim Menu Redirect");
					//then kick player who report me
					remote_event::trigger_event(args, args_size, 1 << sender_id);
				}
				return true; //lets return true if we return false we are really only moving the event to the buffer
			}
			break;
		case TELEPORT_CAYO: //send cayo
			if (g_settings.options["Teleport Cayo Perico Block"])
			{
				message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Blocked Send To Cayo Event From {} with Hash {} Args Count {}", sender_name, EventHash, args_size).c_str(), "~bold~~g~Ellohim Menu Protection");
				if (g_settings.options["Redirect Event"])
				{
					message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Redirect Event To {} with Hash {} Args Count {}", sender_name, EventHash, args_size).c_str(), "~bold~~g~Ellohim Menu Redirect");
					//then kick player who report me
					remote_event::trigger_event(args, args_size, 1 << sender_id);
				}
				return true;
			}
			break;
		case CEO_KICK: //CEO Kick
			if (g_settings.options["CEO Kick Block"])
			{
				message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Blocked CEO Kick Event From {} with Hash {} Args Count {}", sender_name, EventHash, args_size).c_str(), "~bold~~g~Ellohim Menu Protection");
				if (g_settings.options["Redirect Event"])
				{
					message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Redirect Event To {} with Hash {} Args Count {}", sender_name, EventHash, args_size).c_str(), "~bold~~g~Ellohim Menu Redirect");
					//then kick player who report me
					remote_event::trigger_event(args, args_size, 1 << sender_id);
				}
				return true;
			}
			break;
		case CEO_BAN: //CEO Ban
			if (g_settings.options["CEO Ban Block"])
			{
				message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Blocked CEO Ban Event From {} with Hash {} Args Count {}", sender_name, EventHash, args_size).c_str(), "~bold~~g~Ellohim Menu Protection");
				if (g_settings.options["Redirect Event"])
				{
					message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Redirect Event To {} with Hash {} Args Count {}", sender_name, EventHash, args_size).c_str(), "~bold~~g~Ellohim Menu Redirect");
					//then kick player who report me
					remote_event::trigger_event(args, args_size, 1 << sender_id);
				}
				return true;
			}
			break;
		case ROTATE_CAM: //Rotete Cam
			if (g_settings.options["Rotate Cam Block"])
			{
				/*
				HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Blocked Rotete Cam");
				HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", FALSE, 0, sender_name, "~g~Ellohim Menu Protection");
				HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(true, true);
				*/
				return true;
			}
			break;
		case VEHICLE_KICK: //Vehicle Kick
			if (g_settings.options["Vehicle Kick Block"])
			{
				message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Blocked Vehicle Kick Event From {} with Hash {} Args Count {}", sender_name, EventHash, args_size).c_str(), "~bold~~g~Ellohim Menu Protection");
				if (g_settings.options["Redirect Event"])
				{
					message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Redirect Event To {} with Hash {} Args Count {}", sender_name, EventHash, args_size).c_str(), "~bold~~g~Ellohim Menu Redirect");
					//then kick player who report me
					remote_event::trigger_event(args, args_size, 1 << sender_id);
				}
				return true;
			}
			break;
		case TRANSACTION_ERROR:
			if (g_settings.options["Transaction Failed Block"])
			{
				message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Blocked Transaction failed Event From {} with Hash {} Args Count {}", sender_name, EventHash, args_size).c_str(), "~bold~~g~Ellohim Menu Protection");
				if (g_settings.options["Redirect Event"])
				{
					message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Redirect Event To {} with Hash {} Args Count {}", sender_name, EventHash, args_size).c_str(), "~bold~~g~Ellohim Menu Redirect");
					//then kick player who report me
					remote_event::trigger_event(args, args_size, 1 << sender_id);
				}
				return true;
			}
			break;
		case SEND_TO_MISSION_1:
		case SEND_TO_MISSION_2:
			if (g_settings.options["Force To Mission Block"])
			{
				message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Blocked Force Mission Event From {} with Hash {} Args Count {}", sender_name, EventHash, args_size).c_str(), "~bold~~g~Ellohim Menu Protection");
				if (g_settings.options["Redirect Event"])
				{
					message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Redirect Event To {} with Hash {} Args Count {}", sender_name, EventHash, args_size).c_str(), "~bold~~g~Ellohim Menu Redirect");
					//then kick player who report me
					remote_event::trigger_event(args, args_size, 1 << sender_id);
				}
				return true;
			}
			break;
		case PHONE_INVITE:
			if (g_settings.options["Sound Spam"])
			{
				message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Blocked Sound Spam Event From {} with Hash {} Args Count {}", sender_name, EventHash, args_size).c_str(), "~bold~~g~Ellohim Menu Protection");
				if (g_settings.options["Redirect Event"])
				{
					message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Redirect Event To {} with Hash {} Args Count {}", sender_name, EventHash, args_size).c_str(), "~bold~~g~Ellohim Menu Redirect");
					//then kick player who report me
					remote_event::trigger_event(args, args_size, 1 << sender_id);
				}
				return true;
			}
			break;
		case 515799090:
		case 1767220965:
		case 1305720168:
		case -275229102:
		case -654645351:
		case 1848973789:
		case -194543830:
		case -2063448951:
		case 797978700:
		case -176858990:
		case 1731962870:
		case 1152266822:
		case 257478565:
		case 23010443:
		case 496476216:
		case 1455421717:
		case -419415284:
		case 1358851648:
		case -525866785:
		case -1277389265:
		case -892744477:
		case 600486780:
			if (g_settings.options["Block Kick"])
			{
				return true;
			}
			break;
		case 1463355688: //Kick
		case 575344561: //Kick Host
		case -1382676328: //Kick Host
		case 1256866538: //Kick Sp
		case -1753084819: //Kick SP
		case 1119864805: //Kick
		case -1833002148: //Kick
		case -1587276086: //Kick
		case 1954846099: //Kick 1964309656
		case 1659915470://
		case -2017818728: // Kick Host
		case 27785517: // Kick Host
		case 641157117:
		case -347755611: // Kick Host
		case -137439024: // Kick Host
		case 161038699: // Kick Host
		case -1813981910:
		case 2092565704:
		case 202252150:
		case -1503282114:
		case 243981125:
		case -1836118977:
		case -169685950:
		case -2071141142:
		case -149227625:
		case 1433396036:
		case 1608876738:
		case 458875017:
		case 987018372:
		case 813647057:
		case 696123127:
			if (g_settings.options["Block Kick"])
			{
				strcpy(sender_info, "~g~Blocked Kick Event From ");
				strcat(sender_info, sender_name);
				strcat(sender_info, " with hash ");
				strcat(sender_info, std::to_string(EventHash).c_str());

				LOG(INFO_TO_FILE) << "ID : " << std::to_string(sender_id) << " USER SENDER : " << sender_name << " USER ID : " << std::to_string(PlayerRID).c_str() << " EVENT HASH : " << std::to_string(EventHash).c_str();
				message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Block Kick Event From {} SCID {} with Hash {} Args Count {}{}", sender_name, PlayerRID, EventHash, args_size, ip).c_str(), "~bold~~g~Ellohim Menu Protection");
				if (g_settings.options["Redirect Event"])
				{
					strcpy(sender_info, "~g~Redirect Event To ");
					strcat(sender_info, sender_name);
					message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Redirect Event To {} with Hash {} Args Count {}{}", sender_name, EventHash, args_size, ip).c_str(), "~bold~~g~Ellohim Menu Redirect");
					//then kick player who report me
					remote_event::trigger_event(args, args_size, 1 << sender_id);
				}
				return true;
			}
			break;
		}

		return g_hooking->m_script_event_hook.get_original<functions::ScriptGameEvent>()(NetEventStruct, sender);
	}
	
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
	
	int hooks::censor_chat_text(__int64 chat_menu, const char* user_text, const char** output_text)
	{
		if (g_settings.options["Disable Censor"].get<bool>() == false)
			return g_hooking->m_censor_chat_text_hook.get_original<decltype(&censor_chat_text)>()(chat_menu, user_text, output_text);
		return -1;
	}

	bool hooks::clone_create(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, int32_t _object_type, int32_t _object_id, int32_t _object_flag, rage::datBitBuffer* buffer, int32_t timestamp)
	{
		int32_t n = (buffer->m_maxBit + 7) >> 3;
		auto data = buffer->m_data;

		g_hook_variable.entity_id = _object_id;

		strcpy(g_hook_variable.sender_name, src->get_name());

		int16_t object_type = _object_type;
		int16_t object_id = _object_id;
		int16_t object_flag = _object_flag;

		rage::netObject* netObject = g_pointers->m_get_network_object(mgr, object_id, true);
		bool owner = netObject != nullptr;
		bool type = object_type == NetObjEntityType_Submarine || object_type == NetObjEntityType_PickupPlacement || object_type < NetObjEntityType_Automobile || object_type > NetObjEntityType_Train;
		if (g_settings.options["Log Player"])
			LOG(INFO_TO_FILE) << fmt::format("Sender : {} | Receiver : {} | Object ID : {} | Object Type : {} | Flag : {}", src->get_name(), dst->get_name(), object_id, object_type, object_flag);

		if (g_settings.options["Crash Protection"])
		{
			bool block = type || owner;
			if (block)
			{
				LOG(INFO_TO_FILE) << fmt::format("Sender : {} | Receiver : {} | Object ID : {} | Object Type : {} | Flag : {}", src->get_name(), dst->get_name(), object_id, object_type, object_flag);
				buffer->m_unkBit = buffer->m_maxBit;
				return true;
			}
		}
		return g_hooking->m_clone_create_hook.get_original<functions::clone_create_t>()(mgr, src, dst, _object_type, _object_id, _object_flag, buffer, timestamp);
	}
	
	bool hooks::sync_read_buffer(rage::netSyncTree* netSyncTree, int32_t sync_type, int32_t _sync_flag, rage::datBitBuffer* buffer, void* netLogStub)
	{
		g_hook_variable.sync_flag = _sync_flag;
		g_hook_variable.sync_type = sync_type;

		return g_hooking->m_sync_read_buffer_hook.get_original<functions::sync_read_t>()(netSyncTree, sync_type, g_hook_variable.sync_flag, buffer, netLogStub);
	}

	bool hooks::sync_can_apply(rage::netSyncTree* netSyncTree, rage::netObject* netObject)
	{
		auto ped_hash = netSyncTree->m_sync_tree_node->m_ped_model;
		auto obj_hash = netSyncTree->m_sync_tree_node->m_object_model;
		auto vehicle_hash = netSyncTree->m_sync_tree_node->m_vehicle_model;
		auto pickup_hash = netSyncTree->m_sync_tree_node->m_pickup_model;
		auto object_id = netObject->object_id;
		auto sync_tree = netSyncTree;
		auto network_object = netObject;
		
		bool object_validity = netObject->object_type > NetObjEntityType_Train && netObject->object_type < NetObjEntityType_Automobile;

		std::string name = g_hook_variable.entity_id == object_id ? g_hook_variable.sender_name : "Unknown";
		bool is_name_valid = strcmp(name.c_str(), "Unknown") == 0;

		if (g_settings.options["Log Player"])
		{
			auto vehicle_name = vehicle_helper::get_vehicle_name_from_hash(vehicle_hash);
			auto ped_name = player::get_ped_name_from_hash(ped_hash);
			auto object_name = object::get_object_name_from_hash(obj_hash);
			auto player_name = player::get_ped_name_from_hash(netSyncTree->m_sync_tree_node->m_player_model); 
			LOG(INFO_TO_FILE) << fmt::format("Sender : {} | Ped : {} | Vehicle : {} | Object : {} | Pickup : {} | Player : {} | Type : {} | Object Id : {}", name, ped_name, vehicle_name, object_name, pickup_hash, player_name, netObject->object_type, netObject->object_id);
		}
			
		if (g_settings.options["Crash Protection"])
		{
			if (object_validity || systems::is_model_valid(sync_tree, network_object) && !is_name_valid)
			{
				auto vehicle_name = vehicle_helper::get_vehicle_name_from_hash(vehicle_hash);
				auto ped_name = player::get_ped_name_from_hash(ped_hash);
				auto object_name = object::get_object_name_from_hash(obj_hash);
				auto player_name = player::get_ped_name_from_hash(netSyncTree->m_sync_tree_node->m_player_model);

				message::notification("~bold~~o~Ellohim Private Menu", fmt::format("~g~{} Try To Crash You", name).c_str(), "~bold~~g~Ellohim Menu Protection");
				LOG(INFO_TO_FILE) << fmt::format("Sender : {} | Ped : {} | Vehicle : {} | Object : {} | Pickup : {} | Player : {} | Type : {} | Object Id : {}", name, ped_name, vehicle_name, object_name, pickup_hash, player_name, netObject->object_type, netObject->object_id);
				return false;
			}
		}
		return g_hooking->m_sync_can_apply_hook.get_original<functions::sync_can_apply_t>()(netSyncTree, netObject);
	}

	static GtaThread *find_script_thread(rage::joaat_t hash)
	{
		for (auto thread : *g_pointers->m_script_threads)
		{
			if (thread
				&& thread->m_context.m_thread_id
				&& thread->m_handler
				&& thread->m_script_hash == hash)
			{
				return thread;
			}
		}
		return nullptr;
	}

	hooking::hooking() :
		m_swapchain_hook(*g_pointers->m_swapchain, hooks::swapchain_num_funcs),
		m_set_cursor_pos_hook("SetCursorPos", memory::module("user32.dll").get_export("SetCursorPos").as<void*>(), &hooks::set_cursor_pos),
		m_increment_event_hook("m_increment_event_hook", g_pointers->m_increment_event, &hooks::IncrementStatEvent),
		//m_get_event_data_hook("m_get_event_data_hook", g_pointers->m_get_event_data, &hooks::GetEventData),
		m_send_net_info_to_lobby_hook("send_net_data", g_pointers->m_send_net_info_to_lobby, &hooks::send_net_info_to_lobby),
		m_clear_ped_hook("Clear Ped Task Event", g_pointers->m_clear_ped_event, &hooks::ClearPedTaskEvent),
		m_script_event_hook("CScriptedGameEvent", g_pointers->m_script_event, &hooks::ScriptGameEvent),
		m_censor_chat_text_hook("Chat Sensor", g_pointers->m_censor_chat_text, &hooks::censor_chat_text),
		
		m_request_control_event_hook("Request Control Event", g_pointers->m_request_control_event, &hooks::RequestControlEvent),
		m_remove_weapon_event_hook("Remove Weapon Event", g_pointers->m_remove_weapon, &hooks::RemoveWeaponEvent),
		m_kick_vote_hook("Vote Kick Event", g_pointers->m_kick_vote, &hooks::KickVoteEvent),
		m_explosion_event_hook("Explosion Event", g_pointers->m_explosion_event, &hooks::ExplosionEvent),
		m_clone_create_hook("Clone Create", g_pointers->m_clone_create, &hooks::clone_create),
		m_sync_can_apply_hook("Sync Can Apply Obj", g_pointers->m_sync_can_apply, &hooks::sync_can_apply),
		m_sync_read_buffer_hook("Sync Read Buffer", g_pointers->m_sync_read, &hooks::sync_read_buffer),
		m_ptfx_event_hook("m_ptfx_event_hook", g_pointers->m_ptfx_event, &hooks::PTFXEvent),

		m_run_script_threads_hook("Script hook", g_pointers->m_run_script_threads, &hooks::run_script_threads),
		m_convert_thread_to_fiber_hook("ConvertThreadToFiber", memory::module("kernel32.dll").get_export("ConvertThreadToFiber").as<void*>(), &hooks::convert_thread_to_fiber)

	{
		m_swapchain_hook.hook(hooks::swapchain_present_index, &hooks::swapchain_present);
		m_swapchain_hook.hook(hooks::swapchain_resizebuffers_index, &hooks::swapchain_resizebuffers);

		g_hooking = this;
	}

	hooking::~hooking()
	{
		if (m_enabled)
			disable();

		g_hooking = nullptr;
	}

	void hooking::enable()
	{
		m_swapchain_hook.enable();
		m_og_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&hooks::wndproc)));
		m_set_cursor_pos_hook.enable();
		m_increment_event_hook.enable();
		m_send_net_info_to_lobby_hook.enable();
		m_censor_chat_text_hook.enable();
		//m_get_event_data_hook.enable();
		
		m_clear_ped_hook.enable();
		m_remove_weapon_event_hook.enable();
		m_request_control_event_hook.enable();
		m_kick_vote_hook.enable();
		m_explosion_event_hook.enable();
		m_ptfx_event_hook.enable();

		m_script_event_hook.enable();
		m_clone_create_hook.enable();
		m_sync_can_apply_hook.enable();
		m_sync_read_buffer_hook.enable();

		m_run_script_threads_hook.enable();
		m_convert_thread_to_fiber_hook.enable();

		m_enabled = true;
	}

	void hooking::disable()
	{
		m_enabled = false;

		m_convert_thread_to_fiber_hook.disable();
		m_run_script_threads_hook.disable();
		m_increment_event_hook.disable();
		m_send_net_info_to_lobby_hook.disable();
		m_censor_chat_text_hook.disable();
		//m_get_event_data_hook.disable();
		
		m_clear_ped_hook.disable();
		m_remove_weapon_event_hook.disable();
		m_request_control_event_hook.disable();
		m_kick_vote_hook.disable();
		m_explosion_event_hook.disable();
		m_ptfx_event_hook.disable();

		m_script_event_hook.disable();
		m_clone_create_hook.disable();
		m_sync_can_apply_hook.disable();
		m_sync_read_buffer_hook.disable();

		m_set_cursor_pos_hook.disable();
		SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_og_wndproc));
		m_swapchain_hook.disable();
	}

	minhook_keepalive::minhook_keepalive()
	{
		MH_Initialize();
	}

	minhook_keepalive::~minhook_keepalive()
	{
		MH_Uninitialize();
	}

	bool hooks::run_script_threads(std::uint32_t ops_to_execute)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{
				g_script_mgr.tick();
			}

			return g_hooking->m_run_script_threads_hook.get_original<functions::run_script_threads_t>()(ops_to_execute);
		} EXCEPT_CLAUSE
		return false;
	}

	void *hooks::convert_thread_to_fiber(void *param)
	{
		TRY_CLAUSE
		{
			if (IsThreadAFiber())
			{
				return GetCurrentFiber();
			}

			return g_hooking->m_convert_thread_to_fiber_hook.get_original<decltype(&convert_thread_to_fiber)>()(param);
		} EXCEPT_CLAUSE
		return nullptr;
	}

	HRESULT hooks::swapchain_present(IDXGISwapChain *this_, UINT sync_interval, UINT flags)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{
				g_renderer->on_present();
			}

			return g_hooking->m_swapchain_hook.get_original<decltype(&swapchain_present)>(swapchain_present_index)(this_, sync_interval, flags);
		} EXCEPT_CLAUSE
		return NULL;
	}

	HRESULT hooks::swapchain_resizebuffers(IDXGISwapChain * this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{
				g_renderer->pre_reset();

				auto result = g_hooking->m_swapchain_hook.get_original<decltype(&swapchain_resizebuffers)>(swapchain_resizebuffers_index)
					(this_, buffer_count, width, height, new_format, swapchain_flags);

				if (SUCCEEDED(result))
				{
					g_renderer->post_reset();
				}

				return result;
			}

			return g_hooking->m_swapchain_hook.get_original<decltype(&swapchain_resizebuffers)>(swapchain_resizebuffers_index)
				(this_, buffer_count, width, height, new_format, swapchain_flags);
		} EXCEPT_CLAUSE
		return NULL;
	}

	LRESULT hooks::wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{
				g_renderer->wndproc(hwnd, msg, wparam, lparam);
			}

			return CallWindowProcW(g_hooking->m_og_wndproc, hwnd, msg, wparam, lparam);
		} EXCEPT_CLAUSE
		return NULL;
	}

	BOOL hooks::set_cursor_pos(int x, int y)
	{
		TRY_CLAUSE
		{
			if (g_gui.m_opened)
				return true;

			return g_hooking->m_set_cursor_pos_hook.get_original<decltype(&set_cursor_pos)>()(x, y);
		} EXCEPT_CLAUSE
		return FALSE;
	}
}
