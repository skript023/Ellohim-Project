#include "natives.hpp"
#include "common.hpp"
#include "gta_util.hpp"
#include "script_local.hpp"
#include "gta\VehicleValues.h"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include "features.hpp"
#include "blackhole_helper.hpp"
#include "gui/game_tabbar/player_list.h"
#include "gta/Weapons.h"
#include "gui/controller/game_variable.h"
#include "gui/casino/casino.h"
#include "gui/controller/memory_address.hpp"
#include "gui/player/player_option.h"
#include "http_request.hpp"
#include "network_controller.h"
#include "crossmap.hpp"

namespace big
{
    bool ScriptStatus;

    std::vector<uint64_t> get_player_network_handle(Player player) 
    {
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

    void miscellaneous::dump_entry_point()
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

    void miscellaneous::chrono_player_info_blackhole(std::chrono::milliseconds ms)
    {
        static auto start = std::chrono::high_resolution_clock::now();
        if ((start - std::chrono::high_resolution_clock::now()).count() >= ms.count() || trigger_player_info_from_ip)
        {
            
            start = std::chrono::high_resolution_clock::now();
        }
    }

    void miscellaneous::get_player_info_from_ip(Player player)
    {
        if (!network::check_network_status()) return;
        http_response_tick = std::chrono::high_resolution_clock::now();
        if ((std::chrono::high_resolution_clock::now() - http_response_tick).count() >= std::chrono::milliseconds(10000).count() || trigger_player_info_from_ip)
        {
            THREAD_JOB_BEGIN_CLAUSE(=)
            {
                try
                {
                    trigger_player_info_from_ip = false;
                    if (strcmp(player::get_player_ip(player).c_str(), "0.0.0.0") != 0)
                    {
                        http::Request request{ fmt::format("http://ip-api.com/json/{}?fields=66318335", player::get_player_ip(player)) };

                        const auto response = request.send("GET", "", {}, 1000ms);
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
            } THREAD_JOB_END_CLAUSE
        }
    }

    void miscellaneous::variable_attach()
    {
        if (g_local.player != PLAYER::PLAYER_ID() || g_local.ped != PLAYER::PLAYER_PED_ID())
        {
            g_local.player = PLAYER::PLAYER_ID();
            g_local.ped = PLAYER::PLAYER_PED_ID();
        }

        chrono_player_info_blackhole(2000ms);

        g_event_tester.event_ped = player::get_player_ped(g_event_tester.event_player);
        g_local.PlayerVehicle = PED::GET_VEHICLE_PED_IS_USING(g_local.ped);
        g_local.vehicle_net_id = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(g_local.PlayerVehicle);
        g_selected.ped = player::get_player_ped(g_selected.player);
        g_local.is_cutscene_playing = CUTSCENE::IS_CUTSCENE_PLAYING();
        g_local.is_activity_session = NETWORK::NETWORK_IS_ACTIVITY_SESSION();
            

        g_local.ScriptHost = NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0);
        g_local.character = *script_global(1574907).as<int*>();
        g_local.connected_player = NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS();
        
        g_global.vision = g_global.player_stat + 1 + g_local.player * g_global.player_size + 848 + 9 + 1; //h4_islandx_disc_StrandedWhale
        g_global.business_index = g_global.player_stat + 1 + (g_local.player * g_global.player_size) + 267 + 187;
        m_local.blackjack.current_table = 1788 + 1 + (g_local.player * 8) + 4;
        m_local.blackjack.bet_trigger = 1788 + 1 + (g_local.player * 8);

        g_info.player_health = ENTITY::GET_ENTITY_HEALTH(g_selected.ped);
        g_info.player_max_health = ENTITY::GET_ENTITY_MAX_HEALTH(g_selected.ped);
        g_info.player_armour = PED::GET_PED_ARMOUR(g_selected.ped);
        g_info.player_max_armour = PLAYER::GET_PLAYER_MAX_ARMOUR(g_selected.player);
        g_info.PlayerPosition = ENTITY::GET_ENTITY_COORDS(g_selected.ped, FALSE);
        
        PATHFIND::GET_STREET_NAME_AT_COORD(g_info.PlayerPosition.x, g_info.PlayerPosition.y, g_info.PlayerPosition.z, &g_info.StreetNameHash, &g_info.CrossingRoadHash);
        g_info.PlayerStreet = HUD::GET_STREET_NAME_FROM_HASH_KEY(g_info.StreetNameHash);

        if (g_player_option.player_list_open && g_player_option.player_info_open)
            g_info.PlayerZone = HUD::_GET_LABEL_TEXT(ZONE::GET_NAME_OF_ZONE(g_info.PlayerPosition.x, g_info.PlayerPosition.y, g_info.PlayerPosition.z));
    }
}
