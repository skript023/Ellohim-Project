#include "common.hpp"
#include "imgui.h"
#include "script.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "gta_util.hpp"
#include "ImGuiBitfield.h"
#include "script_global.hpp"
#include "features.hpp"
#include "gta/VehicleValues.h"
#include "gui.hpp"
#include "gta/Weapons.h"
#include "script_local.hpp"
#include "misc/cpp/imgui_stdlib.h"
#include "gui/helper_function.hpp"
#include "player_information.h"
#include "gui/game_tabbar/player_list.h"

namespace big
{
    void player_information::render_player_info(const char* tab_name)
    {
        if (ImGui::BeginTabItem(tab_name))
        {
            controller::get_player_info_from_ip(g_selected.player);
            ImGui::Text("Ped ID : %d", g_selected.ped);
            ImGui::SameLine(200);
            ImGui::Text("Script Host : %s", g_local.ScriptHost == g_selected.player ? "True" : "False");
            ImGui::SameLine(400);
            ImGui::Text("Waterproof : %s", player::get_player_waterproof(g_selected.player) ? "True" : "False");
            ImGui::Text("RID : %d", player::get_player_scid(g_selected.player));
            ImGui::SameLine(200);
            ImGui::Text("Host : %s", network::network_is_host(g_selected.player) ? "True" : "False");
            ImGui::SameLine(400);
            ImGui::Text("Godmode : %s", player::get_player_invincible(g_selected.player) ? "True" : "False");

            ImGui::Text("ISP : %s", g_misc_option->provider.c_str());
            ImGui::Text("Country : %s", g_misc_option->country.c_str());
            ImGui::Text("City/Region : %s/%s", g_misc_option->city.c_str(), g_misc_option->region.c_str());
            ImGui::Text("ZIP Code : %s", g_misc_option->zip.c_str());
            ImGui::Text("Proxy/VPN : %s", g_misc_option->proxy ? "True" : "False");

            ImGui::Text("Local IP : %s", player::get_player_local_ip(g_selected.player));
            ImGui::Text("IP : %s", player::get_player_ip(g_selected.player));
            ImGui::SameLine(200);
            ImGui::Text("Wanted Level : %d", player::get_player_wanted_level(g_selected.player));

            ImGui::Text("Cash : $%d", player::get_player_cash(g_selected.player));
            ImGui::SameLine(200);
            ImGui::Text("Bank : $%d", player::get_player_banked_money(g_selected.player));
            ImGui::Text("Level : %d", player::get_player_level(g_selected.player));
            ImGui::SameLine(200);
            ImGui::Text("Off Radar : %s", player::is_player_out_of_radar(g_selected.player) ? "True" : "False");
            ImGui::Text("Modded Account : %s", player::is_modded_account(g_selected.player));
            
            ImGui::Text("Current EXP : %d/%d", player::get_player_exp(g_selected.player), player::get_player_global_exp(g_selected.player));
            ImGui::Text("Location : %s", g_info.PlayerZone);
            ImGui::Text("Zone : %s", g_info.PlayerStreet);

            ImGui::Text("Player HP : %d/%d", g_info.player_health, g_info.player_max_health);
            ImGui::Text("Player Armour : %d/%d", g_info.player_armour, g_info.player_max_armour);
            ImGui::Separator();
            ImGui::Text(fmt::format("Current Vehicle : {}", player::get_player_vehicle_name(g_selected.player)).c_str());
            ImGui::SameLine(350);
            ImGui::Text(fmt::format("Driver : {}", player::is_player_driver(g_selected.ped) ? "true" : "false").c_str());

            ImGui::Text(fmt::format("Current Weapon : {}", player::get_player_weapon(g_selected.player)).c_str());
            ImGui::Text(fmt::format("Infinite Ammo : {} / Infinite Clip : {}", player::get_player_infinite_ammo(g_selected.player), player::get_player_infinite_clip(g_selected.player)).c_str());
            ImGui::Separator();
            ImGui::Text("Main Mission : %s", player::get_player_heist_primary_status(g_selected.player));
            ImGui::Text("Optional Mission : %s", player::get_player_heist_secondary_status(g_selected.player));
            ImGui::Text("Target : %s", player::get_player_heist_target(g_selected.player));
            ImGui::Text("Approach : %s", player::get_player_heist_approach(g_selected.player));
            ImGui::Text("Last Approach : %s", player::get_player_heist_last_approach(g_selected.player));
            ImGui::Text("Hard Approach : %s", player::get_player_heist_hard_approach(g_selected.player));
            ImGui::Text("Driver : %s", player::get_player_heist_driver(g_selected.player));
            ImGui::Text("Gunman : %s", player::get_player_heist_gunman(g_selected.player));
            ImGui::Text("Hacker : %s", player::get_player_heist_hacker(g_selected.player));
            ImGui::Text("Security Pass : Level %d", *script_global(g_global.casino_stat).at(g_selected.player, 68).at(18).at(15).as<int*>());
            ImGui::Text("Disrupted Level : %d", *script_global(g_global.casino_stat).at(g_selected.player, 68).at(18).at(8).as<int*>());

            ImGui::Separator();
            ImGui::Text("X : %f        Y : %f        Z : %f", g_info.PlayerPosition.x, g_info.PlayerPosition.y, g_info.PlayerPosition.z);
            
            ImGui::EndTabItem();
        }

    }

