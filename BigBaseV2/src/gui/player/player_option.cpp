#include "natives.hpp"
#include "common.hpp"
#include "gta_util.hpp"
#include "script_local.hpp"
#include "gta/VehicleValues.h"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include "features.hpp"
#include "gui/controller/blackhole_helper.hpp"
#include "gta/Weapons.h"
#include "gui/controller/game_variable.h"
#include "gui/player/player_option.h"
#include "gui/entity/entity_control.h"
#include "gui/object/object.h"
#include "gui/controller/memory_address.hpp"
#include "gui/controller/system_control.h"
#include "gta/net_object_mgr.hpp"
#include "gui/weapons/weapon_helper.h"
#include "gui/vehicle/vehicle_helper.h"
#include "gui/artificial_intelligence/artificial_intelligence.h"
#include "gui/controller/http_request.hpp"
#include "gui/controller/xostr.h"
#include "gui/controller/network_controller.h"
#include <gui/window/imgui_notify.h>

#pragma warning (disable:4172)

#define ARRAY_SIZE(_ARR)          ((int)(sizeof(_ARR) / sizeof(*(_ARR))))
#define ARR_SZ(_ARR)              ((int)(sizeof(_ARR) / sizeof((_ARR)[0])))

namespace big
{
    void player::set_playeer_super_punch(bool activate)
    {
        static const auto default = rage_helper::get_local_ped()->m_playerinfo->m_super_punch;
        if (activate)
            rage_helper::get_local_ped()->m_playerinfo->m_super_punch = 1000.f;
        else
            rage_helper::get_local_ped()->m_playerinfo->m_super_punch = default;
    }

    void player::set_player_no_damage(bool activate)
    {
        static const auto default_health = rage_helper::get_local_ped()->m_playerinfo->m_damage_hp;
        static const auto default_armour = rage_helper::get_local_ped()->m_playerinfo->m_damage_armour;
        if (activate)
        {
            rage_helper::get_local_ped()->m_playerinfo->m_damage_hp = 0.f;
            rage_helper::get_local_ped()->m_playerinfo->m_damage_armour = 0.f;
        }
        else
        {
            rage_helper::get_local_ped()->m_playerinfo->m_damage_hp = default_health;
            rage_helper::get_local_ped()->m_playerinfo->m_damage_armour = default_armour;
        }
    }

    std::string player::get_player_city(Player player)
    {
        try
        {
            http::Request request{ fmt::format("http://ip-api.com/json/{}", get_player_ip(player)) };

            // send a get request
            const auto response = request.send("GET");
            auto result = nlohmann::json::parse(response.body.begin(), response.body.end());
            return result["city"].get<std::string>(); // print the result
        }
        catch (const std::exception& e)
        {
            LOG(HACKER) << "Request failed, error: " << e.what();
        }
        return "Unidentified";
    }

    std::string player::get_player_internet_provider(Player player)
    {
        try
        {
            http::Request request{ fmt::format("http://ip-api.com/json/{}", get_player_ip(player)) };

            // send a get request
            const auto response = request.send("GET");
            auto result = nlohmann::json::parse(response.body.begin(), response.body.end());
            return result["isp"].get<std::string>(); // print the result
        }
        catch (const std::exception& e)
        {
            LOG(HACKER) << "Request failed, error: " << e.what();
        }
        return "Unidentified";
    }

    std::string player::get_player_country(Player player)
    {
        try
        {
            http::Request request{ fmt::format("http://ip-api.com/json/{}", get_player_ip(player)) };

            // send a get request
            const auto response = request.send("GET");
            auto result = nlohmann::json::parse(response.body.begin(), response.body.end());
            return result["country"].get<std::string>(); // print the result
        }
        catch (const std::exception& e)
        {
            LOG(HACKER) << "Request failed, error: " << e.what();
        }
        return "Unidentified";
    }

    const char* player::get_player_heist_hacker(Player player)
    {
        int selected_hacker = *script_global(g_global.casino_stat).at(player, 68).at(18).at(14).as<int*>();
        switch (selected_hacker)
        {
            case 1:
                return "Rickie Luckens";
            case 2:
                return "Christian";
            case 3:
                return "Yohan";
            case 4:
                return "Avi Schwartzman";
            case 5:
                return "Paige Harris";
        }
        return "Not Selected";
    }

    const char* player::get_player_heist_gunman(Player player)
    {
        int selected_gunman = *script_global(g_global.casino_stat).at(player, 68).at(18).at(10).as<int*>();
        switch (selected_gunman)
        {
            case 1:
                return"Karl Alboraji";
            case 2:
                return"Gustavo";
            case 3:
                return"Charlie";
            case 4:
                return"Chester";
            case 5:
                return"Packie";
        }
        return"Not Selected";
    }

    const char* player::get_player_heist_driver(Player player)
    {
        int selected_driver = *script_global(g_global.casino_stat).at(player, 68).at(18).at(12).as<int*>();
        switch (selected_driver)
        {
            case 1:
                return "Karim Denz";
            case 2:
                return "Taliana";
            case 3:
                return "Eddie Toh";
            case 4:
                return "Zach";
            case 5:
                return "Chester";
        }
        return "Not Selected";
    }

