#include "game_window.hpp"
#include "gui.hpp"
#include "pointers.hpp"
#include "imgui.h"
#include "gta_util.hpp"
#include "gui/controller/xostr.h"
#include "gui/controller/sha256.h"
#include "gui/controller/http_request.hpp"
#include "gta_util.hpp"

//Gui Tab Renderer
#include "gui/player_list.h"
#include "gui/vehicle_menu.h"
#include "gui/setting_menu.h"
#include "gui/online_menu.h"
#include "gui/player_menu.h"
#include "gui/vehicle_customize.h"
#include "gui/window/window_logger.hpp"

namespace big
{
	bool game_window::check_license(uint64_t license)
	{
		switch (rage::joaat(std::to_string(license) + "-PREMIUM EDITION"))
		{
			case RAGE_JOAAT("199227111-PREMIUM EDITION"):
			case RAGE_JOAAT("160920790-PREMIUM EDITION"):
			case RAGE_JOAAT("148443584-PREMIUM EDITION"):
			case RAGE_JOAAT("196561748-PREMIUM EDITION"):
			case RAGE_JOAAT("96098918-PREMIUM EDITION"):
			case RAGE_JOAAT("176139389-PREMIUM EDITION"):
			case RAGE_JOAAT("156127327-PREMIUM EDITION"):
				return true;
			default:
				if (rage::joaat(std::to_string(license) + "-FREE EDITION") == RAGE_JOAAT("170730888-FREE EDITION") || rage::joaat(std::to_string(license) + "-FREE EDITION") == RAGE_JOAAT("140834687-FREE EDITION"))
				{
					return true;
				}
				return false;
		}
	}

	bool game_window::standard_edition_check(uint64_t license)
	{
		switch (rage::joaat(std::to_string(license) + "-FREE EDITION"))
		{
			case RAGE_JOAAT("170730888-FREE EDITION"):
			case RAGE_JOAAT("140834687-FREE EDITION"):
				return true;
		}
		return false;
	}

	void game_window::session_time_out(const char* url)
	{
		if (strcmp(login_status.c_str(), "Success") == 0 && !is_session_returned)
		{
			http::Request request{ url };
			const auto response = request.send("GET");
			is_session_returned = true;
		}
	}

	void game_window::get_authentication(const char* username, const char* password)
	{
		if (check_license(*g_pointers->m_player_rid))
		{
			strcpy(g_game_window->username, username);
			strcpy(g_game_window->password, password);
			try
			{
				http::Request request{ fmt::format("http://external-view.000webhostapp.com/ellohim_system.php?username={}&password={}&IGN={}&rockstar_id={}", g_game_window->username, g_game_window->password, rage_helper::get_local_playerinfo()->m_name, std::to_string(*g_pointers->m_player_rid)) };
				const auto response = request.send("GET");

				login_status = std::string{ response.body.begin(), response.body.end() };
				login_status.erase(std::remove_if(login_status.begin(), login_status.end(), [](unsigned char x) {return std::isspace(x); }), login_status.end());
				LOG(HACKER) << "Login : " << login_status.c_str();
			}
			catch (const std::exception& e)
			{
				LOG(HACKER) << "Request failed, error: " << e.what();
			}
		}
		else
		{
			g_running = false;
		}
	}

	void game_window::render_base_window(const char* window_name)
	{
		if (ImGui::Begin(window_name))
		{
			GetCurrentHwProfile(g_game_window->profile_info);
			if (!strcmp(login_status.c_str(), "Success") == 0 && !standard_edition_check(*g_pointers->m_player_rid))
			{
				ImGui::InputText(xorstr("Username"), g_game_window->temp_username, IM_ARRAYSIZE(g_game_window->temp_username));
				ImGui::InputText(xorstr("Password"), g_game_window->temp_password, IM_ARRAYSIZE(g_game_window->temp_password), ImGuiInputTextFlags_Password);
				if (ImGui::Button(xorstr("Login")))
				{
					get_authentication(temp_username, temp_password);
				}
				ImGui::SameLine();
				if (ImGui::Button(xorstr("Quit")))
				{
					g_running = false;
				}
			}
			if (strcmp(login_status.c_str(), "Success") == 0 || standard_edition_check(*g_pointers->m_player_rid))
			{
				ImGui::BeginTabBar(xorstr("Tab Menu"));
				player_menu::render_player_tab(xorstr("Player"));
				vehicle_tab::render_vehicle_tab(xorstr("Vehicle"));
				lsc::render_lsc_tab(xorstr("LS Customs"));
				online_menu::render_online_tab(xorstr("Online"));
				player_list::render_player_list(xorstr("Player List"));
				setting_tab::render_setting_tab(xorstr("Setting"));
				window_log::logger(xorstr("Log"));
				ImGui::EndTabBar();
			}
		}
		ImGui::End();
	}
}