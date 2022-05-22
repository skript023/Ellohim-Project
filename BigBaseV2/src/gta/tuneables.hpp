#pragma once
#include "fwddec.hpp"

namespace rage
{
	class CTunables
	{
	public:
		char pad_0000[112]; //0x0000
		uint64_t m_base_pointer; //0x0070
		uint16_t m_count; //0x0078
	}; //Size: 0x007A
}