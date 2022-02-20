#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class ai
	{
	public:
		static void Convoy(const char* vehicle, int max);
		static void kill_enemies(bool Activation);
		static void explode_enemies(bool Activation);
		static void kill_all_npc(bool Activation);
		static void explode_all_npc(bool Activation);
	public:
		static inline bool explode_ped{};
		static inline bool kill_ped{};

	};

	class message
	{
	public:
		static void notification(const char* Message, const char* MessageTag);
		static void notification(const char* message);
	};

	inline static ai* g_npc_option{};
}