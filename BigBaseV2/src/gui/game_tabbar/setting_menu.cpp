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
#include "setting_menu.h"
#include "gui/window/game_window.hpp"
#include "fonts/font_list.hpp"

namespace big
{
    void setting_tab::render_setting_tab(const char* tab_name)
    {
        if (ImGui::BeginTabItem(tab_name))
        {
            if (ImGui::Button(xorstr("End Session")))
            {
                g_fiber_pool->queue_job([]
                {
                    NETWORK::NETWORK_SESSION_END(FALSE, FALSE);
                });
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr("End Cutscene")))
            {
                (*g_pointers->m_cutscene_mgr)->m_end_cutscene = 1;
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr("Bail from Session")))
            {
                g_fiber_pool->queue_job([]
                {
                    *script_global(g_global.disconnect).as<int*>() = 1;
                    script::get_current()->yield(5000ms);
                    *script_global(g_global.disconnect).as<int*>() = 0;
                });
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr("Entrypoint")))
            {
                miscellaneous::dump_entry_point();
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr("Benchmark")))
            {
                auto benchmarking = benchmark("Vehicle Spawn");
                vehicle_helper::vehicle("Krieger", g_local.ped);
                ImGui::InsertNotification({ ImGuiToastType_Ellohim, 3000, "finished with a resulting time of %d nanoseconds", benchmarking.get_runtime() });
            }
            ImGui::Separator();
            
            if (ImGui::CollapsingHeader(xorstr(ICON_FA_GAMEPAD " Game Setting")))
            {
                ImGui::Checkbox(xorstr("Expand Radar"), &g_pointers->m_game_setting->m_radar_expansion);
                ImGui::SameLine(150);

                ImGui::Checkbox(xorstr("Subtitle"), &g_pointers->m_game_setting->m_subtitle);
                ImGui::SameLine(300);

                ImGui::Checkbox(xorstr("Effect Killer"), &g_pointers->m_game_setting->m_kill_effect);

                ImGui::Checkbox(xorstr("Overhead Display"), &g_pointers->m_game_setting->m_over_head_display);
                ImGui::SameLine(150);

                ImGui::Checkbox(xorstr("Hud Setting"), &g_pointers->m_game_setting->m_hud_setting);
                ImGui::SameLine(300);

                ImGui::Checkbox(xorstr("Hud Setting"), &g_pointers->m_game_setting->m_crosshair_setting);

                if (ImGui::Checkbox(xorstr("Logger"), g_settings.options["Logger Window"].get<bool*>()))
                    g_settings.save();
                ImGui::SameLine(150);

                ImGui::Checkbox(xorstr("Auto-Clicker"), &g_player_option.auto_click);
                ImGui::SameLine(300);

                ImGui::Checkbox(xorstr("Log Incoming Player"), g_settings.options["Player Join Log"].get<bool*>());
                
                if (ImGui::Checkbox(xorstr("Log Player"), g_settings.options["Log Player"].get<bool*>()))
                    g_settings.save();
                ImGui::SameLine(150);
                if (ImGui::Checkbox(xorstr("Disable Chat Censor"), g_settings.options["Disable Censor"].get<bool*>()))
                    g_settings.save();
                ImGui::Separator();

                ImGui::Text("Aim Change");
                ImGui::PushItemWidth(150.f);
                if (ImGui::Combo(xorstr("##Aim Change"), &g_player_option.player_aim, aim_list, IM_ARRAYSIZE(aim_list)))
                    *g_pointers->m_player_aim = g_player_option.player_aim;
                ImGui::PopItemWidth();

                ImGui::Separator();
            }
            if (ImGui::CollapsingHeader(xorstr(ICON_FA_DESKTOP " Script Monitor")))
            {
                static GtaThread* selected_thread{};
                if (ImGui::ListBoxHeader("##scripts", ImVec2(250, 500)))
                {
                    if (g_settings.options["script monitor sorted"])
                    {
                        std::map<std::string, GtaThread*> sorted_threads;
                        for (auto thread : *g_pointers->m_script_threads)
                            if (thread && thread->m_context.m_thread_id && thread->m_handler)
                                sorted_threads[thread->m_name] = thread;
                        for (auto thread : sorted_threads)
                            if (ImGui::Selectable(thread.second->m_name, thread.second == selected_thread))
                                selected_thread = thread.second;
                    }
                    else
                    {
                        for (auto thread : *g_pointers->m_script_threads)
                            if (thread && thread->m_context.m_thread_id && thread->m_handler)
                                if (ImGui::Selectable(thread->m_name, thread == selected_thread))
                                    selected_thread = thread;
                    }
                    ImGui::ListBoxFooter();
                }
                ImGui::SameLine();
                ImGui::BeginGroup();
                if (ImGui::Checkbox("Sorted?", g_settings.options["script monitor sorted"].get<bool*>()))
                    g_settings.save();
                ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "Script Info:");
                if (selected_thread)
                {
                    if (auto net_component = selected_thread->m_net_component)
                        if (auto owner_list = net_component->m_owner_list)
                            if (auto owner = owner_list->m_owner)
                                ImGui::Text(fmt::format("Host: {}", owner->get_name()).c_str());
                    if (ImGui::Button(fmt::format("Script Pointer: 0x{:X}", (DWORD64)selected_thread).c_str()))
                        miscellaneous::set_clipboard(fmt::format("0x{:X}", (DWORD64)selected_thread).c_str());
                    if (ImGui::Button(fmt::format("m_stack: 0x{:X}", (DWORD64)selected_thread->m_stack).c_str()))
                        miscellaneous::set_clipboard(fmt::format("0x{:X}", (DWORD64)selected_thread->m_stack).c_str());
                    ImGui::Text(fmt::format("m_exit_message: {}", (selected_thread->m_exit_message) ? selected_thread->m_exit_message : "").c_str());
                    if (ImGui::Button(fmt::format("m_handler: 0x{:X}", (DWORD64)selected_thread->m_handler).c_str()))
                        miscellaneous::set_clipboard(fmt::format("0x{:X}", (DWORD64)selected_thread->m_handler).c_str());
                    if (selected_thread->m_net_component != nullptr && ImGui::Button(fmt::format("m_net_component: 0x{:X}", (DWORD64)selected_thread->m_net_component).c_str()))
                        miscellaneous::set_clipboard(fmt::format("0x{:X}", (DWORD64)selected_thread->m_net_component).c_str());
                    ImGui::Text(fmt::format("m_thread_id: {}", selected_thread->m_context.m_thread_id).c_str());
                    ImGui::Text(fmt::format("m_instance_id: {}", selected_thread->m_instance_id).c_str());
                    ImGui::Text(fmt::format("m_flag1: {:X}", selected_thread->m_flag1).c_str());
                    ImGui::Text(fmt::format("m_safe_for_network_game: {}", selected_thread->m_safe_for_network_game).c_str());
                    ImGui::Text(fmt::format("m_is_minigame_script: {}", selected_thread->m_is_minigame_script).c_str());
                    ImGui::Text(fmt::format("m_can_be_paused: {}", selected_thread->m_can_be_paused).c_str());
                    ImGui::Text(fmt::format("m_can_remove_blips_from_other_scripts: {}", selected_thread->m_can_remove_blips_from_other_scripts).c_str());
                    if (ImGui::Button("Kill Script"))
                    {
                        QUEUE_JOB_BEGIN_CLAUSE()
                        {
                            SCRIPT::TERMINATE_THREAD(selected_thread->m_context.m_thread_id);
                        }QUEUE_JOB_END_CLAUSE
                    }
                    static char scriptnames[255];
                    ImGui::InputText("##Scriptnames", scriptnames, IM_ARRAYSIZE(scriptnames));
                    if (ImGui::Button("Request Script"))
                    {
                        QUEUE_JOB_BEGIN_CLAUSE()
                        {
                            rage_helper::execute_as_script(RAGE_JOAAT("freemode"), [] {
                                auto hash = rage::joaat(scriptnames);
                                SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH(hash);
                                while (!SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(hash))
                                {
                                    script::get_current()->yield();
                                }
                                SYSTEM::START_NEW_SCRIPT_WITH_NAME_HASH(hash, 31000);
                                SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(hash);
                            });
                        }QUEUE_JOB_END_CLAUSE
                    }
                }
                ImGui::EndGroup();
                ImGui::Separator();
            }
            if (ImGui::CollapsingHeader(xorstr(ICON_FA_DESKTOP " Script Event Tester")))
            {
                static event_json::event_json event_obj{};
                ImGui::SliderInt(xorstr("Size Of Event Array"), &event_obj.size_of_args_array, 2, 53);
                event_obj.args.resize(event_obj.size_of_args_array);
                event_obj.arg_is_hex.resize(event_obj.size_of_args_array - 2);
                ImGui::PushItemWidth(300.f);
                ImGui::InputScalar(xorstr("Event ID"), ImGuiDataType_S64, &event_obj.args[0]);
                ImGui::PopItemWidth();
                for (int i = 2; i < event_obj.size_of_args_array; i++)
                {
                    ImGui::PushItemWidth(200.f);
                    ImGui::InputScalar(fmt::format("Arg #{}", i).c_str(), ((event_obj.arg_is_hex[i - 2]) ? ImGuiDataType_U64 : ImGuiDataType_S64), &event_obj.args[i], NULL, NULL, ((event_obj.arg_is_hex[i - 2]) ? "%p" : NULL), ((event_obj.arg_is_hex[i - 2]) ? ImGuiInputTextFlags_CharsHexadecimal : ImGuiInputTextFlags_CharsDecimal));
                    ImGui::PopItemWidth();
                    ImGui::SameLine();
                    ImGui::PushItemWidth(50.0f);
                    bool arg_is_hex_tmp = event_obj.arg_is_hex[i - 2];
                    if (ImGui::Checkbox(fmt::format("Hex##{}", i).c_str(), &arg_is_hex_tmp))
                        event_obj.arg_is_hex[i - 2] = arg_is_hex_tmp;
                    ImGui::PopItemWidth();
                    if (i != (event_obj.size_of_args_array - 1) && ((i - 1) % 3 != 0))
                        ImGui::SameLine();
                }
                static int selected_target = 0;
                ImGui::PushItemWidth(200.f);

                if (ImGui::BeginCombo(xorstr("Target Player"), player::get_player_name(g_event_tester.event_player)))
                {
                    for (auto player_list : g_misc_option->player_names)
                    {
                        if (!g_misc_option->player_names.empty())
                        {
                            if (ImGui::Selectable(player_list.second.name, player_list.second.id == g_event_tester.event_player))
                            {
                                if (selected_target != player_list.second.id)
                                    selected_target = player_list.second.id;

                                if (g_event_tester.event_player != player_list.second.id)
                                    g_event_tester.event_player = player_list.second.id;
                            }
                        }
                    }
                    ImGui::EndCombo();
                }
                ImGui::PopItemWidth();
                ImGui::SameLine();
                if (ImGui::Button(xorstr("Send Event")))
                {
                    event_obj.args[1] = g_local.player;//g_event_tester.event_ped;
                    QUEUE_JOB_BEGIN()
                    {
                        SCRIPT::TRIGGER_SCRIPT_EVENT(1, &event_obj.args[0], event_obj.size_of_args_array, (1 << g_event_tester.event_player));
                    } QUEUE_JOB_END
                }

                auto events = script_tester::list_events();
                static std::string selected_event;
                ImGui::PushItemWidth(250);
                ImGui::Text("Saved Events");
                if (ImGui::ListBoxHeader("##empty", ImVec2(200, 200)))
                {
                    for (auto pair : events)
                    {
                        if (ImGui::Selectable(pair.c_str(), selected_event == pair))
                            selected_event = pair;
                    }
                    ImGui::ListBoxFooter();
                }
                ImGui::SameLine();
                ImGui::BeginGroup();
                static char event_name[50]{};
                ImGui::PushItemWidth(250);
                ImGui::InputText(xorstr("##EventName"), event_name, IM_ARRAYSIZE(event_name));
                if (ImGui::Button(xorstr("Save Event")))
                {
                    script_tester::save_event(event_name, event_obj);
                }
                if (ImGui::Button(xorstr("Load Event")))
                {
                    script_tester::load_event_menu(selected_event, event_obj);
                }
                if (ImGui::Button(xorstr("Delete Event")))
                {
                    if (!selected_event.empty())
                    {
                        script_tester::delete_event(selected_event);
                        selected_event.clear();
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button(xorstr("Clear")))
                {
                    event_obj.size_of_args_array = 2;
                    event_obj.args.clear();
                    event_obj.arg_is_hex.clear();
                }
                ImGui::EndGroup();
                ImGui::Separator();
            }
            if (*g_pointers->m_script_globals != nullptr)
            {
                if (ImGui::CollapsingHeader(xorstr(ICON_FA_DESKTOP " Global Script Editor")))
                {
                    static global_test_json::global_test_json global_test{};
                    static script_global glo_bal_sunday = script_global(global_test.global_index);
                    ImGui::SetNextItemWidth(200.f);
                    if (ImGui::InputScalar("Global", ImGuiDataType_U64, &global_test.global_index))
                        glo_bal_sunday = script_global(global_test.global_index);

                    for (int i = 0; i < global_test.global_appendages.size(); i++)
                    {
                        auto item = global_test.global_appendages[i];
                        switch (item.type)
                        {
                        case GlobalAppendageType_At:
                            ImGui::SetNextItemWidth(200.f);
                            ImGui::InputScalar(fmt::format("At##{}{}", i, item.type).c_str(), ImGuiDataType_S64, &global_test.global_appendages[i].index);
                            ImGui::SameLine();
                            ImGui::SetNextItemWidth(200.f);
                            ImGui::InputScalar(fmt::format("Size##{}{}", i, item.type).c_str(), ImGuiDataType_S64, &global_test.global_appendages[i].size);
                            break;
                        case GlobalAppendageType_ReadGlobal:
                            ImGui::Text(fmt::format("Read Global {}", item.global_name).c_str());
                            ImGui::SameLine();
                            ImGui::SetNextItemWidth(200.f);
                            ImGui::InputScalar(fmt::format("Size##{}{}", i, item.type).c_str(), ImGuiDataType_S64, &global_test.global_appendages[i].size);
                            break;
                        case GlobalAppendageType_PlayerId:
                            ImGui::SetNextItemWidth(200.f);
                            ImGui::InputScalar(fmt::format("Read Player ID Size##{}{}", i, item.type).c_str(), ImGuiDataType_S64, &global_test.global_appendages[i].size);
                            break;
                        }
                    }

                    if (ImGui::Button(xorstr("Add Offset")))
                        global_test.global_appendages.push_back({ GlobalAppendageType_At, 0LL, 0ULL });
                    ImGui::SameLine();
                    if (ImGui::Button("Add Read Player Id"))
                        global_test.global_appendages.push_back({ GlobalAppendageType_PlayerId, 0LL, 0ULL });

                    if (global_test.global_appendages.size() > 0 && ImGui::Button("Remove Offset"))
                        global_test.global_appendages.pop_back();
                    static int Global_Type = 0;
                    ImGui::RadioButton("Integer##Global", &Global_Type, 0);
                    ImGui::SameLine();
                    ImGui::RadioButton("Float##Global", &Global_Type, 1);
                    ImGui::SameLine();
                    ImGui::RadioButton("String##Global", &Global_Type, 2);

                    if (auto ptr = global_tester::get_global_ptr(global_test))
                    {
                        ImGui::SetNextItemWidth(200.f);
                        if (Global_Type != 2)
                            ImGui::InputScalar(xorstr("Value"), Global_Type == 0 ? ImGuiDataType_S64 : Global_Type == 1 ? ImGuiDataType_Float : ImGuiDataType_S64, ptr);

                    }
                    else
                        ImGui::Text(xorstr("INVALID_GLOBAL_READ"));

                    auto globals = list_globals();
                    static std::string selected_global;
                    ImGui::Text(xorstr("Saved Globals"));
                    if (ImGui::ListBoxHeader(xorstr("##savedglobals"), ImVec2(200, 200)))
                    {
                        for (auto pair : globals)
                        {
                            if (ImGui::Selectable(pair.first.c_str(), selected_global == pair.first))
                                selected_global = std::string(pair.first);
                        }
                        ImGui::ListBoxFooter();
                    }
                    ImGui::SameLine();
                    if (ImGui::ListBoxHeader(xorstr("##globalvalues"), ImVec2(200, 200)))
                    {
                        for (auto pair : globals)
                        {
                            if (auto ptr = global_tester::get_global_ptr(pair.second))
                                ImGui::Selectable(fmt::format("{}", *ptr).c_str(), false, ImGuiSelectableFlags_Disabled);
                            else
                                ImGui::Selectable(xorstr("INVALID_GLOBAL_READ"), false, ImGuiSelectableFlags_Disabled);
                        }
                        ImGui::ListBoxFooter();
                    }
                    ImGui::SameLine();
                    ImGui::BeginGroup();
                    static char global_name[50]{};
                    ImGui::SetNextItemWidth(200.f);
                    ImGui::InputText(xorstr("##GlobalName"), global_name, IM_ARRAYSIZE(global_name));

                    if (ImGui::Button(xorstr("Save Global")))
                    {
                        global_tester::save_global(global_name, global_test);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(xorstr("Load Global")))
                    {
                        global_tester::load_global_menu(selected_global, global_test);
                    }

                    if (ImGui::Button(xorstr("Delete Global")))
                    {
                        if (!selected_global.empty())
                        {
                            global_tester::delete_global(selected_global);
                            selected_global.clear();
                        }
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(xorstr("Add Read Global")))
                    {
                        global_test.global_appendages.push_back({ GlobalAppendageType_ReadGlobal, 0LL, 0ULL, selected_global });
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(xorstr("Clear")))
                    {
                        global_test.global_index = 0;
                        global_test.global_appendages.clear();
                    }
                    ImGui::EndGroup();
                    ImGui::Separator();
                }
            }
            if (ImGui::CollapsingHeader(xorstr(ICON_FA_DESKTOP " Local Script Editor")))
            {
                static GtaThread* selected_thread{};
                if (ImGui::ListBoxHeader(xorstr("##scriptslocal"), ImVec2(250, 500)))
                {
                    if (g_settings.options["script monitor sorted"])
                    {
                        std::map<std::string, GtaThread*> sorted_threads;
                        for (auto thread : *g_pointers->m_script_threads)
                            if (thread && thread->m_context.m_thread_id && thread->m_handler)
                                sorted_threads[thread->m_name] = thread;
                        for (auto thread : sorted_threads)
                            if (ImGui::Selectable(thread.second->m_name, thread.second == selected_thread))
                                selected_thread = thread.second;
                    }
                    else
                    {
                        for (auto thread : *g_pointers->m_script_threads)
                            if (thread && thread->m_context.m_thread_id && thread->m_handler)
                                if (ImGui::Selectable(thread->m_name, thread == selected_thread))
                                    selected_thread = thread;
                    }
                    ImGui::ListBoxFooter();
                }

                if (selected_thread != nullptr)
                {
                    ImGui::SameLine();
                    ImGui::BeginGroup();
                    if (ImGui::Checkbox(xorstr("Sorted?"), g_settings.options["script monitor sorted"].get<bool*>()))
                        g_settings.save();
                    static local_test_json::local_test_json local_test{};
                    static script_local local_sunday = script_local(selected_thread, local_test.local_index);
                    ImGui::SetNextItemWidth(200.f);
                    if (ImGui::InputScalar(xorstr("Local"), ImGuiDataType_U64, &local_test.local_index))
                        local_sunday = script_local(selected_thread, local_test.local_index);

                    for (int i = 0; i < local_test.local_appendages.size(); i++)
                    {
                        auto item = local_test.local_appendages[i];
                        switch (item.type)
                        {
                        case LocalAppendageType_At:
                            ImGui::SetNextItemWidth(200.f);
                            ImGui::InputScalar(fmt::format("At##Local{}{}", i, item.type).c_str(), ImGuiDataType_S64, &local_test.local_appendages[i].index);
                            ImGui::SameLine();
                            ImGui::SetNextItemWidth(200.f);
                            ImGui::InputScalar(fmt::format("Size##Local{}{}", i, item.type).c_str(), ImGuiDataType_S64, &local_test.local_appendages[i].size);
                            break;
                        case LocalAppendageType_ReadGlobal:
                            ImGui::Text(fmt::format("Read Local {}", item.local_name).c_str());
                            ImGui::SameLine();
                            ImGui::SetNextItemWidth(200.f);
                            ImGui::InputScalar(fmt::format("Size##{}{}", i, item.type).c_str(), ImGuiDataType_S64, &local_test.local_appendages[i].size);
                            break;
                        case LocalAppendageType_PlayerId:
                            ImGui::SetNextItemWidth(200.f);
                            ImGui::InputScalar(fmt::format("Read Player ID Size##Local{}{}", i, item.type).c_str(), ImGuiDataType_S64, &local_test.local_appendages[i].size);
                            break;
                        }
                    }

                    if (ImGui::Button(xorstr("Add Offset##Local")))
                        local_test.local_appendages.push_back({ LocalAppendageType_At, 0LL, 0ULL });
                    ImGui::SameLine();
                    if (ImGui::Button(xorstr("Add Read Player Id##Local")))
                        local_test.local_appendages.push_back({ LocalAppendageType_PlayerId, 0LL, 0ULL });

                    if (local_test.local_appendages.size() > 0 && ImGui::Button(xorstr("Remove Offset")))
                        local_test.local_appendages.pop_back();
                    static int Local_Type = 0;
                    ImGui::RadioButton(xorstr("Integer##Local"), &Local_Type, 0);
                    ImGui::SameLine();
                    ImGui::RadioButton(xorstr("Float##Local"), &Local_Type, 1);
                    ImGui::SameLine();
                    ImGui::RadioButton(xorstr("String##Local"), &Local_Type, 2);

                    if (auto ptr = local_tester::get_local_ptr(selected_thread, local_test))
                    {
                        ImGui::SetNextItemWidth(200.f);
                        if (Local_Type != 2)
                            ImGui::InputScalar("Value##Local", Local_Type == 0 ? ImGuiDataType_S32 : Local_Type == 1 ? ImGuiDataType_Float : ImGuiDataType_S32, ptr);
                    }
                    else
                        ImGui::Text(xorstr("INVALID_LOCAL_READ"));

                    auto locals = list_locals();
                    static std::string selected_local;
                    ImGui::Text(xorstr("Saved Locals"));
                    if (ImGui::ListBoxHeader(xorstr("##savedlocals"), ImVec2(200, 200)))
                    {
                        for (auto pair : locals)
                        {
                            if (ImGui::Selectable(pair.first.c_str(), selected_local == pair.first))
                                selected_local = std::string(pair.first);
                        }
                        ImGui::ListBoxFooter();
                    }
                    ImGui::SameLine();
                    if (ImGui::ListBoxHeader(xorstr("##localvalues"), ImVec2(200, 200)))
                    {
                        for (auto pair : locals)
                        {
                            if (auto ptr = local_tester::get_local_ptr(selected_thread, pair.second))
                                ImGui::Selectable(fmt::format("{}", *ptr).c_str(), false, ImGuiSelectableFlags_Disabled);
                            else
                                ImGui::Selectable(xorstr("INVALID_LOCAL_READ"), false, ImGuiSelectableFlags_Disabled);
                        }
                        ImGui::ListBoxFooter();
                    }
                    static char local_name[50]{};
                    ImGui::SetNextItemWidth(200.f);
                    ImGui::InputText("##LocalName", local_name, IM_ARRAYSIZE(local_name));

                    if (ImGui::Button("Save Local"))
                    {
                        local_tester::save_local(local_name, local_test);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Load Local"))
                    {
                        local_tester::load_local_menu(selected_local, local_test);
                    }

                    if (ImGui::Button("Delete Local"))
                    {
                        if (!selected_local.empty())
                        {
                            local_tester::delete_local(selected_local);
                            selected_local.clear();
                        }
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Add Read Local"))
                    {
                        local_test.local_appendages.push_back({ LocalAppendageType_ReadGlobal, 0LL, 0ULL, selected_local });
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Clear Local"))
                    {
                        local_test.local_index = 0;
                        local_test.local_appendages.clear();
                    }
                    ImGui::EndGroup();
                    ImGui::Separator();
                }
            }
            if (ImGui::CollapsingHeader(xorstr(ICON_FA_CLOUD_DOWNLOAD_ALT " Stat Loader")))
            {
                static stats_json::stats_json stat_obj{};
                static bool loaded = false;
                ImGui::PushItemWidth(150);
                if (ImGui::InputInt("Stats", &stat_obj.stats, 1, 80))
                {
                    if (stat_obj.stats == 0)
                        stat_obj.stats = 1;
                    if (stat_obj.stats > 250)
                        stat_obj.stats = 250;
                }
                ImGui::PopItemWidth();
                stat_obj.stat_type.resize(stat_obj.stats);
                stat_obj.stat_name.resize(stat_obj.stats);
                stat_obj.stat_int_value.resize(stat_obj.stats);
                stat_obj.stat_bool_value.resize(stat_obj.stats);
                stat_obj.stat_float_value.resize(stat_obj.stats);
                ImGui::Separator();
                for (int i = 0; i < stat_obj.stats; i++)
                {
                    ImGui::Text(fmt::format("Stat #{}", i + 1).c_str());
                    ImGui::RadioButton(fmt::format("INT##{}", i + 1).c_str(), &stat_obj.stat_type[i], 0); ImGui::SameLine();
                    ImGui::RadioButton(fmt::format("BOOL##{}", i + 1).c_str(), &stat_obj.stat_type[i], 1); ImGui::SameLine();
                    ImGui::RadioButton(fmt::format("FLOAT##{}", i + 1).c_str(), &stat_obj.stat_type[i], 2);
                    ImGui::PushItemWidth(450);

                    ImGui::InputText(fmt::format("##name{}", i + 1).c_str(), (char*)stat_obj.stat_name[i].c_str(), stat_obj.stat_name[i].capacity() * 2, ImGuiInputTextFlags_CharsUppercase);

                    ImGui::PopItemWidth();
                    if (stat_obj.stat_type[i] == 0)
                    {
                        ImGui::SameLine();
                        ImGui::PushItemWidth(250);
                        ImGui::InputInt(fmt::format("##int{}", i + 1).c_str(), &stat_obj.stat_int_value[i]);
                        ImGui::PopItemWidth();
                    }
                    else if (stat_obj.stat_type[i] == 1)
                    {
                        ImGui::SameLine();
                        bool stat_bool_value_tmp = stat_obj.stat_bool_value[i];
                        if (ImGui::Checkbox(fmt::format("##bool{}", i + 1).c_str(), &stat_bool_value_tmp))
                            stat_obj.stat_bool_value[i] = stat_bool_value_tmp;
                    }
                    else if (stat_obj.stat_type[i] == 2)
                    {
                        ImGui::SameLine();
                        ImGui::PushItemWidth(250);
                        ImGui::InputScalar(fmt::format("##float{}", i + 1).c_str(), ImGuiDataType_Float, &stat_obj.stat_float_value[i], NULL, NULL);
                        ImGui::PopItemWidth();
                    }
                }
                if (ImGui::Button("Set Stats"))
                {
                    for (int i = 0; i < stat_obj.stats; i++)
                    {
                        strcpy((char*)stat_obj.stat_name[i].c_str(), std::regex_replace(stat_obj.stat_name[i], std::regex(R"(\$)"), "").c_str());
                        strcpy((char*)stat_obj.stat_name[i].c_str(), std::regex_replace(stat_obj.stat_name[i], std::regex(R"(\MPX)"), "MP" + std::to_string(rage_helper::get_character())).c_str());
                        strcpy((char*)stat_obj.stat_name[i].c_str(), std::regex_replace(stat_obj.stat_name[i], std::regex(R"(\MPx)"), "MP" + std::to_string(rage_helper::get_character())).c_str());

                        const auto hash = rage::joaat(stat_obj.stat_name[i]);

                        g_fiber_pool->queue_job([i, hash]
                        {
                            if (stat_obj.stat_type[i] == 0)
                            {
                                STATS::STAT_SET_INT(hash, stat_obj.stat_int_value[i], true);
                            }
                            else if (stat_obj.stat_type[i] == 1)
                            {
                                STATS::STAT_SET_BOOL(hash, stat_obj.stat_bool_value[i], true);
                            }
                            else if (stat_obj.stat_type[i] == 2)
                            {
                                STATS::STAT_SET_FLOAT(hash, stat_obj.stat_float_value[i], true);
                            }
                        });
                    }
                }
                ImGui::Separator();
                auto stats = stats::list_stats();
                static std::string selected_stat;
                ImGui::PushItemWidth(250);
                ImGui::Text("Saved Stats");
                if (ImGui::ListBoxHeader("##empty", ImVec2(200, 200)))
                {
                    for (auto pair : stats)
                    {
                        if (ImGui::Selectable(pair.c_str(), selected_stat == pair))
                            selected_stat = pair;
                    }
                    ImGui::ListBoxFooter();
                }
                ImGui::PopItemWidth();
                ImGui::SameLine();
                ImGui::BeginGroup();
                static char save_stat_name[50]{};
                ImGui::PushItemWidth(250);
                ImGui::InputText("##save_stat_name", save_stat_name, IM_ARRAYSIZE(save_stat_name));
                if (ImGui::Button("Save Stat"))
                {
                    stats::save_stat(save_stat_name, stat_obj);
                }
                ImGui::SameLine();
                if (ImGui::Button("Load Stat"))
                {
                    stats::load_stat_menu(selected_stat, stat_obj);
                }
                ImGui::SameLine();
                if (ImGui::Button("Delete Stat"))
                {
                    if (!selected_stat.empty())
                    {
                        stats::delete_stat(selected_stat);
                        selected_stat.clear();
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button("Clear"))
                {
                    stat_obj.stats = 1;
                    stat_obj.stat_type.clear();
                    stat_obj.stat_name.clear();
                    stat_obj.stat_int_value.clear();
                    stat_obj.stat_bool_value.clear();
                    stat_obj.stat_float_value.clear();
                }
                ImGui::PopItemWidth();
                ImGui::EndGroup();
                ImGui::Separator();
            }
            ImGui::Separator();
            if (ImGui::Button(xorstr(ICON_FA_SIGN_OUT_ALT" Unload Mod Menu")))
            {
                message::notification("~bold~~g~Menu Unloaded", "~bold~~g~Ellohim Unloader");
                g_running = false;
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr(ICON_FA_POWER_OFF " Exit Game")))
            {
                game_window::logout();
                exit(0);
            }
            ImGui::EndTabItem();
        }
    }
}