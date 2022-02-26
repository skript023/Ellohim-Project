#include "common.hpp"
#include "player_list.h"
#include "imgui.h"
#include "script.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "gta_util.hpp"
#include "ImGuiBitfield.h"
#include "script_global.hpp"
#include "features.hpp"
#include "gta\VehicleValues.h"
#include "gui.hpp"
#include "gta\Weapons.h"
#include "script_local.hpp"
#include "misc/cpp/imgui_stdlib.h"
#include "gui/helper_function.hpp"
#include "gui/player_information/player_information.h"

namespace big
{
    void player_list::render_player_list(const char* tab_name)
    {
        if (ImGui::BeginTabItem(tab_name))
        {
            ImGui::TextColored(g_local.connected_player <= 30 && g_local.connected_player > 20 ? ImVec4{ 255.0f , 0.0f, 0.0f, 1.0f } : g_local.connected_player <= 20 && g_local.connected_player > 10 ? ImVec4{ 225.0f , 225.0f, 0.0f, 1.0f } : ImVec4{ 0.0f , 255.0f, 0.0f, 1.0f }, ICON_FA_USER" Total Player : %d", g_local.connected_player);
            if (ImGui::ListBoxHeader(xorstr("##PlayerList"), ImVec2(230, 400)))
            {
                for (auto player_list : g_misc_option->player_names)
                {
                    if (!g_misc_option->player_names.empty())
                    {
                        strcpy(players_name, player_list.second.name);
                        if (network::network_is_host(player_list.second.id))
                        {
                            strcat(players_name, " " ICON_FA_CROWN);
                        }
                        if (player_list.second.id == g_local.ScriptHost)
                        {
                            strcat(players_name, " " ICON_FA_USER_TIE);
                        }
                        if (player_list.second.interior)
                        {
                            strcat(players_name, " " ICON_FA_BUILDING);
                        }
                        if (player::is_player_in_any_vehicle(player_list.second.id))
                        {
                            strcat(players_name, " " ICON_FA_CAR);
                        }
                        if (ImGui::Selectable(players_name, player_list.second.id == g_selected.player))
                        {
                            if (g_selected.player != player_list.second.id)
                                g_selected.player = player_list.second.id;

                            if (g_misc_option->trigger_player_info_from_ip != (std::chrono::high_resolution_clock::now().time_since_epoch().count() + g_misc_option->http_response_tick.time_since_epoch().count()) >= std::chrono::milliseconds(1000ms).count())
                                g_misc_option->trigger_player_info_from_ip = (std::chrono::high_resolution_clock::now().time_since_epoch().count() + g_misc_option->http_response_tick.time_since_epoch().count()) >= std::chrono::milliseconds(1000ms).count();
                        }
                    }
                }
                ImGui::ListBoxFooter();
            }
            ImGui::SameLine();
            ImGui::BeginGroup();
            
            ImGui::PushItemWidth(250);
            ImGui::PushID(xorstr("##PlayerInfo"));
            ImGui::BeginTabBar(xorstr("Player Information"));
            //Render
            player_information::render_player_event(xorstr(ICON_FA_STAR" Remote Event"));
            player_information::render_player_info(xorstr(ICON_FA_INFO_CIRCLE" Player Info"));
            player_information::render_player_business_info(xorstr(ICON_FA_INFO_CIRCLE" Business Info"));
            ImGui::EndTabBar();
            ImGui::PopID();
            ImGui::PopItemWidth();
            
            ImGui::Separator();
            ImGui::EndTabItem();
        }
    }
}