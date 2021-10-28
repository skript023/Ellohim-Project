#pragma once
#include "gui/casino/casino.h"
#include "gui/controller/ScriptController.h"
#include "gui/persistence/persist_car.h"
#include "gui/persistence/persist_teleport.h"
#include "gui/stat/stat_helper.h"
#include "gui/vehicle/vehicle_helper.h"
#include "gui/controller/Variable.h"
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
#include <gui\controller\xostr.h>

namespace big
{
	static class content
	{
	public:
		static inline int weapon_hash{};
		static inline int rid{};
		static inline uint8_t ip_1{};
		static inline uint8_t ip_2{};
		static inline uint8_t ip_3{};
		static inline uint8_t ip_4{};
	} g_item;

	static class fitur
	{
	public:
		static inline bool explosive_weapon = false;
		static inline int spoofer{};
		static inline int rid_type{};
		static inline int rid_spoof{};
		static inline int stat_spoofer{};
		static inline bool spread_on{};
		static inline bool recoil_on{};
		static inline bool teleport_gun{};
		static inline bool remove_lester_cut{};
		static inline bool desktop_all{};
		static inline int disconnect_type{};
		static inline bool waterproof{};
		static inline bool testing{};
	}g_fitur;

	static class hook_variable
	{
	public:
		static inline char sender_name[20];
		static inline Entity entity_id;
		static inline int32_t sync_type;
		static inline int32_t sync_flag;
	}g_hook_variable;
}