    const char* player::get_player_heist_target(Player player)
    {
        int selected_target = *script_global(g_global.casino_stat).at(player, 68).at(18).at(7).as<int*>();
        switch (selected_target)
        {
            case 0:
                return "Cash";
            case 1:
                return "Gold";
            case 2:
                return "Artwork";
            case 3:
                return "Diamond";
        }
        return "Unidentified";
    }

    const char* player::get_player_heist_hard_approach(Player player)
    {
        int selected_approach = *script_global(g_global.casino_stat).at(player, 68).at(24).as<int*>();
        switch (selected_approach)
        {
        case 1:
            return "Silent";
        case 2:
            return "Bigcon";
        case 3:
            return "Aggressive";
        }
        return "Not Selected";
    }

    const char* player::get_player_heist_last_approach(Player player)
    {
        int selected_approach = *script_global(g_global.casino_stat).at(player, 68).at(23).as<int*>();
        switch (selected_approach)
        {
        case 1:
            return "Silent";
        case 2:
            return "Bigcon";
        case 3:
            return "Aggressive";
        }
        return "Not Selected";
    }

    const char* player::get_player_heist_approach(Player player)
    {
        int selected_approach = *script_global(g_global.casino_stat).at(player, 68).at(22).as<int*>();
        switch (selected_approach)
        {
            case 1: 
                return "Silent";
            case 2:
                return "Bigcon";
            case 3:
                return "Aggressive";
        }
        return "Not Selected";
    }

    const char* player::get_player_heist_secondary_status(Player player)
    {
        int board_status_2 = *script_global(g_global.casino_stat).at(player, 68).at(18).as<int*>();
        int selected_approach = *script_global(g_global.casino_stat).at(player, 68).at(22).as<int*>();
        const char* casino_status_opsional = board_status_2 == -1 ? "Skip Prep" : (board_status_2 == 61 && selected_approach == 1) ? "Completed" : (board_status_2 == 339990 && selected_approach == 2) ? "Completed" : (board_status_2 == 3670038 && selected_approach == 3) ? "Completed" : board_status_2 == 0 ? "No Progress" : (board_status_2 > 0) ? "In Progress" : "Mission Not Started";
        return casino_status_opsional;
    }

    const char* player::get_player_heist_primary_status(Player player)
    {
        int board_status_1 = *script_global(g_global.casino_stat).at(player, 68).at(18).at(1).as<int*>();
        int selected_approach = *script_global(g_global.casino_stat).at(player, 68).at(22).as<int*>();
        const char* casino_status_wajib = board_status_1 == -1 ? "Skip Prep" : (board_status_1 == 127 && selected_approach == 1) ? "Completed" : (board_status_1 == 159 && selected_approach == 2) ? "Completed" : (board_status_1 == 799 && selected_approach == 3) ? "Completed" : (board_status_1 == 0) ? "No Progress" : (board_status_1 > 0) ? "In Progress" : "Mission Not Started";
        return casino_status_wajib;
    }

    const char* player::is_modded_account(Player player)
    {
        auto result = get_player_exp(player) > get_player_global_exp(player);
        return result ? "True" : "False";
    }

    std::string player::get_player_banked_money(Player player)
    {
        systems::money_formatter get_money("US");
        auto total = *script_global(g_global.player_stat).at(player, g_global.player_size).at(g_global.player_offset).at(56).as<int*>();
        auto cash = *script_global(g_global.player_stat).at(player, g_global.player_size).at(g_global.player_offset).at(3).as<int*>();
        int banked = (total - cash);
        auto result = banked < 0 ? 0 : banked;
        return get_money.as_string(static_cast<double>(result));
    }

    int player::get_player_level(Player player)
    {
        return *script_global(g_global.player_stat).at(player, g_global.player_size).at(g_global.player_offset).at(6).as<int*>();
    }

    int player::get_player_exp(Player player)
    {
        return *script_global(g_global.player_stat).at(player, g_global.player_size).at(g_global.player_offset).at(1).as<int*>();
    }

    int player::get_player_global_exp(Player player)
    {
        return *script_global(g_global.player_stat).at(player, g_global.player_size).at(g_global.player_offset).at(5).as<int*>();
    }

    std::string player::get_player_cash(Player player)
    {
        systems::money_formatter get_money("US");
        auto player_money = *script_global(g_global.player_stat).at(player, g_global.player_size).at(g_global.player_offset).at(3).as<int*>();
        return get_money.as_string(static_cast<double>(player_money));
    }

    int player::get_player_total_money(Player player)
    {
        auto player_total_money = *script_global(g_global.player_stat).at(player, g_global.player_size).at(g_global.player_offset).at(56).as<int*>();
        return player_total_money;
    }

    void player::get_player_location(Player player)
    {
        const std::string domain = "https://get.geojs.io";
        const std::string path = fmt::format("/v1/ip/geo/{}.json", player::get_player_ip(player));

        http::Request request(domain + path);
        std::string body;
        http::Response res = request.send("GET", body);
        LOG(HACKER) << body;
    }

