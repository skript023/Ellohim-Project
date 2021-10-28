#pragma once

#include "common.hpp"
#include "natives.hpp"
#include "gta\blip.hpp"

#define arraysize(_ARR)			 ((int)(sizeof(_ARR) / sizeof(*(_ARR))))
#define ARRAYSIZE_(_ARR)		 ((int)(sizeof(_ARR) / sizeof(*(_ARR))))

namespace big
{
	static class local_player_info_class
	{
	public:
		static inline Player player{};
		static inline Ped ped{};
		static inline Player ScriptHost{};
		static inline Vehicle PlayerVehicle{};
		static inline bool InVehicle{};
		static inline bool Transition{};
		static inline int character{};
		static inline int connected_player{};
		static inline GtaThread* mission{};
		static inline GtaThread* mission_2020{};
		static inline GtaThread* arcade{};
		static inline bool invalid_protection = false;
		static inline bool transition{};
		static inline bool is_male{};
		static inline bool script_transition{};
	} g_local;

	static class selected_player_info
	{
	public:
		static inline Player player{};
		static inline Ped ped{};
	}g_selected;

	static class event_tester
	{
	public:
		static inline Player event_player{};
		static inline Ped event_ped{};
	}g_event_tester;

	static class base_address
	{
	public:
		static inline uintptr_t WorldPTR{};
	} g_ptr;

	static class toggle_bool
	{
	public:
		static inline bool godmode = false;
	} g_toggle;

	static class diamondheistinfo
	{
	public:
		static inline int approach{}, target{}, last_approach{}, hard_approach{};
		static inline int disrupt{}, keylevels{}, crewweap{}, crewdriver{}, crewhacker{}, vehs{}, weaps{}, masks{}, bodyarmorlvl{}, bitset{}, bitsetone{};
	} diamond_heist_info;

	static class constant_global
	{
	public:
		static class crew_gunman
		{
		public:
			//Gunman
			static constexpr inline uint32_t karl_cut = 262145 + 28315; //5
			static constexpr inline uint32_t gustavo_cut = 262145 + 28316; //9
			static constexpr inline uint32_t charlie_cut = 262145 + 28317; //7
			static constexpr inline uint32_t chester_cut = 262145 + 28318; //10
			static constexpr inline uint32_t packie_cut = 262145 + 28319; //8
		} ch_gunman;
		static class crew_driver
		{
		public:
			//Driver
			static constexpr inline uint32_t karim_cut = 262145 + 28320; //5
			static constexpr inline uint32_t taliana_cut = 262145 + 28321; //7
			static constexpr inline uint32_t eddie_cut = 262145 + 28322; //9
			static constexpr inline uint32_t zach_cut = 262145 + 28323; //6
			static constexpr inline uint32_t chester_cut = 262145 + 28324; //10
		}ch_driver;
		static class crew_hacker
		{
		public:
			//Hacker
			static constexpr inline uint32_t rickie_cut = 262145 + 28325; //3
			static constexpr inline uint32_t christian_cut = 262145 + 28326; //7
			static constexpr inline uint32_t yohan_cut = 262145 + 28327; //5
			static constexpr inline uint32_t avi_cut = 262145 + 28328; //10
			static constexpr inline uint32_t paige_cut = 262145 + 28329; //9
		}ch_hacker;

