#pragma once
#include "common.hpp"
#include "gta/array.hpp"
#include "gta/ped_factory.hpp"
#include "gta/player.hpp"
#include "gta/script_thread.hpp"
#include "gta/tls_context.hpp"
#include "pointers.hpp"
#include "script_global.hpp"
#include "gui/controller/memory_address.hpp"

namespace big::rage_helper
{
	inline CPed *get_local_ped()
	{
		if (auto ped_factory = *g_pointers->m_ped_factory)
		{
			return ped_factory->m_local_ped;
		}
		return nullptr;
	}

	inline CPlayerInfo *get_local_playerinfo()
	{
		if (auto ped_factory = *g_pointers->m_ped_factory)
		{
			if (auto ped = ped_factory->m_local_ped)
			{
				return ped->m_playerinfo;
			}
		}
		return nullptr;
	}

	inline CVehicle* get_local_vehicle()
	{
		if (auto ped_factory = *g_pointers->m_ped_factory)
		{
			if (auto ped = ped_factory->m_local_ped)
			{
				return ped->m_last_vehicle;
			}
		}
		return nullptr;
	}

	inline CNetGamePlayer* get_local_net_player(Player player)
	{
		if (auto player_mgr = *g_pointers->m_network_player_mgr)
		{
			if (auto net_player = player_mgr->m_get_player[player])
			{
				return net_player;
			}
		}
		return nullptr;
	}

	inline CNetGamePlayer* get_net_player(Player player)
	{
		return g_pointers->m_get_net_game_player(player);
	}

	inline FriendList* get_friend()
	{
		if (auto friend_list = *g_pointers->m_friend_list)
		{
			return friend_list;
		}
		return nullptr;
	}

	inline int get_character()
	{
		return *script_global(g_global.character).as<int*>();
	}

	template <typename pointer>
	inline pointer entity_to_pointer(Entity entity)
	{
		return reinterpret_cast<pointer>(g_pointers->m_handle_to_ptr(entity));
	}

	inline Entity pointer_to_entity(PVOID pointer)
	{
		return g_pointers->m_ptr_to_handle(pointer);
	}

	inline CPed* get_player_pointer(Player player)
	{
		if (auto local_ped = g_pointers->m_player_ptr(player))
		{
			return local_ped;
		}
		return nullptr;
	}

	inline CPlayerInfo* get_player_info(Player player)
	{
		if (auto local_ped = get_player_pointer(player))
		{
			return local_ped->m_playerinfo;
		}
		return nullptr;
	}

	template<typename setting>
	inline void apply_game_setting(DWORD setting_index, setting setting_flag)
	{
		*(setting*)((DWORD64)g_pointers->m_game_setting + setting_index) = setting_flag;
	}

	template<typename setting>
	inline setting get_game_setting(DWORD setting_index)
	{
		return *(setting*)((DWORD64)g_pointers->m_game_setting + setting_index);
	}

	inline bool get_game_state()
	{
		return *g_pointers->m_game_state == eGameState::Playing;
	}

	inline GtaThread* find_script_thread(rage::joaat_t hash)
	{
		for (auto thread : *g_pointers->m_script_threads)
		{
			if (thread
				&& thread->m_context.m_thread_id
				&& thread->m_handler
				&& thread->m_script_hash == hash)
			{
				return thread;
			}
		}
		return nullptr;
	}

	template <typename F, typename ...Args>
	void execute_as_script(rage::joaat_t script_hash, F &&callback, Args &&...args)
	{
		auto tls_ctx = rage::tlsContext::get();
		for (auto thread : *g_pointers->m_script_threads)
		{
			if (!thread || !thread->m_context.m_thread_id || thread->m_context.m_script_hash != script_hash)
				continue;

			auto og_thread = tls_ctx->m_script_thread;

			tls_ctx->m_script_thread = thread;
			tls_ctx->m_is_script_thread_active = true;

			std::invoke(std::forward<F>(callback), std::forward<Args>(args)...);

			tls_ctx->m_script_thread = og_thread;
			tls_ctx->m_is_script_thread_active = og_thread != nullptr;

			return;
		}
	}
}

namespace big
{
	class memory_util
	{
	public:
		static inline uintptr_t get_multilayer_pointer(uintptr_t base_address, std::vector<DWORD> offsets)
		{
			uintptr_t ptr = *(uintptr_t*)(base_address);
			if (!ptr) 
			{

				return NULL;
			}
			auto level = offsets.size();

			for (auto i = 0; i < level; i++)
			{
				if (i == level - 1)
				{
					ptr += offsets[i];
					if (!ptr) return NULL;
					return ptr;
				}
				else
				{
					ptr = *(uint64_t*)(ptr + offsets[i]);
					if (!ptr) return NULL;
				}
			}

			return ptr;
		}

		template <typename T>
		static inline T get_value(uintptr_t BaseAddress, std::vector<DWORD> offsets)
		{

			uintptr_t Addr = get_multilayer_pointer(BaseAddress, offsets);
			if (Addr == NULL) {
				return NULL;
			}

			return *((T*)Addr);
		}

		template <typename T>
		static inline void set_value(uintptr_t BaseAddress, std::vector<DWORD> offsets, T value)
		{
			uintptr_t Addr = get_multilayer_pointer(BaseAddress, offsets);
			if (Addr == NULL) {
				return;
			}

			*reinterpret_cast<T*>(Addr) = value;
		}

		static inline bool is_bit_set(int _value, int _bit)
		{
			if ((_value >> _bit) & 1LL) return true;
			return false;
		}

		static inline int set_bit(int& _value, int _bit)
		{
			return _value |= 1LL << _bit;
		}

		static inline int clear_bit(int& _value, int _bit)
		{
			return _value &= ~(1LL << _bit);
		}

		template <typename T>
		static inline bool is_bit_set(T* addr, int _bit)
		{
			if ((*addr >> _bit) & 1LL) return true;
			return false;
		}

		template <typename T>
		static inline void set_bit(T* addr, int _bit)
		{
			*addr |= 1LL << _bit;
		}

		template <typename T>
		static inline void clear_bit(T* addr, int _bit)
		{
			*addr &= ~(1LL << _bit);
		}

		template <typename T>
		static inline void toggle_bit(T* addr, int _bit)
		{
			*addr ^= (1i64 << _bit);
		}

		template <typename T>
		static inline bool has_flag(T* addr, int flag)
		{
			if ((*addr & flag) == flag) return true;
			return false;
		}

		template <typename T>
		static inline int set_flag(T* addr, int flag)
		{
			return *addr = flag;
		}

		template <typename T>
		static inline int clear_flag(T* addr, int flag)
		{
			return *addr &= ~(flag);
		}
	};
}
//https://www.xnxx.com/video-12ierjc4/my_classmate_fucks_moms_eng_sub_more_movies_at_myjavengsubtitle.blogspot.com_