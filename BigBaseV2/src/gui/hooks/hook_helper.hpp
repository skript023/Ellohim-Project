#pragma once
#include "gta/net_game_event.hpp"
#include "gta/enums.hpp"
#include "gui/helper_function.hpp"
#include "gta_util.hpp"
#include "gta/net_game_event.hpp"
#include "rage_internal_packet.hpp"

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

				ImGui::InsertNotification({ ImGuiToastType_ReportBlock, 15999, "Blocked Report From %s with stat name %s by value %d", sender_name, stat_name, amount });
				if (g_settings.options["Redirect Report"])
				{
					ImGui::InsertNotification({ ImGuiToastType_ReportBlock, 15999, "Redirect Report To %s with stat name %s by value %d", sender_name, stat_name, amount });
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
		int args_size = net_event_struct->m_args_size;

		auto ip = player::get_player_ip(sender->player_id);
		auto sender_id = sender->player_id;
		auto PlayerRID = sender->get_net_data()->m_rockstar_id;
		const auto event_hash = (int)args[0]; 
		char sender_info[100];
		switch (event_hash)
		{
		case TELEPORT_APARTMENT: //Invite
			if (g_settings.options["Block Invite Apartment"])
			{
				strcpy(sender_info, "~g~Blocked Invite Event From ");
				strcat(sender_info, sender_name);

				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Blocked Invite Event From %s with Hash %d Args Count %d", sender_name, event_hash, args_size });
				if (g_settings.options["Redirect Event"])
				{
					strcpy(sender_info, "~g~Redirect Event To ");
					strcat(sender_info, sender_name);
					ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Redirect Invite Event To %s with Hash %d Args Count %d", sender_name, event_hash, args_size });
					//then kick player who report me
					remote_event::trigger_event(args, args_size, 1 << sender_id);
				}
				return true; //lets return true if we return false we are really only moving the event to the buffer
			}
			break;
		case TELEPORT_CAYO: //send cayo
			if (g_settings.options["Teleport Cayo Perico Block"])
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Blocked Send To Cayo From %s with Hash %d Args Count %d", sender_name, event_hash, args_size });
				if (g_settings.options["Redirect Event"])
				{
					ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Redirect Send To Cayo To %s with Hash %d Args Count %d", sender_name, event_hash, args_size });
					//then kick player who report me
					remote_event::trigger_event(args, args_size, 1 << sender_id);
				}
				return true;
			}
			break;
		case CEO_KICK: //CEO Kick
			if (g_settings.options["CEO Kick Block"])
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Blocked CEO Kick Event From %s with Hash %d Args Count %d", sender_name, event_hash, args_size });
				if (g_settings.options["Redirect Event"])
				{
					ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Redirect CEO Kick Event To %s with Hash %d Args Count %d", sender_name, event_hash, args_size });
					//then kick player who report me
					remote_event::trigger_event(args, args_size, 1 << sender_id);
				}
				return true;
			}
			break;
		case CEO_BAN: //CEO Ban
			if (g_settings.options["CEO Ban Block"])
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Blocked CEO Ban Event From %s with Hash %d Args Count %d", sender_name, event_hash, args_size });
				if (g_settings.options["Redirect Event"])
				{
					ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Redirect CEO Ban Event To %s with Hash %d Args Count %d", sender_name, event_hash, args_size });
					//then kick player who report me
					remote_event::trigger_event(args, args_size, 1 << sender_id);
				}
				return true;
			}
			break;
		case ROTATE_CAM: //Rotete Cam
			if (g_settings.options["Rotate Cam Block"])
			{
				
				return true;
			}
			break;
		case VEHICLE_KICK: //Vehicle Kick
			if (g_settings.options["Vehicle Kick Block"])
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Blocked Vehicle Kick Event From %s with Hash %d Args Count %d", sender_name, event_hash, args_size });
				if (g_settings.options["Redirect Event"])
				{
					ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Redirect Vehicle Kick Event To %s with Hash %d Args Count %d", sender_name, event_hash, args_size });
					//then kick player who report me
					remote_event::trigger_event(args, args_size, 1 << sender_id);
				}
				return true;
			}
			break;
		case TRANSACTION_ERROR:
			if (g_settings.options["Transaction Failed Block"])
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Blocked Transaction failed Event From %s with Hash %d Args Count %d", sender_name, event_hash, args_size });
				if (g_settings.options["Redirect Event"])
				{
					ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Redirect Transaction failed Event To %s with Hash %d Args Count %d", sender_name, event_hash, args_size });
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
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Blocked Force Mission Event From %s with Hash %d Args Count %d", sender_name, event_hash, args_size });
				if (g_settings.options["Redirect Event"])
				{
					ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Redirect Force Mission Event To %s with Hash %d Args Count %d", sender_name, event_hash, args_size });
					//then kick player who report me
					remote_event::trigger_event(args, args_size, 1 << sender_id);
				}
				return true;
			}
			break;
		case PHONE_INVITE:
			if (g_settings.options["Sound Spam"])
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Blocked Sound Spam Event From %s with Hash %d Args Count %d", sender_name, event_hash, args_size });
				if (g_settings.options["Redirect Event"])
				{
					ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Blocked Sound Spam Event To %s with Hash %d Args Count %d", sender_name, event_hash, args_size });
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
				strcat(sender_info, std::to_string(event_hash).c_str());
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Blocked Network Bail Event From %s with Hash %d Args Count %d", sender_name, event_hash, args_size });
				if (g_settings.options["Redirect Event"])
				{
					strcpy(sender_info, "~g~Redirect Event To ");
					strcat(sender_info, sender_name);
					ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Redirect Network Bail Event To %s with Hash %d Args Count %d", sender_name, event_hash, args_size });
					//then kick player who report me
					remote_event::trigger_event(args, args_size, 1 << sender_id);
				}
				return true;
			}
			break;
		case SEND_TO_LOCATION:
		{
			bool known_location = false;

			if (args[2] == 0 && args[3] == 0)
			{
				if (args[4] == 4 && args[5] == 0)
				{
					known_location = true;

					if (true)
					{
						ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Send to Beach by %s", sender_name });

						return true;
					}
				}
				else if ((args[4] == 3 || args[4] == 4) && args[5] == 1)
				{
					known_location = true;

					if (true)
					{
						ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Send to Cayo Perico", sender_name });

						return true;
					}
				}
			}

			if (!known_location)
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "TSE Freeze", sender_name });

				return true;
			}
			break;
		}
		case Unknown1:
			if (g_settings.options["Crash Protection"] && args[2] >= 32)
			{
				
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "%s Crash - #%s", sender_name, std::to_string(args[0]) });

				return true;
			}
			break;
		case Unknown2:
			if (g_settings.options["Crash Protection"] && (args[2] >= 62 || args[3] >= 32))
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "%s Crash - #%s", sender_name, std::to_string(args[0]) });

				return true;
			}
			break;
		case Unknown3:
			if (g_settings.options["Crash Protection"] && args[2] >= 62)
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "%s Crash - #%s", sender_name, std::to_string(args[0]) });

				return true;
			}
			break;
		case Unknown4:
		case Crash:
		case Unknown5:
			if (g_settings.options["Crash Protection"] && args[2] >= 20)
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "%s Crash - #%s", sender_name, std::to_string(args[0]) });

				return true;
			}
			break;
		case Unknown6:
			if (g_settings.options["Crash Protection"]) 
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "%s Crash - #%s", sender_name, std::to_string(args[0]) });

				return true;
			}
			break;
		case SEC3:
			if (
				g_settings.options["Crash Protection"] &&
				(
					(args[2] <= 115831 || args[2] >= 9999449) ||
					(args[3] <= -1 || args[3] >= 1) ||
					(args[4] <= -1 || args[4] >= 3) ||
					(args[5] <= -1 || args[5] >= 101) ||
					(args[6] <= -1 || args[6] >= 3) ||
					(args[7] <= -1 || args[7] >= 1)
					)
				)
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "%s Crash - #%s", sender_name, std::to_string(args[0]) });

				return true;
			}
			break;
		case SEC6:
			if (
				g_settings.options["Crash Protection"] &&
				(
					(args[2] <= -1 || args[2] >= 1) ||
					(args[3] <= -2 || args[3] >= 0) ||
					(args[4] <= 3 || args[4] >= 5) ||
					(args[5] <= 172 || args[5] >= 174) ||
					(args[6] <= 20 || args[6] >= 510) ||
					(args[7] <= 62 || args[7] >= 64) ||
					(args[11] <= -1 || args[11] >= 1) ||
					(args[12] <= -1 || args[12] >= 1) ||
					(args[13] <= -1 || args[13] >= 1)
					)
				)
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "%s Crash - #%s", sender_name, std::to_string(args[0]) });

				return true;
			}
			break;
		case SEC7:
			if (g_settings.options["Crash Protection"])
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "%s Crash - #%s", sender_name, std::to_string(args[0]) });

				return true;
			}
			break;
		case SEC8:
			if (g_settings.options["Crash Protection"])
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "%s Crash - #%s", sender_name, std::to_string(args[0]) });

				return true;
			}
			break;
		case SEC9:
			if (
				g_settings.options["Crash Protection"] &&
				(
					(args[2] <= -1986324736 || args[2] >= 1747413822) ||
					(args[2] > -9999999 || args[2] < 77777777) ||
					(args[3] <= -1986324736 || args[3] >= 1777712108) ||
					(args[3] > -9999999 || args[3] < 77777777) ||
					(args[4] <= -1673857408 || args[4] >= 1780088064) ||
					(args[4] > -9999999 || args[4] < 77777777) ||
					(args[6] <= (0LL - 2588888790LL) || args[6] >= 2100146067)
					)
				) 
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "%s Crash - #%s", sender_name, std::to_string(args[0]) });

				return true;
			}
			break;
		case SEC10:
			if (g_settings.options["Crash Protection"])
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "%s Crash - #%s", sender_name, std::to_string(args[0]) });

				return true;
			}
			break;
		case SEC11:
			if (g_settings.options["Crash Protection"]) 
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "%s Crash - #%s", sender_name, std::to_string(args[0]) });

				return true;
			}
			break;
		case SEC12:
			if (
				g_settings.options["Crash Protection"] &&
				(
					(args[2] <= -1 || args[2] >= 50) ||
					(args[3] <= -1 || args[3] >= 50)
					)
				)
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "%s Crash - #%s", sender_name, std::to_string(args[0]) });

				return true;
			}
			break;
		case SEC13:
			if (g_settings.options["Crash Protection"])
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "%s Crash - #%s", sender_name, std::to_string(args[0]) });

				return true;
			}
			break;
		case Spaghettios:
			if (g_settings.options["Crash Protection"])
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "%s Crash - #%s", sender_name, std::to_string(args[0]) });

				return true;
			}
			break;
		}
		return false;
	}

	// 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8A 42 1C 40 32 FF 48 8B DA 48 8B F1
	inline bool get_message_type(MessageType& msg_type, rage::datBitBuffer& buffer)
	{
		uint32_t pos;
		uint32_t magic;
		uint32_t length;
		uint32_t extended{};
		if ((buffer.m_flagBits & 2) != 0 || (buffer.m_flagBits & 1) == 0 ? (pos = buffer.m_curBit) : (pos = buffer.m_maxBit),
			buffer.m_curBit + 15 > pos || !buffer.ReadDword(&magic, 14) || magic != 0x3246 || !buffer.ReadDword(&extended, 1))
		{
			msg_type = MessageType::MsgInvalid;
			return false;
		}

		length = extended ? 16 : 8;

		if ((buffer.m_flagBits & 1) == 0 ? (pos = buffer.m_curBit) : (pos = buffer.m_maxBit), length + buffer.m_curBit <= pos && buffer.ReadDword((uint32_t*)&msg_type, length))
			return true;
		else
			return false;
	}

	inline CNetGamePlayer* get_player_by_msg_id(uint32_t msg_id)
	{
		for (int i = 0; i <= MAX_PLAYERS; i++)
		{
			if (auto net_player = rage_helper::get_net_player(i))
			{
				if (net_player->m_msg_id == msg_id)
				{
					return net_player;
				}
			}
		}

		return nullptr;
	}
}
//cari di bintaro rs dr suyoto di jl. veteran 
//nantitelpon ibu soenarjati
//

