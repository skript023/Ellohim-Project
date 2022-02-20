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
#include <gui\game_tabbar\player_list.h>
#include <gta\Weapons.h>
#include <gui/controller/game_variable.h>
#include <gui/artificial_intelligence/artificial_intelligence.h>
#include <gui/controller/network_controller.h>
#include <gui/player/player_option.h>

namespace big
{
    void ai::kill_enemies(bool Activation)
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

                if (ped == PLAYER::PLAYER_PED_ID() || ENTITY::GET_ENTITY_HEALTH(ped) == 328 || PED::IS_PED_A_PLAYER(ped))
                    continue;

                if (ENTITY::GET_ENTITY_HEALTH(ped) != 328 || !PED::IS_PED_A_PLAYER(ped))
                {
                    if (player::get_ped_type(ped) != PED_TYPE_MISSION && player::is_ped_enemy(ped))
                    {
                        network::request_control(ped);
                        ENTITY::SET_ENTITY_HEALTH(ped, 0, 0);
                    }
                }
            }
        }
    }

    void ai::kill_all_npc(bool Activation)
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

                if (ped == PLAYER::PLAYER_PED_ID() || ENTITY::GET_ENTITY_HEALTH(ped) == 328 || PED::IS_PED_A_PLAYER(ped))
                    continue;

                if (ENTITY::GET_ENTITY_HEALTH(ped) != 328 || !PED::IS_PED_A_PLAYER(ped))
                {
                    network::request_control(ped);
                    ENTITY::SET_ENTITY_HEALTH(ped, 0, 0);
                }
            }
        }
    }

    void ai::explode_all_npc(bool Activation)
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

                if (ped == PLAYER::PLAYER_PED_ID() || ENTITY::GET_ENTITY_HEALTH(ped) == 328 || PED::IS_PED_A_PLAYER(ped) == TRUE)
                    continue;

                if (ENTITY::GET_ENTITY_HEALTH(ped) != 328 || PED::IS_PED_A_PLAYER(ped) == FALSE)
                {
                    auto pos = ENTITY::GET_ENTITY_COORDS(ped, TRUE);
                    FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, EXPLOSION_GRENADELAUNCHER, 1000.0f, FALSE, TRUE, 0.0f, FALSE);
                }
            }
        }
    }

    void ai::explode_enemies(bool Activation)
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

                if (ped == PLAYER::PLAYER_PED_ID() || ENTITY::GET_ENTITY_HEALTH(ped) == 328 || PED::IS_PED_A_PLAYER(ped) == TRUE)
                    continue;

                if (ENTITY::GET_ENTITY_HEALTH(ped) != 328 || !PED::IS_PED_A_PLAYER(ped) == FALSE)
                {
                    if (player::get_ped_type(ped) != PED_TYPE_MISSION && player::is_ped_enemy(ped))
                    {
                        if (!ENTITY::IS_ENTITY_DEAD(ped, TRUE))
                        {
                            auto pos = ENTITY::GET_ENTITY_COORDS(ped, TRUE);
                            FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, EXPLOSION_GRENADELAUNCHER, 1000.0f, FALSE, TRUE, 0.0f, FALSE);
                        }
                    }
                }
            }
        }
    }

    void message::notification(const char* Message, const char* MessageTag)
    {
        HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
        HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(Message);
        HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", FALSE, 0, MOD_NAME, MessageTag);
        HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(true, true);
    }

    void message::notification(const char* message)
    {
        HUD::SET_TEXT_OUTLINE();
        HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
        HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(message);
        HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, false);
    }

    void ai::Convoy(const char* vehicle, int max)
    {
        QUEUE_JOB_BEGIN_CLAUSE(vehicle, max)
        {
            for (int z = 0; z <= max; z++)
            {
                int WaypointHandle = HUD::GET_FIRST_BLIP_INFO_ID(8);
                if (HUD::DOES_BLIP_EXIST(WaypointHandle))
                {
                    Vector3 waypoint1 = HUD::GET_BLIP_COORDS(WaypointHandle);
                    Hash vehicle_hash = controller::load(vehicle);
                    Vector3 pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0);

                    *(unsigned short*)big::g_pointers->m_model_spawn_bypass = 0x9090;
                    Vehicle veh = VEHICLE::CREATE_VEHICLE(vehicle_hash, pos.x, pos.y, pos.z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), TRUE, FALSE, FALSE);
                    *(unsigned short*)big::g_pointers->m_model_spawn_bypass = 0x0574;

                    while (veh == 0)
                    {
                        script::get_current()->yield();
                    }

                    Ped Driver = PED::CREATE_RANDOM_PED_AS_DRIVER(veh, false);
                    PED::SET_PED_INTO_VEHICLE(Driver, veh, -1);
                    PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, 3);
                    TASK::TASK_VEHICLE_DRIVE_TO_COORD(Driver, veh, waypoint1.x, waypoint1.y, waypoint1.z, 40, 1, ENTITY::GET_ENTITY_MODEL(veh), 7, 6, -1);
                        
                    VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
                    for (int i = 0; i < 50; i++)
                    {
                        VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, false);
                    }

                    VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, "Ellohim Convoy");
                    controller::ShowMessage("~HUD_COLOUR_GREEN~ Convoy spawned!", true);
                }
            }
        } QUEUE_JOB_END_CLAUSE
    }
}