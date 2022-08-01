#include "hooking.hpp"
#include "natives.hpp"
#include <gui/window/imgui_notify.h>
#include <gui/controller/xostr.h>

namespace big
{
	struct chatmessage 
	{
		std::string_view message;
		int64_t player_peerId;
		int network_time;
	};

	std::vector<chatmessage> all_messages;
	std::vector<int64_t> blocked_players;

	__int64* hooks::chat_receive(__int64 chat_pointer, __int64 unk2, __int64 peerId, const char* msg, char IsTeam)
	{
		//Block if the player has already been detected by spamming
		for (auto player : blocked_players) if (player == peerId) return nullptr;

		//Add the message to the list
		all_messages.push_back({ msg, peerId, NETWORK::GET_NETWORK_TIME() });

		chatmessage previousmessage{};
		int messagecounter = NULL;

		//Check whether the same player has been sending messages in intervals less than 1 second
		for (auto msg : all_messages) 
		{
			if (!previousmessage.message.empty() && msg.player_peerId == previousmessage.player_peerId)
				if (msg.network_time - previousmessage.network_time <= 1000) messagecounter++;
			previousmessage = msg;
		}

		if (messagecounter >= 3) 
		{
			ImGui::InsertNotification({ ImGuiToastType_Ellohim, 7000, xorstr("Chat is being spammed, adding spammer to list") });
			blocked_players.push_back(peerId);
			return nullptr;
		}

		//return g_hooking->m_chat_receive_hook.get_original<decltype(&chat_receive)>()(chat_pointer, unk2, peerId, msg, IsTeam);
	}
}