/*
		case KICK_1:
		case KICK_2:
		case KICK_3:
		case KICK_4:
		case KICK_5:
		case KICK_6:
		case KICK_7:
		case KICK_8:
		case KICK_9:
		case KICK_10:
		case KICK_11:
		case KICK_12:
		case KICK_13:
		case KICK_14:
		case KICK_15:
		case KICK_16:
		case KICK_17:
		case KICK_18:
		case KICK_19:
		case KICK_20:
		case KICK_21:
		case KICK_22:
			if (g_settings.options["Block Kick"])
			{
				strcpy(sender_info, "~g~Blocked Kick Event From ");
				strcat(sender_info, sender_name);
				strcat(sender_info, " with hash ");
				strcat(sender_info, std::to_string(event_hash).c_str());
			}
			break;
		*/
		/*
		case KICK_23:
		case KICK_24:
		case KICK_25:
		case KICK_26:
		case KICK_27:
		case KICK_28:
		case KICK_29:
		case KICK_30:
		case KICK_31:
		case KICK_32:
		case KICK_33:
		case KICK_34:
		case KICK_35:
		case KICK_36:
		case KICK_37:
		case KICK_38:
		case KICK_39:
		case KICK_40:
		case KICK_41:
		case KICK_42:
		case KICK_43:
		case KICK_44:
		case KICK_45:
		case KICK_46:
		case KICK_47:
		case KICK_48:
		case KICK_49:
		case KICK_50:
		case KICK_51:
		case KICK_52:
		case KICK_53:
		case KICK_54:
		case KICK_55:
		case KICK_56:
		case KICK_57:
		case KICK_58:
		case KICK_59:
		case KICK_60:
		case KICK_61:
			if (g_settings.options["Block Kick"])
			{
				strcpy(sender_info, "~g~Blocked Kick Event From ");
				strcat(sender_info, sender_name);
				strcat(sender_info, " with hash ");
				strcat(sender_info, std::to_string(event_hash).c_str());

				//LOG(INFO_TO_FILE) << "ID : " << std::to_string(sender_id) << " USER SENDER : " << sender_name << " USER ID : " << std::to_string(PlayerRID).c_str() << " EVENT HASH : " << std::to_string(event_hash).c_str();
				//ImGui::InsertNotification({ ImGuiToastType_Protection, 5999, "Blocked Kick Event Event From %s with Hash %d Args Count %d", sender_name, event_hash, args_size });

			}
			break;
		*/