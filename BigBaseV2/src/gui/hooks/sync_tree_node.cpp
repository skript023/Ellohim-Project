#include "hooking.hpp"
#include "gta/net_object_mgr.hpp"
#include "gta/net_game_event.hpp"
#include "gui/helper_function.hpp"
#include "gta_util.hpp"

namespace big
{
	bool hooks::rid_crash(int64_t a1)
	{
		if (g_settings.options["Crash Protection"])
		{
			if (a1 == rage_helper::get_local_playerinfo()->m_rockstar_id)
			{
				ImGui::InsertNotification({ ImGuiToastType_Protection, 15999, "RID Crash %s", a1 });

				return false;
			}
		}
		//return g_hooking->m_rid_crash.get_original<decltype(&rid_crash)>()(a1);
	}

	enum class eVehicleType : std::uint32_t
	{
		Car,
		Plane,
		Unk2,
		Quadbike,
		Unk4,
		Unk5,
		AmphibiousCar,
		AmphibiousQuadbike,
		Heli,
		Unk9,
		Unk10,
		Bike,
		Bicycle,
		Boat,
		Train
	};

	const CBaseModelInfo* get_model_data(rage::joaat_t hash)
	{
		auto modelTble = g_pointers->m_model_table;
		for (auto i = modelTble->m_lookup_table[hash % modelTble->m_lookup_key]; i; i = i->m_next)
		{
			if (i->m_hash == hash)
			{
				if (const auto model = modelTble->m_data[i->m_idx]; model)
				{
					return reinterpret_cast<CBaseModelInfo*>(model);
				}
			}
		}
		return nullptr;
	}

	signed __int64 hooks::received_clone_sync(CNetworkObjectMgr* mgr,CNetGamePlayer* src,CNetGamePlayer* dst,unsigned __int16 sync_type,unsigned __int16 obj_id,rage::datBitBuffer* buffer,unsigned __int16 a7,unsigned int timestamp)
	{

		if (g_settings.options["Crash Protection"])
		{
			if (auto sync_tree = g_pointers->m_get_sync_tree_for_type(mgr, sync_type); sync_tree && *g_pointers->m_is_session_started)
			{
				if (auto net_obj = g_pointers->m_get_net_object(mgr, obj_id, true); net_obj)
				{
					auto tree_name = g_pointers->m_get_sync_type_info(sync_type, 0);
					bool invalidsync = false;

					if (sync_type < NetObjEntityType_Automobile || sync_type > NetObjEntityType_Max)
					{
						LOG(WARNING) << "Invalid sync: " << "Type: " << sync_type << " Tree name: " << tree_name << " From: " << src->get_name();
						ImGui::InsertNotification({ ImGuiToastType_Protection, 15999, "Invalid sync Type: %d Tree Name : %s From %s", sync_type, tree_name, src->get_name() });
					}
					else if (net_obj->object_type != sync_type)
					{
						LOG(WARNING) << "Invalid sync: " << "Type: " << sync_type << " Tree name: " << tree_name << " From: " << src->get_name();
						ImGui::InsertNotification({ ImGuiToastType_Protection, 15999, "Invalid sync Type: %d Tree Name : %s From %s", sync_type, tree_name, src->get_name() });
						
						return 2;
					}
					else if (auto game_obj = net_obj->GetGameObject(); game_obj)
					{
						if (auto model_info = game_obj->m_model_info)
						{
							if (!STREAMING::IS_MODEL_VALID(model_info->m_model_hash))
							{
								return 2;
							}
							else if (reinterpret_cast<CBaseModelInfo*>(model_info)->m_vehicle_type != get_model_data(model_info->m_model_hash)->m_vehicle_type)
							{
								return 2;
							}
							else if (model_info->m_model_type != get_model_data(model_info->m_model_hash)->m_model_type)
							{
								return 2;
							}
						}
					}
				}
				else if (sync_type != NetObjEntityType_Ped) //We don't want to not sync a player, so we ensure it's not a ped
				{
					return 2;
				}
			}
		}
		auto result = g_hooking->m_received_clone_sync_hook.get_original<decltype(&received_clone_sync)>()(mgr, src, dst, sync_type, obj_id, buffer, a7, timestamp);

		return result;

	}

	char sender_name[128];
	bool hooks::clone_create(rage::CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, int32_t _object_type, int32_t _object_id, int32_t _object_flag, rage::datBitBuffer* buffer, int32_t timestamp)
	{
		strcpy(sender_name, src->get_name());

		return g_hooking->m_clone_create_hook.get_original<decltype(&clone_create)>()(mgr, src, dst, _object_type, _object_id, _object_flag, buffer, timestamp);
	}

	bool hooks::sync_can_apply(rage::netSyncTree* netSyncTree, rage::netObject* netObject)
	{
		auto ped_hash = netSyncTree->m_sync_tree_node->m_ped_model;
		char sender_info[128] = "Crash has been sent by ";
		strcat(sender_info, sender_name);

		if (g_settings.options["Crash Protection"])
		{
			switch (ped_hash)
			{
			case RAGE_JOAAT("slod_human"):
			case RAGE_JOAAT("slod_large_quadped"):
			case RAGE_JOAAT("slod_small_quadped"):
				ImGui::InsertNotification({ ImGuiToastType_Protection, 15999, sender_info });
				return false;
			}
		}
		return g_hooking->m_sync_can_apply_hook.get_original<decltype(&sync_can_apply)>()(netSyncTree, netObject);
	}
}