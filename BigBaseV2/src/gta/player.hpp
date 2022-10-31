#pragma once
#include <cstdint>
#include "fwddec.hpp"
#include "extensible.hpp"
#include "vector.hpp"
#include "gta\natives.hpp"

#pragma pack(push, 1)
namespace rage
{
#	pragma warning(push)
#	pragma warning(disable : 4201) // nonstandard extension used: nameless struct/union
	union netAddress
	{
		std::uint32_t m_raw;
		struct
		{
			std::uint8_t m_field4;
			std::uint8_t m_field3;
			std::uint8_t m_field2;
			std::uint8_t m_field1;
		};
	};
#	pragma warning(pop)

	class netPlayerData
	{
	public:
		char pad_0000[8]; //0x0000
		uint64_t m_rockstar_id; //0x0008
		char pad_0010[52]; //0x0010
		uint32_t m_relay_ip; //0x0044
		uint16_t m_relay_port; //0x0048
		char pad_004A[2]; //0x004A
		uint32_t m_external_ip; //0x004C
		uint16_t m_external_port; //0x0050
		char pad_0052[2]; //0x0052
		uint32_t m_internal_ip; //0x0054
		uint16_t m_internal_port; //0x0058
		char pad_005A[6]; //0x005A
		uint64_t m_host_token; //0x0060
		uint64_t m_peer_id; //0x0068
		uint64_t m_rockstar_id2; //0x0070
		char pad_0078[12]; //0x0078
		char m_name[20]; //0x0084
	}; //Size: 0x0098
	static_assert(sizeof(netPlayerData) == 0x98);

	class nonPhysicalPlayerDataBase
	{
	public:
		virtual ~nonPhysicalPlayerDataBase() = default;    // 0 (0x00)
		virtual void unk_0x08() = 0;                       // 1 (0x08)
		virtual void unk_0x10() = 0;                       // 2 (0x10)
		virtual void unk_0x18() = 0;                       // 3 (0x18)
		virtual void log(netLoggingInterface* logger) = 0; // 4 (0x20)
	};

	class netPlayer
	{
	public:
		virtual ~netPlayer() = default;            // 0 (0x00)
		virtual void reset() = 0;                  // 1 (0x08)
		virtual bool is_valid() const = 0;         // 2 (0x10)
		virtual const char *get_name() const = 0;  // 3 (0x18)
		virtual void _0x20() = 0;                  // 4 (0x20)
		virtual bool is_host() = 0;                // 5 (0x28)
		virtual netPlayerData *get_net_data() = 0; // 6 (0x30)
		virtual void _0x38() = 0;                  // 7 (0x38)
	};

	class netPlayerMgrBase
	{
	public:
		virtual ~netPlayerMgrBase() = default; // 0 (0x00)
	};
}

namespace gta
{
	inline constexpr auto num_players = 32;
}

class CNonPhysicalPlayerData : public rage::nonPhysicalPlayerDataBase
{
public:
	std::int32_t  m_bubble_id; // 0x08
	std::int32_t  m_player_id; // 0x0C
	rage::vector3 m_position;  // 0x10
};

class CNetGamePlayer : public rage::netPlayer
{
public:
	char pad_0008[8]; //0x0008
	class CNonPhysicalPlayerData* m_non_physical_player; //0x0010
	uint32_t m_msg_id; //0x0018
	char pad_001C[4]; //0x001C
	uint8_t m_active_id; //0x0020
	int8_t player_id; //0x0021
	char pad_0022[3]; //0x0022
	uint16_t m_complaints; //0x0025
	char pad_0027[17]; //0x0027
	class CNetGamePlayer* m_unk_net_player_list[10]; //0x0038
	char pad_0088[24]; //0x0088
	CPlayerInfo* player_info; //0x00A0
	char pad_00A8[20]; //0x00A8
	uint32_t bubble_id; //0x00BC
	uint32_t player; //0x00C0
}; //Size: 0x00C4
static_assert(sizeof(CNetGamePlayer) == 0xC4);

