#pragma once
#include "fwddec.hpp"

#pragma pack(push, 1)

class CHashTable
{
public:
	char pad_0000[0x2EB8]; //0x0000
	CPedHashTable *m_ped_hash_table; //0x2EB8
};
static_assert(sizeof(CHashTable) == 0x2EC0);

class CPedHashTable
{
public:
	char pad_0000[0x8E0]; //0x0000
	uint32_t m_slod; //0x08E0
	char pad_08E4[0xC]; //0x08E4
	uint32_t m_slod_small; //0x08F0
	char pad_08F4[0xC]; //0x08F4
	uint32_t m_slod_large; //0x0900
};
static_assert(sizeof(CPedHashTable) == 0x904);

class CPlayerCrew
{
public:
	char pad_0000[8]; //0x0000
	uint64_t m_rockstar_id; //0x0008
	char pad_0010[24]; //0x0010
	uint32_t m_crew_id; //0x0028
	char pad_002C[43]; //0x002C
	char m_crew_tag[4]; //0x0057
	char pad_005B[117]; //0x005B
	bool m_active_crew; //0x00D0
	char* get_crew_tag(int& index) { return (m_crew_tag + (0xB8LL * index)); }
	bool get_active_crew(int& index) { return *(bool*)((DWORD64)this + 0xD0LL + (0xB8LL * index)); }
};
static_assert(sizeof(CPlayerCrew) == 0xD1);

class BusinessMoney
{
public:
	char pad_0000[0x128];
	int32_t money_in_bunker;//0x0128
};
static_assert(sizeof(BusinessMoney) == 0x12C);

class FriendInfo
{
public:
	char pad_0000[128]; //0x0000
	char m_name[20]; //0x0080
	char pad_0094[36]; //0x0094
	uint64_t m_friend_id; //0x00B8
	char pad_00C0[4]; //0x00C0
	int32_t m_friend_status; //0x00C4
	char pad_00C8[304]; //0x00C8
	bool m_is_multiplayer; //0x01F8
	char pad_01F9[7]; //0x01F9
}; //Size: 0x0200
static_assert(sizeof(FriendInfo) == 0x200);

class FriendList
{
public:
	FriendInfo m_friend_info[128];
	const char* get_friend_name(int index) { return m_friend_info[index].m_name; }
	const char* get_friend_status(int index) 
	{
		bool is_multiplayer = m_friend_info[index].m_is_multiplayer;
		int status = m_friend_info[index].m_friend_status;
		bool is_single_player = status >> 1 & 1;
		bool is_online = status & 1;
		return is_multiplayer ? "Multiplayer" : is_single_player ? "Single Player" : is_online ? "Online" : "Offline";
	}

	uint64_t get_friend_id(int index) { return m_friend_info[index].m_friend_id; }
	uint64_t* set_friend_id(int index) { return &m_friend_info[index].m_friend_id; }
};

class GameSetting
{
public:
	char pad_0000[48]; //0x000
	bool m_keyboard_light_effect; //0x030
	char pad_0031[3]; //0x031
	int32_t m_sfx_volume; //0x034
	char pad_0038[8]; //0x038
	int32_t m_output_setting; //0x040
	char pad_0044[4]; //0x044
	int32_t m_radio_station; //0x048
	char pad_004C[52]; //0x04C
	bool m_kill_effect; //0x080
	char pad_0081[3]; //0x081
	bool m_subtitle; //0x084
	char pad_0085[3]; //0x085
	int32_t m_radar_setting; //0x088
	bool m_hud_setting; //0x08C
	char pad_008D[3]; //0x08D
	bool m_crosshair_setting; //0x090
	char pad_0091[3]; //0x091
	int32_t m_reticular_setting; //0x094
	bool m_gps_setting; //0x098
	char pad_0099[3]; //0x099
	int32_t m_safe_zone; //0x09C
	char pad_00A0[460]; //0x0A0
	bool m_radar_expansion; //0x026C
	char pad_026D[3]; //0x026D
	bool m_over_head_display; //0x0270
};
static_assert(sizeof(GameSetting) == 0x271, "GameSetting is not properly sized");

