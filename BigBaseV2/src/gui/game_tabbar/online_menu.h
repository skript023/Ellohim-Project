#pragma once

#include "common.hpp"
#include "natives.hpp"
//IOAN Penampatan Serang 
namespace big 
{
	class online_menu
	{
	public:
		static void render_online_tab(const char* tab_name);

    private:
        static inline const char* get_friend_name(int index)
        { 
            return rage_helper::get_friend()->get_friend_name(index);
        }

        static inline uint64_t get_friend_id(int index)
        { 
            return rage_helper::get_friend()->get_friend_id(index);
        }

        static inline uint64_t* set_friend_id(int index)
        { 
            return rage_helper::get_friend()->set_friend_id(index);
        }

        static inline const char* get_friend_status(int index)
        { 
            return rage_helper::get_friend()->get_friend_status(index);
        }

        static inline bool get_friend_multiplayer(int index)
        { 
            return rage_helper::get_friend()->m_friend_info[index].m_is_multiplayer;
        }
        
        static inline bool block_rid_joiner{};
        static inline const char* const session_list[]{"Join Public Session", "New Public Session", "Closed Crew Session", "Crew Session","Closed Friend Session", "Find Friend Session","Solo Session", "Invite Only Session","Join Crew Session", "Join SCTV", "Leave GTA Online"};
        static inline int selected_session = 0;

        static inline int selected_service = 0;
        static inline  const char* const service_list[]{ "Select", "Terrobyte", "Kosatka", "Avenger", "Mobile Operation Center", "Dinghy" };
	
        static inline const char* const weather_list[]{ "EXTRASUNNY", "CLEAR", "CLOUDS", "SMOG", "FOGGY", "OVERCAST", "RAIN", "THUNDER", "CLEARING", "NEUTRAL", "SNOW", "BLIZZARD", "SNOWLIGHT", "XMAS", "HALLOWEEN" };
        static inline int selected_weather = 0;
        static inline int Hour;
        static inline int Minute;
        static inline int Second;

        static inline const char* const HeistList[]{ "Bigcon", "Silent", "Aggressive", "Cayo Perico" };
        static inline int SelectedHeist = 0;
        static inline int selected_mission = 0;
        static inline int SelectedFriend{};

        static inline int player_cut_1 = 0;
        static inline int player_cut_2 = 0;
        static inline int player_cut_3 = 0;
        static inline int player_cut_4 = 0;

        static inline const char* const tuner_mission[]{ "Union Depository", "Superdollar Deal", "Bank Contract", "ECU Job", "Prison Contract", "Agency Deal", "LOST Contract", "Data Contract" };
        static inline int selected_heist_type = 0;

        static inline int potential_take_value = 0;
        static inline const char* const potential_take_list[]{ "Select", "Diamond", "Gold", "Artwork", "Cash", "Tequila", "Ruby", "Bearer Bonds","Pink Diamond", "Madrazo Files", "Saphire Panther",  "Fleeca", "Prison Break", "Humane Labs", "A Series","Pasific Standard", "ACT I", "ACT II", "ACT III" };
        static inline int selected_potential_take = 0;
        static inline const char* const bag_size[]{ "Bag Level 1", "Bag Level 2", "Bag Level 3", "Bag Level 4", "Over 1", "Over 2", "Infinite" };
        static inline int selected_bag_size = 0;
        static inline int take_type = 0;

        static inline const char* const cargo_rare_items[]{ "Ornament Egg", "Gold Minigun", "Large Diamond", "Rare Hide", "Film Reel", "Pocket Watch" };
        static inline int selected_rare_items = 0;
        static inline int manual_delivery = 0;

        static inline char spoof_crew_tag[5];

        static inline const char* const prize_list[]{ "Select Prize", "1:  2500 RP","2 : $20000","3 : 10000 Chips","4 : Discount","5 : 5000 RP", "6 : $30000","7 : 15000 Chips","8 : Clothing Item","9 : 7500 RP","10 : 20000 Chips","11 : Mystery Prize", "12 : Clothing Item","13 : 10000 RP","14 : $40000","15 : 25000 Chips","16 : Clothing Item","17 : 15000 RP","18 : Podium Vehicle" };
        
        static inline int selected_country{ 0 };
        static inline const char* const internet_protocol_list[]{ "Select Country", "Japan", "Korea", "Canada", "USA" };
        static inline char organization_name[32];
    };
}
//LA(1784, 'gb_gunrunning') bunker = Counter --> LA(2029, 'gb_gunrunning') = Bunker Delivery
//LA(589,'gb_contraband_sell') special cargo
//LA(829,'gb_biker_contraband_sell') Heli Cargo
//Local_533.f_582
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