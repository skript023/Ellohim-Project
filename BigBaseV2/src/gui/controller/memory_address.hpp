#pragma once

#include "common.hpp"
#include "natives.hpp"
#include "gta\blip.hpp"
#include "script_global.hpp"

#define arraysize(_ARR)			 ((int)(sizeof(_ARR) / sizeof(*(_ARR))))
#define ARRAYSIZE_(_ARR)		 ((int)(sizeof(_ARR) / sizeof(*(_ARR))))

namespace big
{
	static class local_player_info_class
	{
	public:
		static inline Player player{};
		static inline Ped ped{};
		static inline int net_id{};
		static inline Player ScriptHost{};
		static inline Vehicle PlayerVehicle{};
		static inline int vehicle_net_id{};
		static inline int character{};
		static inline int connected_player{};
		static inline bool invalid_protection = false;
		static inline bool transition{};
		static inline bool is_male{};
		static inline bool is_cutscene_playing{};
		static inline bool is_activity_session{};
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
			static constexpr inline uint32_t karl_cut = 262145 + 28481; //5 74718927
			static constexpr inline uint32_t gustavo_cut = 262145 + 28482; //9  2084651107
			static constexpr inline uint32_t charlie_cut = 262145 + 28483; //7 2092632403
			static constexpr inline uint32_t chester_cut = 262145 + 28484; //10 -289926524
			static constexpr inline uint32_t packie_cut = 262145 + 28485; //8 -409770275
		} ch_gunman;
		static class crew_driver
		{
		public:
			//Driver
			static constexpr inline uint32_t karim_cut = 262145 + 28486; //5 88090906
			static constexpr inline uint32_t taliana_cut = 262145 + 28487; //7 -891458514
			static constexpr inline uint32_t eddie_cut = 262145 + 28488; //9 1321285827
			static constexpr inline uint32_t zach_cut = 262145 + 28489; //6 -856366310
			static constexpr inline uint32_t chester_cut = 262145 + 28490; //10 -1218087984
		}ch_driver;
		static class crew_hacker
		{
		public:
			//Hacker
			static constexpr inline uint32_t rickie_cut = 262145 + 28491; //3 2027377935
			static constexpr inline uint32_t christian_cut = 262145 + 28492; //7 -634674073
			static constexpr inline uint32_t yohan_cut = 262145 + 28493; //5 -1507129807
			static constexpr inline uint32_t avi_cut = 262145 + 28494; //10 -490900621
			static constexpr inline uint32_t paige_cut = 262145 + 28495; //9 -1454763111
		}ch_hacker;

	public: 
		static constexpr inline int32_t current_creates_1 = 262145 + 15595;//-903055251
		static constexpr inline int32_t current_creates_2 = 262145 + 15594;
		static constexpr inline int32_t current_creates_3 = 262145 + 15593;
		static constexpr inline int32_t current_creates_4 = 262145 + 15592;
		static constexpr inline int32_t current_creates_5 = 262145 + 15591;
		static constexpr inline int32_t current_creates_6 = 262145 + 15590;
		static constexpr inline int32_t current_creates_7 = 262145 + 15589;
		static constexpr inline int32_t current_creates_8 = 262145 + 15588;
		static constexpr inline int32_t current_creates_9 = 262145 + 15587;
		static constexpr inline int32_t current_creates_10 = 262145 + 15586;
		static constexpr inline int32_t current_creates_11 = 262145 + 15585;
		static constexpr inline int32_t current_creates_12 = 262145 + 15584;
		static constexpr inline int32_t current_creates_13 = 262145 + 15583;
		static constexpr inline int32_t current_creates_14 = 262145 + 15582;
		static constexpr inline int32_t current_creates_15 = 262145 + 15581;
		static constexpr inline int32_t current_creates_16 = 262145 + 15580;
		static constexpr inline int32_t current_creates_17 = 262145 + 15579;
		static constexpr inline int32_t current_creates_18 = 262145 + 15578;
		static constexpr inline int32_t current_creates_19 = 262145 + 15577;
		static constexpr inline int32_t current_creates_20 = 262145 + 15576;//1693507980

