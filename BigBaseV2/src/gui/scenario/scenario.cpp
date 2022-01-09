#include "natives.hpp"
#include "common.hpp"
#include "gta_util.hpp"
#include "script_local.hpp"
#include "gta\VehicleValues.h"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include "features.hpp"
#include "gui/controller/ScriptController.h"
#include <gta\Weapons.h>
#include <gui/controller/game_variable.h>
#include <gui/player/player_option.h>
#include <gui/entity/entity_control.h>
#include "gui/object/object.h"
#include "gui/controller/memory_address.hpp"
#include "gui/controller/system_control.h"
#include "gta/net_object_mgr.hpp"
#include "gui/weapons/weapon_helper.h"
#include "gui/vehicle/vehicle_helper.h"
#include "gui/scenario/scenario.h"


namespace big
{
	void scenario::play_scenario(Ped ped, const char* scenario, bool PlayEnterAnim)
	{
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, scenario, 0, PlayEnterAnim);
	}

	void scenario::play_animation(Ped ped, const char* anim_dictionary,const char* anim_name)
	{
		const char* anim = controller::load_anim(anim_name);
		TASK::TASK_PLAY_ANIM(ped, anim_dictionary, anim, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	}

	void scenario::Sexy(Ped ped)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(ped)) return;
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		const char* animID = "ld_2g_p2_s2";
		const char* anim = controller::load_anim("mini@strip_club@lap_dance_2g@ld_2g_p2");

		TASK::TASK_PLAY_ANIM(ped, anim, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	}

	void scenario::Sex(Ped ped)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(ped)) return;
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		const char* animID = "shag_loop_a";
		const char* anim = controller::load_anim("rcmpaparazzo_2");

		TASK::TASK_PLAY_ANIM(ped, anim, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	}

	void scenario::Stripper(Ped ped)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(ped)) return;
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		const char* animID = "stripper_idle_04";
		const char* anim = controller::load_anim("mini@strip_club@idles@stripper");
		
		TASK::TASK_PLAY_ANIM(ped, anim, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	}

	void scenario::Pole(Ped ped)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(ped)) return;
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		const char* anim = "mini@strip_club@pole_dance@pole_dance2";
		const char* animID = "pd_dance_02";
		controller::load_anim(anim);

		TASK::TASK_PLAY_ANIM(ped, anim, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	}

	void scenario::Push(Ped ped)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(ped)) return;
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		const char* anim = "amb@world_human_push_ups@male@base";
		const char* animID = "base";
		controller::load_anim(anim);

		TASK::TASK_PLAY_ANIM(ped, anim, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	}

	void scenario::Sit(Ped ped)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(ped)) return;
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		const char* anim = "amb@world_human_sit_ups@male@base";
		const char* animID = "base";
		controller::load_anim(anim);

		TASK::TASK_PLAY_ANIM(ped, anim, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	}

	void scenario::Celebrate(Ped ped)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(ped)) return;
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		const char* anim = "rcmfanatic1celebrate";
		const char* animID = "celebrate";
		controller::load_anim(anim);

		TASK::TASK_PLAY_ANIM(ped, anim, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	}

	void scenario::Electrocution(Ped ped)
	{

		if (!ENTITY::DOES_ENTITY_EXIST(ped)) return;
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		const char* anim = "ragdoll@human";
		const char* animID = "electrocute";
		controller::load_anim(anim);

		TASK::TASK_PLAY_ANIM(ped, anim, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	}

	void scenario::Suicide(Ped ped)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(ped)) return;
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		const char* anim = "mp_suicide";
		const char* animID = "pistol";
		controller::load_anim(anim);

		TASK::TASK_PLAY_ANIM(ped, anim, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	}

	void scenario::Showering(Ped ped)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(ped)) return;
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		const char* anim = "mp_safehouseshower@male@";
		const char* animID = "male_shower_idle_b";
		controller::load_anim(anim);

		TASK::TASK_PLAY_ANIM(ped, anim, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	}

	void scenario::Dog(Ped ped)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(ped)) return;
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		const char* anim = "missfra0_chop_find";
		const char* animID = "hump_loop_chop";
		controller::load_anim(anim);

		TASK::TASK_PLAY_ANIM(ped, anim, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	}

	void scenario::meditation(Ped ped)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(ped)) return;
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		const char* anim = "rcmcollect_paperleadinout@";
		const char* animID = "meditiate_idle";
		controller::load_anim(anim);

		TASK::TASK_PLAY_ANIM(ped, anim, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	}

	void scenario::SexTake(Ped ped)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(ped)) return;
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		const char* anim = "rcmpaparazzo_2";
		const char* animID = "shag_loop_poppy";
		controller::load_anim(anim);

		TASK::TASK_PLAY_ANIM(ped, anim, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	}

	void scenario::onfire(Ped ped)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(ped)) return;
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		const char* anim = "random@arrests";
		const char* animID = "kneeling_arrest_idle";
		controller::load_anim(anim);

		TASK::TASK_PLAY_ANIM(ped, anim, animID, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	}

	void scenario::Musician(Ped ped)
	{
		const char* anim = "WORLD_HUMAN_MUSICIAN";
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, anim, 0, true);
	}

	void scenario::Welding(Ped ped)
	{
		const char* anim = "WORLD_HUMAN_WELDING";
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, anim, 0, true);
	}

	void scenario::Lifting(Ped ped)
	{
		const char* anim = "WORLD_HUMAN_MUSCLE_FREE_WEIGHTS";
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, anim, 0, true);
	}

	void scenario::Gardener(Ped ped)
	{
		const char* anim = "WORLD_HUMAN_GARDENER_LEAF_BLOWER";
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, anim, 0, true);
	}

	void scenario::Binoculars(Ped ped)
	{
		const char* anim = "WORLD_HUMAN_BINOCULARS";
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, anim, 0, true);
	}

	void scenario::Bum(Ped ped)
	{
		const char* anim = "WORLD_HUMAN_BUM_FREEWAY";
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, anim, 0, true);
	}

	void scenario::High(Ped ped)
	{
		const char* anim = "WORLD_HUMAN_PROSTITUTE_HIGH_CLASS";
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, anim, 0, true);
	}

	void scenario::Smoke(Ped ped)
	{
		const char* anim = "WORLD_HUMAN_AA_SMOKE";
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, anim, 0, true);
	}

	void scenario::Hammering(Ped ped)
	{
		const char* anim = "WORLD_HUMAN_HAMMERING";
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, anim, 0, true);
	}

	void scenario::Maid(Ped ped)
	{
		const char* anim = "WORLD_HUMAN_MAID_CLEAN";
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, anim, 0, true);
	}

	void scenario::Paparazzi(Ped ped)
	{
		const char* anim = "WORLD_HUMAN_PAPARAZZI";
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, anim, 0, true);
	}

	void scenario::Strip(Ped ped)
	{
		const char* anim = "PROP_HUMAN_SEAT_STRIP_WATCH";
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, anim, 0, true);
	}

	void scenario::Partying(Ped ped)
	{
		const char* anim = "WORLD_HUMAN_PARTYING";
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, anim, 0, true);
	}

	void scenario::Smoking(Ped ped)
	{
		const char* anim = "WORLD_HUMAN_SMOKING_POT";
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, anim, 0, true);
	}

	void scenario::Stupor(Ped ped)
	{
		const char* anim = "WORLD_HUMAN_STUPOR";
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, anim, 0, true);
	}

	void scenario::Sumbathe(Ped ped)
	{
		const char* anim = "WORLD_HUMAN_SUNBATHE";
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, anim, 0, true);
	}

	void scenario::Tourist(Ped ped)
	{
		const char* anim = "WORLD_HUMAN_TOURIST_MOBILE";
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, anim, 0, true);
	}

	void scenario::Statue(Ped ped)
	{
		const char* anim = "WORLD_HUMAN_HUMAN_STATUE";
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		TASK::TASK_START_SCENARIO_IN_PLACE(ped, anim, 0, true);
	}

	const char* const scenario::scenario_name[]{ "Disable", "Standing","WORLD_HUMAN_AA_COFFEE","WORLD_HUMAN_AA_SMOKE","WORLD_HUMAN_BINOCULARS","WORLD_HUMAN_BUM_FREEWAY","WORLD_HUMAN_BUM_SLUMPED","WORLD_HUMAN_BUM_STANDING","WORLD_HUMAN_BUM_WASH","WORLD_HUMAN_VALET","WORLD_HUMAN_CAR_PARK_ATTENDANT","WORLD_HUMAN_CHEERING","WORLD_HUMAN_CLIPBOARD","WORLD_HUMAN_CLIPBOARD_FACILITY","WORLD_HUMAN_CONST_DRILL","WORLD_HUMAN_COP_IDLES","WORLD_HUMAN_DRINKING","WORLD_HUMAN_DRINKING_FACILITY","WORLD_HUMAN_DRINKING_CASINO_TERRACE","WORLD_HUMAN_DRUG_DEALER","WORLD_HUMAN_DRUG_DEALER_HARD","WORLD_HUMAN_MOBILE_FILM_SHOCKING","WORLD_HUMAN_GARDENER_LEAF_BLOWER","WORLD_HUMAN_GARDENER_PLANT","WORLD_HUMAN_GOLF_PLAYER","WORLD_HUMAN_GUARD_PATROL","WORLD_HUMAN_GUARD_STAND","WORLD_HUMAN_GUARD_STAND_CASINO","WORLD_HUMAN_GUARD_STAND_CLUBHOUSE","WORLD_HUMAN_GUARD_STAND_FACILITY","WORLD_HUMAN_GUARD_STAND_ARMY","WORLD_HUMAN_HAMMERING","WORLD_HUMAN_HANG_OUT_STREET","WORLD_HUMAN_HANG_OUT_STREET_CLUBHOUSE","WORLD_HUMAN_HIKER","WORLD_HUMAN_HIKER_STANDING","WORLD_HUMAN_HUMAN_STATUE","WORLD_HUMAN_JANITOR","WORLD_HUMAN_JOG","WORLD_HUMAN_JOG_STANDING","WORLD_HUMAN_LEANING","WORLD_HUMAN_LEANING_CASINO_TERRACE","WORLD_HUMAN_MAID_CLEAN","WORLD_HUMAN_MUSCLE_FLEX","WORLD_HUMAN_MUSCLE_FREE_WEIGHTS","WORLD_HUMAN_MUSICIAN","WORLD_HUMAN_PAPARAZZI","WORLD_HUMAN_PARTYING","WORLD_HUMAN_PICNIC","WORLD_HUMAN_POWER_WALKER","WORLD_HUMAN_PROSTITUTE_HIGH_CLASS","WORLD_HUMAN_PROSTITUTE_LOW_CLASS","WORLD_HUMAN_PUSH_UPS","WORLD_HUMAN_SEAT_LEDGE","WORLD_HUMAN_SEAT_LEDGE_EATING","WORLD_HUMAN_SEAT_STEPS","WORLD_HUMAN_SEAT_WALL","WORLD_HUMAN_SEAT_WALL_EATING","WORLD_HUMAN_SEAT_WALL_TABLET","WORLD_HUMAN_SECURITY_SHINE_TORCH","WORLD_HUMAN_SIT_UPS","WORLD_HUMAN_SMOKING","WORLD_HUMAN_SMOKING_CLUBHOUSE","WORLD_HUMAN_SMOKING_POT","WORLD_HUMAN_SMOKING_POT_CLUBHOUSE","WORLD_HUMAN_STAND_FIRE","WORLD_HUMAN_STAND_FISHING","WORLD_HUMAN_STAND_IMPATIENT","WORLD_HUMAN_STAND_IMPATIENT_CLUBHOUSE","WORLD_HUMAN_STAND_IMPATIENT_FACILITY","WORLD_HUMAN_STAND_IMPATIENT_UPRIGHT","WORLD_HUMAN_STAND_IMPATIENT_UPRIGHT_FACILITY","WORLD_HUMAN_STAND_MOBILE","WORLD_HUMAN_STAND_MOBILE_CLUBHOUSE","WORLD_HUMAN_STAND_MOBILE_FACILITY","WORLD_HUMAN_STAND_MOBILE_UPRIGHT","WORLD_HUMAN_STAND_MOBILE_UPRIGHT_CLUBHOUSE","WORLD_HUMAN_STRIP_WATCH_STAND","WORLD_HUMAN_STUPOR","WORLD_HUMAN_STUPOR_CLUBHOUSE","WORLD_HUMAN_SUNBATHE","WORLD_HUMAN_SUNBATHE_BACK","WORLD_HUMAN_SUPERHERO","WORLD_HUMAN_SWIMMING","WORLD_HUMAN_TENNIS_PLAYER","WORLD_HUMAN_TOURIST_MAP","WORLD_HUMAN_TOURIST_MOBILE","WORLD_HUMAN_VEHICLE_MECHANIC","WORLD_HUMAN_WELDING","WORLD_HUMAN_WINDOW_SHOP_BROWSE","WORLD_HUMAN_YOGA","Walk","Walk_Facility","WORLD_BOAR_GRAZING","WORLD_CAT_SLEEPING_GROUND","WORLD_CAT_SLEEPING_LEDGE","WORLD_COW_GRAZING","WORLD_COYOTE_HOWL","WORLD_COYOTE_REST","WORLD_COYOTE_WANDER","WORLD_COYOTE_WALK","WORLD_CHICKENHAWK_FEEDING","WORLD_CHICKENHAWK_STANDING","WORLD_CORMORANT_STANDING","WORLD_CROW_FEEDING","WORLD_CROW_STANDING","WORLD_DEER_GRAZING","WORLD_DOG_BARKING_ROTTWEILER","WORLD_DOG_BARKING_RETRIEVER","WORLD_DOG_BARKING_SHEPHERD","WORLD_DOG_SITTING_ROTTWEILER","WORLD_DOG_SITTING_RETRIEVER","WORLD_DOG_SITTING_SHEPHERD","WORLD_DOG_BARKING_SMALL","WORLD_DOG_SITTING_SMALL","WORLD_DOLPHIN_SWIM","WORLD_FISH_FLEE","WORLD_FISH_IDLE","WORLD_GULL_FEEDING","WORLD_GULL_STANDING","WORLD_HEN_FLEE","WORLD_HEN_PECKING","WORLD_HEN_STANDING","WORLD_MOUNTAIN_LION_REST","WORLD_MOUNTAIN_LION_WANDER","WORLD_ORCA_SWIM","WORLD_PIG_GRAZING","WORLD_PIGEON_FEEDING","WORLD_PIGEON_STANDING","WORLD_RABBIT_EATING","WORLD_RABBIT_FLEE","WORLD_RATS_EATING","WORLD_RATS_FLEEING","WORLD_SHARK_SWIM","WORLD_SHARK_HAMMERHEAD_SWIM","WORLD_STINGRAY_SWIM","WORLD_WHALE_SWIM","DRIVE","WORLD_VEHICLE_ATTRACTOR","PARK_VEHICLE","WORLD_VEHICLE_AMBULANCE","WORLD_VEHICLE_BICYCLE_BMX","WORLD_VEHICLE_BICYCLE_BMX_BALLAS","WORLD_VEHICLE_BICYCLE_BMX_FAMILY","WORLD_VEHICLE_BICYCLE_BMX_HARMONY","WORLD_VEHICLE_BICYCLE_BMX_VAGOS","WORLD_VEHICLE_BICYCLE_MOUNTAIN","WORLD_VEHICLE_BICYCLE_ROAD","WORLD_VEHICLE_BIKE_OFF_ROAD_RACE","WORLD_VEHICLE_BIKER","WORLD_VEHICLE_BOAT_IDLE","WORLD_VEHICLE_BOAT_IDLE_ALAMO","WORLD_VEHICLE_BOAT_IDLE_MARQUIS","WORLD_VEHICLE_BROKEN_DOWN","WORLD_VEHICLE_BUSINESSMEN","WORLD_VEHICLE_HELI_LIFEGUARD","WORLD_VEHICLE_CLUCKIN_BELL_TRAILER","WORLD_VEHICLE_CONSTRUCTION_SOLO","WORLD_VEHICLE_CONSTRUCTION_PASSENGERS","WORLD_VEHICLE_DRIVE_PASSENGERS","WORLD_VEHICLE_DRIVE_PASSENGERS_LIMITED","WORLD_VEHICLE_DRIVE_SOLO","WORLD_VEHICLE_FARM_WORKER","WORLD_VEHICLE_FIRE_TRUCK","WORLD_VEHICLE_EMPTY","WORLD_VEHICLE_MARIACHI","WORLD_VEHICLE_MECHANIC","WORLD_VEHICLE_MILITARY_PLANES_BIG","WORLD_VEHICLE_MILITARY_PLANES_SMALL","WORLD_VEHICLE_PARK_PARALLEL","WORLD_VEHICLE_PARK_PERPENDICULAR_NOSE_IN","WORLD_VEHICLE_PASSENGER_EXIT","WORLD_VEHICLE_POLICE_BIKE","WORLD_VEHICLE_POLICE_CAR","WORLD_VEHICLE_POLICE_NEXT_TO_CAR","WORLD_VEHICLE_QUARRY","WORLD_VEHICLE_SALTON","WORLD_VEHICLE_SALTON_DIRT_BIKE","WORLD_VEHICLE_SECURITY_CAR","WORLD_VEHICLE_STREETRACE","WORLD_VEHICLE_TOURBUS","WORLD_VEHICLE_TOURIST","WORLD_VEHICLE_TANDL","WORLD_VEHICLE_TRACTOR","WORLD_VEHICLE_TRACTOR_BEACH","WORLD_VEHICLE_TRUCK_LOGS","WORLD_VEHICLE_TRUCKS_TRAILERS","PROP_BIRD_IN_TREE","WORLD_VEHICLE_DISTANT_EMPTY_GROUND","PROP_BIRD_TELEGRAPH_POLE","PROP_HUMAN_ATM","PROP_HUMAN_BBQ","PROP_HUMAN_BUM_BIN","PROP_HUMAN_BUM_SHOPPING_CART","PROP_HUMAN_MUSCLE_CHIN_UPS","PROP_HUMAN_MUSCLE_CHIN_UPS_ARMY","PROP_HUMAN_MUSCLE_CHIN_UPS_PRISON","PROP_HUMAN_PARKING_METER","PROP_HUMAN_SEAT_ARMCHAIR","PROP_HUMAN_SEAT_BAR","PROP_HUMAN_SEAT_BENCH","PROP_HUMAN_SEAT_BENCH_FACILITY","PROP_HUMAN_SEAT_BENCH_DRINK","PROP_HUMAN_SEAT_BENCH_DRINK_FACILITY","PROP_HUMAN_SEAT_BENCH_DRINK_BEER","PROP_HUMAN_SEAT_BENCH_FOOD","PROP_HUMAN_SEAT_BENCH_FOOD_FACILITY","PROP_HUMAN_SEAT_BUS_STOP_WAIT","PROP_HUMAN_SEAT_CHAIR","PROP_HUMAN_SEAT_CHAIR_DRINK","PROP_HUMAN_SEAT_CHAIR_DRINK_BEER","PROP_HUMAN_SEAT_CHAIR_FOOD","PROP_HUMAN_SEAT_CHAIR_UPRIGHT","PROP_HUMAN_SEAT_CHAIR_MP_PLAYER","PROP_HUMAN_SEAT_COMPUTER","PROP_HUMAN_SEAT_COMPUTER_LOW","PROP_HUMAN_SEAT_DECKCHAIR","PROP_HUMAN_SEAT_DECKCHAIR_DRINK","PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS","PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS_PRISON","PROP_HUMAN_SEAT_SEWING","PROP_HUMAN_SEAT_STRIP_WATCH","PROP_HUMAN_SEAT_SUNLOUNGER","PROP_HUMAN_STAND_IMPATIENT","CODE_HUMAN_COWER","CODE_HUMAN_CROSS_ROAD_WAIT","CODE_HUMAN_PARK_CAR","PROP_HUMAN_MOVIE_BULB","PROP_HUMAN_MOVIE_STUDIO_LIGHT","CODE_HUMAN_MEDIC_KNEEL","CODE_HUMAN_MEDIC_TEND_TO_DEAD","CODE_HUMAN_MEDIC_TIME_OF_DEATH","CODE_HUMAN_POLICE_CROWD_CONTROL","CODE_HUMAN_POLICE_INVESTIGATE","CHAINING_ENTRY","CHAINING_EXIT","CODE_HUMAN_STAND_COWER","EAR_TO_TEXT","EAR_TO_TEXT_FAT","WORLD_LOOKAT_POINT" };
}