#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class player_menu
	{
	public:
		static void render_player_tab(const char* tab_name);
	private:
		static inline Any tanggal[12];
		static inline char write_stat_name[255] = "";
		static inline float write_float_value = 0;
		static inline float write_increment_value = 0;
		static inline int64_t write_integer_value = 0;
		static inline char write_string_value[255];
		static inline const uint64_t step_one = 100;
		static inline bool write_bool_value = true;
		static inline bool inputs_step = false;

		static inline char read_stat_name[255];
		static inline int read_integer_value;
		static inline float read_float_value;
		static inline int read_bool_value;
		static inline char read_string_value[255];
		static inline Any read_date[12];

		static inline bool get_step = false;
		static inline char bool_to_text[20];
		static inline uint64_t Val;

		static inline int write_packed_ints_value = 0;
		static inline bool write_packed_bools_value = 0;
		static inline char write_packed_stat_name[50];

		static inline int read_packed_ints_value = 0;
		static inline bool read_packed_bools_value = 0;
		static inline char read_packed_stat_name[50];
		static inline int packed_stat_index;
		static inline int packed_stat_hash;
		static inline int packed_stat_value;
		static inline bool packed_bool_value;
		static inline char bool_string[20];

		static inline const char* const packed_bool_list[]{ "_NGPSTAT_BOOL", "_NGPSTAT_BOOL", "_NGTATPSTAT_BOOL", "_NGDLCPSTAT_BOOL", "_NGDLCPSTAT_BOOL" ,
					"_DLCBIKEPSTAT_BOOL", "_DLCGUNPSTAT_BOOL", "_GUNTATPSTAT_BOOL", "_DLCSMUGCHARPSTAT_BOOL", "_GANGOPSPSTAT_BOOL" ,
					"_BUSINESSBATPSTAT_BOOL" , "_ARENAWARSPSTAT_BOOL" , "_CASINOPSTAT_BOOL" , "_CASINOHSTPSTAT_BOOL" ,
					"_HEIST3TATTOOSTAT_BOOL" , "_SU20PSTAT_BOOL" , "_SU20TATTOOSTAT_BOOL" , "_HISLANDPSTAT_BOOL", "_TUNERPSTAT_BOOL", "_FIXERPSTAT_BOOL", "_FIXERTATTOOSTAT_BOOL" };
		static inline int selected_packed_bools = 0;

		static inline int selected_unlocker = 0;
		static inline const char* const unlock_list[]{ "Basic Unlock", "Unlock All Bool Stat", "Unlock All Int Stat", "Unlock All Achievements", "Unlock Penthouse Decorations", "Unlock Casino Shop Stuff", "Unhide Weapons from Gunlocker", "Tuner New Costumes", "Global RP Correction" };
	
		static inline const char* const AppearanceList[] = { "Swat", "Santa", "Ghost", "Special", "Special2", "Police", "For W Captain" };
		static inline const char* SelectedAppearance = AppearanceList[0];

		static inline const char* const LocationName[]{ "Military Tower", "Arcadius Rooftop", "Top of Building in Construction", "FIB Roof", "FIB Top Floor",
					"Vinewood Sign", "Observatory", "Mt. Chilliad", "Mt. Gordo", "office" };
		static inline int SelectedLocation = 0;

		static inline const char* const PropertyBlip[]{ "Arcade","MC Club House","Cocain Lockup","Meth Lab","Counterfeit Cash","Weed Farm","Document Forgery","Bunker","Nightclub","Hangar","CEO Office","Facility","Yacht","Submarine","Terrorbyte","Avanger","MOC","Arena Wars" };
		static inline int SelectedProperty = 0;

		static inline int hair{};
		static inline int hat{};
		static inline int mask{};
		static inline int top{};
		static inline int top2{};
		static inline int legs{};
		static inline int shoes{};
		static inline int gloves{};
		static inline int glasses{};
		static inline int special{};
		static inline int special_1{};
		static inline int special_2{};
		static inline int hair_colour{};
		static inline int hat_colour{};
		static inline int mask_colour{};
		static inline int glasses_colour{};
		static inline int top_colour{};
		static inline int top2_colour{};
		static inline int legs_colour{};
		static inline int gloves_colour{};
		static inline int shoes_colour{};
		static inline int special_colour{};
		static inline int special_1_colour{};
		static inline int special_2_colour{};
		static inline int ears{};
		static inline int ears_colour{};
		static inline int bracelet{};
		static inline int bracelet_colour{};
		static inline int badge{};
		static inline int badge_colour{};
	};
}