		static constexpr inline int32_t tuneable_creates_1 = 262145 + 15616; //1957513681
		static constexpr inline int32_t tuneable_creates_2 = 262145 + 15615;
		static constexpr inline int32_t tuneable_creates_3 = 262145 + 15614;
		static constexpr inline int32_t tuneable_creates_4 = 262145 + 15613;
		static constexpr inline int32_t tuneable_creates_5 = 262145 + 15612;
		static constexpr inline int32_t tuneable_creates_6 = 262145 + 15611;
		static constexpr inline int32_t tuneable_creates_7 = 262145 + 15610;
		static constexpr inline int32_t tuneable_creates_8 = 262145 + 15609;
		static constexpr inline int32_t tuneable_creates_9 = 262145 + 15608;
		static constexpr inline int32_t tuneable_creates_10 = 262145 + 15607;
		static constexpr inline int32_t tuneable_creates_11 = 262145 + 15606;
		static constexpr inline int32_t tuneable_creates_12 = 262145 + 15605;
		static constexpr inline int32_t tuneable_creates_13 = 262145 + 15604;
		static constexpr inline int32_t tuneable_creates_14 = 262145 + 15603;
		static constexpr inline int32_t tuneable_creates_15 = 262145 + 15602;
		static constexpr inline int32_t tuneable_creates_16 = 262145 + 15601;
		static constexpr inline int32_t tuneable_creates_17 = 262145 + 15600;
		static constexpr inline int32_t tuneable_creates_18 = 262145 + 15599;
		static constexpr inline int32_t tuneable_creates_19 = 262145 + 15598;
		static constexpr inline int32_t tuneable_creates_20 = 262145 + 15597;
		static constexpr inline int32_t tuneable_creates_21 = 262145 + 15596; //-1445480509

		static constexpr inline uint32_t level_array = 294354;
		static constexpr inline uint32_t special_crates = 1946644;
		static constexpr inline uint32_t rare_item = 1946798;
		static constexpr inline uint32_t rc_bandito = 2810701 + 6708;
		static constexpr inline uint32_t mini_tank = 2810701 + 6709;
		static constexpr inline uint32_t drone = 1958928;
		static constexpr inline uint32_t moc = 2810701 + 913;
		static constexpr inline uint32_t avanger = 2810701 + 921;
		static constexpr inline uint32_t terorbyte = 2810701 + 925;
		static constexpr inline uint32_t kosatka = 2810701 + 933;
		static constexpr inline uint32_t dinghy = 2810701 + 945;
		static constexpr inline uint32_t player_exp = 1655453 + 185;

		//Heist Global
		static constexpr inline uint32_t lester_cut = 262145 + 28289;
		static constexpr inline uint32_t real_player_cut = 2715551 + 6546;

		static constexpr inline uint32_t casino_cut_1 = 1966739 + 1497 + 736 + 92 + 1;
		static constexpr inline uint32_t casino_cut_2 = 1966739 + 1497 + 736 + 92 + 2;
		static constexpr inline uint32_t casino_cut_3 = 1966739 + 1497 + 736 + 92 + 3;
		static constexpr inline uint32_t casino_cut_4 = 1966739 + 1497 + 736 + 92 + 4;

		static constexpr inline uint32_t doomsday_cut_1 = 1962763 + 812 + 50 + 1;
		static constexpr inline uint32_t doomsday_cut_2 = 1962763 + 812 + 50 + 2;
		static constexpr inline uint32_t doomsday_cut_3 = 1962763 + 812 + 50 + 3;
		static constexpr inline uint32_t doomsday_cut_4 = 1962763 + 812 + 50 + 4;

		static constexpr inline uint32_t apartmen_cut_1 = 1934636 + 3008 + 1;
		static constexpr inline uint32_t apartmen_cut_2 = 1934636 + 3008 + 2;
		static constexpr inline uint32_t apartmen_cut_3 = 1934636 + 3008 + 3;
		static constexpr inline uint32_t apartmen_cut_4 = 1934636 + 3008 + 4;

