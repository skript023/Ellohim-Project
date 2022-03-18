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
#include "gta/Weapons.h"
#include "gui/controller/game_variable.h"
#include "gui/controller/memory_address.hpp"
#include "system_control.h"
#include "gta/net_object_mgr.hpp"
#include "gui/sync_hash.hpp"
#include "gui/vehicle/vehicle_helper.h"
#include "gui/object/object.h"

namespace big
{
    void systems::auto_click(bool activate)
    {
        if (activate)
        {
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        }
    }

    void fire::add_owned_explosion(Ped ped, Vector3 pos, int explosionType, float damageScale, bool isAudible, bool isInvinsible, float ShakeCam)
    {
        *(PWORD)g_pointers->m_add_owned_explosion_bypass_1 = 0xE990;
        *(PWORD)g_pointers->m_add_owned_explosion_bypass_2 = 0x9090;
        FIRE::ADD_OWNED_EXPLOSION(ped, pos.x, pos.y, pos.z, explosionType, damageScale, isAudible, isInvinsible, ShakeCam);
        *(PWORD)g_pointers->m_add_owned_explosion_bypass_1 = 0x850F;
        *(PWORD)g_pointers->m_add_owned_explosion_bypass_2 = 0x0E74;
    }

    bool systems::is_model_valid(rage::netSyncTree* netSyncTree, rage::netObject* netObject)
    {
        auto player_hash = netSyncTree->m_sync_tree_node->m_player_model;
        auto ped_hash = netSyncTree->m_sync_tree_node->m_ped_model;
        auto obj_hash = netSyncTree->m_sync_tree_node->m_object_model;
        auto vehicle_hash = netSyncTree->m_sync_tree_node->m_vehicle_model;
        auto pickup_hash = netSyncTree->m_sync_tree_node->m_pickup_model;

        auto object_type = netObject->object_type;
        switch (object_type)
        {
        case NET_OBJ_TYPE_AUTOMOBILE:
            if (!systems::is_script_active(RAGE_JOAAT("fm_mission_controller") || !systems::is_script_active(RAGE_JOAAT("fm_mission_controller_2020"))))
            {
                for (auto obj : sync_car)
                {
                    if (vehicle_hash == obj)
                    {
                        return false;
                    }
                    else if (vehicle_hash != obj && systems::is_number_32_bit(vehicle_hash))
                    {
                        return false;
                    }
                }
            }
            break;
        case NET_OBJ_TYPE_BIKE:
            if (!systems::is_script_active(RAGE_JOAAT("fm_mission_controller") || !systems::is_script_active(RAGE_JOAAT("fm_mission_controller_2020"))))
            {
                for (auto obj : sync_bike)
                {
                    if (vehicle_hash == obj)
                    {
                        return false;
                    }
                    else if (vehicle_hash != obj && systems::is_number_32_bit(vehicle_hash))
                    {
                        return false;
                    }
                }
            }
            break;
        case NET_OBJ_TYPE_BOAT:
            if (!systems::is_script_active(RAGE_JOAAT("fm_mission_controller") || !systems::is_script_active(RAGE_JOAAT("fm_mission_controller_2020"))))
            {
                for (auto obj : sync_boat)
                {
                    if (vehicle_hash == obj)
                    {
                        return false;
                    }
                    else if (vehicle_hash != obj && systems::is_number_32_bit(vehicle_hash))
                    {
                        return false;
                    }
                }
            }
            break;
        case NET_OBJ_TYPE_DOOR:
            if (!systems::is_script_active(RAGE_JOAAT("fm_mission_controller") || !systems::is_script_active(RAGE_JOAAT("fm_mission_controller_2020"))))
            {
                for (auto obj : sync_door)
                {
                    if (player_hash == obj)
                    {
                        return false;
                    }
                    else if (vehicle_hash != obj && systems::is_number_32_bit(vehicle_hash))
                    {
                        return false;
                    }
                }
            }
            break;
        case NET_OBJ_TYPE_HELI:
            if (!systems::is_script_active(RAGE_JOAAT("fm_mission_controller") || !systems::is_script_active(RAGE_JOAAT("fm_mission_controller_2020"))))
            {
                for (auto obj : sync_heli)
                {
                    if (vehicle_hash == obj)
                    {
                        return false;
                    }
                    else if (vehicle_hash != obj && systems::is_number_32_bit(vehicle_hash))
                    {
                        return false;
                    }
                }
            }
            break;
        case NET_OBJ_TYPE_OBJECT:
            if (!systems::is_script_active(RAGE_JOAAT("fm_mission_controller") || !systems::is_script_active(RAGE_JOAAT("fm_mission_controller_2020"))))
            {
                for (auto obj : sync_objects)
                {
                    if (obj_hash == obj)
                    {
                        return false;//!rage::reverse_joaat(obj, obj_hash) &&
                    }
                    else if (obj_hash != obj && systems::is_number_32_bit(obj_hash))
                    {
                        return false;
                    }
                }
            }
            break;
        case NET_OBJ_TYPE_PED:
            if (!systems::is_script_active(RAGE_JOAAT("fm_mission_controller") || !systems::is_script_active(RAGE_JOAAT("fm_mission_controller_2020"))))
            {
                for (auto obj : sync_ped)
                {
                    if (ped_hash == RAGE_JOAAT("slod_human") || ped_hash == RAGE_JOAAT("slod_large_quadped") || ped_hash == RAGE_JOAAT("slod_small_quadped"))
                        return true;
                    else if (ped_hash == obj)
                        return false;
                }
            }
            break;
        case NET_OBJ_TYPE_PICKUP:
            return false;
        case NET_OBJ_TYPE_PICKUP_PLACEMENT:
            return false;
        case NET_OBJ_TYPE_PLANE:
            if (!systems::is_script_active(RAGE_JOAAT("fm_mission_controller") || !systems::is_script_active(RAGE_JOAAT("fm_mission_controller_2020"))))
            {
                for (auto obj : sync_plane)
                {
                    if (vehicle_hash == obj)
                    {
                        return false;
                    }
                    else if (vehicle_hash != obj && systems::is_number_32_bit(vehicle_hash))
                    {
                        return false;
                    }
                }
            }
            break;
        case NET_OBJ_TYPE_SUBMARINE:
            if (!systems::is_script_active(RAGE_JOAAT("fm_mission_controller") || !systems::is_script_active(RAGE_JOAAT("fm_mission_controller_2020"))))
            {
                for (auto obj : sync_submarine)
                {
                    if (vehicle_hash == obj)
                    {
                        return false;
                    }
                    else if (vehicle_hash != obj && systems::is_number_32_bit(vehicle_hash))
                    {
                        return false;
                    }
                }
            }
            break;
        case NET_OBJ_TYPE_PLAYER:
            if (!systems::is_script_active(RAGE_JOAAT("fm_mission_controller") || !systems::is_script_active(RAGE_JOAAT("fm_mission_controller_2020"))))
            {
                switch (player_hash)
                {
                case RAGE_JOAAT("MP_M_FREEMODE_01"):
                case RAGE_JOAAT("MP_F_FREEMODE_01"):
                    return false;
                    break;
                }
            }
            break;
        case NET_OBJ_TYPE_TRAILER:
            if (!systems::is_script_active(RAGE_JOAAT("fm_mission_controller") || !systems::is_script_active(RAGE_JOAAT("fm_mission_controller_2020"))))
            {
                for (auto obj : sync_trailer)
                {
                    if (vehicle_hash == obj)
                        return false;
                }
            }
            break;
        case NET_OBJ_TYPE_TRAIN:
            if (!systems::is_script_active(RAGE_JOAAT("fm_mission_controller") || !systems::is_script_active(RAGE_JOAAT("fm_mission_controller_2020"))))
            {
                for (auto obj : sync_train)
                {
                    if (vehicle_hash == obj)
                    {
                        return false;
                    }
                    else if (vehicle_hash != obj && systems::is_number_32_bit(vehicle_hash))
                    {
                        return false;
                    }
                }
            }
            break;
        }
        return systems::is_script_active(RAGE_JOAAT("fm_mission_controller")) || !systems::is_script_active(RAGE_JOAAT("fm_mission_controller_2020")) ? false : true;
    }

