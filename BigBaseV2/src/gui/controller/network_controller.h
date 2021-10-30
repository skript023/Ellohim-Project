#pragma once
#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class network
	{
	public:
		static void spectate_player(Ped playerped);
		static void set_session(int SessionId);
		static void request_control(Entity entity);
		static void trigger_meth_production();
		static void trigger_weed_production();
		static void trigger_cocain_production();
		static void trigger_cash_production();
		static void trigger_document_production();
		const char* get_meth_location(Player player);
		const char* get_weed_location(Player player);
		const char* get_cocain_location(Player player);
		const char* get_cash_location(Player player);
		const char* get_document_location(Player player);
	};
}