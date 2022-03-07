#pragma once
#include "gui/casino/casino.h"
#include "gui/controller/blackhole_helper.hpp"
#include "gui/persistence/persist_car.h"
#include "gui/persistence/persist_teleport.h"
#include "gui/stat/stat_helper.h"
#include "gui/vehicle/vehicle_helper.h"
#include "gui/controller/game_variable.h"
#include "gui/weapons/weapon_helper.h"
#include "gui/game_event/game_event.h"
#include "gui/player/player_option.h"
#include "gui/teleport/teleport.h"
#include "gui/artificial_intelligence/artificial_intelligence.h"
#include "gui/object/object.h"
#include "gui/controller/system_control.h"
#include "gui/controller/memory_address.hpp"
#include "gui/controller/network_controller.h"
#include "gui/entity/entity_control.h"
#include "gui/scenario/scenario.h"
#include "gta/blip.hpp"
#include "gui/game_event/game_helper.hpp"
#include "gui/controller/xostr.h"
#include "gui/window/imgui_notify.h"
#include "gui/game_time/game_time.hpp"
#include "gui/streaming/load_game_files.hpp"

namespace big
{
	class variable
	{
	public:
		static inline int casino_take{};
	};
	
	static class hook_variable
	{
	public:
		static inline char sender_name[20];
		static inline Entity entity_id;
		static inline int32_t sync_type;
		static inline int32_t sync_flag;
	}g_hook_variable;

	static variable* g_variable{};

}