    std::string systems::char_to_string(char* a, int size)
    {
        int i;
        std::string s = "";
        for (i = 0; i < size; i++) {
            s = s + a[i];
        }
        return s;
    }

    double systems::milisecond_to_day(int64_t Milisecond)
    {
        auto x = Milisecond / 1000;
        auto seconds = x % 60;
        x = x / 60;
        auto minutes = x % 60;
        x = x / 60;
        auto hours = x % 24;
        x = x / 24;
        auto days = ceil(x);
        return fabs(days);
    }
        
    bool systems::is_number_8_bit(uint8_t number)
    {
        auto result = 8 << number;
        return result == 0;
    }

    bool systems::is_number_16_bit(uint16_t number)
    {
        auto result = 16 << number;
        return result == 0;
    }

    bool systems::is_number_32_bit(uint32_t number)
    {
        auto result = 32 << number;
        return result == 0;
    }

    bool systems::is_number_64_bit(uint64_t number)
    {
        auto result = 64 << number;
        return result == 0;
    }

    bool systems::is_script_active(rage::joaat_t Hash)
    {
        return rage_helper::find_script_thread(Hash) != nullptr;
    }

    void cam::set_cam_blurry()
    {
        STREAMING::SET_FOCUS_POS_AND_VEL(9999.0f, 9999.0f, -9999.0f, 0.0f, 0.0f, 0.0f);

        CAM::SET_CAM_ACTIVE(CAM::GET_RENDERING_CAM(), FALSE);
        CAM::SET_CAM_ACTIVE(1, TRUE);
        CAM::RENDER_SCRIPT_CAMS(TRUE, TRUE, 3000, FALSE, FALSE, FALSE);
    }

