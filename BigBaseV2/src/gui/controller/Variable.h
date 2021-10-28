#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	struct dates {
		uint64_t y;
		uint64_t mo;
		uint64_t d;
		uint64_t h;
		uint64_t mi;
		uint64_t s;
		uint64_t ms;
	};
	class var
	{
	public:
		static std::string character_packed_hash[3290];
		static std::string all_packed_hash[15];
		static const char* const tuner_update[19];
		static std::string character_stat_hash[7425];
		static std::string all_stat_hash[401];
		static const int KickHash[17];
		static const char* const PickupHash[112];
		static const char* const ObjectList[2615];
		static const char* const AllWeaponHashes[92];
		static const char* const AllComponentHashes[338];
		static const char* const VechicleList[736];//720
		static const char* const PedList[671];
		static const char* const VehicleCategory[30];
		static const char* const Boat[20];
		static const char* const Commericals[17];
		static const char* const Compact[9];
		static const char* const Coupes[14];
		static const char* const Bikes[7];
		static const char* const Emergency[21];
		static const char* const Helicopter[22];
		static const char* const Industrial[11];
		static const char* const Military[12];
		static const char* const Motorcycle[47];
		static const char* const Muscle[46];
		static const char* const OffRoad[39];
		static const char* const Plane[37];
		static const char* const SUV[28];
		static const char* const Sedan[33];
		static const char* const Service[12];
		static const char* const Sport[57];
		static const char* const SportClassic[38];
		static const char* const Super[40];
		static const char* const Trailer[21];
		static const char* const Train[6];
		static const char* const Utility[20];
		static const char* const Van[34];
		static const char* const ArenaWar[45];
		static const char* const Casino1[22];
		static const char* const Casino2[20];
		static const char* const SummerUpdate[15];
		static const char* const CayoPerico[21];
		static const char* const ExplosionList[36];
		static const char* const DataPlayer[66];
		static const uint64_t DataPlayerRID[66];
		static const char* const ShootWeapon[7];
		static const char* const TeleportList[7];
		static const char* const Treasure_Hunt[3];
		static const char* const CasinoHeistCoords[16];
		static const char* const CayoPericoHeistCoords[18];
		static const char* const PlayingCard[55];
		static const char* const NavyRevolver[10];
		static const char* const MovieProp[6];
		static const char* const ListFlag[8];
		static const char* const revenge_list[93];
		static std::map<int, std::string> List_Vehicle_Flags_1;
		static std::map<int, std::string> List_Vehicle_Flags_2;
		static std::map<int, std::string> List_Vehicle_Flags_3;
		static std::map<int, std::string> List_Vehicle_Flags_4;
		static std::map<int, std::string> List_Vehicle_Flags_5;
		static std::map<int, std::string> List_Vehicle_Flags_6;
		static std::map<int, std::string> List_Vehicle_Flags_7;
		static const char* const ImpactList[75];
		static Hash weapon_shotgun[8];
	private:
	};
	static class local_data
	{
	public:
		static inline uint64_t rid{};
		static inline bool redirect_trigger{};
	} g_original;

	static class request_model
	{
	public:
		static const unsigned short on_request = 0x9090;
		static const unsigned short has_requested = 0x0574;
	}g_bypass;

	class player_clothing
	{
	public:
		static const char* const mask[195];
		static const char* const parachute[99];
		static const char* const kevlar[22];
		static const char* const female_hair[80];
		static const char* const female_acc[88];
		static const char* const female_legs[145];
		static const char* const female_shoes[106];
		static const char* const female_tops[400];
		static const char* const female_torsos[241];
		static const char* const female_undershirt[222];
		static const char* const female_bracelet[17];
		static const char* const female_ears[23];
		static const char* const female_glasses[35];
		static const char* const female_hats[155];
		static const char* const female_watches[42];
		
		static const char* const male_hair[76];
		static const char* const male_acc[152];
		static const char* const male_legs[138];
		static const char* const male_shoes[102];
		static const char* const male_tops[382];
		static const char* const male_torsos[196];
		static const char* const male_undershirt[184];
		static const char* const male_bracelet[10];
		static const char* const male_ears[42];
		static const char* const male_glasses[35];
		static const char* const male_hats[156];
		static const char* const male_watches[42];
	};
}

/*Pointers
Night Vision GTA5.exe+2276A73
GTA5.exe+25168AC= Current GTA Weather 1
GTA5.exe+25168AC+4 = Current GTA Weather 2
GTA5.exe+25168AC+104 = Force Weather
Thermal Vision GTA5.exe+22762DD
Times Beginns here GTA5.exe+1D107A8 thats the Weekday
next (every time +0x4) is Calendar Day (1-31)
next is Month (0-11)
next is Year
next is Hour, Minute and Seconds
*/
/*
ng_proc_temp
proc_brittlebush_01
proc_desert_sage_01
proc_dry_plants_01
proc_drygrasses01
proc_drygrasses01b
proc_drygrassfronds01
proc_dryplantsgrass_01
proc_dryplantsgrass_02
proc_forest_grass_01
proc_forest_ivy_01
proc_grassdandelion01
proc_grasses01
proc_grasses01b
proc_grassfronds01
proc_grassplantmix_01
proc_grassplantmix_02
proc_indian_pbrush_01
proc_leafybush_01
proc_leafyplant_01
proc_lizardtail_01
proc_lupins_01
proc_meadowmix_01
proc_meadowpoppy_01
proc_sage_01
proc_scrub_bush01
proc_sml_reeds_01
proc_sml_reeds_01b
proc_sml_reeds_01c
proc_stones_01
proc_stones_02
proc_stones_03
proc_stones_04
proc_stones_05
proc_stones_06
proc_wildquinine
prop_dandy_b
prop_dryweed_001_a
prop_dryweed_002_a
prop_fern_01
prop_fernba
prop_fernbb
prop_flowerweed_005_a
prop_grass_001_a
prop_grass_ca
prop_grass_da
prop_log_aa
prop_log_ab
prop_log_ac
prop_log_ad
prop_log_ae
prop_log_af
prop_saplin_001_b
prop_saplin_001_c
prop_saplin_002_b
prop_saplin_002_c
prop_small_bushyba
prop_tall_drygrass_aa
prop_thindesertfiller_aa
prop_weed_001_aa
prop_weed_002_ba
urbandryfrnds_01
urbandrygrass_01
urbangrnfrnds_01
urbangrngrass_01
urbanweeds01
urbanweeds01_l1
urbanweeds02
urbanweeds02_l2
v_proc2_temp
*/