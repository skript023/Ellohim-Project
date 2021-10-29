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

namespace big
{
	void network::trigger_meth_production()
	{
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).as<int*>();
            switch (location)
            {
                case 1:
                case 6:
                case 11:
                case 16:
                    int supply = *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).at(2).as<int*>();
                    int product = *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).at(1).as<int*>();
                    if (product == 20) LOG(HACKER) << "Trigger Meth Production Function: Storage full with 20 Products!";
                    if (supply > 0)
                        *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).at(9).as<int*>() = 0;
                    else
                        LOG(HACKER) << "Trigger Meth Production Function: Supplies are empty! Buy Supplies!";
                break;
            }
        }
	}

    void network::trigger_weed_production()
    {
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).as<int*>();
            switch (location)
            {
            case 2:
            case 7:
            case 12:
            case 17:
                int supply = *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).at(2).as<int*>();
                int product = *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).at(1).as<int*>();
                if (product == 20) LOG(HACKER) << "Trigger Meth Production Function: Storage full with 20 Products!";
                if (supply > 0)
                    *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).at(9).as<int*>() = 0;
                else
                    LOG(HACKER) << "Trigger Meth Production Function: Supplies are empty! Buy Supplies!";
            break;
            }
        }
    }

    void network::trigger_cocain_production()
    {
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).as<int*>();
            switch (location)
            {
            case 3:
            case 8:
            case 13:
            case 18:
                int supply = *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).at(2).as<int*>();
                int product = *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).at(1).as<int*>();
                if (product == 20) LOG(HACKER) << "Trigger Meth Production Function: Storage full with 20 Products!";
                if (supply > 0)
                    *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).at(9).as<int*>() = 0;
                else
                    LOG(HACKER) << "Trigger Meth Production Function: Supplies are empty! Buy Supplies!";
            break;
            }
        }
    }

    void network::trigger_cash_production()
    {
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).as<int*>();
            switch (location)
            {
            case 4:
            case 9:
            case 14:
            case 19:
                int supply = *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).at(2).as<int*>();
                int product = *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).at(1).as<int*>();
                if (product == 20) LOG(HACKER) << "Trigger Meth Production Function: Storage full with 20 Products!";
                if (supply > 0)
                    *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).at(9).as<int*>() = 0;
                else
                    LOG(HACKER) << "Trigger Meth Production Function: Supplies are empty! Buy Supplies!";
            break;
            }
        }
    }

    void network::trigger_document_production()
    {
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).as<int*>();
            switch (location)
            {
            case 5:
            case 10:
            case 15:
            case 20:
                int supply = *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).at(2).as<int*>();
                int product = *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).at(1).as<int*>();
                if (product == 20) LOG(HACKER) << "Trigger Meth Production Function: Storage full with 20 Products!";
                if (supply > 0)
                    *script_global(1590908).at(g_local.player, 874).at(267).at(185).at(a, 12).at(9).as<int*>() = 0;
                else
                    LOG(HACKER) << "Trigger Meth Production Function: Supplies are empty! Buy Supplies!";
            break;
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