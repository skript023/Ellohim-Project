#include "natives.hpp"
#include "common.hpp"
#include "gta_util.hpp"
#include "script_local.hpp"
#include "gta\VehicleValues.h"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include "features.hpp"
#include <gta\Weapons.h>
#include <gui/controller/game_variable.h>
#include <gui/teleport/teleport.h>
#include "gui/controller/memory_address.hpp"
#include "gui/controller/network_controller.h"
#include "gui/controller/system_control.h"
#include "gui/player/player_option.h"

namespace big
{
    Vector3 blip::get_blip_coords(int icon_id, int icon_colour)
    {
        if (rage::BlipList* blip_ptr = g_pointers->m_blip_ptr)
        {
            for (int i = 0; i <= 1492; i++)
            {
                auto blip_list = blip_ptr->m_blips[i].m_blip_entry;
                if (blip_list)
                {
                    int blip_id = blip_list->m_icon;
                    int blip_colour = blip_list->m_color;

                    if (icon_colour == 0)
                        if (blip_id == icon_id)
                            return systems::to_scr_vector(blip_list->blip_coords);

                    if ((blip_id == icon_id) && (blip_colour == icon_colour))
                        return systems::to_scr_vector(blip_list->blip_coords);
                }
            }
        }
        return Vector3(0.0f , 0.0f, 0.0f);
    }

    bool teleport::load_ground(Vector3& coords)
    {
        float ground;
        if (!first_attempt)
        {
            for (int i = 0; i < 20; ++i)
            {
                for (float z = 0.f; z <= 1000.f; z += 100.f)
                {
                    STREAMING::REQUEST_COLLISION_AT_COORD(coords.x, coords.y, z);

                    script::get_current()->yield();
                }

                if (MISC::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, 1000.f, &ground, false, false))
                {
                    coords.z = ground + 2.f;

                    return true;
                }

                script::get_current()->yield();
            }
            first_attempt = true;
        }
        else if (first_attempt)
        {
            for (int i = 0; i < 10; ++i)
            {
                for (float z = 0.f; z <= 1000.f; z += 100.f)
                {
                    STREAMING::REQUEST_COLLISION_AT_COORD(coords.x, coords.y, z);

                    script::get_current()->yield();
                }

                if (MISC::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, 1000.f, &ground, false, false))
                {
                    coords.z = ground + 2.f;

                    return true;
                }

                script::get_current()->yield();
            }
        }

        return false;
    }

    void teleport::teleport_to_coords(Entity e, Vector3 coords) {
        g_fiber_pool->queue_job([=] {
            ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, coords.z, FALSE, FALSE, FALSE);
        });
    }

    Vector3 teleport::get_blip_marker()
    {
        static Vector3 zero;
        Vector3 coords;

        bool blipFound = false;
        // search for marker blip
        int blipIterator = HUD::_GET_WAYPOINT_BLIP_SPRITE();
        for (Blip i = HUD::GET_FIRST_BLIP_INFO_ID(blipIterator); HUD::DOES_BLIP_EXIST(i) != 0; i = HUD::GET_NEXT_BLIP_INFO_ID(blipIterator))
        {
            if (HUD::GET_BLIP_INFO_ID_TYPE(i) == 4)
            {
                coords = HUD::GET_BLIP_INFO_ID_COORD(i);
                blipFound = true;
                break;
            }
        }
        if (blipFound)
        {
            return coords;
        }
        return zero;
    }

    Vector3 teleport::get_mission_blip()
    {
        static Vector3 zero;
        Vector3 coords, oldCoords;
        auto e = rage_helper::get_local_ped()->m_is_in_vehicle ? g_local.PlayerVehicle : g_local.ped;

        bool blipFound = false;
        if (!blipFound)
        {
            for (Blip i = HUD::GET_FIRST_BLIP_INFO_ID(Circle); HUD::DOES_BLIP_EXIST(i) != 0; i = HUD::GET_NEXT_BLIP_INFO_ID(Circle))
            {
                if (HUD::GET_BLIP_COLOUR(i) == YellowMission || HUD::GET_BLIP_COLOUR(i) == Mission || HUD::GET_BLIP_COLOUR(i) == YellowMission2 || HUD::GET_BLIP_COLOUR(i) == Blue)
                {
                    coords = HUD::GET_BLIP_COORDS(i);
                    blipFound = true;
                    oldCoords = ENTITY::GET_ENTITY_COORDS(e, FALSE);
                    break;
                }
            }
            if (blipFound)
            {
                return coords;
            }
        }
        else
        {
            coords = oldCoords;
            return coords;
        }
        return zero;
    }

    void teleport::teleport_to_marker(Player player)
    {
        g_fiber_pool->queue_job([player]
        {
            auto coords = systems::to_scr_vector(*g_pointers->m_waypoint_coords);//blip::get_blip_coords(Waypoint, WaypointColor);

            if (systems::is_3d_vector_zero(coords))
                return;

            load_ground(coords);

            auto e = player::is_player_in_any_vehicle(player) ? player::get_player_vehicle(player::get_player_ped(player), true) : player::get_player_ped(player);

            if (player::is_player_in_any_vehicle(player))
            {
                *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                network::request_control(e);
                *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;
            }

            teleport_to_coords(e, coords);
        });
    }

    void teleport::teleport_to_objective(Player player)
    {
        g_fiber_pool->queue_job([player]
        {
            Vector3 coords = get_mission_blip();

            if (systems::is_3d_vector_zero(coords))
                return;

            auto e = player::is_player_in_any_vehicle(player) ? player::get_player_vehicle(player::get_player_ped(player), true) : player::get_player_ped(player);

            if (player::is_player_in_any_vehicle(player))
            {
                *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
                network::request_control(e);
                *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;
            }

            script::get_current()->yield();
            teleport_to_coords(e, coords);
        });
    }

    void teleport::teleport_to_player(Player source_player, Player target_player)
    {
        auto pos = player::get_player_coords(target_player);
        auto e = player::is_player_in_any_vehicle(source_player) ? player::get_player_vehicle(player::get_player_ped(source_player), false) : player::get_player_ped(source_player);
        if (ENTITY::IS_ENTITY_A_VEHICLE(e))
        {
            *(unsigned short*)g_pointers->m_request_control_bypass = 0x9090;
            network::request_control(e);
            *(unsigned short*)g_pointers->m_request_control_bypass = 0x6A75;
        }
        ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, pos.x, pos.y + 1.5f, pos.z, FALSE, FALSE, FALSE);
    }

    void teleport::teleport_to_player_vehicle(Player player)
    {
        auto ped = player::get_player_ped(player);
        if (player::is_player_in_any_vehicle(player))
        {
            Vehicle targetveh = player::get_player_vehicle(ped, false);
            int seats{};
            for (int p = 0; p < VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(targetveh); p++)
            {
                if (VEHICLE::IS_VEHICLE_SEAT_FREE(targetveh, p, FALSE))
                {
                    seats = p;
                }
            }
            PED::SET_PED_INTO_VEHICLE(g_local.ped, targetveh, seats);
        }
        else
        {
            auto pos = player::get_player_coords(player);
            ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_local.ped, pos.x, pos.y, pos.z + 1.5f, FALSE, FALSE, FALSE);
        }
    }
}