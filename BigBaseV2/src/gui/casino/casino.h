#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class doomsday
	{
	public:

		static void instant_prep();

	};

	class apartment
	{
	public:
		static void instant_prep();
	};

	class cayo_perico
	{
	public:
		static void CayoPericoHeist();
		static void set_heat_to_zero(bool activation);
	};

	class casino_heist
	{
	public:
		static bool ch_is_hard(Player player);
		static void BigconHeist();
		static void SilentHeist();
		static void AggressiveHeist();
		static void all_heist_take(int Take);
		static void RemoveCasinoCrew(bool Activation);
		static void HeistCrewCutToZero(bool Activation);
		static void AutoHeistCut(bool Activate);
	public:
		static inline bool casino_heist_crew{};
		static inline bool auto_heist_cut{};
		static inline bool casino_heist_remove_crew{};
		static inline bool send_heal{};
		static inline bool all_take_heist{};
		static inline bool zero_heat{};
		static inline bool remove_lester_cut{};
		static inline int casino_take{};
	};

	class casino_slot
	{
	public:
		static void AlwaysJackpot(bool Activation);
		static void SetJackpot(int ID);
		static void SetJackpotMultiplier(int Reward);
		static void AutoPlay(bool Activation);
		static void RigSlotMachine(bool Activation);
		static void StopAnimation(bool Activation);
	public:
		static inline bool casino_rig{};

	};

	class blackjack
	{
	public:
		static void BlackJack(bool Activation);
		static bool is_context_active(char* text);
		static void AutoPlay(bool Activation);
	public:
		static inline bool blackjack_rig{};

	};

	static class mission_status
	{
	public:
		static inline bool casino_board{};
		static inline bool cayo_board{};
		static inline bool doomsday_board{};
		static inline bool apartment_board{};
		static inline bool mission_controller{};
		static inline bool mission_controller_new{};

	}g_mission;

	class lucky_wheel
	{
	public:
		static inline int selected_prize{};
	};

	inline lucky_wheel g_lucky_wheel;
	inline static casino_heist* g_heist_option{};
	inline static blackjack* g_blackjack_option{};
	inline static casino_slot* g_casino_option{};
}