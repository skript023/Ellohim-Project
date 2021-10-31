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
#include "gui/player_list.h"

namespace big
{
    void player_information::render_player_info()
    {
        if (ImGui::BeginTabItem(xorstr("Player Info")))
        {
            const char* Host = *script_global(1630816).at(g_selected.player, 597).at(10).as<bool*>() ? "True" : "False";

            int TotalMoney = *script_global(1590908).at(g_selected.player, 874).at(205).at(56).as<int*>();
            int TotalCash = *script_global(1590908).at(g_selected.player, 874).at(205).at(3).as<int*>();
            int GlobalRP = *script_global(1590908).at(g_selected.player, 874).at(205).at(5).as<int*>();
            int CurrentEXP = *script_global(1590908).at(g_selected.player, 874).at(205).at(1).as<int*>();
            int PlayerLevel = *script_global(1590908).at(g_selected.player, 874).at(205).at(6).as<int*>();
            int OffTheRadar = *script_global(2426097).at(g_selected.player, 443).at(204).as<int*>();

            int selected_approach = *script_global(g_global.casino_stat).at(g_selected.player, 68).at(22).as<int*>();
            int selected_target = *script_global(g_global.casino_stat).at(g_selected.player, 68).at(18).at(7).as<int*>();
            int selected_hacker = *script_global(g_global.casino_stat).at(g_selected.player, 68).at(18).at(14).as<int*>();
            int selected_driver = *script_global(g_global.casino_stat).at(g_selected.player, 68).at(18).at(12).as<int*>();
            int selected_gunman = *script_global(g_global.casino_stat).at(g_selected.player, 68).at(18).at(10).as<int*>();
            int board_status_1 = *script_global(g_global.casino_stat).at(g_selected.player, 68).at(18).at(1).as<int*>();
            int board_status_2 = *script_global(g_global.casino_stat).at(g_selected.player, 68).at(18).as<int*>();
            int security_pass = *script_global(g_global.casino_stat).at(g_selected.player, 68).at(18).at(15).as<int*>();
            int duggan_level = *script_global(g_global.casino_stat).at(g_selected.player, 68).at(18).at(8).as<int*>();
            int hard_approach = *script_global(g_global.casino_stat).at(g_selected.player, 68).at(24).as<int*>();
            int last_approach = *script_global(g_global.casino_stat).at(g_selected.player, 68).at(23).as<int*>();
            int transition_check = *script_global(2426097).at(g_selected.player, 443).as<int*>();
            int casino_states = 0;//*script_global(2426097).at(g_selected.player, 443).at(314).at(4).as<int*>();
            //auto CEONames = *script_global(1630816).at(g_selected.player, 597).at(11).at(105).as<uint64_t*>();
            const char* is_modded_account = GlobalRP < CurrentEXP ? "True" : "False";
            const char* is_modded_money = TotalMoney >= INT_MAX ? "True" : "False";
            
            const char* casino_status_wajib = board_status_1 == -1 ? "Skip Prep" : (board_status_1 == 127 && selected_approach == 1) ? "Complete" : (board_status_1 == 159 && selected_approach == 2) ? "Complete" : (board_status_1 == 799 && selected_approach == 3) ? "Complete" : (board_status_1 == 0) ? "No Progress" : (board_status_1 > 0) ? "In Progress" : "Mission Not Started";
            const char* casino_status_opsional = board_status_2 == -1 ? "Skip Prep" : (board_status_2 == 61 && selected_approach == 1) ? "Complete" : (board_status_2 == 339990 && selected_approach == 2) ? "Complete" : (board_status_2 == 3670038 && selected_approach == 3) ? "Complete" : board_status_2 == 0 ? "No Progress" : (board_status_2 > 0) ? "In Progress" : "Mission Not Started";
            const char* target_heist = selected_target == 0 ? "Cash" : selected_target == 1 ? "Gold" : selected_target == 2 ? "Art" : selected_target == 3 ? "Diamond" : "Not Selected";
            const char* approach = selected_approach == 0 ? "Not Selected" : selected_approach == 1 ? "Silent" : selected_approach == 2 ? "Bigcon" : selected_approach == 3 ? "Aggressive" : "Not Selected";
            const char* approach_terakhir = last_approach == 0 ? "Not Selected" : last_approach == 1 ? "Silent" : last_approach == 2 ? "Bigcon" : last_approach == 3 ? "Aggressive" : "Not Selected";
            const char* approach_sulit = hard_approach == 0 ? "Not Selected" : hard_approach == 1 ? "Silent" : hard_approach == 2 ? "Bigcon" : hard_approach == 3 ? "Aggressive" : "Not Selected";


            const char* supir;
            switch (selected_driver)
            {
            case 0:
                supir = "Not Selected";
                break;
            case 1:
                supir = "Karim Denz";
                break;
            case 2:
                supir = "Taliana";
                break;
            case 3:
                supir = "Eddie Toh";
                break;
            case 4:
                supir = "Zach";
                break;
            case 5:
                supir = "Chester";
                break;
            default:
                supir = "Not Selected";
                break;
            }
            const char* gunman;
            switch (selected_gunman)
            {
            case 0:
                gunman = "Not Selected";
                break;
            case 1:
                gunman = "Karl Alboraji";
                break;
            case 2:
                gunman = "Gustavo";
                break;
            case 3:
                gunman = "Charlie";
                break;
            case 4:
                gunman = "Chester";
                break;
            case 5:
                gunman = "Packie";
                break;
            default:
                gunman = "Not Selected";
                break;
            }
            const char* hacker;
            switch (selected_gunman)
            {
            case 0:
                hacker = "Not Selected";
                break;
            case 1:
                hacker = "Rickie Luckens";
                break;
            case 2:
                hacker = "Christian";
                break;
            case 3:
                hacker = "Yohan";
                break;
            case 4:
                hacker = "Avi Schwartzman";
                break;
            case 5:
                hacker = "Paige Harris";
                break;
            default:
                hacker = "Not Selected";
                break;
            }
            const char* is_player_off_radar = OffTheRadar == 1 ? "True" : "False";
            int TotalBanked = TotalMoney - TotalCash;


            ImGui::Text("Ped ID : %d", g_selected.ped);
            ImGui::SameLine(200);
            ImGui::Text("Script Host : %s", g_local.ScriptHost == g_selected.player ? "True" : "False");
            ImGui::SameLine(400);
            ImGui::Text("Waterproof : %s", player::get_player_waterproof(g_selected.player) ? "True" : "False");
            ImGui::Text("RID : %d", player::get_player_scid(g_selected.player));
            ImGui::SameLine(200);
            ImGui::Text("Host : %s", Host);
            ImGui::SameLine(400);
            ImGui::Text("Godmode : %s", player::get_player_invincible(g_selected.player) ? "True" : "False");

            ImGui::Text("IP : %s", player::get_player_ip(g_selected.player));
            ImGui::SameLine(200);
            ImGui::Text("Wanted Level : %d", player::get_player_wanted_level(g_selected.player));

            ImGui::Text("Cash : $%d", TotalCash);
            ImGui::SameLine(200);
            ImGui::Text("Bank : $%d", TotalBanked < 0 ? 0 : TotalBanked);
            ImGui::Text("Level : %d", PlayerLevel);
            ImGui::SameLine(200);
            ImGui::Text("Off Radar : %s", is_player_off_radar);
            ImGui::Text("Modded Account : %s", is_modded_account);
            //ImGui::Text(fmt::format("Organization : {}", CEONames).c_str());//systems::character_filter( CEONames.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") != std::string::npos ? "Error" : 

            ImGui::Text("Current EXP : %d/%d", CurrentEXP, GlobalRP);
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
            //ImGui::Text("Casino States : %s", casino_states == 1 << 0 || casino_states == 1 << 11 ? "Always on" : casino_states == 1 << 2 ? "Blackjack" : casino_states == 1 << 3 ? "Poket" : casino_states == 1 << 5 ? "Roulette" : casino_states == 1 << 6 ? "LuckyWheel" : casino_states == 1 << 7 ? "Rig Slot" : casino_states == 1 << 8 ? "Horse Racing" : casino_states == 1 << 13 ? "Using Bar" : casino_states == 1 << 15 ? "Using Hotspring" : "No Data");
            ImGui::Text("Main Mission : %s", casino_status_wajib);
            ImGui::Text("Optional Mission : %s", casino_status_opsional);
            ImGui::Text("Target : %s", target_heist);
            ImGui::Text("Approach : %s", approach);
            ImGui::Text("Last Approach : %s", approach_terakhir);
            ImGui::Text("Hard Approach : %s", approach_sulit);
            ImGui::Text("Driver : %s", supir);
            ImGui::Text("Gunman : %s", gunman);
            ImGui::Text("Hacker : %s", hacker);
            ImGui::Text("Security Pass : Level %d", security_pass);
            ImGui::Text("Disrupted Level : %d", duggan_level);

            ImGui::Separator();
            ImGui::Text("X : %f        Y : %f        Z : %f", g_info.PlayerPosition.x, g_info.PlayerPosition.y, g_info.PlayerPosition.z);

            ImGui::EndTabItem();
        }

    }

