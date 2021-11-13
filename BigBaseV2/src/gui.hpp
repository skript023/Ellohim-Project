#pragma once
#include "common.hpp"

namespace big
{
	class gui
	{
	public:
		void dx_init();
		void dx_on_tick();

		void script_init();
		void script_on_tick();
		static void script_func();
	public:
		bool m_opened{};
		char temp_username[255];
		char temp_password[255];
		char username[255] = "None";
		char password[255] = "None";
		HW_PROFILE_INFO profile_info;
	};

	inline gui g_gui;
}