    void player::global_exp_correction()
    {
        g_fiber_pool->queue_job([] 
        {
            int first_account = *script_global(g_global.player_exp).at(0).as<int*>();
            int second_account = *script_global(g_global.player_exp).at(1).as<int*>();
            int total = first_account + second_account;
            int global_exp = 0;
            STATS::STAT_GET_INT(RAGE_JOAAT("MPPLY_GLOBALXP"), &global_exp, -1);
            script::get_current()->yield();
            if (global_exp == total)
            {
                ImGui::InsertNotification({ ImGuiToastType_Ellohim, 7000, "Your RP is already corrected" });
            }
            else if (global_exp != total)
            {
                STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_GLOBALXP"), total, true);
                ImGui::InsertNotification({ ImGuiToastType_Ellohim, 7000, "Your RP has been corrected" });
            }
        });
    }

    bool player::is_player_driver(Ped Ped)
    {
        if (CPed* ped = rage_helper::entity_to_pointer<CPed*>(Ped))
        {
            if (ped->m_is_in_vehicle)
            {
                if (auto vehicle = ped->m_last_vehicle)
                {
                    if (auto driver = vehicle->m_driver_ped)
                    {
                        if (auto ptr_to_entity = rage_helper::pointer_to_entity(driver))
                        {
                            return ptr_to_entity == Ped;
                        }
                    }
                }
            }
        }
        return false;
    }

    bool player::is_ped_enemy(Ped Ped)
    {
        auto ped_pointer = rage_helper::entity_to_pointer<CPed*>(Ped);
        auto ped_hostility = ped_pointer->m_hostility;
        return (ped_hostility & 0xff) > 1;
    }

    int player::get_ped_type(Entity Ped)
    {
        auto ped_pointer = rage_helper::entity_to_pointer<uintptr_t*>(Ped);
        auto ped_types = *(uint32_t*)((uintptr_t)ped_pointer + 0x10B8);
        return ((ped_types >> 14) & 0x1f);
    }

    bool player::is_player_model_valid(rage::netSyncTree* netSyncTree, rage::netObject* netObject)
    {
        auto Hash = netSyncTree->m_sync_tree_node->m_player_model;
        auto object_type = netObject->object_type;
        if (Hash == RAGE_JOAAT("MP_M_FREEMODE_01") && object_type == NetObjEntityType_Player)
            return true;
        else if (Hash == RAGE_JOAAT("MP_F_FREEMODE_01") && object_type == NetObjEntityType_Player)
            return true;

        return false;
    }

    std::string player::get_ped_name_from_hash(Hash hash)
    {
        std::string sVar0 = std::to_string(hash);
        for (auto ped : game_variable::ped_hash_list)
        {
            if (rage::reverse_joaat(ped, hash))
            {
                sVar0 = rage::joaat_to_string(ped, hash);
            }
        }
        return sVar0;
    }

