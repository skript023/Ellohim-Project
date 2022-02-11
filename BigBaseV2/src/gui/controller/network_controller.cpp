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
#include "gui/game_tabbar/player_list.h"
#include "gta/Weapons.h"
#include "gui/controller/game_variable.h"
#include "gui/controller/memory_address.hpp"
#include "network_controller.h"
#include "system_control.h"
#include "gui/artificial_intelligence/artificial_intelligence.h"

namespace big
{
    int network::network_get_num_connected_player()
    {
        if (*g_pointers->m_is_session_started)
        {
            return (*g_pointers->m_network_player_mgr)->num_player;
        }
        return 0;
    }

    void network::remove_orbital_cannon_cooldown(bool activate)
    {
        auto cooldown = *script_global(262145).at(22852).as<int*>();
        if (activate && cooldown != 0)
        {
            *script_global(262145).at(22852).as<int*>() = 0;
        }
        else
        {
            *script_global(262145).at(22852).as<int*>() = 2880000;
        }
    }

    bool network::network_is_host(Player player)
    {
        return *script_global(1893548).at(player, 600).at(10).as<bool*>();
    }

    void network::add_meth_supply(Player player, int supply)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).as<int*>();
            switch (location)
            {
            case 1:
            case 6:
            case 11:
            case 16:
                *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).at(2).as<int*>() = supply;
                break;
            }
        }
    }

    void network::add_weed_supply(Player player, int supply)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).as<int*>();
            switch (location)
            {
            case 2:
            case 7:
            case 12:
            case 17:
                *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).at(2).as<int*>() = supply;
                break;
            }
        }
    }

    void network::add_cocain_supply(Player player, int supply)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).as<int*>();
            switch (location)
            {
            case 3:
            case 8:
            case 13:
            case 18:
                *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).at(2).as<int*>() = supply;
                break;
            }
        }
    }

    void network::add_cash_supply(Player player, int supply)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).as<int*>();
            switch (location)
            {
            case 4:
            case 9:
            case 14:
            case 19:
                *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).at(2).as<int*>() = supply;
                break;
            }
        }
    }

    void network::add_document_supply(Player player, int supply)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).as<int*>();
            switch (location)
            {
            case 5:
            case 10:
            case 15:
            case 20:
                *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).at(2).as<int*>() = supply;
                break;
            }
        }
    }

    void network::add_bunker_supply(Player player, int supply)
    {
        if (*g_pointers->m_is_session_started)
        {
            *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(5, 13).at(2).as<int*>() = supply;
        }
    }

    float network::get_meth_supply(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).as<int*>();
            switch (location)
            {
            case 1:
            case 6:
            case 11:
            case 16:
                return systems::int_to_float(*script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).at(3).as<int*>());
            }
        }
        return 0.f;
    }

    float network::get_weed_supply(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).as<int*>();
            switch (location)
            {
            case 2:
            case 7:
            case 12:
            case 17:
                return systems::int_to_float(*script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).at(3).as<int*>());
            }
        }
        return 0.f;
    }

    float network::get_cocain_supply(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).as<int*>();
            switch (location)
            {
            case 3:
            case 8:
            case 13:
            case 18:
                return systems::int_to_float(*script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).at(3).as<int*>());
            }
        }
        return 0.f;
    }

    float network::get_cash_supply(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).as<int*>();
            switch (location)
            {
            case 4:
            case 9:
            case 14:
            case 19:
                return systems::int_to_float(*script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).at(3).as<int*>());
            }
        }
        return 0.f;
    }

    float network::get_document_supply(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).as<int*>();
            switch (location)
            {
            case 5:
            case 10:
            case 15:
            case 20:
                return systems::int_to_float(*script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).at(3).as<int*>());
            }
        }
        return 0.f;
    }

    float network::get_bunker_supply(Player player)
    {
        if (*g_pointers->m_is_session_started)
        {
            return systems::int_to_float(*script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(5, 13).at(2).as<int*>());
        }
        return 0.f;
    }

    float network::get_meth_stock(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).as<int*>();
            switch (location)
            {
            case 1:
            case 6:
            case 11:
            case 16:
                float product = systems::int_to_float(*script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).at(1).as<int*>());
                return (product / 20.f) * 100.f;
            }
        }
        return 0.f;
    }

    float network::get_weed_stock(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).as<int*>();
            switch (location)
            {
            case 2:
            case 7:
            case 12:
            case 17:
                float product = systems::int_to_float(*script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).at(1).as<int*>());
                return (product / 80.f) * 100.f;
            }
        }
        return 0.f;
    }

    float network::get_cocain_stock(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).as<int*>();
            switch (location)
            {
            case 3:
            case 8:
            case 13:
            case 18:
                float product = systems::int_to_float(*script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).at(1).as<int*>());
                return (product / 10.f) * 100.f;
            }
        }
        return 0.f;
    }

    float network::get_cash_stock(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).as<int*>();
            switch (location)
            {
            case 4:
            case 9:
            case 14:
            case 19:
                float product = systems::int_to_float(*script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).at(1).as<int*>());
                return (product / 40.f) * 100.f;
            }
        }
        return 0.f;
    }

    float network::get_document_stock(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).as<int*>();
            switch (location)
            {
            case 5:
            case 10:
            case 15:
            case 20:
                float product = systems::int_to_float(*script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).at(1).as<int*>());
                return (product / 60.f) * 100.f;
            }
        }
        return 0.f;
    }

    float network::get_bunker_stock(Player player)
    {
        if (*g_pointers->m_is_session_started)
        {
            return systems::int_to_float(*script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(5, 13).at(1).as<int*>());
        }
        return 0.f;
    }

    float network::get_research_progress(Player player)
    {
        if (*g_pointers->m_is_session_started)
        {
            auto research_progress = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(5, 13).at(12).as<int*>();
            auto research_percentages = (systems::int_to_float(research_progress) / 60.f) * 100.f;
            return research_percentages;
        }
        return 0.0f;
    }

    const char* network::get_meth_location(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).as<int*>();
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
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).as<int*>();
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
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).as<int*>();
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
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).as<int*>();
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
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(i, 13).as<int*>();
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
        auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(5, 13).as<int*>();

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
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).as<int*>();
            switch (location)
            {
                case 1:
                case 6:
                case 11:
                case 16:
                    int supply = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).at(2).as<int*>();
                    int product = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).at(1).as<int*>();
                    if (product == 20) message::notification("~bold~~g~Trigger Meth Production Function: Storage full with 20 Products!", "~bold~~g~Ellohim Business Manager");
                    if (supply > 0)
                        *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).at(9).as<int*>() = 0;
                    else
                        message::notification("~bold~~g~Trigger Meth Production Function: Supplies are empty! Buy Supplies!", "~bold~~g~Ellohim Business Manager");
                break;
            }
        }
	}

    void network::trigger_weed_production(Player player)
    {
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).as<int*>();
            switch (location)
            {
            case 2:
            case 7:
            case 12:
            case 17:
                int supply = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).at(2).as<int*>();
                int product = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).at(1).as<int*>();
                if (product == 80) message::notification("~bold~~g~Trigger Weed Production Function: Storage full with 80 Products!", "~bold~~g~Ellohim Business Manager");
                if (supply > 0)
                    *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).at(9).as<int*>() = 0;
                else
                    message::notification("~bold~~g~Trigger Weed Production Function: Supplies are empty! Buy Supplies!", "~bold~~g~Ellohim Business Manager");
            break;
            }
        }
    }

    void network::trigger_cocain_production(Player player)
    {
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).as<int*>();
            switch (location)
            {
            case 3:
            case 8:
            case 13:
            case 18:
                int supply = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).at(2).as<int*>();
                int product = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).at(1).as<int*>();
                if (product == 10) message::notification("~bold~~g~Trigger Cocaine Production Function: Storage full with 10 Products!", "~bold~~g~Ellohim Business Manager");
                if (supply > 0)
                    *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).at(9).as<int*>() = 0;
                else
                    message::notification("~bold~~g~Trigger Cocaine Production Function: Supplies are empty! Buy Supplies!", "~bold~~g~Ellohim Business Manager");
            break;
            }
        }
    }

    void network::trigger_cash_production(Player player)
    {
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).as<int*>();
            switch (location)
            {
            case 4:
            case 9:
            case 14:
            case 19:
                int supply = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).at(2).as<int*>();
                int product = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).at(1).as<int*>();
                if (product == 40) message::notification("~bold~~g~Trigger Cash Production Function: Storage full with 40 Products!", "~bold~~g~Ellohim Business Manager");
                if (supply > 0)
                    *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).at(9).as<int*>() = 0;
                else
                    message::notification("~bold~~g~Trigger Cash Production Function: Supplies are empty! Buy Supplies!", "~bold~~g~Ellohim Business Manager");
            break;
            }
        }
    }

    void network::trigger_document_production(Player player)
    {
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).as<int*>();
            switch (location)
            {
            case 5:
            case 10:
            case 15:
            case 20:
                int supply = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).at(2).as<int*>();
                int product = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).at(1).as<int*>();
                if (product == 60) message::notification("~bold~~g~Trigger Documents Production Function: Storage full with 60 Products!", "~bold~~g~Ellohim Business Manager");
                if (supply > 0)
                    *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(a, 13).at(9).as<int*>() = 0;
                else
                    message::notification("~bold~~g~Trigger Documents Production Function: Supplies are empty! Buy Supplies!", "~bold~~g~Ellohim Business Manager");
            break;
            }
        }
    }

    void network::trigger_bunker_production(Player player)
    {
        int supply = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(5, 13).at(2).as<int*>();
        int product = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(5, 13).at(1).as<int*>();
        if (product == 100) message::notification("~bold~~g~Trigger Bunker Production Function: Full Stock!", "~bold~~g~Ellohim Business Manager");
        if (supply > 0)
            *script_global(g_global.business_index).at(5, 13).at(9).as<int*>() = 0;
        else
            message::notification("~bold~~g~Trigger Bunker Production Function: Supplies are empty! Buy Supplies!", "~bold~~g~Ellohim Business Manager");
    }

    void network::trigger_bunker_research(Player player)
    {
        int supply = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(5, 13).at(2).as<int*>();
        int product = *script_global(g_global.player_stat).at(player, g_global.player_size).at(267).at(187).at(5, 13).at(1).as<int*>();
        if (product == 60) message::notification("~bold~~g~Trigger Bunker Research Function: Research Progress Done!", "~bold~~g~Ellohim Business Manager");
        if (supply > 0)
            *script_global(g_global.business_index).at(5, 13).at(13).as<int*>() = 0;
        else
            message::notification("~bold~~g~Trigger Bunker Research Function: Supplies are empty! Buy Supplies!", "~bold~~g~Ellohim Business Manager");
    }

    void network::trigger_nightclub_production()
    {
        for (int i = 0; i < 4; i++)
        {
            if (*script_global(g_global.nc_trigger_product).at(i, 2).at(1).as<int*>() == 1)
            {
                *script_global(g_global.nc_trigger_product).at(i, 2).as<int*>() = 0;//2515749
            }
        }
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