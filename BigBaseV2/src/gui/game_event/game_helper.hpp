#pragma once
#include "common.hpp"
#include "gta/array.hpp"
#include "gta/ped_factory.hpp"
#include "gta/player.hpp"
#include "gta/script_thread.hpp"
#include "gta/tls_context.hpp"
#include "pointers.hpp"
#include "natives.hpp"
#include "script_global.hpp"
#include "gui/controller/memory_address.hpp"

namespace big::game_helper
{
	inline int func_799(int iParam0)
	{
		if (iParam0 >= *script_global(g_global.current_creates_1).as<int*>())
		{
			return g_global.tuneable_creates_1;
		}
		else if (iParam0 >= *script_global(g_global.current_creates_2).as<int*>())
		{
			return g_global.tuneable_creates_2;
		}
		else if (iParam0 >= *script_global(g_global.current_creates_3).as<int*>())
		{
			return g_global.tuneable_creates_3;
		}
		else if (iParam0 >= *script_global(g_global.current_creates_4).as<int*>())
		{
			return g_global.tuneable_creates_4;
		}
		else if (iParam0 >= *script_global(g_global.current_creates_5).as<int*>())
		{
			return g_global.tuneable_creates_5;
		}
		else if (iParam0 >= *script_global(g_global.current_creates_6).as<int*>())
		{
			return g_global.tuneable_creates_6;
		}
		else if (iParam0 >= *script_global(g_global.current_creates_7).as<int*>())
		{
			return g_global.tuneable_creates_7;
		}
		else if (iParam0 >= *script_global(g_global.current_creates_8).as<int*>())
		{
			return g_global.tuneable_creates_8;
		}
		else if (iParam0 >= *script_global(g_global.current_creates_9).as<int*>())
		{
			return g_global.tuneable_creates_9;
		}
		else if (iParam0 >= *script_global(g_global.current_creates_10).as<int*>())
		{
			return g_global.tuneable_creates_10;
		}
		else if (iParam0 >= *script_global(g_global.current_creates_11).as<int*>())
		{
			return g_global.tuneable_creates_11;
		}
		else if (iParam0 >= *script_global(g_global.current_creates_12).as<int*>())
		{
			return g_global.tuneable_creates_12;
		}
		else if (iParam0 >= *script_global(g_global.current_creates_13).as<int*>())
		{
			return g_global.tuneable_creates_13;
		}
		else if (iParam0 >= *script_global(g_global.current_creates_14).as<int*>())
		{
			return g_global.tuneable_creates_14;
		}
		else if (iParam0 >= *script_global(g_global.current_creates_15).as<int*>())
		{
			return g_global.tuneable_creates_15;
		}
		else if (iParam0 >= *script_global(g_global.current_creates_16).as<int*>())
		{
			return g_global.tuneable_creates_16;
		}
		else if (iParam0 >= *script_global(g_global.current_creates_17).as<int*>())
		{
			return g_global.tuneable_creates_17;
		}
		else if (iParam0 >= *script_global(g_global.current_creates_18).as<int*>())
		{
			return g_global.tuneable_creates_18;
		}
		else if (iParam0 >= *script_global(g_global.current_creates_19).as<int*>())
		{
			return g_global.tuneable_creates_19;
		}
		else if (iParam0 >= *script_global(g_global.current_creates_20).as<int*>())
		{
			return g_global.tuneable_creates_20;
		}
		return g_global.tuneable_creates_21;
	}

}