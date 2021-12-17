#pragma once
#include "gta/net_game_event.hpp"
#include "gta/enums.hpp"
#include "gui/helper_function.hpp"
#include "gta_util.hpp"

namespace big::hook_helper
{
	inline bool report_status(CNetworkIncrementStatEvent *net_event_struct, CNetGamePlayer* sender, CNetGamePlayer* receiver)
	{
		auto hash = net_event_struct->m_stat;
		auto amount = net_event_struct->m_ammount;
		const char* sender_name = sender->get_name();
		auto sender_id = sender->player_id;
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

				LOG(HACKER) << fmt::format("Blocked Report From {} with stat name {} and hash {} by value {}", sender_name, stat_name, hash, amount);

				message::notification("~bold~~g~Ellohim Private Menu", sender_info.c_str(), "~bold~~g~Ellohim Menu Received Event");
				if (g_settings.options["Redirect Report"])
				{
					std::string redirect_event = fmt::format("~g~Redirect Report To {} with stat name {} and hash {} by value {}", sender_name, stat_name, hash, amount);
					message::notification("Event Redirect", redirect_event.c_str(), "~bold~~g~Ellohim Menu Redirect");
					g_pointers->m_increment_event(net_event_struct, receiver, sender);
					remote_event::bail_player(sender_id);
				}
				return true;
			}
		}
		return false;
	}

	inline bool validate_game_event(CScriptedGameEvent* net_event_struct, CNetGamePlayer* sender, CNetGamePlayer* receiver)
	{
		auto args = net_event_struct->m_args;
		auto sender_name = sender->get_name();
		auto ip_address = sender->get_net_data()->m_relay_ip;
		int args_size = net_event_struct->m_args_size;

		auto ip = fmt::format(" IP : {}.{}.{}.{}", (ip_address >> 24) & 0xff, (ip_address >> 16) & 0xff, (ip_address >> 8) & 0xff, ip_address & 0xff);
		auto sender_id = sender->player_id;
		auto PlayerRID = sender->get_net_data()->m_rockstar_id;
		const auto EventHash = (int)args[0]; 
		char sender_info[100];
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
		case BAIL_NETWORK:
			if (g_settings.options["Block Kick"])
			{
				strcpy(sender_info, "~g~Blocked Kick Event From ");
				strcat(sender_info, sender_name);
				strcat(sender_info, " with hash ");
				strcat(sender_info, std::to_string(EventHash).c_str());
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
		case -1308840134:
		case 1767220965:
		case -227800145:
		case -399817245:
		case -102469555:
		case -903578754:
		case -83272757:
		case -33103987:
		case -1055758293:
		case 1763436095:
		case -1071325787:
		case 1890277845:
		case -1887269275:
		case 1658337260:
		case 985284033:
		case -943413695:
		case 703680251:
		case 389634423:
		case -211216577:
		case 1836137561:
		case -737858645:
		case -1991317864:
			if (g_settings.options["Block Kick"])
			{
				strcpy(sender_info, "~g~Blocked Kick Event From ");
				strcat(sender_info, sender_name);
				strcat(sender_info, " with hash ");
				strcat(sender_info, std::to_string(EventHash).c_str());
			}
			break;
		case -1970125962: //Kick
		case 69874647: //Kick Host
		case 998716537: //Kick Host
		case 163598572: //Kick Sp
		case 924535804: //Kick SP
		case -1767058336: //Kick
		case 927169576: //Kick
		case -145306724: //Kick
		case 614457627: //Kick 1964309656
		case 1572255940://
		case -1892343528: // Kick Host
		case 1494472464: // Kick Host
		case 1189947075:
		case 1445703181: // Kick Host
		case -225522261: // Kick Host
		case 1481806247: // Kick Host
		case -1501164935:
		case 436475575:
		case 990606644:
		case 1498409190:
		case 526046459:
		case 1902624891:
		case 844746317:
		case -330288802:
		case -581037897:
		case 2002459655:
		case -569621836:
		case -1208585385:
		case 813647057:
		case 1757755807:
		case 677240627:
		case 2112408256:
		case -1386010354:
		case 962740265:
		case -368423380:
		case -290218924:
		case -614457627:
		case -1125867895:
		case 1246667869:
			if (g_settings.options["Block Kick"])
			{
				strcpy(sender_info, "~g~Blocked Kick Event From ");
				strcat(sender_info, sender_name);
				strcat(sender_info, " with hash ");
				strcat(sender_info, std::to_string(EventHash).c_str());

				LOG(INFO_TO_FILE) << "ID : " << std::to_string(sender_id) << " USER SENDER : " << sender_name << " USER ID : " << std::to_string(PlayerRID).c_str() << " EVENT HASH : " << std::to_string(EventHash).c_str();
				message::notification("~bold~~g~Ellohim Private Menu", fmt::format("~g~Block Kick Event From {} SCID {} with Hash {} Args Count {}{}", sender_name, PlayerRID, EventHash, args_size, ip).c_str(), "~bold~~g~Ellohim Menu Protection");
				
			}
			break;
		}
		return false;
	}
}
//cari di bintaro rs dr suyoto di jl. veteran 
//nantitelpon ibu soenarjati
//