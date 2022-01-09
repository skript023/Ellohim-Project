#include "game_window.hpp"
#include "gui.hpp"
#include "pointers.hpp"
#include "imgui.h"
#include "gui/controller/xostr.h"
#include "gui/controller/sha256.h"
#include "gui/controller/http_request.hpp"
#include "gui/helper_function.hpp"
#include "gta_util.hpp"

//Gui Tab Renderer
#include "gui/game_tabbar/player_list.h"
#include "gui/game_tabbar/vehicle_menu.h"
#include "gui/game_tabbar/setting_menu.h"
#include "gui/game_tabbar/online_menu.h"
#include "gui/game_tabbar/player_menu.h"
#include "gui/game_tabbar/vehicle_customize.h"
#include "gui/window/window_logger.hpp"

namespace big
{
	Hash game_window::check_hash(uint64_t user_id)
	{
		switch (rage::joaat(std::to_string(user_id)))
		{
		case RAGE_JOAAT("140834687"):
		case RAGE_JOAAT("170730888"):
			return RAGE_JOAAT("Success");
		}
		return RAGE_JOAAT("Failed");
	}

	bool game_window::create_session(Hash status)
	{
		auto requirement = std::to_string(RAGE_JOAAT("Success"));
		auto actual = std::to_string(status);
		if (strcmp(picosha2::hash256_hex_string(actual.begin(), actual.end()).c_str(), picosha2::hash256_hex_string(requirement.begin(), requirement.end()).c_str()) == 0)
		{
			return true;
		}
		return false;
	}

	const char* game_window::get_login_status_from_hash(Hash hash)
	{
		if (!get_result.empty())
		{
			switch (hash)
			{
			case RAGE_JOAAT("Success"):
				return "Successful";
			case RAGE_JOAAT("Failed"):
				return "Username or Password Incorrect";
			case RAGE_JOAAT("Unauthorized"):
				return "Restricted Access";
			}
		}
		return "Request failed, couldn't connect to server";
	}

	void game_window::get_status()
	{
		if (!get_result.empty())
		{
			switch (status_check)
			{
			case RAGE_JOAAT("Success"):
				ImGui::TextColored(ImVec4(0.0f, 255.0f, 0.0f, 1.0f), xorstr("Success"));
				break;
			case RAGE_JOAAT("Failed"):
				ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.0f), xorstr("Failed"));
				break;
			case RAGE_JOAAT("Unauthorized"):
				ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.0f), xorstr("You're not Developer"));
				break;
			case RAGE_JOAAT("Request failed, couldn't connect to server"):
				ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.0f), xorstr("Couldn't Connect to Server"));
				break;
			default:
				ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.0f), xorstr("Couldn't Connect to Server"));
				break;
			}
		}
	}

	void game_window::interact_to_server(std::chrono::high_resolution_clock::duration time)
	{
		get_session_time = std::chrono::high_resolution_clock::now();
		if (*g_pointers->m_is_session_started && is_auth && (*g_game_window->username && *g_game_window->password))
		{
			if ((std::chrono::high_resolution_clock::now() - get_session_time).count() >= time.count())
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

			get_result = std::string{ response.body.begin(), response.body.end() };
			get_result.erase(std::remove_if(get_result.begin(), get_result.end(), [](unsigned char x) {return std::isspace(x); }), get_result.end());
			status_check = get_result.empty() ? 0 : stoi(get_result);
			login_status = get_result.empty() ? 0 : stoi(get_result);
			return true;
		}
		catch (const std::exception& e)
		{
			LOG(HACKER) << "Request failed, error: " << e.what();
			status_check = RAGE_JOAAT("Request failed, couldn't connect to server");
			return false;
		}
	}

	void game_window::render_base_window(const char* window_name)
	{
		if (ImGui::Begin(window_name))
		{
			if (!game_window::create_session(login_status) && !game_window::create_session(game_window::check_hash(*g_pointers->m_player_rid)))
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
						LOG(HACKER) << "Login : " << game_window::get_login_status_from_hash(login_status);
					}
				}
				ImGui::SameLine();
				if (ImGui::Button(xorstr("Quit")))
				{
					g_running = false;
				}
			}

			if (game_window::create_session(login_status) || game_window::create_session(game_window::check_hash(*g_pointers->m_player_rid)))
			{
				ImGui::BeginTabBar(xorstr("Tab Menu"));
				player_menu::render_player_tab(xorstr("Player"));
				vehicle_tab::render_vehicle_tab(xorstr("Vehicle"));
				lsc::render_lsc_tab(xorstr("LS Customs"));
				online_menu::render_online_tab(xorstr("Online"));
				player_list::render_player_list(xorstr("Player List"));
				setting_tab::render_setting_tab(xorstr("Setting"));
				window_log::logger(xorstr("Log Console"));
				game_window::interact_to_server(240s);
				ImGui::EndTabBar();
			}
		}
		ImGui::End();
	}
}