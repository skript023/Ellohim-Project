#include "hooking.hpp"

namespace big
{
	const char* hooks::get_label_text(void* unk, const char* label)
	{
		if (g_running)
			switch (rage::joaat(label))
			{
			case RAGE_JOAAT("HUD_JOINING"):
			case RAGE_JOAAT("HUD_TRANSP"):

				return "You're Using Wuhan Mod Menu";
			}
		return g_hooking->m_get_label_text.get_original<decltype(&hooks::get_label_text)>()(unk, label);
	}
}