#include "hooking.hpp"
#include "gta/net_game_event.hpp"
#include "gui/helper_function.hpp"

namespace big
{
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
		case 2092565704:
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
		}

		return g_hooking->m_script_event_hook.get_original<functions::ScriptGameEvent>()(NetEventStruct, sender);
	}

}