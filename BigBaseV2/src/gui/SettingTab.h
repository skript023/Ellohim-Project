#pragma once
#include "common.hpp"

namespace big
{
	class setting_tab
	{
	public:
		static void render_setting_tab();
		static void set_clipboard(const char* message);
	};
}