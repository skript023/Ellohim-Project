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
	};
}