		static constexpr inline uint32_t cayo_cut_1 = 1973525 + 823 + 56 + 1;
		static constexpr inline uint32_t cayo_cut_2 = 1973525 + 823 + 56 + 2;
		static constexpr inline uint32_t cayo_cut_3 = 1973525 + 823 + 56 + 3;
		static constexpr inline uint32_t cayo_cut_4 = 1973525 + 823 + 56 + 4;

		static constexpr inline uint32_t diamond = 262145 + 28472; //1277889925
		static constexpr inline uint32_t gold = 262145 + 28471; //-582734553
		static constexpr inline uint32_t artwork = 262145 + 28470; //1934398910
		static constexpr inline uint32_t cash = 262145 + 28469; //-1638885821

		static constexpr inline uint32_t casino_take_indicator = 2453903 + 6251;

		static constexpr inline uint32_t tequila = 262145 + 29632;//132820683
		static constexpr inline uint32_t ruby = 262145 + 29633; //-835710367
		static constexpr inline uint32_t bearer_bond = 262145 + 29634; //-1726558704
		static constexpr inline uint32_t pink_diamond = 262145 + 29635; //1874773759
		static constexpr inline uint32_t madrazo_file = 262145 + 29636;//2142881810
		static constexpr inline uint32_t saphire = 262145 + 29637;//266828370
		static constexpr inline uint32_t bag_size = 262146 + 29638;//1808919381

		static constexpr inline uint32_t fleeca = 262145 + 8920;//-736791602
		static constexpr inline uint32_t prison_break = 262145 + 8921;//-1697146966
		static constexpr inline uint32_t human_lab = 262145 + 8922;//-478542030
		static constexpr inline uint32_t a_series = 262145 + 8923;//joaat("HEIST_SERIES_A_FUNDING_CASH_REWARD")
		static constexpr inline uint32_t pasific_standard = 262145 + 8924;//-1535523991

		static constexpr inline uint32_t act_1 = 262145 + 8925;//419800513
		static constexpr inline uint32_t act_2 = 262145 + 8926;//-829097151
		static constexpr inline uint32_t act_3 = 262145 + 8927;//287993374

		static constexpr inline uint32_t casino_stat = 1971102;

		static constexpr inline uint32_t session_change = 1574589;
		static constexpr inline uint32_t session_type = 1575013;
		static constexpr inline uint32_t is_session_private = 2714635 + 744;//2453009.f_744

		static constexpr inline uint32_t mc_supplies_delay = 262145 + 18749; //728170457
		static constexpr inline uint32_t bunker_supplies_delay = 262145 + 21349; //-2094564985
		static constexpr inline uint32_t bunker_selling_time_1 = 262145 + 21487; //308825481
		static constexpr inline uint32_t bunker_selling_time_2 = 262145 + 21491; //1832002632
		static constexpr inline uint32_t bunker_selling_time_3 = 262145 + 21481; //-338923123
		static constexpr inline uint32_t bunker_selling_time_4 = 262145 + 21489; //2645121
		static constexpr inline uint32_t bunker_selling_time_5 = 262145 + 21494; //-1312217355
		static constexpr inline uint32_t bunker_selling_time_6 = 262145 + 21483; //245293410
		static constexpr inline uint32_t bunker_selling_mult_far = 262145 + 21304; //1021567941
		static constexpr inline uint32_t bunker_selling_mult_near = 262145 + 21303; //1021567941

		static constexpr inline uint32_t mc_selling_time_1 = 262145 + 18320; //-986183860
		static constexpr inline uint32_t mc_selling_time_2 = 262145 + 18317; //-605226498
		static constexpr inline uint32_t mc_selling_time_3 = 262145 + 18307; //1084174861
		static constexpr inline uint32_t mc_selling_time_4 = 262145 + 18311; //643059010
		static constexpr inline uint32_t mc_selling_time_5 = 262145 + 18313; //-2012578927
		static constexpr inline uint32_t mc_selling_time_6 = 262145 + 18347; //2037477066
		static constexpr inline uint32_t mc_selling_time_7 = 262145 + 18344; //-152621008
		static constexpr inline uint32_t mc_selling_time_8 = 262145 + 18354; //-186413482
		static constexpr inline uint32_t mc_selling_time_9 = 262145 + 18358; //286174536
		static constexpr inline uint32_t mc_selling_time_10 = 262145 + 18349; //-2110637751

