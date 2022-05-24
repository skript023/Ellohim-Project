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
		return g_hooking->m_rid_crash.get_original<decltype(&rid_crash)>()(a1);
	}

	signed __int64 hooks::received_clone_sync(CNetworkObjectMgr* mgr,CNetGamePlayer* src,CNetGamePlayer* dst,unsigned __int16 sync_type,unsigned __int16 obj_id,rage::datBitBuffer* buffer,unsigned __int16 a7,unsigned int timestamp)
	{

		if (g_settings.options["Crash Protection"])
		{
			auto sync_tree = g_pointers->m_get_sync_tree_for_type(mgr, sync_type);
			auto tree_name = g_pointers->m_get_sync_type_info(sync_type, 0);
			auto net_obj = mgr->find_object_by_id(obj_id, true);
			bool invalidsync = false;

			if (!net_obj) net_obj = g_pointers->m_get_net_object_for_player(mgr, obj_id, src, true);

			if (!net_obj) return 2;

			if (!sync_tree || sync_type < 0 || sync_type > 14) invalidsync = true;

			if (net_obj->object_type != sync_type) invalidsync = true;

			//TO BE ADDED
			//Node specific entity type checks


			if (invalidsync)
			{

				LOG(WARNING) << "Invalid sync: " << "Type: " << sync_type << " Tree name: " << tree_name << " From: " << src->get_name();
				ImGui::InsertNotification({ ImGuiToastType_Protection, 15999, "Invalid sync Type: %d Tree Name : %s From %s", sync_type, tree_name, src->get_name() });
				return 2;
			}
		}
		auto result = g_hooking->m_received_clone_sync_hook.get_original<decltype(&received_clone_sync)>()(mgr, src, dst, sync_type, obj_id, buffer, a7, timestamp);

		return result;

	}
}