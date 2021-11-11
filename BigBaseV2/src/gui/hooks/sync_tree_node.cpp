#include "hooking.hpp"
#include "gta/net_object_mgr.hpp"
#include "gta/net_game_event.hpp"
#include "gui/helper_function.hpp"

namespace big
{
	bool hooks::clone_create(rage::CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, int32_t _object_type, int32_t _object_id, int32_t _object_flag, rage::datBitBuffer* buffer, int32_t timestamp)
	{
		int32_t n = (buffer->m_maxBit + 7) >> 3;
		auto data = buffer->m_data;

		g_hook_variable.entity_id = _object_id;

		strcpy(g_hook_variable.sender_name, src->get_name());

		int16_t object_type = _object_type;
		int16_t object_id = _object_id;
		int16_t object_flag = _object_flag;

		rage::netObject* netObject = g_pointers->m_get_network_object(mgr, object_id, true);
		bool owner = netObject != nullptr;
		bool type = object_type == NetObjEntityType_Submarine || object_type == NetObjEntityType_PickupPlacement || object_type < NetObjEntityType_Automobile || object_type > NetObjEntityType_Train;
		if (g_settings.options["Log Player"])
			LOG(INFO_TO_FILE) << fmt::format("Sender : {} | Receiver : {} | Object ID : {} | Object Type : {} | Flag : {}", src->get_name(), dst->get_name(), object_id, object_type, object_flag);

		if (g_settings.options["Crash Protection"])
		{
			bool block = type || owner;
			if (block)
			{
				LOG(INFO_TO_FILE) << fmt::format("Sender : {} | Receiver : {} | Object ID : {} | Object Type : {} | Flag : {}", src->get_name(), dst->get_name(), object_id, object_type, object_flag);
				buffer->m_unkBit = buffer->m_maxBit;
				return true;
			}
		}
		return g_hooking->m_clone_create_hook.get_original<functions::clone_create_t>()(mgr, src, dst, _object_type, _object_id, _object_flag, buffer, timestamp);
	}

	bool hooks::sync_read_buffer(rage::netSyncTree* netSyncTree, int32_t sync_type, int32_t _sync_flag, rage::datBitBuffer* buffer, void* netLogStub)
	{
		g_hook_variable.sync_flag = _sync_flag;
		g_hook_variable.sync_type = sync_type;

		return g_hooking->m_sync_read_buffer_hook.get_original<functions::sync_read_t>()(netSyncTree, sync_type, g_hook_variable.sync_flag, buffer, netLogStub);
	}

	bool hooks::sync_can_apply(rage::netSyncTree* netSyncTree, rage::netObject* netObject)
	{
		auto ped_hash = netSyncTree->m_sync_tree_node->m_ped_model;
		auto obj_hash = netSyncTree->m_sync_tree_node->m_object_model;
		auto vehicle_hash = netSyncTree->m_sync_tree_node->m_vehicle_model;
		auto pickup_hash = netSyncTree->m_sync_tree_node->m_pickup_model;
		auto object_id = netObject->object_id;
		auto sync_tree = netSyncTree;
		auto network_object = netObject;

		bool object_validity = netObject->object_type > NetObjEntityType_Train && netObject->object_type < NetObjEntityType_Automobile;

		std::string name = g_hook_variable.entity_id == object_id ? g_hook_variable.sender_name : "Unknown";
		bool is_name_valid = strcmp(name.c_str(), "Unknown") == 0;

		if (g_settings.options["Log Player"])
		{
			auto vehicle_name = vehicle_helper::get_vehicle_name_from_hash(vehicle_hash);
			auto ped_name = player::get_ped_name_from_hash(ped_hash);
			auto object_name = object::get_object_name_from_hash(obj_hash);
			auto player_name = player::get_ped_name_from_hash(netSyncTree->m_sync_tree_node->m_player_model);
			LOG(INFO_TO_FILE) << fmt::format("Sender : {} | Ped : {} | Vehicle : {} | Object : {} | Pickup : {} | Player : {} | Type : {} | Object Id : {}", name, ped_name, vehicle_name, object_name, pickup_hash, player_name, netObject->object_type, netObject->object_id);
		}

		if (g_settings.options["Crash Protection"])
		{
			if (object_validity || systems::is_model_valid(sync_tree, network_object) && !is_name_valid)
			{
				auto vehicle_name = vehicle_helper::get_vehicle_name_from_hash(vehicle_hash);
				auto ped_name = player::get_ped_name_from_hash(ped_hash);
				auto object_name = object::get_object_name_from_hash(obj_hash);
				auto player_name = player::get_ped_name_from_hash(netSyncTree->m_sync_tree_node->m_player_model);

				message::notification("~bold~~o~Ellohim Private Menu", fmt::format("~g~{} Try To Crash You", name).c_str(), "~bold~~g~Ellohim Menu Protection");
				LOG(INFO_TO_FILE) << fmt::format("Sender : {} | Ped : {} | Vehicle : {} | Object : {} | Pickup : {} | Player : {} | Type : {} | Object Id : {}", name, ped_name, vehicle_name, object_name, pickup_hash, player_name, netObject->object_type, netObject->object_id);
				return false;
			}
		}
		return g_hooking->m_sync_can_apply_hook.get_original<functions::sync_can_apply_t>()(netSyncTree, netObject);
	}

}