		static constexpr inline uint32_t mc_sell_mult_far = 262145 + 18862;//1763638426
		static constexpr inline uint32_t mc_sell_mult_near = 262145 + 18863;//706040100
		static constexpr inline uint32_t mc_document = 262145 + 17223;//775812333
		static constexpr inline uint32_t mc_cash = 262145 + 17224;//-666993519
		static constexpr inline uint32_t mc_coke = 262145 + 17225;//1465649180
		static constexpr inline uint32_t mc_meth = 262145 + 17226;//-1177528994
		static constexpr inline uint32_t mc_weed = 262145 + 17227;//1074427467

		static constexpr inline uint32_t special_cargo_selling_cooldown = 262145 + 15362;//1291620941
		static constexpr inline uint32_t special_cargo_buying_cooldown = 262145 + 15361;//153204142
		static constexpr inline uint32_t special_cargo_selling_time = 262145 + 15375;//389090185
		
		static constexpr inline uint32_t contract_mission_cooldown = 262145 + 31330;//389090185

		static constexpr inline uint32_t nc_trigger_product = 2783670;

		static constexpr inline uint32_t sctv = 2676084;
		static constexpr inline uint32_t session_id = 1575012;
		static constexpr inline uint32_t session_unk_1 = 31512;
		static constexpr inline uint32_t session_unk_2 = 1574628;
		static constexpr inline uint32_t session_unk_3 = 1575007;
		static inline uint32_t session_unk_4{};
		
		static constexpr inline uint32_t host_kick = 1622591 + 1;
		static const inline int32_t repair_vehicle = 2426865 + 1 + (g_local.player * 449) + 231;
		static constexpr inline uint32_t disconnect = 31788;

		//Player Stats
		static constexpr inline int32_t player_stat = 1853131;
		static constexpr inline int32_t player_size = 888;
		static constexpr inline int32_t player_offset = 205;

		static constexpr inline int32_t radar_toggle = 2689224;
		static constexpr inline int32_t radar_size = 451;
		static constexpr inline int32_t radar_time = 2703660;
		static constexpr inline int32_t radar_offset = 209;

		static constexpr inline int32_t blind_cops = 2810701;
		static constexpr inline int32_t blind_cops_offset = 4624;

		static constexpr inline int32_t bullshark_time = radar_time;
		static constexpr inline int32_t suicide_time = radar_time;

		static constexpr inline int32_t garage = 1585853;
		static constexpr inline int32_t call_personal_vehicle = 2810701;
		static constexpr inline int32_t show_take = 4718592 + 87451;
		static constexpr inline int32_t request_model = 2725269;
		static constexpr inline int32_t vehicle_id = 2810701 + 6636;
		static constexpr inline int32_t current_personal_vehicle_index = 2359296;
		static constexpr inline int bypass_dlc_vehicle_in_single_player = 4533757;
		static constexpr inline int bounty_trigger = 1921039;
		static constexpr inline int script_event = 1893551;
		static constexpr inline int script_event_size = 599;
		static constexpr inline int clear_wanted_trigger = 1921039 + 9;
		static constexpr inline int vehicle_net_id = 2810701 + 298;
		static constexpr inline int network_id = 2689224;
		static constexpr inline int character = 1574915;

