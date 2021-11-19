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
#include "gui/entity/entity_control.h"
#include "gui/object/object.h"
#include "gui/controller/memory_address.hpp"
#include "gui/controller/system_control.h"
#include "gta/net_object_mgr.hpp"
#include "gui/weapons/weapon_helper.h"
#include "gui/vehicle/vehicle_helper.h"
#include "gui/artificial_intelligence/artificial_intelligence.h"
#include "gui/controller/http_request.hpp"

#define ARRAY_SIZE(_ARR)          ((int)(sizeof(_ARR) / sizeof(*(_ARR))))
#define ARR_SZ(_ARR)              ((int)(sizeof(_ARR) / sizeof((_ARR)[0])))

namespace big
{
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
                message::notification("~bold~~g~Ellohim Private Menu", "~bold~~g~Your RP no longer need correction", "~bold~~g~Ellohim Recovery");
            }
            else if (global_exp != total)
            {
                STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_GLOBALXP"), total, true);
                message::notification("~bold~~g~Ellohim Private Menu", "~bold~~g~Your RP Has Been Corrected", "~bold~~g~Ellohim Recovery");
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
        for (auto ped : var::PedList)
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

            Vector3 pos = ENTITY::GET_ENTITY_COORDS(e, false);
            ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, pos.x, pos.y, pos.z, false, false, false);
            if (GetAsyncKeyState(systems::hotkey('S')))
            {
                float fivef = .5f;
                float heading = ENTITY::GET_ENTITY_HEADING(e);
                float xVec = fivef * sin(systems::degree(heading)) * -1.5f;
                float yVec = fivef * cos(systems::degree(heading));
                ENTITY::SET_ENTITY_HEADING(e, heading);

                pos.x -= xVec, pos.y -= yVec;
                ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, pos.x, pos.y, pos.z, false, false, false);
            }
            if (GetAsyncKeyState(systems::hotkey('W')))
            {
                float fivef = .5f;
                float heading = ENTITY::GET_ENTITY_HEADING(e);
                float xVec = fivef * sin(systems::degree(heading)) * -1.5f;
                float yVec = fivef * cos(systems::degree(heading));
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
        else if (!Trigger)
        {
            *script_global(262145).at(87).as<int*>() = 120000;
            *script_global(262145).at(88).as<int*>() = 300000;
            *script_global(262145).at(89).as<int*>() = 600000;
            *script_global(262145).at(90).as<int*>() = 900000;
        }
    }

    void player::AutoHeal(bool Activation)
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

    void player::PlayerHealthRegen(bool Activation)
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

    void player::NeverWanted(bool Activation)
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

    void player::AllMissionLives(bool Activation)
    {
        if (Activation)
        {
            if (systems::is_script_active(RAGE_JOAAT("fm_mission_controller")))
            {
                rage_helper::execute_as_script(RAGE_JOAAT("fm_mission_controller"), [] {
                    if (auto fm_mission_controller = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller")))
                    {
                        *script_local(fm_mission_controller, m_local.tc_live).as<int*>() = 9999;
                    }
                });
            }
            else if (systems::is_script_active(RAGE_JOAAT("fm_mission_controller_2020")))
            {
                rage_helper::execute_as_script(RAGE_JOAAT("fm_mission_controller_2020"), [] {
                    if (auto mission_controller_2020 = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")))
                    {
                        *script_local(mission_controller_2020, m_local.tc_live_c).as<int*>() = 9999;
                    }
                });
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

    void player::SetPlayerSeatBelt(bool Activation)
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
            if (Activation && !player_ped->is_water_proof())
            {
                player_ped->enable_water_proof();// = 0x1000000;
            }
            else if (!Activation && player_ped->is_water_proof())
            {
                player_ped->disable_water_proof();// = 0x4194316;
            }
        }
    }

    void player::BlindCops(bool Activation)
    {
        if (Activation)
        {
            *script_global(2544210).at(4623).as<int*>() = 1;
            *script_global(2544210).at(4625).as<int*>() = NETWORK::GET_NETWORK_TIME();
            *script_global(2544210).at(4622).as<int*>() = 5;
        }
        else
        {
            *script_global(2544210).at(4623).as<int*>() = 0;
            *script_global(2544210).at(4625).as<int*>() = 0;
            *script_global(2544210).at(4622).as<int*>() = 0;
        }
    }

    void player::RevealRadar(bool Activation)
    {
        if (Activation)
        {
            *script_global(2426865).at(PLAYER::PLAYER_ID(), 449).at(212).as<int*>() = 1;
            *script_global(2441237).at(71).as<int*>() = NETWORK::GET_NETWORK_TIME();
        }
        else
        {
            *script_global(2426865).at(PLAYER::PLAYER_ID(), 449).at(212).as<int*>() = 0;
            *script_global(2441237).at(71).as<int*>() = NETWORK::GET_NETWORK_TIME();
        }
    }

    void player::OffTheRadar(bool Activation)
    {
        if (Activation)
        {
            *script_global(2426865).at(PLAYER::PLAYER_ID(), 449).at(209).as<int*>() = 1;
            *script_global(2441237).at(70).as<int*>() = NETWORK::GET_NETWORK_TIME();
            *script_global(2544210).at(4628).as<int*>() = 3;
        }
        else
        {
            *script_global(2426865).at(PLAYER::PLAYER_ID(), 449).at(209).as<int*>() = 0;
            *script_global(2441237).at(70).as<int*>() = 0;
            *script_global(2544210).at(4628).as<int*>() = 0;
        }
    }

    void player::GhostOrganization(bool Activation)
    {
        if (Activation)
        {
            *script_global(2426865).at(PLAYER::PLAYER_ID(), 449).at(209).as<int*>() = 1;
            *script_global(2441237).at(70).as<int*>() = NETWORK::GET_NETWORK_TIME();
            *script_global(2544210).at(4628).as<int*>() = 4;
        }
        else
        {
            *script_global(2426865).at(PLAYER::PLAYER_ID(), 449).at(209).as<int*>() = 0;
            *script_global(2441237).at(70).as<int*>() = 0;
            *script_global(2544210).at(4628).as<int*>() = 0;
        }
    }

    void player::SetPlayerNoCollision(bool Activation)
    {
        if (Activation)
        {
            rage_helper::get_local_ped()->m_navigation->m_ph_arche->m_ph_bound->m_ph_composite->m_ph_geometry[0x0]->m_collision = -1.0f;//Memory::set_value(g_ptr.WorldPTR, { 0x8, 0x30, 0x10, 0x20, 0x70, 0x0, 0x2C }, -1.0f);
        }
        else
        {
            rage_helper::get_local_ped()->m_navigation->m_ph_arche->m_ph_bound->m_ph_composite->m_ph_geometry[0x0]->m_collision = 0.25f;//Memory::set_value(g_ptr.WorldPTR, { 0x8, 0x30, 0x10, 0x20, 0x70, 0x0, 0x2C }, 0.25f);
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
                LOG(HACKER) << g_pointers->m_player_crew->get_crew_tag(i);
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
            *script_global(1590908).at(g_local.player, 874).at(205).at(6).as<int*>() = level;
        }
    }

    void spoofer::player_money(bool activation, int money)
    {
        if (activation)
        {
            *script_global(1590908).at(g_local.player, 874).at(205).at(56).as<int*>() = money;
        }
    }

    void outfit::changeAppearance(char* family, int model, int texture)
    {
        if (controller::cstrcmp(family, "HATS") || controller::cstrcmp(family, "GLASSES") || controller::cstrcmp(family, "EARS") || controller::cstrcmp(family, "WATCH") || controller::cstrcmp(family, "BRACELET"))
        {
            if (controller::cstrcmp(family, "HATS"))
                big::player_list::fam = 0;
            else if (controller::cstrcmp(family, "GLASSES"))
                big::player_list::fam = 1;
            else if (controller::cstrcmp(family, "EARS"))
                big::player_list::fam = 2;
            else  if (controller::cstrcmp(family, "WATCH"))
                big::player_list::fam = 6;
            else if (controller::cstrcmp(family, "BRACELET"))
                big::player_list::fam = 7;
            PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), big::player_list::fam, model - 1, texture, 1);
        }
        else
        {
            if (controller::cstrcmp(family, "FACE"))
                big::player_list::fam = 0;
            else if (controller::cstrcmp(family, "MASK"))
                big::player_list::fam = 1;
            else if (controller::cstrcmp(family, "HAIR"))
                big::player_list::fam = 2;
            else if (controller::cstrcmp(family, "JACKET"))
                big::player_list::fam = 3;
            else if (controller::cstrcmp(family, "LEGS"))
                big::player_list::fam = 4;
            else if (controller::cstrcmp(family, "BACK"))
                big::player_list::fam = 5;
            else if (controller::cstrcmp(family, "SHOES"))
                big::player_list::fam = 6;
            else if (controller::cstrcmp(family, "ACCESSORY"))
                big::player_list::fam = 7;
            else if (controller::cstrcmp(family, "UNDERSHIRT"))
                big::player_list::fam = 8;
            else if (controller::cstrcmp(family, "KEVLAR"))
                big::player_list::fam = 9;
            else if (controller::cstrcmp(family, "BADGE"))
                big::player_list::fam = 10;
            else if (controller::cstrcmp(family, "TORSO2"))
                big::player_list::fam = 11;
            PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), big::player_list::fam, model, texture, 0);
        }
    }

    void outfit::ResetAppearance()
    {
        PED::CLEAR_ALL_PED_PROPS(PLAYER::PLAYER_PED_ID());
        PED::CLEAR_PED_DECORATIONS(PLAYER::PLAYER_PED_ID());
        PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 1, 0, 0, 0);
        PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 5, 0, 0, 0);
        PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), 9, 0, 0, 0);
    }

    void outfit::StealOutfit(Player player)
    {
        Ped their_ped = player::get_player_ped(player);
        for (int i = 0; i < 12; i++)
        {
            PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, PED::GET_PED_DRAWABLE_VARIATION(their_ped, i),
                PED::GET_PED_TEXTURE_VARIATION(their_ped, i),
                PED::GET_PED_PALETTE_VARIATION(their_ped, i));
        }
    }

    void player::RunSpeed(float speed)
    {
        rage_helper::get_local_playerinfo()->m_run_speed = speed;
    }

    void player::UltraRun(bool Activation)
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

    void player::SwimSpeed(float speed)
    {
        rage_helper::get_local_playerinfo()->m_swim_speed = speed;
    }

    void player::GiveHealAll(bool Activation)
    {
        if (Activation)
        {
            for (int i = 0; i <= g_local.connected_player; i++)
            {
                Ped ped = get_player_ped(i);
                auto GetHealth = ENTITY::GET_ENTITY_HEALTH(ped);
                if (GetHealth >= 100 && GetHealth < 200)
                {
                    if (ped != g_local.ped && ped != 0)
                    {
                        object::CreatePickup("PICKUP_HEALTH_STANDARD", "prop_ld_health_pack", 1, ped);
                        object::CreatePickup("PICKUP_ARMOUR_STANDARD", "prop_ld_armour", 1, ped);
                    }
                }
            }
        }
    }

    void player::SetPlayerLevel(int PlayerLevel)
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

    std::string player::get_player_ip(Player player)
    {
        uint32_t player_ip = 0;
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            player_ip = ped->m_playerinfo->m_online_ip;
        }
        return fmt::format("{}.{}.{}.{}", (player_ip >> 24) & 0xff, (player_ip >> 16) & 0xff, (player_ip >> 8) & 0xff, player_ip & 0xff);
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
        if (auto ped = rage_helper::get_player_pointer(player))
        {
            if (ped->m_is_in_vehicle)
            {
                if (auto vehicle = ped->m_last_vehicle)
                {
                    if (auto vehicle_info = vehicle->m_model_info)
                    {
                        return vehicle_info->m_vehicle_name;
                    }
                }
            }
        }
        return "Not In Vehicle";
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
}