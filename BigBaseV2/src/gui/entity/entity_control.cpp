#include "natives.hpp"
#include "common.hpp"
#include "gta_util.hpp"
#include "script_local.hpp"
#include "gta/VehicleValues.h"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include "features.hpp"
#include "gui/controller/ScriptController.h"
#include "gui/player_list.h"
#include "gta/Weapons.h"
#include "gui/controller/game_variable.h"
#include "gui/player/player_option.h"
#include "gui/object/object.h"
#include "gui/controller/memory_address.hpp"
#include "gui/controller/system_control.h"
#include "gta/net_object_mgr.hpp"
#include "gui/weapons/weapon_helper.h"
#include "gui/vehicle/vehicle_helper.h"
#include "gui/entity/entity_control.h"

namespace big
{
	Vector3 entity::get_entity_coords(Entity entity, bool Alive)
	{
		if (auto ent = rage_helper::entity_to_pointer<CPed*>(entity))
		{
			if (Alive)
			{
				if (!systems::is_float_equal(ent->m_health, 0.0f))
				{
					return systems::to_scr_vector(ent->m_navigation->m_position);
				}
			}
			else if (!Alive)
			{
				return systems::to_scr_vector(ent->m_navigation->m_position);
			}
		}
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	int entity::get_entity_health(Entity entity)
	{
		if (auto ent = rage_helper::entity_to_pointer<CPed*>(entity))
		{
			return systems::float_to_int(ent->m_health);
		}
		return 0;
	}

	int entity::get_entity_max_health(Entity entity)
	{
		if (auto ent = rage_helper::entity_to_pointer<CPed*>(entity))
		{
			return systems::float_to_int(ent->m_max_health);
		}
		return 0;
	}

	bool entity::get_entity_invincible(Entity entity)
	{
		if (auto ent = rage_helper::entity_to_pointer<CPed*>(entity))
		{
			return ent->is_invincible();
		}
		return false;
	}

	Hash entity::get_entity_model(Entity entity)
	{
		if (auto ent = rage_helper::entity_to_pointer<CPed*>(entity))
		{
			return ent->m_model_info->m_model_hash;
		}
		return 0;
	}

    Ped ped::clone_ped(Ped ped)
    {
        if (ENTITY::DOES_ENTITY_EXIST(ped) && !ENTITY::IS_ENTITY_DEAD(ped, FALSE))
        {
            return PED::CLONE_PED(ped, ENTITY::GET_ENTITY_HEADING(ped), TRUE, FALSE);
        }
        return 0;
    }

    void ped::create_ped(Hash PedHash, Vector3 SpawnCoordinates, int ped_type, bool network_handle)
    {
        QUEUE_JOB_BEGIN_CLAUSE(PedHash, SpawnCoordinates, ped_type, network_handle)
        {
            Ped NewPed;
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
                    NewPed = PED::CREATE_PED(ped_type, PedHash, SpawnCoordinates.x, SpawnCoordinates.y, SpawnCoordinates.z, 0, network_handle, 1);
                    *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
                    if (*g_pointers->m_is_session_started)
                    {
                        ENTITY::_SET_ENTITY_SOMETHING(NewPed, TRUE); //True means it can be deleted by the engine when switching lobbies/missions/etc, false means the script is expected to clean it up.
                        auto networkId = NETWORK::PED_TO_NET(NewPed);
                        if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(NewPed))
                            NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
                    }
                    //ENTITY::ATTACH_ENTITY_TO_ENTITY(NewPed, g_selected.ped, SKEL_Spine0, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, FALSE, FALSE, FALSE, TRUE, 2, TRUE);

                    if (big::player_list::IsVisible)
                    {
                        ENTITY::SET_ENTITY_VISIBLE(NewPed, FALSE, FALSE);
                    }
                    else if (!big::player_list::IsVisible)
                    {
                        ENTITY::SET_ENTITY_VISIBLE(NewPed, TRUE, FALSE);
                    }
                    if (big::player_list::AggressivePed)
                    {
                        PED::SET_PED_CAN_SWITCH_WEAPON(NewPed, true);
                        WEAPON::GIVE_DELAYED_WEAPON_TO_PED(NewPed, RAGE_JOAAT("WEAPON_MINIGUN"), 9999, TRUE);

                        PED::REGISTER_TARGET(NewPed, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selected.player));
                        TASK::TASK_COMBAT_PED(NewPed, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selected.player), 0, 1);
                        PED::SET_PED_AS_COP(NewPed, TRUE);
                    }
                    if (big::player_list::AsBodyGuard)
                    {
                        Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selected.player);
                        int my_group = PLAYER::GET_PLAYER_GROUP(selectedplayer);
                        PED::SET_PED_AS_GROUP_LEADER(selectedplayer, my_group);
                        PED::SET_PED_AS_GROUP_MEMBER(NewPed, my_group);
                        PED::SET_PED_NEVER_LEAVES_GROUP(NewPed, my_group);
                        ENTITY::SET_ENTITY_INVINCIBLE(NewPed, FALSE);
                        WEAPON::GIVE_WEAPON_TO_PED(NewPed, WEAPON_COMBATMG, 9999, FALSE, TRUE);
                        PED::SET_PED_CAN_SWITCH_WEAPON(NewPed, TRUE);
                        PED::SET_GROUP_FORMATION(my_group, 3);
                        PED::SET_PED_MAX_HEALTH(NewPed, 5000);
                        PED::SET_PED_COMBAT_ABILITY(NewPed, 100);
                    }
                    STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PedHash);
                }
            }
        }
        QUEUE_JOB_END_CLAUSE
    }

    void ped::attach_ped(Hash PedHash, Ped Target)
    {
        QUEUE_JOB_BEGIN_CLAUSE(PedHash, Target)
        {
            STREAMING::REQUEST_MODEL(PedHash);
            while (!STREAMING::HAS_MODEL_LOADED(PedHash))
            {
                script::get_current()->yield();
            }

            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
            Ped NewPed = PED::CREATE_PED(2, PedHash, 0.0f, 0.0f, 0.0f, 0, TRUE, FALSE);
            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
            if (*g_pointers->m_is_session_started)
            {
                ENTITY::_SET_ENTITY_SOMETHING(NewPed, TRUE); //True means it can be deleted by the engine when switching lobbies/missions/etc, false means the script is expected to clean it up.
                auto networkId = NETWORK::PED_TO_NET(NewPed);
                if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(NewPed))
                    NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
            }
            ENTITY::ATTACH_ENTITY_TO_ENTITY(NewPed, Target, SKEL_Spine0, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, FALSE, FALSE, FALSE, TRUE, 2, TRUE);

        } QUEUE_JOB_END_CLAUSE
    }
}