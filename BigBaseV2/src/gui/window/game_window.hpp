#pragma once
#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class game_window
	{
	public:
		static bool create_session(Hash status);
		static const char* get_login_status_from_hash(Hash hash);
		static void get_status();
		static void interact_to_server(std::chrono::high_resolution_clock::duration time);
		static void logout();
		static bool get_authentication(const char* username, const char* password);
		static void render_base_window(const char* window_name);
		static Hash check_hash(uint64_t user_id);
	public:
		static inline bool logger{};
		static inline Hash login_status{ 0 };
	private:
		static inline std::string get_result{};
		static inline char temp_username[128];
		static inline char temp_password[128];
		static inline char username[128];
		static inline char password[128];
		static inline HW_PROFILE_INFO *profile_info;
		static inline std::string username_hash{};
		static inline std::string password_hash{};
		static inline bool is_auth{ true };
		static inline std::chrono::steady_clock::time_point get_session_time;
		static inline bool is_session_returned{ false };
		static inline Hash status_check{ 0 };
	};

	inline static game_window* g_game_window{};
}