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
#include "benchmark.h"
#include "online_menu.h"

namespace big
{
    void online_menu::render_online_tab(const char* tab_name)
    {
        if (ImGui::BeginTabItem(tab_name))
        {
            ImGui::Combo(xorstr("Session Changer"), &selected_session, session_list, IM_ARRAYSIZE(session_list));
            if (ImGui::Button(xorstr("Select Session")))
            {
                switch (selected_session)
                {
                case 0:
                    network::set_session(0);
                    break;
                case 1:
                    network::set_session(1);
                    break;
                case 2:
                    network::set_session(2);
                    break;
                case 3:
                    network::set_session(3);
                    break;
                case 4:
                    network::set_session(6);
                    break;
                case 5:
                    network::set_session(9);
                    break;
                case 6:
                    network::set_session(10);
                    break;
                case 7:
                    network::set_session(11);
                    break;
                case 8:
                    network::set_session(12);
                    break;
                case 9:
                    network::set_session(13);
                    break;
                case 10:
                    network::set_session(-1);
                    break;
                }
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr("Choose Character")))
            {
                *script_global(g_global.session_unk_1).as<int*>() = 0;
                *script_global(g_global.session_change).at(2).as<int*>() = 0;
                *script_global(g_global.session_change).as<int*>() = 65;
                *script_global(g_global.session_unk_2).as<int*>() = 1;
                *script_global(g_global.session_unk_3).as<int*>() = 4;
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr("Creator Mode")))
            {
                *script_global(g_global.session_unk_1).as<int*>() = 2;
                *script_global(g_global.session_change).at(2).as<int*>() = 2;
                *script_global(g_global.session_change).as<int*>() = 1;
            }
            ImGui::Separator();

            ImGui::Checkbox(xorstr("Off Radar"), &g_player_option.ghost_organizations);
            ImGui::SameLine(200);

            ImGui::Checkbox(xorstr("Reveal Player"), &g_player_option.reveal_players);
            ImGui::SameLine(400);
            ImGui::Checkbox(xorstr("Blind Cops"), &g_player_option.blinds_cops);

            ImGui::Checkbox(xorstr("All Mission Lives"), &g_player_option.all_mission_lives);
            ImGui::SameLine(200);
            ImGui::Checkbox(xorstr("Time Scale"), &g_misc_option->time_scale);
            ImGui::SameLine(400);
            ImGui::Checkbox(xorstr("Explode Enemies"), &g_npc_option->explode_ped);

            ImGui::Checkbox(xorstr("Kill Enemies"), &g_npc_option->kill_ped);
            ImGui::SameLine(200);
            ImGui::Checkbox(xorstr("Time Spam"), &g_misc_option->time_spam);
            ImGui::SameLine(400);
            ImGui::Checkbox(xorstr("NPC HeadShot"), &g_weapon_option.auto_headshot);

