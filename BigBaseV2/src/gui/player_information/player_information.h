#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class player_information
	{
	public:
		static void render_player_info(const char* tab_name);
		static void render_player_event(const char* tab_name);
		static void render_player_business_info(const char* tab_name);

	private:
        static inline const char* const ScriptEvent[]{ "Teleport To Cayo", "Invite Apartment", "CEO Kick", "CEO Ban", "Rotate Cam","Vehicle Kick", "Clear Wanted", "Kick", "Send Transaction Failed", "Send To Mission", "Give Wanted Level", "Fake Money", "Bounty" };
        static inline const char* const NetworkEvent[]{ "Weapon", "Request Anim Player", "Send Explosion", "Spectate", "Send Shoot", "Repair Vehicle", "Control Vehicle", "Bad Sport" };
        static inline const char* const OtherEvent[]{ "Teleport To Player", "Clone Player", "Teleport All Ped", "Cage Player", "Steal Costume", "Disconnect", "Force Teleport", "Give Vehicle Godmode"};
        static inline int SelectedScriptEvent = 0;
        static inline int SelectedNetworkEvent = 0;
        static inline int SelectedOtherEvent = 0;
        static inline int selected_apartment = 0;
        static inline bool is_all_player = false;

        static inline int SelectedShoot = 0;
        static inline int MoneyValue = 0;
        static inline int type = 0;
        static inline int SelectedExplosion = 0;
        static inline int SelectedBlame = 0;
        static inline int WeaponOption = 0;
        static inline int ExplosiveMode = 0;
        static inline int teleport_type = 0;
        static inline int control_type = 0;
        static inline bool isAudio = true;
        static inline bool isInvinsible = false;
        static inline bool AirStrike = false;
        static inline bool AutoGetIn = false;
        static inline int event_type = 0;
        static inline bool bonus_repair = false;
        static inline bool all_player = false;
	};
}