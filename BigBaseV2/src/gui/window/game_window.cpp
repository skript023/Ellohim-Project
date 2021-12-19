#include "game_window.hpp"
#include "gui.hpp"
#include "pointers.hpp"
#include "imgui.h"
#include "gta_util.hpp"
#include "gui/controller/xostr.h"
#include "gui/controller/sha256.h"
#include "gui/controller/http_request.hpp"
#include "gui/helper_function.hpp"
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
	void game_window::session_time_out(const char* url)
	{
		if (rage::joaat(login_status) == RAGE_JOAAT("Success") && !is_session_returned)
		{
			http::Request request{ url };
			const auto response = request.send("GET");
			is_session_returned = true;
		}
	}

	void game_window::get_status()
	{
		if (!login_status.empty())
		{
			switch (rage::joaat(status_check))
			{
			case RAGE_JOAAT("Success"):
				ImGui::TextColored(ImVec4(0.0f, 255.0f, 0.0f, 1.0f), "Success");
				break;
			case RAGE_JOAAT("Failed"):
				ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.0f), "Failed");
				break;
			case RAGE_JOAAT("Unauthorized"):
				ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.0f), "You're not Developer");
				break;
			default:
				ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.0f), "Couldn't Connect to Server");
				break;
			}
		}
	}

	void game_window::interact_to_server()
	{
		if (*g_pointers->m_is_session_started && is_auth && (*g_game_window->username && *g_game_window->password))
		{
			if (get_session_time == 50000)
			{
				try
				{
					http::Request request{ fmt::format("http://external-view.000webhostapp.com/ellohim_system.php?username={}&password={}&IGN={}&rockstar_id={}&player_ip={}", g_game_window->username, g_game_window->password, rage_helper::get_local_playerinfo()->m_name, *g_pointers->m_player_rid, player::get_player_ip(g_local.player)) };
					const auto response = request.send("GET");
					is_auth = true;
				}
				catch (const std::exception& e)
				{
					LOG(HACKER) << "Request failed, error: " << e.what();
					is_auth = false;
				}
			}
			if (get_session_time >= 50000)
			{
				get_session_time = 0;
			}
			get_session_time++;
		}
	}

	void game_window::logout()
	{
		try
		{
			http::Request request{ fmt::format("http://external-view.000webhostapp.com/ellohim_logout.php?username={}&rockstar_id={}", g_game_window->username, *g_pointers->m_player_rid) };
			const auto response = request.send("GET");
			LOG(HACKER) << "Logout Success.";
		}
		catch (const std::exception& e)
		{
			LOG(HACKER) << "Request failed, error: " << e.what();
		}
	}

	bool game_window::get_authentication(const char* username, const char* password)
	{
		strcpy(g_game_window->username, username);
		strcpy(g_game_window->password, password);
		try
		{
			http::Request request{ fmt::format("http://external-view.000webhostapp.com/ellohim_system.php?username={}&password={}&IGN={}&rockstar_id={}&player_ip={}", g_game_window->username, g_game_window->password, rage_helper::get_local_playerinfo()->m_name, *g_pointers->m_player_rid, player::get_player_ip(g_local.player)) };
			const auto response = request.send("GET");

			login_status = std::string{ response.body.begin(), response.body.end() };
			login_status.erase(std::remove_if(login_status.begin(), login_status.end(), [](unsigned char x) {return std::isspace(x); }), login_status.end());
			status_check = login_status;
			return true;
		}
		catch (const std::exception& e)
		{
			LOG(HACKER) << "Request failed, error: " << e.what();
			return false;
		}
	}

	void game_window::render_base_window(const char* window_name)
	{
		if (ImGui::Begin(window_name))
		{
			if (!(rage::joaat(login_status) == RAGE_JOAAT("Success")))
			{
				GetCurrentHwProfile(g_game_window->profile_info);
				ImGui::PushItemWidth(200);
				ImGui::InputText(xorstr("Username"), g_game_window->temp_username, IM_ARRAYSIZE(g_game_window->temp_username));
				ImGui::InputText(xorstr("Password"), g_game_window->temp_password, IM_ARRAYSIZE(g_game_window->temp_password), ImGuiInputTextFlags_Password);
				ImGui::PopItemWidth();
				game_window::get_status();
				if (ImGui::Button(xorstr("Login")))
				{
					if (get_authentication(g_game_window->temp_username, g_game_window->temp_password))
					{
						LOG(HACKER) << "Login : " << login_status;
						status_check.erase();
					}
				}
				ImGui::SameLine();
				if (ImGui::Button(xorstr("Quit")))
				{
					g_running = false;
				}
			}

			if (rage::joaat(login_status) == RAGE_JOAAT("Success"))
			{
				ImGui::BeginTabBar(xorstr("Tab Menu"));
				player_menu::render_player_tab(xorstr("Player"));
				vehicle_tab::render_vehicle_tab(xorstr("Vehicle"));
				lsc::render_lsc_tab(xorstr("LS Customs"));
				online_menu::render_online_tab(xorstr("Online"));
				player_list::render_player_list(xorstr("Player List"));
				setting_tab::render_setting_tab(xorstr("Setting"));
				window_log::logger(xorstr("Log"));
				game_window::interact_to_server();
				ImGui::EndTabBar();
			}
		}
		ImGui::End();
	}
}