class CPed : public fwEntity
{
public:
	char pad_02A4[4]; //0x02A4
	void* m_attackers; //0x02A8
	char pad_02B0[112]; //0x02B0
	rage::vector3 m_velocity; //0x0320
	char pad_032C[2564]; //0x032C
	CVehicle* m_last_vehicle; //0x0D30
	char pad_0D38[282]; //0x0D38
	bool m_is_in_vehicle; //0x0E52
	char pad_0E53[613]; //0x0E53
	uint8_t m_ragdoll; //0x10B8
	char pad_10B9[3]; //0x10B9
	int8_t m_decal_index; //0x10BC
	int8_t m_decal_info; //0x10BD
	char pad_10BE[2]; //0x10BE
	UnknownPlayer* m_unk_player; //0x10C0
	CPlayerInfo* m_playerinfo; //0x10C8
	CPedInventory* m_weapon_inventory; //0x10D0
	CPedWeaponManager* m_weapon_mgr; //0x10D8
	char pad_10E0[892]; //0x10E0
	uint8_t seatbelt; //0x145C
	char pad_145D[16]; //0x145D
	int m_ped_task; //ox146D
	char pad_1471[191]; //0x1471
	float m_armor; //0x1530
};	//Size: 0x14E4
static_assert(sizeof(CPed) == 0x1534, "CPed is not properly sized");
#pragma pack(pop)

class CPedFactory
{
public:
	virtual ~CPedFactory() = default;
	CPed *m_local_ped;
};

class PresenceData
{
public:
	virtual ~PresenceData() = default; // 0 (0x00)
	virtual bool updateIntegerAttribute(uint32_t alwaysZero, const char* attributeName, int64_t attr) = 0; // 1 (0x08)
	virtual bool _0x10(unsigned int a2, int64_t a3) = 0; // 2 (0x10)
	virtual bool updateStringAttribute(uint32_t alwaysZero, const char* attributeName, const char* str) = 0; // 3 (0x18)
	virtual bool _0x20(unsigned int a2, int64_t a3, uint64_t* a4) = 0; // 4 (0x20)
	virtual bool _0x28(unsigned int a2, int64_t a3, uint64_t* a4) = 0; // 5 (0x28)
	virtual bool _0x30(unsigned int a2, int64_t a3, uint8_t* a4, unsigned int a5) = 0; // 6 (0x30)
	virtual bool _0x38() = 0; // 7 (0x38)
	virtual bool _0x40() = 0; // 8 (0x40)
	virtual bool _0x48() = 0; // 9 (0x48)
	virtual bool _0x50() = 0; // 10 (0x50)
	virtual bool _0x58() = 0; // 11 (0x58)
	virtual bool _0x60(unsigned __int8 a2) = 0; // 12 (0x60)
	virtual bool _0x68(uint8_t* a2) = 0; // 13 (0x68)
	virtual bool _0x70(unsigned __int8 a2) = 0; // 14 (0x70)
	virtual bool _0x78(uint8_t* a2) = 0; // 15 (0x78)
	virtual bool _0x80(unsigned int a2, int64_t a3, unsigned int a4) = 0; // 16 (0x80)
	virtual bool _0x88(unsigned int a2, int64_t a3, unsigned int a4) = 0; // 17 (0x88)
	virtual bool _0x90(int a2) = 0; // 18 (0x90)
	virtual bool _0x98() = 0; // 19 (0x98)
	virtual bool _0xa0(uint8_t* a2) = 0; // 20 (0xa0)
	virtual bool _0xa8(unsigned __int8 a2) = 0; // 21 (0xa8)
	virtual bool _0xb0(int64_t a2, int64_t a3) = 0; // 22 (0xb0)
	virtual bool _0xb8() = 0; // 23 (0xb8)
	virtual bool _0xc0(int64_t a2) = 0; // 24 (0xc0)
	virtual bool _0xc8() = 0; // 25 (0xc8)
};