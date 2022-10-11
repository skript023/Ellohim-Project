#pragma once


#pragma pack(push, 1)
class CPlayerGamerDataNode
{
public:
	char pad_0000[192];// 0x0000
	int64_t m_clan_member_id;// 0x00C0
	int64_t m_clan_id;// 0x00C8
	int32_t m_clan_color;// 0x00D0
	int32_t m_clan_member_count;// 0x00D4
	int32_t m_clan_created_time;// 0x00D8
	bool m_is_system_clan;// 0x00DC
	bool m_is_clan_open;// 0x00DD
	char m_clan_name[25];// 0x00DE
	char m_clan_tag[5];// 0x00F7
	char m_clan_motto[65];// 0x00FC
	char pad_013D[3];// 0x013D
	int64_t m_clan_id_2;// 0x0140
	char m_clan_rank_name[25];// 0x0148
	char pad_0161[3];// 0x0161
	int32_t m_clan_rank_order;// 0x0164
	int64_t m_clan_rank_flags;// 0x0168
	char pad_0170[8];// 0x0170
	bool m_need_crew_rank_sysflags;// 0x0178
	bool m_need_crew_rank_title;// 0x0179
	char m_crew_rank_title[25];// 0x017A
	bool m_has_started_transition;// 0x0193
	bool m_has_transition_info;// 0x0194
	char m_transition_info_buffer[125];// 0x0195
	bool m_is_rockstar_dev;// 0x0212
	bool m_is_rockstar_qa;// 0x0213
	bool m_is_cheater;// 0x0214
	char pad_0215[3];// 0x0215
	uint32_t m_matchmaking_group;// 0x0218
	bool m_need_mute_data;// 0x021C
	char pad_021D[3];// 0x021D
	int32_t m_mute_count;// 0x0220
	int32_t m_mute_talkers_count;// 0x0224
	uint32_t unk_0x228;// 0x0228
	bool m_has_communication_privilege;// 0x022C
	char pad_022D[3];// 0x022D
	int32_t unk_0x230;// 0x0230
	char pad_0234[620];// 0x0234
};
static_assert(sizeof(CPlayerGamerDataNode) == 0x4A0);

#pragma pack(pop)