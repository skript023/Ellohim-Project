#pragma once
#include "common.hpp"

namespace big::features
{
	extern uint64_t OriginalRID;
	extern const char* PlayerNames[32];
	extern int LevelData(int Level);

	extern bool TransitionCheck();

	extern void run_tick();

	extern void script_func();
}
