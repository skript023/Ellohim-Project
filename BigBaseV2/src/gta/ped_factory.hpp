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

class FriendList
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
	const char* get_friend_name(const int& index) { return (m_name + (0x200LL * index)); }
	uint64_t get_friend_id(const int& index) { return  *(uint64_t*)((DWORD64)this + 0xB8 + (0x200LL * index)); }
	void set_rockstar_id(const int& index, uint64_t user_id) { *(uint64_t*)((DWORD64)this + 0xB8 + (0x200LL * index)) = user_id; }
	int get_friend_status(const int& index) { return *(int*)((DWORD64)this + 0xC4 + (0x200LL * index)); }
	bool get_friend_multiplayer(const int& index) { return *(bool*)((DWORD64)this + 0x1F8 + (0x200LL * index)); }
	const char* get_player_status(const int& index)
	{
		int status = get_friend_status(index);
		bool is_multiplayer = get_friend_multiplayer(index);
		bool is_single_player = status >> 1 & 1;
		bool is_online = status & 1;
		return is_multiplayer ? "Multiplayer" : is_single_player ? "Single Player" : is_online ? "Online" : "Offline";
	}
}; //Size: 0x01F9
static_assert(sizeof(FriendList) == 0x1F9);

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
	char pad_02A4[2700]; //0x02A4
	CVehicle* m_last_vehicle; //0x0D30
	char pad_0D38[282]; //0x0D38
	bool m_is_in_vehicle; //0x0E52
	char pad_0E53[613]; //0x0E53
	uint8_t m_ragdoll; //0x10B8
	char pad_10B9[3]; //0x10B9
	int8_t m_decal_index; //0x10BC
	int8_t m_decal_info; //0x10BD
	char pad_10BE[10]; //0x10BE
	CPlayerInfo* m_playerinfo; //0x10C8
	CPedInventory* m_weapon_inventory; //0x10D0
	CPedWeaponManager* m_weapon_mgr; //0x10D8
	char pad_10E0[812]; //0x10E0
	uint8_t seatbelt; //0x140C
	char pad_140D[211]; //0x140D
	float m_armor; //0x14E0
};	//Size: 0x14E4
static_assert(sizeof(CPed) == 0x14E4, "CPed is not properly sized");
#pragma pack(pop)

class CPedFactory
{
public:
	virtual ~CPedFactory() = default;
	CPed *m_local_ped;
};