class CNetworkPlayerMgr
{
public:
	char pad_0x0000[376]; //0x0000
	int32_t num_player; //0x0178 
	char pad_0x017C[4]; //0x017C
	CNetGamePlayer* m_get_player[33]; //0x0180
};
static_assert(sizeof(CNetworkPlayerMgr) == 0x288);

class CutsceneManager
{
public:
	char pad_0000[0xC98]; //0x0000
	int m_end_cutscene; //0xC98
};
static_assert(sizeof(CutsceneManager) == 0xC9C, "CutsceneManager Not Sized Properly");

class VehicleCollision
{
public:
	char pad_0000[44];
	float m_collision; //0x02C
};
static_assert(sizeof(VehicleCollision) == 0x030);

class phBoundGeometry
{
public:
	VehicleCollision* m_ph_geometry[0x40]; //0x00
};
static_assert(sizeof(phBoundGeometry) == 0x200);

class phBoundComposite
{
public:
	char pad_0000[0x70]; //0x0000
	phBoundGeometry *m_ph_composite; //0x0070
};
static_assert(sizeof(phBoundComposite) == 0x078);

class phArcheTypeDamp
{
public:
	char pad_0000[32]; //0x0020
	phBoundComposite* m_ph_bound; //0x0020
	char pad_0028[44]; //0x028
	float m_water_collision; //0x054
	VehicleCollision* get_geometry(const int& index)
	{
		if (m_ph_bound->m_ph_composite->m_ph_geometry[index] != nullptr)
			return m_ph_bound->m_ph_composite->m_ph_geometry[index];
		return nullptr;
	}
};
static_assert(sizeof(phArcheTypeDamp) == 0x58);

class CNavigation
{
public:
	char pad_0000[16]; //0x0000
	phArcheTypeDamp* m_ph_arche; //0x0010
	char pad_0018[8]; //0x0018
	rage::vector2 m_heading; //0x0020
	char pad_0028[8]; //0x0028
	rage::vector3 m_rotation; //0x0030
	char pad_003C[20]; //0x003C
	rage::vector3 m_position; //0x0050
}; //Size: 0x005C
static_assert(sizeof(CNavigation) == 0x5C);

class CWeaponAmmo
{
public:
	char pad_0000[32]; //0x0000
	int16_t m_ammo; //0x0020
	char pad_0022[2]; //0x0022
	bool m_infinite_ammo; //0x0024
};
static_assert(sizeof(CWeaponAmmo) == 0x25);

class CWeaponPointer
{
public:
	CWeaponAmmo* m_weapon_ammo[48];
};
static_assert(sizeof(CWeaponPointer) == 0x180);

class CPedInventory
{
public:
	char pad_0000[72]; //0x0000
	CWeaponPointer *m_weapon_list; //0x0048
	int16_t m_total_player_weapon; //0x0050
	char pad_0052[38]; //0x0052
	int m_weapon_ammo_flag; //0x0078

	void enable_infinite_ammo() { m_weapon_ammo_flag |= (1 << 0); }
	void disable_infinite_ammo() { m_weapon_ammo_flag &= ~(1 << 0); }
	bool is_infinite_ammo() { return (m_weapon_ammo_flag & (1 << 0)); }

	void enable_infinite_clip() { m_weapon_ammo_flag |= (1 << 1); }
	void disable_infinite_clip() { m_weapon_ammo_flag &= ~(1 << 1); }
	bool is_infinite_clip() { return (m_weapon_ammo_flag & (1 << 1)); }
};
static_assert(sizeof(CPedInventory) == 0x7C);

class CPedWeaponManager
{
public:
	char pad_0000[16]; //0x0000
	class CPed* m_owner; //0x0010
	uint32_t m_selected_weapon_hash; //0x0018
	uint32_t m_name_hash; //0x001C
	class CWeaponInfo* m_weapon_info; //0x0020
	char pad_0028[72]; //0x0028
	class CWeaponInfo* m_vehicle_weapon_info; //0x0070
	char pad_0078[312]; //0x0078
	rage::vector3 m_last_impact_coords; //0x01B0
}; //Size: 0x0028
static_assert(sizeof(CPedWeaponManager) == 0x1BC, "CPedWeaponManager is not properly sized");

