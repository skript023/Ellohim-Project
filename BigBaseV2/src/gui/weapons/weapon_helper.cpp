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
#include <gta/Weapons.h>
#include <gui/weapons/weapon_helper.h>
#include <gui/controller/game_variable.h>
#include <gui/player/player_option.h>
#include "gui/controller/memory_address.hpp"
#include "gui/controller/network_controller.h"
#include "gui/controller/system_control.h"

namespace big
{
    void weapon_helper::set_super_jump_this_frame(Player player, bool activation)
    {
        if (activation)
        {
            if (auto ped = g_pointers->m_player_ptr(player))
            {
                ped->m_playerinfo->m_frame_flags |= (1 << 14);
            }
        }
    }

    void weapon_helper::set_explosive_melee_this_frame(Player player, bool activation)
    {
        if (activation)
        {
            if (auto ped = g_pointers->m_player_ptr(player))
            {
                ped->m_playerinfo->m_frame_flags |= (1 << 13);
            }
        }
    }

    void weapon_helper::set_fire_ammo_this_frame(Player player, bool activation)
    {
        if (activation)
        {
            if (auto ped = g_pointers->m_player_ptr(player))
            {
                ped->m_playerinfo->m_frame_flags |= (1 << 12);
            }
        }
    }

    void weapon_helper::set_explosive_ammo_this_frame(Player player, bool activation)
    {
        if (activation)
        {
            if (auto ped = g_pointers->m_player_ptr(player))
            {
                ped->m_playerinfo->m_frame_flags |= (1 << 11);
            }
        }
    }