            if (ImGui::Button(xorstr("Load Norden Yankton"), ImVec2(200, 0)))
            {
                g_fiber_pool->queue_job([]
                {
                    STREAMING::REQUEST_IPL("prologue01");
                    STREAMING::REQUEST_IPL("Prologue01c");
                    STREAMING::REQUEST_IPL("Prologue01d");
                    STREAMING::REQUEST_IPL("Prologue01e");
                    STREAMING::REQUEST_IPL("Prologue01f");
                    STREAMING::REQUEST_IPL("Prologue01g");
                    STREAMING::REQUEST_IPL("prologue01h");
                    STREAMING::REQUEST_IPL("prologue01i");
                    STREAMING::REQUEST_IPL("prologue01j");
                    STREAMING::REQUEST_IPL("prologue01k");
                    STREAMING::REQUEST_IPL("prologue01z");
                    STREAMING::REQUEST_IPL("prologue02");
                    STREAMING::REQUEST_IPL("prologue03");
                    STREAMING::REQUEST_IPL("prologue03b");
                    STREAMING::REQUEST_IPL("prologue03_grv_cov");
                    STREAMING::REQUEST_IPL("prologue03_grv_dug");
                    STREAMING::REQUEST_IPL("prologue03_grv_fun");
                    STREAMING::REQUEST_IPL("prologue04");
                    STREAMING::REQUEST_IPL("prologue04b");
                    STREAMING::REQUEST_IPL("prologue04_cover");
                    STREAMING::REQUEST_IPL("prologue05");
                    STREAMING::REQUEST_IPL("prologue05b");
                    STREAMING::REQUEST_IPL("prologue06");
                    STREAMING::REQUEST_IPL("prologue06b");
                    STREAMING::REQUEST_IPL("prologue06_int");
                    STREAMING::REQUEST_IPL("prologuerd");
                    STREAMING::REQUEST_IPL("prologuerdb");
                    STREAMING::REQUEST_IPL("prologue_DistantLights");
                    STREAMING::REQUEST_IPL("prologue_grv_torch");
                    STREAMING::REQUEST_IPL("prologue_m2_door");
                    STREAMING::REQUEST_IPL("prologue_LODLights");
                    STREAMING::REQUEST_IPL("DES_ProTree_start");
                    Vector3 Coords;
                    Coords.x = 3595.39673f; Coords.y = -4893.727f; Coords.z = 115.838394f;
                    Ped player = PLAYER::PLAYER_PED_ID();
                    if (PED::IS_PED_IN_ANY_VEHICLE(player, TRUE))
                    {
                        player = PED::GET_VEHICLE_PED_IS_USING(player);
                    }
                    teleport::teleport_to_coords(player, Coords);
                });
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr("RC Bandito"), ImVec2(200, 0)))
            {
                g_fiber_pool->queue_job([] {
                    *script_global(g_global.rc_bandito).as<int*>() = 1;
                    script::get_current()->yield(1000ms);
                    *script_global(g_global.rc_bandito).as<int*>() = 0;
                    });
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr("Minitank"), ImVec2(200, 0)))
            {
                g_fiber_pool->queue_job([] {
                    *script_global(g_global.mini_tank).as<int*>() = 1;
                    script::get_current()->yield(1000ms);
                    *script_global(g_global.mini_tank).as<int*>() = 0;
                    });
            }

            if (ImGui::Button(xorstr("Drone"), ImVec2(200, 0)))
            {
                g_fiber_pool->queue_job([] {
                    int flags = *script_global(g_global.drone).as<int*>();
                    flags = memory_util::set_bit(flags, 2);
                    flags = memory_util::set_bit(flags, 22);
                    flags = memory_util::set_bit(flags, 23);
                    flags = memory_util::set_bit(flags, 24);
                    *script_global(g_global.drone).as<int*>() = flags;
                    script::get_current()->yield(200ms);
                    flags = *script_global(g_global.drone).as<int*>();
                    flags = memory_util::clear_bit(flags, 2);
                    flags = memory_util::clear_bit(flags, 22);
                    flags = memory_util::clear_bit(flags, 23);
                    *script_global(g_global.drone).as<int*>() = flags;
                    });
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr("Remove Insurance"), ImVec2(200, 0)))
            {
                vehicle_helper::claim_insurance_for_all_vehicle();
            }

            ImGui::PushItemWidth(250.f);
            if (ImGui::Combo(xorstr("Service"), &selected_service, service_list, IM_ARRAYSIZE(service_list)))
            {
                switch (selected_service)
                {
                case 1:
                    *script_global(g_global.terorbyte).as<bool*>() = true;
                    break;
                case 2:
                    *script_global(g_global.kosatka).as<bool*>() = true;
                    break;
                case 3:
                    *script_global(g_global.avanger).as<bool*>() = true;
                    break;
                case 4:
                    *script_global(g_global.moc).as<bool*>() = true;
                    break;
                case 5:
                    *script_global(g_global.dinghy).as<bool*>() = true;
                    break;
                }
            }
            ImGui::Combo(xorstr("Revenger"), &g_weapon_option.weapon_hash, game_variable::revenge_list, IM_ARRAYSIZE(game_variable::revenge_list));
            ImGui::PopItemWidth();
            //ImGui::MenuItem("Menu item", "CTRL+M");
            if (ImGui::CollapsingHeader(xorstr(ICON_FA_CLOCK" Time & Clock")))
            {
                ImGui::Text(xorstr("Weather Changer"));
                
                ImGui::Combo(xorstr("##WeatherID"), &selected_weather, weather_list, IM_ARRAYSIZE(weather_list));
                if (ImGui::Button(xorstr("Set Weather")))
                {
                    systems::set_weather_type(weather_list[selected_weather]);
                }
                ImGui::Separator();
                ImGui::Text(xorstr("Clock Changer"));
                
                if (ImGui::SliderInt(xorstr("Hour"), &Hour, 1, 23))
                {
                    g_fiber_pool->queue_job([]
                    {
                        if (*g_pointers->m_is_session_started)
                        {
                            NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(Hour, Minute, Second);
                            //g_pointers->m_set_lobby_time(1, 0);
                        }
                        else
                        {
                            CLOCK::SET_CLOCK_TIME(Hour, Minute, Second);
                        }
                    });
                }
                if (ImGui::SliderInt(xorstr("Minute"), &Minute, 1, 59))
                {
                    g_fiber_pool->queue_job([]
                    {
                        if (*g_pointers->m_is_session_started)
                        {
                            NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(Hour, Minute, Second);
                            //g_pointers->m_set_lobby_time(1, 0);
                        }
                        else
                        {
                            CLOCK::SET_CLOCK_TIME(Hour, Minute, Second);
                        }
                    });
                }
                if (ImGui::SliderInt(xorstr("Second"), &Second, 1, 59))
                {
                    g_fiber_pool->queue_job([]
                    {
                        if (*g_pointers->m_is_session_started)
                        {
                            NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(Hour, Minute, Second);
                            //g_pointers->m_set_lobby_time(1, 0);
                        }
                        else
                        {
                            CLOCK::SET_CLOCK_TIME(Hour, Minute, Second);
                        }
                    });
                }
                static int selected_scenario = 0;
                ImGui::Text(xorstr("Scenario"));
                if (ImGui::Combo(xorstr("##Scenario"), &selected_scenario, scenario::scenario_name, IM_ARRAYSIZE(scenario::scenario_name)))
                {
                    g_fiber_pool->queue_job([] {
                        if (selected_scenario == 0)
                        {
                            TASK::CLEAR_PED_TASKS_IMMEDIATELY(g_local.ped);
                        }
                        scenario::play_scenario(g_local.ped, scenario::scenario_name[selected_scenario], true);
                    });
                }
            }
            if (ImGui::CollapsingHeader(xorstr(ICON_FA_SEARCH_DOLLAR" Heist")))
            {
                ImGui::Checkbox(xorstr("All Crew Cut 0%"), &g_heist_option->casino_heist_crew);
                ImGui::SameLine(200);
                ImGui::Checkbox(xorstr("Auto Cut 85%"), &g_heist_option->auto_heist_cut);
                ImGui::SameLine(400);
                ImGui::Checkbox(xorstr("Auto Remove Crew"), &g_heist_option->casino_heist_remove_crew);

                ImGui::Checkbox(xorstr("Lester Cut"), &g_heist_option->remove_lester_cut);
                ImGui::SameLine(200);
                ImGui::Checkbox(xorstr("Glass Cutter"), &g_heist_option->zero_heat);

                if (ImGui::Button(xorstr(ICON_FA_DOOR_OPEN" Open Vault Door"), ImVec2(200, 0)))
                {
                    if (auto mission_thread = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller")))
                    {
                        *script_local(mission_thread, m_local.vault_door).as<int*>() = *script_local(mission_thread, m_local.vault_door_total).as<int*>();
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button(xorstr("Doomsday ACT III Hack"), ImVec2(200, 0)))
                {
                    if (auto mission_thread = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller")))
                    {
                        *script_local(mission_thread, m_local.doomsday_act_3_hack).as<int*>() = 0;
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button(xorstr(ICON_FA_FINGERPRINT" Instant Hack FP"), ImVec2(200, 0)))
                {
                    if (auto new_mission_thread = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")))
                    {
                        *script_local(new_mission_thread, m_local.finger_clone).as<int*>() += 1;
                    }

                    if (auto mission_thread = rage_helper::find_script_thread(RAGE_JOAAT("fm_missifon_controller")))
                    {
                        *script_local(mission_thread, m_local.finger_print).as<int*>() += 1;
                        *script_local(mission_thread, m_local.door_hack).as<int*>() += 1;
                    }
                }

                if (ImGui::Button(xorstr("Voltage Hack"), ImVec2(200, 0)))
                {
                    rage_helper::execute_as_script(RAGE_JOAAT("fm_mission_controller_2020"), [] {
                        if (auto new_mission_thread = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")))
                        {
                            *script_local(new_mission_thread, m_local.voltage_hack_target).as<int*>() = *script_local(new_mission_thread, m_local.voltage_hack_current).as<int*>();
                        }
                    });
                }
                ImGui::SameLine();
                if (ImGui::Button(xorstr("Safe Crack"), ImVec2(200, 0)))
                {
                    rage_helper::execute_as_script(RAGE_JOAAT("fm_mission_controller_2020"), [] {
                        if (auto new_mission_thread = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")))
                        {
                            for (int i = 0; i <= 2; i++)
                            {
                                *script_local(new_mission_thread, m_local.safe_hack).at(1).at(i, 2).as<float*>() = systems::int_to_float(*script_local(new_mission_thread, m_local.safe_hack).at(1).at(i, 2).at(1).as<int*>());
                            }
                        }
                    });
                }
                ImGui::SameLine();
                if (ImGui::Button(xorstr("Motherboard Hacking"), ImVec2(200, 0)))
                {
                    if (auto mission_thread = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller")))
                    {
                        *script_local(mission_thread, m_local.board_hacking_x).as<float*>() = 0.7f;
                        *script_local(mission_thread, m_local.board_hacking_y).as<float*>() = 0.3f;
                        *script_local(mission_thread, m_local.board_hacking_requirement).as<int*>() = 1;
                    }
                }

                if (ImGui::Button(xorstr("Plasma Cutter"), ImVec2(200, 0)))
                {
                    rage_helper::execute_as_script(RAGE_JOAAT("fm_mission_controller_2020"), [] {
                        if (auto new_mission_thread = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")))
                        {
                            *script_local(new_mission_thread, m_local.glass_cutter_heat).as<float*>() = 100.f;
                        }
                    });
                }
                ImGui::SameLine();
                if (ImGui::Button(xorstr("Sewer Cutting Skip"), ImVec2(200, 0)))
                {
                    rage_helper::execute_as_script(RAGE_JOAAT("fm_mission_controller_2020"), [] {
                        if (auto new_mission_thread = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")))
                        {
                            *script_local(new_mission_thread, m_local.skip_sewer_cutter).as<int*>() = 6;
                        }
                    });
                }
                ImGui::SameLine();
                if (ImGui::Button(xorstr("Instant Complete Heist"), ImVec2(200, 0)))
                {
                    if (auto mission_thread = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller")))
                    {
                        *script_local(mission_thread, m_local.instant_casino_complete).as<int*>() |= 983040;
                        *script_local(mission_thread, m_local.instant_casino_complete_2).as<int*>() |= 50;
                    }
                    if (auto new_mission_thread = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")))
                    {
                        *script_local(new_mission_thread, m_local.instant_mission_complete).as<int*>() |= 983040;
                        *script_local(new_mission_thread, m_local.instant_mission_complete_2).as<int*>() |= 50;
                    }

                }

                ImGui::Text(xorstr("Instant Heist Setup"));
                
                ImGui::RadioButton(xorstr("Instant Heist Setup"), &selected_heist_type, 0);
                ImGui::SameLine();
                ImGui::RadioButton(xorstr("Instant Mission Contract Setup"), &selected_heist_type, 1);
                ImGui::SameLine();
                ImGui::RadioButton(xorstr("Casino Heist Preparation"), &selected_heist_type, 2);

                switch (selected_heist_type)
                {
                case 0:
                    if (ImGui::BeginCombo(xorstr("##Heist List"), HeistList[SelectedHeist])) // The second parameter is the label previewed before opening the combo.
                    {
                        for (int i = 0; i < IM_ARRAYSIZE(HeistList); i++)
                        {
                            if (ImGui::Selectable(HeistList[i], SelectedHeist == i))
                                SelectedHeist = i;
                        }
                        ImGui::EndCombo();
                    }
                    if (ImGui::Button(xorstr("Set Setup##Set Heist Prep")))
                    {
                        switch (SelectedHeist)
                        {
                        case 0:
                            casino_heist::BigconHeist();
                            break;
                        case 1:
                            casino_heist::SilentHeist();
                            break;
                        case 2:
                            casino_heist::AggressiveHeist();
                            break;
                        case 3:
                            cayo_perico::CayoPericoHeist();
                            break;
                        }
                    }
                    break;
                case 1:
                    ImGui::Combo(xorstr("Skip Setup Tuner Mission"), &selected_mission, tuner_mission, IM_ARRAYSIZE(tuner_mission));
                    if (ImGui::Button(xorstr("Set Setup##Tuner")))
                    {
                        g_fiber_pool->queue_job([]
                        {
                            std::string character = std::to_string(g_local.character);
                            STATS::STAT_SET_INT(rage::joaat("MP" + character + "_TUNER_CURRENT"), selected_mission, TRUE);
                            STATS::STAT_SET_INT(rage::joaat("MP" + character + "_TUNER_GEN_BS"), 12543, TRUE);
                        });
                    }
                    break;
                case 2:
                    bool is_main_character = g_local.character == 0;
                    const char* const approach_list[] = { "Unselected", "Silent & Sneaky", "The Big Con", "Aggressive" };
                    if (ImGui::Combo(xorstr("Select Approach"), &diamond_heist_info.approach, approach_list, IM_ARRAYSIZE(approach_list)))
                        set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_APPROACH") : RAGE_JOAAT("MP1_H3OPT_APPROACH"), diamond_heist_info.approach);
                    const char* const target_list[] = { "Money", "Gold", "Art", "Diamonds" };
                    if (ImGui::Combo(xorstr("Select Target"), &diamond_heist_info.target, target_list, IM_ARRAYSIZE(target_list)))
                        set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_TARGET") : RAGE_JOAAT("MP1_H3OPT_TARGET"), diamond_heist_info.target);
                    bool vault_contents = (diamond_heist_info.bitsetone & CasinoHeistBitsetOne::VaultContents);
                    if (ImGui::Checkbox(xorstr("Vault Contents"), &vault_contents))
                        set_bitset_one(CasinoHeistBitsetOne::VaultContents);

                    if (ImGui::Combo(xorstr("Last Heist"), &diamond_heist_info.last_approach, approach_list, IM_ARRAYSIZE(approach_list)))
                        set_stat(is_main_character ? RAGE_JOAAT("MP0_H3_LAST_APPROACH") : RAGE_JOAAT("MP1_H3_LAST_APPROACH"), diamond_heist_info.last_approach);

                    if (ImGui::Combo(xorstr("Hard Approach"), &diamond_heist_info.hard_approach, approach_list, IM_ARRAYSIZE(approach_list)))
                        set_stat(is_main_character ? RAGE_JOAAT("MP0_H3_HARD_APPROACH") : RAGE_JOAAT("MP1_H3_HARD_APPROACH"), diamond_heist_info.hard_approach);

                    ImGui::Separator();

                    const char* const gunman_list[] = { "Unselected", "Karl Abolaji", "Gustavo Mota", "Charlie Reed", "Chester McCoy", "Patrick McReary" };
                    if (ImGui::Combo(xorstr("Gunman"), &diamond_heist_info.crewweap, gunman_list, IM_ARRAYSIZE(gunman_list)))
                        set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_CREWWEAP") : RAGE_JOAAT("MP1_H3OPT_CREWWEAP"), diamond_heist_info.crewweap);

                    const char* const driver_list[] = { "Unselected", "Karim Deniz", "Taliana Martinez", "Eddie Toh", "Zach Nelson", "Chester McCoy" };
                    if (ImGui::Combo(xorstr("Driver"), &diamond_heist_info.crewdriver, driver_list, IM_ARRAYSIZE(driver_list)))
                        set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_CREWDRIVER") : RAGE_JOAAT("MP1_H3OPT_CREWDRIVER"), diamond_heist_info.crewdriver);

                    const char* const hacker_list[] = { "Unselected", "Rickie Lukens", "Christian Feltz", "Yohan Blair", "Avi Schwartzman", "Page Harris" };
                    if (ImGui::Combo(xorstr("Hacker"), &diamond_heist_info.crewhacker, hacker_list, IM_ARRAYSIZE(hacker_list)))
                        set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_CREWHACKER") : RAGE_JOAAT("MP1_H3OPT_CREWHACKER"), diamond_heist_info.crewhacker);

                    switch (diamond_heist_info.crewweap)
                    {
                        case 1: //Karl Abolaji
                        {
                            const char* const karl_gun_list[4][2] = { {"##1", "##2"}, { "Micro SMG Loadout", "Machine Pistol Loadout" }, { "Micro SMG Loadout", "Shotgun Loadout" }, { "Shotgun Loadout", "Revolver Loadout" } };
                            if (ImGui::Combo(xorstr("Unmarked Weapons##2"), &diamond_heist_info.weaps, karl_gun_list[diamond_heist_info.approach], 2))
                                set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_WEAPS") : RAGE_JOAAT("MP1_H3OPT_WEAPS"), diamond_heist_info.weaps);

                            break;
                        }
                        case 2: //Gustavo Mota
                        {
                            const char* const gus_gun_list[] = { "Rifle Loadout", "Shotgun Loadout" };
                            if (ImGui::Combo(xorstr("Unmarked Weapons##2"), &diamond_heist_info.weaps, gus_gun_list, IM_ARRAYSIZE(gus_gun_list)))
                                set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_WEAPS") : RAGE_JOAAT("MP1_H3OPT_WEAPS"), diamond_heist_info.weaps);

                            break;
                        }
                        case 3: //Charlie Reed
                        {
                            const char* const charlie_gun_list[4][2] = { {"##1", "##2"}, { "SMG Loadout", "Shotgun Loadout" }, { "Machine Pistol Loadout", "Shotgun Loadout" }, { "SMG Loadout", "Shotgun Loadout" } };
                            if (ImGui::Combo(xorstr("Unmarked Weapons##2"), &diamond_heist_info.weaps, charlie_gun_list[diamond_heist_info.approach], 2))
                                set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_WEAPS") : RAGE_JOAAT("MP1_H3OPT_WEAPS"), diamond_heist_info.weaps);

                            break;
                        }
                        case 4: //Chester McCoy
                        {
                            const char* const chester_gun_list[4][2] = { {"##1", "##2"}, { "MK II Shotgun Loadout", "MK II Rifle Loadout" }, { "MK II SMG Loadout", "MK II Rifle Loadout" }, { "MK II Shotgun Loadout", "MK II Rifle Loadout" } };
                            if (ImGui::Combo(xorstr("Unmarked Weapons##2"), &diamond_heist_info.weaps, chester_gun_list[diamond_heist_info.approach], 2))
                                set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_WEAPS") : RAGE_JOAAT("MP1_H3OPT_WEAPS"), diamond_heist_info.weaps);

                            break;
                        }
                        case 5: //Patrick McReary
                        {
                            const char* const packie_gun_list[4][2] = { {"##1", "##2"}, { "Combat PDW Loadout", "Rifle Loadout" }, { "Shotgun Loadout", "Rifle Loadout" }, { "Shotgun Loadout", "Combat MG Loadout" } };
                            if (ImGui::Combo(xorstr("Unmarked Weapons##2"), &diamond_heist_info.weaps, packie_gun_list[diamond_heist_info.approach], 2))
                                set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_WEAPS") : RAGE_JOAAT("MP1_H3OPT_WEAPS"), diamond_heist_info.weaps);

                        }
                    }

                    switch (diamond_heist_info.crewdriver)
                    {
                        case 1: //Karim Deniz
                        {
                            const char* const karim_vehicle_list[] = { "Issi Classic", "Asbo", "Kanjo", "Sentinel Classic" };
                            if (ImGui::Combo(xorstr("Getaway Vehicles##2"), &diamond_heist_info.vehs, karim_vehicle_list, IM_ARRAYSIZE(karim_vehicle_list)))
                                set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_VEHS") : RAGE_JOAAT("MP1_H3OPT_VEHS"), diamond_heist_info.vehs);
                            break;
                        }
                        case 2: //Taliana Martinez
                        {
                            const char* const taliana_vehicle_list[] = { "Retinue MK II", "Drift Yosemite", "Sugoi", "Jugular" };
                            if (ImGui::Combo("Getaway Vehicles##2", &diamond_heist_info.vehs, taliana_vehicle_list, IM_ARRAYSIZE(taliana_vehicle_list)))
                                set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_VEHS") : RAGE_JOAAT("MP1_H3OPT_VEHS"), diamond_heist_info.vehs);
                            break;
                        }
                        case 3: //Eddie Toh
                        {
                            const char* const eddie_vehicle_list[] = { "Sultan Classic", "Guantlet Classic", "Ellie", "Komoda" };
                            if (ImGui::Combo("Getaway Vehicles##2", &diamond_heist_info.vehs, eddie_vehicle_list, IM_ARRAYSIZE(eddie_vehicle_list)))
                                set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_VEHS") : RAGE_JOAAT("MP1_H3OPT_VEHS"), diamond_heist_info.vehs);
                            break;
                        }
                        case 4: //Zach Nelson
                        {
                            const char* const zach_vehicle_list[] = { "Manchez", "Stryder", "Defiler", "Lectro" };
                            if (ImGui::Combo("Getaway Vehicles##2", &diamond_heist_info.vehs, zach_vehicle_list, IM_ARRAYSIZE(zach_vehicle_list)))
                                set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_VEHS") : RAGE_JOAAT("MP1_H3OPT_VEHS"), diamond_heist_info.vehs);
                            break;
                        }
                        case 5: //Chester McCoy
                        {
                            const char* const chester_vehicle_list[] = { "Zhaba", "Vagrant", "Outlaw", "Everon" };
                            if (ImGui::Combo("Getaway Vehicles##2", &diamond_heist_info.vehs, chester_vehicle_list, IM_ARRAYSIZE(chester_vehicle_list)))
                                set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_VEHS") : RAGE_JOAAT("MP1_H3OPT_VEHS"), diamond_heist_info.vehs);
                            break;
                        }
                    }

                    bool weapons_mission = (diamond_heist_info.bitsetone & CasinoHeistBitsetOne::WeaponsMissionFinished);
                    if (ImGui::Checkbox("Unmarked Weapons##1", &weapons_mission))
                        set_bitset_one(CasinoHeistBitsetOne::WeaponsMissionFinished);
                    ImGui::SameLine(200);
                    bool patrol_routes = (diamond_heist_info.bitset & CasinoHeistBitsetZero::PatrolRoutes);
                    if (ImGui::Checkbox("Patrol Routes", &patrol_routes))
                        set_bitset(CasinoHeistBitsetZero::PatrolRoutes);

                    bool vehicle_mission = (diamond_heist_info.bitsetone & CasinoHeistBitsetOne::VehicleMissionFinished);
                    if (ImGui::Checkbox("Getaway Vehicles##1", &vehicle_mission))
                        set_bitset_one(CasinoHeistBitsetOne::VehicleMissionFinished);
                    ImGui::SameLine(200);
                    bool duggan_shipments = (diamond_heist_info.bitset & CasinoHeistBitsetZero::DugganShipments);
                    if (ImGui::Checkbox("Duggan Shipments", &duggan_shipments))
                        set_bitset(CasinoHeistBitsetZero::DugganShipments);

                    bool hacking_device = (diamond_heist_info.bitsetone & CasinoHeistBitsetOne::HackingDevice);
                    if (ImGui::Checkbox("Hacking Device", &hacking_device))
                        set_bitset_one(CasinoHeistBitsetOne::HackingDevice);

                    bool vault_keys = (diamond_heist_info.bitsetone & CasinoHeistBitsetOne::VaultKeys);
                    if (ImGui::Checkbox("Vault Keycards", &vault_keys))
                        set_bitset_one(CasinoHeistBitsetOne::VaultKeys);
                    ImGui::SameLine(200);
                    bool power_drills = (diamond_heist_info.bitset & CasinoHeistBitsetZero::PowerDrills);
                    if (ImGui::Checkbox("Power Drills", &power_drills))
                        set_bitset(CasinoHeistBitsetZero::PowerDrills);

                    if (diamond_heist_info.approach == 1)
                    {
                        bool nano_drone = (diamond_heist_info.bitsetone & CasinoHeistBitsetOne::NanoDrone);
                        if (ImGui::Checkbox("Nano Drone", &nano_drone))
                            set_bitset_one(CasinoHeistBitsetOne::NanoDrone);
                        ImGui::SameLine(200);
                        bool steal_emp = (diamond_heist_info.bitset & CasinoHeistBitsetZero::EMP);
                        if (ImGui::Checkbox("Steal EMP", &steal_emp))
                            set_bitset(CasinoHeistBitsetZero::EMP);

                        bool vault_laser = (diamond_heist_info.bitsetone & CasinoHeistBitsetOne::VaultLaser);
                        if (ImGui::Checkbox("Vault Laser", &vault_laser))
                            set_bitset_one(CasinoHeistBitsetOne::VaultLaser);
                        ImGui::SameLine(200);
                        bool infiltration_suits = (diamond_heist_info.bitset & CasinoHeistBitsetZero::InfiltrationSuits);
                        if (ImGui::Checkbox("Infiltration Suits", &infiltration_suits))
                            set_bitset(CasinoHeistBitsetZero::InfiltrationSuits);
                    }
                    else if (diamond_heist_info.approach == 2)
                    {
                        bool bugstars_part_one = (diamond_heist_info.bitset & CasinoHeistBitsetZero::BugstarsPartOne);
                        if (ImGui::Checkbox("Bugstars I", &bugstars_part_one))
                            set_bitset(CasinoHeistBitsetZero::BugstarsPartOne);
                        ImGui::SameLine(200);
                        bool bugstars_part_two = (diamond_heist_info.bitset & CasinoHeistBitsetZero::BugstarsPartTwo);
                        if (ImGui::Checkbox("II##bug", &bugstars_part_two))
                            set_bitset(CasinoHeistBitsetZero::BugstarsPartTwo);

                        bool maintenance_part_one = (diamond_heist_info.bitset & CasinoHeistBitsetZero::MaintenancePartOne);
                        if (ImGui::Checkbox("Maintenance I", &maintenance_part_one))
                            set_bitset(CasinoHeistBitsetZero::MaintenancePartOne);
                        ImGui::SameLine(200);
                        bool maintenance_part_two = (diamond_heist_info.bitset & CasinoHeistBitsetZero::MaintenancePartTwo);
                        if (ImGui::Checkbox("II##maint", &maintenance_part_two))
                            set_bitset(CasinoHeistBitsetZero::MaintenancePartTwo);

                        bool gruppe_sechs_part_one = (diamond_heist_info.bitset & CasinoHeistBitsetZero::GruppeSechsPartOne);
                        if (ImGui::Checkbox("Gruppe Sechs I", &gruppe_sechs_part_one))
                            set_bitset(CasinoHeistBitsetZero::GruppeSechsPartOne);
                        ImGui::SameLine(200);
                        bool gruppe_sechs_part_two = (diamond_heist_info.bitset & CasinoHeistBitsetZero::GruppeSechsPartTwo);
                        if (ImGui::Checkbox("II##gruppe", &gruppe_sechs_part_two))
                            set_bitset(CasinoHeistBitsetZero::GruppeSechsPartTwo);

                        bool yung_ancestor_part_one = (diamond_heist_info.bitset & CasinoHeistBitsetZero::YungAncestorPartOne);
                        if (ImGui::Checkbox("Yung Ancestor I", &yung_ancestor_part_one))
                            set_bitset(CasinoHeistBitsetZero::YungAncestorPartOne);
                        ImGui::SameLine(200);
                        bool yung_ancestor_part_two = (diamond_heist_info.bitset & CasinoHeistBitsetZero::YungAncestorPartTwo);
                        if (ImGui::Checkbox("II##yung", &yung_ancestor_part_two))
                            set_bitset(CasinoHeistBitsetZero::YungAncestorPartTwo);

                        bool noose_exit = (diamond_heist_info.bitset & CasinoHeistBitsetZero::NOOSEGearExitDisguise);
                        if (ImGui::Checkbox("NOOSE Exit Disguise", &noose_exit))
                            set_bitset(CasinoHeistBitsetZero::NOOSEGearExitDisguise);
                        ImGui::SameLine(200);
                        bool firefighter_exit = (diamond_heist_info.bitset & CasinoHeistBitsetZero::FirefighterGearExitDisguise);
                        if (ImGui::Checkbox("Firefighter Exit Disguise", &firefighter_exit))
                            set_bitset(CasinoHeistBitsetZero::FirefighterGearExitDisguise);

                        bool vault_drills = (diamond_heist_info.bitsetone & CasinoHeistBitsetOne::VaultDrill);
                        if (ImGui::Checkbox("Vault Drills", &vault_drills))
                            set_bitset_one(CasinoHeistBitsetOne::VaultDrill);
                    }
                    else if (diamond_heist_info.approach == 3)
                    {
                        bool thermal_charges = (diamond_heist_info.bitsetone & CasinoHeistBitsetOne::ThermalCharges);
                        if (ImGui::Checkbox("Thermal Charges", &thermal_charges))
                            set_bitset_one(CasinoHeistBitsetOne::ThermalCharges);
                        ImGui::SameLine(200);
                        bool reinforced_armor = (diamond_heist_info.bitset & CasinoHeistBitsetZero::ReinforcedArmor);
                        if (ImGui::Checkbox("Reinforced Armor", &reinforced_armor))
                            set_bitset(CasinoHeistBitsetZero::ReinforcedArmor);

                        bool vault_explosives = (diamond_heist_info.bitsetone & CasinoHeistBitsetOne::VaultExplosives);
                        if (ImGui::Checkbox("Vault Explosives", &vault_explosives))
                            set_bitset_one(CasinoHeistBitsetOne::VaultExplosives);
                        ImGui::SameLine(200);
                        bool boring_machine = (diamond_heist_info.bitset & CasinoHeistBitsetZero::BoringMachine);
                        if (ImGui::Checkbox("Boring Machine", &boring_machine))
                            set_bitset(CasinoHeistBitsetZero::BoringMachine);

                        const char* const armor_levels[] = { "Unselected", "One", "Two", "Three" };
                        if (ImGui::Combo("Armor Level", &diamond_heist_info.bodyarmorlvl, armor_levels, IM_ARRAYSIZE(armor_levels)))
                            set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_BODYARMORLVL") : RAGE_JOAAT("MP1_H3OPT_BODYARMORLVL"), diamond_heist_info.bodyarmorlvl);

                    }

                    bool clean_vehicle = (diamond_heist_info.bitset & CasinoHeistBitsetZero::CleanVehicle);
                    if (ImGui::Checkbox("Clean Vehicle", &clean_vehicle))
                        set_bitset(CasinoHeistBitsetZero::CleanVehicle);
                    ImGui::SameLine(200);
                    bool gunman_decoy = (diamond_heist_info.bitset & CasinoHeistBitsetZero::GunmanDecoy);
                    if (ImGui::Checkbox("Gunman Decoy", &gunman_decoy))
                        set_bitset(CasinoHeistBitsetZero::GunmanDecoy);

                    const char* const mask_list[] = { "Unselected", "Geometric Set", "Hunter Set", "Oni Half Mask Set", "Emoji Set", "Ornate Skull Set", "Lucky Fruit Set", "Gurilla Set", "Clown Set", "Animal Set", "Riot Set", "Oni Set", "Hockey Set" };
                    if (ImGui::Combo("Masks", &diamond_heist_info.masks, mask_list, IM_ARRAYSIZE(mask_list)))
                        set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_MASKS") : RAGE_JOAAT("MP1_H3OPT_MASKS"), diamond_heist_info.masks);

                    const char* const security_pass_list[] = { "Unselected", "Level 1", "Level 2" };
                    if (ImGui::Combo("Security Pass", &diamond_heist_info.keylevels, security_pass_list, IM_ARRAYSIZE(security_pass_list)))
                        set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_KEYLEVELS") : RAGE_JOAAT("MP1_H3OPT_KEYLEVELS"), diamond_heist_info.keylevels);

                    const char* const disrupt_levels[] = { "Unselected", "One", "Two", "Three" };
                    if (ImGui::Combo("Disrupt Level", &diamond_heist_info.disrupt, disrupt_levels, IM_ARRAYSIZE(disrupt_levels)))
                        set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_DISRUPTSHIP") : RAGE_JOAAT("MP1_H3OPT_DISRUPTSHIP"), diamond_heist_info.disrupt);

                    //if(ImGui::InputScalar("BITSET0", ImGuiDataType_U32, &diamond_heist_info.bitset, NULL, NULL, "%08X", ImGuiInputTextFlags_CharsHexadecimal))
                    //	set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_BITSET0") : RAGE_JOAAT("MP1_H3OPT_BITSET0"), diamond_heist_info.bitset);
                    //if(ImGui::InputScalar("BITSET1", ImGuiDataType_U32, &diamond_heist_info.bitsetone, NULL, NULL, "%08X", ImGuiInputTextFlags_CharsHexadecimal))
                    //	set_stat(is_main_character ? RAGE_JOAAT("MP0_H3OPT_BITSET1") : RAGE_JOAAT("MP1_H3OPT_BITSET0"), diamond_heist_info.bitsetone);

                    if (ImGui::Button("Unlock All Heist Options"))
                    {
                        QUEUE_JOB_BEGIN_CLAUSE()
                        {
                            auto character = g_local.character == 0;
                            int character_index = g_local.character;
                            STATS::STAT_SET_INT(character ? RAGE_JOAAT("MP0_H3OPT_TARGET") : RAGE_JOAAT("MP1_H3OPT_TARGET"), -1, TRUE);
                            STATS::STAT_SET_INT(character ? RAGE_JOAAT("MP0_H3OPT_ACCESSPOINTS") : RAGE_JOAAT("MP1_H3OPT_ACCESSPOINTS"), -1, TRUE);
                            STATS::STAT_SET_INT(character ? RAGE_JOAAT("MP0_H3OPT_POI") : RAGE_JOAAT("MP1_H3OPT_POI"), -1, TRUE);
                            STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_H3_COOLDOWN"), 0, TRUE);
                            STATS::STAT_SET_INT(character ? RAGE_JOAAT("MP0_H3_COMPLETEDPOSIX") : RAGE_JOAAT("MP1_H3_COMPLETEDPOSIX"), 0, TRUE);
                            STATS::STAT_SET_INT(character ? -1836134507 : 123524422, -1, TRUE); //Unlock Packie and Avi.
                            STATS::STAT_SET_BOOL_MASKED(STATS::_GET_NGSTAT_BOOL_HASH((26969 - 26810), 0, 1, character_index, "_CASINOPSTAT_BOOL"),
                                TRUE, ((26969 - 26810) - STATS::_STAT_GET_PACKED_BOOL_MASK((26969 - 26810)) * 64), 1); //Unlock High Roller.
                        } QUEUE_JOB_END_CLAUSE
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Get Heist Status"))
                    {
                        QUEUE_JOB_BEGIN_CLAUSE()
                        {
                            auto character = g_local.character == 0;
                            STATS::STAT_GET_INT(character ? RAGE_JOAAT("MP0_H3OPT_APPROACH") : RAGE_JOAAT("MP1_H3OPT_APPROACH"), &diamond_heist_info.approach, -1);
                            STATS::STAT_GET_INT(character ? RAGE_JOAAT("MP0_H3OPT_TARGET") : RAGE_JOAAT("MP1_H3OPT_TARGET"), &diamond_heist_info.target, -1);
                            STATS::STAT_GET_INT(character ? RAGE_JOAAT("MP0_H3OPT_DISRUPTSHIP") : RAGE_JOAAT("MP1_H3OPT_DISRUPTSHIP"), &diamond_heist_info.disrupt, -1);
                            STATS::STAT_GET_INT(character ? RAGE_JOAAT("MP0_H3OPT_KEYLEVELS") : RAGE_JOAAT("MP1_H3OPT_KEYLEVELS"), &diamond_heist_info.keylevels, -1);
                            STATS::STAT_GET_INT(character ? RAGE_JOAAT("MP0_H3OPT_CREWWEAP") : RAGE_JOAAT("MP1_H3OPT_CREWWEAP"), &diamond_heist_info.crewweap, -1);
                            STATS::STAT_GET_INT(character ? RAGE_JOAAT("MP0_H3OPT_CREWDRIVER") : RAGE_JOAAT("MP1_H3OPT_CREWDRIVER"), &diamond_heist_info.crewdriver, -1);
                            STATS::STAT_GET_INT(character ? RAGE_JOAAT("MP0_H3OPT_CREWHACKER") : RAGE_JOAAT("MP1_H3OPT_CREWHACKER"), &diamond_heist_info.crewhacker, -1);
                            STATS::STAT_GET_INT(character ? RAGE_JOAAT("MP0_H3OPT_VEHS") : RAGE_JOAAT("MP1_H3OPT_VEHS"), &diamond_heist_info.vehs, -1);
                            STATS::STAT_GET_INT(character ? RAGE_JOAAT("MP0_H3OPT_WEAPS") : RAGE_JOAAT("MP1_H3OPT_WEAPS"), &diamond_heist_info.weaps, -1);
                            STATS::STAT_GET_INT(character ? RAGE_JOAAT("MP0_H3OPT_MASKS") : RAGE_JOAAT("MP1_H3OPT_MASKS"), &diamond_heist_info.masks, -1);
                            STATS::STAT_GET_INT(character ? RAGE_JOAAT("MP0_H3OPT_BODYARMORLVL") : RAGE_JOAAT("MP1_H3OPT_BODYARMORLVL"), &diamond_heist_info.bodyarmorlvl, -1);
                            STATS::STAT_GET_INT(character ? RAGE_JOAAT("MP0_H3OPT_BITSET0") : RAGE_JOAAT("MP1_H3OPT_BITSET0"), &diamond_heist_info.bitset, -1); //Optional Missions
                            STATS::STAT_GET_INT(character ? RAGE_JOAAT("MP0_H3OPT_BITSET1") : RAGE_JOAAT("MP1_H3OPT_BITSET1"), &diamond_heist_info.bitsetone, -1); //Required Missions
                            STATS::STAT_GET_INT(character ? RAGE_JOAAT("MP0_H3_LAST_APPROACH") : RAGE_JOAAT("MP1_H3_LAST_APPROACH"), &diamond_heist_info.last_approach, -1);
                            STATS::STAT_GET_INT(character ? RAGE_JOAAT("MP0_H3_HARD_APPROACH") : RAGE_JOAAT("MP1_H3_HARD_APPROACH"), &diamond_heist_info.hard_approach, -1);
                        } QUEUE_JOB_END_CLAUSE
                    }
                    break;
                }

                ImGui::Separator();
                ImGui::PushItemWidth(60);
                ImGui::Text(xorstr("Player 1"));
                ImGui::SameLine();
                ImGui::Text(xorstr("Player 2"));
                ImGui::SameLine();
                ImGui::Text(xorstr("Player 3"));
                ImGui::SameLine();
                ImGui::Text(xorstr("Player 4"));
                
                ImGui::InputScalar(xorstr("##Cut1"), ImGuiDataType_S8, &player_cut_1);
                ImGui::SameLine();
                ImGui::InputScalar(xorstr("##Cut2"), ImGuiDataType_S8, &player_cut_2);
                ImGui::SameLine();
                ImGui::InputScalar(xorstr("##Cut3"), ImGuiDataType_S8, &player_cut_3);
                ImGui::SameLine();
                ImGui::InputScalar(xorstr("##Cut4"), ImGuiDataType_S8, &player_cut_4);
                ImGui::PopItemWidth();
                ImGui::SameLine();
                if (ImGui::Button(xorstr("Set Cut")))
                {
                    g_fiber_pool->queue_job([]
                    {
                        if (systems::is_script_active(RAGE_JOAAT("gb_casino_heist_planning")))
                        {
                            *script_global(g_global.casino_cut_1).as<int*>() = player_cut_1;
                            *script_global(g_global.casino_cut_2).as<int*>() = player_cut_2;
                            *script_global(g_global.casino_cut_3).as<int*>() = player_cut_3;
                            *script_global(g_global.casino_cut_4).as<int*>() = player_cut_4;
                            *script_global(g_global.real_player_cut).as<int*>() = g_local.player == 0 ? player_cut_1 : g_local.player == 1 ? player_cut_2 : g_local.player == 2 ? player_cut_3 : g_local.player == 3 ? player_cut_4 : 0;
                        }

                        if (systems::is_script_active(RAGE_JOAAT("gb_gang_ops_planning")))
                        {
                            *script_global(g_global.doomsday_cut_1).as<int*>() = player_cut_1;
                            *script_global(g_global.doomsday_cut_2).as<int*>() = player_cut_2;
                            *script_global(g_global.doomsday_cut_3).as<int*>() = player_cut_3;
                            *script_global(g_global.doomsday_cut_4).as<int*>() = player_cut_4;
                            *script_global(g_global.real_player_cut).as<int*>() = g_local.player == 0 ? player_cut_1 : g_local.player == 1 ? player_cut_2 : g_local.player == 2 ? player_cut_3 : g_local.player == 3 ? player_cut_4 : 0;
                        }

                        if (systems::is_script_active(RAGE_JOAAT("fmmc_launcher")))
                        {
                            *script_global(g_global.apartmen_cut_1).as<int*>() = player_cut_1;
                            *script_global(g_global.apartmen_cut_2).as<int*>() = player_cut_2;
                            *script_global(g_global.apartmen_cut_3).as<int*>() = player_cut_3;
                            *script_global(g_global.apartmen_cut_4).as<int*>() = player_cut_4;
                            *script_global(g_global.real_player_cut).as<int*>() = g_local.player == 0 ? player_cut_1 : g_local.player == 1 ? player_cut_2 : g_local.player == 2 ? player_cut_3 : g_local.player == 3 ? player_cut_4 : 0;
                        }

                        if (systems::is_script_active(RAGE_JOAAT("heist_island_planning")))
                        {
                            *script_global(g_global.cayo_cut_1).as<int*>() = player_cut_1;
                            *script_global(g_global.cayo_cut_2).as<int*>() = player_cut_2;
                            *script_global(g_global.cayo_cut_3).as<int*>() = player_cut_3;
                            *script_global(g_global.cayo_cut_4).as<int*>() = player_cut_4;
                            *script_global(g_global.real_player_cut).as<int*>() = g_local.player == 0 ? player_cut_1 : g_local.player == 1 ? player_cut_2 : g_local.player == 2 ? player_cut_3 : g_local.player == 3 ? player_cut_4 : 0;
                        }
                    });
                }
                ImGui::Separator();
                
                ImGui::RadioButton(xorstr("Potential Take"), &take_type, 0);
                ImGui::SameLine();
                ImGui::RadioButton(xorstr("Heist Take"), &take_type, 1);
                ImGui::SameLine();
                ImGui::RadioButton(xorstr("Bag Size"), &take_type, 2);

                switch (take_type)
                {
                case 0:
                    ImGui::Text(xorstr("Potential Take"));
                    if (ImGui::BeginCombo(xorstr("##Potential Take"), potential_take_list[selected_potential_take]))
                    {
                        for (int i = 0; i < IM_ARRAYSIZE(potential_take_list); i++)
                        {
                            if (ImGui::Selectable(potential_take_list[i], selected_potential_take == i))
                                selected_potential_take = i;
                        }
                        ImGui::EndCombo();
                    }
                    ImGui::InputInt(xorstr("##Value"), &potential_take_value, 1000000, 1000000);
                    if (ImGui::Button(xorstr("Set Value")))
                    {
                        switch (selected_potential_take)//"Diamond"
                        {
                        case 1:
                            *script_global(g_global.diamond).as<int*>() = potential_take_value;
                            break;
                        case 2:
                            *script_global(g_global.gold).as<int*>() = potential_take_value;
                            break;
                        case 3:
                            *script_global(g_global.artwork).as<int*>() = potential_take_value;
                            break;
                        case 4:
                            *script_global(g_global.cash).as<int*>() = potential_take_value;
                            break;
                        case 5:
                            *script_global(g_global.tequila).as<int*>() = potential_take_value;
                            break;
                        case 6:
                            *script_global(g_global.ruby).as<int*>() = potential_take_value;
                            break;
                        case 7:
                            *script_global(g_global.bearer_bond).as<int*>() = potential_take_value;
                            break;
                        case 8:
                            *script_global(g_global.pink_diamond).as<int*>() = potential_take_value;
                            break;
                        case 9:
                            *script_global(g_global.madrazo_file).as<int*>() = potential_take_value;
                            break;
                        case 10:
                            *script_global(g_global.saphire).as<int*>() = potential_take_value;
                            break;
                        case 11:
                            *script_global(g_global.fleeca).as<int*>() = potential_take_value;
                            break;
                        case 12:
                            *script_global(g_global.prison_break).as<int*>() = potential_take_value;
                            break;
                        case 13:
                            *script_global(g_global.human_lab).as<int*>() = potential_take_value;
                            break;
                        case 14:
                            *script_global(g_global.a_series).as<int*>() = potential_take_value;
                            break;
                        case 15:
                            *script_global(g_global.pasific_standard).as<int*>() = potential_take_value;
                            break;
                        case 16:
                            *script_global(g_global.act_1).as<int*>() = potential_take_value;
                            break;
                        case 17:
                            *script_global(g_global.act_2).as<int*>() = potential_take_value;
                            break;
                        case 18:
                            *script_global(g_global.act_3).as<int*>() = potential_take_value;
                            break;
                        }
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(xorstr("Default")))
                    {
                        *script_global(g_global.diamond).as<int*>() = 3290000;
                        *script_global(g_global.gold).as<int*>() = 2585000;
                        *script_global(g_global.artwork).as<int*>() = 2350000;
                        *script_global(g_global.cash).as<int*>() = 2115000;
                        *script_global(g_global.tequila).as<int*>() = 900000;
                        *script_global(g_global.ruby).as<int*>() = 1000000;
                        *script_global(g_global.bearer_bond).as<int*>() = 1100000;
                        *script_global(g_global.pink_diamond).as<int*>() = 1300000;
                        *script_global(g_global.madrazo_file).as<int*>() = 1100000;
                        *script_global(g_global.saphire).as<int*>() = 1900000;
                        *script_global(g_global.fleeca).as<int*>() = 115000;
                        *script_global(g_global.prison_break).as<int*>() = 400000;
                        *script_global(g_global.human_lab).as<int*>() = 540000;
                        *script_global(g_global.a_series).as<int*>() = 404000;
                        *script_global(g_global.pasific_standard).as<int*>() = 1000000;
                        *script_global(g_global.act_1).as<int*>() = 650000;
                        *script_global(g_global.act_2).as<int*>() = 950000;
                        *script_global(g_global.act_3).as<int*>() = 1200000;
                    }
                    break;
                case 1:
                    ImGui::Text(xorstr("Current Take Heist"));
                    ImGui::InputInt(xorstr("##InputTake"), &g_heist_option->casino_take, 1000000, 1000000);
                    if (ImGui::Button("Set Take"))
                    {
                        if (systems::is_script_active(RAGE_JOAAT("fm_mission_controller")))
                            g_heist_option->all_take_heist = true;

                        if (systems::is_script_active(RAGE_JOAAT("fm_mission_controller_2020")))
                            casino_heist::all_heist_take(g_heist_option->casino_take);
                    }
                    if (systems::is_script_active(RAGE_JOAAT("fm_mission_controller")))
                    {
                        ImGui::SameLine();
                        if (ImGui::Button(xorstr("TSE Version Take")))
                        {
                            remote_event::take_all_casino(g_heist_option->casino_take);
                        }
                    }
                    break;
                case 2:
                    ImGui::Text(xorstr("Cayo Perico Bag"));
                    if (ImGui::BeginCombo(xorstr("##CayoBags"), bag_size[selected_bag_size])) // The second parameter is the label previewed before opening the combo.
                    {
                        for (int i = 0; i < IM_ARRAYSIZE(bag_size); i++)
                        {
                            //static bool is_selected = (SelectedHeist == PotentialTake[PotentialTakeTotal]);
                            if (ImGui::Selectable(bag_size[i], selected_bag_size == i))
                                selected_bag_size = i;
                        }
                        ImGui::EndCombo();
                    }
                    if (ImGui::Button(xorstr("Set Bag")))
                    {
                        if (selected_bag_size == 0)
                        {
                            *script_global(g_global.bag_size).as<int*>() = 1800;
                        }
                        else if (selected_bag_size == 1)
                        {
                            *script_global(g_global.bag_size).as<int*>() = 3600;
                        }
                        else if (selected_bag_size == 2)
                        {
                            *script_global(g_global.bag_size).as<int*>() = 5600;
                        }
                        else if (selected_bag_size == 3)
                        {
                            *script_global(g_global.bag_size).as<int*>() = 6400;
                        }
                        else if (selected_bag_size == 4)
                        {
                            *script_global(g_global.bag_size).as<int*>() = 16400;
                        }
                        else if (selected_bag_size == 5)
                        {
                            *script_global(g_global.bag_size).as<int*>() = 26400;
                        }
                        else if (selected_bag_size == 6)
                        {
                            *script_global(g_global.bag_size).as<int*>() = INT32_MAX;
                        }
                    }
                    break;
                }
            }
            if (ImGui::CollapsingHeader(xorstr(ICON_FA_BRIEFCASE" Business")))
            {
                if (ImGui::BeginCombo(xorstr("Rare Item"), cargo_rare_items[selected_rare_items])) // The second parameter is the label previewed before opening the combo.
                {
                    for (int i = 0; i < IM_ARRAYSIZE(cargo_rare_items); i++)
                    {
                        static bool is_selected = (selected_rare_items == i);
                        if (ImGui::Selectable(cargo_rare_items[i], is_selected))
                            selected_rare_items = i;
                        if (is_selected)
                            ImGui::SetItemDefaultFocus(); // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
                    }
                    ImGui::EndCombo();
                }

                if (ImGui::Button(xorstr("Set Rare Item")))
                {
                    switch (selected_rare_items)
                    {
                    case 0:
                        *script_global(g_global.special_crates).as<int*>() = 2;
                        break;
                    case 1:
                        *script_global(g_global.special_crates).as<int*>() = 4;
                        break;
                    case 2:
                        *script_global(g_global.special_crates).as<int*>() = 6;
                        break;
                    case 3:
                        *script_global(g_global.special_crates).as<int*>() = 7;
                        break;
                    case 4:
                        *script_global(g_global.special_crates).as<int*>() = 8;
                        break;
                    case 5:
                        *script_global(g_global.special_crates).as<int*>() = 9;
                        break;
                    }
                }
                ImGui::SameLine();
                static bool toggle_rare_items = *script_global(g_global.rare_item).as<bool*>();
                if (ImGui::Checkbox(xorstr("Toggle Rare Items"), &toggle_rare_items))
                {
                    if (!toggle_rare_items)
                    {
                        *script_global(g_global.rare_item).as<bool*>() = true;
                    }
                    else
                    {
                        *script_global(g_global.rare_item).as<bool*>() = false;
                    }
                }
                ImGui::Separator();
                bool is_private = *script_global(g_global.is_session_private).as<int*>() != 1;
                if (ImGui::Checkbox(xorstr("Bypass Session"), &is_private))
                {
                    if (is_private)
                    {
                        *script_global(g_global.is_session_private).as<bool*>() = false;
                        *script_global(g_global.session_type).as<int*>() = 0;
                    }
                    else
                    {
                        *script_global(g_global.is_session_private).as<bool*>() = true;
                        *script_global(g_global.session_type).as<int*>() = 0;
                    }
                }
                static bool supply_bool = *script_global(g_global.mc_supplies_delay).as<int*>() == 0;
                if (ImGui::Checkbox(xorstr("Remove MC Supply Cooldown"), &supply_bool))
                {
                    if (supply_bool)
                    {
                        *script_global(g_global.mc_supplies_delay).as<int*>() = 0;
                    }
                    else
                    {
                        *script_global(g_global.mc_supplies_delay).as<int*>() = 600;
                    }
                }
                static bool bunker_supply_bool = *script_global(g_global.bunker_supplies_delay).as<int*>() == 0;
                if (ImGui::Checkbox(xorstr("Remove Bunker Supply Cooldown"), &bunker_supply_bool))
                {
                    if (bunker_supply_bool)
                    {
                        *script_global(g_global.bunker_supplies_delay).as<int*>() = 0;
                    }
                    else
                    {
                        *script_global(g_global.bunker_supplies_delay).as<int*>() = 600;
                    }
                }
                static bool bunker_timer_bool = false;
                if (ImGui::Checkbox(xorstr("Extend Bunker Selling Time"), &bunker_timer_bool))
                {
                    if (bunker_timer_bool)
                    {
                        *script_global(g_global.bunker_selling_time_1).as<int*>() = 18000000;
                        *script_global(g_global.bunker_selling_time_2).as<int*>() = 9000000;
                        *script_global(g_global.bunker_selling_time_3).as<int*>() = 9000000;
                        *script_global(g_global.bunker_selling_time_4).as<int*>() = 9000000;
                        *script_global(g_global.bunker_selling_time_5).as<int*>() = 9000000;
                        *script_global(g_global.bunker_selling_time_6).as<int*>() = 9000000;
                    }
                    else
                    {
                        *script_global(g_global.bunker_selling_time_1).as<int*>() = 1800000;
                        *script_global(g_global.bunker_selling_time_2).as<int*>() = 900000;
                        *script_global(g_global.bunker_selling_time_3).as<int*>() = 900000;
                        *script_global(g_global.bunker_selling_time_4).as<int*>() = 900000;
                        *script_global(g_global.bunker_selling_time_5).as<int*>() = 900000;
                        *script_global(g_global.bunker_selling_time_6).as<int*>() = 900000;
                    }

                }
                static bool mc_timer_bool = false;
                if (ImGui::Checkbox(xorstr("Extend MC Selling Time"), &mc_timer_bool))
                {
                    if (mc_timer_bool)
                    {
                        *script_global(g_global.mc_selling_time_1).as<int*>() = 18000000;
                        *script_global(g_global.mc_selling_time_2).as<int*>() = 18000000;
                        *script_global(g_global.mc_selling_time_3).as<int*>() = 18000000;
                        *script_global(g_global.mc_selling_time_4).as<int*>() = 18000000;
                        *script_global(g_global.mc_selling_time_5).as<int*>() = 18000000;
                        *script_global(g_global.mc_selling_time_6).as<int*>() = 18000000;
                        *script_global(g_global.mc_selling_time_7).as<int*>() = 18000000;
                        *script_global(g_global.mc_selling_time_8).as<int*>() = 18000000;
                        *script_global(g_global.mc_selling_time_9).as<int*>() = 18000000;
                        *script_global(g_global.mc_selling_time_10).as<int*>() = 18000000;
                    }
                    else
                    {
                        *script_global(g_global.mc_selling_time_1).as<int*>() = 1800000;
                        *script_global(g_global.mc_selling_time_2).as<int*>() = 1800000;
                        *script_global(g_global.mc_selling_time_3).as<int*>() = 1800000;
                        *script_global(g_global.mc_selling_time_4).as<int*>() = 1800000;
                        *script_global(g_global.mc_selling_time_5).as<int*>() = 1800000;
                        *script_global(g_global.mc_selling_time_6).as<int*>() = 1800000;
                        *script_global(g_global.mc_selling_time_7).as<int*>() = 1800000;
                        *script_global(g_global.mc_selling_time_8).as<int*>() = 1800000;
                        *script_global(g_global.mc_selling_time_9).as<int*>() = 1800000;
                        *script_global(g_global.mc_selling_time_10).as<int*>() = 1800000;
                    }

                }
                static bool sell_cargo_cooldown = *script_global(g_global.special_cargo_selling_cooldown).as<int*>() == 0;
                if (ImGui::Checkbox(xorstr("Sell Cargo Cooldown"), &sell_cargo_cooldown))
                {
                    if (sell_cargo_cooldown)
                    {
                        *script_global(g_global.special_cargo_selling_cooldown).as<int*>() = 0;
                    }
                    else
                    {
                        *script_global(g_global.special_cargo_selling_cooldown).as<int*>() = 1800000;
                    }
                }
                static bool buy_cargo_cooldown = *script_global(g_global.special_cargo_buying_cooldown).as<int*>() == 0;
                if (ImGui::Checkbox(xorstr("Buy Cargo Cooldown"), &buy_cargo_cooldown))
                {
                    if (buy_cargo_cooldown)
                    {
                        *script_global(g_global.special_cargo_buying_cooldown).as<int*>() = 0;
                    }
                    else
                    {
                        *script_global(g_global.special_cargo_buying_cooldown).as<int*>() = 300000;
                    }
                }
                static bool cargo_selling_time = *script_global(g_global.special_cargo_selling_time).as<int*>() == 0;
                if (ImGui::Checkbox(xorstr("Extend Special Cargo Selling Time"), &cargo_selling_time))
                {
                    if (cargo_selling_time)
                    {
                        *script_global(g_global.special_cargo_selling_time).as<int*>() = 18000000;
                    }
                    else
                    {
                        *script_global(g_global.special_cargo_selling_time).as<int*>() = 1800000;
                    }
                }
                if (ImGui::Button(xorstr("Trigger Meth Product"), ImVec2(200, 0)))
                {
                    network::trigger_meth_production(g_local.player);
                }
                ImGui::SameLine(220);
                if (ImGui::Button(xorstr("Trigger Weed Production"), ImVec2(200, 0)))
                {
                    network::trigger_weed_production(g_local.player);
                }
                ImGui::SameLine(430);
                if (ImGui::Button(xorstr("Trigger Coke Production"), ImVec2(200, 0)))
                {
                    network::trigger_cocain_production(g_local.player);
                }

                if (ImGui::Button(xorstr("Trigger Cash Production"), ImVec2(200, 0)))
                {
                    network::trigger_cash_production(g_local.player);
                }
                ImGui::SameLine(220);
                if (ImGui::Button(xorstr("Trigger Document Production"), ImVec2(200, 0)))
                {
                    network::trigger_document_production(g_local.player);
                }
                ImGui::SameLine(430);
                if (ImGui::Button(xorstr("Trigger Bunker Product"), ImVec2(200, 0)))
                {
                    network::trigger_bunker_production(g_local.player);
                }
                
                if (ImGui::Button(xorstr("Trigger Bunker Research"), ImVec2(200, 0)))
                {
                    network::trigger_bunker_research(g_local.player);
                }
                ImGui::SameLine(220);
                if (ImGui::Button(xorstr("Trigger Nightclub Product"), ImVec2(200, 0)))
                {
                    network::trigger_nightclub_production();
                }
                ImGui::SameLine(430);
                if (ImGui::Button(xorstr("Max Nightclub Popularity"), ImVec2(200, 0)))
                {
                    g_fiber_pool->queue_job([]
                        {
                            const auto mpx = std::to_string(g_local.character);
                            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_CLUB_POPULARITY"), 1000, TRUE);
                        });
                }
                
                if (ImGui::Button(xorstr("Max Snack & Armour"), ImVec2(200, 0)))
                {
                    g_fiber_pool->queue_job([]
                        {
                            const auto mpx = std::to_string(g_local.character);
                            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_NO_BOUGHT_YUM_SNACKS"), 30, TRUE);
                            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_NO_BOUGHT_HEALTH_SNACKS"), 15, TRUE);
                            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_NO_BOUGHT_EPIC_SNACKS"), 5, TRUE);
                            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_NUMBER_OF_ORANGE_BOUGHT"), 10, TRUE);
                            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_NUMBER_OF_BOURGE_BOUGHT"), 10, TRUE);
                            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_CIGARETTES_BOUGHT"), 20, TRUE);
                            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_MP_CHAR_ARMOUR_1_COUNT"), 10, TRUE);
                            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_MP_CHAR_ARMOUR_2_COUNT"), 10, TRUE);
                            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_MP_CHAR_ARMOUR_3_COUNT"), 10, TRUE);
                            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_MP_CHAR_ARMOUR_4_COUNT"), 10, TRUE);
                            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_MP_CHAR_ARMOUR_5_COUNT"), 10, TRUE);
                        });
                }
                
                ImGui::Text(xorstr("Select Bunker Location"));
                ImGui::PushItemWidth(200);
                if (ImGui::Combo(xorstr("##Bunker Location"), &selected_location, location, IM_ARRAYSIZE(location)))
                {
                    switch (selected_location)
                    {
                    case 1:
                        *constant_global::business_index(g_local.player).at(5, 12).as<int*>() = 23;
                        break;
                    case 2:
                        *constant_global::business_index(g_local.player).at(5, 12).as<int*>() = 24;
                        break;
                    case 3:
                        *constant_global::business_index(g_local.player).at(5, 12).as<int*>() = 25;
                        break;
                    case 4:
                        *constant_global::business_index(g_local.player).at(5, 12).as<int*>() = 26;
                        break;
                    case 5:
                        *constant_global::business_index(g_local.player).at(5, 12).as<int*>() = 27;
                        break;
                    case 6:
                        *constant_global::business_index(g_local.player).at(5, 12).as<int*>() = 28;
                        break;
                    case 7:
                        *constant_global::business_index(g_local.player).at(5, 12).as<int*>() = 29;
                        break;
                    case 8:
                        *constant_global::business_index(g_local.player).at(5, 12).as<int*>() = 30;
                        break;
                    case 9:
                        *constant_global::business_index(g_local.player).at(5, 12).as<int*>() = 31;
                        break;
                    }
                }
                ImGui::PopItemWidth();
                static int crates = 0;
                ImGui::PushItemWidth(100);
                ImGui::Text(xorstr("Special Cargo Crates"));
                ImGui::InputScalar(xorstr("##Special Cargo Crates"), ImGuiDataType_S32, &crates);
                ImGui::PopItemWidth();
                ImGui::SameLine();
                if (ImGui::Button(xorstr("Set##Cargo")))
                {
                    if (auto crates_cargo = rage_helper::find_script_thread(RAGE_JOAAT("gb_contraband_buy")))
                    {
                        *script_local(crates_cargo, m_local.special_cargo_buying).at(1).as<int*>() = crates;
                        *script_local(crates_cargo, m_local.special_cargo_buying).at(193).as<int*>() = crates;
                        *script_local(crates_cargo, m_local.special_cargo_buying).at(6).as<int*>() = 9;
                        *script_local(crates_cargo, m_local.special_cargo_buying).at(8).as<int*>() = 4;
                        *script_local(crates_cargo, m_local.special_cargo_buying).at(9).as<int*>() = 9;
                        *script_local(crates_cargo, m_local.special_cargo_buying).at(7).as<int*>() = 21;
                    }
                }

                static const char* const business_name[]{ "Bunker", "MC Business" , "Special Cargo" , "Hangar", "Nightclub" };
                static int business_index = 0;
                ImGui::RadioButton(xorstr("Bunker"), &business_index, 0);
                ImGui::SameLine();
                ImGui::RadioButton(xorstr("MC Business"), &business_index, 1);
                ImGui::SameLine();
                ImGui::RadioButton(xorstr("Special Cargo"), &business_index, 2);
                ImGui::SameLine();
                ImGui::RadioButton(xorstr("Hangar"), &business_index, 3);
                ImGui::SameLine();
                ImGui::RadioButton(xorstr("Nightclub"), &business_index, 4);
                ImGui::Separator();
                static int BusinessMoney;
                ImGui::PushItemWidth(100);
                ImGui::Text(business_name[business_index]);
                ImGui::InputScalar(xorstr("##BusinessMoney"), ImGuiDataType_S32, &BusinessMoney);
                ImGui::PopItemWidth();
                ImGui::SameLine();
                if (ImGui::Button(xorstr("Set ##BunkerMoney")))
                {
                    switch (business_index)
                    {
                    case 0:
                        g_fiber_pool->queue_job([]
                        {
                            if (auto bunker_selling = rage_helper::find_script_thread(RAGE_JOAAT("gb_gunrunning")))
                            {
                                auto money_bunker = (*g_pointers->m_business_money)->total_money;
                                if (money_bunker == 0) return;

                                int kargo = *script_local(bunker_selling, m_local.bunker_sell).at(551).at(1).at(19).as<int*>();
                                int data = BusinessMoney / money_bunker;
                                *script_local(bunker_selling, m_local.bunker_sell).at(816).as<int*>() = kargo;
                                *script_global(g_global.bunker_selling_mult_far).as<float*>() = systems::int_to_float(data);
                                *script_global(g_global.bunker_selling_mult_near).as<float*>() = systems::int_to_float(data);

                                int mission_time_remaining = *script_local(bunker_selling, m_local.bunker_sell_time_remaining).as<int*>();
                                int mission_time_delivering = *script_local(bunker_selling, m_local.bunker_sell).at(579).as<int*>(); //*(uint32_t*)((DWORD64)nightclub->m_stack + 8 * (2314 + 22));
                                int mission_time = mission_time_delivering - (mission_time_remaining - 1000);
                                //*script_local(bunker_selling, m_local.bunker_sell).at(579).as<int*>() = mission_time;
                                auto trigger_function = script_local(bunker_selling, m_local.bunker_sell).at(4).at(63).at(0, 1).at(0, 1).as<int*>();
                                memory_util::set_bit(trigger_function, 6);

                                if (systems::wait_script(RAGE_JOAAT("gb_gunrunning")))
                                {
                                    *script_global(g_global.bunker_selling_mult_far).as<float*>() = 1.5f;
                                    *script_global(g_global.bunker_selling_mult_near).as<float*>() = 1.0f;
                                }
                            }
                        });
                        break;
                    case 1:
                        g_fiber_pool->queue_job([]
                        {
                            if (auto mc_selling = rage_helper::find_script_thread(RAGE_JOAAT("gb_biker_contraband_sell")))
                            {
                                auto money_in_mc = (*g_pointers->m_business_money)->total_money;
                                if (money_in_mc == 0) return;
                                float mc_multiplier = systems::int_to_float(BusinessMoney / money_in_mc);

                                *script_global(g_global.mc_sell_mult_far).as<float*>() = mc_multiplier;
                                *script_global(g_global.mc_sell_mult_near).as<float*>() = mc_multiplier;
                                int requirement = *script_local(mc_selling, m_local.mc_sell).at(143).as<int*>();
                                *script_local(mc_selling, m_local.mc_sell).at(122).as<int*>() = requirement;

                                if (systems::wait_script(RAGE_JOAAT("gb_biker_contraband_sell")))
                                {
                                    *script_global(g_global.mc_sell_mult_far).as<float*>() = 1.5f;
                                    *script_global(g_global.mc_sell_mult_near).as<float*>() = 1.0f;
                                }
                            }
                        });
                        break;
                    case 2:
                        g_fiber_pool->queue_job([]
                        {
                            if (auto special_cargo = rage_helper::find_script_thread(RAGE_JOAAT("gb_contraband_sell")))
                            {
                                int requirement = *script_local(special_cargo, m_local.special_cargo_sell).at(65).as<int*>();
                                int cargo = *script_local(special_cargo, m_local.special_cargo_sell).at(55).as<int*>();//54 2 choice
                                auto tuneable = game_helper::func_799(cargo);
                                int temp = *script_global(tuneable).as<int*>();
                                int result = BusinessMoney / cargo;
                                if (result == 0) return;
                                *script_global(tuneable).as<int*>() = result;
                                *script_local(special_cargo, m_local.special_cargo_sell).at(56).as<int*>() = requirement;

                                while (systems::is_script_active(RAGE_JOAAT("gb_contraband_sell"))) script::get_current()->yield();

                                *script_global(tuneable).as<int*>() = temp;
                            }
                        });
                        break;
                    case 3:
                        g_fiber_pool->queue_job([]
                        {
                            //Kosong Seperti Hati Ini
                        });
                        break;
                    case 4:
                        g_fiber_pool->queue_job([]
                        {
                            if (auto nightclub = rage_helper::find_script_thread(RAGE_JOAAT("business_battles_sell")))
                            {
                                int delivery_requirement = *script_local(nightclub, m_local.nc_sell).at(202).as<int*>();
                                *script_local(nightclub, m_local.nc_sell).at(201).as<int*>() = delivery_requirement;
                                script::get_current()->yield();
                                int mission_time_1 = *script_local(nightclub, m_local.nc_time_remaining).as<int*>();
                                int mission_time_2 = *script_local(nightclub, m_local.nc_sell).at(22).as<int*>(); //*(uint32_t*)((DWORD64)nightclub->m_stack + 8 * (2314 + 22));
                                int mission_time = mission_time_2 - (mission_time_1 - 1000);
                                //*script_local(nightclub, m_local.nc_sell).at(22).as<int*>() = mission_time; //*(uint32_t*)((DWORD64)nightclub->m_stack + 8 * (2314 + 22)) = mission_time;
                                auto trigger_function = script_local(nightclub, m_local.nc_sell).at(31).at(0, 42).at(11, 1).as<int*>();

                                memory_util::set_bit(trigger_function, 1);
                            }
                        });
                        break;
                    }
                }

                ImGui::PushItemWidth(100);
                ImGui::Text(xorstr("Delivery Manual"));
                ImGui::InputScalar(xorstr("Delivery ##Manual"), ImGuiDataType_S32, &manual_delivery);
                ImGui::PopItemWidth();
                ImGui::SameLine();
                if (ImGui::Button(xorstr("Set##DelivManual")))
                {
                    switch (business_index)
                    {
                    case 0:
                        if (auto bunker_selling = rage_helper::find_script_thread(RAGE_JOAAT("gb_gunrunning")))
                        {
                            *script_local(bunker_selling, m_local.bunker_sell).at(816).as<int*>() = manual_delivery;
                        }
                        break;
                    case 1:
                        if (auto mc_selling = rage_helper::find_script_thread(RAGE_JOAAT("gb_biker_contraband_sell")))
                        {
                            *script_local(mc_selling, m_local.mc_sell).at(122).as<int*>() = manual_delivery;
                        }
                        break;
                    case 2:
                        if (auto special_cargo = rage_helper::find_script_thread(RAGE_JOAAT("gb_contraband_sell")))
                        {
                            *script_local(special_cargo, m_local.special_cargo_sell).at(56).as<int*>() = manual_delivery;
                        }
                        break;
                    case 4:
                        if (auto nightclub = rage_helper::find_script_thread(RAGE_JOAAT("business_battles_sell")))
                        {
                            int DeliveryRequirement = *script_local(nightclub, m_local.nc_sell).at(202).as<int*>();
                            *script_local(nightclub, m_local.nc_sell).at(201).as<int*>() = DeliveryRequirement;
                            script::get_current()->yield();
                            int mission_time_1 = *script_local(nightclub, m_local.nc_time_remaining).as<int*>();
                            int mission_time_2 = *script_local(nightclub, m_local.nc_sell).at(22).as<int*>(); //*(uint32_t*)((DWORD64)nightclub->m_stack + 8 * (2314 + 22));
                            int mission_time = mission_time_2 - (mission_time_1 - 1000u);
                            *script_local(nightclub, m_local.nc_sell).at(22).as<int*>() = mission_time; //*(uint32_t*)((DWORD64)nightclub->m_stack + 8 * (2314 + 22)) = mission_time;
                        }
                        break;
                    }
                }
            }
            if (ImGui::CollapsingHeader(xorstr(ICON_FA_USER_SHIELD" Spoofer")))
            {
                ImGui::RadioButton(xorstr("Name Spoofer"), &g_spoofer_option->spoofer_type, 0);
                ImGui::SameLine();
                ImGui::RadioButton(xorstr("Crew Spoofer"), &g_spoofer_option->spoofer_type, 1);
                ImGui::SameLine();
                ImGui::RadioButton(xorstr("IP Spoofer"), &g_spoofer_option->spoofer_type, 2);
                ImGui::SameLine();
                ImGui::RadioButton(xorstr("SCID Spoofer"), &g_spoofer_option->spoofer_type, 3);

                switch (g_spoofer_option->spoofer_type)
                {
                case 0:
                    ImGui::InputText(xorstr("##NameSpoof"), g_spoofer_option->spoofed_name, IM_ARRAYSIZE( g_spoofer_option->spoofed_name));
                    if (ImGui::Button(xorstr("Set Spoof##Set Name")))
                    {
                        player::local_name(g_spoofer_option->spoofed_name);
                    }
                    if (ImGui::IsItemHovered())
                        ImGui::SetTooltip(xorstr("Dont Set This For Send Net To Session"));
                break;
                case 1:
                    ImGui::Text(xorstr("Crew Tag Spoofer"));
                    ImGui::InputText(xorstr("##CrewTag"), spoof_crew_tag, IM_ARRAYSIZE(spoof_crew_tag), ImGuiInputTextFlags_CharsUppercase);
                    if (ImGui::Button(xorstr("Set Spoof##Set Crew Tag")))
                    {
                        spoofer::player_crew(spoof_crew_tag);
                    }
                break;
                case 2:
                    ImGui::Text(xorstr(ICON_FA_WIFI" Change IP by country"));
                    ImGui::PushItemWidth(200.f);
                    if (ImGui::Combo(xorstr("##change ip by country"), &selected_country, internet_protocol_list, IM_ARRAYSIZE(internet_protocol_list)))
                    {
                        static const auto ip_address = rage_helper::get_local_playerinfo()->m_online_ip;
                        switch (selected_country)
                        {
                        case 0:
                        {
                            uint8_t out[4];
                            *(uint32_t*)&out = ip_address;
                            g_spoofer_option->ip_1 = out[3];
                            g_spoofer_option->ip_2 = out[2];
                            g_spoofer_option->ip_3 = out[1];
                            g_spoofer_option->ip_4 = out[0];
                            break;
                        }
                        case 1:
                            g_spoofer_option->ip_1 = 219;
                            g_spoofer_option->ip_2 = 100;
                            g_spoofer_option->ip_3 = 37;
                            g_spoofer_option->ip_4 = 121;
                            break;
                        case 2:
                            g_spoofer_option->ip_1 = 121;
                            g_spoofer_option->ip_2 = 137;
                            g_spoofer_option->ip_3 = 177;
                            g_spoofer_option->ip_4 = 221;
                            break;
                        case 3:
                            g_spoofer_option->ip_1 = 24;
                            g_spoofer_option->ip_2 = 48;
                            g_spoofer_option->ip_3 = 0;
                            g_spoofer_option->ip_4 = 1;
                            break;
                        case 4:
                            g_spoofer_option->ip_1 = 198;
                            g_spoofer_option->ip_2 = 13;
                            g_spoofer_option->ip_3 = 36;
                            g_spoofer_option->ip_4 = 179;
                            break;
                        }
                    }
                    ImGui::PopItemWidth();

                    ImGui::Separator();

                    ImGui::Text(xorstr("IP Spoofer"));
                    ImGui::PushItemWidth(100);
                    ImGui::InputScalar(xorstr("##IP 1"), ImGuiDataType_U8, &g_spoofer_option->ip_1);
                    ImGui::SameLine();
                    ImGui::InputScalar(xorstr("##IP 2"), ImGuiDataType_U8, &g_spoofer_option->ip_2);
                    ImGui::SameLine();
                    ImGui::InputScalar(xorstr("##IP 3"), ImGuiDataType_U8, &g_spoofer_option->ip_3);
                    ImGui::SameLine();
                    ImGui::InputScalar(xorstr("##IP 4"), ImGuiDataType_U8, &g_spoofer_option->ip_4);
                    ImGui::PopItemWidth();
                    if (ImGui::Button(xorstr("Reset IP##Set Ip")))
                    {
                        auto ip_address = rage_helper::get_local_playerinfo()->m_online_ip;
                        uint8_t out[4];
                        *(uint32_t*)&out = ip_address;
                        g_spoofer_option->ip_1 = out[3];
                        g_spoofer_option->ip_2 = out[2];
                        g_spoofer_option->ip_3 = out[1];
                        g_spoofer_option->ip_4 = out[0];
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(xorstr("Set Random IP##Set Ip")))
                    {
                        g_spoofer_option->ip_1 = std::rand() % 255;
                        g_spoofer_option->ip_2 = std::rand() % 255;
                        g_spoofer_option->ip_3 = std::rand() % 255;
                        g_spoofer_option->ip_4 = std::rand() % 255;
                    }
                break;
                case 3:
                    static uint64_t RIDSpoof;
                    ImGui::Text(xorstr("Manual RID Spoof"));
                    ImGui::InputScalar(xorstr("##RID Spoof"), ImGuiDataType_S64, &RIDSpoof);
                    if (ImGui::Button(xorstr("Set Spoof##Set RID")))  /*auto WorldPTR = *g_pointers->m_ped_factory;auto PlayerInfo = WorldPTR->m_local_ped->m_playerinfo;PlayerInfo->m_rockstar_id = RIDSpoof;*/
                    {
                        spoofer::player_scid(RIDSpoof);
                    }
                break;
                }
                ImGui::RadioButton(xorstr("Level Spoofer"), &g_spoofer_option->stat_spoofer, 0);
                ImGui::SameLine();
                ImGui::RadioButton(xorstr("Money Spoofer"), &g_spoofer_option->stat_spoofer, 1);
                ImGui::SameLine();
                ImGui::RadioButton(xorstr("Organization Name Spoofer"), &g_spoofer_option->stat_spoofer, 2);

                switch (g_spoofer_option->stat_spoofer)
                {
                case 0:
                    ImGui::InputScalar(xorstr("##Name"), ImGuiDataType_S32, &g_spoofer_option->spoofed_level);
                    if (ImGui::Button(xorstr("Set Spoof##LoopLevel")))
                    {
                        g_spoofer_option->level_spoofer = true;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(xorstr("Disable Spoof##LoopLevel")))
                    {
                        g_spoofer_option->level_spoofer = false;
                    }
                    break;
                case 1:
                    ImGui::InputScalar(xorstr("##Money"), ImGuiDataType_S32, &g_spoofer_option->spoofed_money);
                    if (ImGui::Button(xorstr("Set Spoof##Set Spoof Money")))
                    {
                        g_spoofer_option->money_spoofer = true;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(xorstr("Set Spoof##Disable Money Spoofer##S")))
                    {
                        g_spoofer_option->money_spoofer = false;
                    }
                    break;
                case 2:
                    ImGui::InputText(xorstr("##Organization Name"), organization_name, IM_ARRAYSIZE(organization_name));
                    if (ImGui::Button(xorstr("Set Organization Name")))
                    {
                        auto name = script_global(1893548).at(g_local.player, 600).at(11).at(105).as<void*>();
                        strcpy(static_cast<char*>(name), organization_name);
                    }
                    break;
                }
                ImGui::RadioButton(xorstr("Instant SCID Spoof"), &g_spoofer_option->rid_spoof_type, 0);
                ImGui::SameLine();
                ImGui::RadioButton(xorstr("Network SCID Spoof"), &g_spoofer_option->rid_spoof_type, 1);
                switch (g_spoofer_option->rid_spoof_type)
                {
                case 0:
                    ImGui::Text(xorstr("Instant RID Spoof"));
                    if (ImGui::Combo(xorstr("##InstantRIDSpoof"), &g_spoofer_option->rid, game_variable::player_data_list, IM_ARRAYSIZE(game_variable::player_data_list)))
                    {
                        if (g_spoofer_option->rid == 0)
                            rage_helper::get_local_playerinfo()->m_rockstar_id = *g_pointers->m_player_rid;
                    }
                    break;
                case 1:
                    ImGui::Text(xorstr("Network RID Spoof"));
                    ImGui::Combo(xorstr("##InstantRIDSpoof"), &g_spoofer_option->rid_spoof, game_variable::player_data_list, IM_ARRAYSIZE(game_variable::player_data_list));
                    break;
                }
            }
            if (ImGui::CollapsingHeader(xorstr(ICON_FA_DOLLAR_SIGN " Casino Stuff")))
            {
                ImGui::Checkbox(xorstr("Blackjack Rig 2,5m Auto"), &g_blackjack_option->blackjack_rig);
                ImGui::Checkbox(xorstr("Slot Machine Rig 2,5m Auto"), &g_casino_option->casino_rig);
                static int Reward;
                ImGui::InputInt(xorstr("Rig Slot Multiplier"), &Reward);
                if (ImGui::Button(xorstr("Set Multiplier")))
                {
                    casino_slot::SetJackpotMultiplier(Reward);
                }
                static bool DeveloperMode = false;
                if (ImGui::Checkbox(xorstr("Developer Mode"), &DeveloperMode))
                {
                    if (DeveloperMode)
                    {
                        *(unsigned int*)g_pointers->m_is_dlc_present = 0x24C301B0;
                    }
                    else if (!DeveloperMode)
                    {
                        *(unsigned int*)g_pointers->m_is_dlc_present = 0x245C8948;
                    }
                }
                ImGui::Text(xorstr("Lucky Wheel Prize"));
                
                if (ImGui::Combo("##LuckyWheel", &g_lucky_wheel.selected_prize, prize_list, IM_ARRAYSIZE(prize_list)))
                {
                    if (auto lucky_wheel = rage_helper::find_script_thread(RAGE_JOAAT("casino_lucky_wheel")))
                    {
                        *script_local(lucky_wheel, m_local.lucky_wheel.podium_vehicle).as<int*>() = g_lucky_wheel.selected_prize;
                        *script_local(lucky_wheel, m_local.lucky_wheel.trigger_wheel).as<int*>() = 11;
                    }
                }
            }
            if (ImGui::CollapsingHeader(xorstr(ICON_FA_USER " Friend List")))
            {
                if (ImGui::ListBoxHeader(xorstr("##Friend"), ImVec2(210, 400)))
                {
                    for (int i = 0; i < *g_pointers->m_total_friend; ++i)
                    {
                        if (ImGui::Selectable(get_friend_name(i), i == SelectedFriend))
                        {
                            SelectedFriend = i;
                        }
                    }
                    ImGui::ListBoxFooter();
                }
                ImGui::SameLine();
                ImGui::BeginGroup();
                ImGui::Text("RID : %d", get_friend_id(SelectedFriend));
                ImGui::Text("Status : %s", get_friend_status(SelectedFriend));
                static uint64_t target_rid;
                ImGui::PushItemWidth(200);
                ImGui::InputScalar(xorstr("Put Target RID"), ImGuiDataType_U64, &target_rid);
                ImGui::PopItemWidth();
                if (ImGui::Button(xorstr("Set RID Join")))
                {
                    *set_friend_id(SelectedFriend) = target_rid;
                }

                ImGui::EndGroup();
            }
            if (ImGui::CollapsingHeader(xorstr(ICON_FA_SHIELD_ALT" Protection")))
            {
                if (ImGui::Button(xorstr("Detach Object")))
                {
                    QUEUE_JOB_BEGIN_CLAUSE()
                    {
                        Ped player_ped = g_local.ped;
                        Object weapon = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(player_ped);
                        rage::CObjectInterface* objIF = g_pointers->m_replay_interface->m_object_interface;
                        int numObj = objIF->m_max_objects;
                        for (int i = 0; i < numObj; i++)
                        {
                            rage::CObject* pCObject = objIF->get_object(i);
                            if (pCObject == nullptr)
                                continue;

                            Object object = g_pointers->m_ptr_to_handle(pCObject);
                            if (object == 0)
                                break;

                            if (!ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(player_ped, object) || weapon == object)
                                continue;

                            network::request_control(object);
                            script::get_current()->yield();

                            ENTITY::DETACH_ENTITY(object, 0, 0);
                            ENTITY::SET_ENTITY_COORDS(object, 0, 0, -100, 0, 0, 0, 0);
                            NETWORK::NETWORK_FADE_OUT_ENTITY(object, 0, 0);
                            ENTITY::SET_ENTITY_AS_MISSION_ENTITY(object, 0, 0);
                            OBJECT::DELETE_OBJECT(&object);
                        }
                    } QUEUE_JOB_END_CLAUSE
                }
                ImGui::SameLine();
                if (ImGui::Button(xorstr("Detach Ped")))
                {
                    QUEUE_JOB_BEGIN_CLAUSE()
                    {
                        Ped player_ped = g_local.ped;
                        Object weapon = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(player_ped);
                        rage::CPedInterface* ped_interface = g_pointers->m_replay_interface->m_ped_interface;
                        for (int i = 0; i < ped_interface->m_max_peds; i++)
                        {
                            auto* ped_ptr = ped_interface->get_ped(i);
                            if (ped_ptr == nullptr)
                                continue;

                            Ped ped = g_pointers->m_ptr_to_handle(ped_ptr);
                            if (ped == 0)
                                break;

                            if (!ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(player_ped, ped) || weapon == ped)
                                continue;

                            network::request_control(ped);
                            script::get_current()->yield();

                            ENTITY::DETACH_ENTITY(ped, 0, 0);
                            ENTITY::SET_ENTITY_COORDS(ped, 0, 0, -100, 0, 0, 0, 0);
                            NETWORK::NETWORK_FADE_OUT_ENTITY(ped, 0, 0);
                            ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ped, 0, 0);
                            ENTITY::DELETE_ENTITY(&ped);
                        }
                    } QUEUE_JOB_END_CLAUSE
                }
                ImGui::SameLine();
                if (ImGui::Button(xorstr("Detach Vehicle")))
                {
                    QUEUE_JOB_BEGIN_CLAUSE()
                    {
                        Ped player_ped = g_local.ped;
                        Object weapon = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(player_ped);
                        rage::CVehicleInterface* vehicle_interface = g_pointers->m_replay_interface->m_vehicle_interface;
                        for (int i = 0; i < vehicle_interface->m_max_vehicles; i++)
                        {
                            auto* vehicle_ptr = vehicle_interface->get_vehicle(i);
                            if (vehicle_ptr == nullptr)
                                continue;

                            Vehicle vehicle = g_pointers->m_ptr_to_handle(vehicle_ptr);
                            if (vehicle == 0)
                                break;

                            if (!ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(player_ped, vehicle) || weapon == vehicle)
                                continue;

                            network::request_control(vehicle);
                            script::get_current()->yield();

                            ENTITY::DETACH_ENTITY(vehicle, 0, 0);
                            ENTITY::SET_ENTITY_COORDS(vehicle, 0, 0, -100, 0, 0, 0, 0);
                            NETWORK::NETWORK_FADE_OUT_ENTITY(vehicle, 0, 0);
                            ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, 0, 0);
                            ENTITY::DELETE_ENTITY(&vehicle);
                        }
                    } QUEUE_JOB_END_CLAUSE
                }
                ImGui::SameLine();
                if (ImGui::Checkbox(xorstr("Block RID Joiner"), &block_rid_joiner))
                {
                    if (block_rid_joiner)
                    {
                        if (const auto presence_data = *g_pointers->m_presence_data; *g_pointers->m_presence_data && presence_data)
                        {
                            presence_data->updateIntegerAttribute(0, "gstype", 5); // put your game session type here, you know the values most likely (5 being public and so on)
                            presence_data->updateStringAttribute(0, "gsinfo", "gjtriwgjtrg"); // this is the example of some invalid data, if you want to do join redirect you would need to fetch the gsinfo from the player you want to redirect to. 
                        }
                    }
                }

                if (ImGui::Checkbox(xorstr("Request Control"), g_settings.options["Request Control Block"].get<bool*>()))
                    g_settings.save();
                ImGui::SameLine(200);
                if (ImGui::Checkbox(xorstr("Remove Weapon"), g_settings.options["Remove Weapon Block"].get<bool*>()))
                    g_settings.save();
                ImGui::SameLine(400);
                if (ImGui::Checkbox(xorstr("PTFX Event"), g_settings.options["PTFX Event Block"].get<bool*>()))
                    g_settings.save();

                if (ImGui::Checkbox(xorstr("Block Report"), g_settings.options["Block Report"].get<bool*>()))
                    g_settings.save();
                ImGui::SameLine(200);
                if (ImGui::Checkbox(xorstr("Kick Vote"), g_settings.options["Kick Vote Block"].get<bool*>()))
                    g_settings.save();
                ImGui::SameLine(400);
                if (ImGui::Checkbox(xorstr("Explosion Event"), g_settings.options["Explosion Event Block"].get<bool*>()))
                    g_settings.save();

                g_settings.save();
                if (ImGui::Checkbox(xorstr("Kick"), g_settings.options["Block Kick"].get<bool*>()))
                    g_settings.save();
                ImGui::SameLine(200);
                if (ImGui::Checkbox(xorstr("Force Invite"), g_settings.options["Block Invite Apartment"].get<bool*>()))
                    g_settings.save();
                ImGui::SameLine(400);
                if (ImGui::Checkbox(xorstr("Teleport to Cayo"), g_settings.options["Teleport Cayo Perico Block"].get<bool*>()))
                    g_settings.save();

                if (ImGui::Checkbox(xorstr("CEO Kick"), g_settings.options["CEO Kick Block"].get<bool*>()))
                    g_settings.save();
                ImGui::SameLine(200);
                if (ImGui::Checkbox(xorstr("CEO Ban"), g_settings.options["CEO Ban Block"].get<bool*>()))
                    g_settings.save();
                ImGui::SameLine(400);
                if (ImGui::Checkbox(xorstr("Rotate Cam"), g_settings.options["Rotate Cam Block"].get<bool*>()))
                    g_settings.save();

                if (ImGui::Checkbox(xorstr("Vehicle Kick"), g_settings.options["Vehicle Kick Block"].get<bool*>()))
                    g_settings.save();
                ImGui::SameLine(200);
                if (ImGui::Checkbox(xorstr("Force Mission"), g_settings.options["Force To Mission Block"].get<bool*>()))
                    g_settings.save();
                ImGui::SameLine(400);
                if (ImGui::Checkbox(xorstr("Transaction Failed"), g_settings.options["Transaction Failed Block"].get<bool*>()))
                    g_settings.save();
                if (ImGui::Checkbox(xorstr("Block Freeze"), g_settings.options["Clear Ped Task Block"].get<bool*>()))
                    g_settings.save();
                ImGui::SameLine(200);
                if (ImGui::Checkbox(xorstr("Block Sound Spam"), g_settings.options["Sound Spam"].get<bool*>()))
                    g_settings.save();
                ImGui::SameLine(400);
                if (ImGui::Checkbox(xorstr("Crash Protection"), g_settings.options["Crash Protection"].get<bool*>())) //g_settings.options["Invalid Model Protection"].get<bool*>()
                    g_settings.save();

                if (ImGui::Checkbox(xorstr("Redirect Report"), g_settings.options["Redirect Report"].get<bool*>()))
                    g_settings.save();
                ImGui::SameLine(200);
                if (ImGui::Checkbox(xorstr("Redirect Event"), g_settings.options["Redirect Event"].get<bool*>()))
                    g_settings.save();
                ImGui::SameLine(400);
                if (ImGui::Checkbox(xorstr("Redirect Network Event"), g_settings.options["Redirect Network Event"].get<bool*>()))
                    g_settings.save();

                if (ImGui::Checkbox(xorstr("Enable Anti-Sig Scanner"), g_settings.options["Sig Scanner Block"].get<bool*>()))
                    g_settings.save();
            }
            ImGui::EndTabItem();
        }
    }
}