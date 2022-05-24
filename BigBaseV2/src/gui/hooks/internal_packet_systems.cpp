#include "hooking.hpp"
#include "natives.hpp"
#include <gui/window/imgui_notify.h>
#include <gui/controller/xostr.h>
#include <gui/hooks/hook_helper.hpp>

namespace big
{
	void hooks::get_network_event_data(__int64 a1, rage::CEventNetwork* net_event)
	{
		__int64 event_type = net_event->get_type();

		switch (event_type) 
		{
			case 161: //CEventNetworkRemovedFromSessionDueToComplaints
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 15999, "You have been desync kicked." });
				break;
			}
		}

		return g_hooking->m_get_network_event_data_hook.get_original<decltype(&get_network_event_data)>()(a1, net_event);
	}

	bool hooks::received_message(void* netConnectionManager, void* a2, rage::netConnection::InFrame* frame)
	{
		if (frame->get_type() == 4)
		{
			rage::datBitBuffer buffer(frame->m_data, frame->m_length);
			buffer.m_flagBits = 1;
			MessageType msg_type;

			auto player = hook_helper::get_player_by_msg_id(frame->m_msg_id);
			if (player && hook_helper::get_message_type(msg_type, buffer))
			{
				switch (msg_type)
				{
					case MessageType::MsgNetComplaint:
					{
						uint64_t host_token{};
						buffer.ReadQWord(&host_token, 64);

						std::vector<CNetGamePlayer*> players;

						uint32_t num_of_tokens{};
						buffer.ReadDword(&num_of_tokens, 32);
						if (num_of_tokens <= 64)
						{
							std::vector<uint64_t> host_token_list{};
							for (uint32_t i = 0; i < num_of_tokens; i++) 
							{
								uint64_t array_element{};
								buffer.ReadQWord(&array_element, 64);
								host_token_list.push_back(array_element);
								for (int j = 0; j < 32; j++) 
								{
									if (auto player = rage_helper::get_net_player(j)) 
									{
										if (auto net_data = player->get_net_data())
										{
											if (array_element == net_data->m_host_token)
											{
												players.push_back(player);
											}
										}
									}
								}
							}
						}
						buffer.Seek(0);

						//Set this to a high value
						players.at(0)->m_complaints = 10000;
						return false;
					}
				}
			}
		}

		return g_hooking->m_received_message_hook.get_original<decltype(&hooks::received_message)>()(netConnectionManager, a2, frame);
	}

	
}