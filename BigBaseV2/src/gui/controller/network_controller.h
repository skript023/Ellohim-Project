#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class network
	{
	public:
		static void spectate_player(Ped playerped);
		static void set_session(int SessionId);
		static void request_control(Entity entity);

		static void trigger_meth_production(Player player);
		static void trigger_weed_production(Player player);
		static void trigger_cocain_production(Player player);
		static void trigger_cash_production(Player player);
		static void trigger_document_production(Player player);
        static void trigger_bunker_production(Player player);
        static void trigger_bunker_research(Player player);

        static const char* get_meth_location(Player player);
        static const char* get_weed_location(Player player);
        static const char* get_cocain_location(Player player);
        static const char* get_cash_location(Player player);
        static const char* get_document_location(Player player);
        static const char* get_bunker_location(Player player);

        static float get_meth_stock(Player player);
        static float get_weed_stock(Player player);
        static float get_cocain_stock(Player player);
        static float get_cash_stock(Player player);
        static float get_document_stock(Player player);
        static float get_bunker_stock(Player player);
        static float get_research_progress(Player player);

        static float get_meth_supply(Player player);
        static float get_weed_supply(Player player);
        static float get_cocain_supply(Player player);
        static float get_cash_supply(Player player);
        static float get_document_supply(Player player);
        static float get_bunker_supply(Player player);

        static void add_meth_supply(Player player, int supply);
        static void add_weed_supply(Player player, int supply);
        static void add_cocain_supply(Player player, int supply);
        static void add_cash_supply(Player player, int supply);
        static void add_document_supply(Player player, int supply);
        static void add_bunker_supply(Player player, int supply);
	};
}
/*
for (int a = 0; a <= 4; a++)
            {
                for (int b = 0; b <= 5; b++)
                {
                    for (int c = 0; c <= 4; c++)
                    {
                        for (int d = 0; d <= 1; d++)
                        {
                            if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 1 && var::tbl_business[b][c][d] == 1)
                            {
                                MethLocation = "Paleto Bay";
                            }
                            else if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 6 && var::tbl_business[b][c][d] == 6)
                            {
                                MethLocation = "El Burro Heights";
                            }
                            else if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 11 && var::tbl_business[b][c][d] == 11)
                            {
                                MethLocation = "Grand Senora Desert";
                            }
                            else if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 16 && var::tbl_business[b][c][d] == 16)
                            {
                                MethLocation = "Terminal";
                            }
                            else if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 2 && var::tbl_business[b][c][d] == 2)
                            {
                                WeedLocation = "Mount Chiliad";
                            }
                            else if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 7 && var::tbl_business[b][c][d] == 7)
                            {
                                WeedLocation = "Downtown Vinewood";
                            }
                            else if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 12 && var::tbl_business[b][c][d] == 12)
                            {
                                WeedLocation = "San Chianski";
                            }
                            else if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 17 && var::tbl_business[b][c][d] == 17)
                            {
                                WeedLocation = "Elysian Island";
                            }
                            else if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 3 && var::tbl_business[b][c][d] == 3)
                            {
                                CokeLocation = "Paleto Bay";
                            }
                            else if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 8 && var::tbl_business[b][c][d] == 8)
                            {
                                CokeLocation = "Morningwood";
                            }
                            else if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 13 && var::tbl_business[b][c][d] == 13)
                            {
                                CokeLocation = "Alamo Sea";
                            }
                            else if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 18 && var::tbl_business[b][c][d] == 18)
                            {
                                CokeLocation = "Elysian Island";
                            }
                            else if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 4 && var::tbl_business[b][c][d] == 4)
                            {
                                CashLocation = "Paleto Bay";
                            }
                            else if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 9 && var::tbl_business[b][c][d] == 9)
                            {
                                CashLocation = "Vespucci Canals";
                            }
                            else if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 14 && var::tbl_business[b][c][d] == 14)
                            {
                                CashLocation = "Grand Senora Desert";
                            }
                            else if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 19 && var::tbl_business[b][c][d] == 19)
                            {
                                CashLocation = "Cypress Flats";
                            }
                            else if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 5 && var::tbl_business[b][c][d] == 5)
                            {
                                DocLocation = "Paleto Bay";
                            }
                            else if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 10 && var::tbl_business[b][c][d] == 10)
                            {
                                DocLocation = "Textile City";
                            }
                            else if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 15 && var::tbl_business[b][c][d] == 15)
                            {
                                DocLocation = "Grapeseed";
                            }
                            else if (*script_global(1590908).at(g_selected.player, 874).at(267).at(185).at(a, 12).as<int*>() == 20 && var::tbl_business[b][c][d] == 20)
                            {
                                DocLocation = "Elysian Island";
                            }
                        }
                    }
                }
            }
*/