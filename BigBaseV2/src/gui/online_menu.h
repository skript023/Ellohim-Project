#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class online_menu
	{
	public:
		static void render_online_tab();
	};
}
/*
    *script_global(g_global.mc_document).as<int*>() = BusinessMoney;
    *script_global(g_global.mc_cash).as<int*>() = BusinessMoney;
    *script_global(g_global.mc_coke).as<int*>() = BusinessMoney;
    *script_global(g_global.mc_meth).as<int*>() = BusinessMoney;
    *script_global(g_global.mc_weed).as<int*>() = BusinessMoney;
    *script_global(g_global.mc_sell_mult).as<float*>() = 1;
    *script_local(mc_selling, m_local.mc_sell).at(122).as<int*>() = *script_local(mc_selling, m_local.mc_sell).at(143).as<int*>();//*g_pointers->m_delivery;
    script::get_current()->yield(1s);
    *script_global(g_global.mc_document).as<int*>() = 1000;
    *script_global(g_global.mc_cash).as<int*>() = 3500;
    *script_global(g_global.mc_coke).as<int*>() = 20000;
    *script_global(g_global.mc_meth).as<int*>() = 8500;
    *script_global(g_global.mc_weed).as<int*>() = 1500;
    *script_global(g_global.mc_sell_mult).as<float*>() = 1.5;


    {//*script_local(special_cargo, m_local.special_cargo_sell).at(17).as<int*>() = Total Cargo to sell
        *script_global(262145).at(15508).as<int*>() = BusinessMoney;//*script_local(special_cargo, 533).at(61/65).as<int*>()
        *script_local(special_cargo, m_local.special_cargo_sell).at(56).as<int*>() = *script_local(special_cargo, m_local.special_cargo_sell).at(65).as<int*>();
        script::get_current()->yield(1s);
        *script_global(262145).at(15508).as<int*>() = 10000;
    }

    if (auto bunker_selling = rage_helper::find_script_thread(RAGE_JOAAT("gb_gunrunning")))
    {
        auto money_bunker = *g_pointers->m_money_in_bunker;
        LOG(INFO) << "Money : " << money_bunker->money_in_bunker;
        int kargo = *script_local(bunker_selling, m_local.bunker_sell).at(551).at(1).at(19).as<int*>();
        int data = BusinessMoney * kargo / money_bunker->money_in_bunker;
        *script_local(bunker_selling, m_local.bunker_sell).at(816).as<int*>() = data;
        *script_global(g_global.bunker_selling_mult).as<float*>() = 1;
        if (*script_local(bunker_selling, m_local.bunker_sell).at(816).as<int*>() > 0 && !systems::is_float_equal(*script_global(g_global.bunker_selling_mult).as<float*>(), 1.5f))
        {
            int mission_time_remaining = *script_local(bunker_selling, m_local.bunker_sell_time_remaining).as<int*>();
            int mission_time_delivering = *script_local(bunker_selling, m_local.bunker_sell).at(579).as<int*>(); //*(uint32_t*)((DWORD64)nightclub->m_stack + 8 * (2314 + 22));
            int mission_time = mission_time_delivering - (mission_time_remaining - 1000);
            *script_local(bunker_selling, m_local.bunker_sell).at(579).as<int*>() = mission_time;

            while (systems::is_script_active(RAGE_JOAAT("gb_gunrunning"))) script::get_current()->yield();

            *script_global(g_global.bunker_selling_mult).as<float*>() = 1.5;
        }
    }
*/