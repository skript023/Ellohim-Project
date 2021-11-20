#include "game_window.hpp"
#include "gui.hpp"
#include "pointers.hpp"
#include "imgui.h"
#include "gta_util.hpp"

//Gui Tab Renderer
#include "gui/player_list.h"
#include "gui/vehicle_menu.h"
#include "gui/setting_menu.h"
#include "gui/online_menu.h"
#include "gui/player_menu.h"
#include "gui/vehicle_customize.h"
#include "gui\controller\xostr.h"

namespace big
{
	bool game_window::check_license(uint64_t license)
	{
		switch (rage::joaat(std::to_string(license) + "-PREMIUM_EDITION"))
		{
		case RAGE_JOAAT("199227111-PREMIUM_EDITION"):
		case RAGE_JOAAT("160920790-PREMIUM_EDITION"):
		case RAGE_JOAAT("148443584-PREMIUM_EDITION"):
		case RAGE_JOAAT("196561748-PREMIUM_EDITION"):
		case RAGE_JOAAT("96098918-PREMIUM_EDITION"):
		case RAGE_JOAAT("176139389-PREMIUM_EDITION"):
		case RAGE_JOAAT("156127327-PREMIUM_EDITION"):
			return true;
		default:
			if (rage::joaat(std::to_string(license) + "-FREE_EDITION") == RAGE_JOAAT("170730888-FREE_EDITION") || rage::joaat(std::to_string(license) + "-FREE_EDITION") == RAGE_JOAAT("140834687-FREE_EDITION"))
			{
				return true;
			}
			return false;
		}
	}

	void game_window::render_base_window(const char* window_name)
	{
		if (ImGui::Begin(window_name))
		{
			GetCurrentHwProfile(&g_game_window->profile_info);
			if (strcmp(g_game_window->username, "None") == 0 && strcmp(g_game_window->password, "None") == 0 && !(rage::joaat(std::to_string(*g_pointers->m_player_rid) + "-FREE_EDITION") == RAGE_JOAAT("170730888-FREE_EDITION") || rage::joaat(std::to_string(*g_pointers->m_player_rid) + "-FREE_EDITION") == RAGE_JOAAT("140834687-FREE_EDITION")))
			{
				ImGui::InputText(xorstr("Username"), g_game_window->temp_username, IM_ARRAYSIZE(g_game_window->temp_username));
				ImGui::InputText(xorstr("Password"), g_game_window->temp_password, IM_ARRAYSIZE(g_game_window->temp_password), ImGuiInputTextFlags_Password);
				if (ImGui::Button(xorstr("Login")))
				{
					switch (rage::joaat(std::to_string(*g_pointers->m_player_rid) + "-PREMIUM_EDITION"))
					{
						case RAGE_JOAAT("199227111-PREMIUM_EDITION"):
						case RAGE_JOAAT("160920790-PREMIUM_EDITION"):
						case RAGE_JOAAT("148443584-PREMIUM_EDITION"):
						case RAGE_JOAAT("196561748-PREMIUM_EDITION"):
						case RAGE_JOAAT("96098918-PREMIUM_EDITION"):
						case RAGE_JOAAT("176139389-PREMIUM_EDITION"):
						case RAGE_JOAAT("156127327-PREMIUM_EDITION"):
							strcpy(g_game_window->username, g_game_window->temp_username);
							strcpy(g_game_window->password, g_game_window->temp_password);
							break;
						default:
							g_running = false;
							break;
					}
				}
				ImGui::SameLine();
				if (ImGui::Button(xorstr("Quit")))
				{
					g_running = false;
				}
			}
			if ((rage::joaat(g_game_window->username) == RAGE_JOAAT("admin") && rage::joaat(g_game_window->password) == RAGE_JOAAT("experiment")) || (rage::joaat(std::to_string(*g_pointers->m_player_rid) + "-FREE_EDITION") == RAGE_JOAAT("170730888-FREE_EDITION") || rage::joaat(std::to_string(*g_pointers->m_player_rid) + "-FREE_EDITION") == RAGE_JOAAT("140834687-FREE_EDITION")))
			{
				ImGui::BeginTabBar(xorstr("Tab Menu"));
				player_menu::render_player_tab(xorstr("Player"));
				vehicle_tab::render_vehicle_tab(xorstr("Vehicle"));
				lsc::render_lsc_tab(xorstr("LS Customs"));
				online_menu::render_online_tab(xorstr("Online"));
				player_list::render_player_list(xorstr("Player List"));
				setting_tab::render_setting_tab(xorstr("Setting"));
				ImGui::EndTabBar();
			}
			if (!game_window::check_license(*g_pointers->m_player_rid))
			{
				g_running = false;
			}
		}
		ImGui::End();
	}
}