    int systems::hotkey(char ch)
    {
        return ch;
    }

    float systems::degree_to_radian(float degs)
    {
        return degs * 3.141592653589793f / 180.f;
    }

    std::string systems::character_filter(const char* str)
    {
        return str[strspn(str, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_!@#$%^&*()-.,[]{}=+ ")] != 0 ? "Error" : std::string::basic_string(str);
    }

    bool systems::has_special_character(const char* str)
    {
        return str[strspn(str, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_!@#$%^&*()-.,[]{}=+ ")] != 0;
    }

    bool systems::is_not_number(const char* str)
    {
        return str[strspn(str, "0123456789")] != 0;
    }

    bool systems::is_2d_vector_equal(rage::vector2 a, rage::vector2 b, float epsilon)
    {
        return (fabs(a.x - b.x) <= epsilon * std::max(fabs(a.x), fabs(b.x))) && (fabs(a.y - b.y) <= epsilon * std::max(fabs(a.y), fabs(b.y)));
    }

    bool systems::is_3d_vector_equal(Vector3 a, Vector3 b, float epsilon)
    {
        return (fabs(a.x - b.x) <= epsilon * std::max(fabs(a.x), fabs(b.x))) && (fabs(a.y - b.y) <= epsilon * std::max(fabs(a.y), fabs(b.y))) && (fabs(a.z - b.z) <= epsilon * std::max(fabs(a.z), fabs(b.z)));
    }

    bool systems::is_3d_vector_equal(rage::vector3 a, rage::vector3 b, float epsilon)
    {
        return (fabs(a.x - b.x) <= epsilon * std::max(fabs(a.x), fabs(b.x))) && (fabs(a.y - b.y) <= epsilon * std::max(fabs(a.y), fabs(b.y))) && (fabs(a.z - b.z) <= epsilon * std::max(fabs(a.z), fabs(b.z)));
    }

    bool systems::is_3d_vector_zero(Vector3 a, float epsilon)
    {
        return (fabs(a.x - 0.0f) <= epsilon * std::max(fabs(a.x), fabs(0.0f))) && (fabs(a.y - 0.0f) <= epsilon * std::max(fabs(a.y), fabs(0.0f))) && (fabs(a.z - 0.0f) <= epsilon * std::max(fabs(a.z), fabs(0.0f)));
    }

    bool systems::is_3d_vector_zero(rage::vector3 a, float epsilon)
    {
        return (fabs(a.x - 0.0f) <= epsilon * std::max(fabs(a.x), fabs(0.0f))) && (fabs(a.y - 0.0f) <= epsilon * std::max(fabs(a.y), fabs(0.0f))) && (fabs(a.z - 0.0f) <= epsilon * std::max(fabs(a.z), fabs(0.0f)));
    }

    bool systems::is_float_equal(float a, float b, float epsilon)
    {
        return (fabs(a - b) <= epsilon * std::max(fabs(a), fabs(b)));
    }

    void systems::set_weather_type(const char* WeatherType)
    {
        g_fiber_pool->queue_job([WeatherType]
        {
            if (strcmp(WeatherType, "XMAS") == 0)
            {
                *script_global(262145).at(4723).as<int*>() = 1;
            }
            MISC::SET_WEATHER_TYPE_NOW_PERSIST(WeatherType);
            *script_global(262145).at(4723).as<int*>() = 0;
        });
    }

    Player systems::get_player_id_from_name(const char* player_name)
    {
        if (*g_pointers->m_is_session_started)
        {
            for (int i = 0; i <= 32; ++i)
            {
                if (auto net_player = rage_helper::get_net_player(i))
                {
                    if (strcmp(net_player->get_name(), player_name) == 0)
                    {
                        return net_player->player_id;
                    }
                }
            }
        }
        return -1;
    }

    Vector3 systems::to_scr_vector(rage::vector3 vector)
    {
        return Vector3(vector.x, vector.y, vector.z);
    }

    rage::vector3 systems::to_rage_vector(Vector3 vector)
    {
        rage::vector3 coordinates = { vector.x, vector.y, vector.z };
        return coordinates;
    }

    int systems::float_to_int(const float& num) 
    {
        //check if float fits into integer
        if (std::numeric_limits<int>::digits < std::numeric_limits<float>::digits)
        {
            // check if float is smaller than max int
            if ((num < static_cast<float>(std::numeric_limits<int>::max())) &&
                (num > static_cast<float>(std::numeric_limits<int>::min())))
            {
                return static_cast<int>(num); //safe to cast
            }
            else 
            {
                //NaN is not defined for int return the largest int value
                return std::numeric_limits<int>::max();
            }
        }
        else 
        {
            //It is safe to cast
            return static_cast<int>(num);
        }
    }

    float systems::int_to_float(int x)
    {
        if (std::abs(long(static_cast<float>(x))) <= std::abs(long(x)))
            return static_cast<float>(x);
        return std::nextafter(static_cast<float>(x), 0.f);
    }

    float systems::round(float var)
    {
        return floorf(var * 100) / 100;
    }

    std::string systems::title_case (const std::string str)
    {
        
        char first_capital = rage::joaat_to_upper(str[0]);
        std::string title_str;
        title_str = first_capital;
        
        for (int i =1; i <str.size(); i++)
        {
            if(str[i-1] == ' ' &&  str[i] >= 'a' && str[i] <= 'z')
            {
                char capital = rage::joaat_to_upper(str[i]);
                title_str += capital;
                continue;
            }
            else
            {
                title_str += rage::joaat_to_lower(str[i]);
            }
        }
        return title_str;
    }

    bool validate_pointer(float Pointer, int64_t Bit)
    {
        auto pointer = std::addressof(Pointer);
        auto result = pointer;
        return result == 0;
    }

    bool long_number_to_char(char character)
    {
        uint64_t x = 281474976710655;
        unsigned char value[sizeof(x)];
        std::memcpy(value, &x, sizeof(x));
    }
}