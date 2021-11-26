#pragma once

namespace big
{
	class window_log
	{
	public:
		static void logger(const char* window_name);
	public:
		static inline size_t iLastLogCount{ 0 };
	};

	inline window_log g_window_log;
}