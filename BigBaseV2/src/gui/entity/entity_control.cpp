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
#include <gui\player_list.h>
#include <gta\Weapons.h>
#include <gui/controller/Variable.h>
#include <gui/player/player_option.h>
#include "gui/object/object.h"
#include "gui/controller/memory_address.hpp"
#include "gui/controller/system_control.h"
#include "gta/net_object_mgr.hpp"
#include "gui/weapons/weapon_helper.h"
#include "gui/vehicle/vehicle_helper.h"
#include "gui/entity/entity_control.h"

namespace big
{
	Vector3 entity::get_entity_coords(Entity entity, bool Alive)
	{
		if (auto ent = rage_helper::entity_to_pointer<CPed*>(entity))
		{
			if (Alive)
			{
				if (!systems::is_float_equal(ent->m_health, 0.0f))
				{
					return systems::to_scr_vector(ent->m_navigation->m_position);
				}
			}
			else if (!Alive)
			{
				return systems::to_scr_vector(ent->m_navigation->m_position);
			}
		}
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	int entity::get_entity_health(Entity entity)
	{
		if (auto ent = rage_helper::entity_to_pointer<CPed*>(entity))
		{
			return systems::float_to_int(ent->m_health);
		}
		return 0;
	}

	int entity::get_entity_max_health(Entity entity)
	{
		if (auto ent = rage_helper::entity_to_pointer<CPed*>(entity))
		{
			return systems::float_to_int(ent->m_max_health);
		}
		return 0;
	}

	bool entity::get_entity_invincible(Entity entity)
	{
		if (auto ent = rage_helper::entity_to_pointer<CPed*>(entity))
		{
			return ent->is_invincible();
		}
		return false;
	}

	Hash entity::get_entity_model(Entity entity)
	{
		if (auto ent = rage_helper::entity_to_pointer<CPed*>(entity))
		{
			return ent->m_model_info->m_model_hash;
		}
		return 0;
	}
}