    void player_information::render_player_business_info(const char* tab_name)
    {
        if (ImGui::BeginTabItem(tab_name))
        {
            if (ImGui::CollapsingHeader(xorstr(ICON_FA_MAP_MARKED" Business Location")))
            {
                ImGui::Text(fmt::format("Meth Location : {}", network::get_meth_location(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Weed Location : {}", network::get_weed_location(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Coke Location :{}", network::get_cocain_location(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Cash Location : {}", network::get_cash_location(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Document Location : {}", network::get_document_location(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Bunker Location : {}", network::get_bunker_location(g_selected.player)).c_str());
                ImGui::Separator();
            }
            if (ImGui::CollapsingHeader(xorstr(ICON_FA_FORKLIFT" Total Stock of Product")))
            {
                ImGui::Text(fmt::format("Meth Product : {:.2f}%%", network::get_meth_stock(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Weed Product : {:.2f}%%", network::get_weed_stock(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Cocain Product : {:.2f}%%", network::get_cocain_stock(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Cash Product : {:.2f}%%", network::get_cash_stock(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Document Product : {:.2f}%%", network::get_document_stock(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Bunker Product : {:.2f}%%", network::get_bunker_stock(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Research Progress : {:.2f}%%", network::get_research_progress(g_selected.player)).c_str());
                ImGui::Separator();
            }
            if (ImGui::CollapsingHeader(xorstr(ICON_FA_FORKLIFT" Total Supply")))
            {
                ImGui::Text(fmt::format("Meth Supply : {:.2f}%%", network::get_meth_supply(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Weed Supply : {:.2f}%%", network::get_weed_supply(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Cocain Supply : {:.2f}%%", network::get_cocain_supply(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Cash Supply : {:.2f}%%", network::get_cash_supply(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Document Supply : {:.2f}%%", network::get_document_supply(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Bunker Supply : {:.2f}%%", network::get_bunker_supply(g_selected.player)).c_str());
            }
            ImGui::EndTabItem();
        }
    }

    void player_information::render_player_event(const char* tab_name)
    {
        if (ImGui::BeginTabItem(tab_name))
        {
            ImGui::RadioButton(xorstr("Script Event"), &event_type, 0);
            ImGui::SameLine();
            ImGui::RadioButton(xorstr("Network Event"), &event_type, 1);
            ImGui::SameLine();
            ImGui::RadioButton(xorstr("Other##Event"), &event_type, 2);

            switch (event_type)
            {
            case 0:
                ImGui::Text(xorstr("Script Event"));
                ImGui::PushItemWidth(250);
                ImGui::Combo(xorstr("##Script Event"), &SelectedScriptEvent, ScriptEvent, IM_ARRAYSIZE(ScriptEvent));
                ImGui::PopItemWidth();
                if (SelectedScriptEvent == 11)
                {
                    ImGui::PushItemWidth(250);
                    ImGui::InputScalar(xorstr("Money Value"), ImGuiDataType_S32, &MoneyValue);
                    ImGui::PopItemWidth();
                    ImGui::RadioButton(xorstr("Banked"), &type, 0);
                    ImGui::SameLine();
                    ImGui::RadioButton(xorstr("Remove"), &type, 1);
                    ImGui::SameLine();
                    ImGui::RadioButton(xorstr("Steal"), &type, 2);
                    ImGui::Separator();
                }
                if (SelectedScriptEvent == 0)
                {
                    ImGui::Checkbox("All Player?", &is_all_player);
                }
                if (SelectedScriptEvent == 1)
                {
                    ImGui::PushItemWidth(250.f);
                    ImGui::Text("Choose Apartment Location");
                    ImGui::Combo("##Apartment Location", &selected_apartment, game_variable::apartment_list, IM_ARRAYSIZE(game_variable::apartment_list));
                    ImGui::PopItemWidth();
                    ImGui::Checkbox("All Player?", &is_all_player);
                }

                if (ImGui::Button(xorstr("Send Event")))
                {
                    switch (SelectedScriptEvent)
                    {
                    case 0:
                        if (!is_all_player)
                        {
                            remote_event::teleport_player_to_cayo(g_selected.player);
                        }
                        else if (is_all_player)
                        {
                            for (int i = 0; i <= 32; i++)
                            {
                                if (i == g_local.player)
                                    continue;

                                if (i != g_local.player)
                                    remote_event::teleport_player_to_cayo(i);
                            }
                        }
                        break;
                    case 1:
                        if (!is_all_player)
                        {
                            remote_event::force_invite_apartment(g_selected.player, selected_apartment);
                        }
                        else if (is_all_player)
                        {
                            for (int i = 0; i <= 32; i++)
                            {
                                if (i == g_local.player) 
                                    continue;

                                if (i != g_local.player)
                                    remote_event::force_invite_apartment(i, selected_apartment);
                            }
                        }
                        break;
                    case 2:
                        remote_event::ceo_kick(g_selected.player);
                        break;
                    case 3:
                        remote_event::ceo_ban(g_selected.player);
                        break;
                    case 4:
                        remote_event::rotate_cam(g_selected.player);
                        break;
                    case 5:
                        remote_event::vehicle_kick(g_selected.player);
                        break;
                    case 6:
                        remote_event::clear_wanted(g_selected.player);
                        break;
                    case 7:
                        remote_event::kick_player(g_selected.player);
                        break;
                    case 8:
                        remote_event::transaction_fail(g_selected.player);
                        break;
                    case 9:
                        remote_event::send_to_mission(g_selected.player);
                        break;
                    case 10:
                        remote_event::give_wanted_level(g_selected.player);
                        break;
                    case 11:
                        switch (type)
                        {
                        case 0:
                            remote_event::give_fake_money(g_selected.player, MoneyValue);
                            break;
                        case 1:
                            remote_event::remove_fake_money(g_selected.player, MoneyValue);
                            break;
                        case 2:
                            remote_event::steal_fake_money(g_selected.player, MoneyValue);
                            break;
                        }
                        break;
                    case 12:
                        remote_event::set_bounty(g_selected.player);
                        break;
                    }
                }
                break;
            case 1:
                ImGui::Text(xorstr("Network Event"));
                ImGui::PushItemWidth(250);
                ImGui::Combo(xorstr("##Network Event"), &SelectedNetworkEvent, NetworkEvent, IM_ARRAYSIZE(NetworkEvent));
                ImGui::PopItemWidth();
                if (SelectedNetworkEvent == 0)
                {
                    ImGui::RadioButton(xorstr("Give Weapon"), &WeaponOption, 0);
                    ImGui::SameLine();
                    ImGui::RadioButton(xorstr("Add Ammo"), &WeaponOption, 1);
                    ImGui::SameLine();
                    ImGui::RadioButton(xorstr("Remove Weapon"), &WeaponOption, 2);
                    ImGui::Separator();
                }
                if (SelectedNetworkEvent == 4)
                {
                    ImGui::PushItemWidth(250);
                    if (!AirStrike)
                        ImGui::Combo(xorstr("Select Shoot Type"), &SelectedShoot, game_variable::shoot_troll_list, IM_ARRAYSIZE(game_variable::shoot_troll_list));
                    ImGui::Checkbox(xorstr("Air Strike"), &AirStrike);
                    ImGui::Separator();
                    ImGui::PopItemWidth();
                }
                if (SelectedNetworkEvent == 2)
                {
                    ImGui::PushItemWidth(250);
                    if (ExplosiveMode == 0)
                    {
                        ImGui::Combo(xorstr("Select Explosion Type"), &SelectedExplosion, game_variable::explosion_list, IM_ARRAYSIZE(game_variable::explosion_list));
                        if (ImGui::BeginCombo(xorstr("Blame Player"), player::get_player_name(SelectedBlame)))
                        {
                            for (auto player_list : g_misc_option->player_names)
                            {
                                if (!g_misc_option->player_names.empty())
                                {
                                    if (ImGui::Selectable(player_list.second.name, player_list.second.id == SelectedBlame))
                                    {
                                        if (SelectedBlame != player_list.second.id)
                                            SelectedBlame = player_list.second.id;
                                    }
                                }
                            }
                            ImGui::EndCombo();
                        }
                    }
                    ImGui::Checkbox(xorstr("Audio"), &isAudio);
                    ImGui::Checkbox(xorstr("Invisible"), &isInvinsible);
                    ImGui::RadioButton(xorstr("Explode Normal"), &ExplosiveMode, 0);
                    ImGui::SameLine();
                    ImGui::RadioButton(xorstr("Explode Lobby Blame"), &ExplosiveMode, 1);
                    ImGui::SameLine();
                    ImGui::RadioButton(xorstr("Explode Lobby"), &ExplosiveMode, 2);
                    ImGui::Text("Bypass 1 : 0x%X | Bypass 2 : 0x0%X", *(unsigned short*)g_pointers->m_add_owned_explosion_bypass_1, *(unsigned short*)g_pointers->m_add_owned_explosion_bypass_2);
                    ImGui::Separator();
                    ImGui::PopItemWidth();
                }
                if (SelectedNetworkEvent == 5)
                {
                    ImGui::Checkbox(xorstr("Bonus Full Upgrade"), &bonus_repair);
                }
                if (SelectedNetworkEvent == 6)
                {
                    ImGui::Text(xorstr("Player Must Inside Vehicle"));
                    ImGui::RadioButton("Launch", &control_type, 0);
                    ImGui::SameLine();
                    ImGui::RadioButton("Boost", &control_type, 1);
                    ImGui::SameLine();
                    ImGui::RadioButton("Front Flip", &control_type, 2);

                    ImGui::RadioButton("Back Flip", &control_type, 3);
                    ImGui::SameLine();
                    ImGui::RadioButton("Side Flip", &control_type, 4);
                    ImGui::SameLine();
                    ImGui::RadioButton("Kick Flip", &control_type, 5);

                    ImGui::RadioButton("Heel Flip", &control_type, 6);
                    ImGui::SameLine();
                    ImGui::RadioButton("Bunny Flip", &control_type, 7);
                    ImGui::SameLine();
                    ImGui::RadioButton("Launch  Flip", &control_type, 8);
                }

                if (ImGui::Button(xorstr("Send Event")))
                {
                    QUEUE_JOB_BEGIN()
                    {
                        switch (SelectedNetworkEvent)
                        {
                        case 0:
                            switch (WeaponOption)
                            {
                            case 0:
                                int MaxAmmo;
                                for (auto WeaponList : game_variable::weapon_hash_list)
                                {
                                    if (!WEAPON::HAS_PED_GOT_WEAPON(g_selected.ped, rage::joaat(WeaponList), FALSE))
                                    {
                                        script::get_current()->yield();
                                        for (auto ComponentHashes : game_variable::weapon_component_list)
                                        {
                                            WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(g_selected.ped, rage::joaat(WeaponList), rage::joaat(ComponentHashes));
                                        }
                                        WEAPON::GIVE_DELAYED_WEAPON_TO_PED(g_selected.ped, rage::joaat(WeaponList), (WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), rage::joaat(WeaponList), &MaxAmmo) == TRUE) ? MaxAmmo : 9999, FALSE);
                                    }
                                }
                                break;
                            case 1:
                                for (auto name : game_variable::weapon_hash_list)
                                {
                                    auto ent = g_selected.ped;
                                    if (ENTITY::DOES_ENTITY_EXIST(ent) && !ENTITY::IS_ENTITY_DEAD(ent, FALSE))
                                    {
                                        WEAPON::ADD_AMMO_TO_PED(ent, rage::joaat(name), 9999);
                                    }
                                    script::get_current()->yield();
                                }
                                break;
                            case 2:
                                for (auto name : game_variable::weapon_hash_list)
                                {
                                    auto ent = g_selected.ped;
                                    if (ENTITY::DOES_ENTITY_EXIST(ent) && !ENTITY::IS_ENTITY_DEAD(ent, FALSE))
                                    {
                                        WEAPON::REMOVE_WEAPON_FROM_PED(ent, rage::joaat(name));
                                    }
                                    script::get_current()->yield();
                                }
                                break;
                            }
                            break;
                        case 1:
                            TASK::CLEAR_PED_TASKS_IMMEDIATELY(g_selected.ped);
                            /*int bounty[21] = { -116602735, player, 1, 9999, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, *script_global(1652336).at(9).as<int*>(), *script_global(1652336).at(10).as<int*>() };
                            SCRIPT::TRIGGER_SCRIPT_EVENT(1, reinterpret_cast<uint64_t*>(bounty), 22, 1 << g_selected.player);*/
                            break;
                        case 2:
                            switch (ExplosiveMode)
                            {
                            case 0:
                            {
                                auto pos = ENTITY::GET_ENTITY_COORDS(g_selected.ped, TRUE);
                                auto BlameThisPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(SelectedBlame);
                                *(PWORD)g_pointers->m_add_owned_explosion_bypass_1 = 0xE990;
                                *(PWORD)g_pointers->m_add_owned_explosion_bypass_2 = 0x9090;
                                FIRE::ADD_OWNED_EXPLOSION(BlameThisPlayer, pos.x, pos.y, pos.z, SelectedExplosion, 1000.0f, isAudio, isInvinsible, 0.0f);
                                *(PWORD)g_pointers->m_add_owned_explosion_bypass_1 = 0x850F;
                                *(PWORD)g_pointers->m_add_owned_explosion_bypass_2 = 0x0E74;
                            }
                            break;
                            case 1:
                            {
                                for (int i = 0; i <= 32; i++)
                                {
                                    if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) == PLAYER::PLAYER_PED_ID()) continue;
                                    {
                                        Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
                                        *(PWORD)g_pointers->m_add_owned_explosion_bypass_1 = 0xE990;
                                        *(PWORD)g_pointers->m_add_owned_explosion_bypass_2 = 0x9090;
                                        FIRE::ADD_OWNED_EXPLOSION(g_selected.ped, coords.x, coords.y, coords.z, EXPLOSION_TRAIN, 1000.0f, isAudio, isInvinsible, 100.0f);
                                        *(PWORD)g_pointers->m_add_owned_explosion_bypass_1 = 0x850F;
                                        *(PWORD)g_pointers->m_add_owned_explosion_bypass_2 = 0x0E74;
                                    }
                                    script::get_current()->yield();
                                }
                            }
                            break;
                            case 2:
                            {
                                for (int i = 0; i <= 32; i++)
                                {
                                    if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) == PLAYER::PLAYER_PED_ID()) continue;
                                    {
                                        Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
                                        FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, EXPLOSION_TRAIN, 1000.f, isAudio, isInvinsible, 100.f, false);
                                    }
                                    script::get_current()->yield();
                                }
                            }
                            break;
                            }
                            break;
                        case 3:
                        {
                            NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, g_selected.ped);
                        }
                        break;
                        case 4:
                        {
                            if (!AirStrike)
                            {
                                Ped owner = rage::joaat(game_variable::shoot_troll_list[SelectedShoot]) == rage::joaat("WEAPON_STUNGUN") ? PLAYER::PLAYER_PED_ID() : 0;
                                int damage = rage::joaat(game_variable::shoot_troll_list[SelectedShoot]) == rage::joaat("WEAPON_STUNGUN") ? 0 : 250;
                                auto Coords = ENTITY::GET_ENTITY_COORDS(g_selected.ped, true);
                                Coords.y += 2;
                                Coords.x += 2;
                                MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x + 2, Coords.y + 2, Coords.z, Coords.x, Coords.y, Coords.z, damage, true, rage::joaat(game_variable::shoot_troll_list[SelectedShoot]), owner, true, true, 1000); //VEHICLE_WEAPON_SPACE_ROCKET
                                MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x + 2, Coords.y + 2, Coords.z, Coords.x, Coords.y, Coords.z, damage, false, rage::joaat(game_variable::shoot_troll_list[SelectedShoot]), owner, true, true, 1000);
                                MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x + 2, Coords.y + 2, Coords.z, Coords.x, Coords.y, Coords.z, damage, false, rage::joaat(game_variable::shoot_troll_list[SelectedShoot]), owner, true, true, 1000);
                            }
                            if (AirStrike)
                            {
                                int total = 10;
                                for (auto i = 0; i <= total; i++)
                                {
                                    auto Coords = ENTITY::GET_ENTITY_COORDS(g_selected.ped, true);
                                    Coords.z += 15;
                                    MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x, Coords.y, Coords.z + 35, Coords.x, Coords.y, Coords.z, 250, true, VEHICLE_WEAPON_SPACE_ROCKET, g_selected.ped, true, true, 500); //VEHICLE_WEAPON_SPACE_ROCKET
                                    MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x, Coords.y, Coords.z + 35, Coords.x, Coords.y, Coords.z, 250, false, VEHICLE_WEAPON_SPACE_ROCKET, 0, true, true, 500);
                                    MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x, Coords.y, Coords.z + 35, Coords.x, Coords.y, Coords.z, 250, false, VEHICLE_WEAPON_SPACE_ROCKET, g_selected.ped, true, true, 600);
                                    script::get_current()->yield(500ms);
                                }
                            }
                        }
                        break;
                        case 5:
                        {
                            int tick = 0;
                            Vehicle VehicleId = PED::GET_VEHICLE_PED_IS_IN(g_selected.ped, FALSE);


                            *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                            network::request_control(VehicleId);
                            *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;

                            script::get_current()->yield();

                            VEHICLE::SET_VEHICLE_FIXED(VehicleId);
                            VEHICLE::SET_VEHICLE_ENGINE_HEALTH(VehicleId, 1000.0f);
                            VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(VehicleId, 1000.0f);
                            VEHICLE::SET_VEHICLE_DIRT_LEVEL(VehicleId, 0.0f);
                            if (!VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(VehicleId))
                            {
                                VEHICLE::SET_VEHICLE_ENGINE_ON(VehicleId, TRUE, TRUE, FALSE);
                            }
                            if (bonus_repair)
                            {
                                VEHICLE::TOGGLE_VEHICLE_MOD(VehicleId, MOD_XENONHEADLIGHTS, TRUE);
                                VEHICLE::TOGGLE_VEHICLE_MOD(VehicleId, MOD_TURBO, TRUE);
                                VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehicleId, 0, TRUE);
                                VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehicleId, 1, TRUE);
                                VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehicleId, 2, TRUE);
                                VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehicleId, 3, TRUE);
                                VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehicleId, NEON_COLOR_RED);
                                VEHICLE::_SET_VEHICLE_XENON_LIGHTS_COLOR(VehicleId, 8);
                                VEHICLE::SET_VEHICLE_MOD_KIT(VehicleId, 0);

                                for (int i = 0; i < 50; i++)
                                {
                                    VEHICLE::SET_VEHICLE_MOD(VehicleId, i, VEHICLE::GET_NUM_VEHICLE_MODS(VehicleId, i) - 1, TRUE);
                                }
                                VEHICLE::SET_VEHICLE_WHEEL_TYPE(VehicleId, 9);
                                VEHICLE::SET_VEHICLE_MOD(VehicleId, MOD_FRONTWHEEL, 52, TRUE);
                            }
                        }
                        break;
                        case 6:
                            switch (control_type)
                            {
                            case 0:
                                if (PED::IS_PED_IN_ANY_VEHICLE(g_selected.ped, FALSE))
                                {
                                    Vehicle Veh = player::get_player_vehicle(g_selected.ped, false);

                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                                    network::request_control(Veh);
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;
                                    script::get_current()->yield();

                                    VEHICLE::SET_VEHICLE_FORWARD_SPEED(Veh, 1000.0f);
                                    ENTITY::APPLY_FORCE_TO_ENTITY(Veh, 1, 150.0f, 180.0f, 200.0f, 20.0f, 20.0f, 50.0f, 0, FALSE, TRUE, TRUE, FALSE, TRUE);
                                }
                                break;
                            case 1:
                                if (PED::IS_PED_IN_ANY_VEHICLE(g_selected.ped, FALSE))
                                {
                                    Vehicle Veh = player::get_player_vehicle(g_selected.ped, true);

                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                                    network::request_control(Veh);
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;
                                    script::get_current()->yield();

                                    VEHICLE::SET_VEHICLE_FORWARD_SPEED(Veh, 700.0f);
                                }
                                break;
                            case 2:
                                if (PED::IS_PED_IN_ANY_VEHICLE(g_selected.ped, FALSE))
                                {
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                                    network::request_control(player::get_player_vehicle(player::get_player_ped(g_selected.player), false));
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;
                                    script::get_current()->yield();
                                    ENTITY::APPLY_FORCE_TO_ENTITY(player::get_player_vehicle(player::get_player_ped(g_selected.player), false), true, 0, 0, 6.0f, 0, -2.0f, 0, true, true, true, true, false, true);
                                }
                                break;
                            case 3:
                                if (PED::IS_PED_IN_ANY_VEHICLE(g_selected.ped, FALSE))
                                {
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                                    network::request_control(player::get_player_vehicle(player::get_player_ped(g_selected.player), false));
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;
                                    script::get_current()->yield();
                                    ENTITY::APPLY_FORCE_TO_ENTITY(player::get_player_vehicle(player::get_player_ped(g_selected.player), false), true, 0, 0, 6.0f, 0, 2.0f, 0, true, true, true, true, false, true);
                                }
                                break;
                            case 4:
                                if (PED::IS_PED_IN_ANY_VEHICLE(g_selected.ped, FALSE))
                                {
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                                    network::request_control(player::get_player_vehicle(player::get_player_ped(g_selected.player), false));
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;
                                    script::get_current()->yield();
                                    ENTITY::APPLY_FORCE_TO_ENTITY(player::get_player_vehicle(player::get_player_ped(g_selected.player), false), true, 0, 0, 6.0f, 5.0f, 2.0f, 0, true, true, true, true, false, true);
                                }
                                break;
                            case 5:
                                if (PED::IS_PED_IN_ANY_VEHICLE(g_selected.ped, FALSE))
                                {
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                                    network::request_control(player::get_player_vehicle(player::get_player_ped(g_selected.player), false));
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;
                                    script::get_current()->yield();
                                    ENTITY::APPLY_FORCE_TO_ENTITY(player::get_player_vehicle(player::get_player_ped(g_selected.player), false), true, 0, 0, 5.0f, 2.0f, 0, 0, true, true, true, true, false, true);
                                }
                                break;
                            case 6:
                                if (PED::IS_PED_IN_ANY_VEHICLE(g_selected.ped, FALSE))
                                {
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                                    network::request_control(player::get_player_vehicle(player::get_player_ped(g_selected.player), false));
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;
                                    script::get_current()->yield();
                                    ENTITY::APPLY_FORCE_TO_ENTITY(player::get_player_vehicle(player::get_player_ped(g_selected.player), false), true, 0, 0, 5.0f, -2.0f, 0, 0, true, true, true, true, false, true);
                                }
                                break;
                            case 7:
                                if (PED::IS_PED_IN_ANY_VEHICLE(g_selected.ped, FALSE))
                                {
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                                    network::request_control(player::get_player_vehicle(player::get_player_ped(g_selected.player), false));
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;
                                    script::get_current()->yield();
                                    ENTITY::APPLY_FORCE_TO_ENTITY(player::get_player_vehicle(player::get_player_ped(g_selected.player), false), true, 0, 0, 7.0f, 0, 0, 0, true, true, true, true, false, true);
                                }
                                break;
                            case 8:
                                if (PED::IS_PED_IN_ANY_VEHICLE(g_selected.ped, FALSE))
                                {
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                                    network::request_control(player::get_player_vehicle(player::get_player_ped(g_selected.player), false));
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;
                                    script::get_current()->yield();
                                    ENTITY::APPLY_FORCE_TO_ENTITY(player::get_player_vehicle(player::get_player_ped(g_selected.player), false), true, 0, 0, 40.0f, 0, 0, 0, true, true, true, true, false, true);
                                }
                                break;
                            }
                            break;
                        case 7:
                            for (int i = 0; i <= 32; i++)
                            {
                                Vehicle player_pv = vehicle_helper::get_personal_vehicle(i);
                                auto pos = entity::get_entity_coords(player_pv, FALSE);
                                fire::add_owned_explosion(g_selected.ped, pos, EXPLOSION_TRAIN, 1000.0f, true, false, 0.0f);
                            }
                            break;
                        }
                    } QUEUE_JOB_END
                }
                if (SelectedNetworkEvent == 3)
                {
                    ImGui::SameLine();
                    if (ImGui::Button("Quit Spectating"))
                    {
                        QUEUE_JOB_BEGIN() 
                        {
                            NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, g_selected.ped);
                        }QUEUE_JOB_END
                    }
                }
                break;
            case 2:
                ImGui::Text(xorstr("Other"));
                ImGui::PushItemWidth(250);
                ImGui::Combo(xorstr("##Other Event"), &SelectedOtherEvent, OtherEvent, IM_ARRAYSIZE(OtherEvent));
                ImGui::PopItemWidth();
                if (SelectedOtherEvent == 0)
                {
                    ImGui::Checkbox(xorstr("Auto Get Into Vehicle"), &AutoGetIn);
                    ImGui::Separator();
                }
                if (SelectedOtherEvent == 5)
                {
                    ImGui::RadioButton(xorstr("Force Quit"), &g_remote_option->disconnect_type, 0);
                    ImGui::SameLine();
                    ImGui::RadioButton(xorstr("Network Error"), &g_remote_option->disconnect_type, 1);
                    ImGui::SameLine();
                    ImGui::RadioButton(xorstr("DoS Attack"), &g_remote_option->disconnect_type, 2);

                    if (g_remote_option->disconnect_type == 0)
                        ImGui::Checkbox(xorstr("Force Quit All?"), &g_remote_option->desktop_all);
                }
                if (SelectedOtherEvent == 6)
                {
                    ImGui::Text(xorstr("Target must inside vehicle"));
                    ImGui::RadioButton(xorstr("Teleport To Me"), &teleport_type, 0);
                    ImGui::RadioButton(xorstr("Teleport To Waypoint"), &teleport_type, 1);
                    ImGui::RadioButton(xorstr("Teleport To Objective"), &teleport_type, 2);
                    ImGui::Checkbox(xorstr("All Player ?"), &all_player);
                }

                if (ImGui::Button(xorstr("Send Event")))
                {
                    QUEUE_JOB_BEGIN()
                    {
                        switch (SelectedOtherEvent)
                        {
                        case 0:
                        {
                            if (!AutoGetIn)
                            {
                                teleport::teleport_to_player(g_local.player, g_selected.player);
                            }
                            if (AutoGetIn)
                            {
                                teleport::teleport_to_player_vehicle(g_selected.player);
                            }
                        }
                        break;
                        case 1:
                        {
                            auto Cloned = ped::clone_ped(g_selected.ped);
                            ENTITY::SET_ENTITY_INVINCIBLE(Cloned, TRUE);
                            WEAPON::GIVE_DELAYED_WEAPON_TO_PED(Cloned, RAGE_JOAAT("WEAPON_MINIGUN"), 9999, TRUE);
                        }
                        break;
                        case 2:
                        {
                            rage::CPedInterface* ped_interface = g_pointers->m_replay_interface->m_ped_interface;
                            for (int i = 0; i < ped_interface->m_max_peds; i++)
                            {
                                auto* ped_ptr = ped_interface->get_ped(i);
                                if (ped_ptr == nullptr)
                                    continue;

                                Ped ped = rage_helper::pointer_to_entity(ped_ptr);
                                if (ped == 0 || ped == g_local.ped || entity::get_entity_health(ped) == 328)
                                    continue;

                                if (entity::get_entity_health(ped) != 328 || ped != g_local.ped)
                                {
                                    network::request_control(ped);
                                    auto pos = entity::get_entity_coords(g_selected.ped, FALSE);
                                    teleport::teleport_to_coords(ped, pos);
                                }
                            }
                        }
                        break;
                        case 3:
                        {
                            Vector3 pos = ENTITY::GET_ENTITY_COORDS(g_selected.ped, true);
                            Hash cage = controller::load("prop_gold_cont_01");
                            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                            Object obj = OBJECT::CREATE_OBJECT(cage, pos.x, pos.y, pos.z - 1.0f, true, false, false);
                            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

                            script::get_current()->yield();
                            if (*g_pointers->m_is_session_started)
                            {
                                ENTITY::_SET_ENTITY_SOMETHING(obj, TRUE); //True means it can be deleted by the engine when switching lobbies/missions/etc, false means the script is expected to clean it up.
                                auto networkId = NETWORK::OBJ_TO_NET(obj);
                                if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(obj))
                                    NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
                            }
                            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(cage);
                        }
                        break;
                        case 4:
                            outfit::steal_outfit(g_selected.player);
                            break;
                        case 5:
                            switch (g_remote_option->disconnect_type)
                            {
                            case 0:
                                if (!g_remote_option->desktop_all)
                                {
                                    if (ENTITY::DOES_ENTITY_EXIST(g_selected.ped))
                                    {
                                        auto pos = ENTITY::GET_ENTITY_COORDS(g_selected.ped, TRUE);
                                        auto forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(g_selected.ped);

                                        remote_event::crash_player(g_selected.ped, pos);

                                        ImGui::InsertNotification({ ImGuiToastType_Ellohim, 3000, "Crash Has Been Sent to %s", PLAYER::GET_PLAYER_NAME(g_selected.player) });
                                    }
                                }
                                if (g_remote_option->desktop_all)
                                {
                                    for (int i = 0; i <= 32; i++)
                                    {
                                        Ped player_ped = player::get_player_ped(i);
                                        if (ENTITY::DOES_ENTITY_EXIST(player_ped))
                                        {
                                            if (player_ped == g_local.ped)
                                                continue;

                                            if (player_ped != g_local.ped)
                                            {
                                                auto coords = ENTITY::GET_ENTITY_COORDS(player_ped, TRUE);
                                                remote_event::crash_player(player_ped, coords);
                                            }
                                        }
                                        script::get_current()->yield();
                                    }
                                    controller::ShowMessage("~g~Crash All Done", false);
                                    ImGui::InsertNotification({ ImGuiToastType_Ellohim, 3000, "Crash All Done" });
                                }
                                break;
                            case 1:
                            {
                                remote_event::bail_player(g_selected.player);
                            }
                            break;
                            case 2:
                            {
                                if (ENTITY::DOES_ENTITY_EXIST(g_selected.ped))
                                {
                                    auto pos = ENTITY::GET_ENTITY_COORDS(g_selected.ped, TRUE);
                                    auto forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(g_selected.ped);

                                    remote_event::crash_player(g_selected.ped, pos);
                                }
                                remote_event::bail_player(g_selected.player);

                                auto message = fmt::format("~g~DoS Attack Has Been Sent to {}", player::get_player_ip(g_selected.player));
                                message::notification(message.c_str(), "~bold~~g~Ellohim DoS Attack");
                            }
                            break;
                            }
                            break;
                        case 6:
                            switch (teleport_type)
                            {
                            case 0:
                                if (PED::IS_PED_IN_ANY_VEHICLE(g_selected.ped, TRUE))
                                {
                                    Vehicle e = PED::GET_VEHICLE_PED_IS_USING(g_selected.ped);
                                    auto pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                                    network::request_control(e);
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;
                                    teleport::teleport_to_coords(e, pos);
                                }
                                break;
                            case 1:
                                if (player::is_player_in_any_vehicle(g_selected.player))
                                {
                                    teleport::teleport_to_marker(g_selected.player);
                                }
                                if (all_player)
                                {
                                    for (int i = 0; i <= 32; i++)
                                    {
                                        if (player::is_player_in_any_vehicle(i))
                                        {
                                            teleport::teleport_to_marker(i);
                                        }
                                    }
                                }
                                break;
                            case 2:
                                if (player::is_player_in_any_vehicle(g_selected.player))
                                {
                                    teleport::teleport_to_objective(g_selected.player);
                                }
                                if (all_player)
                                {
                                    for (int i = 0; i <= 32; i++)
                                    {
                                        if (player::is_player_in_any_vehicle(i))
                                        {
                                            teleport::teleport_to_objective(i);
                                        }
                                    }
                                }
                                break;
                            }
                            break;
                        }
                    }QUEUE_JOB_END
                }
                break;
            }

            ImGui::Checkbox(xorstr("Remote Off Radar"), &g_remote_option->remote_off_the_radars);
            ImGui::SameLine(200);
            ImGui::Checkbox(xorstr("Send Heal"), &g_player_option.send_heal);

            ImGui::Checkbox(xorstr("Remote Bribe"), &g_remote_option->bribe_authority);
            ImGui::SameLine(200);
            ImGui::Checkbox(xorstr("Give Explosive Ammo"), &g_weapon_option.explosive_weapon);

            if (network::network_is_host(g_local.player))
            {
                if (ImGui::Button(xorstr("Kick (Host Only)")))
                {
                    g_fiber_pool->queue_job([]
                    {
                        NETWORK::NETWORK_SESSION_KICK_PLAYER(g_selected.player);
                    });
                }
            }
            if (ImGui::CollapsingHeader(xorstr("Other")))
            {
                ImGui::PushID(xorstr("##Control"));
                if (ImGui::BeginMenu(xorstr("Control Entity")))
                {
                    static char VehicleName[200];
                    ImGui::InputText(xorstr("Vehicle Model Name##Name"), VehicleName, IM_ARRAYSIZE(VehicleName), ImGuiInputTextFlags_CharsUppercase);
                    if (ImGui::Button(xorstr("Ram Player")))
                    {
                        QUEUE_JOB_BEGIN_CLAUSE()
                        {
                            float offset;

                            Hash vehmodel = controller::load(VehicleName);
                            Vector3 pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_selected.ped, 0.0, -10.0, 0.0);

                            if (STREAMING::IS_MODEL_IN_CDIMAGE(vehmodel))
                            {
                                Vector3 dim1, dim2;
                                MISC::GET_MODEL_DIMENSIONS(vehmodel, &dim1, &dim2);

                                offset = dim2.y * 1.6f;

                                Vector3 dir = ENTITY::GET_ENTITY_FORWARD_VECTOR(g_selected.ped);
                                float rot = (ENTITY::GET_ENTITY_ROTATION(g_selected.ped, 0)).z;
                                *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                                Vehicle veh = VEHICLE::CREATE_VEHICLE(vehmodel, pos.x + (dir.x * offset), pos.y + (dir.y * offset), pos.z, rot, TRUE, TRUE, FALSE);
                                *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
                                VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, 0.0f);
                                ENTITY::SET_ENTITY_VISIBLE(veh, true, 0);
                                VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 700.0);
                            }
                        } QUEUE_JOB_END_CLAUSE
                    }

                    ImGui::EndMenu();
                }
                ImGui::PopID();

                ImGui::Separator();

                ImGui::PushID(xorstr("##ObjectSpawner"));
                if (ImGui::BeginMenu(xorstr("Object Spawner")))
                {
                    static int g_selected_object = 0;
                    static char ObjHash[200];
                    ImGui::PushItemWidth(250);
                    ImGui::InputText("Hash Object##Manual", ObjHash, IM_ARRAYSIZE(ObjHash), ImGuiInputTextFlags_CharsUppercase);
                    ImGui::PopItemWidth();
                    if (ImGui::Button("Spawn Object##Manual"))
                    {
                        object::spawn_object(ObjHash, g_selected.ped);
                    }
                    if (ImGui::Button("Attach Object##Manual"))
                    {
                        object::AttacthObject(ObjHash, g_selected.ped);
                    }
                    ImGui::PushItemWidth(250);
                    ImGui::Combo("##ListObject", &g_selected_object, game_variable::object_hash_list, IM_ARRAYSIZE(game_variable::object_hash_list));
                    ImGui::PopItemWidth();
                    if (ImGui::Button("Spawn"))
                    {
                        object::spawn_object(game_variable::object_hash_list[g_selected_object], g_selected.ped);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Attach"))
                    {
                        object::AttacthObject(game_variable::object_hash_list[g_selected_object], g_selected.ped);
                    }
                    if (ImGui::Button("Semi-Godmode"))
                    {
                        QUEUE_JOB_BEGIN_CLAUSE()
                        {
                            auto pos = ENTITY::GET_ENTITY_COORDS(g_selected.ped, TRUE);
                            auto forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(g_selected.ped);
                            auto heading = ENTITY::GET_ENTITY_HEADING(g_selected.ped);

                            Hash hash_object = controller::load("prop_juicestand");
                            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                            auto obj = OBJECT::CREATE_OBJECT(hash_object, pos.x, pos.y, pos.z, TRUE, FALSE, FALSE);
                            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
                            script::get_current()->yield();
                            network::request_control(obj);
                            script::get_current()->yield();
                            ENTITY::SET_ENTITY_INVINCIBLE(obj, TRUE);
                            ENTITY::SET_ENTITY_VISIBLE(obj, FALSE, FALSE);
                            ENTITY::ATTACH_ENTITY_TO_ENTITY(obj, g_selected.ped, SKEL_Spine0, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, FALSE, FALSE, FALSE, TRUE, 2, TRUE);
                        }
                        QUEUE_JOB_END_CLAUSE
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Detach"))
                    {
                        g_fiber_pool->queue_job([]
                            {
                                Ped player_ped = g_selected.ped;
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

                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                                    network::request_control(object);
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;


                                    ENTITY::DETACH_ENTITY(object, 0, 0);
                                    //ENTITY::SET_ENTITY_COORDS(object, 0, 0, -100, 0, 0, 0, 0);
                                    //NETWORK::NETWORK_FADE_OUT_ENTITY(object, 0, 0);
                                    //ENTITY::SET_ENTITY_AS_MISSION_ENTITY(object, 0, 0);
                                    //ENTITY::DELETE_ENTITY(&object);
                                };
                            });
                    }
                    if (ImGui::Button("Remove Object Around"))
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

                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                                    network::request_control(object);
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;
                                    script::get_current()->yield();
                                    //ENTITY::SET_ENTITY_COORDS(object, 0, 0, -100, 0, 0, 0, 0);
                                    NETWORK::NETWORK_FADE_OUT_ENTITY(object, 0, 0);
                                    ENTITY::SET_ENTITY_AS_MISSION_ENTITY(object, 0, 0);
                                    OBJECT::DELETE_OBJECT(&object);
                                };
                            });
                    }
                    ImGui::Checkbox("Apply Force", &g_player_option.is_force_applied);
                    ImGui::EndMenu();
                }
                ImGui::PopID();

                ImGui::Separator();

                ImGui::PushID(xorstr("##VehicleSpawner"));
                if (ImGui::BeginMenu(xorstr("Vehicle Spawner")))
                {
                    ImGui::Text("Bypass : 0x0%X", *(unsigned short*)g_pointers->m_model_spawn_bypass);
                    static char VehHash[200];
                    ImGui::PushItemWidth(250);
                    ImGui::InputText(xorstr("Hash Vehicle##Manual"), VehHash, IM_ARRAYSIZE(VehHash), ImGuiInputTextFlags_CharsUppercase);
                    ImGui::PopItemWidth();
                    if (ImGui::Button(xorstr("Spawn Manual##Manual")))
                    {
                        vehicle_helper::vehicle(VehHash, g_selected.ped);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(xorstr("Plane Chase")))
                    {
                        vehicle_helper::swam(VehHash, g_selected.ped);
                    }
                    if (ImGui::Button(xorstr("Attach Vehicle")))
                    {
                        vehicle_helper::attach_vehicle(VehHash, g_selected.player);
                    }
                    ImGui::SameLine();
                    ImGui::Checkbox(xorstr("Godmode"), &g_toggle.godmode);

                    ImGui::PushItemWidth(250);
                    ImGui::Combo(xorstr("##ListVeh"), &g_vehicle_option->selected_vehicle, game_variable::vehicle_hash_list, IM_ARRAYSIZE(game_variable::vehicle_hash_list)); // The second parameter is the label previewed before opening the combo.
                    ImGui::PopItemWidth();
                    if (ImGui::Button(xorstr("Spawn Native")))
                    {
                        vehicle_helper::vehicle(game_variable::vehicle_hash_list[g_vehicle_option->selected_vehicle], g_selected.ped);
                    }
                    ImGui::SameLine();
                    if (ImGui::Checkbox(xorstr("Maxed Out"), g_settings.options["Full Upgrade Bool"].get<bool*>()))
                        g_settings.save();
                    ImGui::SameLine();
                    if (ImGui::Checkbox(xorstr("Auto Get-in ##V"), g_settings.options["Auto Get-in"].get<bool*>()))
                        g_settings.save();
                    if (ImGui::Button(xorstr("Send CargoPlaneToAll")))
                    {
                        QUEUE_JOB_BEGIN_CLAUSE()
                        {
                            for (int i = 0; i <= 32; i++)
                            {
                                script::get_current()->yield();
                                if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) != g_local.ped)
                                    vehicle_helper::vehicle("Cargoplane", PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
                            }
                        } QUEUE_JOB_END_CLAUSE
                    }
                    if (ImGui::Button(xorstr("Remove Vehicle Around")))
                    {
                        g_fiber_pool->queue_job([]
                            {
                                Ped player_ped = PLAYER::PLAYER_PED_ID();
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

                                    if (vehicle == PED::GET_VEHICLE_PED_IS_USING(player_ped))
                                        continue;

                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                                    network::request_control(vehicle);
                                    *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;
                                    script::get_current()->yield();
                                    //ENTITY::SET_ENTITY_COORDS(vehicle, 0, 0, -100, 0, 0, 0, 0);
                                    NETWORK::NETWORK_FADE_OUT_ENTITY(vehicle, 0, 0);
                                    ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, 0, 0);
                                    VEHICLE::DELETE_VEHICLE(&vehicle);
                                }
                            });
                    }
                    if (ImGui::Button(xorstr("Remove Player Vehicle")))
                    {
                        g_fiber_pool->queue_job([]
                            {
                                Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(g_selected.ped, TRUE);
                                *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                                network::request_control(vehicle);
                                *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;
                                script::get_current()->yield();
                                //ENTITY::SET_ENTITY_COORDS(vehicle, 0, 0, -100, 0, 0, 0, 0);
                                NETWORK::NETWORK_FADE_OUT_ENTITY(vehicle, 0, 0);
                                ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, 0, 0);
                                VEHICLE::DELETE_VEHICLE(&vehicle);
                            });
                    }
                    ImGui::EndMenu();
                }
                ImGui::PopID();

                ImGui::Separator();

                ImGui::PushID(xorstr("##PedSpawner"));
                if (ImGui::BeginMenu(xorstr("Ped Spawner")))
                {
                    static int SelectedPed = 0;
                    static char PedHash[200];
                    ImGui::PushItemWidth(250);
                    ImGui::InputText(xorstr("Ped Hash##Manual"), PedHash, IM_ARRAYSIZE(PedHash), ImGuiInputTextFlags_CharsUppercase);
                    ImGui::PopItemWidth();
                    if (ImGui::Button(xorstr("Spawn Ped##Manual")))
                    {
                        g_fiber_pool->queue_job([] {
                            auto coords = ENTITY::GET_ENTITY_COORDS(g_selected.ped, TRUE);
                            ped::create_ped(rage::joaat(PedHash), coords, 3, TRUE);
                            });
                    }
                    if (ImGui::Button(xorstr("Attach Ped##Manual")))
                    {
                        ped::attach_ped(rage::joaat(PedHash), g_selected.ped);
                    }
                    ImGui::PushItemWidth(250);
                    ImGui::Combo(xorstr("##PedList"), &SelectedPed, game_variable::ped_hash_list, IM_ARRAYSIZE(game_variable::ped_hash_list));
                    ImGui::PopItemWidth();
                    if (ImGui::Button(xorstr("Spawn Ped")))
                    {
                        g_fiber_pool->queue_job([] {
                            auto coords = ENTITY::GET_ENTITY_COORDS(g_selected.ped, TRUE);
                            ped::create_ped(rage::joaat(game_variable::ped_hash_list[SelectedPed]), coords, 3, TRUE);
                            });
                    }
                    if (ImGui::Button(xorstr("Attach Ped")))
                    {
                        ped::attach_ped(rage::joaat(game_variable::ped_hash_list[SelectedPed]), g_selected.ped);
                    }
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

                                *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                                network::request_control(ped);
                                *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;

                                ENTITY::DETACH_ENTITY(ped, 0, 0);
                                //ENTITY::SET_ENTITY_COORDS(ped, 0, 0, -100, 0, 0, 0, 0);
                                NETWORK::NETWORK_FADE_OUT_ENTITY(ped, 0, 0);
                                ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ped, 0, 0);
                                ENTITY::DELETE_ENTITY(&ped);
                            }
                        } QUEUE_JOB_END_CLAUSE
                    }
                    ImGui::Checkbox(xorstr("Invisible Ped"), &g_player_option.is_ped_visible);
                    ImGui::SameLine();
                    ImGui::Checkbox(xorstr("Aggresive Ped"), &g_player_option.is_ped_aggressive);
                    ImGui::Checkbox(xorstr("Body Guard"), &g_player_option.is_ped_bodyguard);

                    ImGui::EndMenu();
                }
                ImGui::PopID();

                ImGui::Separator();

                ImGui::PushID(xorstr("##PickupSpawner"));
                if (ImGui::BeginMenu(xorstr("Pickup Spawner")))
                {
                    static int selected_pickup = 0;
                    static int selected_object = 0;
                    ImGui::Combo(xorstr("##PickupHash"), &selected_pickup, game_variable::pickup_hash_list, IM_ARRAYSIZE(game_variable::pickup_hash_list));
                    ImGui::Combo(xorstr("##PropList"), &selected_object, game_variable::object_hash_list, IM_ARRAYSIZE(game_variable::object_hash_list));
                    if (ImGui::Button(xorstr("Send Pickup")))
                    {
                        object::create_pickup(game_variable::pickup_hash_list[selected_pickup], game_variable::pickup_hash_list[selected_object], 9999, g_selected.ped);
                    }
                    ImGui::EndMenu();
                }
                ImGui::PopID();
            }
            ImGui::EndGroup();
            ImGui::EndTabItem();
        }
    }
}