class CWeaponInfoName
{
public:
	char m_weapon_name[10];
};

class CWeaponInfo
{
public:
	char pad_0000[16]; //0x0000
	uint32_t m_weapon_hash; //0x0010
	char pad_0014[12]; //0x0014
	int32_t m_impact_type; //0x0020
	int32_t m_impact_explosion_type; //0x0024
	char pad_0028[44]; //0x0028
	int32_t m_bullet_modifier; //0x0054
	char pad_0058[8]; //0x0058
	class CAmmoModifier* m_ammo_modifier; //0x0060
	char pad_0068[12]; //0x0068
	float m_weapon_spread; //0x0074
	float m_accurate_mode_accuracy_modifier; //0x0078
	float m_run_and_gun_accuracy; //0x007C
	float m_run_and_gun_min_accuracy; //0x0080
	float m_recoil_accuracy_max; //0x0084
	float m_recoil_error_time; //0x0088
	float m_recoil_recovery_rate; //0x008C
	float m_recoil_accuracy_to_allow_headshot_ai; //0x0090
	float m_min_headshot_distance_ai; //0x0094
	float m_max_headshot_distance_ai; //0x0098
	float m_headshot_damage_modifier_ai; //0x009C
	float m_bullet_damage; //0x00A0
	float m_min_headshot_distance_player; //0x00A4
	float m_max_headshot_distance_player; //0x00A8
	float m_headshot_damage_modifier_player; //0x00AC
	float m_damage; //0x00B0
	float m_damage_time; //0x00B4
	float m_damage_time_in_vehicle; //0x00B8
	float m_damage_time_in_vehicle_headshot; //0x00BC
	float N000008F9; //0x00C0
	uint32_t N00000898; //0x00C4
	float m_hit_limbs_damage_modifier; //0x00C8
	float m_network_hit_limbs_damage_modifier; //0x00CC
	float m_lightly_armoured_damage_modifier; //0x00D0
	float m_vehicle_damage_modifier; //0x00D4
	float m_bullet_mass; //0x00D8
	float m_ped_force; //0x00DC
	float m_vehicle_force; //0x00E0
	float m_heli_force; //0x00E4
	char pad_00E8[16]; //0x00E8
	float m_force_max_strength_mult; //0x00F8
	float m_force_falloff_range_start; //0x00FC
	float m_force_falloff_range_end; //0x0100
	float m_force_falloff_range_min; //0x0104
	float m_project_force; //0x0108
	float m_frag_impulse; //0x010C
	float m_penetration; //0x0110
	float m_vertical_launch_adjustment; //0x0114
	float m_drop_forward_velocity; //0x0118
	float m_speed; //0x011C
	int32_t m_bullet_batch; //0x0120
	float m_batch_spread; //0x0124
	float m_reload_time_mp; //0x0128
	float m_reload_time_sp; //0x012C
	float m_vehicle_reload_time; //0x0130
	float m_reload_speed; //0x0134
	int32_t m_bullets_per_anime_loop; //0x0138
	float m_time_between_shots; //0x013C
	float m_time_left_between_shots_where_should_fire_is_cached; //0x0140
	float m_spinup_time; //0x0144
	float m_spin_time; //0x0148
	float m_spindown_time; //0x014C
	float m_alternate_wait_time; //0x0150
	char pad_0154[296]; //0x0154
	float m_network_player_damage_modifier; //0x027C
	float m_network_ped_damage_modifier; //0x0280
	float m_network_headshot_modifier; //0x0284
	float m_lock_on_range; //0x0288
	float m_weapon_range; //0x028C
	char pad_0290[8]; //0x0290
	float m_damage_fall_off_range_min; //0x0298
	float m_damage_fall_off_range_max; //0x029C
	float m_damage_fall_off_modifier; //0x02A0
	char pad_02A4[64]; //0x02A4
	uint32_t m_recoil_shake_hash; //0x02E4
	uint32_t m_recoil_shake_hash_first_person; //0x02E8
	float m_min_time_between_recoil_shakes; //0x02EC
	float m_recoil_shake_amplitude; //0x02F0
	float m_weapon_recoil; //0x02F4
	char pad_02F8[760]; //0x02F8
	class CWeaponInfoName* m_weapon_name_info; //0x05F0
}; //Size: 0x02F8
static_assert(sizeof(CWeaponInfo) == 0x5F8);

