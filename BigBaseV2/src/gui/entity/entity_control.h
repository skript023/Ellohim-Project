#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class entity
	{
	public:
		static int get_entity_health(Entity entity);
		static int get_entity_max_health(Entity entity);
		static bool get_entity_invincible(Entity entity);
		static Hash get_entity_model(Entity entity);
		static Vector3 get_entity_coords(Entity entity, bool Alive);
	};
}