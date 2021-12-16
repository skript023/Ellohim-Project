#include "common.hpp"
#include "vehicle_helper.h"
#include "script.hpp"
#include "gta_util.hpp"
#include "gta/net_object_mgr.hpp"
#include "script_global.hpp"
#include "gui/player_list.h"
#include "gui/controller/ScriptController.h"
#include "gui/controller/system_control.h"
#include "gui/controller/game_variable.h"
#include "gui/controller/memory_address.hpp"
#include "gui/player/player_option.h"
#include "gui/controller/network_controller.h"
#include "gui/game_event/game_event.h"

namespace big
{
    void vehicle_helper::set_vehicle_collision(Player player, bool activation)
    {
        if (activation)
        {
            if (player::is_player_in_any_vehicle(player))
            {//0.03999999911f
                for (int i = 0; i <= 64; i++)//-100000000.f
                {
                    if (rage_helper::get_local_vehicle()->m_navigation->m_ph_arche->get_geometry(i) == nullptr || rage_helper::get_local_vehicle()->m_navigation->m_ph_arche->get_geometry(i) > reinterpret_cast<VehicleCollision*>(0x7FFFFFFFFFF) || rage_helper::get_local_vehicle()->m_navigation->m_ph_arche->get_geometry(i) < rage_helper::get_local_vehicle()->m_navigation->m_ph_arche->get_geometry(1))
                        continue;
                    if (systems::is_float_equal(rage_helper::get_local_vehicle()->m_navigation->m_ph_arche->get_geometry(i)->m_collision, 0.03999999911f))
                        rage_helper::get_local_vehicle()->m_navigation->m_ph_arche->get_geometry(i)->m_collision = -100000000.f;
                }
            }
        }
    }
    
    void vehicle_helper::set_vehicle_turn_light(Vehicle vehicle, int TurnLight)
    {
        if (auto veh = rage_helper::entity_to_pointer<CVehicle*>(vehicle))
        {
            veh->m_turn_light = TurnLight;
        }
    }

    void vehicle_helper::set_vehicle_engine_on(Vehicle vehicle, bool EngineStatus)
    {
        if (auto veh = rage_helper::entity_to_pointer<CVehicle*>(vehicle))
        {
            if (EngineStatus)
                veh->m_vehicle_engine = 17;
            else if (!EngineStatus)
                veh->m_vehicle_engine = 1;
        }
    }

    bool vehicle_helper::get_vehicle_engine(Vehicle vehicle)
    {
        int engine_status = 0;
        if (auto veh = rage_helper::entity_to_pointer<CVehicle*>(vehicle))
        {
            engine_status = veh->m_vehicle_engine;
        }
        return engine_status == 17;
    }

    Vehicle vehicle_helper::get_personal_vehicle(Player player)
    {
        if (rage::joaat(SCRIPT::GET_THIS_SCRIPT_NAME()) == RAGE_JOAAT("freemode"))
        {
            if (NETWORK::NETWORK_DOES_NETWORK_ID_EXIST(*script_global(2689156).at(player, 453).at(38).as<int*>()) && NETWORK::NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID(*script_global(2689156).at(player, 453).at(38).as<int*>()))
            {
                return NETWORK::NET_TO_VEH(*script_global(2689156).at(player, 453).at(38).as<int*>());
            }
        } 
        return *script_global(2810287).at(298).as<int*>();
    }

    std::string vehicle_helper::get_vehicle_name_from_hash(Hash vehicle_hash)
    {
        std::string sVar0 = std::to_string(vehicle_hash);
        for (auto vehicle : var::VechicleList)
        {
            if (rage::joaat(vehicle) == vehicle_hash)
            {
                sVar0 = rage::joaat_to_string(vehicle, vehicle_hash);
            }
        }
        return sVar0;
    }