    std::string weapon_helper::get_weapon_name_from_hash(Hash weaponHash)
    {
        switch (weaponHash) 
        {
            case WEAPON_UNARMED:
                return "Unarmed";
            case WEAPON_KNIFE:
                return "Knife";
            case WEAPON_NIGHTSTICK:
                return "Nightstick";
            case WEAPON_HAMMER:
                return "Hammer";
            case WEAPON_BAT:
                return "Bat";
            case WEAPON_GOLFCLUB:
                return "GolfClub";
            case WEAPON_CROWBAR:
                return "Crowbar";
            case WEAPON_PISTOL:
                return "Pistol";
            case WEAPON_PISTOL_MK2:
                return "Pistol MK2";
            case WEAPON_COMBATPISTOL: 
                return "Combat Pistol";
            case WEAPON_APPISTOL: 
                return "AP Pistol";
            case WEAPON_PISTOL50: 
                return "Pistol 50";
            case WEAPON_MICROSMG: 
                return "Micro SMG";
            case WEAPON_SMG: 
                return "SMG";
            case WEAPON_SMG_MK2:
                return "SMG MK2";
            case WEAPON_ASSAULTSMG: 
                return "Assault SMG";
            case WEAPON_ASSAULTRIFLE:
                return "Assault Riffle";
            case WEAPON_ASSAULTRIFLE_MK2:
                return "Assault Rifle MK2";
            case WEAPON_CARBINERIFLE: 
                return "Carbine Riffle";
            case WEAPON_CARBINERIFLE_MK2:
                return "Carbine Riffle MK2";
            case WEAPON_ADVANCEDRIFLE: 
                return "Advanced Riffle";
            case WEAPON_MG: 
                return "MG";
            case WEAPON_COMBATMG: 
                return "Combat MG";
            case WEAPON_COMBATMG_MK2:
                return "Combat MG MK2";
            case WEAPON_PUMPSHOTGUN: 
                return "Pump Shotgun";
            case WEAPON_PUMPSHOTGUN_MK2:
                return "Pump Shotgun MK2";
            case WEAPON_SAWNOFFSHOTGUN: 
                return "Sawed-Off Shotgun";
            case WEAPON_ASSAULTSHOTGUN: 
                return "Assault Shotgun";
            case WEAPON_BULLPUPSHOTGUN: 
                return "Bullpup Shotgun";
            case WEAPON_STUNGUN: 
                return "Stun Gun";
            case WEAPON_SNIPERRIFLE: 
                return "Sniper Rifle";
            case WEAPON_HEAVYSNIPER: 
                return "Heavy Sniper";
            case WEAPON_HEAVYSNIPER_MK2:
                return "Heavy Sniper MK2";
            case WEAPON_GRENADELAUNCHER: 
                return "Grenade Launcher";
            case WEAPON_GRENADELAUNCHER_SMOKE: 
                return "Smoke Grenade Launcher";
            case WEAPON_RPG: 
                return "RPG";
            case WEAPON_MINIGUN: 
                return "Minigun";
            case WEAPON_GRENADE: 
                return "Grenade";
            case WEAPON_STICKYBOMB: 
                return "Sticky Bomb";
            case WEAPON_SMOKEGRENADE: 
                return "Smoke Grenade";
            case WEAPON_BZGAS: 
                return "BZGas";
            case WEAPON_MOLOTOV: 
                return "Molotov";
            case WEAPON_FIREEXTINGUISHER: 
                return "Fire Extinguisher";
            case WEAPON_PETROLCAN: 
                return "Petrol Can";
            case 0xFDBADCED: 
                return "Digital scanner";
            case 0x88C78EB7: 
                return "Briefcase";
            case WEAPON_BALL: 
                return "Ball";
            case WEAPON_FLARE: 
                return "Flare";
            case WEAPON_BOTTLE: 
                return "Bottle";
            case WEAPON_GUSENBERG: 
                return "Gusenberg";
            case WEAPON_SPECIALCARBINE: 
                return "Special Carabine";
            case WEAPON_SPECIALCARBINE_MK2:
                return "Special Carabine MK2";
            case WEAPON_HEAVYPISTOL: 
                return "Heavy Pistol";
            case WEAPON_SNSPISTOL: 
                return "SNS Pistol";
            case WEAPON_SNSPISTOL_MK2:
                return "SNS Pistol MK2";
            case WEAPON_BULLPUPRIFLE: 
                return "Bullpup Rifle";
            case WEAPON_BULLPUPRIFLE_MK2:
                return "Bullpup Rifle MK2";
            case WEAPON_DAGGER: 
                return "Dagger";
            case WEAPON_VINTAGEPISTOL: 
                return "Vintage Pistol";
            case WEAPON_FIREWORK: 
                return "Firework";
            case WEAPON_MUSKET: 
                return "Musket";
            case WEAPON_HEAVYSHOTGUN: 
                return "Heavy Shotgun";
            case WEAPON_MARKSMANRIFLE: 
                return "Marksman Rifle";
            case WEAPON_MARKSMANRIFLE_MK2:
                return "Marksman Rifle MK2";
            case WEAPON_HOMINGLAUNCHER: 
                return "Homing Launcher";
            case WEAPON_PROXMINE: 
                return "Proximity Mine";
            case WEAPON_SNOWBALL: 
                return "Snowball";
            case WEAPON_FLAREGUN: 
                return "Flare Gun";
            case 0xE232C28C: 
                return "Garbage Bag";
            case 0xD04C944D: 
                return "Handcuffs";
            case WEAPON_COMBATPDW: 
                return "Combat PDW";
            case WEAPON_MARKSMANPISTOL: 
                return "Marksman Pistol";
            case WEAPON_KNUCKLE: 
                return "Brass Knuckles";
            case WEAPON_RAILGUN:
                return "Railgun";
            case WEAPON_REVOLVER:
                return "Revolver";
            case WEAPON_REVOLVER_MK2:
                return "Revolver MK2";
            case WEAPON_COMBATSHOTGUN:
                return "Combat Shogun";
            case WEAPON_GADGETPISTOL:
                return "Perico Pistol";
            case WEAPON_MILITARYRIFLE:
                return "Military Rifle";
        }
        return "Unarmed";
    }

