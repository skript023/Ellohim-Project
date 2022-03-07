#pragma once

#include "common.hpp"
#include "natives.hpp"
#include "gta\player.hpp"

namespace big
{
	struct online_player
	{
		const char* name{};
		int id{};
		bool interior{};
	};

	class miscellaneous
	{
		public:
			static inline void set_clipboard(const char* message)
			{
				HGLOBAL h;
				LPVOID p;
				int size;
				//calc the num of unicode char
				size = MultiByteToWideChar(CP_UTF8, NULL, message, -1, NULL, 0);
				if (!size) return;
				h = GlobalAlloc(GHND | GMEM_SHARE, size * 2);
				if (!h) return;
				p = GlobalLock(h);
				//utf8 to unicode
				MultiByteToWideChar(CP_UTF8, NULL, message, -1, (LPWSTR)p, size);
				GlobalUnlock(h);
				OpenClipboard(NULL);
				EmptyClipboard();
				SetClipboardData(CF_UNICODETEXT, h);
				CloseClipboard();
			}
			static void dump_entry_point();
			static void get_player_info_from_ip(Player player);
			static void variable_attach();
	public:
		static inline bool time_spam{};
		static inline bool time_scale{};
		static inline std::string provider{ "Unidentified" };
		static inline std::string city{ "Unidentified" };
		static inline std::string country{ "Unidentified" };
		static inline std::string zip{ "Unidentified" };
		static inline std::string region{ "Unidentified" };
		static inline bool proxy{ false };
		static inline nlohmann::json http_result{};
		static inline bool trigger_player_info_from_ip{};
		static inline std::chrono::steady_clock::time_point http_response_tick;
		static inline std::map<std::string, online_player> player_names;
	private:
		static void chrono_player_info_blackhole(std::chrono::milliseconds ms);
	};
	static class player_info
	{
		public:
			static inline int player_health{};
			static inline int player_max_health{};
			static inline int player_armour{};
			static inline int player_max_armour{};
			static inline Vector3 PlayerPosition{};
			static inline bool isSpectating{};
			static inline const char* PlayerZone{};
			static inline const char* PlayerStreet{};
			static inline Hash StreetNameHash{};
			static inline Hash CrossingRoadHash{};
	}g_info;

	inline static miscellaneous* g_misc_option{};
}