    void vehicle_helper::infinite_boosts(bool Activation)
    {
        if (Activation)
        {

            if (g_local.InVehicle)
            {
                script::get_current()->yield();
                auto VehicleHash = rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_model_hash;
                auto Flag = rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_4; //*(uint32_t*)((DWORD64)VehicleInfo + 0x588);
                auto BoostLevel = rage_helper::get_local_vehicle()->m_vehicle_boost;//Memory::get_value<float>(g_ptr.WorldPTR, { 0x8, 0xD30, 0x320 });//*(float*)((DWORD64)VehiclePTR + 0x320);

                if (VehicleHash == RAGE_JOAAT("Oppressor2") && BoostLevel < 0.99f && GetKeyState(0x58) & 0x8000)
                {
                    rage_helper::get_local_vehicle()->m_vehicle_boost = 1.00f;
                }
                else if (VehicleHash == RAGE_JOAAT("Scramjet") && BoostLevel < 2.24f && GetKeyState(0x58) & 0x8000)
                {
                    rage_helper::get_local_vehicle()->m_vehicle_boost = 2.25f;
                }
                else if (VehicleHash == RAGE_JOAAT("Toreador") && BoostLevel < 0.99f && GetKeyState(0x45) & 0x8000)
                {
                    rage_helper::get_local_vehicle()->m_vehicle_boost = 1.00f;
                }
                else if (VehicleHash == RAGE_JOAAT("Voltic2") || VehicleHash == RAGE_JOAAT("Oppressor") || VehicleHash == RAGE_JOAAT("Vigilante") && GetKeyState(0x45) && BoostLevel < 1.24f)
                {
                    rage_helper::get_local_vehicle()->m_vehicle_boost = 1.25f;
                }
                else if (Flag == 1107558400 || Memory::Is_Bit_Set(Flag, 30) && BoostLevel < 1.24f && GetKeyState(0x45) & 0x8000)
                {
                    rage_helper::get_local_vehicle()->m_vehicle_boost = 1.25f;
                }
                else
                {
                    return;
                }
            }
        }
    }

