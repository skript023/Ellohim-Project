#pragma once
#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class load_files
	{
	public:
		static Hash load_model(const char* name);
		static void ptfx_asset_load(const char* name);
		static Hash load_model(Hash hash);
		static const char* load_anim(const char* anim);
	};
}