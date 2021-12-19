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
#include "crossmap.hpp"
#include "gui/casino/casino.h"
#include "object.h"
#include "gta/net_object_mgr.hpp"
#include "gui/sync_hash.hpp"

namespace big
{
    bool object::is_object_model_valid(rage::netSyncTree* netSyncTree, rage::netObject* netObject)
    {
        auto Hash = netSyncTree->m_sync_tree_node->m_player_model;
        auto object_type = netObject->object_type;
        for (auto obj : sync_object)
        {
            if (Hash == rage::joaat(obj) && object_type == NetObjEntityType_Object)
                return true;
        }
        return false;
    }

    std::string object::get_object_name_from_hash(Hash hash)
    {
        std::string sVar0 = std::to_string(hash);
        for (auto obj : sync_object)
        {
            if (rage::joaat(obj) == hash)
            {
                sVar0 = rage::joaat_to_string(obj, hash);
            }
        }
        return sVar0;
    }

    void object::spawn_object(const char* name, Entity entity)
    {
        QUEUE_JOB_BEGIN_CLAUSE(name, entity)
        {
            auto pos = ENTITY::GET_ENTITY_COORDS(entity, TRUE);
            auto forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity);
            auto heading = ENTITY::GET_ENTITY_HEADING(entity);

            pos.x += big::player_list::DISTANCE_SPAWN * forward.x;
            pos.y += big::player_list::DISTANCE_SPAWN * forward.y;

            MISC::GET_GROUND_Z_FOR_3D_COORD(pos.x, pos.y, pos.z, &pos.z, FALSE, FALSE);

            Hash hash_object = controller::load(name);
            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
            auto obj = OBJECT::CREATE_OBJECT(hash_object, pos.x, pos.y, pos.z, TRUE, TRUE, TRUE);
            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

            script::get_current()->yield();
            if (*g_pointers->m_is_session_started)
            {
                ENTITY::_SET_ENTITY_SOMETHING(obj, TRUE); //True means it can be deleted by the engine when switching lobbies/missions/etc, false means the script is expected to clean it up.
                auto networkId = NETWORK::OBJ_TO_NET(obj);
                if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(obj))
                    NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
            }
            ENTITY::SET_ENTITY_COLLISION(obj, TRUE, TRUE);
            if (big::player_list::ApplyForce)
            {
                ENTITY::APPLY_FORCE_TO_ENTITY(obj, 1, 150.0f, 180.0f, 200.0f, 20.0f, 20.0f, 50.0f, 0, FALSE, TRUE, TRUE, FALSE, TRUE);
            }
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash_object);

            //ENTITY::SET_ENTITY_INVINCIBLE(obj, TRUE);
            //ENTITY::SET_ENTITY_CAN_BE_DAMAGED(obj, FALSE);
        }
        QUEUE_JOB_END_CLAUSE
    }

    void object::spawn_object(Hash hash, Entity entity)
    {
        QUEUE_JOB_BEGIN_CLAUSE(hash, entity)
        {
            auto pos = ENTITY::GET_ENTITY_COORDS(entity, TRUE);
            auto forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity);
            auto heading = ENTITY::GET_ENTITY_HEADING(entity);

            pos.x += big::player_list::DISTANCE_SPAWN * forward.x;
            pos.y += big::player_list::DISTANCE_SPAWN * forward.y;

            MISC::GET_GROUND_Z_FOR_3D_COORD(pos.x, pos.y, pos.z, &pos.z, FALSE, FALSE);

            Hash hash_object = controller::load(hash);
            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
            auto obj = OBJECT::CREATE_OBJECT(hash_object, pos.x, pos.y, pos.z, TRUE, TRUE, TRUE);
            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

            script::get_current()->yield();
            if (*g_pointers->m_is_session_started)
            {
                ENTITY::_SET_ENTITY_SOMETHING(obj, TRUE); //True means it can be deleted by the engine when switching lobbies/missions/etc, false means the script is expected to clean it up.
                auto networkId = NETWORK::OBJ_TO_NET(obj);
                if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(obj))
                    NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
            }
            ENTITY::SET_ENTITY_COLLISION(obj, TRUE, TRUE);
            if (big::player_list::ApplyForce)
            {
                ENTITY::APPLY_FORCE_TO_ENTITY(obj, 1, 150.0f, 180.0f, 200.0f, 20.0f, 20.0f, 50.0f, 0, FALSE, TRUE, TRUE, FALSE, TRUE);
            }
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash_object);

            //ENTITY::SET_ENTITY_INVINCIBLE(obj, TRUE);
            //ENTITY::SET_ENTITY_CAN_BE_DAMAGED(obj, FALSE);
        }
        QUEUE_JOB_END_CLAUSE
    }

    void object::CreatePickup(const char* pickup, const char* prop, int amount, Entity entity)
    {
        QUEUE_JOB_BEGIN_CLAUSE(pickup, prop, amount, entity)
        {
            auto pos = ENTITY::GET_ENTITY_COORDS(entity, TRUE);
            auto forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity);
            auto heading = ENTITY::GET_ENTITY_HEADING(entity);

            pos.z += 1.2f;

            Hash pickup_hash = rage::joaat(pickup);
            Hash hash_prop = controller::load(prop);
            auto pickup = OBJECT::CREATE_AMBIENT_PICKUP(pickup_hash, pos.x, pos.y, pos.z, 0, amount, hash_prop, FALSE, TRUE);

            script::get_current()->yield();
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash_prop);
        }
        QUEUE_JOB_END_CLAUSE
    }

    void object::AttacthObject(const char* name, Entity entity)
    {
        QUEUE_JOB_BEGIN_CLAUSE(name, entity)
        {
            auto pos = ENTITY::GET_ENTITY_COORDS(entity, TRUE);
            auto forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity);
            auto heading = ENTITY::GET_ENTITY_HEADING(entity);

            Hash hash_object = controller::load(name);
            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
            auto obj = OBJECT::CREATE_OBJECT(hash_object, pos.x, pos.y, pos.z, TRUE, TRUE, FALSE);
            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

            script::get_current()->yield();
            ENTITY::SET_ENTITY_INVINCIBLE(obj, TRUE);
            ENTITY::SET_ENTITY_CAN_BE_DAMAGED(obj, FALSE);

            ENTITY::ATTACH_ENTITY_TO_ENTITY(obj, entity, SKEL_Spine0, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, FALSE, FALSE, FALSE, FALSE, 2, TRUE);
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash_object);
        }
        QUEUE_JOB_END_CLAUSE
    }

}