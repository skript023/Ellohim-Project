#pragma once
#include "gta/fwddec.hpp"

namespace rage::netConnection
{
	class InFrame
	{
	public:
		virtual ~InFrame() = default;

		virtual void destroy() = 0;
		virtual uint32_t get_type() = 0;
		virtual uint32_t _0x18() = 0;

		char pad_0008[56]; //0x0008
		uint32_t m_msg_id; //0x0040
		char pad_0044[4]; //0x0044
		InFrame* m_this; //0x0048
		char pad_0050[40]; //0x0050
		uint32_t m_length; //0x0078
		char pad_007C[4]; //0x007C
		void* m_data; //0x0080
	};
}