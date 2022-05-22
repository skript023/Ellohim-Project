#pragma once
#include "fwddec.hpp"

namespace rage
{
	// copied from the game
	template <typename T>
	struct atSingleton
	{
	private:
		T* m_basePtr{};

	public:
		bool is_valid() const
		{
			return m_basePtr != nullptr;
		}

		T* get_instance()
		{
			return m_basePtr;
		}
	};
}