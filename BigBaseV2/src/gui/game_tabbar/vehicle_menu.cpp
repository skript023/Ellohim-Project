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
#include "gui/helper_function.hpp"
#include "vehicle_menu.h"
#include "gui/vehicle/vehicle_list.hpp"

namespace big
{
    void vehicle_tab::render_vehicle_tab(const char* tab_name)
    {
        if (ImGui::BeginTabItem(tab_name))
        {
            memset(&g_vehicle_option->vehicle_tab_open, true, 1);
            ImGui::InputText(xorstr("##Kosong"), nama_mobil, IM_ARRAYSIZE(nama_mobil), ImGuiInputTextFlags_CharsUppercase);
            ImGui::PushItemWidth(100.f);
            ImGui::InputScalar(xorstr("##Num"), ImGuiDataType_S32, &total_ped);
            ImGui::PopItemWidth();
            if (ImGui::Button(xorstr("Native")))
            {
                vehicle_helper::vehicle(nama_mobil, g_local.ped);
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr("External")))
            {
                vehicle_helper::SpawnVehicle(nama_mobil, FALSE, g_local.player);
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr("Personal")))
            {
                int vehicle_index = vehicle_helper::get_vehicle_index_from_hash(rage::joaat(nama_mobil));
                vehicle_helper::call_personal_vehicle(vehicle_index);
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr("Convoy")))
            {
                ai::Convoy(nama_mobil, total_ped);
            }
            ImGui::Separator();
            
            ImGui::RadioButton(xorstr("Vehicle"), &vehicle_menu, 0);
            ImGui::SameLine();
            ImGui::RadioButton(xorstr("Personal Vehicle"), &vehicle_menu, 1);
            ImGui::SameLine();
            ImGui::RadioButton(xorstr("Saved Vehicle"), &vehicle_menu, 2);

            memset(&g_vehicle_option->personal_vehicle_menu, vehicle_menu == 1, sizeof(g_vehicle_option->personal_vehicle_menu));
            memset(&g_vehicle_option->vehicle_list_menu, vehicle_menu == 0, sizeof(g_vehicle_option->personal_vehicle_menu));

            switch (vehicle_menu)
            {
            case 0:
                ImGui::PushItemWidth(250);
                if (ImGui::Combo(xorstr("##VehicleCategory"), &selected_category, vehicles_hash::vehicle_category_list, IM_ARRAYSIZE(vehicles_hash::vehicle_category_list)))
                    memset(&g_vehicle_option->vehicle_types_menu, selected_category, sizeof(g_vehicle_option->personal_vehicle_menu));

                if (ImGui::ListBoxHeader(xorstr("##Vehicle List")))
                {
                    for (auto get_vehicle : g_get_vehicle->get_vehicle_data)
                    {
                        if (ImGui::Selectable(get_vehicle.first.c_str(), get_vehicle.second.hash == SelectedVehicleHash))
                        {
                            if (SelectedVehicleHash != get_vehicle.second.hash)
                                SelectedVehicleHash = get_vehicle.second.hash;

                            if (strcmp(SelectedVehicle, get_vehicle.second.hash_key) != 0)
                                strcpy(SelectedVehicle, get_vehicle.second.hash_key);
                        }
                    }
                    ImGui::ListBoxFooter();
                }
                ImGui::PopItemWidth();
                ImGui::SameLine();
                ImGui::BeginGroup();
                if (ImGui::Button(xorstr("Spawn Native")))
                {
                    vehicle_helper::vehicle(SelectedVehicle, g_local.ped);
                }
                ImGui::SameLine();
                if (ImGui::Button(xorstr("Spawn External")))
                {
                    vehicle_helper::SpawnVehicle(SelectedVehicle, FALSE, g_local.player);
                }
                ImGui::EndGroup();
            break;
            case 1:
                ImGui::PushItemWidth(250);
                ImGui::Text(xorstr("Vehicle Changer"));
                ImGui::Combo(xorstr("##Change"), &selected_hash, game_variable::vehicle_hash_list, IM_ARRAYSIZE(game_variable::vehicle_hash_list));
                ImGui::PopItemWidth();
                ImGui::SameLine();
                if (ImGui::Button(xorstr("Change")))
                {
                    *script_global(g_global.garage).at(SelectedPersonal, 142).at(66).as<uint32_t*>() = rage::joaat(game_variable::vehicle_hash_list[selected_hash]);
                }
                ImGui::PushItemWidth(250);
                if (ImGui::ListBoxHeader(xorstr("##Personal Vehicle List")))
                {
                    if (!g_vehicle_option->personal_vehicle_list.empty())
                    {
                        for (auto personal_vehicle : g_vehicle_option->personal_vehicle_list)
                        {
                            if (strcmp(personal_vehicle.first.c_str(), "Not Found") != 0)
                            {
                                if (ImGui::Selectable((personal_vehicle.first.c_str()), personal_vehicle.second == SelectedPersonal))
                                {
                                    SelectedPersonal = personal_vehicle.second;
                                }
                            }
                        }
                    }
                    ImGui::ListBoxFooter();
                }
                ImGui::PopItemWidth();
                ImGui::SameLine();
                ImGui::BeginGroup();
                if (ImGui::Button(xorstr("Call Personal")))
                {
                    vehicle_helper::call_personal_vehicle(SelectedPersonal);
                }
                ImGui::EndGroup();
            break;
            case 2:
                static char vehicle_file_name_input[50]{};
                ImGui::PushItemWidth(250);
                ImGui::InputText(xorstr("Vehicle File Name"), vehicle_file_name_input, IM_ARRAYSIZE(vehicle_file_name_input));
                ImGui::PopItemWidth();
                if (ImGui::Button(xorstr("Save Vehicle ##SaveVeh")))
                {
                    QUEUE_JOB_BEGIN_CLAUSE()
                    {
                        persist_car::do_save_vehicle(vehicle_file_name_input);
                    } QUEUE_JOB_END_CLAUSE
                }
                auto vehicle_files = persist_car::list_files();
                static std::string selected_vehicle_file;
                ImGui::PushItemWidth(250);
                ImGui::Text(xorstr("Saved Vehicles"));
                if (ImGui::ListBoxHeader(xorstr("##empty"), ImVec2(200, 200)))
                {
                    for (auto pair : vehicle_files)
                    {
                        if (ImGui::Selectable(pair.c_str(), selected_vehicle_file == pair))
                            selected_vehicle_file = pair;
                    }
                    ImGui::ListBoxFooter();
                }
                ImGui::SameLine();
                ImGui::BeginGroup();
                ImGui::PushItemWidth(250);

                if (ImGui::Button(xorstr("Load Vehicle")))
                {
                    QUEUE_JOB_BEGIN_CLAUSE()
                    {
                        big::persist_car::do_load_vehicle(selected_vehicle_file);
                    } QUEUE_JOB_END_CLAUSE
                }
                if (ImGui::Checkbox(xorstr("Set To Spawned Vehicle"), g_settings.options["Auto Get-in"].get<bool*>()))
                    g_settings.save();

                ImGui::PopItemWidth();
                ImGui::EndGroup();
            break;
            }

            ImGui::Separator();
            if (ImGui::Checkbox(xorstr("Full Upgrade"), g_settings.options["Full Upgrade Bool"].get<bool*>()))
                g_settings.save();
            ImGui::SameLine(200);
            if (ImGui::Checkbox(xorstr("Auto Get-in"), g_settings.options["Auto Get-in"].get<bool*>()))
                g_settings.save();
            ImGui::Separator();

            if (ImGui::Checkbox(xorstr("Vehicle Godmode"), g_settings.options["Vehicle Godmode"].get<bool*>()))
                g_settings.save();
            ImGui::SameLine(200);
            ImGui::Checkbox("Seat Belt", g_settings.options["Seatbelt"].get<bool*>());
            if (ImGui::Checkbox(xorstr("Boost Flag"), &BoostFlag))
            {
                if (BoostFlag)
                {
                    vehicle_helper::set_vehicle_flag(4,30);
                }
                else if (!BoostFlag)
                {
                    vehicle_helper::clear_vehicle_flag(4,30);
                }
            }
            ImGui::SameLine(200);
            if (ImGui::Checkbox(xorstr("Jump Flag"), &JumpFlag))
            {
                if (JumpFlag)
                {
                    vehicle_helper::set_vehicle_flag(4,29);
                }
                else if (!JumpFlag)
                {
                    vehicle_helper::clear_vehicle_flag(4,29);
                }
            }
            ImGui::SameLine(400);
            if (ImGui::Checkbox(xorstr("Parachute Flag"), &ParachuteFlag))
            {
                if (ParachuteFlag)
                {
                    vehicle_helper::set_vehicle_flag(5,0);
                }
                else if (!ParachuteFlag)
                {
                    vehicle_helper::clear_vehicle_flag(5,0);
                }
            }
            if (ImGui::Checkbox(xorstr("Oppressor Flag"), &OppressorFlag))
            {
                if (OppressorFlag)
                {
                    vehicle_helper::set_vehicle_flag(4, 1);
                }
                else if (!OppressorFlag)
                {
                    vehicle_helper::clear_vehicle_flag(4, 1);
                }
            }
            ImGui::SameLine(200);
            ImGui::Checkbox(xorstr("Horn Boost"), &g_vehicle_option->horn_boost);
            ImGui::SameLine(400);
            if (ImGui::Checkbox(xorstr("PV Revenge"), g_settings.options["PV Revenge"].get<bool*>()))
                g_settings.save();
            ImGui::Checkbox(xorstr("Infinite Boost On Key"), &g_vehicle_option->infinite_boost);
            ImGui::SameLine(200);
            ImGui::Checkbox(xorstr("Infinite Vehicle Ammo"), &g_vehicle_option->infinite_ammo);
            ImGui::SameLine(400);
            if (ImGui::Checkbox(xorstr("Activate Turn Lamp"), g_settings.options["Vehicle Light Control"].get<bool*>()))
                g_settings.save();

            ImGui::Checkbox(xorstr("Drive Underwater"), &g_vehicle_option->drive_underwater);

            ImGui::Separator();

            if (ImGui::Button(xorstr("Repair Vehicle")))
            {
                vehicle_helper::repair_vehicle(g_local.ped);
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr("Get-in Closest Vehicle")))
            {
                g_fiber_pool->queue_job([]
                {
                    rage::CVehicleInterface* vehicle_interface = g_pointers->m_replay_interface->m_vehicle_interface;
                    for (int i = 0; i < vehicle_interface->m_max_vehicles; i++)
                    {
                        auto* vehicle_ptr = vehicle_interface->get_vehicle(i);
                        if (vehicle_ptr == nullptr)
                            continue;

                        Vehicle vehicle = g_pointers->m_ptr_to_handle(vehicle_ptr);
                        if (vehicle == 0)
                            break;

                        PED::SET_PED_INTO_VEHICLE(g_local.ped, vehicle, -1);
                    }
                });
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr("Set Ownership of Vehicle")))
            {
                *script_global(2097152).at(6175, 2).as<int*>() = -1;
                *script_global(2440277).at(502).at(16).as<int*>() = 1;
            }
            
            if (ImGui::Button(xorstr("Shinra Tensei")))
            {
                g_fiber_pool->queue_job([] {
                    rage::CObjectInterface* objIF = g_pointers->m_replay_interface->m_object_interface;
                    rage::CVehicleInterface* vehIF = g_pointers->m_replay_interface->m_vehicle_interface;
                    auto pedIF = g_pointers->m_replay_interface->m_ped_interface;
                    int numObj = objIF->m_max_objects;
                    for (int i = 0; i < numObj; i++)
                    {
                        rage::CObject* pCObject = objIF->get_object(i);
                        auto pCVehicle = vehIF->get_vehicle(i);
                        auto pCPed = pedIF->get_ped(i);
                        if (pCObject == nullptr || pCVehicle == nullptr || pCPed == nullptr)
                            continue;

                        Object object = rage_helper::pointer_to_entity(pCObject);
                        Vehicle vehicle = rage_helper::pointer_to_entity(pCVehicle);
                        Ped ped = rage_helper::pointer_to_entity(pCPed);
                        if (object == 0 || vehicle == 0 || ped == 0)
                            continue;

                        if (!PED::IS_PED_A_PLAYER(ped))
                        {
                            network::request_control(vehicle);
                            ENTITY::APPLY_FORCE_TO_ENTITY(object, 3, 150.0f, 180.0f, 200.0f, 20.0f, 20.0f, 50.0f, 0, FALSE, TRUE, TRUE, FALSE, TRUE);
                            ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 3, 150.0f, 180.0f, 200.0f, 20.0f, 20.0f, 50.0f, 0, FALSE, TRUE, TRUE, FALSE, TRUE);
                            ENTITY::APPLY_FORCE_TO_ENTITY(ped, 3, 150.0f, 180.0f, 200.0f, 20.0f, 20.0f, 50.0f, 0, FALSE, TRUE, TRUE, FALSE, TRUE);
                        }
                    }
                });
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr("Penis Truct")))
            {
                QUEUE_JOB_BEGIN_CLAUSE()
                {
                    auto pos = player::get_player_coords(PLAYER::PLAYER_ID());
                    auto heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
                    Vehicle playerVeh = vehicle_helper::create_vehicle(0x50B0215A, pos.x * 10, pos.y * 10, pos.z, heading);
                    VEHICLE::SET_VEHICLE_COLOURS(playerVeh, 64, 40);
                    VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(playerVeh, 1);

                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                    Object spawnedOrange = OBJECT::CREATE_OBJECT_NO_OFFSET(0x8DA1C0E, pos.x * 10, pos.y * 10, pos.z, TRUE, FALSE, FALSE);
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

                    ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, 0, -0.690002, 2.089998, 0, 0, 90, false, false, true, false, 0, true); //1
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                    spawnedOrange = OBJECT::CREATE_OBJECT_NO_OFFSET(0x8DA1C0E, pos.x * 10, pos.y * 10, pos.z, TRUE, FALSE, FALSE);
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

                    ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, 0, -6, 2.08998, 0, -22, 90, false, false, true, false, 0, true); //2
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                    spawnedOrange = OBJECT::CREATE_OBJECT_NO_OFFSET(0x8DA1C0E, pos.x * 10, pos.y * 10, pos.z, TRUE, FALSE, FALSE);
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

                    ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, 0, -3.35, 2.500000, 0, -11, 90, false, false, true, false, 0, true); //3
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                    spawnedOrange = OBJECT::CREATE_OBJECT_NO_OFFSET(0x8DA1C0E, pos.x * 10, pos.y * 10, pos.z, TRUE, FALSE, FALSE);
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

                    ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, -0.5, -3.35, 3, 0, -11, 90, false, false, true, false, 0, true); //4
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                    spawnedOrange = OBJECT::CREATE_OBJECT_NO_OFFSET(0x8DA1C0E, pos.x * 10, pos.y * 10, pos.z, TRUE, FALSE, FALSE);
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

                    ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, -1, -3.35, 3.5, 0, -11, 90, false, false, true, false, 0, true); //5
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                    spawnedOrange = OBJECT::CREATE_OBJECT_NO_OFFSET(0x8DA1C0E, pos.x * 10, pos.y * 10, pos.z, TRUE, FALSE, FALSE);
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

                    ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, -1.5, -3.35, 4.25, 43, -11, 90, false, false, true, false, 0, true); //6
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                    spawnedOrange = OBJECT::CREATE_OBJECT_NO_OFFSET(0x8DA1C0E, pos.x * 10, pos.y * 10, pos.z, TRUE, FALSE, FALSE);
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

                    ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, -2, -3.35, 5, 23.25, -11, 90, false, false, true, false, 0, true); //7
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                    spawnedOrange = OBJECT::CREATE_OBJECT_NO_OFFSET(0x8DA1C0E, pos.x * 10, pos.y * 10, pos.z, TRUE, FALSE, FALSE);
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

                    ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, -2.5, -3.35, 5.75, 31.25, -11, 90, false, false, true, false, 0, true); //8
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                    spawnedOrange = OBJECT::CREATE_OBJECT_NO_OFFSET(0x8DA1C0E, pos.x * 10, pos.y * 10, pos.z, TRUE, FALSE, FALSE);
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

                    ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, -3, -3.35, 6.25, 18.5, -11, 90, false, false, true, false, 0, true); //9
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                    spawnedOrange = OBJECT::CREATE_OBJECT_NO_OFFSET(0x8DA1C0E, pos.x * 10, pos.y * 10, pos.z, TRUE, FALSE, FALSE);
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

                    ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, -3.5, -3.35, 6.5, 18.5, -11, 90, false, false, true, false, 0, true); //11
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                    spawnedOrange = OBJECT::CREATE_OBJECT_NO_OFFSET(0x8DA1C0E, pos.x * 10, pos.y * 10, pos.z, TRUE, FALSE, FALSE);
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

                    ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, -4.5, -3.35, 7, 18.5, -11, 90, false, false, true, false, 0, true); //12
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                    spawnedOrange = OBJECT::CREATE_OBJECT_NO_OFFSET(0x8DA1C0E, pos.x * 10, pos.y * 10, pos.z, TRUE, FALSE, FALSE);
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

                    ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnedOrange, playerVeh, 0, -6.25, -3.35, 7.5, 9.25, -11, 90, false, false, true, false, 0, true); //13
                } QUEUE_JOB_END_CLAUSE
            }

            if (ImGui::CollapsingHeader(xorstr("Vehicle Handling")))
            {
                const float top_min = -1.0f, top_max = 10.0f;
                const float min = 1.0f, max = 10.0f;
                g_handling.acceleration = rage_helper::get_local_vehicle()->m_handling->m_acceleration;
                ImGui::Text(xorstr("Vehicle Handling"));
                if (ImGui::SliderScalar(xorstr("Acceleration"), ImGuiDataType_Float, &g_handling.acceleration, &min, &max))
                {
                    if (rage_helper::get_local_ped()->m_is_in_vehicle)
                        rage_helper::get_local_vehicle()->m_handling->m_acceleration = g_handling.acceleration;
                }

                if (ImGui::SliderScalar(xorstr("Top Speed"), ImGuiDataType_Float, &g_handling.top_speed, &top_min, &top_max))
                {
                    g_fiber_pool->queue_job([] {
                        if (rage_helper::get_local_ped()->m_is_in_vehicle)
                            VEHICLE::MODIFY_VEHICLE_TOP_SPEED(g_local.PlayerVehicle, g_handling.top_speed);
                    });
                }
                g_handling.traction_curve_min = rage_helper::get_local_vehicle()->m_handling->m_traction_curve_min;
                if (ImGui::SliderScalar(xorstr("Traction Curve Min"), ImGuiDataType_Float, &g_handling.traction_curve_min, &min, &max))
                {
                    if (rage_helper::get_local_ped()->m_is_in_vehicle)
                        rage_helper::get_local_vehicle()->m_handling->m_traction_curve_min = g_handling.traction_curve_min;
                }
                g_handling.traction_curve_max = rage_helper::get_local_vehicle()->m_handling->m_traction_curve_max;
                if (ImGui::SliderScalar(xorstr("Traction Curve Max"), ImGuiDataType_Float, &g_handling.traction_curve_max, &min, &max))
                {
                    if (rage_helper::get_local_ped()->m_is_in_vehicle)
                        rage_helper::get_local_vehicle()->m_handling->m_traction_curve_max = g_handling.traction_curve_max;
                }

                ImGui::Text(xorstr("Flying Handling"));
                g_handling.f_acceleration = rage_helper::get_local_vehicle()->m_handling->m_flying_acceleration;
                if (ImGui::SliderScalar(xorstr("Flying Acceleration"), ImGuiDataType_S32, &g_handling.f_acceleration, &min, &max))
                {
                    if (rage_helper::get_local_ped()->m_is_in_vehicle)
                        rage_helper::get_local_vehicle()->m_handling->m_flying_acceleration = g_handling.f_acceleration;
                }
            }
            if (ImGui::CollapsingHeader(xorstr("Vehicle Flag")))
            {
                static int selected_flag = 0;
                ImGui::Text(xorstr("Vehicle Flag Type"));
                if (ImGui::BeginCombo(xorstr("##FlagList"), game_variable::ListFlag[selected_flag]))
                {
                    for (int i = 0; i <= IM_ARRAYSIZE(game_variable::ListFlag); i++)
                    {
                        if (ImGui::Selectable(game_variable::ListFlag[i], i == g_handling.selected_flag))
                        {
                            selected_flag = i;
                            g_handling.selected_flag = i;
                        }
                    }
                    ImGui::EndCombo();
                }
                switch (rage_helper::get_local_ped()->m_is_in_vehicle ? selected_flag : 0)
                {
                    case 1:
                        //std::map<int, std::string>::iterator it = game_variable::List_Vehicle_Flags_1.begin();
                        for (auto it : game_variable::List_Vehicle_Flags_1)
                        {
                            if (ImGui::Checkbox(it.second.c_str(), &g_handling.Flag_1[it.first]))
                            {
                                if (g_handling.Flag_1[it.first])
                                {
                                    vehicle_helper::set_vehicle_flag(1, it.first);
                                }
                                else if (!g_handling.Flag_1[it.first])
                                {
                                    vehicle_helper::clear_vehicle_flag(1, it.first);
                                }
                            }
                        }
                        break;
                    case 2:
                        for (auto it : game_variable::List_Vehicle_Flags_2)
                        {
                            if (ImGui::Checkbox(it.second.c_str(), &g_handling.Flag_2[it.first]))
                            {
                                if (g_handling.Flag_2[it.first])
                                {
                                    vehicle_helper::set_vehicle_flag(2, it.first);
                                }
                                else if (!g_handling.Flag_2[it.first])
                                {
                                    vehicle_helper::clear_vehicle_flag(2, it.first);
                                }
                            }
                        }
                        break;
                    case 3:
                        for (auto it : game_variable::List_Vehicle_Flags_3)
                        {
                            if (ImGui::Checkbox(it.second.c_str(), &g_handling.Flag_3[it.first]))
                            {
                                if (g_handling.Flag_3[it.first])
                                {
                                    vehicle_helper::set_vehicle_flag(3, it.first);
                                }
                                else if (!g_handling.Flag_3[it.first])
                                {
                                    vehicle_helper::clear_vehicle_flag(3, it.first);
                                }
                            }
                        }
                        break;
                    case 4:
                        for (auto it : game_variable::List_Vehicle_Flags_4)
                        {
                            if (ImGui::Checkbox(it.second.c_str(), &g_handling.Flag_4[it.first]))
                            {
                                if (g_handling.Flag_4[it.first])
                                {
                                    vehicle_helper::set_vehicle_flag(4, it.first);
                                }
                                else if (!g_handling.Flag_4[it.first])
                                {
                                    vehicle_helper::clear_vehicle_flag(4, it.first);
                                }
                            }
                        }
                        break;
                    case 5:
                        for (auto it : game_variable::List_Vehicle_Flags_5)
                        {
                            if (ImGui::Checkbox(it.second.c_str(), &g_handling.Flag_5[it.first]))
                            {
                                if (g_handling.Flag_5[it.first])
                                {
                                    vehicle_helper::set_vehicle_flag(5, it.first);
                                }
                                else if (!g_handling.Flag_5[it.first])
                                {
                                    vehicle_helper::clear_vehicle_flag(5, it.first);
                                }
                            }
                        }
                        break;
                    case 6:
                        for (auto it : game_variable::List_Vehicle_Flags_6)
                        {
                            if (ImGui::Checkbox(it.second.c_str(), &g_handling.Flag_6[it.first]))
                            {
                                if (g_handling.Flag_6[it.first])
                                {
                                    vehicle_helper::set_vehicle_flag(6, it.first);
                                }
                                else if (!g_handling.Flag_6[it.first])
                                {
                                    vehicle_helper::clear_vehicle_flag(6, it.first);
                                }
                            }
                        }
                        break;
                    case 7:
                        for (auto it : game_variable::List_Vehicle_Flags_7)
                        {
                            if (ImGui::Checkbox(it.second.c_str(), &g_handling.Flag_7[it.first]))
                            {
                                if (g_handling.Flag_7[it.first])
                                {
                                    vehicle_helper::set_vehicle_flag(7, it.first);
                                }
                                else if (!g_handling.Flag_7[it.first])
                                {
                                    vehicle_helper::clear_vehicle_flag(7, it.first);
                                }
                            }
                        }
                        break;
                }
            }
            
            if (ImGui::CollapsingHeader(xorstr("Object Spawner")))
            {
                static char NamaObjek[255] = "";
                ImGui::InputText(xorstr("##NamaObject"), NamaObjek, IM_ARRAYSIZE(NamaObjek), ImGuiInputTextFlags_CharsUppercase);
                if (ImGui::Button(xorstr("Spawn Object##InputVersion")))
                {
                    object::spawn_object(NamaObjek, g_local.ped);
                }
                static int SelectedObject = 0;
                ImGui::Combo(xorstr("##Object List"), &SelectedObject, game_variable::object_hash_list, IM_ARRAYSIZE(game_variable::object_hash_list));
                if (ImGui::Button(xorstr("Spawn Object")))
                {
                    object::spawn_object(game_variable::object_hash_list[SelectedObject], g_local.ped);
                }
                if (ImGui::Button(xorstr("Remove Object Around Player")))
                {
                    g_fiber_pool->queue_job([]
                    {
                        Ped player_ped = PLAYER::PLAYER_PED_ID();
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

                            if (weapon == object)
                                continue;

                            network::request_control(object);
                            ENTITY::SET_ENTITY_COORDS(object, 0, 0, -100, 0, 0, 0, 0);
                            NETWORK::NETWORK_FADE_OUT_ENTITY(object, 0, 0);
                            ENTITY::SET_ENTITY_AS_MISSION_ENTITY(object, 0, 0);
                            ENTITY::DELETE_ENTITY(&object);
                        };
                    });
                }
            }
            if (ImGui::CollapsingHeader(xorstr("Ped Spawner")))
            {
                static char NamaPed[255];
                ImGui::Text("Spawn Ped Manually");
                ImGui::InputText("##PedHash", NamaPed, IM_ARRAYSIZE(NamaPed), ImGuiInputTextFlags_CharsUppercase);
                if (ImGui::Button("Spawn Ped ##SpawnManual"))
                {
                    QUEUE_JOB_BEGIN_CLAUSE()
                    {
                        auto coords = ENTITY::GET_ENTITY_COORDS(g_local.ped, TRUE);
                        ped::create_ped(rage::joaat(NamaPed), coords, 1, TRUE);
                    } QUEUE_JOB_END_CLAUSE
                }
                static int SelectionPedSpawn = 0;
                ImGui::Text("Selection Ped Spawner");
                ImGui::Combo("##PedSpawnSelection", &SelectionPedSpawn, game_variable::ped_hash_list, IM_ARRAYSIZE(game_variable::ped_hash_list));
                if (ImGui::Button("Spawn Ped##SelectedPed"))
                {
                    QUEUE_JOB_BEGIN_CLAUSE()
                    {
                        auto coords = ENTITY::GET_ENTITY_COORDS(g_local.ped, TRUE);
                        ped::create_ped(rage::joaat(game_variable::ped_hash_list[SelectionPedSpawn]), coords, 1, TRUE);
                    } QUEUE_JOB_END_CLAUSE
                }
            }
            ImGui::EndTabItem();
        }
        else
        {
            memset(&g_vehicle_option->vehicle_tab_open, false, 1);
        }
    }
}