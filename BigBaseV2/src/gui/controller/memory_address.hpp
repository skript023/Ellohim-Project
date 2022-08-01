#pragma once

#include "common.hpp"
#include "natives.hpp"
#include "gta\blip.hpp"
#include "script_global.hpp"
#include "script_local.hpp"

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
			static constexpr inline uint32_t karl_cut = 262145 + 28805; //5 74718927
			static constexpr inline uint32_t gustavo_cut = 262145 + 28806; //9  2084651107
			static constexpr inline uint32_t charlie_cut = 262145 + 28807; //7 2092632403
			static constexpr inline uint32_t chester_cut = 262145 + 28808; //10 -289926524
			static constexpr inline uint32_t packie_cut = 262145 + 28809; //8 -409770275
		} ch_gunman;
		static class crew_driver
		{
		public:
			//Driver
			static constexpr inline uint32_t karim_cut = 262145 + 28810; //5 88090906
			static constexpr inline uint32_t taliana_cut = 262145 + 28811; //7 -891458514
			static constexpr inline uint32_t eddie_cut = 262145 + 28812; //9 1321285827
			static constexpr inline uint32_t zach_cut = 262145 + 28813; //6 -856366310
			static constexpr inline uint32_t chester_cut = 262145 + 28814; //10 -1218087984
		}ch_driver;
		static class crew_hacker
		{
		public:
			//Hacker
			static constexpr inline uint32_t rickie_cut = 262145 + 28815; //3 2027377935
			static constexpr inline uint32_t christian_cut = 262145 + 28816; //7 -634674073
			static constexpr inline uint32_t yohan_cut = 262145 + 28817; //5 -1507129807
			static constexpr inline uint32_t avi_cut = 262145 + 28818; //10 -490900621
			static constexpr inline uint32_t paige_cut = 262145 + 28819; //9 -1454763111
		}ch_hacker;

	public: 
		//-903055251
		static constexpr inline int32_t current_creates_1 = 262145 + 15823;
		static constexpr inline int32_t current_creates_2 = 262145 + 15824;
		static constexpr inline int32_t current_creates_3 = 262145 + 15825;
		static constexpr inline int32_t current_creates_4 = 262145 + 15826;
		static constexpr inline int32_t current_creates_5 = 262145 + 15827;
		static constexpr inline int32_t current_creates_6 = 262145 + 15828;
		static constexpr inline int32_t current_creates_7 = 262145 + 15829;
		static constexpr inline int32_t current_creates_8 = 262145 + 15830;
		static constexpr inline int32_t current_creates_9 = 262145 + 15831;
		static constexpr inline int32_t current_creates_10 = 262145 + 15832;
		static constexpr inline int32_t current_creates_11 = 262145 + 15833;
		static constexpr inline int32_t current_creates_12 = 262145 + 15834;
		static constexpr inline int32_t current_creates_13 = 262145 + 15835;
		static constexpr inline int32_t current_creates_14 = 262145 + 15836;
		static constexpr inline int32_t current_creates_15 = 262145 + 15837;
		static constexpr inline int32_t current_creates_16 = 262145 + 15838;
		static constexpr inline int32_t current_creates_17 = 262145 + 15839;
		static constexpr inline int32_t current_creates_18 = 262145 + 15840;
		static constexpr inline int32_t current_creates_19 = 262145 + 15841;
		static constexpr inline int32_t current_creates_20 = 262145 + 15842;
		//1693507980	

		/*
		local x = 1
		for i = 15843, 15863, 1 do
			print("static constexpr inline int32_t tuneable_creates_" ..x.. " = " .. "262145 + " .. i ..";")
			x = x + 1
		end
		*/
		//1957513681
		static constexpr inline int32_t tuneable_creates_1 = 262145 + 15843;
		static constexpr inline int32_t tuneable_creates_2 = 262145 + 15844;
		static constexpr inline int32_t tuneable_creates_3 = 262145 + 15845;
		static constexpr inline int32_t tuneable_creates_4 = 262145 + 15846;
		static constexpr inline int32_t tuneable_creates_5 = 262145 + 15847;
		static constexpr inline int32_t tuneable_creates_6 = 262145 + 15848;
		static constexpr inline int32_t tuneable_creates_7 = 262145 + 15849;
		static constexpr inline int32_t tuneable_creates_8 = 262145 + 15850; 
		static constexpr inline int32_t tuneable_creates_9 = 262145 + 15851;
		static constexpr inline int32_t tuneable_creates_10 = 262145 + 15852;
		static constexpr inline int32_t tuneable_creates_11 = 262145 + 15853;
		static constexpr inline int32_t tuneable_creates_12 = 262145 + 15854; 
		static constexpr inline int32_t tuneable_creates_13 = 262145 + 15855;
		static constexpr inline int32_t tuneable_creates_14 = 262145 + 15856;
		static constexpr inline int32_t tuneable_creates_15 = 262145 + 15857;
		static constexpr inline int32_t tuneable_creates_16 = 262145 + 15858;
		static constexpr inline int32_t tuneable_creates_17 = 262145 + 15859;
		static constexpr inline int32_t tuneable_creates_18 = 262145 + 15860;
		static constexpr inline int32_t tuneable_creates_19 = 262145 + 15861;
		static constexpr inline int32_t tuneable_creates_20 = 262145 + 15862;
		static constexpr inline int32_t tuneable_creates_21 = 262145 + 15863;
		//-1445480509
		//t.me//lowongancpnsbumn.com @festivalnyarikerja
		//Heist Global
		static constexpr inline uint32_t lester_cut = 262145 + 28289;
		static constexpr inline uint32_t real_player_cut = 2715699 + 6568;

		static constexpr inline uint32_t casino_cut_1 = 1966534 + 1497 + 736 + 92 + 1;
		static constexpr inline uint32_t casino_cut_2 = 1966534 + 1497 + 736 + 92 + 2;
		static constexpr inline uint32_t casino_cut_3 = 1966534 + 1497 + 736 + 92 + 3;
		static constexpr inline uint32_t casino_cut_4 = 1966534 + 1497 + 736 + 92 + 4;

		static constexpr inline uint32_t doomsday_cut_1 = 1962546 + 812 + 50 + 1;
		static constexpr inline uint32_t doomsday_cut_2 = 1962546 + 812 + 50 + 2;
		static constexpr inline uint32_t doomsday_cut_3 = 1962546 + 812 + 50 + 3;
		static constexpr inline uint32_t doomsday_cut_4 = 1962546 + 812 + 50 + 4;

		static constexpr inline uint32_t apartmen_cut_1 = 1933908 + 3008 + 1;
		static constexpr inline uint32_t apartmen_cut_2 = 1933908 + 3008 + 2;
		static constexpr inline uint32_t apartmen_cut_3 = 1933908 + 3008 + 3;
		static constexpr inline uint32_t apartmen_cut_4 = 1933908 + 3008 + 4;

		static constexpr inline uint32_t cayo_cut_1 = 1973321 + 823 + 56 + 1;
		static constexpr inline uint32_t cayo_cut_2 = 1973321 + 823 + 56 + 2;
		static constexpr inline uint32_t cayo_cut_3 = 1973321 + 823 + 56 + 3;
		static constexpr inline uint32_t cayo_cut_4 = 1973321 + 823 + 56 + 4;

		static constexpr inline uint32_t diamond = 262145 + 28796; //1277889925
		static constexpr inline uint32_t gold = 262145 + 28795; //-582734553
		static constexpr inline uint32_t artwork = 262145 + 28794; //1934398910
		static constexpr inline uint32_t cash = 262145 + 28793; //-1638885821

		static constexpr inline uint32_t casino_take_indicator = 2453903 + 6251;

		static constexpr inline uint32_t tequila = 262145 + 29970;//132820683
		static constexpr inline uint32_t ruby = 262145 + 29971; //-835710367
		static constexpr inline uint32_t bearer_bond = 262145 + 29972; //-1726558704
		static constexpr inline uint32_t pink_diamond = 262145 + 29973; //1874773759
		static constexpr inline uint32_t madrazo_file = 262145 + 29974;//2142881810
		static constexpr inline uint32_t saphire = 262145 + 29976;//266828370
		static constexpr inline uint32_t bag_size = 262146 + 29977;//1808919381

		static constexpr inline uint32_t fleeca = 262145 + 9127;//-736791602
		static constexpr inline uint32_t prison_break = 262145 + 9128;//-1697146966
		static constexpr inline uint32_t human_lab = 262145 + 9129;//-478542030
		static constexpr inline uint32_t a_series = 262145 + 9130;//joaat("HEIST_SERIES_A_FUNDING_CASH_REWARD")
		static constexpr inline uint32_t pasific_standard = 262145 + 9131;//-1535523991

		static constexpr inline uint32_t act_1 = 262145 + 9132;//419800513
		static constexpr inline uint32_t act_2 = 262145 + 9133;//-829097151
		static constexpr inline uint32_t act_3 = 262145 + 9134;//287993374

		static constexpr inline uint32_t mc_supplies_delay = 262145 + 18999; //728170457
		static constexpr inline uint32_t bunker_supplies_delay = 262145 + 21601; //-2094564985
		static constexpr inline uint32_t bunker_selling_time_1 = 262145 + 21739; //308825481
		static constexpr inline uint32_t bunker_selling_time_2 = 262145 + 21743; //1832002632
		static constexpr inline uint32_t bunker_selling_time_3 = 262145 + 21733; //-338923123
		static constexpr inline uint32_t bunker_selling_time_4 = 262145 + 21741; //2645121
		static constexpr inline uint32_t bunker_selling_time_5 = 262145 + 21746; //-1312217355
		static constexpr inline uint32_t bunker_selling_time_6 = 262145 + 21735; //245293410
		static constexpr inline uint32_t bunker_selling_mult_far = 262145 + 21554; //1021567941
		static constexpr inline uint32_t bunker_selling_mult_near = 262145 + 21553; //1865029244

		static constexpr inline uint32_t mc_selling_time_1 = 262145 + 18570; //-986183860
		static constexpr inline uint32_t mc_selling_time_2 = 262145 + 18567; //-605226498
		static constexpr inline uint32_t mc_selling_time_3 = 262145 + 18557; //1084174861
		static constexpr inline uint32_t mc_selling_time_4 = 262145 + 18561; //643059010
		static constexpr inline uint32_t mc_selling_time_5 = 262145 + 18563; //-2012578927
		static constexpr inline uint32_t mc_selling_time_6 = 262145 + 18597; //2037477066
		static constexpr inline uint32_t mc_selling_time_7 = 262145 + 18594; //-152621008
		static constexpr inline uint32_t mc_selling_time_8 = 262145 + 18604; //-186413482
		static constexpr inline uint32_t mc_selling_time_9 = 262145 + 18608; //286174536
		static constexpr inline uint32_t mc_selling_time_10 = 262145 + 18599; //-2110637751

		static constexpr inline uint32_t mc_sell_mult_far = 262145 + 19112;//1763638426
		static constexpr inline uint32_t mc_sell_mult_near = 262145 + 19113;//706040100
		static constexpr inline uint32_t mc_document = 262145 + 17471;//775812333
		static constexpr inline uint32_t mc_cash = 262145 + 17472;//-666993519
		static constexpr inline uint32_t mc_coke = 262145 + 17474;//1465649180
		static constexpr inline uint32_t mc_meth = 262145 + 17475;//-1177528994
		static constexpr inline uint32_t mc_weed = 262145 + 17476;//1074427467

		static constexpr inline uint32_t special_cargo_selling_cooldown = 262145 + 15609;//1291620941
		static constexpr inline uint32_t special_cargo_buying_cooldown = 262145 + 15608;//153204142
		static constexpr inline uint32_t special_cargo_selling_time = 262145 + 15622;//389090185
		
		static constexpr inline uint32_t contract_mission_cooldown = 262145 + 31672;//1870939070

		static constexpr inline uint32_t level_array = 295824;
		static constexpr inline uint32_t special_crates = 1945957;
		static constexpr inline uint32_t rare_item = 1946111;
		static constexpr inline uint32_t rc_bandito = 2815059 + 6751;
		static constexpr inline uint32_t mini_tank = 2815059 + 6752;
		static constexpr inline uint32_t drone = 1958711;
		static constexpr inline uint32_t moc = 2815059 + 913;
		static constexpr inline uint32_t avanger = 2815059 + 921;
		static constexpr inline uint32_t terorbyte = 2815059 + 925;
		static constexpr inline uint32_t kosatka = 2815059 + 933;
		static constexpr inline uint32_t dinghy = 2815059 + 945;
		static constexpr inline uint32_t player_exp = 1659575 + 185;

		static constexpr inline uint32_t casino_stat = 1971102;

		static constexpr inline uint32_t session_change = 1574589;
		static constexpr inline uint32_t session_type = 1575016;
		static constexpr inline uint32_t is_session_private = 2714762 + 744;//2453009.f_744

		static constexpr inline uint32_t nc_trigger_product = 2787863;

		static constexpr inline uint32_t sctv = 2676154;
		static constexpr inline uint32_t session_id = 1575015;
		static constexpr inline uint32_t session_unk_1 = 31960;
		static constexpr inline uint32_t session_unk_2 = 1574628;
		static constexpr inline uint32_t session_unk_3 = 1575010;
		static inline uint32_t session_unk_4{};
		
		static constexpr inline uint32_t host_kick = 1622591 + 1;
		static const inline int32_t repair_vehicle = 2426865 + 1 + (g_local.player * 449) + 231;//Global_2689224[bParam0 451].f_229
		/*
		int func_248(bool bParam0, bool bParam1, int iParam2)
		{
			if (Global_2689224[bParam0 451].f_229 == 99)
			{
				if ((iParam2 && Global_2689224[bParam0 451].f_232 == 0) || iParam2 == 0)
				{
					return 0;
				}
			}
			if (bParam1)
			{
				if (Global_2689224[bParam0 451].f_229 == 13)
				{
					return 0;
				}
			}
			return 1;
		}
		
		*/
		static constexpr inline uint32_t disconnect = 32236;

		//Player Stats
		static constexpr inline int32_t player_stat = 1853348;
		static constexpr inline int32_t player_size = 834;
		static constexpr inline int32_t player_offset = 205;

		static constexpr inline int32_t radar_toggle = 2689235;
		static constexpr inline int32_t radar_size = 453;
		static constexpr inline int32_t radar_time = 2703735;
		static constexpr inline int32_t radar_offset = 208;

		static constexpr inline int32_t radar_type = 2815059 + 4630;

		static constexpr inline int32_t blind_cops = 2815059;
		static constexpr inline int32_t blind_cops_offset = 4624;

		static constexpr inline int32_t bullshark_time = radar_time;
		static constexpr inline int32_t suicide_time = radar_time;

		static constexpr inline int32_t garage = 1585857;
		static constexpr inline int32_t call_personal_vehicle = 2815059;
		static constexpr inline int32_t show_take = 4718592 + 116986;
		static constexpr inline int32_t request_model = 2725439;
		static constexpr inline int32_t vehicle_id = 2815059 + 6679;
		static constexpr inline int32_t current_personal_vehicle_index = 2359296;
		static constexpr inline int bypass_dlc_vehicle_in_single_player = 4539659;
		static constexpr inline int bounty_trigger = 1920255;
		static constexpr inline int script_event = 1892703;
		static constexpr inline int script_event_size = 599;
		static constexpr inline int clear_wanted_trigger = 1920255 + 9;
		static constexpr inline int vehicle_net_id = 2815059 + 298;
		static constexpr inline int network_id = 2689235;
		static constexpr inline int character = 1574918;

		public:
			static inline bool* vision() { return script_global(player_stat).at(g_local.player, player_size).at(794).at(9, 1).as<bool*>(); } //h4_islandx_disc_StrandedWhale) if (iVar10 == iVar11)
			static inline script_global business_index(Player player){ return script_global(player_stat).at(player, player_size).at(267).at(187); }
			static inline script_global get_organization_name(Player player) { return script_global(script_event).at(player, script_event_size).at(10).at(105); }
	} g_global;

	static class constant_local
	{
	public:
		static class blackjack_local
		{
		public:
			//static inline uint32_t current_table{};
			static constexpr inline uint32_t current_card = 109 + 1;
			//static inline uint32_t bet_trigger{};
			static constexpr inline uint32_t button_ready = 2026 + 874 + 693;
			static constexpr inline uint32_t unk_1 = 2026;
			static constexpr inline uint32_t unk_2 = 3613;
			static constexpr inline uint32_t unk_3 = 101;//122
			static inline script_local current_table(rage::scrThread* thread, Player player) { return script_local(thread, 1769 + 1 + (player * 8) + 4); }
			static inline script_local bet_trigger(rage::scrThread* thread, Player player) { return script_local(thread, 1769 + 1 + (player * 8)); }
		}blackjack;
		static class casino_slot_local
		{
		public:
			//static inline uint32_t current_slot{};
			static constexpr inline int32_t jackpot_trigger = 1341;
			static constexpr inline int32_t animation = 1633;
			static constexpr inline int32_t slot_autoplay = 1631;
			static constexpr inline int32_t entry_func = 3394;
			static constexpr inline uint32_t struct_21 = 106;
			static constexpr inline uint32_t unk_1 = 2118;
			static constexpr inline uint32_t unk_2 = 2121;
		}slot;
		static class casino_lucky_wheel
		{
		public:
			static constexpr inline uint32_t podium_vehicle = 273 + 14;
			static constexpr inline uint32_t trigger_wheel = 273 + 45;
		}lucky_wheel;
	public:
		//fm_mission_controller.ysc
		static constexpr inline uint32_t take_casino = 19679 + 2686;//19406
		static constexpr inline uint32_t vault_door = 10082 + 7;//9842
		static constexpr inline uint32_t vault_door_total = 10082 + 37;
		static constexpr inline uint32_t tc_live = 26105 + 1322 + 1;
		static constexpr inline uint32_t finger_print = 52929; //52899 52649 DLC_H3_Fingerprint_Hack_Scene
		static constexpr inline uint32_t door_hack = 53991; //53729 53711 DLC_H3_Door_Hack_Scene
		static constexpr inline uint32_t board_hacking_x = 11731 + 26;//11471
		static constexpr inline uint32_t board_hacking_y = 11731 + 27;
		static constexpr inline uint32_t board_hacking_requirement = 11731 + 39;
		static constexpr inline uint32_t doomsday_act_3_hack = 1263 + 5;//1343
		static constexpr inline uint32_t set_vault_door_broken = 59295;//59294
		static constexpr inline int32_t instant_casino_complete = 19679 + 1;
		static constexpr inline int32_t instant_casino_complete_2 = 19679 + 1374 + 1;

		//fm_mission_controller_2020.ysc
		static constexpr inline uint32_t take_cayo = 41707 + 1392 + 53;//39493 + 1536 + 53 //31600 + 9482 (41082) 39493.f_1589
		static constexpr inline uint32_t take_cayo_2 = 41334; //41112 1.58
		static constexpr inline uint32_t tc_live_c = 44664 + 865 + 1;//42692 + 1009 + 1;
		static constexpr inline uint32_t finger_clone = 23385; //23181
		static constexpr inline uint32_t voltage_hack_target = 1715;
		static constexpr inline uint32_t voltage_hack_current = 1716;
		static constexpr inline uint32_t glass_cutter_power = 28736 + 4;
		static constexpr inline uint32_t glass_cutter_heat = 28736 + 3;
		static constexpr inline int32_t skip_sewer_cutter = 27500;
		static constexpr inline uint32_t underwater_torch_total = 28708;
		static constexpr inline uint32_t underwater_torch_sound = 28713;
		static constexpr inline int32_t safe_hack = 28715;
		static constexpr inline int32_t instant_mission_complete = 41707 + 1;
		static constexpr inline int32_t instant_mission_complete_2 = 41707 + 1374 + 1;//38257;


		//heist_island_planning.ysc
		static constexpr inline uint32_t submarine_computer = 1523;

		//gb_contraband_buy.ysc
		static constexpr inline uint32_t special_cargo_buying = 596;

		//gb_contraband_sell.ysc
		static constexpr inline uint32_t special_cargo_sell = 538;

		//gb_gunrunnning.ysc
		static constexpr inline uint32_t bunker_sell = 1203;
		static constexpr inline uint32_t bunker_sell_time_remaining = 1185;

		//gb_biker_contraband_sell.ysc
		static constexpr inline uint32_t mc_sell = 696;

		//business_battle_sell.ysc
		static constexpr inline uint32_t nc_sell = 2304;
		static constexpr inline uint32_t nc_time_remaining = 745;


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