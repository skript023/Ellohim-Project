#include "gta/net_game_event.hpp"
#include "gta/enums.hpp"
#include "gui/helper_function.hpp"
#include "gta_util.hpp"
#include "hooking.hpp"
#include "hook_helper.hpp"
#include "gta/net_object_mgr.hpp"

namespace big
{
	bool hooks::received_event(rage::netEventMgr* event_manager,CNetGamePlayer* source_player,CNetGamePlayer* target_player,uint16_t event_id,int event_index,int event_handled_bitset,int64_t bit_buffer_size,rage::datBitBuffer* buffer)
	{
		if (event_id > 90u) return false;

		const char* event_name = *(char**)((DWORD64)event_manager + 8i64 * event_id + 243376);
		if (event_name == nullptr || source_player == nullptr || source_player->player_id < 0 || source_player->player_id >= 32)
		{
			g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
			return false;
		}

		switch (event_id)
		{
			case SCRIPTED_GAME_EVENT:
			{
				//** Instansiasi Class CScriptedGameEvent
				auto game_event = CScriptedGameEvent();
				//** Mengambil total argument dari script event
				buffer->ReadDword(&game_event.m_args_size, 32);
				//** Pengecheckan jumlah argument dalam event lalu mengambil array yang berisikan argument
				if (game_event.m_args_size <= 0x1AF)
					buffer->ReadArray(&game_event.m_args, 8 * game_event.m_args_size);

				//** Melakukan pengecekan event Hash, apabila event dari para bangsat maka block
				if (hook_helper::validate_game_event(&game_event, source_player, target_player))
				{
					//** Block Event Sepeti Kick, CEO Kick, CEO Ban dan semacamnya
					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return false;
				}
				buffer->Seek(0);
				break;
			}
			case NETWORK_INCREMENT_STAT_EVENT:
			{
				//** Instansiasi Class
				auto event_obj = CNetworkIncrementStatEvent();
				//** Mengambil stat report ke dalam class
				buffer->ReadDword(&event_obj.m_stat, 32); 
				//** mengambil jumlah report yang dikirim oleh modder
				buffer->ReadDword(&event_obj.m_ammount, 32); 
				//** Melakukan pengecekan stat, apabila stat report maka block
				if (hook_helper::report_status(&event_obj, source_player, target_player)) //
				{
					//** Block Report dari pada bangsat
					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return false;
				}
				//** Menghapus Buffer dan biarkan event berjalan
				buffer->Seek(0);
				break;
			}
			case NETWORK_CLEAR_PED_TASKS_EVENT:
			{
				if (source_player->player_id < 32)
				{
					uint16_t network_id{};
					buffer->ReadWord(&network_id, 0xD);
					if (!g_local.is_cutscene_playing && (!(g_local.is_activity_session && rage_helper::get_local_vehicle()->m_model_info->m_model_hash == VEHICLE_PBUS)))
					{
						if (g_settings.options["Clear Ped Task Block"])
						{
							ImGui::InsertNotification({ ImGuiToastType_Protection, 4000, "Blocked Clear Ped Task From %s", source_player->get_name() });
							g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

							return false;
						}
					}
					buffer->Seek(0);
				}

				break;
			}
			case REMOVE_WEAPON_EVENT:
			{
				uint16_t network_id{};
				buffer->ReadWord(&network_id, 0xD);
				if (g_settings.options["Remove Weapon Block"])
				{
					ImGui::InsertNotification({ ImGuiToastType_Protection, 4000, "Blocked Remove Weapon From %s", source_player->get_name() });
					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return false;
				}
				buffer->Seek(0);
				break;
			}
			// Don't block this event, we still want to report this player
			// because if we still report others, our account seems less fishy
			case REPORT_CASH_SPAWN_EVENT:
			{
				uint32_t money;

				buffer->Seek(64);
				buffer->ReadDword(&money, 32);
				buffer->Seek(0);

				if (money >= 2000)
				{
					ImGui::InsertNotification({ ImGuiToastType_Protection, 4000, "%s is spawning cash", source_player->get_name() });
				}

				break;
			}
			// player sending this event is a modder
			case NETWORK_CHECK_CODE_CRCS_EVENT:
			case REPORT_MYSELF_EVENT:
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 4000, "%s flagged as cheater", source_player->get_name() });
				break;
			}
			case REQUEST_CONTROL_EVENT:
			{
				if (g_settings.options["Request Control Block"])
				{
					uint16_t network_id{};
					buffer->ReadWord(&network_id, 0xD);
					if (player::is_player_driver(g_local.ped))
					{
						ImGui::InsertNotification({ ImGuiToastType_Protection, 3000, "Blocked Request Control From %s", source_player->get_name() });

						g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
						return false;
					}
					buffer->Seek(0);
				}
				break;
			}
			case KICK_VOTES_EVENT:
			{
				uint32_t bitset{};
				buffer->ReadDword(&bitset, MAX_PLAYERS);
				if (g_settings.options["Kick Vote Block"])
				{
					if (bitset & (1 << target_player->player_id))
					{
						ImGui::InsertNotification({ ImGuiToastType_Protection, 10000, "Blocked Vote Kick From %s", source_player->get_name() });
						remote_event::bail_player(source_player->player_id);
						g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
						return false;
					}
				}
				buffer->Seek(0);
				break;
			}
			case EXPLOSION_EVENT:
			{
				uint16_t explosion_owner{};
				uint32_t explosion_flags{};
				int32_t explosion_type{};
				buffer->Seek(29);
				buffer->ReadWord(&explosion_owner, 13);
				buffer->Seek(55);
				buffer->ReadInt32(&explosion_type, 8);
				buffer->Seek(149);
				buffer->ReadDword(&explosion_flags, 32);
				auto ped_owner_id = -1;
				if (auto net_obj = (*g_pointers->m_network_object_manager)->find_object_by_id(explosion_owner, false))
					ped_owner_id = net_obj->owner_id;
				if ((explosion_flags & 11) && (source_player->player_id != ped_owner_id) && ped_owner_id != -1)
				{
					if (g_settings.options["Explosion Event Block"])
					{
						ImGui::InsertNotification({ ImGuiToastType_Protection, 4000, "Blocked Explosion Event From %s", source_player->get_name() });
						g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
						return false;
					}
				}
				buffer->Seek(0);
				break;
			}
			case NETWORK_PTFX_EVENT:
			{
				uint16_t network_id{};
				buffer->ReadWord(&network_id, 0xD);
				if (g_settings.options["PTFX Event Block"])
				{
					ImGui::InsertNotification({ ImGuiToastType_Protection, 4000, "Blocked PTFX Event From %s", source_player->get_name() });
					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return false;
				}
				buffer->Seek(0);
				break;
			}
			case SCRIPT_ENTITY_STATE_CHANGE_EVENT:
			{
				uint16_t entity; buffer->ReadWord(&entity, 13);
				uint32_t type; buffer->ReadDword(&type, 4);
				uint32_t unk; buffer->ReadDword(&unk, 32);
				buffer->Seek(0);

				if (type == 6) 
				{

					g_pointers->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

					return false;
				}
				break;
			}
		}
		return g_hooking->m_received_event_hook.get_original<decltype(&received_event)>()(event_manager, source_player, target_player, event_id, event_index, event_handled_bitset, bit_buffer_size, buffer);
	}
}