	public:
		static constexpr inline uint32_t special_cargo_price_1 = 262145 + 15508; //10000; // 1
		static constexpr inline uint32_t special_cargo_price_2 = 262145 + 15509; // = 11000; // 2
		static constexpr inline uint32_t special_cargo_price_3 = 262145 + 15510; // = 12000; // 3
		static constexpr inline uint32_t special_cargo_price_4 = 262145 + 15511; // = 13000; // 4-5
		static constexpr inline uint32_t special_cargo_price_5 = 262145 + 15512; // = 13500; // 6-7
		static constexpr inline uint32_t special_cargo_price_6 = 262145 + 15513; // = 14000; // 8-9
		static constexpr inline uint32_t special_cargo_price_7 = 262145 + 15514; // = 14500; // 10-14
		static constexpr inline uint32_t special_cargo_price_8 = 262145 + 15515; // = 15000; // 15-19
		static constexpr inline uint32_t special_cargo_price_9 = 262145 + 15516; // = 16000; // 25-29
		static constexpr inline uint32_t special_cargo_price_10 = 262145 + 15517; // = 16500; // 30-34
		static constexpr inline uint32_t special_cargo_price_11 = 262145 + 15518; // = 17000; // 35-39
		static constexpr inline uint32_t special_cargo_price_12 = 262145 + 15519; // = 17500; // 40-44
		static constexpr inline uint32_t special_cargo_price_13 = 262145 + 15520; // = 17750; // 45-49
		static constexpr inline uint32_t special_cargo_price_14 = 262145 + 15521; // = 18000; // 50-59
		static constexpr inline uint32_t special_cargo_price_15 = 262145 + 15522; // = 18250; // 60-69
		static constexpr inline uint32_t special_cargo_price_16 = 262145 + 15523; // = 18500; // 70-79
		static constexpr inline uint32_t special_cargo_price_17 = 262145 + 15524; // = 18750; // 80-89
		static constexpr inline uint32_t special_cargo_price_18 = 262145 + 15525; // = 19000; // 90-99
		static constexpr inline uint32_t special_cargo_price_19 = 262145 + 15526; // = 19500; // 100-110
		static constexpr inline uint32_t special_cargo_price_20 = 262145 + 15527; // = 20000; // 111

		static constexpr inline uint32_t level_array = 293362;
		static constexpr inline uint32_t special_crates = 1683673;
		static constexpr inline uint32_t rare_item = 1683827;
		static constexpr inline uint32_t rc_bandito = 2544210 + 6688;
		static constexpr inline uint32_t mini_tank = 2544210 + 6689;
		static constexpr inline uint32_t drone = 1695733;
		static constexpr inline uint32_t moc = 2544210 + 913;
		static constexpr inline uint32_t avanger = 2544210 + 921;
		static constexpr inline uint32_t terorbyte = 2544210 + 925;
		static constexpr inline uint32_t kosatka = 2544210 + 933;
		static constexpr inline uint32_t dinghy = 2544210 + 945;
		static constexpr inline uint32_t player_exp = 1390343 + 185;

		//Heist Global
		static constexpr inline uint32_t lester_cut = 262145 + 28289;
		static constexpr inline uint32_t real_player_cut = 2453903 + 6494;

		static constexpr inline uint32_t casino_cut_1 = 1703513 + 2325 + 1;
		static constexpr inline uint32_t casino_cut_2 = 1703513 + 2325 + 2;
		static constexpr inline uint32_t casino_cut_3 = 1703513 + 2325 + 3;
		static constexpr inline uint32_t casino_cut_4 = 1703513 + 2325 + 4;

		static constexpr inline uint32_t doomsday_cut_1 = 1699568 + 812 + 50 + 1;
		static constexpr inline uint32_t doomsday_cut_2 = 1699568 + 812 + 50 + 2;
		static constexpr inline uint32_t doomsday_cut_3 = 1699568 + 812 + 50 + 3;
		static constexpr inline uint32_t doomsday_cut_4 = 1699568 + 812 + 50 + 4;

		static constexpr inline uint32_t apartmen_cut_1 = 1671773 + 3008 + 1;
		static constexpr inline uint32_t apartmen_cut_2 = 1671773 + 3008 + 2;
		static constexpr inline uint32_t apartmen_cut_3 = 1671773 + 3008 + 3;
		static constexpr inline uint32_t apartmen_cut_4 = 1671773 + 3008 + 4;

		static constexpr inline uint32_t cayo_cut_1 = 1710289 + 823 + 56 + 1;
		static constexpr inline uint32_t cayo_cut_2 = 1710289 + 823 + 56 + 2;
		static constexpr inline uint32_t cayo_cut_3 = 1710289 + 823 + 56 + 3;
		static constexpr inline uint32_t cayo_cut_4 = 1710289 + 823 + 56 + 4;

		static constexpr inline uint32_t diamond = 262145 + 28306;
		static constexpr inline uint32_t gold = 262145 + 28305;
		static constexpr inline uint32_t artwork = 262145 + 28304;
		static constexpr inline uint32_t cash = 262145 + 28303;

