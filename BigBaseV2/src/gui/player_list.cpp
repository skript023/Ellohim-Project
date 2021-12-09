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
#include "helper_function.hpp"
#include "gui/player_information/player_information.h"

namespace big
{
    bool player_list::AsBodyGuard = false;
    bool player_list::ApplyForce = false;
    bool player_list::IsVisible = false;
    bool player_list::AggressivePed = false;
    const int player_list::DISTANCE_SPAWN = 10;
    int player_list::fam;
    const char* player_list::StringValue = " ";
    int player_list::CasinoTake = 0;
    bool is_session_started;
    //int g_SelectedPlayer{};
    int player_list::SelectedVehicle = 0;
    
    bool has_loaded = false;
    Player isHostScript;
    bool isSpectating;
    char player_list::NameSpoofer[20];

    const char * IsTransition()
    {
        static bool Transition;
        g_fiber_pool->queue_job([]
        {
            Transition = big::features::TransitionCheck();
        });
        return Transition ? "True" : "False";
    }
    
    //======================================================Tab Render================================================================
    void player_list::render_player_list(const char* tab_name)
    {
        if (ImGui::BeginTabItem(tab_name))
        {
            ImGui::TextColored(ImVec4{ 255.0f , 0.0f, 0.0f, 1.0f }, "Total Player : %d", g_local.connected_player);
            char PlayerListMenu[200];
            if (ImGui::ListBoxHeader(xorstr("##empty"), ImVec2(230, 400)))
            {
                for (int i = 0; i < 32; ++i)
                {
                    std::string num = std::to_string(i);
                    if (!strcmp(g_misc_option->player_names[i],"**Invalid**") == 0)
                    {
                        strcpy(PlayerListMenu, "[");
                        strcat(PlayerListMenu, num.c_str());
                        strcat(PlayerListMenu, "]");
                        strcat(PlayerListMenu, g_misc_option->player_names[i]);
                        if (network::network_is_host(i))
                        {
                            strcat(PlayerListMenu, "[H]");
                        }
                        if (i == g_local.ScriptHost)
                        {
                            strcat(PlayerListMenu, "[SH]");
                        }
                        if (ImGui::Selectable(PlayerListMenu, i == g_selected.player))
                        {
                            g_selected.player = i;
                            g_misc_option->http_response_tick = 99;
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