    void weapon_helper::teleport_gun(bool activation)
    {
        g_fiber_pool->queue_job([activation] {
            if (activation && (PAD::IS_CONTROL_PRESSED(0, INPUT_ATTACK)) && player::is_ped_shooting(g_local.ped))
            {
                auto last_aimed_coords = rage_helper::get_local_playerinfo()->m_last_aimed_coords;
                ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_local.ped, last_aimed_coords.x, last_aimed_coords.y, last_aimed_coords.z, TRUE, TRUE, FALSE);
            }
        });
    }

    void weapon_helper::set_bullet_batch_spread(Player player, float spread)
    {
        if (auto local_ped = rage_helper::get_player_pointer(player))
        {
            if (auto weapon_mgr = local_ped->m_weapon_mgr)
            {
                if (auto weapon_info = weapon_mgr->m_weapon_info)
                {
                    weapon_info->m_batch_spread = spread;
                }
            }
        }
    }

    void weapon_helper::set_bullet_batch(Player player, int sharpnell)
    {
        if (auto local_ped = rage_helper::get_player_pointer(player))
        {
            if (auto weapon_mgr = local_ped->m_weapon_mgr)
            {
                if (auto weapon_info = weapon_mgr->m_weapon_info)
                {
                    weapon_info->m_bullet_batch = sharpnell;
                }
            }
        }
    }

    int weapon_helper::get_bullet_batch(Player player)
    {
        if (auto local_ped = rage_helper::get_player_pointer(player))
        {
            if (auto weapon_mgr = local_ped->m_weapon_mgr)
            {
                if (auto weapon_info = weapon_mgr->m_weapon_info)
                {
                    return weapon_info->m_bullet_batch;
                }
            }
        }
        return 0;
    }

    float weapon_helper::get_bullet_batch_spread(Player player)
    {
        if (auto local_ped = rage_helper::get_player_pointer(player))
        {
            if (auto weapon_mgr = local_ped->m_weapon_mgr)
            {
                if (auto weapon_info = weapon_mgr->m_weapon_info)
                {
                    return weapon_info->m_batch_spread;
                }
            }
        }
        return 0.f;
    }

    void  weapon_helper::no_recoil(bool activation)
    {
        static Hash old_current_weapon = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_hash;
        Hash current_weapon = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_hash;
        static auto old_recoil = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_recoil;
        if (activation)
        {
            if (WEAPON::IS_PED_ARMED(g_local.ped, 4))
            {
                if (old_current_weapon == current_weapon)
                {
                    rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_recoil = 0.f;
                }
                if (old_current_weapon != current_weapon)
                {
                    rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_recoil = old_recoil;
                    old_recoil = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_recoil;
                    old_current_weapon = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_hash;
                }
            }
        }
        else
        {
            rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_recoil = old_recoil;
            old_recoil = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_recoil;
            old_current_weapon = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_hash;
        }
    }

    void  weapon_helper::no_spread(bool activation)
    {
        static Hash old_current_weapon = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_hash;
        Hash current_weapon = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_hash;
        static auto old_spread = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_spread;

        if (activation)
        {
            if (WEAPON::IS_PED_ARMED(g_local.ped, 4))
            {
                if (old_current_weapon == current_weapon)
                {
                    rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_spread = 0.f;
                }
                if (old_current_weapon != current_weapon)
                {
                    rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_spread = old_spread;
                    old_spread = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_spread;
                    old_current_weapon = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_hash;
                }
            }
        }
        else
        {
            rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_spread = old_spread;
            old_spread = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_spread;
            old_current_weapon = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_hash;
        }
    }

    void weapon_helper::burst_weapon_ammo(bool activation)
    {
        Hash current_weapon = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_hash;
        static Hash old_weapon = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_hash;
        static auto old_batch = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_bullet_batch;
        static auto old_spread = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_batch_spread;
        if (activation)
        {
            if (WEAPON::IS_PED_ARMED(g_local.ped, 4))
            {
            
                if (old_weapon == current_weapon)
                {
                    rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_bullet_batch = 300;
                    rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_batch_spread = 0.5f;
                }
            }
            if (old_weapon != current_weapon)
            {
                rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_bullet_batch = old_batch;
                rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_batch_spread = old_spread;
                old_batch = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_bullet_batch;
                old_spread = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_batch_spread;
                old_weapon = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_hash;
            }
        }
        else
        {
            old_batch = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_bullet_batch;
            old_spread = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_batch_spread;
            old_weapon = rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_weapon_hash;
            rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_bullet_batch = old_batch;
            rage_helper::get_local_ped()->m_weapon_mgr->m_weapon_info->m_batch_spread = old_spread;
        }
    }

    bool weapon_helper::is_model_shotgun(Hash hash)
    {
        for (int i = 0; i <= arraysize(game_variable::weapon_shotgun); i++)
        {
            if (hash == game_variable::weapon_shotgun[i]) return true;
        }
        return false;
    }

    void weapon_helper::object_guns(bool Activation)
    {
        if (Activation)
        {
            if (player::is_ped_shooting(PLAYER::PLAYER_PED_ID()))
            {
                Ped entity = PLAYER::PLAYER_PED_ID();
                float offset;
                Vector3 dim1, dim2;

                offset = dim2.y * 1.6f;

                auto pos = ENTITY::GET_ENTITY_COORDS(entity, TRUE);
                auto forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity);
                auto heading = ENTITY::GET_ENTITY_ROTATION(entity, 2);

                pos.x += DISTANCE_SPAWN * forward.x;
                pos.y += DISTANCE_SPAWN * forward.y;

                Hash hash_object = controller::load("prop_bank_vaultdoor");
                MISC::GET_MODEL_DIMENSIONS(hash_object, &dim1, &dim2);

                *(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
                auto obj = OBJECT::CREATE_OBJECT(hash_object, pos.x, pos.y, pos.z, TRUE, FALSE, TRUE);
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
                ENTITY::APPLY_FORCE_TO_ENTITY(obj, 1, 0.0f, 13.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, FALSE, TRUE, TRUE, FALSE, TRUE);
                STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash_object);
            }
        }
    }

    void weapon_helper::ghost_guns(bool Activation)
    {
        Entity EntityID;
        if (Activation && (PAD::IS_CONTROL_PRESSED(0, INPUT_ATTACK)))
        {
            if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &EntityID))
            {
                if (ENTITY::DOES_ENTITY_EXIST(EntityID))
                {
                    network::request_control(EntityID);
                    ENTITY::SET_ENTITY_ALPHA(EntityID, 102, FALSE);
                    ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(PLAYER::PLAYER_PED_ID(), EntityID, FALSE);
                }
            }
        }
    }

    void weapon_helper::removal_gun(bool activation)
    {
        Entity EntityID;
        if ((activation) && (PAD::IS_CONTROL_PRESSED(0, INPUT_ATTACK)))
        {
            if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &EntityID))
            {
                if (ENTITY::DOES_ENTITY_EXIST(EntityID))
                {
                    network::request_control(EntityID);
                    ENTITY::SET_ENTITY_COORDS(EntityID, 0, 0, -100, 0, 0, 0, 0);
                    NETWORK::NETWORK_FADE_OUT_ENTITY(EntityID, 0, 0);
                    ENTITY::SET_ENTITY_AS_MISSION_ENTITY(EntityID, TRUE, TRUE);
                    ENTITY::DELETE_ENTITY(&EntityID);
                }
            }
        }
    }

    void infinite_ammo(bool activation)
    {
        rage_helper::get_local_ped()->m_weapon_inventory->m_weapon_ammo_flag = activation;//Memory::set_value(g_ptr.WorldPTR, { 0x8, 0x10D0, 0x78 }, type);
    }

    void weapon_helper::revenge(Hash Weapon, bool Activation)
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

    void weapon_helper::headshot_all_npc(bool Activation)
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
                    network::request_control(ped);
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

    void weapon_helper::explosive_ammo(bool Activation, Ped Target)
    {
        if (Activation)
        {
            if (player::is_ped_shooting(Target))
            {
                Vector3 pos;
                if (get_last_impact_coords(Target, &pos))
                {
                    if (!systems::is_3d_vector_zero(pos))
                    {
                        *(PWORD)g_pointers->m_add_owned_explosion_bypass_1 = 0xE990;
                        *(PWORD)g_pointers->m_add_owned_explosion_bypass_2 = 0x9090;
                        FIRE::ADD_OWNED_EXPLOSION(Target, pos.x, pos.y, pos.z, EXPLOSION_TRAIN, 1000.0f, TRUE, FALSE, 1.5f);
                        *(PWORD)g_pointers->m_add_owned_explosion_bypass_1 = 0x850F;
                        *(PWORD)g_pointers->m_add_owned_explosion_bypass_2 = 0x0E74;
                    }
                }
            }
        }
    }

    Vector3 weapon_helper::get_last_impact_coords(Ped Ped)
    {
        if (auto ped = rage_helper::entity_to_pointer<CPed*>(Ped))
        {
            return systems::to_scr_vector(ped->m_weapon_mgr->m_last_impact_coords);
        }

        return Vector3(0.f, 0.f, 0.f);
    }

    bool weapon_helper::get_last_impact_coords(Ped ped, Vector3 *coords)
    {
        if (auto local_ped = rage_helper::entity_to_pointer<CPed*>(ped))
        {
            *coords = systems::to_scr_vector(local_ped->m_weapon_mgr->m_last_impact_coords);

            return true;
        }

        return false;
    }

    bool weapon_helper::get_last_aimed_coords(Ped ped, Vector3* coords)
    {
        if (auto local_ped = rage_helper::entity_to_pointer<CPed*>(ped))
        {
            *coords = systems::to_scr_vector(local_ped->m_playerinfo->m_last_aimed_coords);

            return true;
        }

        return false;
    }

    void weapon_helper::infinite_ammo(bool Activation)
    {
        if (Activation)
        {
            for (auto weapon : game_variable::weapon_hash_list)
            {
                if (WEAPON::IS_WEAPON_VALID(rage::joaat(weapon)))
                {
                    WEAPON::SET_PED_INFINITE_AMMO(PLAYER::PLAYER_PED_ID(), true, rage::joaat(weapon));
                }
            }
        }
        else
        {
            for (auto weapon : game_variable::weapon_hash_list)
            {
                if (WEAPON::IS_WEAPON_VALID(rage::joaat(weapon)))
                {
                    WEAPON::SET_PED_INFINITE_AMMO(PLAYER::PLAYER_PED_ID(), false, rage::joaat(weapon));
                }
            }
        }
    }

    void weapon_helper::rapid_fire(bool toggle)
    {
        if (toggle)
        {
            Player playerPed = PLAYER::PLAYER_PED_ID();
            if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), TRUE)) 
            {
                PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), TRUE);
                Vector3 gameplayCam = CAM::GET_GAMEPLAY_CAM_COORD();
                Vector3 gameplayCamRot = CAM::GET_GAMEPLAY_CAM_ROT(0);
                Vector3 gameplayCamDirection = rotation_to_direction(gameplayCamRot);
                Vector3 startCoords = add_vector(gameplayCam, (multiply_vector(gameplayCamDirection, 1.0f)));
                Vector3 endCoords = add_vector(startCoords, multiply_vector(gameplayCamDirection, 500.0f));
                Hash weaponhash;
                WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &weaponhash, 1);
                if (PAD::IS_CONTROL_PRESSED(2, 208) || (GetKeyState(VK_LBUTTON) & 0x8000))
                {
                    MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(startCoords.x, startCoords.y, startCoords.z, endCoords.x, endCoords.y, endCoords.z, 50, TRUE, weaponhash, playerPed, TRUE, TRUE, 0xbf800000);
                }
            }
        }
    }

    void weapon_helper::weapon_blackhole()
    {
        weapon_helper::teleport_gun(g_weapon_option.teleport_gun_bool);
        weapon_helper::no_spread(g_weapon_option.spread_on);
        weapon_helper::no_recoil(g_weapon_option.recoil_on);
        weapon_helper::rapid_fire(g_weapon_option.rapid_shoot);
        weapon_helper::headshot_all_npc(g_weapon_option.auto_headshot);
        weapon_helper::revenge(rage::joaat(game_variable::revenge_list[g_weapon_option.weapon_hash]), g_weapon_option.weapon_hash != 0);
        WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), g_settings.options["Infinite Clip"]);

        weapon_helper::infinite_ammo(g_settings.options["Infinite Ammo"]);
        weapon_helper::explosive_ammo(g_weapon_option.explosive_weapon, player::get_player_ped(g_selected.player));
        weapon_helper::object_guns(g_weapon_option.object_gun);
        weapon_helper::removal_gun(g_weapon_option.delete_gun);
        weapon_helper::ghost_guns(g_weapon_option.ghost_gun);

        weapon_helper::set_explosive_ammo_this_frame(PLAYER::PLAYER_ID(), g_weapon_option.explosives_ammo);
        weapon_helper::set_fire_ammo_this_frame(PLAYER::PLAYER_ID(), g_weapon_option.fire_ammo);
        weapon_helper::set_super_jump_this_frame(PLAYER::PLAYER_ID(), g_weapon_option.super_jump);
        weapon_helper::set_explosive_melee_this_frame(PLAYER::PLAYER_ID(), g_weapon_option.explosive_fist);
    }
}