		static constexpr inline uint32_t casino_take_indicator = 2453903 + 6251;

		static constexpr inline uint32_t tequila = 262145 + 29461;
		static constexpr inline uint32_t ruby = 262145 + 29462;
		static constexpr inline uint32_t bearer_bond = 262145 + 29463;
		static constexpr inline uint32_t pink_diamond = 262145 + 29464;
		static constexpr inline uint32_t madrazo_file = 262145 + 29465;
		static constexpr inline uint32_t saphire = 262145 + 29466;
		static constexpr inline uint32_t bag_size = 262146 + 29226;

		static constexpr inline uint32_t fleeca = 262145 + 8834;
		static constexpr inline uint32_t prison_break = 262145 + 8835;
		static constexpr inline uint32_t human_lab = 262145 + 8836;
		static constexpr inline uint32_t a_series = 262145 + 8837;
		static constexpr inline uint32_t pasific_standard = 262145 + 8838;

		static constexpr inline uint32_t act_1 = 262145 + 8839;
		static constexpr inline uint32_t act_2 = 262145 + 8839;
		static constexpr inline uint32_t act_3 = 262145 + 8839;

		static constexpr inline uint32_t casino_stat = 1707876;

		static constexpr inline uint32_t session_change = 1312443;
		static constexpr inline uint32_t session_type = 1312861;
		static constexpr inline uint32_t is_session_private = 2453009 + 744;//2453009.f_744

		static constexpr inline uint32_t mc_supplies_delay = 262145 + 18661;
		static constexpr inline uint32_t bunker_supplies_delay = 262145 + 21261;
		static constexpr inline uint32_t bunker_selling_time_1 = 262145 + 21399; //308825481
		static constexpr inline uint32_t bunker_selling_time_2 = 262145 + 21403; //1832002632
		static constexpr inline uint32_t bunker_selling_time_3 = 262145 + 21393; //-338923123
		static constexpr inline uint32_t bunker_selling_time_4 = 262145 + 21401; //2645121
		static constexpr inline uint32_t bunker_selling_time_5 = 262145 + 21406; //-1312217355
		static constexpr inline uint32_t bunker_selling_time_6 = 262145 + 21395; //245293410
		static constexpr inline uint32_t bunker_selling_mult = 262145 + 21216; //1021567941

		static constexpr inline uint32_t mc_selling_time_1 = 262145 + 18232; //-986183860
		static constexpr inline uint32_t mc_selling_time_2 = 262145 + 18229; //-605226498
		static constexpr inline uint32_t mc_selling_time_3 = 262145 + 18219; //1084174861
		static constexpr inline uint32_t mc_selling_time_4 = 262145 + 18223; //643059010
		static constexpr inline uint32_t mc_selling_time_5 = 262145 + 18225; //-2012578927
		static constexpr inline uint32_t mc_selling_time_6 = 262145 + 18259; //2037477066
		static constexpr inline uint32_t mc_selling_time_7 = 262145 + 18256; //-152621008
		static constexpr inline uint32_t mc_selling_time_8 = 262145 + 18266; //-186413482
		static constexpr inline uint32_t mc_selling_time_9 = 262145 + 18270; //286174536
		static constexpr inline uint32_t mc_selling_time_10 = 262145 + 18261; //-2110637751

		static constexpr inline uint32_t mc_sell_mult_far = 262145 + 18774;//1763638426
		static constexpr inline uint32_t mc_sell_mult_near = 262145 + 18773;//1763638426
		static constexpr inline uint32_t mc_document = 262145 + 17135;
		static constexpr inline uint32_t mc_cash = 262145 + 17136;
		static constexpr inline uint32_t mc_coke = 262145 + 17137;
		static constexpr inline uint32_t mc_meth = 262145 + 17138;
		static constexpr inline uint32_t mc_weed = 262145 + 17139;

		static constexpr inline uint32_t special_cargo_selling_cooldown = 262145 + 15274;//1291620941
		static constexpr inline uint32_t special_cargo_buying_cooldown = 262145 + 15273;//153204142
		static constexpr inline uint32_t special_cargo_selling_time = 262145 + 15287;//389090185
		static inline uint32_t business_index{};

