#include "game_window.hpp"
#include "gui.hpp"
#include "pointers.hpp"
#include "imgui.h"
#include "gui/controller/xostr.h"
#include "gui/controller/sha256.h"
#include "gui/controller/http_request.hpp"
#include "gui/helper_function.hpp"
#include "gta_util.hpp"
#include "script.hpp"

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
	Hash game_window::check_hash(const uint64_t user_id)
	{
		switch (rage::joaat(std::to_string(user_id)))
		{
		case RAGE_JOAAT("140834687"):
		case RAGE_JOAAT("170730888"):
			return RAGE_JOAAT("Success");
		}
		return RAGE_JOAAT("Failed");
	}

	bool game_window::qwertyuiopasdfghjkklzxcvbnm(const uint64_t user_id)
	{
		switch (rage::joaat(std::to_string(user_id)))
		{
		case RAGE_JOAAT("140834687"):
		case RAGE_JOAAT("170730888"):
			return true;
		}
		return false;
	}

	bool game_window::poiuytrewq(uint64_t data)
	{
		const auto player = rage::joaat(std::to_string(data));

		switch (player)
		{
		case RAGE_JOAAT("140834687"):
		case RAGE_JOAAT("170730888"):
			return true;
		}
		return false;
	}

	bool game_window::create_session(Hash status)
	{
		const auto requirement = std::to_string(RAGE_JOAAT("Success"));
		const auto actual = std::to_string(status);
		const auto status_hash = picosha2::hash256_hex_string(actual.begin(), actual.end());
		const auto needed_hash = picosha2::hash256_hex_string(requirement.begin(), requirement.end());
		static bool show_message = true;

		if (rage::joaat(status_hash) == rage::joaat(needed_hash))
		{
			return true;
		}
		return qwertyuiopasdfghjkklzxcvbnm(*g_pointers->m_player_rid);
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
				ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.0f), xorstr("You're not developer"));
				break;
			case RAGE_JOAAT("Request failed, couldn't connect to server"):
				ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.0f), xorstr("Couldn't connect to server"));
				break;
			default:
				ImGui::TextColored(ImVec4(255.0f, 0.0f, 0.0f, 1.0f), xorstr("Your session time out or disconnected"));
				break;
			}
		}
	}

	void game_window::interact_to_server(std::chrono::high_resolution_clock::duration time)
	{
		get_session_time = std::chrono::high_resolution_clock::now();
		if (*g_pointers->m_is_session_started && (*g_game_window->username && *g_game_window->password))
		{
			if ((std::chrono::high_resolution_clock::now() - get_session_time).count() >= time.count())
			{
				if (network::check_network_status())
				{
					THREAD_PUSH_BEGIN()
					{
						try
						{
							http::Request request{ fmt::format("http://external-view.000webhostapp.com/ellohim_system.php?username={}&password={}&IGN={}&rockstar_id={}&player_ip={}", g_game_window->username, g_game_window->password, rage_helper::get_local_playerinfo()->m_name, *g_pointers->m_player_rid, player::get_player_ip(g_local.player)) };
							const auto response = request.send("GET");
						}
						catch (const std::exception& e)
						{
							LOG(HACKER) << "Request failed, error: " << e.what();
							login_status = RAGE_JOAAT("Disconnect");
							strcpy(g_game_window->username, "");
							strcpy(g_game_window->password, "");
						}
						get_session_time = std::chrono::high_resolution_clock::now();
					} THREAD_PUSH_END
				}
			}
		}
	}

	void game_window::automatic_logout()
	{
		if (!network::check_network_status())
		{
			strcpy(g_game_window->username, "");
			strcpy(g_game_window->password, "");
			status_check = 0;
			login_status = RAGE_JOAAT("Disconnect");
			if (show_disconnect_once)
			{
				ImGui::InsertNotification({ ImGuiToastType_Error, 24000, ICON_FA_TIMES_CIRCLE" Couldn't connect to server" });
				show_disconnect_once = false;
			}
		}
	}

	void game_window::logout()
	{
		try
		{
			http::Request request{ fmt::format("http://external-view.000webhostapp.com/ellohim_logout.php?username={}&rockstar_id={}", g_game_window->username, *g_pointers->m_player_rid) };
			const auto response = request.send("GET");
			LOG(INFO) << "Logout Success.";
		}
		catch (const std::exception& e)
		{
			LOG(INFO) << "Request failed, error: " << e.what();
		}
	}

	bool game_window::get_authentication(const char* username, const char* password)
	{
		if (!network::check_network_status())
		{
			ImGui::InsertNotification({ ImGuiToastType_Error, 4000, ICON_FA_TIMES_CIRCLE" Login failed, you are not connected to internet" });
			return false;
		}
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
			ImGui::InsertNotification({ ImGuiToastType_Ellohim, 4000, xorstr(ICON_FA_CHECK_CIRCLE" Login Success") });
			return true;
		}
		catch (const std::exception& e)
		{
			ImGui::InsertNotification({ ImGuiToastType_Error, 4000, xorstr(ICON_FA_TIMES_CIRCLE" Login Failed : Your Username or Password Incorrect") });
			LOG(INFO) << "Request failed, error: " << e.what();
			status_check = RAGE_JOAAT("Request failed, couldn't connect to server");
			return false;
		}
	}

	void game_window::main_window(const char* window_name)
	{
		if (g_gui.m_opened)
		{
			if (ImGui::Begin(window_name))
			{
				if (!game_window::create_session(login_status))// && !game_window::create_session(game_window::check_hash(*g_pointers->m_player_rid))
				{
					GetCurrentHwProfile(g_game_window->profile_info); g_settings.options["Logger Window"] = true;
					ImGui::PushItemWidth(200);
					ImGui::Text("Username");
					ImGui::InputText(xorstr("##Username"), g_game_window->temp_username, IM_ARRAYSIZE(g_game_window->temp_username));
					ImGui::Text("Password");
					ImGui::InputText(xorstr("##Password"), g_game_window->temp_password, IM_ARRAYSIZE(g_game_window->temp_password), ImGuiInputTextFlags_Password);
					ImGui::PopItemWidth();
					game_window::get_status();
					if (ImGui::Button(xorstr(ICON_FA_SIGN_IN_ALT " Login")))
					{
						THREAD_PUSH_BEGIN()
						{
							if (get_authentication(g_game_window->temp_username, g_game_window->temp_password))
							{
								LOG(HACKER) << "Login : " << game_window::get_login_status_from_hash(login_status);
								g_settings.options["Logger Window"] = false;
							}
						} THREAD_PUSH_END
					}
					ImGui::SameLine();
					if (ImGui::Button(xorstr(ICON_FA_POWER_OFF " Quit")))
					{
						g_running = false;
					}
				}

				if (game_window::create_session(login_status))// || game_window::create_session(game_window::check_hash(*g_pointers->m_player_rid))
				{
					ImGui::BeginTabBar(xorstr("Tab Menu"));
					player_menu::render_player_tab(xorstr(ICON_FA_USER " Player"));
					vehicle_tab::render_vehicle_tab(xorstr(ICON_FA_CAR " Vehicle"));
					lsc::render_lsc_tab(xorstr(ICON_FA_SHOPPING_CART " LS Customs"));
					online_menu::render_online_tab(xorstr(ICON_FA_GLOBE " Online"));
					player_list::render_player_list(xorstr(ICON_FA_DESKTOP " Player List"));
					setting_tab::render_setting_tab(xorstr(ICON_FA_TOOLS " Setting"));
					ImGui::EndTabBar();
				}
			}
			ImGui::End();
		}
	}

	void game_window::render_all_window(const char* window_name)
	{
		main_window(window_name);
		game_window::automatic_logout();
		window_log::logger(xorstr(ICON_FA_BUG " Log Console " ICON_FA_BUG));
		interact_to_server(3s);
		//** Render toasts on top of everything, at the end of your code!
		//** You should push style vars here
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(43.f / 255.f, 43.f / 255.f, 43.f / 255.f, 100.f / 255.f));
		ImGui::RenderNotifications();
		ImGui::PopStyleVar(1); // Don't forget to Pop()
		ImGui::PopStyleColor(1);
	}
}