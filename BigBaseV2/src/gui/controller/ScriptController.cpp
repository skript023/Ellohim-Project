#include "natives.hpp"
#include "common.hpp"
#include "gta_util.hpp"
#include "script_local.hpp"
#include "gta\VehicleValues.h"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include "features.hpp"
#include "ScriptController.h"
#include "gui/game_tabbar/player_list.h"
#include "gta/Weapons.h"
#include "gui/controller/game_variable.h"
#include "crossmap.hpp"
#include "gui/casino/casino.h"
#include "gui/controller/memory_address.hpp"
#include "gui/player/player_option.h"
#include "http_request.hpp"
#include "network_controller.h"

namespace big
{
    bool ScriptStatus;

    std::vector<uint64_t> get_player_network_handle(Player player) {
        const int size = 13;
        uint64_t* buffer = std::make_unique<uint64_t[]>(size).get();
        NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, reinterpret_cast<int*>(buffer), 13);
        for (int i = 0; i < size; i++)
        {
            LOG(INFO) << "network handle: " << i << " : " << buffer[i];
        }
        std::vector<uint64_t> result(buffer, buffer + sizeof(buffer));
        return result;
    }
    
    bool is_player_spectating(Player player)
    {
        const int handle_size = 76;
        int network_handle[handle_size];
        NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &network_handle[0], handle_size);
        if (NETWORK::NETWORK_IS_HANDLE_VALID(&network_handle[0], handle_size))
        {
            return NETWORK::NETWORK_IS_ACTIVITY_SPECTATOR_FROM_HANDLE(&network_handle[0]);
        }
        return false;
    }
    
    bool controller::cstrcmp(const char* s1, const char* s2)
    {
        while (*s1 && (*s1 == *s2))
            s1++, s2++;
        if (*(const unsigned char*)s1 - *(const unsigned char*)s2 == 0)
            return true;
        else
            return false;
    }

    Hash controller::load(const char* name)
    {
        Hash hash = rage::joaat(name);
        while (!STREAMING::HAS_MODEL_LOADED(hash))
        {
            STREAMING::REQUEST_MODEL(hash);
            script::get_current()->yield();
        }
        return hash;
    }

    Hash controller::load(Hash hash)
    {
        while (!STREAMING::HAS_MODEL_LOADED(hash))
        {
            STREAMING::REQUEST_MODEL(hash);
            script::get_current()->yield();
        }
        return hash;
    }

    void controller::ptfx_asset_load(const char* name)
    {
        while (!STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(name))
        {
            STREAMING::REQUEST_NAMED_PTFX_ASSET(name);
            script::get_current()->yield();
        }
    }

    const char* controller::load_anim(const char* anim)
    {
        while (!STREAMING::HAS_ANIM_DICT_LOADED(anim))
        {
            STREAMING::REQUEST_ANIM_DICT(anim);
            script::get_current()->yield();
        }
        return anim;
    }

    void controller::faster_time_scale(bool Activation)
    {
        if (Activation)
        {
            static int min = CLOCK::GET_CLOCK_MINUTES();
            static int hour = CLOCK::GET_CLOCK_HOURS();
            min += 1;
            if (min == 59)
            {
                hour += 1;
                min = 0;
            }
            if (hour == 23)
            {
                hour = 0;
            }

            if (*g_pointers->m_is_session_started)
            {
                NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(hour, min, CLOCK::GET_CLOCK_SECONDS());
            }
            else
            {
                CLOCK::SET_CLOCK_TIME(hour, min, CLOCK::GET_CLOCK_SECONDS());
            }
        }
    }

    void controller::TimeSpam(bool Activation)
    {
        if (Activation)
        {
            if (*g_pointers->m_is_session_started)
            {
                NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(12, CLOCK::GET_CLOCK_MINUTES(), CLOCK::GET_CLOCK_SECONDS());
                script::get_current()->yield(1s);
                NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(0, CLOCK::GET_CLOCK_MINUTES(), CLOCK::GET_CLOCK_SECONDS());
            }
            else
            {
                CLOCK::SET_CLOCK_TIME(12, CLOCK::GET_CLOCK_MINUTES(), CLOCK::GET_CLOCK_SECONDS());
                script::get_current()->yield(1s);
                CLOCK::SET_CLOCK_TIME(0, CLOCK::GET_CLOCK_MINUTES(), CLOCK::GET_CLOCK_SECONDS());
            }
        }
    }

    void controller::InvalidModelProtection(bool Activation)
    {
        if (Activation && !g_local.transition)
        {
            auto hash_table = *g_pointers->m_hash_table; hash_table->m_ped_hash_table->m_slod = rage::joaat("player_one");
            hash_table->m_ped_hash_table->m_slod_small = rage::joaat("player_one");
            hash_table->m_ped_hash_table->m_slod_large = rage::joaat("player_one");
        }
        else
        {
            auto hash_table = *g_pointers->m_hash_table; hash_table->m_ped_hash_table->m_slod = rage::joaat("slod_human");
            hash_table->m_ped_hash_table->m_slod_small = rage::joaat("slod_small_quadped");
            hash_table->m_ped_hash_table->m_slod_large = rage::joaat("slod_large_quadped");
        }
    }

    void controller::ShowMessage(const char* Message, bool InPauseMenu)
    {
        HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
        HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(Message);
        HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", FALSE, 0, "~bold~~g~Ellohim Private Menu", "~bold~~y~Ellohim Message");
        HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(true, InPauseMenu);
    }

    void controller::CheckInvalidPed()
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

            auto playerPosition = ENTITY::GET_ENTITY_COORDS(g_local.ped, TRUE);
            auto SpawnCoordinates = ENTITY::GET_ENTITY_COORDS(ped, TRUE);
            if (ENTITY::GET_ENTITY_MODEL(ped) == RAGE_JOAAT("slod_human") || ENTITY::GET_ENTITY_MODEL(ped) == RAGE_JOAAT("slod_small_quadped") || ENTITY::GET_ENTITY_MODEL(ped) == RAGE_JOAAT("slod_large_quadped"))
            {
                if (MISC::GET_DISTANCE_BETWEEN_COORDS(playerPosition.x, playerPosition.y, playerPosition.z, SpawnCoordinates.x, SpawnCoordinates.y, SpawnCoordinates.z, false) <= 250.0f)
                {
                    ENTITY::SET_ENTITY_COORDS(ped, 0, 0, -100, 0, 0, 0, 0);
                    NETWORK::NETWORK_FADE_OUT_ENTITY(ped, 0, 0);
                    ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ped, 0, 0);
                    ENTITY::DELETE_ENTITY(&ped);
                }
            }
        }
    }

    void controller::set_clipboard(const char* message)
    {
        HGLOBAL h;
        LPVOID p;
        int size;
        //calc the num of unicode char
        size = MultiByteToWideChar(CP_UTF8, NULL, message, -1, NULL, 0);
        if (!size) return;
        h = GlobalAlloc(GHND | GMEM_SHARE, size * 2);
        if (!h) return;
        p = GlobalLock(h);
        //utf8 to unicode
        MultiByteToWideChar(CP_UTF8, NULL, message, -1, (LPWSTR)p, size);
        GlobalUnlock(h);
        OpenClipboard(NULL);
        EmptyClipboard();
        SetClipboardData(CF_UNICODETEXT, h);
        CloseClipboard();
    }

    void controller::DumpEntryBoi()
    {
        std::string settings_file = std::getenv("appdata");
        settings_file += "\\Ellohim Menu\\EntryPoints.txt";

        std::ofstream file(settings_file, std::ios::out | std::ios::trunc);
        for (auto& map : g_crossmap)
        {
            auto address = g_pointers->m_get_native_handler(g_pointers->m_native_registration_table, map.second);

            file << std::hex << std::uppercase << "0x" << map.first << " : " << "0x" << address << std::endl;
        }

        file.close();
    }

    void controller::get_player_info_from_ip(Player player)
    {
        if (!network::check_network_status()) return;
        http_response_tick = std::chrono::high_resolution_clock::now();
        if ((std::chrono::high_resolution_clock::now() - http_response_tick).count() >= std::chrono::milliseconds(3000ms).count() || trigger_player_info_from_ip)
        {
            try
            {
                trigger_player_info_from_ip = false;
                if (strcmp(player::get_player_ip(player).c_str(), "0.0.0.0") != 0)
                {
                    http::Request request{ fmt::format("http://ip-api.com/json/{}?fields=66318335", player::get_player_ip(player)) };

                    const auto response = request.send("GET", "", {}, std::chrono::milliseconds(500));
                    auto result = nlohmann::json::parse(response.body.begin(), response.body.end());
                    provider = result["isp"].get<std::string>();
                    country = result["country"].get<std::string>();
                    city = result["city"].get<std::string>();
                    region = result["regionName"].get<std::string>();
                    zip = result["zip"].get<std::string>();
                    proxy = result["proxy"].get<bool>();
                }
            }
            catch (const std::exception& e)
            {
                trigger_player_info_from_ip = false;
                LOG(HACKER) << "Request failed, error: " << e.what();
            }
            http_response_tick = std::chrono::high_resolution_clock::now();
        }
    }

    void controller::variable_attach()
    {
        if (g_local.player != PLAYER::PLAYER_ID() || g_local.ped != PLAYER::PLAYER_PED_ID())
        {
            g_local.player = PLAYER::PLAYER_ID();
            g_local.ped = PLAYER::PLAYER_PED_ID();
        }
        g_event_tester.event_ped = player::get_player_ped(g_event_tester.event_player);
        g_local.InVehicle = PED::IS_PED_IN_ANY_VEHICLE(g_local.ped, FALSE);
        g_local.PlayerVehicle = PED::GET_VEHICLE_PED_IS_USING(g_local.ped);
        g_local.vehicle_net_id = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(g_local.PlayerVehicle);
        g_selected.ped = player::get_player_ped(g_selected.player);
        g_local.is_cutscene_playing = CUTSCENE::IS_CUTSCENE_PLAYING();
        g_local.is_activity_session = NETWORK::NETWORK_IS_ACTIVITY_SESSION();


        g_local.ScriptHost = NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0);
        g_local.character = *script_global(1574907).as<int*>();
        g_local.connected_player = NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS();
        g_local.mission = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller"));
        g_local.arcade = rage_helper::find_script_thread(RAGE_JOAAT("gb_casino_heist_planning"));
        g_local.mission_2020 = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020"));
        g_mission.mission_controller = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller")) != nullptr;
        g_mission.mission_controller_new = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")) != nullptr;
        g_mission.casino_board = rage_helper::find_script_thread(RAGE_JOAAT("gb_casino_heist_planning")) != nullptr;
        g_mission.cayo_board = rage_helper::find_script_thread(RAGE_JOAAT("heist_island_planning")) != nullptr;
        g_mission.doomsday_board = rage_helper::find_script_thread(RAGE_JOAAT("gb_gang_ops_planning")) != nullptr;
        g_mission.apartment_board = rage_helper::find_script_thread(RAGE_JOAAT("fmmc_launcher")) != nullptr;
        g_local.script_transition = features::TransitionCheck() && *g_pointers->m_is_session_started;
        g_global.vision = g_global.player_stat + 1 + g_local.player * g_global.player_size + 848 + 9 + 1; //h4_islandx_disc_StrandedWhale
        g_global.business_index = g_global.player_stat + 1 + (g_local.player * g_global.player_size) + 267 + 187;
        m_local.blackjack.current_table = 1788 + 1 + (g_local.player * 8) + 4;
        m_local.blackjack.bet_trigger = 1788 + 1 + (g_local.player * 8);

        g_ptr.WorldPTR = (uintptr_t)g_pointers->m_ped_factory;

        g_info.player_health = ENTITY::GET_ENTITY_HEALTH(g_selected.ped);
        g_info.player_max_health = ENTITY::GET_ENTITY_MAX_HEALTH(g_selected.ped);
        g_info.player_armour = PED::GET_PED_ARMOUR(g_selected.ped);
        g_info.player_max_armour = PLAYER::GET_PLAYER_MAX_ARMOUR(g_selected.player);
        g_info.PlayerPosition = ENTITY::GET_ENTITY_COORDS(g_selected.ped, FALSE);
        g_info.PlayerZone = HUD::_GET_LABEL_TEXT(ZONE::GET_NAME_OF_ZONE(g_info.PlayerPosition.x, g_info.PlayerPosition.y, g_info.PlayerPosition.z));
        PATHFIND::GET_STREET_NAME_AT_COORD(g_info.PlayerPosition.x, g_info.PlayerPosition.y, g_info.PlayerPosition.z, &g_info.StreetNameHash, &g_info.CrossingRoadHash);
        g_info.PlayerStreet = HUD::GET_STREET_NAME_FROM_HASH_KEY(g_info.StreetNameHash);
    }
}
