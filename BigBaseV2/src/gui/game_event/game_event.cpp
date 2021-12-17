#include "natives.hpp"
#include "common.hpp"
#include "gta_util.hpp"
#include "script_local.hpp"
#include "gta\VehicleValues.h"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include "features.hpp"
#include "gui/controller/ScriptController.h"
#include "gui/player_list.h"
#include "gui/player_list.h"
#include "gta/Weapons.h"
#include "gui/controller/game_variable.h"
#include "game_event.h"
#include "gui/controller/memory_address.hpp"
#include "gui/entity/entity_control.h"

namespace big
{
    Ped remote_event::crash_player(Entity target, Vector3 SpawnCoordinates)
    {
        Ped NewPed;
        Hash PedHash = rage::joaat("slod_human");
        auto playerPosition = ENTITY::GET_ENTITY_COORDS(g_local.ped, TRUE);
        if (MISC::GET_DISTANCE_BETWEEN_COORDS(playerPosition.x, playerPosition.y, playerPosition.z, SpawnCoordinates.x, SpawnCoordinates.y, SpawnCoordinates.z, false) > 300.0f)
        {
            if (STREAMING::IS_MODEL_IN_CDIMAGE(PedHash))
            {
                if (STREAMING::IS_MODEL_VALID(PedHash))
                {
                    STREAMING::REQUEST_MODEL(PedHash);
                    while (!STREAMING::HAS_MODEL_LOADED(PedHash))
                    {
                        script::get_current()->yield();
                    }

                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                    NewPed = PED::CREATE_PED(3, PedHash, SpawnCoordinates.x, SpawnCoordinates.y, SpawnCoordinates.z, 0, TRUE, TRUE);
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
                    // Segmentation Fault
                    script::get_current()->yield();
                    if (*g_pointers->m_is_session_started)
                    {
                        ENTITY::_SET_ENTITY_SOMETHING(NewPed, TRUE); //True means it can be deleted by the engine when switching lobbies/missions/etc, false means the script is expected to clean it up.
                        auto networkId = NETWORK::PED_TO_NET(NewPed);
                        if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(NewPed))
                            NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
                    }
                    ENTITY::ATTACH_ENTITY_TO_ENTITY(NewPed, target, SKEL_Spine0, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, FALSE, FALSE, TRUE, TRUE, 2, TRUE);

                    STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PedHash);
                    return NewPed;
                }
            }
        }
        else
        {
            controller::ShowMessage("Crash failed because target is near you", false);
            return -1;
        }
        return -1;
    }

    void remote_event::take_all_cayo(int take)
    {
        QUEUE_JOB_BEGIN_CLAUSE(take)
        {
            int64_t cayo_take[] = { TAKE_CAYO, g_local.player, take, 1 };
            for (int i = 0; i <= g_local.connected_player; i++)
            {
                SCRIPT::TRIGGER_SCRIPT_EVENT(1, cayo_take, 4, 1 << i);
                script::get_current()->yield();
            }
        } QUEUE_JOB_END_CLAUSE
    }

    void remote_event::take_all_casino(int take)
    {
        QUEUE_JOB_BEGIN_CLAUSE(take)
        {
            rage_helper::execute_as_script(RAGE_JOAAT("fm_mission_controller"), [take] {
                *script_global(g_global.show_take).as<int*>() = 32;
                *script_global(g_global.casino_take_indicator).as<int*>() = 1;
                *script_global(g_global.pasific_standard).as<int*>() = take;
                script::get_current()->yield(1500ms);
                int64_t casino_take[] = { TAKE_PASIFIC, g_local.player, *script_global(g_global.pasific_standard).as<int*>(), 1, 1, 0, 0, 0 };
                for (int i = 0; i <= g_local.connected_player; i++)
                {
                    SCRIPT::TRIGGER_SCRIPT_EVENT(1, casino_take, 8, 1 << i);
                    script::get_current()->yield();
                }
                script::get_current()->yield(2000ms);
                *script_global(g_global.pasific_standard).as<int*>() = 1000000;
            });
        } QUEUE_JOB_END_CLAUSE
    }

    void remote_event::take_casino_partial(int take)
    {
        QUEUE_JOB_BEGIN_CLAUSE(take)
        {
            *script_global(g_global.artwork).as<int*>() = (take * 100) / 18;
            script::get_current()->yield(1500ms);
            int64_t casino_take[] = { TAKE_CASINO, g_local.player, 5, 1 };
            for (int i = 0; i <= g_local.connected_player; i++)
            {
                SCRIPT::TRIGGER_SCRIPT_EVENT(1, casino_take, 4, 1 << i);
                script::get_current()->yield();
            }
            *script_global(g_global.artwork).as<int*>() = 2350000;
        } QUEUE_JOB_END_CLAUSE
    }

    void remote_event::set_bounty(Player player, int amount)
    {
        g_fiber_pool->queue_job([=]
        {
            int64_t args[22] = {
            1294995624, // 0
            PLAYER::PLAYER_ID(), // 1 Player in script self
            player, // 2 Player in script self
            0, // 3 unk
            amount, // 4
            0, // 5 => never set
            1, // 6 => always 1
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            *script_global(1921036).at(9).as<int*>(),
            *script_global(1921036).at(10).as<int*>()
            };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 22, 1 << player);
        });
    }

    void remote_event::give_wanted_level(Player player)
    {
        g_fiber_pool->queue_job([player]
        {
            Vector3 coordinate = { 0.0f, 0.0f, 0.0f };
            ped::create_ped(rage::joaat("s_m_y_swat_01"), coordinate, 3, TRUE);
            *(PWORD)g_pointers->m_add_owned_explosion_bypass_1 = 0xE990;
            *(PWORD)g_pointers->m_add_owned_explosion_bypass_2 = 0x9090;
            FIRE::ADD_OWNED_EXPLOSION(player, coordinate.x, coordinate.y, coordinate.z, EXPLOSION_TRAIN, 1000.0f, TRUE, FALSE, 2.0f);
            *(PWORD)g_pointers->m_add_owned_explosion_bypass_1 = 0x850F;
            *(PWORD)g_pointers->m_add_owned_explosion_bypass_2 = 0x0E74;
        });
    }

    void remote_event::steal_fake_money(Player player, int TotalMoney)
    {
        g_fiber_pool->queue_job([player, TotalMoney]
        {
            int64_t steal_money[4] = { FAKE_MONEY, g_local.player, FAKE_STEAL, TotalMoney };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, steal_money, 9, 1 << g_selected.player);
        });
    }

    void remote_event::remove_fake_money(Player player, int TotalMoney)
    {
        g_fiber_pool->queue_job([player, TotalMoney]
        {
            int64_t remove_money[4] = { FAKE_MONEY, g_local.player, FAKE_REMOVE, TotalMoney };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, remove_money, 9, 1 << g_selected.player);
        });
    }

    void remote_event::give_fake_money(Player player, int TotalMoney)
    {
        g_fiber_pool->queue_job([player, TotalMoney]
        {
            int64_t banked_money[4] = { FAKE_MONEY, g_local.player, FAKE_BANKED, TotalMoney };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, banked_money, 9, 1 << g_selected.player);
        });
    }

    void remote_event::send_to_mission(Player player)
    {
        g_fiber_pool->queue_job([player]
        {
            int64_t send_to_mission_1[9] = { SEND_TO_MISSION_1, g_local.player, 0, 0, 0, -1, 1, 1, 0 };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, send_to_mission_1, 9, 1 << player);

            int64_t send_to_mission_2[9] = { SEND_TO_MISSION_2, g_local.player, 0, 0, 0, -1, 1, 1, 0 };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, send_to_mission_2, 9, 1 << player);
        });
    }

    void remote_event::transaction_fail(Player player)
    {
        g_fiber_pool->queue_job([player]
        {
            int64_t trans_fail[8] = { TRANSACTION_ERROR, g_local.player, 10000, 0, 0, *script_global(1893548).at(player, 600).at(511).as<int64_t*>(), *script_global(1921036).at(9).as<int64_t*>(), *script_global(1921036).at(9).as<int64_t*>() };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, trans_fail, 8, 1 << player);
        });
    }

    void remote_event::kick_player(Player player)
    {
        g_fiber_pool->queue_job([player]
        {
                for (int64_t KickEvent : var::KickHash)
                {
                    int64_t kick[2] = { KickEvent, g_local.player };
                    SCRIPT::TRIGGER_SCRIPT_EVENT(1, kick, 2, 1 << player);
                }
        });
    }

    void remote_event::clear_wanted(Player player)
    {
        g_fiber_pool->queue_job([player]
        {
            int64_t clear_wanted[3] = { CLEAR_WANTED, g_selected.player, *script_global(1893548).at(player, 600).at(511).as<int64_t*>() };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, clear_wanted, 3, 1 << player);
        });
    }

    void remote_event::vehicle_kick(Player player)
    {
        g_fiber_pool->queue_job([player]
        {
            int64_t vehicle_kick[2] = { VEHICLE_KICK, g_local.player };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, vehicle_kick, 2, 1 << player);
        });
    }

    void remote_event::rotate_cam(Player player)
    {
        g_fiber_pool->queue_job([player]
        {
            int64_t rotate_cam[3] = { ROTATE_CAM, g_local.player, -1952943290 };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, rotate_cam, 3, 1 << player);
        });
    }

    void remote_event::ceo_ban(Player player)
    {
        g_fiber_pool->queue_job([player]
        {
            int64_t ceo_ban[4] = { CEO_BAN , g_local.player, 1, 5 };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, ceo_ban, 4, 1 << player);
        });
    }

    void remote_event::ceo_kick(Player player)
    {
        g_fiber_pool->queue_job([player]
        {
            int64_t ceo_kick[4] = { CEO_KICK , g_local.player, 1, 5 };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, ceo_kick, 4, 1 << player);
        });
    }

    void remote_event::force_invite_apartment(Player player)
    {
        g_fiber_pool->queue_job([player]
        {
            int64_t invite_apartment[9] = { TELEPORT_APARTMENT, g_local.player, 1, -1, 1, 12728, 0, 1, 0 };//uint64_t args[9] = { 1097312011 , player, 1, -1, 1, 12728, 0, 1, 0 };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, invite_apartment, 9, 1 << player);//uint64_t soundspam[4] = { 1097312011, player, 0, 0 }; sound spam
        });
    }

    void remote_event::teleport_player_to_cayo(Player player)
    {
        g_fiber_pool->queue_job([player]
        {
            int64_t send_to_cayo[2] = { TELEPORT_CAYO , g_local.player };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, send_to_cayo, 2, 1 << player);
        });
    }

    void remote_event::revenge_kick(bool Activation)
    {
        if (Activation)
        {
            rage::CPedInterface* ped_interface = g_pointers->m_replay_interface->m_ped_interface;
            for (int i = 0; i < ped_interface->m_max_peds; i++)
            {
                auto* ped_ptr = ped_interface->get_ped(i);
                if (ped_ptr == nullptr)
                    continue;

                Ped ped = g_pointers->m_ptr_to_handle(ped_ptr);
                if (ped == 0)
                    break;

                Player player = NETWORK::NETWORK_GET_PLAYER_INDEX_FROM_PED(ped);
                if (PED::IS_PED_A_PLAYER(ped))
                {
                    if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(g_local.InVehicle ? g_local.PlayerVehicle : g_local.ped, ped, TRUE) && WEAPON::HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(g_local.InVehicle ? g_local.PlayerVehicle : g_local.ped, 0, 2))
                    {
                        bail_player(player);
                        controller::ShowMessage(fmt::format("~g~Kick Has Been Sent To {}", PLAYER::GET_PLAYER_NAME(player)).c_str(), false);
                    }
                }
            }
        }
    }

    void remote_event::get_name_from_event_hash(int32_t hash)
    {

    }

    void remote_event::trigger_event(int64_t* args, int argsCount, int bitset)
    {
        g_fiber_pool->queue_job([args, argsCount, bitset] {
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, argsCount, bitset);
        });
    }

    void remote_event::bail_player(Player player)
    {
        g_fiber_pool->queue_job([player]
        {
            int64_t bail_event[3] = { BAIL_NETWORK, g_local.player, *script_global(1893548).at(player, 600).at(511).as<int64_t*>() };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, bail_event, 3, 1 << player);
        });
    }

    bool script_helper::is_script_active(Hash ScriptHash)
    {
        return rage_helper::find_script_thread(ScriptHash) != nullptr;
    }

    void remote_event::remote_off_the_radar(bool toggle)
    {
        if (toggle)
        {
            int64_t args[7] = { OFF_RADAR, g_local.player, *script_global(g_global.radar_time).at(70).as<int*>(), NETWORK::GET_NETWORK_TIME(), 1, 1, *script_global(1893548).at(g_selected.player, 600).at(511).as<int64_t*>() };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 7, 1 << g_selected.player);
            *script_global(g_global.radar_toggle).at(g_selected.player, 449).at(209).as<bool*>() = toggle;
        }
    }

    void remote_event::remote_blind_cops(bool toggle)
    {
        if (toggle)
        {
            int64_t args[7] = { -151720011, g_local.player, 0, *script_global(g_global.blind_cops).at(4625).as<int*>(), NETWORK::GET_NETWORK_TIME(), 1, *script_global(1893548).at(g_selected.player, 600).at(511).as<int64_t*>() };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 7, 1 << g_selected.player);
            *script_global(g_global.blind_cops).at(4623).as<bool*>() = toggle;
        }
    }

    std::filesystem::path script_tester::get_events_config()
    {
        auto file_path = std::filesystem::path(std::getenv("appdata"));
        file_path /= "Ellohim Menu";

        if (!std::filesystem::exists(file_path))
        {
            std::filesystem::create_directory(file_path);
        }
        else if (!std::filesystem::is_directory(file_path))
        {
            std::filesystem::remove(file_path);
            std::filesystem::create_directory(file_path);
        }

        file_path /= "TestEvents.json";

        return file_path;
    }

    nlohmann::json script_tester::get_events_json()
    {
        auto file_path = get_events_config();
        nlohmann::json locations;
        std::ifstream file(file_path);

        if (!file.fail())
            file >> locations;

        return locations;
    }

    std::vector<std::string> script_tester::list_events()
    {
        std::vector<std::string> return_value;
        auto json = get_events_json();
        for (auto& item : json.items())
            return_value.push_back(item.key());
        return return_value;
    }

    void script_tester::load_event_menu(std::string& selected_event, event_json::event_json& event_obj)
    {
        if (!selected_event.empty())
        {
            auto events = get_events_json();
            if (events[selected_event].is_null())
                return;
            event_obj = events[selected_event].get<event_json::event_json>();
        }
    }

    void script_tester::save_event(char* event_name, event_json::event_json& event_obj)
    {
        std::string teleport_name_string = event_name;
        if (!teleport_name_string.empty())
        {
            auto json = get_events_json();
            json[event_name] = event_obj;

            auto file_path = get_events_config();
            std::ofstream file(file_path, std::ios::out | std::ios::trunc);
            file << json.dump(4);
            file.close();
            ZeroMemory(event_name, sizeof(event_name));
        }
    }

    void script_tester::delete_event(std::string name)
    {
        auto locations = get_events_json();
        if (locations[name].is_null())
            return;
        locations.erase(name);
        auto file_path = get_events_config();
        std::ofstream file(file_path, std::ios::out | std::ios::trunc);
        file << locations.dump(4);
        file.close();
    }

    std::filesystem::path global_tester::get_globals_config()
    {
        auto file_path = std::filesystem::path(std::getenv("appdata"));
        file_path /= "Ellohim Menu";

        if (!std::filesystem::exists(file_path))
        {
            std::filesystem::create_directory(file_path);
        }
        else if (!std::filesystem::is_directory(file_path))
        {
            std::filesystem::remove(file_path);
            std::filesystem::create_directory(file_path);
        }

        file_path /= "TestGlobals.json";

        return file_path;
    }

    nlohmann::json global_tester::get_globals_json()
    {
        auto file_path = get_globals_config();
        nlohmann::json locations;
        std::ifstream file(file_path);

        if (!file.fail())
            file >> locations;

        return locations;
    }

    std::map<std::string, global_test_json::global_test_json> return_value;

    std::map<std::string, global_test_json::global_test_json> list_globals()
    {
        auto json = global_tester::get_globals_json();
        for (auto& item : json.items())
            return_value[item.key()] = item.value();
        return return_value;
    }

    void global_tester::load_global_menu(const std::string& selected_global, global_test_json::global_test_json& global_obj)
    {
        if (!selected_global.empty())
        {
            auto globals = get_globals_json();
            if (globals[selected_global].is_null())
                return;
            global_obj = globals[selected_global].get<global_test_json::global_test_json>();
        }
    }

    void global_tester::save_global(char* global_name, global_test_json::global_test_json& global_obj)
    {
        std::string teleport_name_string = global_name;
        if (!teleport_name_string.empty())
        {
            auto json = get_globals_json();
            json[global_name] = global_obj;

            auto file_path = get_globals_config();
            std::ofstream file(file_path, std::ios::out | std::ios::trunc);
            file << json.dump(4);
            file.close();
            ZeroMemory(global_name, sizeof(global_name));
        }
    }

    void global_tester::delete_global(std::string name)
    {
        auto locations = get_globals_json();
        if (locations[name].is_null())
            return;
        locations.erase(name);
        auto file_path = get_globals_config();
        std::ofstream file(file_path, std::ios::out | std::ios::trunc);
        file << locations.dump(4);
        file.close();
    }

    int64_t* global_tester::get_global_ptr(global_test_json::global_test_json& global_test)
    {
        script_global global_to_read = script_global(global_test.global_index);
        for (auto item : global_test.global_appendages)
        {
            if (item.type == GlobalAppendageType_At)
            {
                if (item.size != 0)
                    global_to_read = global_to_read.at(item.index, item.size);
                else
                    global_to_read = global_to_read.at(item.index);
            }
            else if (item.type == GlobalAppendageType_ReadGlobal)
            {
                global_test_json::global_test_json global_read;
                load_global_menu(item.global_name, global_read);
                if (auto ptr = get_global_ptr(global_read))
                    if (item.size != 0)
                        global_to_read = global_to_read.at(*ptr, item.size);
                    else
                        global_to_read = global_to_read.at(*ptr);
                else
                    LOG(WARNING) << "Failed to read " << item.global_name << "for get_global_ptr";
            }
            else if (item.type == GlobalAppendageType_PlayerId)
            {
                if (item.size != 0)
                    global_to_read = global_to_read.at(g_local.player, item.size);
                else
                    global_to_read = global_to_read.at(g_local.player);
            }
        }
        auto retn_val = global_to_read.as<int64_t*>();
        if ((size_t)retn_val < UINT32_MAX)
            return nullptr;
        return retn_val;
    }

    std::filesystem::path local_tester::get_locals_config()
    {
        auto file_path = std::filesystem::path(std::getenv("appdata"));
        file_path /= "Ellohim Menu";

        if (!std::filesystem::exists(file_path))
        {
            std::filesystem::create_directory(file_path);
        }
        else if (!std::filesystem::is_directory(file_path))
        {
            std::filesystem::remove(file_path);
            std::filesystem::create_directory(file_path);
        }

        file_path /= "TestLocals.json";

        return file_path;
    }

    nlohmann::json local_tester::get_locals_json()
    {
        auto file_path = get_locals_config();
        nlohmann::json locations;
        std::ifstream file(file_path);

        if (!file.fail())
            file >> locations;

        return locations;
    }

    std::map<std::string, local_test_json::local_test_json> return_local;

    std::map<std::string, local_test_json::local_test_json> list_locals()
    {
        auto json = local_tester::get_locals_json();
        for (auto& item : json.items())
            return_local[item.key()] = item.value();
        return return_local;
    }

    void local_tester::load_local_menu(const std::string& selected_local, local_test_json::local_test_json& local_obj)
    {
        if (!selected_local.empty())
        {
            auto locals = get_locals_json();
            if (locals[selected_local].is_null())
                return;
            local_obj = locals[selected_local].get<local_test_json::local_test_json>();
        }
    }

    void local_tester::save_local(char* local_name, local_test_json::local_test_json& local_obj)
    {
        std::string teleport_name_string = local_name;
        if (!teleport_name_string.empty())
        {
            auto json = get_locals_json();
            json[local_name] = local_obj;

            auto file_path = get_locals_config();
            std::ofstream file(file_path, std::ios::out | std::ios::trunc);
            file << json.dump(4);
            file.close();
            ZeroMemory(local_name, sizeof(local_name));
        }
    }

    void local_tester::delete_local(std::string name)
    {
        auto locations = get_locals_json();
        if (locations[name].is_null())
            return;
        locations.erase(name);
        auto file_path = get_locals_config();
        std::ofstream file(file_path, std::ios::out | std::ios::trunc);
        file << locations.dump(4);
        file.close();
    }

    int32_t* local_tester::get_local_ptr(GtaThread* scriptThread, local_test_json::local_test_json& local_test)
    {
        script_local local_to_read = script_local(scriptThread, local_test.local_index);
        for (auto item : local_test.local_appendages)
        {
            if (item.type == LocalAppendageType_At)
            {
                if (item.size != 0)
                    local_to_read = local_to_read.at(item.index, item.size);
                else
                    local_to_read = local_to_read.at(item.index);
            }
            else if (item.type == LocalAppendageType_ReadGlobal)
            {
                local_test_json::local_test_json local_read;
                load_local_menu(item.local_name, local_read);
                if (auto ptr = get_local_ptr(scriptThread, local_read))
                    if (item.size != 0)
                        local_to_read = local_to_read.at(*ptr, item.size);
                    else
                        local_to_read = local_to_read.at(*ptr);
                else
                    LOG(WARNING) << "Failed to read " << item.local_name << "for get_local_ptr";
            }
            else if (item.type == LocalAppendageType_PlayerId)
            {
                if (item.size != 0)
                    local_to_read = local_to_read.at(g_local.player, item.size);
                else
                    local_to_read = local_to_read.at(g_local.player);
            }
        }
        auto retn_val = local_to_read.as<int32_t*>();
        if ((size_t)retn_val < UINT32_MAX)
            return nullptr;
        return retn_val;
    }

}
