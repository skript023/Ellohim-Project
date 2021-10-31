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
#include <gui\player_list.h>
#include <gta\Weapons.h>
#include <gui/controller/Variable.h>
#include <gui/controller/memory_address.hpp>
#include "network_controller.h"
#include "system_control.h"

namespace big
{
    int network::get_meth_supply(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 1:
            case 6:
            case 11:
            case 16:
                return *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(2).as<int*>();
            }
        }
        return 0;
    }

    int network::get_weed_supply(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 2:
            case 7:
            case 12:
            case 17:
                return *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(2).as<int*>();
            }
        }
        return 0;
    }

    int network::get_cocain_supply(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 3:
            case 8:
            case 13:
            case 18:
                return *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(2).as<int*>();
            }
        }
        return 0;
    }

    int network::get_cash_supply(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 4:
            case 9:
            case 14:
            case 19:
                return *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(2).as<int*>();
            }
        }
        return 0;
    }

    int network::get_document_supply(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 5:
            case 10:
            case 15:
            case 20:
                return *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(2).as<int*>();
            }
        }
        return 0;
    }

    int network::get_bunker_supply(Player player)
    {
        if (*g_pointers->m_is_session_started)
        {
            return *script_global(1590908).at(player, 874).at(267).at(185).at(5, 12).at(2).as<int*>();
        }
        return 0;
    }

    int network::get_meth_stock(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 1:
            case 6:
            case 11:
            case 16:
                return *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(1).as<int*>();
            }
        }
        return 0;
    }

    int network::get_weed_stock(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 2:
            case 7:
            case 12:
            case 17:
                return *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(1).as<int*>();
            }
        }
        return 0;
    }

    int network::get_cocain_stock(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 3:
            case 8:
            case 13:
            case 18:
                return *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(1).as<int*>();
            }
        }
        return 0;
    }

    int network::get_cash_stock(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 4:
            case 9:
            case 14:
            case 19:
                return *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(1).as<int*>();
            }
        }
        return 0;
    }

    int network::get_document_stock(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 5:
            case 10:
            case 15:
            case 20:
                return *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(1).as<int*>();
            }
        }
        return 0;
    }

    int network::get_bunker_stock(Player player)
    {
        if (*g_pointers->m_is_session_started)
        {
            return *script_global(1590908).at(player, 874).at(267).at(185).at(5, 12).at(1).as<int*>();
        }
        return 0;
    }

    float network::get_research_progress(Player player)
    {
        if (*g_pointers->m_is_session_started)
        {
            auto research_progress = *script_global(1590908).at(player, 874).at(267).at(185).at(5, 12).at(12).as<int*>();
            auto research_percentages = (research_progress / 60) * 100;
            return systems::int_to_float(research_percentages);
        }
        return 0;
    }

    const char* network::get_meth_location(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 1:
                return "Paleto Bay";
            case 6:
                return "El Burro Heights";
            case 11:
                return "Grand Senora Desert";
            case 16:
                return "Terminal";
            }
        }
        return "No Data";
    }

    const char* network::get_weed_location(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 2:
                return "Mount Chiliad";
            case 7:
                return "Downtown Vinewood";
            case 12:
                return "San Chianski";
            case 17:
                return "Elysian Island";
            }
        }
        return "No Data";
    }

    const char* network::get_cocain_location(Player player)
    {
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).as<int*>();
            switch (location)
            {
            case 3:
                return "Paleto Bay";
            case 8:
                return "Morningwood";
            case 13:
                return "Alamo Sea";
            case 18:
                return "Elysian Island";
            }
        }
        return "No Data";
    }

    const char* network::get_cash_location(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 4:
                return "Paleto Bay";
            case 9:
                return "Vespucci Canals";
            case 14:
                return "Grand Senora Desert";
            case 19:
                return "Cypress Flats";
            }
        }
        return "No Data";
    }

    const char* network::get_document_location(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 5:
                return "Paleto Bay";
            case 10:
                return "Textile City";
            case 15:
                return "Grapeseed";
            case 20:
                return "Elysian Island";
            }
        }
        return "No Data";
    }

    const char* network::get_bunker_location(Player player)
    {
        auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(5, 12).as<int*>();

        switch (location)
        {
        case 23:
            return "Route86";
        case 24:
            return "Farmhouse";
        case 25:
            return "Smoke Tree Road";
        case 26:
            return "Thomson Scrapyard";
        case 27:
            return "Grapeseed";
        case 28:
            return "Paleto Forest";
        case 29:
            return "Ranton Canyon";
        case 30:
            return "Lago Zancudo";
        case 31:
            return "Chumash";
        }
        return "No Data";
    }

	void network::trigger_meth_production(Player player)
	{
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).as<int*>();
            switch (location)
            {
                case 1:
                case 6:
                case 11:
                case 16:
                    int supply = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(2).as<int*>();
                    int product = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(1).as<int*>();
                    if (product == 20) LOG(HACKER) << "Trigger Meth Production Function: Storage full with 20 Products!";
                    if (supply > 0)
                        *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(9).as<int*>() = 0;
                    else
                        LOG(HACKER) << "Trigger Meth Production Function: Supplies are empty! Buy Supplies!";
                break;
            }
        }
	}

    void network::trigger_weed_production(Player player)
    {
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).as<int*>();
            switch (location)
            {
            case 2:
            case 7:
            case 12:
            case 17:
                int supply = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(2).as<int*>();
                int product = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(1).as<int*>();
                if (product == 80) LOG(HACKER) << "Trigger Weed Production Function: Storage full with 80 Products!";
                if (supply > 0)
                    *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(9).as<int*>() = 0;
                else
                    LOG(HACKER) << "Trigger Weed Production Function: Supplies are empty! Buy Supplies!";
            break;
            }
        }
    }

    void network::trigger_cocain_production(Player player)
    {
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).as<int*>();
            switch (location)
            {
            case 3:
            case 8:
            case 13:
            case 18:
                int supply = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(2).as<int*>();
                int product = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(1).as<int*>();
                if (product == 10) LOG(HACKER) << "Trigger Cocaine Production Function: Storage full with 10 Products!";
                if (supply > 0)
                    *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(9).as<int*>() = 0;
                else
                    LOG(HACKER) << "Trigger Cocaine Production Function: Supplies are empty! Buy Supplies!";
            break;
            }
        }
    }

    void network::trigger_cash_production(Player player)
    {
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).as<int*>();
            switch (location)
            {
            case 4:
            case 9:
            case 14:
            case 19:
                int supply = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(2).as<int*>();
                int product = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(1).as<int*>();
                if (product == 40) LOG(HACKER) << "Trigger Cash Production Function: Storage full with 40 Products!";
                if (supply > 0)
                    *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(9).as<int*>() = 0;
                else
                    LOG(HACKER) << "Trigger Cash Production Function: Supplies are empty! Buy Supplies!";
            break;
            }
        }
    }

    void network::trigger_document_production(Player player)
    {
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).as<int*>();
            switch (location)
            {
            case 5:
            case 10:
            case 15:
            case 20:
                int supply = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(2).as<int*>();
                int product = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(1).as<int*>();
                if (product == 60) LOG(HACKER) << "Trigger Documents Production Function: Storage full with 60 Products!";
                if (supply > 0)
                    *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(9).as<int*>() = 0;
                else
                    LOG(HACKER) << "Trigger Documents Production Function: Supplies are empty! Buy Supplies!";
            break;
            }
        }
    }

    void network::trigger_bunker_production(Player player)
    {
        int supply = *script_global(1590908).at(player, 874).at(267).at(185).at(5, 12).at(2).as<int*>();
        int product = *script_global(1590908).at(player, 874).at(267).at(185).at(5, 12).at(1).as<int*>();
        if (product == 100) LOG(HACKER) << "Trigger Bunker Production Function: Full Stock!";
        if (supply > 0)
            *script_global(g_global.business_index).at(5, 12).at(9).as<int*>() = 0;
        else
            LOG(HACKER) << "Trigger Bunker Production Function: Supplies are empty! Buy Supplies!";
    }

    void network::trigger_bunker_research(Player player)
    {
        int supply = *script_global(1590908).at(player, 874).at(267).at(185).at(5, 12).at(2).as<int*>();
        int product = *script_global(1590908).at(player, 874).at(267).at(185).at(5, 12).at(1).as<int*>();
        if (product == 60) LOG(HACKER) << "Trigger Bunker Research Function: Research Progress Done!";
        if (supply > 0)
            *script_global(g_global.business_index).at(5, 12).at(13).as<int*>() = 0;
        else
            LOG(HACKER) << "Trigger Bunker Research Function: Supplies are empty! Buy Supplies!";
    }

	void network::spectate_player(Ped playerped)
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

	void network::request_control(Entity entity)
	{
		int network_id = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
		for (int i = 0; i < 250 && !NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity); i++)
		{
			if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) || !NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(network_id))
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
				NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(network_id);
				script::get_current()->yield();
			}
		}
		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(network_id, TRUE);
	}

	void network::set_session(int SessionId)
	{
		g_fiber_pool->queue_job([SessionId]
		{
			if (SessionId == -1)
			{
				*script_global(g_global.session_change).at(2).as<int*>() = -1;
				*script_global(g_global.session_change).as<int*>() = 1;
				script::get_current()->yield(200ms);
				*script_global(g_global.session_change).as<int*>() = 0;
				*script_global(g_global.sctv).as<bool*>() = false;
			}
			else if (SessionId == 13)
			{
				*script_global(g_global.session_id).as<int*>() = SessionId;
				*script_global(g_global.session_change).as<int*>() = 1;
				script::get_current()->yield(200ms);
				*script_global(g_global.session_change).as<int*>() = 0;
				*script_global(g_global.sctv).as<bool*>() = true;
			}
			else
			{
				*script_global(g_global.session_id).as<int*>() = SessionId;
				*script_global(g_global.session_change).as<int*>() = 1;
				script::get_current()->yield(200ms);
				*script_global(g_global.session_change).as<int*>() = 0;
				*script_global(g_global.sctv).as<bool*>() = false;
			}
		});
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
}