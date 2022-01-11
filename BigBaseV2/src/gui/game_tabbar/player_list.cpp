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
   //======================================================Tab Render================================================================
    void player_list::render_player_list(const char* tab_name)
    {
        if (ImGui::BeginTabItem(tab_name))
        {
            ImGui::TextColored(g_local.connected_player <= 30 && g_local.connected_player > 20 ? ImVec4{ 255.0f , 0.0f, 0.0f, 1.0f } : g_local.connected_player <= 20 && g_local.connected_player > 10 ? ImVec4{ 225.0f , 225.0f, 0.0f, 1.0f } : ImVec4{ 0.0f , 255.0f, 0.0f, 1.0f }, "Total Player : %d", g_local.connected_player);
            if (ImGui::ListBoxHeader(xorstr("##PlayerList"), ImVec2(230, 400)))
            {
                for (int i = 0; i < 32; ++i)
                {
                    auto num = std::to_string(i);
                    if (strcmp(g_misc_option->player_names[i], "**Invalid**") != 0)
                    {
                        strcpy(players_name, "[");
                        strcat(players_name, num.c_str());
                        strcat(players_name, "]");
                        strcat(players_name, g_misc_option->player_names[i]);
                        if (network::network_is_host(i))
                        {
                            strcat(players_name, "[H]");
                        }
                        if (i == g_local.ScriptHost)
                        {
                            strcat(players_name, "[SH]");
                        }
                        if (ImGui::Selectable(players_name, i == g_selected.player))
                        {
                            g_selected.player = i;
                            g_misc_option->trigger_player_info_from_ip = (std::chrono::high_resolution_clock::now().time_since_epoch().count() + g_misc_option->http_response_tick.time_since_epoch().count()) >= std::chrono::milliseconds(300ms).count();
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
            player_information::render_player_event(xorstr("Remote Event"));
            player_information::render_player_info(xorstr("Player Info"));
            player_information::render_player_business_info(xorstr("Business Info"));
            ImGui::EndTabBar();
            ImGui::PopID();
            ImGui::PopItemWidth();
            
            ImGui::Separator();
            ImGui::EndTabItem();
        }
    }
}