class CAmmoModifier
{
public:
	char pad_0000[16]; //0x0000
	uint64_t m_bullet_type; //0x0010
}; //Size: 0x0018
static_assert(sizeof(CAmmoModifier) == 0x18);

class CBaseModelInfo
{
public:
	char pad_0000[24]; //0x0000
	uint32_t m_model_hash; //0x0018
	char pad_001C[20]; //0x001C
	rage::vector3 m_min_dimensions; //0x0030
	char pad_003C[4]; //0x003C
	rage::vector3 m_max_dimensions; //0x0040
	char pad_004C[81]; //0x004C
	uint8_t m_model_type; //0x009D
	char pad_009E[506]; //0x009E
	char m_vehicle_name[12]; //0x0298
	char m_factory_name[12]; //0x02A4
	char pad_02B0[144]; //0x02B0
	uint32_t m_vehicle_type; //0x0340
	uint32_t m_unk_vehicle_type; //0x0344
	uint32_t m_diffuse_tint; //0x0348
	char pad_034C[560]; //0x034C
	uint32_t m_flag_1; //0x057C
	uint32_t m_flag_2; //0x0580
	uint32_t m_flag_3; //0x0584
	uint32_t m_flag_4; //0x0588
	uint32_t m_flag_5; //0x058C
	uint32_t m_flag_6; //0x0590
	uint32_t m_flag_7; //0x0594
};
static_assert(sizeof(CBaseModelInfo) == 0x598);

class CHandlingData
{
public:
	char pad_0000[8]; //0x0000
	uint32_t m_model_hash; //0x0008
	float m_mass; //0x000C
	float m_initial_drag_coeff; //0x0010
	float m_downforce_multiplier; //0x0014
	float m_popup_light_rotation; //0x0018
	char pad_001C[4]; //0x001C
	rage::vector3 m_centre_of_mass; //0x0020
	char pad_002C[4]; //0x002C
	rage::vector3 m_inertia_mult; //0x0030
	char pad_003C[4]; //0x003C
	float m_buoyancy; //0x0040
	float m_drive_bias_rear; //0x0044
	float m_drive_bias_front; //0x0048
	float m_acceleration; //0x004C
	uint8_t m_initial_drive_gears; //0x0050
	char pad_0051[3]; //0x0051
	float m_drive_inertia; //0x0054
	float m_upshift; //0x0058
	float m_downshift; //0x005C
	float m_initial_drive_force; //0x0060
	float m_drive_max_flat_velocity; //0x0064
	float m_initial_drive_max_flat_vel; //0x0068
	float m_brake_force; //0x006C
	char pad_0070[4]; //0x0070
	float m_brake_bias_front; //0x0074
	float m_brake_bias_rear; //0x0078
	float m_handbrake_force; //0x007C
	float m_steering_lock; //0x0080
	float m_steering_lock_ratio; //0x0084
	float m_traction_curve_max; //0x0088
	float m_traction_curve_lateral; //0x008C
	float m_traction_curve_min; //0x0090
	float m_traction_curve_ratio; //0x0094
	float m_curve_lateral; //0x0098
	float m_curve_lateral_ratio; //0x009C
	float m_traction_spring_delta_max; //0x00A0
	float m_traction_spring_delta_max_ratio; //0x00A4
	float m_low_speed_traction_loss_mult; //0x00A8
	float m_camber_stiffness; //0x00AC
	float m_traction_bias_front; //0x00B0
	float m_traction_bias_rear; //0x00B4
	float m_traction_loss_mult; //0x00B8
	float m_suspension_force; //0x00BC
	float m_suspension_comp_damp; //0x00C0
	float m_suspension_rebound_damp; //0x00C4
	float m_suspension_upper_limit; //0x00C8
	float m_suspension_lower_limit; //0x00CC
	float m_suspension_raise; //0x00D0
	float m_suspension_bias_front; //0x00D4
	float m_suspension_bias_rear; //0x00D8
	float m_anti_rollbar_force; //0x00DC
	float m_anti_rollbar_bias_front; //0x00E0
	float m_anti_rollbar_bias_rear; //0x00E4
	float m_roll_centre_height_front; //0x00E8
	float m_roll_centre_height_rear; //0x00EC
	float m_collision_damage_mult; //0x00F0
	float m_weapon_damage_mult; //0x00F4
	float m_deformation_mult; //0x00F8
	float m_engine_damage_mult; //0x00FC
	float m_petrol_tank_volume; //0x0100
	float m_oil_volume; //0x0104
	char pad_0108[4]; //0x0108
	rage::vector3 m_seat_offset_dist; //0x010C
	uint32_t m_monetary_value; //0x0118
	char pad_011C[8]; //0x011C
	uint32_t m_model_flags; //0x0124
	uint32_t m_handling_flags; //0x0128
	uint32_t m_damage_flags; //0x012C
	char pad_0130[12]; //0x0130
	uint32_t m_ai_handling_hash; //0x013C
	char pad_0140[504]; //0x0140
	float m_flying_acceleration; //0x338
	char pad_033C[1636]; //0x33C
	int32_t m_weapon_1; //0x09A0
	int32_t m_weapon_2; //0x09A4
	int32_t m_weapon_3; //0x09A8
	int32_t m_weapon_4; //0x09AC
	int32_t m_weapon_5; //0x09B0
};
static_assert(sizeof(CHandlingData) == 0x9B4);

