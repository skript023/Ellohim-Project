#include "hooking.hpp"
#include "gui/player_list.h"
#include "gta/net_game_event.hpp"
#include "gta/net_object_mgr.hpp"
#include "gui/helper_function.hpp"

namespace big
{
	int hooks::censor_chat_text(__int64 chat_menu, const char* user_text, const char** output_text)
	{
		if (g_settings.options["Disable Censor"].get<bool>() == false)
			return g_hooking->m_censor_chat_text_hook.get_original<decltype(&censor_chat_text)>()(chat_menu, user_text, output_text);
		return -1;
	}

}