		static constexpr inline uint32_t nc_trigger_product = 2518601;

		static constexpr inline uint32_t sctv = 2464755;
		static constexpr inline uint32_t session_id = 1312860;
		static constexpr inline uint32_t session_unk_1 = 31346;
		static constexpr inline uint32_t session_unk_2 = 1312482;
		static constexpr inline uint32_t session_unk_3 = 1312855;
		static inline uint32_t session_unk_4{};
		static inline uint32_t vision{};
		static constexpr inline uint32_t host_kick = 1622591 + 1;
		static const inline int32_t repair_vehicle = 2426865 + 1 + (g_local.player * 449) + 231;
		static constexpr inline uint32_t disconnect = 31622;
	} g_global;

	static class constant_local
	{
	public:
		static class blackjack_local
		{
		public:
			static inline uint32_t current_table{};
			static constexpr inline uint32_t current_card = 124 + 1;
			static inline uint32_t bet_trigger{};
			static constexpr inline uint32_t button_ready = 2041 + 874 + 693;
			static constexpr inline uint32_t unk_1 = 2041;
			static constexpr inline uint32_t unk_2 = 3628;
			static constexpr inline uint32_t unk_3 = 122;
		}blackjack;
		static class casino_slot_local
		{
		public:
			static inline uint32_t current_slot{};
			static constexpr inline uint32_t struct_21 = 221;
			static constexpr inline uint32_t unk_1 = 2133;
			static constexpr inline uint32_t unk_2 = 2136;
		}slot;
		static class casino_lucky_wheel
		{
		public:
			static constexpr inline uint32_t podium_vehicle = 270 + 14;
			static constexpr inline uint32_t trigger_wheel = 270 + 45;
		}lucky_wheel;
	public:
		static constexpr inline uint32_t take_casino = 19406 + 2685;
		static constexpr inline uint32_t take_cayo = 39493 + 1536 + 53;// 31600 + 9482 (41082) 39493.f_1589
		static constexpr inline uint32_t take_cayo_2 = 41112;
		static constexpr inline uint32_t vault_door = 9842 + 7;
		static constexpr inline uint32_t vault_door_total = 9842 + 37;
		static constexpr inline uint32_t tc_live_c = 42692 + 1009 + 1;
		static constexpr inline uint32_t tc_live = 25831 + 1322 + 1;
		static constexpr inline uint32_t finger_clone = 15227;
		static constexpr inline uint32_t finger_print = 52649; //DLC_H3_Fingerprint_Hack_Scene
		static constexpr inline uint32_t door_hack = 53711; //DLC_H3_Door_Hack_Scene
		static constexpr inline uint32_t board_hacking_x = 11471 + 26;
		static constexpr inline uint32_t board_hacking_y = 11471 + 27;
		static constexpr inline uint32_t board_hacking_requirement = 11471 + 39;
		static constexpr inline uint32_t voltage_hack_target = 1793;
		static constexpr inline uint32_t voltage_hack_current = 1794;
		static constexpr inline uint32_t glass_cutter_heat = 28286 + 4;
		static constexpr inline uint32_t underwater_torch_total = 28261;
		static constexpr inline uint32_t underwater_torch_sound = 28266;
		static constexpr inline uint32_t set_vault_door_broken = 59295;//59294

		static constexpr inline uint32_t doomsday_act_3_hack = 1343 + 4;
		static constexpr inline uint32_t submarine_computer = 1538;

		static constexpr inline uint32_t special_cargo_buying = 610;
		static constexpr inline uint32_t special_cargo_sell = 535;
		static constexpr inline uint32_t bunker_sell = 1215;
		static constexpr inline uint32_t bunker_sell_time_remaining = 1197;

		static constexpr inline uint32_t mc_sell = 709;

		static constexpr inline uint32_t nc_sell = 2316;
		static constexpr inline uint32_t nc_time_remaining = 758;
		static constexpr inline uint32_t host_kick = 6076;
	} m_local;

	static class script_event
	{
	public:
		static inline int clear_wanted{};
	}g_script_event;

}
//LA(11471 + 26,'fm_mission_controller')
//LA(11471 + 27,'fm_mission_controller')
//LA(11471 + 39,'fm_mission_controller')