class CEntityDrawHandler
{
public:
	char pad_0000[904]; //0x0000
	uint8_t m_primary_color; //0x0388
	char pad_0389[3]; //0x0389
	uint8_t m_pearlescent; //0x038C
	char pad_038D[3]; //0x038D
	uint8_t m_secondary_color; //0x0390
	char pad_0391[15]; //0x0391
	uint8_t m_neon_blue; //0x03A0
	uint8_t m_neon_green; //0x03A1
	uint8_t m_neon_red; //0x03A2
	char pad_03A3[15]; //0x03A3
	uint8_t m_spoiler; //0x03B2
	uint8_t m_bumper_front; //0x03B3
	uint8_t m_bumper_rear; //0x03B4
	uint8_t m_sideskirts; //0x03B5
	uint8_t m_exhaust; //0x03B6
	uint8_t m_frame; //0x03B7
	uint8_t m_grille; //0x03B8
	uint8_t m_hood; //0x03B9
	uint8_t m_fenders; //0x03BA
	uint8_t m_bullbars; //0x03BB
	uint8_t m_roof; //0x03BC
	char pad_03BD[3]; //0x03BD
	uint8_t m_ornaments; //0x03C0
	char pad_03C1[1]; //0x03C1
	uint8_t m_dail_design; //0x03C2
	uint8_t m_sunstrips; //0x03C3
	uint8_t m_seats; //0x03C4
	uint8_t m_steering_wheel; //0x03C5
	uint8_t m_column_shifter_levers; //0x03C6
	char pad_03C7[2]; //0x03C7
	uint8_t m_truck_beds; //0x03C9
	char pad_03CA[4]; //0x03CA
	uint8_t m_roll_cages; //0x03CE
	uint8_t m_skid_plate; //0x03CF
	uint8_t m_secondary_light_surrounds; //0x03D0
	uint8_t m_hood_accessories; //0x03D1
	uint8_t m_doors; //0x03D2
	uint8_t m_snorkel; //0x03D3
	uint8_t m_livery; //0x03D4
	char pad_03D5[1]; //0x03D5
	uint8_t m_engine; //0x03D6
	uint8_t m_brakes; //0x03D7
	uint8_t m_transmission; //0x03D8
	uint8_t m_horn; //0x03D9
	uint8_t m_suspension; //0x03DA
	uint8_t m_armor; //0x03DB
	char pad_03DC[1]; //0x03DC
	uint8_t m_turbo; //0x03DD
	char pad_03DE[3]; //0x03DE
	uint8_t m_xenon; //0x03E1
	uint8_t m_tire_design; //0x03E2
	char pad_03E3[16]; //0x03E3
	uint8_t m_truck_bed; //0x03F3
	char pad_03F4[5]; //0x03F4
	uint8_t m_wheel_color; //0x03F9
	char pad_03FA[5]; //0x03FA
	uint8_t m_window; //0x03FF
	char pad_0400[2]; //0x0400
	uint8_t m_neon_left; //0x0402
	uint8_t m_neon_right; //0x0403
	uint8_t m_neon_front; //0x0404
	uint8_t m_neon_rear; //0x0405
}; //Size: 0x0406
static_assert(sizeof(CEntityDrawHandler) == 0x406);