    void player_information::render_player_business_info()
    {
        if (ImGui::BeginTabItem(xorstr("Business Info")))
        {
            if (ImGui::CollapsingHeader(xorstr("Business Location")))
            {
                ImGui::Text("Business Location : ");
                ImGui::Text(fmt::format("Meth Location : {}", network::get_meth_location(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Weed Location : {}", network::get_weed_location(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Coke Location :{}", network::get_cocain_location(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Cash Location : {}", network::get_cash_location(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Document Location : {}", network::get_document_location(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Bunker Location : {}", network::get_bunker_location(g_selected.player)).c_str());
                ImGui::Separator();
            }
            if (ImGui::CollapsingHeader(xorstr("Total Stock of Product")))
            {
                ImGui::Text("Business Stock : ");
                ImGui::Text(fmt::format("Meth Product : {}%%", network::get_meth_stock(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Weed Product : {}%%", network::get_weed_stock(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Cocain Product : {}%%", network::get_cocain_stock(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Cash Product : {}%%", network::get_cash_stock(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Document Product : {}%%", network::get_document_stock(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Bunker Product : {}%%", network::get_bunker_stock(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Research Progress : {:.2f}%%", network::get_research_progress(g_selected.player)).c_str());
                ImGui::Separator();
            }
            if (ImGui::CollapsingHeader(xorstr("Total Supply")))
            {
                ImGui::Text("Business Supply : ");
                ImGui::Text(fmt::format("Meth Supply : {}%%", network::get_meth_supply(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Weed Supply : {}%%", network::get_weed_supply(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Cocain Supply : {}%%", network::get_cocain_supply(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Cash Supply : {}%%", network::get_cash_supply(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Document Supply : {}%%", network::get_document_supply(g_selected.player)).c_str());
                ImGui::Text(fmt::format("Bunker Supply : {}%%", network::get_bunker_supply(g_selected.player)).c_str());
            }
            ImGui::EndTabItem();
        }
    }

    void player_information::render_player_event()
    {
        if (ImGui::BeginTabItem(xorstr("Game Event")))
        {
            static const char* const ScriptEvent[]{ "Teleport To Cayo", "Invite Apartment", "CEO Kick", "CEO Ban", "Rotate Cam","Vehicle Kick", "Clear Wanted", "Kick", "Send Transaction Failed", "Send To Mission", "Give Wanted Level", "Fake Money" };
            static const char* const NetworkEvent[]{ "Weapon", "Request Anim Player", "Send Explosion", "Spectate", "Send Shoot", "Repair Vehicle", "Control Vehicle", "Bad Sport" };
            static const char* const OtherEvent[]{ "Teleport To Player", "Clone Player", "Teleport All Ped", "Cage Player", "Steal Costume", "Disconnect", "Force Teleport" };
            static int SelectedScriptEvent = 0;
            static int SelectedNetworkEvent = 0;
            static int SelectedOtherEvent = 0;

            static int SelectedShoot = 0;
            static int MoneyValue = 0;
            static int type = 0;
            static int SelectedExplosion = 0;
            static int SelectedBlame = 0;
            static int WeaponOption = 0;
            static int ExplosiveMode = 0;
            static int teleport_type = 0;
            static int control_type = 0;
            static bool isAudio = true;
            static bool isInvinsible = false;
            static bool AirStrike = false;
            static bool AutoGetIn = false;
            static int event_type = 0;
            static bool bonus_repair = false;
            static bool all_player = false;

            ImGui::RadioButton("Script Event", &event_type, 0);
            ImGui::SameLine();
            ImGui::RadioButton("Network Event", &event_type, 1);
            ImGui::SameLine();
            ImGui::RadioButton("Other##Event", &event_type, 2);

            switch (event_type)
            {
            case 0:
                ImGui::Text("Script Event");
                ImGui::PushItemWidth(250);
                ImGui::Combo("##Script Event", &SelectedScriptEvent, ScriptEvent, IM_ARRAYSIZE(ScriptEvent));
                ImGui::PopItemWidth();
                if (SelectedScriptEvent == 11)
                {
                    ImGui::PushItemWidth(250);
                    ImGui::InputScalar("Money Value", ImGuiDataType_S32, &MoneyValue);
                    ImGui::PopItemWidth();
                    ImGui::RadioButton("Banked", &type, 0);
                    ImGui::SameLine();
                    ImGui::RadioButton("Remove", &type, 1);
                    ImGui::SameLine();
                    ImGui::RadioButton("Steal", &type, 2);
                    ImGui::Separator();
                }

                if (ImGui::Button("Send Event"))
                {
                    switch (SelectedScriptEvent)
                    {
                    case 0:
                        remote_event::teleport_player_to_cayo(g_selected.player);
                        break;
                    case 1:
                        remote_event::force_invite_apartment(g_selected.player);
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
                    }
                }
                break;
            case 1:
                ImGui::Text("Network Event");
                ImGui::PushItemWidth(250);
                ImGui::Combo("##Network Event", &SelectedNetworkEvent, NetworkEvent, IM_ARRAYSIZE(NetworkEvent));
                ImGui::PopItemWidth();
                if (SelectedNetworkEvent == 0)
                {
                    ImGui::RadioButton("Give Weapon", &WeaponOption, 0);
                    ImGui::SameLine();
                    ImGui::RadioButton("Add Ammo", &WeaponOption, 1);
                    ImGui::SameLine();
                    ImGui::RadioButton("Remove Weapon", &WeaponOption, 2);
                    ImGui::Separator();
                }
                if (SelectedNetworkEvent == 4)
                {
                    ImGui::PushItemWidth(250);
                    if (!AirStrike)
                        ImGui::Combo("Select Shoot Type", &SelectedShoot, var::ShootWeapon, IM_ARRAYSIZE(var::ShootWeapon));
                    ImGui::Checkbox("Air Strike", &AirStrike);
                    ImGui::Separator();
                    ImGui::PopItemWidth();
                }
                if (SelectedNetworkEvent == 2)
                {
                    ImGui::PushItemWidth(250);
                    if (ExplosiveMode == 0)
                    {
                        ImGui::Combo("Select Explosion Type", &SelectedExplosion, var::ExplosionList, IM_ARRAYSIZE(var::ExplosionList));
                        //ImGui::Combo("Blame Player", &SelectedBlame, features::PlayerNames, IM_ARRAYSIZE(features::PlayerNames));
                        if (ImGui::BeginCombo("Blame Player", features::PlayerNames[SelectedBlame]))
                        {
                            for (int i = 0; i < 32; ++i)
                            {
                                if (!controller::cstrcmp(features::PlayerNames[i], "**Invalid**"))
                                {
                                    if (ImGui::Selectable(features::PlayerNames[i], i == SelectedBlame))
                                    {
                                        SelectedBlame = i;
                                    }
                                }
                            }
                            ImGui::EndCombo();
                        }
                    }
                    ImGui::Checkbox("Audio", &isAudio);
                    ImGui::Checkbox("Invisible", &isInvinsible);
                    ImGui::RadioButton("Explode Normal", &ExplosiveMode, 0);
                    ImGui::SameLine();
                    ImGui::RadioButton("Explode Lobby Blame", &ExplosiveMode, 1);
                    ImGui::SameLine();
                    ImGui::RadioButton("Explode Lobby", &ExplosiveMode, 2);
                    ImGui::Text("Bypass 1 : 0x%X | Bypass 2 : 0x0%X", *(unsigned short*)g_pointers->m_add_owned_explosion_bypass_1, *(unsigned short*)g_pointers->m_add_owned_explosion_bypass_2);
                    ImGui::Separator();
                    ImGui::PopItemWidth();
                }
                if (SelectedNetworkEvent == 5)
                {
                    ImGui::Checkbox("Bonus Full Upgrade", &bonus_repair);
                }
                if (SelectedNetworkEvent == 6)
                {
                    ImGui::Text("Player Must Inside Vehicle");
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

                if (ImGui::Button("Send Event"))
                {
                    QUEUE_JOB_BEGIN_CLAUSE()
                    {
                        switch (SelectedNetworkEvent)
                        {
                        case 0:
                            switch (WeaponOption)
                            {
                            case 0:
                                int MaxAmmo;
                                for (auto WeaponList : var::AllWeaponHashes)
                                {
                                    if (!WEAPON::HAS_PED_GOT_WEAPON(g_selected.ped, rage::joaat(WeaponList), FALSE))
                                    {
                                        script::get_current()->yield();
                                        for (auto ComponentHashes : var::AllComponentHashes)
                                        {
                                            WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(g_selected.ped, rage::joaat(WeaponList), rage::joaat(ComponentHashes));
                                        }
                                        WEAPON::GIVE_DELAYED_WEAPON_TO_PED(g_selected.ped, rage::joaat(WeaponList), (WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), rage::joaat(WeaponList), &MaxAmmo) == TRUE) ? MaxAmmo : 9999, FALSE);
                                    }
                                }
                                break;
                            case 1:
                                for (auto name : var::AllWeaponHashes)
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
                                for (auto name : var::AllWeaponHashes)
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
                                for (int i = 0; i < g_local.connected_player; i++)
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
                                for (int i = 0; i < g_local.connected_player; i++)
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
                                Ped owner = rage::joaat(var::ShootWeapon[SelectedShoot]) == rage::joaat("WEAPON_STUNGUN") ? PLAYER::PLAYER_PED_ID() : 0;
                                int damage = rage::joaat(var::ShootWeapon[SelectedShoot]) == rage::joaat("WEAPON_STUNGUN") ? 0 : 250;
                                auto Coords = ENTITY::GET_ENTITY_COORDS(g_selected.ped, true);
                                Coords.y += 2;
                                Coords.x += 2;
                                MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x + 2, Coords.y + 2, Coords.z, Coords.x, Coords.y, Coords.z, damage, true, rage::joaat(var::ShootWeapon[SelectedShoot]), owner, true, true, 1000); //VEHICLE_WEAPON_SPACE_ROCKET
                                MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x + 2, Coords.y + 2, Coords.z, Coords.x, Coords.y, Coords.z, damage, false, rage::joaat(var::ShootWeapon[SelectedShoot]), owner, true, true, 1000);
                                MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x + 2, Coords.y + 2, Coords.z, Coords.x, Coords.y, Coords.z, damage, false, rage::joaat(var::ShootWeapon[SelectedShoot]), owner, true, true, 1000);
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
                            for (int i = 0; i <= g_local.connected_player; i++)
                            {
                                Vehicle player_pv = vehicle_helper::get_personal_vehicle(i);
                                auto pos = entity::get_entity_coords(player_pv, FALSE);
                                fire::add_owned_explosion(g_selected.ped, pos, EXPLOSION_TRAIN, 1000.0f, true, false, 0.0f);
                            }
                            break;
                        }
                    } QUEUE_JOB_END_CLAUSE
                }
                if (SelectedNetworkEvent == 3)
                {
                    ImGui::SameLine();
                    if (ImGui::Button("Quit Spectating"))
                    {
                        g_fiber_pool->queue_job([] {
                            NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, g_selected.ped);
                            });
                    }
                }
                break;
            case 2:
                ImGui::Text("Other");
                ImGui::PushItemWidth(250);
                ImGui::Combo("##Other Event", &SelectedOtherEvent, OtherEvent, IM_ARRAYSIZE(OtherEvent));
                ImGui::PopItemWidth();
                if (SelectedOtherEvent == 0)
                {
                    ImGui::Checkbox("Auto Get Into Vehicle", &AutoGetIn);
                    ImGui::Separator();
                }
                if (SelectedOtherEvent == 5)
                {
                    ImGui::RadioButton("Desktop", &g_fitur.disconnect_type, 0);
                    ImGui::SameLine();
                    ImGui::RadioButton("Network Error", &g_fitur.disconnect_type, 1);
                    ImGui::SameLine();
                    ImGui::RadioButton("DoS Attack", &g_fitur.disconnect_type, 2);

                    if (g_fitur.disconnect_type == 0)
                        ImGui::Checkbox("Desktop All?", &g_fitur.desktop_all);
                }
                if (SelectedOtherEvent == 6)
                {
                    ImGui::Text("Target must inside vehicle");
                    ImGui::RadioButton("Teleport To Me", &teleport_type, 0);
                    ImGui::RadioButton("Teleport To Waypoint", &teleport_type, 1);
                    ImGui::RadioButton("Teleport To Objective", &teleport_type, 2);
                    ImGui::Checkbox("All Player ?", &all_player);
                }

                if (ImGui::Button("Send Event"))
                {
                    g_fiber_pool->queue_job([]
                        {
                            switch (SelectedOtherEvent)
                            {
                            case 0:
                            {
                                if (!AutoGetIn)
                                {
                                    teleport::teleport_to_player(g_selected.player);
                                }
                                if (AutoGetIn)
                                {
                                    teleport::teleport_to_player_vehicle(g_selected.player);
                                }
                            }
                            break;
                            case 1:
                            {
                                auto Cloned = controller::ClonePed(g_selected.ped);
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
                                Vector3 remotePos = ENTITY::GET_ENTITY_COORDS(g_selected.ped, true);
                                constexpr auto cage = RAGE_JOAAT("prop_gold_cont_01");
                                Object obj = OBJECT::CREATE_OBJECT(cage, remotePos.x, remotePos.y, remotePos.z - 1.0f, true, false, false);
                            }
                            break;
                            case 4:
                                outfit::StealOutfit(g_selected.player);
                                break;
                            case 5:
                                switch (g_fitur.disconnect_type)
                                {
                                case 0:
                                    if (!g_fitur.desktop_all)
                                    {
                                        if (ENTITY::DOES_ENTITY_EXIST(g_selected.ped))
                                        {
                                            auto pos = ENTITY::GET_ENTITY_COORDS(g_selected.ped, TRUE);
                                            auto forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(g_selected.ped);

                                            Ped NewPed = controller::CrashPlayer(g_selected.ped, pos);
                                            int tick = 0;
                                            while (tick < 32)
                                            {
                                                script::get_current()->yield();
                                                tick++;
                                            }

                                            if (ENTITY::DOES_ENTITY_EXIST(NewPed))
                                            {
                                                ENTITY::DETACH_ENTITY(NewPed, FALSE, FALSE);
                                                ENTITY::SET_ENTITY_COORDS_NO_OFFSET(NewPed, -5000.0f, -5000.0f, -100.0f, FALSE, FALSE, TRUE);
                                                NETWORK::NETWORK_FADE_OUT_ENTITY(NewPed, FALSE, FALSE);
                                                ENTITY::SET_ENTITY_AS_MISSION_ENTITY(NewPed, FALSE, FALSE);
                                                ENTITY::DELETE_ENTITY(&NewPed);

                                                char message[100];
                                                strcpy(message, "~g~Crash Has Been Sent to ");
                                                strcat(message, PLAYER::GET_PLAYER_NAME(g_selected.player));
                                                message::notification("~bold~~g~Ellohim Private Menu", message, "~bold~~g~Ellohim Event Sender");
                                            }
                                        }
                                    }
                                    if (g_fitur.desktop_all)
                                    {
                                        Ped NewPed[33]{};
                                        int done = 0;
                                        for (int i = 0; i <= g_local.connected_player; i++)
                                        {
                                            Ped AllPlayer = player::get_player_ped(i);
                                            if (ENTITY::DOES_ENTITY_EXIST(AllPlayer))
                                            {
                                                if (AllPlayer == g_local.ped) {
                                                    continue;
                                                }

                                                if (AllPlayer != g_local.ped) {
                                                    auto coords = ENTITY::GET_ENTITY_COORDS(AllPlayer, TRUE);
                                                    NewPed[i] = controller::CrashPlayer(AllPlayer, coords);
                                                }
                                            }
                                            script::get_current()->yield();
                                        }

                                        for (auto ped : NewPed)
                                        {
                                            if (ENTITY::DOES_ENTITY_EXIST(ped))
                                            {
                                                ENTITY::DETACH_ENTITY(ped, FALSE, FALSE);
                                                ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ped, -5000.0f, -5000.0f, -100.0f, FALSE, FALSE, TRUE);
                                                NETWORK::NETWORK_FADE_OUT_ENTITY(ped, FALSE, FALSE);
                                                ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ped, FALSE, FALSE);
                                                ENTITY::DELETE_ENTITY(&ped);
                                            }
                                        }
                                        controller::ShowMessage("~g~Crash All End", false);
                                    }
                                    break;
                                case 1:
                                {
                                    int64_t bail_event[3] = { 2092565704, g_local.player, *script_global(1630816).at(g_selected.player, 597).at(508).as<int64_t*>() };
                                    SCRIPT::TRIGGER_SCRIPT_EVENT(1, bail_event, 3, 1 << g_selected.player);
                                }
                                break;
                                case 2:
                                {
                                    if (ENTITY::DOES_ENTITY_EXIST(g_selected.ped))
                                    {
                                        auto pos = ENTITY::GET_ENTITY_COORDS(g_selected.ped, TRUE);
                                        auto forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(g_selected.ped);

                                        Ped NewPed = controller::CrashPlayer(g_selected.ped, pos);
                                        int tick = 0;
                                        while (tick < 32)
                                        {
                                            script::get_current()->yield();
                                            tick++;
                                        }

                                        if (ENTITY::DOES_ENTITY_EXIST(NewPed))
                                        {
                                            ENTITY::DETACH_ENTITY(NewPed, FALSE, FALSE);
                                            ENTITY::SET_ENTITY_COORDS_NO_OFFSET(NewPed, -5000.0f, -5000.0f, -100.0f, FALSE, FALSE, TRUE);
                                            NETWORK::NETWORK_FADE_OUT_ENTITY(NewPed, FALSE, FALSE);
                                            ENTITY::SET_ENTITY_AS_MISSION_ENTITY(NewPed, FALSE, FALSE);
                                            ENTITY::DELETE_ENTITY(&NewPed);
                                        }
                                    }
                                    int64_t bail_event[3] = { 2092565704, g_local.player, *script_global(1630816).at(g_selected.player, 597).at(508).as<int64_t*>() };
                                    SCRIPT::TRIGGER_SCRIPT_EVENT(1, bail_event, 3, 1 << g_selected.player);

                                    auto message = fmt::format("~g~DoS Attack Has Been Sent to {}", player::get_player_ip(g_selected.player));
                                    message::notification("~bold~~g~Ellohim Private Menu", message.c_str(), "~bold~~g~Ellohim DoS Attack");
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
                                        script::get_current()->yield();
                                        teleport::teleport_to_coords(e, pos);
                                    }
                                    break;
                                case 1:
                                    if (PED::IS_PED_IN_ANY_VEHICLE(g_selected.ped, TRUE))
                                    {
                                        Vehicle e = PED::GET_VEHICLE_PED_IS_USING(g_selected.ped);

                                        Vector3 coords = blip::get_blip_coords(Waypoint, WaypointColor);

                                        if (systems::is_3d_vector_zero(coords))
                                            return;

                                        coords = teleport::GetGroundCoords(coords, 30);
                                        *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                                        network::request_control(e);
                                        *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;
                                        script::get_current()->yield();
                                        teleport::teleport_to_coords(e, coords);
                                    }
                                    if (all_player)
                                    {
                                        for (int i = 0; i <= 32; i++)
                                        {
                                            if (PED::IS_PED_IN_ANY_VEHICLE(player::get_player_ped(i), TRUE))
                                            {
                                                Vehicle e = PED::GET_VEHICLE_PED_IS_USING(player::get_player_ped(i));

                                                Vector3 coords = blip::get_blip_coords(Waypoint, WaypointColor);

                                                if (systems::is_3d_vector_zero(coords))
                                                    return;

                                                coords = teleport::GetGroundCoords(coords, 30);
                                                *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                                                network::request_control(e);
                                                *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;
                                                script::get_current()->yield();
                                                teleport::teleport_to_coords(e, coords);
                                            }
                                        }
                                    }
                                    break;
                                case 2:
                                    if (PED::IS_PED_IN_ANY_VEHICLE(g_selected.ped, TRUE))
                                    {
                                        Vehicle e = PED::GET_VEHICLE_PED_IS_USING(g_selected.ped);

                                        Vector3 coords = teleport::get_mission_blip();

                                        if (systems::is_3d_vector_zero(coords))
                                            return;

                                        *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                                        network::request_control(e);
                                        *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;

                                        script::get_current()->yield();
                                        teleport::teleport_to_coords(e, coords);
                                    }
                                    if (all_player)
                                    {
                                        for (int i = 0; i <= 32; i++)
                                        {
                                            if (PED::IS_PED_IN_ANY_VEHICLE(player::get_player_ped(i), TRUE))
                                            {
                                                Vehicle e = PED::GET_VEHICLE_PED_IS_USING(player::get_player_ped(i));

                                                Vector3 coords = teleport::get_mission_blip();

                                                if (systems::is_3d_vector_zero(coords))
                                                    return;

                                                *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                                                network::request_control(e);
                                                *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;

                                                script::get_current()->yield();
                                                teleport::teleport_to_coords(e, coords);
                                            }
                                        }
                                    }
                                    break;
                                }
                                break;
                            }
                        });
                }
                break;
            }

            ImGui::Checkbox("Remote Off Radar", &features::remoteOTR);
            ImGui::SameLine(200);
            ImGui::Checkbox("Send Heal", &features::send_heal);

            ImGui::Checkbox("Remote Bribe", &features::RemoteBribeToggle);
            ImGui::SameLine(200);
            ImGui::Checkbox("Give Explosive Ammo", &g_fitur.explosive_weapon);

            bool IsHost = *script_global(1630816).at(g_local.player, 597).at(10).as<bool*>();
            if (IsHost)
            {
                if (ImGui::Button("Kick (Host Only)"))
                {
                    g_fiber_pool->queue_job([]
                        {
                            NETWORK::NETWORK_SESSION_KICK_PLAYER(g_selected.player);
                        });
                }
            }
            if (ImGui::CollapsingHeader("Other"))
            {
                ImGui::PushID("##Control");
                if (ImGui::BeginMenu("Control Entity"))
                {
                    static char VehicleName[200];
                    ImGui::InputText("Vehicle Model Name##Name", VehicleName, IM_ARRAYSIZE(VehicleName), ImGuiInputTextFlags_CharsUppercase);
                    if (ImGui::Button("Ram Player"))
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

                ImGui::PushID("##ObjectSpawner");
                if (ImGui::BeginMenu("Object Spawner"))
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
                    ImGui::Combo("##ListObject", &g_selected_object, var::ObjectList, IM_ARRAYSIZE(var::ObjectList));
                    ImGui::PopItemWidth();
                    if (ImGui::Button("Spawn"))
                    {
                        object::spawn_object(var::ObjectList[g_selected_object], g_selected.ped);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Attach"))
                    {
                        object::AttacthObject(var::ObjectList[g_selected_object], g_selected.ped);
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
                    ImGui::Checkbox("Apply Force", &player_list::ApplyForce);
                    ImGui::EndMenu();
                }
                ImGui::PopID();

                ImGui::Separator();

                ImGui::PushID("##VehicleSpawner");
                if (ImGui::BeginMenu("Vehicle Spawner"))
                {
                    ImGui::Text("Bypass : 0x0%X", *(unsigned short*)g_pointers->m_model_spawn_bypass);
                    static char VehHash[200];
                    ImGui::PushItemWidth(250);
                    ImGui::InputText("Hash Vehicle##Manual", VehHash, IM_ARRAYSIZE(VehHash), ImGuiInputTextFlags_CharsUppercase);
                    ImGui::PopItemWidth();
                    if (ImGui::Button("Spawn Manual##Manual"))
                    {
                        vehicle_helper::vehicle(VehHash, g_selected.ped);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Plane Chase"))
                    {
                        vehicle_helper::swam(VehHash, g_selected.ped);
                    }
                    if (ImGui::Button("Attach Vehicle"))
                    {
                        vehicle_helper::attach_vehicle(VehHash, g_selected.player);
                    }
                    ImGui::SameLine();
                    ImGui::Checkbox("Godmode", &g_toggle.godmode);

                    ImGui::PushItemWidth(250);
                    ImGui::Combo("##ListVeh", &player_list::SelectedVehicle, var::VechicleList, IM_ARRAYSIZE(var::VechicleList)); // The second parameter is the label previewed before opening the combo.
                    ImGui::PopItemWidth();
                    if (ImGui::Button("Spawn Native"))
                    {
                        vehicle_helper::vehicle(var::VechicleList[player_list::SelectedVehicle], g_selected.ped);
                    }
                    ImGui::SameLine();
                    if (ImGui::Checkbox("Maxed Out", g_settings.options["Full Upgrade Bool"].get<bool*>()))
                        g_settings.save();
                    ImGui::SameLine();
                    if (ImGui::Checkbox("Auto Get-in ##V", g_settings.options["Auto Get-in"].get<bool*>()))
                        g_settings.save();
                    if (ImGui::Button("Send CargoPlaneToAll"))
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
                    if (ImGui::Button("Remove Vehicle Around"))
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
                    if (ImGui::Button("Remove Player Vehicle"))
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

                ImGui::PushID("##PedSpawner");
                if (ImGui::BeginMenu("Ped Spawner"))
                {
                    static int SelectedPed = 0;
                    static char PedHash[200];
                    ImGui::PushItemWidth(250);
                    ImGui::InputText("Ped Hash##Manual", PedHash, IM_ARRAYSIZE(PedHash), ImGuiInputTextFlags_CharsUppercase);
                    ImGui::PopItemWidth();
                    if (ImGui::Button("Spawn Ped##Manual"))
                    {
                        g_fiber_pool->queue_job([] {
                            auto coords = ENTITY::GET_ENTITY_COORDS(g_selected.ped, TRUE);
                            controller::CreatePed(rage::joaat(PedHash), coords, 3, TRUE);
                            });
                    }
                    if (ImGui::Button("Attach Ped##Manual"))
                    {
                        controller::AttachPed(rage::joaat(PedHash), g_selected.ped);
                    }
                    ImGui::PushItemWidth(250);
                    ImGui::Combo("##PedList", &SelectedPed, var::PedList, IM_ARRAYSIZE(var::PedList));
                    ImGui::PopItemWidth();
                    if (ImGui::Button("Spawn Ped"))
                    {
                        g_fiber_pool->queue_job([] {
                            auto coords = ENTITY::GET_ENTITY_COORDS(g_selected.ped, TRUE);
                            controller::CreatePed(rage::joaat(var::PedList[SelectedPed]), coords, 3, TRUE);
                            });
                    }
                    if (ImGui::Button("Attach Ped"))
                    {
                        controller::AttachPed(rage::joaat(var::PedList[SelectedPed]), g_selected.ped);
                    }
                    if (ImGui::Button("Detach Ped"))
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
                    ImGui::Checkbox("Invisible Ped", &player_list::IsVisible);
                    ImGui::SameLine();
                    ImGui::Checkbox("Aggresive Ped", &player_list::AggressivePed);
                    ImGui::Checkbox("Body Guard", &player_list::AsBodyGuard);

                    ImGui::EndMenu();
                }
                ImGui::PopID();

                ImGui::Separator();

                ImGui::PushID("##PickupSpawner");
                if (ImGui::BeginMenu("Pickup Spawner"))
                {
                    static int selected_pickup = 0;
                    static int selected_object = 0;
                    ImGui::Combo("##PickupHash", &selected_pickup, var::PickupHash, IM_ARRAYSIZE(var::PickupHash));
                    ImGui::Combo("##PropList", &selected_object, var::ObjectList, IM_ARRAYSIZE(var::ObjectList));
                    if (ImGui::Button("Send Pickup"))
                    {
                        object::CreatePickup(var::PickupHash[selected_pickup], var::ObjectList[selected_object], 9999, g_selected.ped);
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