    void vehicle_helper::horn_boosts(bool Activation)
    {
        if (Activation)
        {
            if (PLAYER::IS_PLAYER_PRESSING_HORN(PLAYER::PLAYER_ID()))
            {
                Vehicle Veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), false);
                NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Veh);
                if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Veh))
                {
                    VEHICLE::SET_VEHICLE_FORWARD_SPEED(Veh, 700.f);
                }
            }
        }
    }

    void vehicle_helper::vehicle_godmode(bool Activation)
    {
        if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE))
        {
            auto VehId = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
            script::get_current()->yield();
            if (Activation)
            {
                ENTITY::SET_ENTITY_INVINCIBLE(VehId, TRUE);
                VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(VehId, FALSE);
                ENTITY::SET_ENTITY_PROOFS(VehId, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE);
                VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(VehId, FALSE);
                VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(VehId, FALSE);
                if (VEHICLE::_IS_VEHICLE_DAMAGED(VehId))
                {
                    VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(VehId);
                    GRAPHICS::REMOVE_DECALS_FROM_VEHICLE(VehId);
                    if (!VEHICLE::IS_VEHICLE_WINDOW_INTACT(VehId, 6))
                        VEHICLE::FIX_VEHICLE_WINDOW(VehId, 6);
                    if (!VEHICLE::IS_VEHICLE_WINDOW_INTACT(VehId, 7))
                        VEHICLE::FIX_VEHICLE_WINDOW(VehId, 7);
                }
            }
            else
            {
                ENTITY::SET_ENTITY_INVINCIBLE(VehId, FALSE);
                VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(VehId, TRUE);
                ENTITY::SET_ENTITY_PROOFS(VehId, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);
                VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(VehId, TRUE);
                VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(VehId, TRUE);
            }
        }
    }

    void vehicle_helper::anti_grief_vehicle(bool Activation)
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
                            remote_event::crash_player(ped, target);
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

    void vehicle_helper::claim_insurance()
    {
        int _maxslots = 0, _index = 0, _hash = 0, _flags = 0;
        _maxslots = *script_global(g_global.garage).as<int*>();//1323678
        for (int i = 0; i < _maxslots; i++)
        {
            _index = g_global.garage + 1 + (i * 142);
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

    void vehicle_helper::set_vehicle_flag(int Flag, uint32_t flagBit)
    {
        if (g_local.InVehicle)
        {
            switch (Flag)
            {
                case 1:
                {
                    auto set_bit = rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_1;
                    uint32_t bit_set = Memory::Set_Bit(set_bit, flagBit);
                    rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_1 = bit_set;
                    break;
                }
                case 2:
                {
                    auto set_bit = rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_2;
                    uint32_t bit_set = Memory::Set_Bit(set_bit, flagBit);
                    rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_2 = bit_set;
                    break;
                }
                case 3:
                {
                    auto set_bit = rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_3;
                    uint32_t bit_set = Memory::Set_Bit(set_bit, flagBit);
                    rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_3 = bit_set;
                    break;
                }
                case 4:
                {
                    auto set_bit = rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_4;
                    uint32_t bit_set = Memory::Set_Bit(set_bit, flagBit);
                    rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_4 = bit_set;
                    break;
                }
                case 5:
                {
                    auto set_bit = rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_5;
                    uint32_t bit_set = Memory::Set_Bit(set_bit, flagBit);
                    rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_5 = bit_set;
                    break;
                }
                case 6:
                {
                    auto set_bit = rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_6;
                    uint32_t bit_set = Memory::Set_Bit(set_bit, flagBit);
                    rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_6 = bit_set;
                    break;
                }
                case 7:
                {
                    auto set_bit = rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_7;
                    uint32_t bit_set = Memory::Set_Bit(set_bit, flagBit);
                    rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_7 = bit_set;
                    break;
                }
            }
        }
    }

    void vehicle_helper::clear_vehicle_flag(int Flag, uint32_t flagBit)
    {
        if (g_local.InVehicle)
        {
            switch (Flag)
            {
                case 1:
                {
                    auto set_bit = rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_1;
                    uint32_t bit_set = Memory::Clear_Bit(set_bit, flagBit);
                    rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_1 = bit_set;
                    break;
                }
                case 2:
                {
                    auto set_bit = rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_2;
                    uint32_t bit_set = Memory::Clear_Bit(set_bit, flagBit);
                    rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_2 = bit_set;
                    break;
                }
                case 3:
                {
                    auto set_bit = rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_3;
                    uint32_t bit_set = Memory::Clear_Bit(set_bit, flagBit);
                    rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_3 = bit_set;
                    break;
                }
                case 4:
                {
                    auto set_bit = rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_4;
                    uint32_t bit_set = Memory::Clear_Bit(set_bit, flagBit);
                    rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_4 = bit_set;
                    break;
                }
                case 5:
                {
                    auto set_bit = rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_5;
                    uint32_t bit_set = Memory::Clear_Bit(set_bit, flagBit);
                    rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_5 = bit_set;
                    break;
                }
                case 6:
                {
                    auto set_bit = rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_6;
                    uint32_t bit_set = Memory::Clear_Bit(set_bit, flagBit);
                    rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_6 = bit_set;
                    break;
                }
                case 7:
                {
                    auto set_bit = rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_7;
                    uint32_t bit_set = Memory::Clear_Bit(set_bit, flagBit);
                    rage_helper::get_local_ped()->m_last_vehicle->m_model_info->m_flag_7 = bit_set;
                    break;
                }
            }
        }
    }

    void vehicle_helper::infinite_vehicle_ammo(bool Activation)
    {
        if (Activation && rage_helper::get_local_ped()->m_is_in_vehicle)
        {
            rage_helper::get_local_ped()->m_last_vehicle->m_vehicle_missile = INT_MAX;
            rage_helper::get_local_ped()->m_last_vehicle->m_oppressor_missile = INT_MAX;
            rage_helper::get_local_ped()->m_last_vehicle->m_air_craft_bomb = INT_MAX;
            rage_helper::get_local_ped()->m_last_vehicle->m_counter_meassure = INT_MAX;
        }
    }

    void vehicle_helper::repair_vehicle(Ped player_ped)
    {
        g_fiber_pool->queue_job([=] {
            Vehicle VehicleId = PED::GET_VEHICLE_PED_IS_IN(player_ped, FALSE);

            network::request_control(VehicleId);
            script::get_current()->yield();

            VEHICLE::SET_VEHICLE_FIXED(VehicleId);
            VEHICLE::SET_VEHICLE_ENGINE_HEALTH(VehicleId, 1000.0f);
            VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(VehicleId, 1000.0f);
            VEHICLE::SET_VEHICLE_DIRT_LEVEL(VehicleId, 0.0f);
            if (!VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(VehicleId))
            {
                VEHICLE::SET_VEHICLE_ENGINE_ON(VehicleId, TRUE, TRUE, FALSE);
            }
        });
    }

    void vehicle_helper::vehicle(const char* name, Entity entity)
    {
        QUEUE_JOB_BEGIN_CLAUSE(=)
        {
            if (!*g_pointers->m_is_session_started) *script_global(4533757).as<bool*>() = true;
            auto pos = ENTITY::GET_ENTITY_COORDS(entity, TRUE);
            auto forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity);
            auto heading = ENTITY::GET_ENTITY_HEADING(entity);

            pos.x += player_list::DISTANCE_SPAWN * forward.x;
            pos.y += player_list::DISTANCE_SPAWN * forward.y;
            
            Hash hash_vehicle = controller::load(name);//load(name);

            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
            auto vehicle = VEHICLE::CREATE_VEHICLE(hash_vehicle, pos.x, pos.y, pos.z + 1.f, heading + 90.0f, TRUE, TRUE, FALSE);
            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

            script::get_current()->yield();

            VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(vehicle, 1.f);
            VEHICLE::_SET_VEHICLE_CAN_BE_LOCKED_ON(vehicle, FALSE, FALSE);
            VEHICLE::_SET_VEHICLE_MAX_SPEED(vehicle, 1.39f * VEHICLE::GET_VEHICLE_ESTIMATED_MAX_SPEED(vehicle));
            VEHICLE::MODIFY_VEHICLE_TOP_SPEED(vehicle, 1.39f);
            VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, "Janda");

            if (g_settings.options["Auto Get-in"])
            {
                PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);
            }

            if (g_toggle.godmode)
            {
                ENTITY::SET_ENTITY_INVINCIBLE(vehicle, TRUE);
            }

            if (g_settings.options["Full Upgrade Bool"])
            {
                VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_XENONHEADLIGHTS, TRUE);
                VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_TURBO, TRUE);
                VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 0, TRUE);
                VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 1, TRUE);
                VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 2, TRUE);
                VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 3, TRUE);
                VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(vehicle, NEON_COLOR_RED);
                VEHICLE::_SET_VEHICLE_XENON_LIGHTS_COLOR(vehicle, 8);
                VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);

                for (int i = 0; i < 50; i++)
                {
                    VEHICLE::SET_VEHICLE_MOD(vehicle, i, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, i) - 1, TRUE);
                }
                VEHICLE::SET_VEHICLE_WHEEL_TYPE(vehicle, 9);
                VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_FRONTWHEEL, 52, TRUE);
            }

            if (VEHICLE::IS_THIS_MODEL_A_PLANE(hash_vehicle))
            {
                VEHICLE::SET_PLANE_TURBULENCE_MULTIPLIER(vehicle, 0.0f);
            }
            if (g_settings.options["Auto Get-in"])
            {
                STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
                GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
                GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_clown_appears", PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.6, false, false, false);
            }
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash_vehicle);

            if (*g_pointers->m_is_session_started)
            {
                DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
                ENTITY::_SET_ENTITY_SOMETHING(vehicle, TRUE); //True means it can be deleted by the engine when switching lobbies/missions/etc, false means the script is expected to clean it up.
                auto networkId = NETWORK::VEH_TO_NET(vehicle);
                if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
                    NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
                VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
            }
        }
        QUEUE_JOB_END_CLAUSE
    }

    void vehicle_helper::SpawnVehicle(const char* name, bool pegasus, Player player_target)
    {
        QUEUE_JOB_BEGIN_CLAUSE(=)
        {
            //Vector3 player_coords = { Memory::get_value<float>(g_ptr.WorldPTR, { 0x8, 0x30, 0x50 }), Memory::get_value<float>(g_ptr.WorldPTR, { 0x8, 0x30, 0x54 }), Memory::get_value<float>(g_ptr.WorldPTR, { 0x8, 0x30, 0x58 }) };
            auto ped = player::get_player_ped(player_target);
            Vector3 player_coords = ENTITY::GET_ENTITY_COORDS(ped, TRUE);
            auto heading = rage_helper::get_local_ped()->m_navigation->m_heading;
            player_coords.x = player_coords.x - (heading.y * player_list::DISTANCE_SPAWN);
            player_coords.y = player_coords.y + (heading.x * player_list::DISTANCE_SPAWN);

            *script_global(2463533).at(7).at(0).as<float*>() = player_coords.x;
            *script_global(2463533).at(7).at(1).as<float*>() = player_coords.y;
            *script_global(2463533).at(7).at(2).as<float*>() = player_coords.z;
            *script_global(2463533).at(27).at(66).as<uint32_t*>() = rage::joaat(name);
            *script_global(2463533).at(27).at(28).as<int*>() = 1;
            *script_global(2463533).at(27).at(95).as<int*>() = 14;
            *script_global(2463533).at(27).at(94).as<int*>() = 2;
            *script_global(2463533).at(27).at(5).as<int*>() = -1;
            *script_global(2463533).at(27).at(6).as<int*>() = -1;
            *script_global(2463533).at(5).as<bool*>() = true;
            *script_global(2463533).at(2).as<bool*>() = true;
            *script_global(2463533).at(3).as<bool*>() = pegasus;
            *script_global(2463533).at(27).at(77).as<uint32_t*>() = 4030726305;
            script::get_current()->yield(1s);
            Vehicle vehicle = *script_global(2544210).at(6610).as<Vehicle*>();
            VEHICLE::_SET_VEHICLE_CAN_BE_LOCKED_ON(vehicle, FALSE, FALSE);
            VEHICLE::_SET_VEHICLE_MAX_SPEED(vehicle, 1.39f * VEHICLE::GET_VEHICLE_ESTIMATED_MAX_SPEED(vehicle));
            VEHICLE::MODIFY_VEHICLE_TOP_SPEED(vehicle, 1.39f);

            if (g_settings.options["Auto Get-in"])
            {
                PED::SET_PED_INTO_VEHICLE(g_local.ped, vehicle, -1);
                STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
                GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
                GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_clown_appears", vehicle, 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.6, false, false, false);
            }

            if (g_settings.options["Full Upgrade Bool"])
            {
                VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_XENONHEADLIGHTS, TRUE);
                VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_TURBO, TRUE);
                VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 0, TRUE);
                VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 1, TRUE);
                VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 2, TRUE);
                VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 3, TRUE);
                VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(vehicle, NEON_COLOR_RED);
                VEHICLE::_SET_VEHICLE_XENON_LIGHTS_COLOR(vehicle, 8);
                VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);

                for (int i = 0; i < 50; i++)
                {
                    VEHICLE::SET_VEHICLE_MOD(vehicle, i, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, i) - 1, TRUE);
                }
                VEHICLE::SET_VEHICLE_WHEEL_TYPE(vehicle, 9);
                VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_FRONTWHEEL, 52, TRUE);
            }

            if (VEHICLE::IS_THIS_MODEL_A_PLANE(rage::joaat(name)))
            {
                VEHICLE::SET_PLANE_TURBULENCE_MULTIPLIER(vehicle, 0.0f);
            }
        } QUEUE_JOB_END_CLAUSE
    }

    void vehicle_helper::swam(const char* name, Entity entity)
    {
        QUEUE_JOB_BEGIN_CLAUSE(name, entity)
        {
            auto pos = ENTITY::GET_ENTITY_COORDS(entity, TRUE);
            auto forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity);
            auto heading = ENTITY::GET_ENTITY_HEADING(entity);

            Hash hash_vehicle = controller::load(name);

            pos.x += 20.0f * forward.x;
            pos.y += 20.0f * forward.y;
            pos.z += VEHICLE::IS_THIS_MODEL_A_PLANE(hash_vehicle) || VEHICLE::IS_THIS_MODEL_A_HELI(hash_vehicle) ? 120.0f : 0;

            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
            auto plane = VEHICLE::CREATE_VEHICLE(hash_vehicle, pos.x, pos.y, pos.z, heading, TRUE, TRUE, FALSE);
            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

            VEHICLE::TOGGLE_VEHICLE_MOD(plane, MOD_XENONHEADLIGHTS, TRUE);
            VEHICLE::TOGGLE_VEHICLE_MOD(plane, MOD_TURBO, TRUE);
            VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(plane, 0, TRUE);
            VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(plane, 1, TRUE);
            VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(plane, 2, TRUE);
            VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(plane, 3, TRUE);
            VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(plane, NEON_COLOR_RED);
            VEHICLE::_SET_VEHICLE_XENON_LIGHTS_COLOR(plane, 8);
            VEHICLE::SET_VEHICLE_MOD_KIT(plane, 0);

            for (int i = 0; i < 50; i++)
            {
                VEHICLE::SET_VEHICLE_MOD(plane, i, VEHICLE::GET_NUM_VEHICLE_MODS(plane, i) - 1, TRUE);
            }
            VEHICLE::SET_VEHICLE_WHEEL_TYPE(plane, 9);
            VEHICLE::SET_VEHICLE_MOD(plane, MOD_FRONTWHEEL, 52, TRUE);

            script::get_current()->yield();
            //PED_TYPE_ARMY = 29 //PED_TYPE_SWAT = 27,  
            Hash hash_ped = controller::load("s_m_y_swat_01");
            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
            auto pilot = PED::CREATE_PED_INSIDE_VEHICLE(plane, 29, hash_ped, -1, TRUE, TRUE);
            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

            //3: Retracted 
            float speed = VEHICLE::IS_THIS_MODEL_A_PLANE(hash_vehicle) || VEHICLE::IS_THIS_MODEL_A_HELI(hash_vehicle) ? 100.f : 1.f;
            VEHICLE::CONTROL_LANDING_GEAR(plane, 3);
            VEHICLE::SET_VEHICLE_ENGINE_ON(plane, TRUE, TRUE, FALSE);
            VEHICLE::SET_VEHICLE_FORWARD_SPEED(plane, speed);

            TASK::TASK_PLANE_CHASE(pilot, entity, 0.0f, 0.0f, 0.0f);
            TASK::TASK_COMBAT_PED(pilot, entity, 0, 16);
            if (g_toggle.godmode)
            {
                ENTITY::SET_ENTITY_INVINCIBLE(plane, TRUE);
                ENTITY::SET_ENTITY_INVINCIBLE(pilot, TRUE);
            }

        } QUEUE_JOB_END_CLAUSE
    }

	void vehicle_helper::add_clan_logo_to_vehicle(Vehicle vehicle, Ped ped)
	{
		rage::vector3 x, y, z;
		float scale;
		Hash modelHash = ENTITY::GET_ENTITY_MODEL(vehicle);
		if (GetVehicleInfoForClanLogo(modelHash, x, y, z, scale))
		{
			int alpha = 200;
			if (modelHash == VEHICLE_WINDSOR || modelHash == VEHICLE_COMET4)
				alpha = 255;

			GRAPHICS::ADD_VEHICLE_CREW_EMBLEM(vehicle, ped, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "chassis_dummy"), x.x, x.y, x.z, y.x, y.y, y.z, z.x, z.y, z.z, scale, 0, alpha);
			if (y.z >= 0.0f)
				GRAPHICS::ADD_VEHICLE_CREW_EMBLEM(vehicle, ped, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "chassis_dummy"), x.x * -1.0f, x.y, x.z, y.x * -1.0f, y.y, y.z, z.x * -1.0f, z.y * -1.0f, z.z, scale, 1, alpha);
		}
	}

	void vehicle_helper::set_mp_parameters_for_vehicle(Vehicle vehicle)
	{
		DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
		auto networkId = NETWORK::VEH_TO_NET(vehicle);
		if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
			NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
		VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
	}

	Vehicle vehicle_helper::create_vehicle(Hash modelHash, float x, float y, float z, float heading)
	{
		*script_global(4533757).as<bool*>() = true;
		while (!STREAMING::HAS_MODEL_LOADED(modelHash))
		{
			STREAMING::REQUEST_MODEL(modelHash);
			script::get_current()->yield();
		}
		*(unsigned short*)big::g_pointers->m_model_spawn_bypass = 0x9090;
		Vehicle vehicle = VEHICLE::CREATE_VEHICLE(modelHash, x, y, z, heading, TRUE, FALSE, FALSE);
		*(unsigned short*)big::g_pointers->m_model_spawn_bypass = 0x0574;
		script::get_current()->yield(); //This allows the car to initalize so when we write things like radio station, it will overwrite.

		
		ENTITY::_SET_ENTITY_SOMETHING(vehicle, TRUE);

        if (g_settings.options["Auto Get-in"])
        {
            STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
            GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
            GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_clown_appears", vehicle, 0.0f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.6f, false, false, false);

            PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);
        }

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(modelHash);
		if (*big::g_pointers->m_is_session_started)
			set_mp_parameters_for_vehicle(vehicle);
		return vehicle;
	}

    void vehicle_helper::attach_vehicle(const char* vehicle_name, Player player)
    {
        QUEUE_JOB_BEGIN_CLAUSE(=)
        {
            if (!*g_pointers->m_is_session_started) *script_global(4270934).as<bool*>() = true;
            auto entity = player::get_player_ped(player);
            auto pos = ENTITY::GET_ENTITY_COORDS(entity, TRUE);
            auto forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity);
            auto heading = ENTITY::GET_ENTITY_HEADING(entity);

            pos.x += player_list::DISTANCE_SPAWN * forward.x;
            pos.y += player_list::DISTANCE_SPAWN * forward.y;

            Hash hash_vehicle = controller::load(vehicle_name);//load(name);

            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
            auto vehicle = VEHICLE::CREATE_VEHICLE(hash_vehicle, pos.x, pos.y, pos.z + 1, heading + 90.0f, TRUE, TRUE, FALSE);
            *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

            script::get_current()->yield();

            if (*g_pointers->m_is_session_started)
            {
                DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
                ENTITY::_SET_ENTITY_SOMETHING(vehicle, TRUE); //True means it can be deleted by the engine when switching lobbies/missions/etc, false means the script is expected to clean it up.
                auto networkId = NETWORK::VEH_TO_NET(vehicle);
                if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
                    NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
                VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
            }

            ENTITY::ATTACH_ENTITY_TO_ENTITY(vehicle, entity, SKEL_Spine0, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, FALSE, FALSE, TRUE, FALSE, 2, TRUE);
            ENTITY::SET_ENTITY_ALPHA(vehicle, 10, TRUE);
            ENTITY::SET_ENTITY_COLLISION(vehicle, FALSE, FALSE);
            ENTITY::SET_ENTITY_INVINCIBLE(vehicle, TRUE);

            if (VEHICLE::IS_THIS_MODEL_A_PLANE(hash_vehicle))
            {
                VEHICLE::SET_PLANE_TURBULENCE_MULTIPLIER(vehicle, 0.0f);
            }
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash_vehicle);
        }
        QUEUE_JOB_END_CLAUSE
    }
}