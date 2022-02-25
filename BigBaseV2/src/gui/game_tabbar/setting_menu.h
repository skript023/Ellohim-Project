#pragma once

#include "common.hpp"
#include "natives.hpp"

namespace big
{
	class setting_tab
	{
	public:
		static void render_setting_tab(const char* tab_name);
        static inline std::uint8_t* m_font{};
    private:
        static inline int selected_fonts{};
        static inline const char* const aim_list[]{ "Assisted Aim - Full", "Assisted Aim - Partial", "Free Aim - Assisted", "Free Aim" };
        static inline const char* const fonts_list[]{ "Default", "Fira Code", "Nanum Ghotic Bold", "Roboto Condensed" };
	};
}


/*
            if (ImGui::Button("Give Ammo"))
            {
                for (int i = 0; i <= rage_helper::get_local_ped()->m_weapon_inventory->m_total_player_weapon; ++i)
                {
                    rage_helper::get_local_ped()->m_weapon_inventory->m_weapon_list->m_weapon_ammo[i]->m_ammo = 9999;
                }
            }
            //ImGui::Checkbox("Test", &g_fitur.testing);

            if (ImGui::Button("Test"))
            {
                if (player::is_player_in_any_vehicle(g_local.player))
                {//0.03999999911f
                    for (int i = 0; i <= 64; i++)//-100000000.f
                    {
                        if (rage_helper::get_local_vehicle()->m_navigation->m_ph_arche->get_geometry(i) == nullptr || rage_helper::get_local_vehicle()->m_navigation->m_ph_arche->get_geometry(i) > reinterpret_cast<VehicleCollision*>(0x7FFFFFFFFFF) || rage_helper::get_local_vehicle()->m_navigation->m_ph_arche->get_geometry(i) < rage_helper::get_local_vehicle()->m_navigation->m_ph_arche->get_geometry(1))
                            continue;
                        if (systems::is_float_equal(rage_helper::get_local_vehicle()->m_navigation->m_ph_arche->get_geometry(i)->m_collision, 0.03999999911f))
                            rage_helper::get_local_vehicle()->m_navigation->m_ph_arche->get_geometry(i)->m_collision = -100000000.f;
                    }
                }
            }
            */