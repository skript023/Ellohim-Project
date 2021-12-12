#pragma once
#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class game_window
	{
	public:
		static void session_time_out(const char* url);
		static void get_authentication(const char* username, const char* password);
		static void render_base_window(const char* window_name);

	public:
		static inline bool logger{};
	private:
		static inline char temp_username[255];
		static inline char temp_password[255];
		static inline char username[255];
		static inline char password[255];
		static inline HW_PROFILE_INFO *profile_info;
		static inline std::string username_hash{};
		static inline std::string password_hash{};
		static inline std::string login_status{};
		static inline bool is_auth{ false };
		static inline int get_session_time{ 0 };
		static inline bool is_session_returned{ false };
	};

	inline static game_window* g_game_window{};
}