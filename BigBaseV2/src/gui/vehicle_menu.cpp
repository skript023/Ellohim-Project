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

namespace big
{
    void vehicle_tab::render_vehicle_tab(const char* tab_name)
    {
        if (ImGui::BeginTabItem(tab_name))
        {
            static char NamaMobil[255] = "";
            static int total_ped = 0;
            ImGui::InputText(xorstr("##Kosong"), NamaMobil, IM_ARRAYSIZE(NamaMobil), ImGuiInputTextFlags_CharsUppercase);
            ImGui::PushItemWidth(100.f);
            ImGui::InputScalar(xorstr("##Num"), ImGuiDataType_S32, &total_ped);
            ImGui::PopItemWidth();
            if (ImGui::Button(xorstr("Native")))
            {
                vehicle_helper::vehicle(NamaMobil, g_local.ped);
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr("External")))
            {
                vehicle_helper::SpawnVehicle(NamaMobil, FALSE, g_local.player);
            }
            ImGui::SameLine();
            if (ImGui::Button(xorstr("Convoy")))
            {
                ai::Convoy(NamaMobil, total_ped);
            }
            ImGui::Separator();
            static int vehicle_menu = 0;
            static int selected_hash = 0;

            ImGui::RadioButton(xorstr("Vehicle"), &vehicle_menu, 0);
            ImGui::SameLine();
            ImGui::RadioButton(xorstr("Personal Vehicle"), &vehicle_menu, 1);
            ImGui::SameLine();
            ImGui::RadioButton(xorstr("Saved Vehicle"), &vehicle_menu, 2);

            switch (vehicle_menu)
            {
                case 0:
                    ImGui::Combo(xorstr("##VehicleCategory"), &selected_category, var::VehicleCategory, IM_ARRAYSIZE(var::VehicleCategory));
                    switch (selected_category)
                    {
                    case 0:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Super, IM_ARRAYSIZE(var::Super));
                        break;
                    case 1:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Sport, IM_ARRAYSIZE(var::Sport));
                        break;
                    case 2:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::SportClassic, IM_ARRAYSIZE(var::SportClassic));
                        break;
                    case 3:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::SummerUpdate, IM_ARRAYSIZE(var::SummerUpdate));
                        break;
                    case 4:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Sedan, IM_ARRAYSIZE(var::Sedan));
                        break;
                    case 5:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Service, IM_ARRAYSIZE(var::Service));
                        break;
                    case 6:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::SUV, IM_ARRAYSIZE(var::SUV));
                        break;
                    case 7:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Plane, IM_ARRAYSIZE(var::Plane));
                        break;
                    case 8:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Helicopter, IM_ARRAYSIZE(var::Helicopter));
                        break;
                    case 9:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::OffRoad, IM_ARRAYSIZE(var::OffRoad));
                        break;
                    case 10:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Muscle, IM_ARRAYSIZE(var::Muscle));
                        break;
                    case 11:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Motorcycle, IM_ARRAYSIZE(var::Motorcycle));
                        break;
                    case 12:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Military, IM_ARRAYSIZE(var::Military));
                        break;
                    case 13:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Trailer, IM_ARRAYSIZE(var::Trailer));
                        break;
                    case 14:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Train, IM_ARRAYSIZE(var::Train));
                        break;
                    case 15:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Utility, IM_ARRAYSIZE(var::Utility));
                        break;
                    case 16:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Van, IM_ARRAYSIZE(var::Van));
                        break;
                    case 17:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::ArenaWar, IM_ARRAYSIZE(var::ArenaWar));
                        break;
                    case 18:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Casino1, IM_ARRAYSIZE(var::Casino1));
                        break;
                    case 19:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Casino2, IM_ARRAYSIZE(var::Casino2));
                        break;
                    case 20:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Emergency, IM_ARRAYSIZE(var::Emergency));
                        break;
                    case 21:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Industrial, IM_ARRAYSIZE(var::Industrial));
                        break;
                    case 22:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Coupes, IM_ARRAYSIZE(var::Coupes));
                        break;
                    case 23:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Compact, IM_ARRAYSIZE(var::Compact));
                        break;
                    case 24:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Boat, IM_ARRAYSIZE(var::Boat));
                        break;
                    case 25:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Bikes, IM_ARRAYSIZE(var::Bikes));
                        break;
                    case 26:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::Commericals, IM_ARRAYSIZE(var::Commericals));
                        break;
                    case 27:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::CayoPerico, IM_ARRAYSIZE(var::CayoPerico));
                        break;
                    case 28:
                        ImGui::ListBox("##Vehicle List", &SelectedVehicle, var::tuner_update, IM_ARRAYSIZE(var::tuner_update));
                        break;
                    }
                    if (ImGui::Button(xorstr("Spawn Native")))
                    {
                        switch (selected_category)
                        {
                        case 0:
                            vehicle_helper::vehicle(var::Super[SelectedVehicle], g_local.ped);
                            break;
                        case 1:
                            vehicle_helper::vehicle(var::Sport[SelectedVehicle], g_local.ped);;
                            break;
                        case 2:
                            vehicle_helper::vehicle(var::SportClassic[SelectedVehicle], g_local.ped);
                            break;
                        case 3:
                            vehicle_helper::vehicle(var::SummerUpdate[SelectedVehicle], g_local.ped);
                            break;
                        case 4:
                            vehicle_helper::vehicle(var::Sedan[SelectedVehicle], g_local.ped);
                            break;
                        case 5:
                            vehicle_helper::vehicle(var::Service[SelectedVehicle], g_local.ped);
                            break;
                        case 6:
                            vehicle_helper::vehicle(var::SUV[SelectedVehicle], g_local.ped);
                            break;
                        case 7:
                            vehicle_helper::vehicle(var::Plane[SelectedVehicle], g_local.ped);
                            break;
                        case 8:
                            vehicle_helper::vehicle(var::Helicopter[SelectedVehicle], g_local.ped);
                            break;
                        case 9:
                            vehicle_helper::vehicle(var::OffRoad[SelectedVehicle], g_local.ped);
                            break;
                        case 10:
                            vehicle_helper::vehicle(var::Muscle[SelectedVehicle], g_local.ped);
                            break;
                        case 11:
                            vehicle_helper::vehicle(var::Motorcycle[SelectedVehicle], g_local.ped);
                            break;
                        case 12:
                            vehicle_helper::vehicle(var::Military[SelectedVehicle], g_local.ped);
                            break;
                        case 13:
                            vehicle_helper::vehicle(var::Trailer[SelectedVehicle], g_local.ped);
                            break;
                        case 14:
                            vehicle_helper::vehicle(var::Train[SelectedVehicle], g_local.ped);
                            break;
                        case 15:
                            vehicle_helper::vehicle(var::Utility[SelectedVehicle], g_local.ped);
                            break;
                        case 16:
                            vehicle_helper::vehicle(var::Van[SelectedVehicle], g_local.ped);
                            break;
                        case 17:
                            vehicle_helper::vehicle(var::ArenaWar[SelectedVehicle], g_local.ped);
                            break;
                        case 18:
                            vehicle_helper::vehicle(var::Casino1[SelectedVehicle], g_local.ped);
                            break;
                        case 19:
                            vehicle_helper::vehicle(var::Casino2[SelectedVehicle], g_local.ped);
                            break;
                        case 20:
                            vehicle_helper::vehicle(var::Emergency[SelectedVehicle], g_local.ped);
                            break;
                        case 21:
                            vehicle_helper::vehicle(var::Industrial[SelectedVehicle], g_local.ped);
                            break;
                        case 22:
                            vehicle_helper::vehicle(var::Coupes[SelectedVehicle], g_local.ped);
                            break;
                        case 23:
                            vehicle_helper::vehicle(var::Compact[SelectedVehicle], g_local.ped);
                            break;
                        case 24:
                            vehicle_helper::vehicle(var::Boat[SelectedVehicle], g_local.ped);
                            break;
                        case 25:
                            vehicle_helper::vehicle(var::Bikes[SelectedVehicle], g_local.ped);
                            break;
                        case 26:
                            vehicle_helper::vehicle(var::Commericals[SelectedVehicle], g_local.ped);
                            break;
                        case 27:
                            vehicle_helper::vehicle(var::CayoPerico[SelectedVehicle], g_local.ped);
                            break;
                        case 28:
                            vehicle_helper::vehicle(var::tuner_update[SelectedVehicle], g_local.ped);
                            break;
                        }
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(xorstr("Spawn External")))
                    {
                        switch (selected_category)
                        {
                        case 0:
                            vehicle_helper::SpawnVehicle(var::Super[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 1:
                            vehicle_helper::SpawnVehicle(var::Sport[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 2:
                            vehicle_helper::SpawnVehicle(var::SportClassic[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 3:
                            vehicle_helper::SpawnVehicle(var::SummerUpdate[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 4:
                            vehicle_helper::SpawnVehicle(var::Sedan[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 5:
                            vehicle_helper::SpawnVehicle(var::Service[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 6:
                            vehicle_helper::SpawnVehicle(var::SUV[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 7:
                            vehicle_helper::SpawnVehicle(var::Plane[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 8:
                            vehicle_helper::SpawnVehicle(var::Helicopter[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 9:
                            vehicle_helper::SpawnVehicle(var::OffRoad[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 10:
                            vehicle_helper::SpawnVehicle(var::Muscle[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 11:
                            vehicle_helper::SpawnVehicle(var::Motorcycle[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 12:
                            vehicle_helper::SpawnVehicle(var::Military[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 13:
                            vehicle_helper::SpawnVehicle(var::Trailer[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 14:
                            vehicle_helper::SpawnVehicle(var::Train[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 15:
                            vehicle_helper::SpawnVehicle(var::Utility[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 16:
                            vehicle_helper::SpawnVehicle(var::Van[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 17:
                            vehicle_helper::SpawnVehicle(var::ArenaWar[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 18:
                            vehicle_helper::SpawnVehicle(var::Casino1[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 19:
                            vehicle_helper::SpawnVehicle(var::Casino2[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 20:
                            vehicle_helper::SpawnVehicle(var::Emergency[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 21:
                            vehicle_helper::SpawnVehicle(var::Industrial[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 22:
                            vehicle_helper::SpawnVehicle(var::Coupes[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 23:
                            vehicle_helper::SpawnVehicle(var::Compact[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 24:
                            vehicle_helper::SpawnVehicle(var::Boat[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 25:
                            vehicle_helper::SpawnVehicle(var::Bikes[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 26:
                            vehicle_helper::SpawnVehicle(var::Commericals[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 27:
                            vehicle_helper::SpawnVehicle(var::CayoPerico[SelectedVehicle], FALSE, g_local.player);
                            break;
                        case 28:
                            vehicle_helper::SpawnVehicle(var::tuner_update[SelectedVehicle], FALSE, g_local.player);
                            break;
                        }
                    }
                break;
                case 1:
                    if (ImGui::ListBoxHeader(xorstr("##Personal Vehicle List")))
                    {
                        if (*g_pointers->m_is_session_started)
                        {
                            static int max_slots = *script_global(1323703).as<int*>();
                            for (int x = 0; x <= max_slots; ++x)
                            {
                                Hash hash = *script_global(1323703).at(x, 142).at(66).as<uint32_t*>();
                                auto names = FindVehicleName(hash);
                                static const char* local_name;

                                if (!controller::cstrcmp(names, "none"))
                                {
                                    if (ImGui::Selectable((names), x == SelectedPersonal))
                                    {
                                        SelectedPersonal = x;
                                    }
                                }
                            }
                        }
                        ImGui::ListBoxFooter();
                    }
                    if (ImGui::Button(xorstr("Call Personal")))
                    {
                        g_fiber_pool->queue_job([]
                        {
                            *script_global(2544210).at(965).as<int*>() = SelectedPersonal;
                            *script_global(2544210).at(962).as<bool*>() = true;
                            script::get_current()->yield(1500ms);
                            if (g_settings.options["Auto Get-in"])
                            {
                                if (rage::joaat(SCRIPT::GET_THIS_SCRIPT_NAME()) == RAGE_JOAAT("freemode"))
                                {
                                    if (NETWORK::NETWORK_DOES_NETWORK_ID_EXIST(*script_global(2426865).at(g_local.player, 449).at(38).as<int*>()) && NETWORK::NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID(*script_global(2426865).at(g_local.player, 449).at(38).as<int*>()))
                                    {
                                        Vehicle vehicle = NETWORK::NET_TO_VEH(*script_global(2426865).at(g_local.player, 449).at(38).as<int*>());
                                        PED::SET_PED_INTO_VEHICLE(g_local.ped, vehicle, -1);
                                    }
                                }
                                PED::SET_PED_INTO_VEHICLE(g_local.ped, *script_global(2544210).at(298).as<int*>(), -1);
                            }
                        });
                    }
                    ImGui::Combo(xorstr("##Change"), &selected_hash, var::VechicleList, IM_ARRAYSIZE(var::VechicleList));
                    if (ImGui::Button(xorstr("Change")))
                    {
                        *script_global(1323703).at(SelectedPersonal, 142).at(66).as<uint32_t*>() = rage::get_hash_key<uint32_t>(var::VechicleList[selected_hash]);
                    }
                break;
                case 2:
                    static char vehicle_file_name_input[50]{};
                    ImGui::InputText(xorstr("Vehicle File Name"), vehicle_file_name_input, IM_ARRAYSIZE(vehicle_file_name_input));
                    if (ImGui::Button(xorstr("Save Vehicle ##SaveVeh")))
                    {
                        QUEUE_JOB_BEGIN_CLAUSE()
                        {
                            big::persist_car::do_save_vehicle(vehicle_file_name_input);
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
            ImGui::Checkbox(xorstr("Infinite Vehicle Ammo"), &g_vehicle_option->infinite_ammo);
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
                g_handling.acceleration = Memory::get_value<float>((uintptr_t)g_pointers->m_ped_factory, { 0x8, 0xD30, 0x938, 0x4C });
                ImGui::Text(xorstr("Vehicle Handling"));
                if (ImGui::SliderScalar(xorstr("Acceleration"), ImGuiDataType_Float, &g_handling.acceleration, &min, &max))
                {
                    if (g_local.InVehicle)
                        Memory::set_value((uintptr_t)g_pointers->m_ped_factory, { 0x8, 0xD30, 0x938, 0x4C }, g_handling.acceleration);
                }

                if (ImGui::SliderScalar(xorstr("Top Speed"), ImGuiDataType_Float, &g_handling.top_speed, &top_min, &top_max))
                {
                    g_fiber_pool->queue_job([] {
                        if (g_local.InVehicle)
                            VEHICLE::MODIFY_VEHICLE_TOP_SPEED(g_local.PlayerVehicle, g_handling.top_speed);
                    });
                }
                g_handling.traction_curve_min = Memory::get_value<float>((uintptr_t)g_pointers->m_ped_factory, { 0x8, 0xD30, 0x938, 0x90 });
                if (ImGui::SliderScalar(xorstr("Traction Curve Min"), ImGuiDataType_Float, &g_handling.traction_curve_min, &min, &max))
                {
                    if (g_local.InVehicle)
                        Memory::set_value((uintptr_t)g_pointers->m_ped_factory, { 0x8, 0xD30, 0x938, 0x90 }, g_handling.traction_curve_min);
                }
                g_handling.traction_curve_max = Memory::get_value<float>((uintptr_t)g_pointers->m_ped_factory, { 0x8, 0xD30, 0x938, 0x88 });
                if (ImGui::SliderScalar(xorstr("Traction Curve Max"), ImGuiDataType_Float, &g_handling.traction_curve_max, &min, &max))
                {
                    if (g_local.InVehicle)
                        Memory::set_value((uintptr_t)g_pointers->m_ped_factory, { 0x8, 0xD30, 0x938, 0x88 }, g_handling.traction_curve_max);
                }

                ImGui::Text(xorstr("Flying Handling"));
                g_handling.f_acceleration = Memory::get_value<float>((uintptr_t)g_pointers->m_ped_factory, { 0x8, 0xD30, 0x938, 0x338 });
                if (ImGui::SliderScalar(xorstr("Flying Acceleration"), ImGuiDataType_S32, &g_handling.f_acceleration, &min, &max))
                {
                    if (g_local.InVehicle)
                        Memory::set_value((uintptr_t)g_pointers->m_ped_factory, { 0x8, 0xD30, 0x938, 0x338 }, g_handling.f_acceleration);
                }
            }
            if (ImGui::CollapsingHeader(xorstr("Vehicle Flag")))
            {
                static int selected_flag = 0;
                ImGui::Text(xorstr("Vehicle Flag Type"));
                if (ImGui::BeginCombo(xorstr("##FlagList"), var::ListFlag[selected_flag]))
                {
                    for (int i = 0; i <= IM_ARRAYSIZE(var::ListFlag); i++)
                    {
                        if (ImGui::Selectable(var::ListFlag[i], i == g_handling.selected_flag))
                        {
                            selected_flag = i;
                            g_handling.selected_flag = i;
                        }
                    }
                    ImGui::EndCombo();
                }
                switch (g_local.InVehicle ? selected_flag : 0)
                {
                    case 1:
                        //std::map<int, std::string>::iterator it = var::List_Vehicle_Flags_1.begin();
                        for (auto it : var::List_Vehicle_Flags_1)
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
                        for (auto it : var::List_Vehicle_Flags_2)
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
                        for (auto it : var::List_Vehicle_Flags_3)
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
                        for (auto it : var::List_Vehicle_Flags_4)
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
                        for (auto it : var::List_Vehicle_Flags_5)
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
                        for (auto it : var::List_Vehicle_Flags_6)
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
                        for (auto it : var::List_Vehicle_Flags_7)
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
                ImGui::Combo(xorstr("##Object List"), &SelectedObject, var::ObjectList, IM_ARRAYSIZE(var::ObjectList));
                if (ImGui::Button(xorstr("Spawn Object")))
                {
                    object::spawn_object(var::ObjectList[SelectedObject], g_local.ped);
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
                ImGui::Combo("##PedSpawnSelection", &SelectionPedSpawn, var::PedList, IM_ARRAYSIZE(var::PedList));
                if (ImGui::Button("Spawn Ped##SelectedPed"))
                {
                    QUEUE_JOB_BEGIN_CLAUSE()
                    {
                        auto coords = ENTITY::GET_ENTITY_COORDS(g_local.ped, TRUE);
                        ped::create_ped(rage::joaat(var::PedList[SelectionPedSpawn]), coords, 1, TRUE);
                    } QUEUE_JOB_END_CLAUSE
                }
            }
            ImGui::EndTabItem();
        }
    }
}