class fwEntity
{
public:
	char pad_0000[32]; //0x0000
	class CBaseModelInfo* m_model_info; //0x0020
	char pad_0028[4]; //0x0028
	int8_t m_invisible; //0x002C
	char pad_002D[3]; //0x002D
	class CNavigation* m_navigation; //0x0030
	char pad_0038[1]; //0x0038
	int8_t m_entity_type; //0x0039
	char pad_003A[14]; //0x003A
	class CEntityDrawHandler* m_vehicle_draw; //0x0048
	char pad_0050[64]; //0x0050
	rage::vector3 m_entity_position; //0x0090
	char pad_009C[52]; //0x009C
	class netObject* m_net_object; //0x00D0
	char pad_00D8[176]; //0x00D8
	uint32_t m_damage_bits; //0x0188
	uint32_t m_hostility; //0x018C
	char pad_0190[168]; //0x0190
	int m_freeze_entity; //0x0238
	char pad_023C[68]; //0x023C
	float m_health; //0x0280
	float m_max_health; //0x0284
	char padding[28]; //0x0288

	bool is_invincible() { return (m_damage_bits & (1 << 8)); }
	void enable_invincible() { m_damage_bits |= (1 << 8); }
	void disable_invincible() { m_damage_bits &= ~(1 << 8); }

	bool is_water_proof() { return (m_damage_bits & (1 << 24)); }
	void enable_water_proof() { m_damage_bits |= (1 << 24); }
	void disable_water_proof() { m_damage_bits &= ~(1 << 24); }
}; //Size: 0x018C
static_assert(sizeof(fwEntity) == 0x2A4, "fwEntity is not properly sized");

class CVehicle : public fwEntity
{
public:
	char pad_02A4[104]; //0x0284
	float m_vehicle_boost; //0x0320
	char pad_0324[1308]; //0x0324
	float m_vehicle_health_2; //0x0840
	float m_vehicle_health_3; //0x0844
	char pad_0848[128]; //0x0848
	float m_initial_drive; //0x08C8
	char pad_08CC[60]; //0x08CC
	float m_vehicle_health_4; //0x0908
	char pad_090C[44]; //0x090C
	CHandlingData* m_handling; //0x0938
	char pad_0940[8]; //0x0940
	int8_t m_vehicle_headlight; //0x0948
	int8_t m_turn_light; //0x0949
	int8_t m_vehicle_engine; //0x094A
	char pad_094B[105]; //0x094B
	float m_vehicle_turning; //0x09B4
	char pad_09B8[4]; //0x09B8
	float m_vehicle_forward; //0x09BC
	float m_vehicle_brake; //0x09C0
	char pad_09C4[548]; //0x09C4
	int8_t m_vehicle_type; //0x0BE8
	char pad_0BE9[121]; //0x0BE9
	int8_t m_passanger; //0x0C62
	char pad_0C63[5]; //0x0C63
	CPed* m_driver_ped; //0x0C68
	char pad_0C70[140]; //0x0C70
	float m_gravity; //0x0CFC
	char pad_0D00[1440]; //0x0D00
	uint32_t m_vehicle_missile; //0x12A0
	uint32_t m_oppressor_missile; //0x12A4
	char pad_12A8[12]; //0x12A8
	uint32_t m_air_craft_bomb; //0x12B4
	uint32_t m_counter_meassure; //0x12B8
	char pad_12BC[2100]; //0x12BC
	float m_heli_rotor_1; //0x1AF0
	float m_heli_rotor_2; //0x1AF4
	float m_heli_rotor_3; //0x1AF8
	char pad_1AFC[480]; //0x1AFC
	float m_plane_rotor_1; //0x1CDC
	float m_plane_rotor_2; //0x1CE0
	float m_plane_rotor_3; //0x1CE4
	float m_plane_rotor_4; //0x1CE8
}; //Size: 0x1CD8
static_assert(sizeof(CVehicle) == 0x1CD8);

