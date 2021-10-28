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
	};

	class message
	{
	public:
		static void notification(const char* sender, const char* Message, const char* MessageTag);
	};
}