		public:
			static bool* vision() { return script_global(player_stat).at(g_local.player, player_size).at(848).at(9, 1).as<bool*>(); } //h4_islandx_disc_StrandedWhale)
			static script_global business_index(Player player){ return script_global(player_stat).at(player, player_size).at(267).at(187); }

	} g_global;

	static class constant_local
	{
	public:
		static class blackjack_local
		{
		public:
			static inline uint32_t current_table{};
			static constexpr inline uint32_t current_card = 107 + 1;
			static inline uint32_t bet_trigger{};
			static constexpr inline uint32_t button_ready = 2024 + 874 + 693;
			static constexpr inline uint32_t unk_1 = 2024;
			static constexpr inline uint32_t unk_2 = 3611;
			static constexpr inline uint32_t unk_3 = 99;//122
		}blackjack;
		static class casino_slot_local
		{
		public:
			//static inline uint32_t current_slot{};
			static constexpr inline int32_t jackpot_trigger = 1339;
			static constexpr inline int32_t animation = 1631;
			static constexpr inline int32_t slot_autoplay = 1629;
			static constexpr inline int32_t entry_func = 3392	;
			static constexpr inline uint32_t struct_21 = 104;
			static constexpr inline uint32_t unk_1 = 2116;
			static constexpr inline uint32_t unk_2 = 2119;
		}slot;
		static class casino_lucky_wheel
		{
		public:
			static constexpr inline uint32_t podium_vehicle = 271 + 14;
			static constexpr inline uint32_t trigger_wheel = 271 + 45;
		}lucky_wheel;
	public:
		//fm_mission_controller.ysc
		static constexpr inline uint32_t take_casino = 19652 + 2685;//19406
		static constexpr inline uint32_t vault_door = 10068 + 7;//9842
		static constexpr inline uint32_t vault_door_total = 10068 + 37;
		static constexpr inline uint32_t tc_live = 26077 + 1322 + 1;
		static constexpr inline uint32_t finger_print = 52899; //52649 DLC_H3_Fingerprint_Hack_Scene
		static constexpr inline uint32_t door_hack = 53729; //53711 DLC_H3_Door_Hack_Scene
		static constexpr inline uint32_t board_hacking_x = 11485 + 26;//11471
		static constexpr inline uint32_t board_hacking_y = 11485 + 27;
		static constexpr inline uint32_t board_hacking_requirement = 11485 + 39;
		static constexpr inline uint32_t doomsday_act_3_hack = 1347 + 4;//1343
		static constexpr inline uint32_t set_vault_door_broken = 59295;//59294

		//fm_mission_controller_2020.ysc
		static constexpr inline uint32_t take_cayo = 40004 + 1392 + 53;//39493 + 1536 + 53 //31600 + 9482 (41082) 39493.f_1589
		static constexpr inline uint32_t take_cayo_2 = 41334; //41112 1.58
		static constexpr inline uint32_t tc_live_c = 43059 + 865 + 1;//42692 + 1009 + 1;
		static constexpr inline uint32_t finger_clone = 23177; //23181
		static constexpr inline uint32_t voltage_hack_target = 1776;
		static constexpr inline uint32_t voltage_hack_current = 1777;
		static constexpr inline uint32_t glass_cutter_power = 28269 + 4;
		static constexpr inline uint32_t glass_cutter_heat = 28269 + 3;
		static constexpr inline uint32_t underwater_torch_total = 28244;
		static constexpr inline uint32_t underwater_torch_sound = 28249;
		static constexpr inline int32_t safe_hack = 28251;

		//heist_island_planning.ysc
		static constexpr inline uint32_t submarine_computer = 1521;

		//gb_contraband_buy.ysc
		static constexpr inline uint32_t special_cargo_buying = 594;

		//gb_contraband_sell.ysc
		static constexpr inline uint32_t special_cargo_sell = 536;

		//gb_gunrunnning.ysc
		static constexpr inline uint32_t bunker_sell = 1199;
		static constexpr inline uint32_t bunker_sell_time_remaining = 1181;

		//gb_biker_contraband_sell.ysc
		static constexpr inline uint32_t mc_sell = 692;

		//business_battle_sell.ysc
		static constexpr inline uint32_t nc_sell = 2300;
		static constexpr inline uint32_t nc_time_remaining = 741;


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
/*
http://jobstreet.co.id/id/job/management-trainee-store-supervisor-penempatan-seluruh-indonesia-3722969?jobid=jobstreet-id-job-3722969&sectionRank=2&token=0~c283643e-11d6-4e4d-b154-f8c4bbc3477&fr=SRP+Job+Listing
*/