class UnknownPlayer
{
public:
	char pad_0000[0x278]; //0x0000
	float m_oxygen; //0x00278
};
static_assert(sizeof(UnknownPlayer) == 0x27C);

class CPlayerInfo : public rage::fwExtensibleBase
{
public:
	char pad_0020[52]; //0x0020
	uint32_t m_internal_ip; //0x0054
	uint16_t m_internal_port; //0x0058
	char pad_005A[2]; //0x005A
	uint32_t m_relay_ip; //0x005C
	uint16_t m_relay_port; //0x0060
	char pad_0062[10]; //0x0062
	uint32_t m_online_ip; //0x006C
	uint16_t m_online_port; //0x0070
	char pad_0072[2]; //0x0072
	uint32_t m_external_ip; //0x0074
	uint16_t m_external_port; //0x0078
	char pad_007A[6]; //0x007A
	uint32_t m_host_token; //0x0080
	char pad_0084[4]; //0x0084
	uint32_t m_peer_id; //0x0088
	char pad_008C[4]; //0x008C
	uint64_t m_rockstar_id; //0x0090
	char pad_0098[12]; //0x0098
	char m_name[20]; //0x00A4
	char pad_00B8[184]; //0x00B8
	float m_swim_speed; //0x0170
	char pad_0174[20]; //0x0174
	uint32_t m_water_proof; //0x0188
	float m_sneak_speed; //0x018C
	char pad_0190[53]; //0x0190
	bool m_rockstar_dev; //0x01C5
	char pad_01C6[1]; //0x01C6
	bool m_is_cheater; //0x01C7
	char pad_01C8[11]; //0x01C8
	bool m_is_online; //0x01D3
	char pad_01D4[20]; //0x01D4
	class CPed* m_ped; //0x01E8
	char pad_01F0[40]; //0x01F0
	uint32_t m_frame_flags; //0x0218
	char pad_021C[28]; //0x021C
	uint32_t m_player_controls; //0x0238
	char pad_023C[196]; //0x023C
	rage::vector3 m_last_aimed_coords; //0x0300
	char pad_030C[1072]; //0x030C
	float m_wanted_can_change; //0x073C
	char pad_0740[304]; //0x0740
	uint32_t m_npc_ignore; //0x0870
	char pad_0874[12]; //0x0874
	bool m_is_wanted; //0x0880
	char pad_0881[3]; //0x0881
	int8_t m_wanted_level_display; //0x0884
	char pad_0885[3]; //0x0885
	int8_t m_wanted_level; //0x0888
	char pad_0889[1127]; //0x0889
	float m_run_speed; //0x0CF0
	float m_stamina; //0x0CF4
	float m_max_stamina; //0x0CF8
	char pad_0CFC[16]; //0x0CFC
	float m_damage_gun_multiplier; //0x0D0C
	float m_damage_hp; //0x0D10
	float m_damage_armour; //0x0D14
	float m_damage_melee_multiplier; //0x0D18
	float m_super_punch; //0x0D1C
}; //Size: 0xD18
static_assert(sizeof(CPlayerInfo) == 0xD20); //0xD18

static_assert(sizeof(CNonPhysicalPlayerData) == 0x1C);
#pragma pack(pop)
