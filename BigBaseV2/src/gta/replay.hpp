#pragma once
#pragma pack(push, 4)

#include "common.hpp"
#include "fwddec.hpp"

namespace rage
{
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
		char pad_003A[150]; //0x003A
		class netObject* m_net_object; //0x00D0
		char pad_00D8[176]; //0x00D8
		uint32_t m_damage_bits; //0x0188

		bool is_invincible() { return(m_damage_bits & (1 << 8)); }
		void enable_invincible() { m_damage_bits |= (1 << 8); }
		void disable_invincible() { m_damage_bits &= ~(1 << 8); }
	}; //Size: 0x018C
	static_assert(sizeof(fwEntity) == 0x18C, "fwEntity is not properly sized");


	class CVehicle : public fwEntity
	{
	public:
		char pad_018C[2716]; //0x018C
	}; //Size: 0x018C

	class CNavigation
	{
	public:
		char pad_0000[32]; //0x0000
		float m_heading; //0x0020
		float m_heading2; //0x0024
		char pad_0028[8]; //0x0028
		vector3 m_rotation; //0x0030
		char pad_003C[20]; //0x003C
		vector3 m_position; //0x0050
	}; //Size: 0x005C

	class CPed : public fwEntity
	{
	public:
		uint32_t m_hostility; //0x018C
		char pad_0190[240]; //0x0190
		float m_health; //0x0280
		char pad_0284[28]; //0x0284
		float m_max_health; //0x02A0
		char pad_02A4[2700]; //0x02A4
		class CVehicle* m_last_vehicle; //0x0D30
		char pad_0D38[896]; //0x0D38
		uint8_t m_ragdoll; //0x10B8
		char pad_10B9[3]; //0x10B9
		int8_t m_decal_index; //0x10BC
		int8_t m_decal_info; //0x10BD
		char pad_10BE[10]; //0x10BE
		class CPlayerInfo* m_player_info; //0x10C8
		class CPedInventory* m_weapon_inventory; //0x10D0
		class CPedWeaponManager* m_weapon_mgr; //0x10D8
		char pad_10E0[812]; //0x10E0
		uint8_t seatbelt; //0x140C
		char pad_140D[211]; //0x140D
		float m_armor; //0x14E0
	};
	static_assert(sizeof(CPed) == 0x14E4, "CPed is not properly sized");

	class CPlayerInfo
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
		char pad_007A[22]; //0x007A
		uint64_t m_rockstar_id; //0x0090
		char pad_0098[12]; //0x0098
		char m_name[20]; //0x00A4
		char pad_00B8[184]; //0x00B8
		float m_swim_speed; //0x0170
		char pad_0174[24]; //0x0174
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
		float m_last_aimed_x; //0x0300
		float m_last_aimed_y; //0x0300
		float m_last_aimed_z; //0x0300
		char pad_030C[1396]; //0x030C
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
	}; //Size: 0x081C

	class CObject : public fwEntity
	{
	public:
	}; //Size: 0x018C

	class CBaseModelInfo
	{
	public:
		char pad_0000[24]; //0x0000
		uint32_t m_model; //0x0018
	}; //Size: 0x001C

	class CPedFactory
	{
	public:
		virtual ~CPedFactory() = default;
		class CPed* m_local_ped; //0x0008
	}; //Size: 0x0010

	class CObjectHandle
	{
	public:
		class CObject* m_object; //0x0000
		int32_t m_handle; //0x0008
		char pad_000C[4]; //0x000C
	}; //Size: 0x0010
	static_assert(sizeof(CObjectHandle) == 0x10, "CObjectHandle is not properly sized");

	class CObjectList
	{
	public:
		class CObjectHandle m_objects[2300]; //0x0000
	}; //Size: 0x8FC0

	class CObjectInterface
	{
	public:
		char pad_0000[344]; //0x0000
		class CObjectList* m_object_list; //0x0158
		int32_t m_max_objects; //0x0160
		char pad_0164[4]; //0x0164
		int32_t m_cur_objects; //0x0168

		rage::CObject* get_object(const int& index)
		{
			if (index < m_max_objects)
				return m_object_list->m_objects[index].m_object;
			return nullptr;
		}
	}; //Size: 0x016C

	class CPedHandle
	{
	public:
		class CPed* m_ped; //0x0000
		int32_t m_handle; //0x0008
		char pad_000C[4]; //0x000C
	}; //Size: 0x0010
	static_assert(sizeof(CPedHandle) == 0x10, "CPedHandle is not properly sized");

	class CPedList
	{
	public:
		class CPedHandle m_peds[256]; //0x0000
	}; //Size: 0x1000

	class CPedInterface
	{
	public:
		char pad_0000[256]; //0x0000
		class CPedList* m_ped_list; //0x0100
		int32_t m_max_peds; //0x0108
		char pad_010C[4]; //0x010C
		int32_t m_cur_peds; //0x0110

		CPed* get_ped(const int& index)
		{
			if (index < m_max_peds)
				return m_ped_list->m_peds[index].m_ped;
			return nullptr;
		}
	}; //Size: 0x0114

	class CVehicleHandle
	{
	public:
		class CVehicle* m_vehicle; //0x0000
		int32_t m_handle; //0x0008
		char pad_000C[4]; //0x000C
	}; //Size: 0x0010
	static_assert(sizeof(CVehicleHandle) == 0x10, "CVehicleHandle is not properly sized");

	class CVehicleList
	{
	public:
		class CVehicleHandle m_vehicles[300]; //0x0000
	}; //Size: 0x12C0

	class CVehicleInterface
	{
	public:
		char pad_0000[384]; //0x0000
		class CVehicleList* m_vehicle_list; //0x0180
		int32_t m_max_vehicles; //0x0188
		char pad_018C[4]; //0x018C
		int32_t m_cur_vehicles; //0x0190

		CVehicle* get_vehicle(const int& index)
		{
			if (index < m_max_vehicles)
				return m_vehicle_list->m_vehicles[index].m_vehicle;
			return nullptr;
		}
	}; //Size: 0x0194


	class CReplayInterface
	{
	public:
		char pad_0000[16]; //0x0000
		class CVehicleInterface* m_vehicle_interface; //0x0010
		class CPedInterface* m_ped_interface; //0x0018
		char pad_0020[8]; //0x0020
		class CObjectInterface* m_object_interface; //0x0028
	}; //Size: 0x0030
}
#pragma pack(pop)