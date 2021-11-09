#include "hooking.hpp"

namespace big
{
	int hooks::censor_chat_text(__int64 chat_menu, const char* user_text, const char** output_text)
	{
		if (g_settings.options["Disable Censor"].get<bool>() == false)
			return g_hooking->m_censor_chat_text_hook.get_original<decltype(&censor_chat_text)>()(chat_menu, user_text, output_text);
		return -1;
	}

}