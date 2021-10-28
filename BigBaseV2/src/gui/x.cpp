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
#include <gui\base_tab.h>
#include <gta\Weapons.h>
#include <gui\Variable.h>
#include "crossmap.hpp"
#define arraysize(_ARR)          ((int)(sizeof(_ARR) / sizeof(*(_ARR))))

namespace big
{
    bool ScriptStatus;

    std::vector<UINT64> GetPlayerNetworkHandle(Player player) {
        const int size = 13;
        uint64_t* buffer = std::make_unique<uint64_t[]>(size).get();
        NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, reinterpret_cast<int*>(buffer), 13);
        for (int i = 0; i < size; i++) {
            //Log::Msg("networkhandle[%i]: %llx", i, buffer[i]);
        }
        std::vector<UINT64> result(buffer, buffer + sizeof(buffer));
        return result;
    }
    bool isSpectatingMe(Player player)
    {
        const int HandleSize = 76;
        int Networkhandle[76];
        NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &Networkhandle[0], HandleSize);
        if (NETWORK::NETWORK_IS_HANDLE_VALID(&Networkhandle[0], HandleSize))
        {
            return NETWORK::NETWORK_IS_ACTIVITY_SPECTATOR_FROM_HANDLE(&Networkhandle[0]);
        }
        return false;
    }
    void set_stat(Hash stat, int value)
    {
        QUEUE_JOB_BEGIN_CLAUSE(stat, value)
        {
            STATS::STAT_SET_INT(stat, value, TRUE);
        } QUEUE_JOB_END_CLAUSE
    }
    void set_bitset(int value)
    {
        diamond_heist_info.bitset ^= value;
        QUEUE_JOB_BEGIN_CLAUSE()
        {
            auto stat = g_local.character == 0 ? RAGE_JOAAT("MP0_H3OPT_BITSET0") : RAGE_JOAAT("MP1_H3OPT_BITSET0");
            STATS::STAT_SET_INT(stat, diamond_heist_info.bitset, TRUE);
        } QUEUE_JOB_END_CLAUSE
    }
    void set_bitset_one(int value)
    {
        diamond_heist_info.bitsetone ^= value;
        QUEUE_JOB_BEGIN_CLAUSE()
        {
            auto stat = g_local.character == 0 ? RAGE_JOAAT("MP0_H3OPT_BITSET1") : RAGE_JOAAT("MP1_H3OPT_BITSET1");
            STATS::STAT_SET_INT(stat, diamond_heist_info.bitsetone, TRUE);
        } QUEUE_JOB_END_CLAUSE
    }
    void Notification(const char* Meesage)
    {
        g_fiber_pool->queue_job([Meesage]
            {
                HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
                HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(Meesage);
                HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(true, true);
            });
    }

    void controller::ResetAppearance()
    {
        PED::CLEAR_ALL_PED_PROPS(PLAYER::PLAYER_PED_ID());
        PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
        PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, 0, 0, 0);
        PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, 0, 0, 0);
        PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, 0, 0, 0);
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
        auto hash = rage::get_hash_key<Hash>(name);
        
        STREAMING::REQUEST_MODEL(hash);
        while (!STREAMING::HAS_MODEL_LOADED(rage::joaat(name)))
        {
            script::get_current()->yield();
        }
        return hash;
    }

    void controller::changeAppearance(char* family, int model, int texture)
    {
        if (cstrcmp(family, "HATS") || cstrcmp(family, "GLASSES") || cstrcmp(family, "EARS") || cstrcmp(family, "WATCH") || cstrcmp(family, "BRACELET"))
        {
            if (cstrcmp(family, "HATS"))
                big::base_tab::fam = 0;
            else if (cstrcmp(family, "GLASSES"))
                big::base_tab::fam = 1;
            else if (cstrcmp(family, "EARS"))
                big::base_tab::fam = 2;
            else  if (cstrcmp(family, "WATCH"))
                big::base_tab::fam = 6;
            else if (cstrcmp(family, "BRACELET"))
                big::base_tab::fam = 7;
            PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), big::base_tab::fam, model - 1, texture, 1);
        }
        else
        {
            if (cstrcmp(family, "FACE"))
                big::base_tab::fam = 0;
            else if (cstrcmp(family, "MASK"))
                big::base_tab::fam = 1;
            else if (cstrcmp(family, "HAIR"))
                big::base_tab::fam = 2;
            else if (cstrcmp(family, "JACKET"))
                big::base_tab::fam = 3;
            else if (cstrcmp(family, "LEGS"))
                big::base_tab::fam = 4;
            else if (cstrcmp(family, "BACK"))
                big::base_tab::fam = 5;
            else if (cstrcmp(family, "SHOES"))
                big::base_tab::fam = 6;
            else if (cstrcmp(family, "ACCESSORY"))
                big::base_tab::fam = 7;
            else if (cstrcmp(family, "UNDERSHIRT"))
                big::base_tab::fam = 8;
            else if (cstrcmp(family, "KEVLAR"))
                big::base_tab::fam = 9;
            else if (cstrcmp(family, "BADGE"))
                big::base_tab::fam = 10;
            else if (cstrcmp(family, "TORSO2"))
                big::base_tab::fam = 11;
            PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), big::base_tab::fam, model, texture, 0);
        }
    }

    void controller::spawn_object(const char* name, Entity entity)
    {
        QUEUE_JOB_BEGIN_CLAUSE(name, entity)
        {
            auto pos = ENTITY::GET_ENTITY_COORDS(entity, TRUE);
            auto forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity);
            auto heading = ENTITY::GET_ENTITY_HEADING(entity);

            pos.x += big::base_tab::DISTANCE_SPAWN * forward.x;
            pos.y += big::base_tab::DISTANCE_SPAWN * forward.y;

            MISC::GET_GROUND_Z_FOR_3D_COORD(pos.x, pos.y, pos.z, &pos.z, FALSE, FALSE);

            Hash hash_object = load(name);
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
            if (big::base_tab::ApplyForce)
            {
                ENTITY::APPLY_FORCE_TO_ENTITY(obj, 1, 150.0f, 180.0f, 200.0f, 20.0f, 20.0f, 50.0f, 0, FALSE, TRUE, TRUE, FALSE, TRUE);
            }
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash_object);

            //ENTITY::SET_ENTITY_INVINCIBLE(obj, TRUE);
            //ENTITY::SET_ENTITY_CAN_BE_DAMAGED(obj, FALSE);
        }
        QUEUE_JOB_END_CLAUSE
    }

    void controller::CreatePickup(const char* pickup, const char* prop, int amount, Entity entity)
    {
        QUEUE_JOB_BEGIN_CLAUSE(pickup, prop, amount, entity)
        {
            auto pos = ENTITY::GET_ENTITY_COORDS(entity, TRUE);
            auto forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity);
            auto heading = ENTITY::GET_ENTITY_HEADING(entity);

            pos.z += 1.2f;

            Hash pickup_hash = rage::joaat(pickup);
            Hash hash_prop = load(prop);
            auto pickup = OBJECT::CREATE_AMBIENT_PICKUP(pickup_hash, pos.x, pos.y, pos.z, 0, amount, hash_prop, FALSE, TRUE);

            script::get_current()->yield();
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash_prop);
        }
        QUEUE_JOB_END_CLAUSE
    }

    void controller::AttacthObject(const char* name, Entity entity)
    {
        QUEUE_JOB_BEGIN_CLAUSE(name, entity)
        {
            auto pos = ENTITY::GET_ENTITY_COORDS(entity, TRUE);
            auto forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity);
            auto heading = ENTITY::GET_ENTITY_HEADING(entity);

            Hash hash_object = load(name);
            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
            auto obj = OBJECT::CREATE_OBJECT(hash_object, pos.x, pos.y, pos.z, TRUE, TRUE, FALSE);
            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

            ENTITY::ATTACH_ENTITY_TO_ENTITY(obj, entity, SKEL_Spine0, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, FALSE, FALSE, TRUE, FALSE, 2, TRUE);
            script::get_current()->yield();
            ENTITY::SET_ENTITY_INVINCIBLE(obj, TRUE);
            ENTITY::SET_ENTITY_CAN_BE_DAMAGED(obj, FALSE);
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash_object);
        }
        QUEUE_JOB_END_CLAUSE
    }

    Vector3 controller::GetGroundCoords(Vector3 coords, int tries)
    {
        float groundZ;
        for (int i = 0; i < tries; ++i)
        {
            if (i)
            {
                for (float z = 1000.f; z >= 0.f; z -= 100.f)
                {
                    STREAMING::REQUEST_COLLISION_AT_COORD(coords.x, coords.y, z);
                    script::get_current()->yield();
                }
            }

            if (MISC::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, 1000.f, &groundZ, FALSE, FALSE))
            {
                return Vector3(coords.x, coords.y, groundZ + 1.0f);
            }
        }
        return Vector3(coords.x, coords.y, 225.f);
    }

    void controller::teleport_to_coords(Entity e, Vector3 coords) {
        g_fiber_pool->queue_job([e, coords] {
            ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, coords.z, FALSE, FALSE, TRUE);
            });
    }

    Vector3 controller::get_blip_marker()
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

    Vector3 controller::get_mission_blip()
    {
        static Vector3 zero;
        Vector3 coords, oldCoords;
        auto e = g_local.InVehicle ? g_local.PlayerVehicle : g_local.ped;
        
        bool blipFound = false;
        if (!blipFound)
        {
            for (Blip i = HUD::GET_FIRST_BLIP_INFO_ID(Circle); HUD::DOES_BLIP_EXIST(i) != 0; i = HUD::GET_NEXT_BLIP_INFO_ID(Circle))
            {
                if (HUD::GET_BLIP_COLOUR(i) == YellowMission || HUD::GET_BLIP_COLOUR(i) == Mission || HUD::GET_BLIP_COLOUR(i) == YellowMission2)
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

    void controller::teleport_to_marker()
    {
        g_fiber_pool->queue_job([] {
            int tick = 0;
            Vector3 coords = get_blip_marker();

            if (coords.x == 0 && coords.y == 0)
            {
                return;
            }
            coords = controller::GetGroundCoords(coords, 20);

            auto e = g_local.InVehicle ? g_local.PlayerVehicle : g_local.ped;

            RequestControlOfEnt(e);

            script::get_current()->yield();
            teleport_to_coords(e, coords);
        });
    }

    void controller::teleport_to_objective()
    {
        g_fiber_pool->queue_job([] {
            int tick = 0;
            Vector3 coords = get_mission_blip();
            if (coords.x == 0 && coords.y == 0)
            {
                return;
            }

            // get entity to teleport
            auto e = g_local.InVehicle ? g_local.PlayerVehicle : g_local.ped;;
            
            RequestControlOfEnt(e);

            script::get_current()->yield();
            teleport_to_coords(e, coords);
        });
    }

    float controller::GetPlayerHP()
    {
        static auto WorldPTR = *g_pointers->m_ped_factory;
        return *(FLOAT*)((DWORD64)WorldPTR->m_local_ped + 0x2A0);
    }

    void controller::RequestControlOfid(Entity netid)
    {
        int tick = 0;
        while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netid))
        {
            NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
            script::get_current()->yield();
        }
    }

    void controller::RequestControlOfEnt(Entity entity)
    {
        int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
        for (int i = 0; i < 250 && !NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity); i++) 
        {
            if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) || !NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netID)) 
            {
                NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
                NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netID);
                script::get_current()->yield();
            }
        }
        NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
    }

    Ped controller::ClonePed(Ped ped)
    {
        if (ENTITY::DOES_ENTITY_EXIST(ped) && !ENTITY::IS_ENTITY_DEAD(ped, FALSE))
        {
            return PED::CLONE_PED(ped, ENTITY::GET_ENTITY_HEADING(ped), TRUE, TRUE);
        }

        return 0;
    }

    void controller::CreatePed(Hash PedHash, Vector3 SpawnCoordinates, int ped_type, bool network_handle)
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
                    //ENTITY::ATTACH_ENTITY_TO_ENTITY(NewPed, g_local.SelectedPed, SKEL_Spine0, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, FALSE, FALSE, FALSE, TRUE, 2, TRUE);

                    if (big::base_tab::IsVisible)
                    {
                        ENTITY::SET_ENTITY_VISIBLE(NewPed, FALSE, FALSE);
                    }
                    else if (!big::base_tab::IsVisible)
                    {
                        ENTITY::SET_ENTITY_VISIBLE(NewPed, TRUE, FALSE);
                    }
                    if (big::base_tab::AggressivePed)
                    {
                        PED::SET_PED_CAN_SWITCH_WEAPON(NewPed, true);
                        WEAPON::GIVE_DELAYED_WEAPON_TO_PED(NewPed, RAGE_JOAAT("WEAPON_MINIGUN"), 9999, TRUE);

                        PED::REGISTER_TARGET(NewPed, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_local.SelectedPlayer));
                        TASK::TASK_COMBAT_PED(NewPed, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_local.SelectedPlayer), 0, 1);
                        PED::SET_PED_AS_COP(NewPed, TRUE);
                    }
                    if (big::base_tab::AsBodyGuard)
                    {
                        Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_local.SelectedPlayer);
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

    void controller::AttachPed(Hash PedHash, Ped Target)
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

    void controller::SetPlayerLevel(int PlayerLevel)
    {
        g_fiber_pool->queue_job([PlayerLevel] {
            int SettingLevelPlayer = big::features::LevelData(PlayerLevel);
            const auto mpx = std::to_string(g_local.character);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_CHAR_SET_RP_GIFT_ADMIN"), *script_global(g_global.level_array).at(PlayerLevel, 1).as<int*>(), TRUE);
        });
    }

    void controller::GiveHealAll(bool Activation)
    {
        if (Activation)
        {
            int total_player = g_local.connected_player;
            for (int i = 0; i <= total_player - 1; i++)
            {
                Ped selected_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
                auto GetHealth = ENTITY::GET_ENTITY_HEALTH(selected_ped);
                if (GetHealth >= 100 && GetHealth < 200)
                {
                    if (selected_ped != g_local.ped)
                    {
                        controller::CreatePickup("PICKUP_HEALTH_STANDARD", "prop_ld_health_pack", 1, selected_ped);
                        controller::CreatePickup("PICKUP_ARMOUR_STANDARD", "prop_ld_armour", 1, selected_ped);
                    }
                }
            }
        }
    }

    void controller::SpectatePlayer(Ped playerped)
    {
        g_fiber_pool->queue_job([playerped] {
            Cam SpectateCam;

            Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerped, FALSE);
            SpectateCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_ANIMATED_CAMERA", playerPosition.x, playerPosition.y, playerPosition.z, 0.0, 0.0, 0.0, 50.0, 0, 2);
            CAM::ATTACH_CAM_TO_ENTITY(SpectateCam, playerped, 0, -5, 1, TRUE);
            CAM::POINT_CAM_AT_ENTITY(SpectateCam, playerped, playerPosition.x, playerPosition.y, playerPosition.z, TRUE);
            CAM::SET_CAM_FOV(SpectateCam, 50.0);
            CAM::SET_CAM_ACTIVE(SpectateCam, 1);
            });
    }

    void controller::ChangeCrewTag(char* Tag)
    {
        for (int i = 0; i <= 4; i++)
        {
            DWORD crew_index = (0xB8 * i);
            if (*(bool*)((DWORD64)g_pointers->m_player_crew + 0xD0 + (0xB8 * i)))//Memory::get_value<bool>((uintptr_t)g_pointers->m_player_crew, { 0xD0 + crew_index })
            {
                for (int x = arraysize(Tag); x >= 0; x--)
                {
                    *(char*)((DWORD64)g_pointers->m_player_crew + 0x57 + (0xB8 * i) + x) = Tag[x];//;Memory::set_value((uintptr_t)g_pointers->m_player_crew, { 0x57 + crew_index + x}, Tag)
                }
            }
        }
    }

    bool Script::DoesScriptExist(rage::joaat_t Hash)
    {
        g_fiber_pool->queue_job([Hash]
        {
            if (gta_util::find_script_thread(Hash) != nullptr)
            {
                ScriptStatus = true;
            }
            else if (gta_util::find_script_thread(Hash) == nullptr)
            {
                ScriptStatus = false;
            }
        });
        return ScriptStatus;
    }

    void controller::FasterTimeScale(bool Activation)
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
                //g_pointers->m_set_lobby_time(1, 0);
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
                //g_pointers->m_set_lobby_time(1, 0);
            }
            else
            {
                CLOCK::SET_CLOCK_TIME(12, CLOCK::GET_CLOCK_MINUTES(), CLOCK::GET_CLOCK_SECONDS());
                script::get_current()->yield(1s);
                CLOCK::SET_CLOCK_TIME(0, CLOCK::GET_CLOCK_MINUTES(), CLOCK::GET_CLOCK_SECONDS());
            }
        }
    }

    void controller::RIDSpoofer(uint64_t FakeRID)
    {
        g_fiber_pool->queue_job([FakeRID]
            {
                auto original = *g_pointers->m_player_rid;
                int JoinStatus = *script_global(2426097).at(PLAYER::PLAYER_ID(), 443).as<int*>();
                auto Transition = gta_util::find_script_thread(RAGE_JOAAT("fm_maintain_transition_players"));
                auto Freemode = gta_util::find_script_thread(RAGE_JOAAT("freemode"));
                if (JoinStatus != 4 && Transition != nullptr && Freemode != nullptr)
                {
                    auto WorldPTR = *g_pointers->m_ped_factory;
                    auto PlayerInfo = WorldPTR->m_local_ped->m_playerinfo;
                    PlayerInfo->m_rockstar_id = original;
                }
                auto WorldPTR = *g_pointers->m_ped_factory;
                auto PlayerInfo = WorldPTR->m_local_ped->m_playerinfo;
                PlayerInfo->m_rockstar_id = FakeRID;
            });
    }

    void controller::Revenge(Hash Weapon, bool Activation)
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

                if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(g_local.InVehicle ? g_local.PlayerVehicle : g_local.ped, ped, TRUE) && WEAPON::HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(g_local.InVehicle ? g_local.PlayerVehicle : g_local.ped, 0, 2))
                {
                    for (int i = 0; i <= 10; i++)
                    {
                        Vector3 pos = PED::GET_PED_BONE_COORDS(ped, SKEL_Head, 0.0f, 0.0f, 0.0f);
                        pos.y += 2;
                        pos.x += 2;
                        MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(pos.x + 2, pos.y + 2, pos.z, pos.x, pos.y, pos.z, 1000, false, Weapon, g_local.ped, false, true, 1000);
                        MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(pos.x + 2, pos.y + 2, pos.z, pos.x, pos.y, pos.z, 1000, true, Weapon, g_local.ped, false, true, 1000);
                    }
                }
            }
        }
    }

    void controller::RevengeKick(bool Activation)
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

                if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(g_local.InVehicle ? g_local.PlayerVehicle : g_local.ped, ped, TRUE) && WEAPON::HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(g_local.InVehicle ? g_local.PlayerVehicle : g_local.ped, 0, 2))
                {
                    for (int64_t kick : var::KickHash)
                    {
                        int64_t kick_event[2] = { kick, g_local.SelectedPed };
                        SCRIPT::TRIGGER_SCRIPT_EVENT(1, kick_event, 2, 1 << g_local.SelectedPlayer);
                    }
                }
            }
        }
    }

    void controller::StealOutfit(Player player)
    {
        Ped their_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
        for (int i = 0; i < 12; i++)
        {
            PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, PED::GET_PED_DRAWABLE_VARIATION(their_ped, i),
            PED::GET_PED_TEXTURE_VARIATION(their_ped, i),
            PED::GET_PED_PALETTE_VARIATION(their_ped, i));
        }
    }

    uint64_t controller::GetPlayerRid(Player player)
    {
        auto PlayerListPTR = *g_pointers->m_network_player_mgr;
        auto PlayerIndex = *(uintptr_t*)((DWORD64)PlayerListPTR + (0x180 + (player * 0x8)));
        auto PlayerInfo = PlayerIndex ? *(uintptr_t*)((DWORD64)PlayerIndex + 0xA0) : 0;
        auto PlayerRID = PlayerInfo ? *(uint64_t*)((DWORD64)PlayerInfo + 0x90) : 0;
        return PlayerRID;
    }

    void controller::RunSpeed(float speed)
    {
        auto WorldPTR = *g_pointers->m_ped_factory;
        auto CPed = WorldPTR->m_local_ped;
        CPed->m_playerinfo->m_run_speed = speed;
    }

    void controller::UltraRun(bool Activation)
    {
        if (Activation)
        {
            if (GetAsyncKeyState(0x57))
            {
                Vector3 offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_local.ped, 0, 0.6, 0);
                ENTITY::APPLY_FORCE_TO_ENTITY(g_local.ped, 1, 0.0f, 1.3, 0, 0.0f, 0.0f, 0.0f, 0, TRUE, TRUE, TRUE, FALSE, TRUE);
                PLAYER::SET_PLAYER_SPRINT(g_local.player, 1);
                RunSpeed(1.30f);
            }
        }
    }

    void controller::SwimSpeed(float speed)
    {
        auto WorldPTR = *g_pointers->m_ped_factory;
        auto CPed = WorldPTR->m_local_ped;
        CPed->m_playerinfo->m_swim_speed = speed;
    }

    void controller::HeadShotNPC(bool Activation)
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

                if (ped == g_local.ped || PED::IS_PED_A_PLAYER(ped))
                    continue;

                if (!PED::IS_PED_A_PLAYER(ped))
                {
                    controller::RequestControlOfEnt(ped);
                    if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ped) && !ENTITY::IS_ENTITY_DEAD(ped, TRUE))
                    {
                        Vector3 Coords = PED::GET_PED_BONE_COORDS(ped, SKEL_Head, 0.0f, 0.0f, 0.0f);
                        Coords.y += 0.1f;
                        Coords.x += 0.1f;
                        MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Coords.x + 0.1f, Coords.y + 0.1f, Coords.z, Coords.x, Coords.y, Coords.z, 1, false, WEAPON_MG, g_local.ped, true, true, 1000);
                    }
                }
            }
        }
    }

    void controller::AntiGriefVehicle(bool Activation)
    {
        if (Activation)
        {
            Vehicle vehicle;
            if (rage::joaat(SCRIPT::GET_THIS_SCRIPT_NAME()) == RAGE_JOAAT("freemode"))
            {
                if (NETWORK::NETWORK_DOES_NETWORK_ID_EXIST(*script_global(2426865).at(g_local.player, 449).at(38).as<int*>()) && NETWORK::NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID(*script_global(2426865).at(g_local.player, 449).at(38).as<int*>()))
                {
                    vehicle = NETWORK::NET_TO_VEH(*script_global(2426865).at(g_local.player, 449).at(38).as<int*>());
                }
            }
            vehicle = *script_global(2544210).at(298).as<int*>();
            rage::CPedInterface* ped_interface = g_pointers->m_replay_interface->m_ped_interface;
            for (int i = 0; i < ped_interface->m_max_peds; i++)
            {
                auto* ped_ptr = ped_interface->get_ped(i);
                if (ped_ptr == nullptr)
                    continue;

                Ped ped = g_pointers->m_ptr_to_handle(ped_ptr);
                if (ped == 0)
                    break;

                if (ped == g_local.ped || PED::IS_PED_A_PLAYER(ped))
                    continue;

                Player player = NETWORK::NETWORK_GET_PLAYER_INDEX_FROM_PED(ped);
                if (!PED::IS_PED_A_PLAYER(ped))
                {
                    if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(vehicle, ped, TRUE) && WEAPON::HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(vehicle, 0, 2))
                    {
                        auto playerPosition = ENTITY::GET_ENTITY_COORDS(g_local.ped, TRUE);
                        auto target = ENTITY::GET_ENTITY_COORDS(ped, TRUE);
                        if (MISC::GET_DISTANCE_BETWEEN_COORDS(playerPosition.x, playerPosition.y, playerPosition.z, target.x, target.y, target.z, false) > 300.0f)
                        {
                            CrashPlayer(ped, target);
                        }
                        for (int64_t kick : var::KickHash)
                        {
                            int64_t kick_event[2] = { kick, ped };
                            SCRIPT::TRIGGER_SCRIPT_EVENT(1, kick_event, 2, 1 << player);
                        }
                    }
                }
            }
        }
    }

    void controller::InvalidModelProtection(bool Activation)
    {
        if (Activation && !g_local.transition)
        {
            Memory::set_value((uintptr_t)g_pointers->m_hash_table, { 0x2EB8, 0x8E0 }, rage::joaat("player_one"));
            Memory::set_value((uintptr_t)g_pointers->m_hash_table, { 0x2EB8, 0x8F0 }, rage::joaat("player_one"));
            Memory::set_value((uintptr_t)g_pointers->m_hash_table, { 0x2EB8, 0x900 }, rage::joaat("player_one"));
        }
        else
        {
            Memory::set_value((uintptr_t)g_pointers->m_hash_table, { 0x2EB8, 0x8E0 }, rage::joaat("slod_human"));
            Memory::set_value((uintptr_t)g_pointers->m_hash_table, { 0x2EB8, 0x8F0 }, rage::joaat("slod_small_quadped"));
            Memory::set_value((uintptr_t)g_pointers->m_hash_table, { 0x2EB8, 0x900 }, rage::joaat("slod_large_quadped"));
        }
    }

    void controller::ShowMessage(const char* Message, bool InPauseMenu)
    {
        HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
        HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(Message);
        HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", FALSE, 0, "~bold~Ellohim", "~bold~~y~Private Mod Menu");
        HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(true, InPauseMenu);
    }

    Ped controller::CrashPlayer(Entity target, Vector3 SpawnCoordinates)
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

    void controller::NightclubTriggerProduction()
    {
        for (int i = 0; i < 4; i++)
        {
            if (*script_global(g_global.nc_trigger_product).at(i, 2).at(1).as<int*>() == 1)
            {
                *script_global(g_global.nc_trigger_product).at(i, 2).as<int*>() = 0;//2515749
            }
        }
    }

    void controller::RemoveInsuranceClaims()
    {
        int _maxslots = 0, _index = 0, _hash = 0, _flags = 0;
        _maxslots = *script_global(1323703).as<int*>();//1323678
        for (int i = 0; i < _maxslots; i++) 
        {
            _index = 1323703 + 1 + (i * 142);
            _hash = *script_global(_index).at(66).as<int*>();
            if (_hash != 0) 
            {
                _flags = *script_global(_index).at(103).as<int*>();
                if (_flags != 0) 
                {
                    _flags = Memory::Clear_Bit(_flags, 1); // Vehicle destroyed : "Your Personal Vehicle has been destroyed. You can call Mors Mutual Insurance to make a claim"
                    _flags = Memory::Clear_Bit(_flags, 7); // Insurance Claim open or in process
                    _flags = Memory::Clear_Bit(_flags, 16); // Vehicle outside the Garage and no Insurance or a Insurance Claim(is open or in process)
                    *script_global(_index).at(103).as<int*>() = _flags;
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

    bool controller::HasSpecialCharacters(const char* str)
    {
        return str[strspn(str, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_!@#$%^&*()-.,[]{}=+ ")] != 0;
    }

    bool controller::IsNotANumber(const char* str)
    {
        return str[strspn(str, "0123456789")] != 0;
    }

    std::string controller::char_to_string(char* a, int size)
    {
        int i;
        std::string s = "";
        for (i = 0; i < size; i++) {
            s = s + a[i];
        }
        return s;
    }

    std::filesystem::path controller::get_events_config()
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

    nlohmann::json controller::get_events_json()
    {
        auto file_path = get_events_config();
        nlohmann::json locations;
        std::ifstream file(file_path);

        if (!file.fail())
            file >> locations;

        return locations;
    }

    std::vector<std::string> controller::list_events()
    {
        std::vector<std::string> return_value;
        auto json = get_events_json();
        for (auto& item : json.items())
            return_value.push_back(item.key());
        return return_value;
    }

    void controller::load_event_menu(std::string& selected_event, event_json::event_json& event_obj)
    {
        if (!selected_event.empty())
        {
            auto events = get_events_json();
            if (events[selected_event].is_null())
                return;
            event_obj = events[selected_event].get<event_json::event_json>();
        }
    }

    void controller::save_event(char* event_name, event_json::event_json& event_obj)
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

    void controller::delete_event(std::string name)
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

    std::filesystem::path controller::get_globals_config()
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

    nlohmann::json controller::get_globals_json()
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
        auto json = controller::get_globals_json();
        for (auto& item : json.items())
            return_value[item.key()] = item.value();
        return return_value;
    }

    void controller::load_global_menu(const std::string& selected_global, global_test_json::global_test_json& global_obj)
    {
        if (!selected_global.empty())
        {
            auto globals = get_globals_json();
            if (globals[selected_global].is_null())
                return;
            global_obj = globals[selected_global].get<global_test_json::global_test_json>();
        }
    }

    void controller::save_global(char* global_name, global_test_json::global_test_json& global_obj)
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

    void controller::delete_global(std::string name)
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

    int64_t* controller::get_global_ptr(global_test_json::global_test_json& global_test)
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

    std::filesystem::path controller::get_locals_config()
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

    nlohmann::json controller::get_locals_json()
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
        auto json = controller::get_locals_json();
        for (auto& item : json.items())
            return_local[item.key()] = item.value();
        return return_local;
    }

    void controller::load_local_menu(const std::string& selected_local, local_test_json::local_test_json& local_obj)
    {
        if (!selected_local.empty())
        {
            auto locals = get_locals_json();
            if (locals[selected_local].is_null())
                return;
            local_obj = locals[selected_local].get<local_test_json::local_test_json>();
        }
    }

    void controller::save_local(char* local_name, local_test_json::local_test_json& local_obj)
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

    void controller::delete_local(std::string name)
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

    int32_t* controller::get_local_ptr(GtaThread* scriptThread, local_test_json::local_test_json& local_test)
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

    void controller::DumpEntryBoi()
    {
        std::string settings_file = std::getenv("appdata");
        settings_file += "\\Em1R\\EntryPoints.txt";

        std::ofstream file(settings_file, std::ios::out | std::ios::trunc);
        for (auto& map : g_crossmap)
        {
            auto address = g_pointers->m_get_native_handler(g_pointers->m_native_registration_table, map.second);

            file << std::hex << std::uppercase << "0x" << map.first << " : " << "0x" << address << std::endl;
        }

        file.close();
    }

    void controller::variable_attach()
    {
        if (g_local.player != PLAYER::PLAYER_ID() || g_local.ped != PLAYER::PLAYER_PED_ID())
        {
            g_local.player = PLAYER::PLAYER_ID();
            g_local.ped = PLAYER::PLAYER_PED_ID();
        }
        g_event_tester.event_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_event_tester.event_player);
        g_local.InVehicle = PED::IS_PED_IN_ANY_VEHICLE(g_local.ped, FALSE);
        g_local.PlayerVehicle = PED::GET_VEHICLE_PED_IS_USING(g_local.ped);
        g_local.SelectedPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_local.SelectedPlayer);
        g_local.ScriptHost = NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0);
        g_local.character = *script_global(1312763).as<int*>();
        g_local.connected_player = NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS();
        g_local.mission = gta_util::find_script_thread(RAGE_JOAAT("fm_mission_controller"));
        g_local.arcade = gta_util::find_script_thread(RAGE_JOAAT("gb_casino_heist_planning"));
        g_local.mission_2020 = gta_util::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020"));
        g_ptr.WorldPTR = (uintptr_t)g_pointers->m_ped_factory;
        g_original.rid = *g_pointers->m_player_rid;

        const uint32_t tuneable = 262145u;
        g_global.level_array = 293362;
        g_global.rc_bandito = 2544210 + 6688;
        g_global.mini_tank = 2544210 + 6689;
        g_global.drone = 1695733;
        g_global.moc = 2544210 + 913;
        g_global.avanger = 2544210 + 921;
        g_global.terorbyte = 2544210 + 925;
        g_global.kosatka = 2544210 + 933;
        g_global.dinghy = 2544210 + 945;

        g_global.casino_cut_1 = 1703513 + 2325 + 1;
        g_global.casino_cut_2 = 1703513 + 2325 + 2;
        g_global.casino_cut_3 = 1703513 + 2325 + 3;
        g_global.casino_cut_4 = 1703513 + 2325 + 4;

        g_global.doomsday_cut_1 = 1699568 + 812 + 50 + 1;
        g_global.doomsday_cut_2 = 1699568 + 812 + 50 + 2;
        g_global.doomsday_cut_3 = 1699568 + 812 + 50 + 3;
        g_global.doomsday_cut_4 = 1699568 + 812 + 50 + 4;

        g_global.apartmen_cut_1 = 1671773 + 3008 + 1;
        g_global.apartmen_cut_2 = 1671773 + 3008 + 2;
        g_global.apartmen_cut_3 = 1671773 + 3008 + 3;
        g_global.apartmen_cut_4 = 1671773 + 3008 + 4;

        g_global.cayo_cut_1 = 1710289 + 823 + 56 + 1;
        g_global.cayo_cut_2 = 1710289 + 823 + 56 + 2;
        g_global.cayo_cut_3 = 1710289 + 823 + 56 + 3;
        g_global.cayo_cut_4 = 1710289 + 823 + 56 + 4;

        g_global.diamond = tuneable + 28306;
        g_global.gold = tuneable + 28305;
        g_global.artwork = tuneable + 28304;
        g_global.cash = tuneable + 28303;

        g_global.tequila = tuneable + 29461;
        g_global.ruby = tuneable + 29462;
        g_global.bearer_bond = tuneable + 29463;
        g_global.pink_diamond = tuneable + 29464;
        g_global.madrazo_file = tuneable + 29465;
        g_global.saphire = tuneable + 29466;
        g_global.bag_size = tuneable + 29476;

        g_global.fleeca = tuneable + 8834u;
        g_global.prison_break = tuneable + 8835;
        g_global.human_lab = tuneable + 8836;
        g_global.a_series = tuneable + 8837;
        g_global.pasific_standard = tuneable + 8838;

        g_global.act_1 = tuneable + 8839;
        g_global.act_2 = tuneable + 8840;
        g_global.act_3 = tuneable + 8841;

        g_global.session_change = 1312443;
        g_global.session_type = 1312861;
        g_global.is_session_private = 2453009 + 744;//2453009.f_744
        g_global.sctv = 2464755;
        g_global.session_unk_1 = 31346;
        g_global.session_unk_2 = 1312482;
        g_global.session_unk_3 = 1312855;

        g_global.casino_stat = 1707876;
        g_global.ch_gunman.karl_cut = tuneable + 28315;
        g_global.ch_gunman.gustavo_cut = tuneable + 28316;
        g_global.ch_gunman.charlie_cut = tuneable + 28317;
        g_global.ch_gunman.chester_cut = tuneable + 28318;
        g_global.ch_gunman.packie_cut = tuneable + 28319;
        g_global.ch_driver.karim_cut = tuneable + 28320;
        g_global.ch_driver.taliana_cut = tuneable + 28321;
        g_global.ch_driver.eddie_cut = tuneable + 28322;
        g_global.ch_driver.zach_cut = tuneable + 28323;
        g_global.ch_driver.chester_cut = tuneable + 28324;
        g_global.ch_hacker.rickie_cut = tuneable + 28325;
        g_global.ch_hacker.christian_cut = tuneable + 28326;
        g_global.ch_hacker.yohan_cut = tuneable + 28327;
        g_global.ch_hacker.avi_cut = tuneable + 28328;
        g_global.ch_hacker.paige_cut = tuneable + 28329;

        g_global.special_crates = 1683673;
        g_global.rare_item = 1683827;
        
        g_global.mc_supplies_delay = tuneable + 18661;
        g_global.bunker_supplies_delay = tuneable + 21261;
        g_global.bunker_selling_time_1 = tuneable + 21399;
        g_global.bunker_selling_time_2 = tuneable + 21403;
        g_global.bunker_selling_time_3 = tuneable + 21393;
        g_global.bunker_selling_time_4 = tuneable + 21401;
        g_global.bunker_selling_time_5 = tuneable + 21406;
        g_global.bunker_selling_time_6 = tuneable + 21395;
        g_global.bunker_selling_mult = tuneable + 21216;

        g_global.mc_selling_time_1 = tuneable + 18232;
        g_global.mc_selling_time_2 = tuneable + 18229;
        g_global.mc_selling_time_3 = tuneable + 18219;
        g_global.mc_selling_time_4 = tuneable + 18223;
        g_global.mc_selling_time_5 = tuneable + 18225;
        g_global.mc_selling_time_6 = tuneable + 18259;
        g_global.mc_selling_time_7 = tuneable + 18256;
        g_global.mc_selling_time_8 = tuneable + 18266;
        g_global.mc_selling_time_9 = tuneable + 18270;
        g_global.mc_selling_time_10 = tuneable + 18261;
        g_global.mc_sell_mult = tuneable + 18774;
        g_global.mc_document = tuneable + 17135;
        g_global.mc_cash = tuneable + 17136;
        g_global.mc_coke = tuneable + 17137;
        g_global.mc_meth = tuneable + 17138;
        g_global.mc_weed = tuneable + 17139;
        g_global.vision = 1590908 + 1 + g_local.player * 874 + 834 + 9 + 1;

        g_global.special_cargo_selling_cooldown = tuneable + 15274;
        g_global.special_cargo_buying_cooldown = tuneable + 15273;
        g_global.special_cargo_selling_time = tuneable + 15287;
        g_global.business_index = 1590908 + 1 + (g_local.player * 874) + 267 + 185;
        g_global.nc_trigger_product = 2518601;

        m_local.take_casino = 19406 + 2685;
        m_local.take_cayo = 39493 + 1536 + 53;// 31600 + 9482 (41082) 39493.f_1589
        m_local.take_cayo_2 = 41112;
        m_local.vault_door = 8853 + 996;
        m_local.submarine_computer = 1538;
        m_local.tc_live_c = 42692 + 1009 + 1;
        m_local.tc_live = 25831 + 1322 + 1;
        m_local.doomsday_act_3_hack = 1343 + 4;

        m_local.special_cargo_buying = 610;
        m_local.special_cargo_sell = 535;

        m_local.bunker_sell = 1215;
        m_local.bunker_sell_time_remaining = 1197;

        m_local.mc_sell = 709;

        m_local.nc_sell = 2316;
        m_local.nc_time_remaining = 758;

        m_local.blackjack.current_table = 1784 + 1 + (g_local.player * 8) + 4;
        m_local.blackjack.current_card = 124 + 1;
        m_local.blackjack.bet_trigger = 1784 + 1 + (g_local.player * 8);
        m_local.blackjack.unk_1 = 2041;
        m_local.blackjack.unk_2 = 3628;
        m_local.blackjack.unk_3 = 122;
        m_local.blackjack.button_ready = 2041 + 874 + 693;
        m_local.slot.struct_21 = 221;
        m_local.slot.unk_1 = 2133;
        m_local.slot.unk_2 = 2136;
        m_local.lucky_wheel.podium_vehicle = 270 + 14;
        m_local.lucky_wheel.trigger_wheel = 270 + 45;

        g_script_event.clear_wanted = 1630816 + 1 + (g_local.SelectedPlayer * 597) + 508;
    }
}
