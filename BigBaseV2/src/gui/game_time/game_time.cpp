#include "game_time.hpp"
#include "gta_util.hpp"
#include "script.hpp"

namespace big
{
    void game_time::faster_time_scale(bool Activation)
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
            }
            else
            {
                CLOCK::SET_CLOCK_TIME(hour, min, CLOCK::GET_CLOCK_SECONDS());
            }
        }
    }

    void game_time::day_to_night_spam(bool Activation)
    {
        if (Activation)
        {
            if (*g_pointers->m_is_session_started)
            {
                NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(12, CLOCK::GET_CLOCK_MINUTES(), CLOCK::GET_CLOCK_SECONDS());
                script::get_current()->yield(1s);
                NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(0, CLOCK::GET_CLOCK_MINUTES(), CLOCK::GET_CLOCK_SECONDS());
            }
            else
            {
                CLOCK::SET_CLOCK_TIME(12, CLOCK::GET_CLOCK_MINUTES(), CLOCK::GET_CLOCK_SECONDS());
                script::get_current()->yield(1s);
                CLOCK::SET_CLOCK_TIME(0, CLOCK::GET_CLOCK_MINUTES(), CLOCK::GET_CLOCK_SECONDS());
            }
        }
    }

    void game_time::hash_table_protection(bool Activation)
    {
        if (Activation)
        {
            auto hash_table = *g_pointers->m_hash_table; hash_table->m_ped_hash_table->m_slod = rage::joaat("player_one");
            hash_table->m_ped_hash_table->m_slod_small = rage::joaat("player_one");
            hash_table->m_ped_hash_table->m_slod_large = rage::joaat("player_one");
        }
        else
        {
            auto hash_table = *g_pointers->m_hash_table; hash_table->m_ped_hash_table->m_slod = rage::joaat("slod_human");
            hash_table->m_ped_hash_table->m_slod_small = rage::joaat("slod_small_quadped");
            hash_table->m_ped_hash_table->m_slod_large = rage::joaat("slod_large_quadped");
        }
    }
}