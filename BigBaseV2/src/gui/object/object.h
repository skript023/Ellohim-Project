#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class object
	{
	public:
		static bool is_object_model_valid(rage::netSyncTree* netSyncTree, rage::netObject* netObject);
		static std::string get_object_name_from_hash(Hash hash);
		static void spawn_object(const char* name, Entity entity);
		static void spawn_object(Hash name, Entity entity);
		static void create_pickup(const char* pickup, const char* prop, int amount, Entity entity);
		static void AttacthObject(const char* name, Entity entity);
		static void attach_pickup(const char* pickup, const char* prop, int amount, Entity entity);
	};
}