    void player::set_player_no_clip(bool toggle) 
    {
        if (toggle)
        {
            int e = rage_helper::get_local_ped()->m_is_in_vehicle ? g_local.PlayerVehicle : g_local.ped;
            if (rage_helper::get_local_ped()->m_is_in_vehicle && !player::is_player_driver(g_local.ped))
                network::request_control(e);
            Vector3 pos = ENTITY::GET_ENTITY_COORDS(e, false);
            ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, pos.x, pos.y, pos.z, false, false, false);
            if (GetAsyncKeyState(systems::hotkey('S')))
            {
                float fivef = .5f;
                float heading = ENTITY::GET_ENTITY_HEADING(e);
                float xVec = fivef * sin(systems::degree_to_radian(heading)) * -1.5f;
                float yVec = fivef * cos(systems::degree_to_radian(heading));
                ENTITY::SET_ENTITY_HEADING(e, heading);

                pos.x -= xVec, pos.y -= yVec;
                ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, pos.x, pos.y, pos.z, false, false, false);
            }
            if (GetAsyncKeyState(systems::hotkey('W')))
            {
                float fivef = .5f;
                float heading = ENTITY::GET_ENTITY_HEADING(e);
                float xVec = fivef * sin(systems::degree_to_radian(heading)) * -1.5f;
                float yVec = fivef * cos(systems::degree_to_radian(heading));
                ENTITY::SET_ENTITY_HEADING(e, heading);

                pos.x += xVec, pos.y += yVec;
                ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, pos.x, pos.y, pos.z, false, false, false);
            }
            if (GetAsyncKeyState(systems::hotkey('A')))
            {
                float fivef = .5f;
                float heading = ENTITY::GET_ENTITY_HEADING(e);
                ENTITY::SET_ENTITY_HEADING(e, heading + 0.5f);
            }
            if (GetAsyncKeyState(systems::hotkey('D')))
            {
                float fivef = .5f;
                float heading = ENTITY::GET_ENTITY_HEADING(e);
                ENTITY::SET_ENTITY_HEADING(e, heading - 0.5f);
            }
            if (GetAsyncKeyState(VK_CONTROL))
            {
                float heading = ENTITY::GET_ENTITY_HEADING(e);
                ENTITY::SET_ENTITY_HEADING(e, heading);

                pos.z -= 0.5f;
                ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, pos.x, pos.y, pos.z, false, false, false);
            }
            if (GetAsyncKeyState(VK_SHIFT))
            {
                float heading = ENTITY::GET_ENTITY_HEADING(e);
                ENTITY::SET_ENTITY_HEADING(e, heading);

                pos.z += 0.5f;
                ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, pos.x, pos.y, pos.z, false, false, false);
            }
        }
    }

    void player::set_player_health(Player player, int HealthValue)
    {
        if (auto pointer = rage_helper::get_player_pointer(player))
        {
            pointer->m_health = systems::int_to_float(HealthValue);
        }
    }

    void player::set_player_armour(Player player, int ArmourValue)
    {
        if (auto pointer = rage_helper::get_player_pointer(player))
        {
            pointer->m_armor = systems::int_to_float(ArmourValue);
        }
    }

    void player::disable_player_ragdoll(Player player, bool activation)
    {
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            if (activation && ped->m_ragdoll > 0x0F)
            {
                ped->m_ragdoll = 0x01;
            }
            else if (!activation && ped->m_ragdoll <= 0x0F)
            {
                ped->m_ragdoll = 0x20;
            }
        }
    }

    bool player::is_player_in_any_vehicle(Player player)
    {
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            return ped->m_is_in_vehicle;
        }
        return false;
    }

    Vehicle player::get_player_vehicle(Ped ped, bool last_vehicle)
    {
        if (auto player = rage_helper::entity_to_pointer<CPed*>(ped))
        {
            if (last_vehicle)
            {
                if (auto player_vehicle = player->m_last_vehicle)
                {
                    return g_pointers->m_ptr_to_handle(player_vehicle);
                }
            }
            else
            {
                if (player->m_is_in_vehicle)
                {
                    if (auto player_vehicle = player->m_last_vehicle)
                    {
                        return g_pointers->m_ptr_to_handle(player_vehicle);
                    }
                }
            }
        }
        return 0;
    }

    Ped player::get_player_ped(Player player)
    {
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            return rage_helper::pointer_to_entity(ped);
        }
        return 0;
    }

    void player::no_idle_kick(bool Trigger)
    {
        if (Trigger)
        {
            *script_global(262145).at(87).as<int*>() = INT32_MAX;
            *script_global(262145).at(88).as<int*>() = INT32_MAX;
            *script_global(262145).at(89).as<int*>() = INT32_MAX;
            *script_global(262145).at(90).as<int*>() = INT32_MAX;
        }
        else
        {
            *script_global(262145).at(87).as<int*>() = 120000;
            *script_global(262145).at(88).as<int*>() = 300000;
            *script_global(262145).at(89).as<int*>() = 600000;
            *script_global(262145).at(90).as<int*>() = 900000;
        }
    }

    void player::auto_heal(bool Activation)
    {
        if (Activation)
        {
            int player_health = get_player_health(g_local.player);
            int player_max_health = get_player_max_health(g_local.player);
            int player_max_armor = PLAYER::GET_PLAYER_MAX_ARMOUR(g_local.player);
            if (player_health >= 100 && player_health <= 200)
            {
                set_player_health(g_local.player, player_max_health);
                set_player_armour(g_local.player, player_max_armor);
                rage_helper::get_local_playerinfo()->m_damage_hp = 0.3f;
            }
            else
            {
                rage_helper::get_local_playerinfo()->m_damage_hp = 1.0f;
            }
        }
    }

    void player::player_health_regeneration(bool Activation)
    {
        if (Activation)
        {
            int player_health = entity::get_entity_health(g_local.ped);
            int player_max_health = entity::get_entity_max_health(g_local.ped);
            if (player_health < player_max_health)
            {
                player::set_player_health(g_local.player, player_health += 7);
            }
        }
    }

    void player::set_player_wanted_level(Player player, int Wantedlevel)
    {
        if (auto player_ped = rage_helper::get_player_pointer(player))
        {
            player_ped->m_playerinfo->m_wanted_level = Wantedlevel;
        }
    }

    bool player::does_player_exist(Player player)
    {
        if (auto player_ped = rage_helper::get_player_pointer(player))
        {
            return true;
        }
        return false;
    }

    void player::never_wanted(bool Activation)
    {
        bool is_wanted_level = rage_helper::get_local_playerinfo()->m_is_wanted;
        if (Activation)
        {
            if (is_wanted_level)
            {
                rage_helper::execute_as_script(RAGE_JOAAT("shop_controller"), [] 
                {
                    PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
                });
            }
        }
    }

    void player::mission_lives(bool Activation)
    {
        if (Activation)
        {
            if (auto fm_mission_controller = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller")))
            {
                *script_local(fm_mission_controller, m_local.tc_live).as<int*>() = 9999;
            }

            if (auto mission_controller_2020 = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")))
            {
                *script_local(mission_controller_2020, m_local.tc_live_c).as<int*>() = 9999;
            }
        }
        else
        {
            if (auto fm_mission_controller = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller")))
            {
                *script_local(fm_mission_controller, m_local.tc_live).as<int*>() = 1;
            }
            else if (auto mission_controller_2020 = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")))
            {
                *script_local(mission_controller_2020, m_local.tc_live_c).as<int*>() = 1;
            }
        }
    }

    void player::set_player_invincible(Player player, bool Activation)
    {
        if (auto player_ped = rage_helper::get_player_pointer(player))
        {
            if (Activation && !player_ped->is_invincible())
            {
                player_ped->enable_invincible();
            }
            else if (!Activation && player_ped->is_invincible())
            {
                player_ped->disable_invincible();
            }
        }
    }

    void player::set_player_seatbelt(bool Activation)
    {
        if (Activation)
        {
            rage_helper::get_local_ped()->seatbelt = 0xC9;
        }
        else
        {
            rage_helper::get_local_ped()->seatbelt = 0xC8;
        }
    }

    void player::set_player_waterproof(Player player, bool Activation)
    {
        if (auto player_ped = rage_helper::get_player_pointer(player))
        {
            if (Activation && !systems::is_float_equal(player_ped->m_navigation->m_ph_arche->m_water_collision, 0.0f))
            {
                player_ped->m_navigation->m_ph_arche->m_water_collision = 0;// = 0x1000000;
            }
            else if (!Activation && systems::is_float_equal(player_ped->m_navigation->m_ph_arche->m_water_collision, 0.0f))
            {
                player_ped->m_navigation->m_ph_arche->m_water_collision = 1.f;// = 0x4194316;
            }
        }
    }

    void player::set_player_infinite_oxygen(Player player, bool activation)
    {
        if (auto player_ped = rage_helper::get_player_pointer(player))
        {
            static const float default_value = player_ped->m_unk_player->m_oxygen;
            if (activation)
            {
                player_ped->m_unk_player->m_oxygen = 0.f;
            }
            else
            {
                player_ped->m_unk_player->m_oxygen = default_value;
            }
        }
    }

    void player::blind_cops(bool Activation)
    {
        if (Activation && *g_pointers->m_is_session_started)
        {
            *script_global(g_global.blind_cops).at(g_global.blind_cops_offset).as<int*>() = 1;
            *script_global(g_global.blind_cops).at(g_global.blind_cops_offset).at(2).as<int*>() = NETWORK::GET_NETWORK_TIME();
            *script_global(g_global.blind_cops).at(g_global.blind_cops_offset-1).as<int*>() = 5;
        }
        else if (!Activation && *g_pointers->m_is_session_started)
        {
            *script_global(g_global.blind_cops).at(g_global.blind_cops_offset).as<int*>() = 0;
            *script_global(g_global.blind_cops).at(g_global.blind_cops_offset).at(2).as<int*>() = 0;
            *script_global(g_global.blind_cops).at(g_global.blind_cops_offset-1).as<int*>() = 0;
        }
    }

    void player::reveal_player(bool Activation)
    {
        if (Activation && *g_pointers->m_is_session_started)
        {
            *script_global(g_global.radar_toggle).at(PLAYER::PLAYER_ID(), g_global.radar_size).at(212).as<int*>() = 1;
            *script_global(g_global.radar_time).at(71).as<int*>() = NETWORK::GET_NETWORK_TIME();
        }
        else if (!Activation && *g_pointers->m_is_session_started)
        {
            *script_global(g_global.radar_toggle).at(PLAYER::PLAYER_ID(), g_global.radar_size).at(212).as<int*>() = 0;
            *script_global(g_global.radar_time).at(71).as<int*>() = NETWORK::GET_NETWORK_TIME();
        }
    }

    void player::off_the_radar(bool Activation)
    {
        if (Activation && *g_pointers->m_is_session_started)
        {
            *script_global(g_global.radar_toggle).at(PLAYER::PLAYER_ID(), g_global.radar_size).at(g_global.radar_offset).as<int*>() = 1;
            *script_global(g_global.radar_time).at(70).as<int*>() = NETWORK::GET_NETWORK_TIME();
            *script_global(2544210).at(4628).as<int*>() = 3;
        }
        else if (!Activation && *g_pointers->m_is_session_started)
        {
            *script_global(g_global.radar_toggle).at(PLAYER::PLAYER_ID(), g_global.radar_size).at(g_global.radar_offset).as<int*>() = 0;
            *script_global(g_global.radar_time).at(70).as<int*>() = 0;
            *script_global(2544210).at(4628).as<int*>() = 0;
        }
    }

    void player::ghost_organization(bool Activation)
    {
        if (Activation && *g_pointers->m_is_session_started)
        {
            *script_global(g_global.radar_toggle).at(PLAYER::PLAYER_ID(), g_global.radar_size).at(g_global.radar_offset).as<int*>() = 1;
            *script_global(g_global.radar_time).at(70).as<int*>() = NETWORK::GET_NETWORK_TIME();
            *script_global(g_global.radar_type).as<int*>() = 4;
        }
        else if (!Activation && *g_pointers->m_is_session_started)
        {
            *script_global(g_global.radar_toggle).at(PLAYER::PLAYER_ID(), g_global.radar_size).at(g_global.radar_offset).as<int*>() = 0;
            *script_global(g_global.radar_time).at(70).as<int*>() = 0;
            *script_global(g_global.radar_type).as<int*>() = 0;
        }
    }

    void player::set_player_no_collision(bool Activation)
    {
        static const float default_value = rage_helper::get_local_ped()->m_navigation->m_ph_arche->get_geometry(0)->m_collision;
        if (Activation)
        {
            rage_helper::get_local_ped()->m_navigation->m_ph_arche->get_geometry(0)->m_collision = -1.0f;//Memory::set_value(g_ptr.WorldPTR, { 0x8, 0x30, 0x10, 0x20, 0x70, 0x0, 0x2C }, -1.0f);
        }
        else
        {
            rage_helper::get_local_ped()->m_navigation->m_ph_arche->get_geometry(0)->m_collision = default_value;//Memory::set_value(g_ptr.WorldPTR, { 0x8, 0x30, 0x10, 0x20, 0x70, 0x0, 0x2C }, 0.25f);
        }
    }

    void player::local_name(char* Name)
    {
        strcpy(rage_helper::get_local_playerinfo()->m_name, Name);
        strcpy(g_pointers->m_player_name_esp, Name);
        strcpy(g_pointers->m_player_name_display, Name);
    }

    void player::change_name(const std::string& name, rage::netPlayerData* data)
    {
        auto len = std::min(name.size(), (std::size_t)18);
        std::memcpy(data->m_name, name.data(), len);
        data->m_name[len] = '\0';
    }

    bool player::is_ped_shooting(Ped ped)
    {
        Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, 1);
        return PED::IS_PED_SHOOTING_IN_AREA(ped, coords.x, coords.y, coords.z, coords.x, coords.y, coords.z, true, true);
    }

    void spoofer::player_crew(char *Tag)
    {
        for (int i = 0; i <= 4; i++)
        {
            if (g_pointers->m_player_crew->get_active_crew(i))
            {
                strcpy(g_pointers->m_player_crew->get_crew_tag(i), Tag);
            }
        }
    }

    void spoofer::player_scid(uint64_t FakeRID)
    {
        auto original = *g_pointers->m_player_rid;
        if (g_local.transition)
        {
            rage_helper::get_local_playerinfo()->m_rockstar_id = original;
        }
        rage_helper::get_local_playerinfo()->m_rockstar_id = FakeRID;
    }

    void spoofer::player_level(bool activation, int level)
    {
        if (activation)
        {
            *script_global(g_global.player_stat).at(g_local.player, g_global.player_size).at(g_global.player_offset).at(6).as<int*>() = level;
        }
    }

    void spoofer::player_money(bool activation, int money)
    {
        if (activation)
        {
            *script_global(g_global.player_stat).at(g_local.player, g_global.player_size).at(g_global.player_offset).at(56).as<int*>() = money;
        }
    }

    void outfit::set_appearance(char* family, int model, int texture)
    {
        if (systems::cstrcmp(family, "HATS") || systems::cstrcmp(family, "GLASSES") || systems::cstrcmp(family, "EARS") || systems::cstrcmp(family, "WATCH") || systems::cstrcmp(family, "BRACELET"))
        {
            if (systems::cstrcmp(family, "HATS"))
                fam = 0;
            else if (systems::cstrcmp(family, "GLASSES"))
                fam = 1;
            else if (systems::cstrcmp(family, "EARS"))
                fam = 2;
            else  if (systems::cstrcmp(family, "WATCH"))
                fam = 6;
            else if (systems::cstrcmp(family, "BRACELET"))
                fam = 7;
            PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), fam, model - 1, texture, 1);
        }
        else
        {
            if (systems::cstrcmp(family, "FACE"))
                fam = 0;
            else if (systems::cstrcmp(family, "MASK"))
                fam = 1;
            else if (systems::cstrcmp(family, "HAIR"))
                fam = 2;
            else if (systems::cstrcmp(family, "JACKET"))
                fam = 3;
            else if (systems::cstrcmp(family, "LEGS"))
                fam = 4;
            else if (systems::cstrcmp(family, "BACK"))
                fam = 5;
            else if (systems::cstrcmp(family, "SHOES"))
                fam = 6;
            else if (systems::cstrcmp(family, "ACCESSORY"))
                fam = 7;
            else if (systems::cstrcmp(family, "UNDERSHIRT"))
                fam = 8;
            else if (systems::cstrcmp(family, "KEVLAR"))
                fam = 9;
            else if (systems::cstrcmp(family, "BADGE"))
                fam = 10;
            else if (systems::cstrcmp(family, "TORSO2"))
                fam = 11;
            PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), fam, model, texture, 0);
        }
    }

    void outfit::reset_appearance()
    {
        PED::CLEAR_ALL_PED_PROPS(PLAYER::PLAYER_PED_ID());
        PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
        PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, 0, 0, 0);
        PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, 0, 0, 0);
        PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, 0, 0, 0);
    }

    void outfit::steal_outfit(Player player)
    {
        Ped their_ped = player::get_player_ped(player);
        for (int i = 0; i < 12; i++)
        {
            PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, PED::GET_PED_DRAWABLE_VARIATION(their_ped, i),
                PED::GET_PED_TEXTURE_VARIATION(their_ped, i),
                PED::GET_PED_PALETTE_VARIATION(their_ped, i));
        }
    }

    void player::ultra_run(bool Activation)
    {
        if (Activation)
        {
            if (GetAsyncKeyState(0x57))
            {
                Vector3 offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_local.ped, 0, 0.6, 0);
                ENTITY::APPLY_FORCE_TO_ENTITY(g_local.ped, 1, 0.0f, 1.3, 0, 0.0f, 0.0f, 0.0f, 0, TRUE, TRUE, TRUE, FALSE, TRUE);
                PLAYER::SET_PLAYER_SPRINT(g_local.player, 1);
                rage_helper::get_local_playerinfo()->m_run_speed = 1.30f;
            }
        }
    }

    void player::give_all_heal(bool Activation)
    {
        if (Activation)
        {
            for (int i = 0; i <= network::network_get_num_connected_player(); i++)
            {
                Ped ped = get_player_ped(i);
                auto GetHealth = ENTITY::GET_ENTITY_HEALTH(ped);
                if (GetHealth >= 100 && GetHealth < 200)
                {
                    if (ped != g_local.ped && ped != 0)
                    {
                        object::create_pickup("PICKUP_HEALTH_STANDARD", "prop_ld_health_pack", 1, ped);
                        object::create_pickup("PICKUP_ARMOUR_STANDARD", "prop_ld_armour", 1, ped);
                    }
                }
            }
        }
    }

    void player::set_payer_level(int PlayerLevel)
    {
        g_fiber_pool->queue_job([PlayerLevel] {
            int SettingLevelPlayer = big::features::LevelData(PlayerLevel);
            const auto mpx = std::to_string(g_local.character);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_CHAR_SET_RP_GIFT_ADMIN"), *script_global(g_global.level_array).at(PlayerLevel, 1).as<int*>(), TRUE);
        });
    }

    int player::get_player_max_health(Player player)
    {
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            return systems::float_to_int(ped->m_max_health);
        }
        return 0;
    }

    int player::get_player_health(Player player)
    {
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            return systems::float_to_int(ped->m_health);
        }
        return 0;
    }

    int player::get_player_armour(Player player)
    {
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            return systems::float_to_int(ped->m_armor);
        }
        return 0;
    }

    int player::get_player_max_amour(Player player)
    {
        static int armour = 0;
        g_fiber_pool->queue_job([player] {
            armour = PLAYER::GET_PLAYER_MAX_ARMOUR(player);
        });
        return armour;
    }

    std::string player::get_player_local_ip(Player player)
    {
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            rage::netAddress player_ip = *(rage::netAddress*)&ped->m_playerinfo->m_external_ip;
            return fmt::format("{}.{}.{}.{}", player_ip.m_field1, player_ip.m_field2, player_ip.m_field3, player_ip.m_field4);
        }
        return fmt::format("{}.{}.{}.{}", 0, 0, 0, 0);
    }

    std::string player::get_player_ip(Player player)
    {
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            rage::netAddress player_ip = *(rage::netAddress*)&ped->m_playerinfo->m_online_ip;
            return fmt::format("{}.{}.{}.{}", player_ip.m_field1, player_ip.m_field2, player_ip.m_field3, player_ip.m_field4);
        }
        return fmt::format("{}.{}.{}.{}", 0, 0, 0, 0);
    }

    uint64_t player::get_player_scid(Player player)
    {
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            return ped->m_playerinfo->m_rockstar_id;
        }
        return 0;
    }

    int player::get_player_wanted_level(Player player)
    {
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            return ped->m_playerinfo->m_wanted_level;
        }
        return 0;
    }

    bool player::get_player_invincible(Player player)
    {
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            return ped->is_invincible();
        }
        return false;
    }

    bool player::get_player_waterproof(Player player)
    {
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            return ped->is_water_proof();
        }
        return false;
    }

    bool player::get_player_vehicle_invincible(Entity entity)
    {
        if (CVehicle* e = rage_helper::entity_to_pointer<CVehicle*>(entity))
        {
            return e->is_invincible();
        }
        return false;
    }

    uint32_t player::get_player_host_token(Player player)
    {
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            return ped->m_playerinfo->m_host_token;
        }
        return 0u;
    }

    uint32_t player::get_player_peer_id(Player player)
    {
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            return ped->m_playerinfo->m_peer_id;
        }
        return 0u;
    }

    std::string player::get_player_weapon(Player player)
    {
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            if (auto weapon = ped->m_weapon_mgr)
            {
                if (auto weapon_info = weapon->m_weapon_info)
                {
                    if (auto weapon_hash = weapon_info->m_weapon_hash)
                    {
                        return weapon_helper::get_weapon_name_from_hash(weapon_hash);
                    }
                }
            }
        }
        return weapon_helper::get_weapon_name_from_hash(0);
    }

    std::string player::get_player_vehicle_name(Player player)
    {
        static std::string name;
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            if (ped->m_is_in_vehicle)
            {
                if (auto vehicle = ped->m_last_vehicle)
                {
                    if (auto vehicle_info = vehicle->m_model_info)
                    {
                        QUEUE_JOB_BEGIN(=)
                        {
                            static auto hash = vehicle_info->m_model_hash;
                            if (hash != vehicle_info->m_model_hash || name.empty())
                            {
                                name = HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(vehicle_info->m_model_hash));
                                hash = vehicle_info->m_model_hash;
                            }
                        } QUEUE_JOB_END
                    }
                }
            }
            else
            {
                name = "Not in any vehicle";
            }
        }
        return name;
    }

    const char* player::get_player_name(Player player)
    {
        return g_pointers->m_get_player_name(player);
    }

    Vector3 player::get_player_coords(Player player)
    {
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            return systems::to_scr_vector(ped->m_navigation->m_position);
        }
        return Vector3(0.f, 0.f, 0.f);
    }

    bool player::get_player_infinite_clip(Player player)
    {
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            return ped->m_weapon_inventory->is_infinite_clip();
        }
        return false;
    }

    bool player::get_player_infinite_ammo(Player player)
    {
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            return ped->m_weapon_inventory->is_infinite_ammo();
        }
        return false;
    }

    bool player::is_player_out_of_radar(Player player)
    {
        return *script_global(g_global.radar_toggle).at(player, g_global.radar_size).at(209).as<bool*>();
    }

    Ped player::player_ped_id()
    {
        return rage_helper::pointer_to_entity(rage_helper::get_local_ped());
    }

    const char* player::get_player_organization_name(Player player)
    {
        auto pointer = g_global.get_organization_name(player).as<void*>();//script_global(1893548).at(player, 600).at(11).at(105).as<void*>();
        char* name = (char*)pointer;

        if (name != nullptr)
        {
            return name;
        }
        return " ";
    }

    void player::self_noclip(bool activate) 
    {
        Entity ent = PLAYER::PLAYER_PED_ID();
        bool bInVehicle = PED::IS_PED_IN_ANY_VEHICLE(ent, true);
        if (bInVehicle) ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

        // cleanup when changing entities
        if (prev != ent)
        {
            ENTITY::FREEZE_ENTITY_POSITION(prev, false);
            ENTITY::SET_ENTITY_COLLISION(prev, true, true);

            prev = ent;
        }

        if (activate)
        {
            for (int control : controls)
                PAD::DISABLE_CONTROL_ACTION(0, control, true);

            Vector3 cur_pos = ENTITY::GET_ENTITY_COORDS(ent, true);
            Vector3 vel = { 0.f, 0.f, 0.f };
            float heading = 0.f;

            // Left Shift
            if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 21))
                vel.z += speed / 2;
            // Left Control
            if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 36))
                vel.z -= speed / 2;
            // Forward
            if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 32))
                vel.y += speed;
            // Backward
            if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 33))
                vel.y -= speed;
            // Left
            if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 34))
                vel.x -= speed / 2;
            // Right
            if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 35))
                vel.x += speed / 2;

            rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
            ENTITY::SET_ENTITY_ROTATION(ent, 0.f, rot.y, rot.z, 2, 0);
            ENTITY::SET_ENTITY_COLLISION(ent, false, false);
            if (vel.x == 0.f && vel.y == 0.f && vel.z == 0.f)
            {
                // freeze entity to prevent drifting when standing still
                ENTITY::FREEZE_ENTITY_POSITION(ent, true);

                mult = 0.f;
            }
            else
            {
                if (mult < 20.f)
                    mult += 0.15f;

                ENTITY::FREEZE_ENTITY_POSITION(ent, false);

                Vector3 offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, vel.x, vel.y, 0.f);
                vel.x = offset.x - cur_pos.x;
                vel.y = offset.y - cur_pos.y;

                ENTITY::SET_ENTITY_VELOCITY(ent, vel.x * mult, vel.y * mult, vel.z * mult);
            }
        }
        else if (activate != bLastNoclip)
        {
            network::request_control(ent);
            ENTITY::FREEZE_ENTITY_POSITION(ent, false);
            ENTITY::SET_ENTITY_COLLISION(ent, true, false);
        }

        bLastNoclip = activate;
    }

    void player::fill_player_list()
    {
        if (player_list_open)
        {
            if ((network::network_get_num_connected_player() != g_misc_option->player_names.size()) && *g_pointers->m_is_session_started)
            {
                g_misc_option->player_names.clear();
                for (int i = 0; i < MAX_PLAYERS; i++)
                {
                    if (auto net_player = rage_helper::get_net_player(i))
                    {
                        auto cstr_name = net_player->get_name();
                        std::string name = cstr_name;
                        auto is_in_interior = INTERIOR::GET_INTERIOR_FROM_ENTITY(player::get_player_ped(i)) != 0;
                        transform(name.begin(), name.end(), name.begin(), ::tolower);
                        g_misc_option->player_names[name] = { cstr_name, i, is_in_interior };
                    }
                }
            }
            if (!*g_pointers->m_is_session_started)
            {
                if (g_misc_option->player_names.size() >= 1)
                    g_misc_option->player_names.clear();

                auto cstr_name = player::get_player_name(g_local.player);
                std::string name = cstr_name;
                auto is_in_interior = INTERIOR::GET_INTERIOR_FROM_ENTITY(player::get_player_ped(g_local.ped)) != 0;
                g_misc_option->player_names[cstr_name] = { cstr_name, g_local.player, is_in_interior };
            }
        }
    }

    void player::player_blackhole()
    {
        player::set_player_waterproof(g_local.player, g_player_option.waterproof);
        player::self_noclip(g_player_option.no_clip);
        player::ghost_organization(g_player_option.ghost_organizations);
        player::reveal_player(g_player_option.reveal_players);
        player::blind_cops(g_player_option.blinds_cops);
        player::ultra_run(g_player_option.ultra_run_bool);
        player::never_wanted(g_settings.options["Never Wanted"]);
        player::mission_lives(g_player_option.all_mission_lives);
        player::set_player_seatbelt(g_settings.options["Seatbelt"]);
        player::set_player_invincible(PLAYER::PLAYER_ID(), g_settings.options["Player Godmode"]);
        player::give_all_heal(g_player_option.send_heal);
        player::auto_heal(g_settings.options["Auto Heal"]);
        player::set_player_no_collision(g_player_option.pass_through_wall);
        player::no_idle_kick(g_settings.options["No Idle Kick"]);
        player::set_player_infinite_oxygen(PLAYER::PLAYER_ID(), g_player_option.is_infinite_oxygen);

        player::fill_player_list();
    }
}