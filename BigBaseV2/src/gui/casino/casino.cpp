#include "natives.hpp"
#include "common.hpp"
#include "gta_util.hpp"
#include "script_local.hpp"
#include "gta/VehicleValues.h"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include "features.hpp"
#include "gui/controller/ScriptController.h"
#include "casino.h"
#include "gui/controller/game_variable.h"
#include "gui/controller/memory_address.hpp"
#include "gui/controller/system_control.h"
#include "gui/game_event/game_event.h"
#include "gui/player/player_option.h"

namespace big
{
    void apartment::instant_prep()
    {
        const auto mpx = std::to_string(g_local.character);
        STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_HEIST_PLANNING_STAGE"), -1, TRUE);
    }

    void doomsday::instant_prep()
    {
        const auto mpx = std::to_string(g_local.character);
        STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_GANGOPS_FLOW_MISSION_PROG"), -1, TRUE);
    }

    void casino_heist::BigconHeist()
    {
        g_fiber_pool->queue_job([]
            {
                const auto mpx = std::to_string(g_local.character);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_APPROACH"), 2, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3_LAST_APPROACH"), 3, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3_HARD_APPROACH"), 2, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_TARGET"), 3, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_DISRUPTSHIP"), 3, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_KEYLEVELS"), 2, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_CREWWEAP"), 2, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_CREWDRIVER"), 2, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_CREWHACKER"), 4, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_VEHS"), 3, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_WEAPS"), 0, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_BITSET1"), 159, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_BITSET0"), 392982, TRUE);
            });
    }

    void casino_heist::SilentHeist()
    {
        g_fiber_pool->queue_job([]
            {
                const auto mpx = std::to_string(g_local.character);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_APPROACH"), 1, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3_LAST_APPROACH"), 2, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3_HARD_APPROACH"), 1, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_TARGET"), 3, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_DISRUPTSHIP"), 3, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_KEYLEVELS"), 2, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_CREWWEAP"), 5, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_CREWDRIVER"), 2, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_CREWHACKER"), 4, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_VEHS"), 3, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_WEAPS"), 1, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_BITSET1"), 127, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_BITSET0"), 62, TRUE);
            });
    }

    void casino_heist::AggressiveHeist()
    {
        g_fiber_pool->queue_job([]
            {
                const auto mpx = std::to_string(g_local.character);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_APPROACH"), 3, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3_LAST_APPROACH"), 2, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3_HARD_APPROACH"), 3, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_TARGET"), 3, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_DISRUPTSHIP"), 3, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_KEYLEVELS"), 2, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_CREWWEAP"), 5, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_CREWDRIVER"), 2, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_CREWHACKER"), 4, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_VEHS"), 3, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_WEAPS"), 1, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_BITSET1"), 799, TRUE);
                STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H3OPT_BITSET0"), 3670038, TRUE);
            });
    }

    void cayo_perico::CayoPericoHeist()
    {
        g_fiber_pool->queue_job([]
        {
            const auto mpx = std::to_string(g_local.character);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4LOOT_CASH_I"), 0, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4LOOT_CASH_I_SCOPED"), 0, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4LOOT_CASH_C"), 0, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4LOOT_CASH_C_SCOPED"), 0, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4LOOT_WEED_I"), 0, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4LOOT_WEED_I_SCOPED"), 0, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4LOOT_WEED_C"), 0, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4LOOT_WEED_C_SCOPED"), 0, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4LOOT_COKE_I"), 0, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4LOOT_COKE_I_SCOPED"), 0, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4LOOT_COKE_C"), 0, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4LOOT_COKE_C_SCOPED"), 0, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4LOOT_GOLD_I_SCOPED"), 16777215, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4LOOT_GOLD_I"), 16777215, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4LOOT_GOLD_C_SCOPED"), 255, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4LOOT_GOLD_C"), 255, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4LOOT_PAINT_SCOPED"), 255, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4LOOT_PAINT"), 255, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4CNF_BS_ENTR"), 63, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4CNF_BS_ABIL"), 63, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4CNF_WEP_DISRP"), 3, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4CNF_HEL_DISRP"), 3, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4CNF_ARM_DISRP"), 3, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4CNF_BOLTCUT"), 4641, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4CNF_GRAPPEL"), 33024, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4CNF_UNIFORM"), 16770, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4CNF_TROJAN"), 1, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4CNF_APPROACH"), -1, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4CNF_VOLTAGE"), 3, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4CNF_BS_GEN"), 131071, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4CNF_WEAPONS"), 2, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4CNF_TARGET"), 5, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4_PROGRESS"), 130415, TRUE);
            STATS::STAT_SET_INT(rage::joaat("MP" + mpx + "_H4_MISSIONS"), 65535, TRUE);
            if (auto heist_island_planning = rage_helper::find_script_thread(RAGE_JOAAT("heist_island_planning")))
            {
                *script_local(heist_island_planning, m_local.submarine_computer).as<int*>() = 2;
            }
        });
    }

    void cayo_perico::set_heat_to_zero(bool activation)
    {
        if (activation)
        {
            rage_helper::execute_as_script(RAGE_JOAAT("fm_mission_controller_2020"), [] {
                if (auto cayo = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")))
                {
                    *script_local(cayo, m_local.glass_cutter_heat).as<float*>() = 75.0f;
                }
            });
        }
    }

    bool casino_heist::ch_is_hard(Player player)
    {
        if (player::does_player_exist(player))
        {
            if (*script_global(1630816).at(player, 597).at(10).as<bool*>())
            {
                return *script_global(g_global.casino_stat).at(player, 68).at(24).as<int*>() == *script_global(g_global.casino_stat).at(player, 68).at(22).as<int*>();
            }
        }
        return false;
    }

    void casino_heist::all_heist_take(int Take)
    {
        if (auto casino = rage_helper::find_script_thread(RAGE_JOAAT("fm_mission_controller")))
        {
            *script_local(casino, m_local.take_casino).as<int*>() = Take;
        }
        if (systems::is_script_active(RAGE_JOAAT("fm_mission_controller_2020")))
        {
            remote_event::take_all_cayo(Take);
        }
    }

    void casino_heist::RemoveCasinoCrew(bool Activation)
    {
        if (Activation)
        {
            if (g_local.mission != nullptr && g_local.arcade == nullptr)
            {
                *script_global(g_global.casino_stat).at(PLAYER::PLAYER_ID(), 68).at(18).at(14).as<int*>() = 6;
                *script_global(g_global.casino_stat).at(PLAYER::PLAYER_ID(), 68).at(18).at(12).as<int*>() = 6;
                *script_global(g_global.casino_stat).at(PLAYER::PLAYER_ID(), 68).at(18).at(10).as<int*>() = 6;
            }
        }
    }

    void casino_heist::AutoHeistCut(bool Activate)
    {
        if (Activate)
        {
            if (g_local.transition && script_helper::is_script_active(RAGE_JOAAT("gb_casino_heist_planning")))
            {
                if (*script_global(g_global.casino_cut_1).as<int*>() >= 15 && *script_global(g_global.casino_cut_1).as<int*>() < 85)
                {
                    *script_global(g_global.casino_cut_1).as<int*>() = 85;
                }
                else if (*script_global(g_global.casino_cut_2).as<int*>() >= 15 && *script_global(g_global.casino_cut_2).as<int*>() < 85)
                {
                    *script_global(g_global.casino_cut_2).as<int*>() = 85;
                }
                else if (*script_global(g_global.casino_cut_3).as<int*>() >= 15 && *script_global(g_global.casino_cut_3).as<int*>() < 85)
                {
                    *script_global(g_global.casino_cut_3).as<int*>() = 85;
                }
                else if (*script_global(g_global.casino_cut_4).as<int*>() >= 15 && *script_global(g_global.casino_cut_4).as<int*>() < 85)
                {
                    *script_global(g_global.casino_cut_4).as<int*>() = 85;
                }
            }

            if (g_local.transition && script_helper::is_script_active(RAGE_JOAAT("gb_gang_ops_planning")))
            {
                if (*script_global(g_global.doomsday_cut_1).as<int*>() >= 15 && *script_global(g_global.doomsday_cut_1).as<int*>() < 85)
                {
                    *script_global(g_global.doomsday_cut_1).as<int*>() = 85;
                }
                else if (*script_global(g_global.doomsday_cut_2).as<int*>() >= 15 && *script_global(g_global.doomsday_cut_2).as<int*>() < 85)
                {
                    *script_global(g_global.doomsday_cut_2).as<int*>() = 85;
                }
                else if (*script_global(g_global.doomsday_cut_3).as<int*>() >= 15 && *script_global(g_global.doomsday_cut_3).as<int*>() < 85)
                {
                    *script_global(g_global.doomsday_cut_3).as<int*>() = 85;
                }
                else if (*script_global(g_global.doomsday_cut_4).as<int*>() >= 15 && *script_global(g_global.doomsday_cut_4).as<int*>() < 85)
                {
                    *script_global(g_global.doomsday_cut_4).as<int*>() = 85;
                }
            }

            if (g_local.transition && script_helper::is_script_active(RAGE_JOAAT("fmmc_launcher")))
            {
                if (*script_global(g_global.apartmen_cut_1).as<int*>() >= 15 && *script_global(g_global.apartmen_cut_1).as<int*>() < 85)
                {
                    *script_global(g_global.apartmen_cut_1).as<int*>() = 85;
                }
                else if (*script_global(g_global.apartmen_cut_2).as<int*>() >= 15 && *script_global(g_global.apartmen_cut_2).as<int*>() < 85)
                {
                    *script_global(g_global.apartmen_cut_2).as<int*>() = 85;
                }
                else if (*script_global(g_global.apartmen_cut_3).as<int*>() >= 15 && *script_global(g_global.apartmen_cut_3).as<int*>() < 85)
                {
                    *script_global(1666211).at(3008).at(3).as<int*>() = 85;
                }
                else if (*script_global(g_global.apartmen_cut_4).as<int*>() >= 15 && *script_global(g_global.apartmen_cut_4).as<int*>() < 85)
                {
                    *script_global(g_global.apartmen_cut_4).as<int*>() = 85;
                }
            }

            if (g_local.transition && script_helper::is_script_active(RAGE_JOAAT("heist_island_planning")))
            {
                if (*script_global(g_global.cayo_cut_1).as<int*>() >= 15 && *script_global(g_global.cayo_cut_1).as<int*>() < 85)
                {
                    *script_global(g_global.cayo_cut_1).as<int*>() = 85;
                }
                else if (*script_global(g_global.cayo_cut_2).as<int*>() >= 15 && *script_global(g_global.cayo_cut_2).as<int*>() < 85)
                {
                    *script_global(g_global.cayo_cut_2).as<int*>() = 85;
                }
                else if (*script_global(g_global.cayo_cut_3).as<int*>() >= 15 && *script_global(g_global.cayo_cut_3).as<int*>() < 85)
                {
                    *script_global(g_global.cayo_cut_3).as<int*>() = 85;
                }
                else if (*script_global(g_global.cayo_cut_4).as<int*>() >= 15 && *script_global(g_global.cayo_cut_4).as<int*>() < 85)
                {
                    *script_global(g_global.cayo_cut_4).as<int*>() = 85;
                }
            }
            *script_global(g_global.real_player_cut).as<int*>() = 85;
        }
    }

    void casino_heist::HeistCrewCutToZero(bool Activation)
    {
        if (Activation)
        {
            *script_global(g_global.ch_gunman.karl_cut).as<int*>() = 0;
            *script_global(g_global.ch_gunman.gustavo_cut).as<int*>() = 0;
            *script_global(g_global.ch_gunman.charlie_cut).as<int*>() = 0;
            *script_global(g_global.ch_gunman.chester_cut).as<int*>() = 0;
            *script_global(g_global.ch_gunman.packie_cut).as<int*>() = 0;
            *script_global(g_global.ch_hacker.rickie_cut).as<int*>() = 0;
            *script_global(g_global.ch_hacker.christian_cut).as<int*>() = 0;
            *script_global(g_global.ch_hacker.yohan_cut).as<int*>() = 0;
            *script_global(g_global.ch_hacker.avi_cut).as<int*>() = 0;
            *script_global(g_global.ch_hacker.paige_cut).as<int*>() = 0;
            *script_global(g_global.ch_driver.karim_cut).as<int*>() = 0;
            *script_global(g_global.ch_driver.taliana_cut).as<int*>() = 0;
            *script_global(g_global.ch_driver.eddie_cut).as<int*>() = 0;
            *script_global(g_global.ch_driver.zach_cut).as<int*>() = 0;
            *script_global(g_global.ch_driver.chester_cut).as<int*>() = 0;
            *script_global(g_global.real_player_cut).as<int*>() = 85;
        }
        else
        {
            *script_global(g_global.ch_gunman.karl_cut).as<int*>() = 5;
            *script_global(g_global.ch_gunman.gustavo_cut).as<int*>() = 9;
            *script_global(g_global.ch_gunman.charlie_cut).as<int*>() = 7;
            *script_global(g_global.ch_gunman.chester_cut).as<int*>() = 10;
            *script_global(g_global.ch_gunman.packie_cut).as<int*>() = 8;
            *script_global(g_global.ch_hacker.rickie_cut).as<int*>() = 3;
            *script_global(g_global.ch_hacker.christian_cut).as<int*>() = 7;
            *script_global(g_global.ch_hacker.yohan_cut).as<int*>() = 5;
            *script_global(g_global.ch_hacker.avi_cut).as<int*>() = 10;
            *script_global(g_global.ch_hacker.paige_cut).as<int*>() = 9;
            *script_global(g_global.ch_driver.karim_cut).as<int*>() = 5;
            *script_global(g_global.ch_driver.taliana_cut).as<int*>() = 7;
            *script_global(g_global.ch_driver.eddie_cut).as<int*>() = 9;
            *script_global(g_global.ch_driver.zach_cut).as<int*>() = 6;
            *script_global(g_global.ch_driver.chester_cut).as<int*>() = 10;
        }
    }

    void casino_slot::StopAnimation(bool Activation)
    {
        if (Activation)
        {
            if (auto slots_thread = rage_helper::find_script_thread(RAGE_JOAAT("CASINO_SLOTS")))
            {
                *script_local(slots_thread, m_local.slot.animation).as<int*>() = 4;
            }
        }
    }

    void casino_slot::AlwaysJackpot(bool Activation)
    {
        if (Activation)
        {
            if (auto slots_thread = rage_helper::find_script_thread(RAGE_JOAAT("CASINO_SLOTS")))
            {
                for (int i = 1; i <= 195; i++)
                {
                    auto local1356 = script_local(slots_thread, m_local.slot.jackpot_trigger).at(1);
                    int break_value = *local1356.at(i).as<int*>();
                    if (break_value != 64)
                    {
                        *local1356.at(i).as<int*>() = 6;
                    }
                }
            }
        }
    }

    void casino_slot::SetJackpot(int ID)
    {
        if (auto slots_thread = rage_helper::find_script_thread(RAGE_JOAAT("CASINO_SLOTS")))
        {
            for (int f = 0; f <= 2; f++)
            {
                for (int c = 0; c <= 63; c++)
                {
                    *script_local(slots_thread, m_local.slot.jackpot_trigger).at(1).at(f, 65).at(1).at(c).as<int*>() = ID;
                }
            }
        }
    }

    void casino_slot::SetJackpotMultiplier(int Reward)
    {
        g_fiber_pool->queue_job([Reward] {
            if (auto slots_thread = rage_helper::find_script_thread(RAGE_JOAAT("CASINO_SLOTS")))
            {
                for (int i = 1; i <= 10; i++)
                {
                    auto local1356 = script_local(slots_thread, m_local.slot.jackpot_trigger).at(278);
                    *local1356.at(i).as<int*>() = Reward; //if 1000 it will set to 1000x
                }
            }
            });
    }

    void casino_slot::AutoPlay(bool Activation)
    {
        if (Activation)
        {
            if (auto slots_thread = rage_helper::find_script_thread(RAGE_JOAAT("CASINO_SLOTS")))
            {
                auto local_1644 = script_local(slots_thread, m_local.slot.slot_autoplay).as<int*>();
                auto local_3407 = script_local(slots_thread, m_local.slot.entry_func).at(PLAYER::PLAYER_ID(), 11).at(10).as<int*>();
                if (*local_3407 == 0)
                {
                    *script_local(slots_thread, m_local.slot.slot_autoplay).as<int*>() = 8;
                }
                else if (*local_3407 == 3) {
                    *script_local(slots_thread, m_local.slot.entry_func).at(PLAYER::PLAYER_ID(), 11).at(10).as<int*>() = 6;
                }
            }
        }
    }

    void casino_slot::RigSlotMachine(bool Activation)
    {
        if (Activation)
        {
            if (auto slots_thread = rage_helper::find_script_thread(RAGE_JOAAT("CASINO_SLOTS")))
            {
                auto local_219 = script_local(slots_thread, m_local.slot.struct_21);
                auto local_2131 = script_local(slots_thread, m_local.slot.unk_1).as<int*>();

                *local_219.at(*local_2131, 21).at(16).as<int*>() = 500;
                *script_local(slots_thread, m_local.slot.unk_2).as<int*>() = 5;
            }
        }
    }

    bool blackjack::is_context_active(char* text)
    {
        HUD::BEGIN_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(text);
        return HUD::END_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(0);
    }

    void blackjack::AutoPlay(bool Activation)
    {
        if (Activation)
        {
            if (auto blackjack_thread = rage_helper::find_script_thread(RAGE_JOAAT("BLACKJACK")))
            {
                auto current_table = script_local(blackjack_thread, m_local.blackjack.current_table).as<int*>();
                auto all_buttons_ready = script_local(blackjack_thread, m_local.blackjack.button_ready).as<int*>();

                if (is_context_active("BJACK_BET") && *all_buttons_ready == 5)
                {
                    *script_local(blackjack_thread, m_local.blackjack.bet_trigger).as<int*>() = 36864;
                    *script_global(262145).at(26688).as<int*>() = INT_MAX;
                }
            }
        }
        else if (!Activation && !systems::is_script_active(RAGE_JOAAT("BLACKJACK")))
        {
            *script_global(262145).at(26688).as<int*>() = 5000000;
        }
    }

    void blackjack::BlackJack(bool Activation)
    {
        if (Activation)
        {
            if (auto blackjack_thread = rage_helper::find_script_thread(RAGE_JOAAT("BLACKJACK")))
            {
                auto current_table = script_local(blackjack_thread, m_local.blackjack.current_table).as<int*>();
                auto cur_card = script_local(blackjack_thread, m_local.blackjack.current_card).at(*current_table, 211);

                if (*current_table != -1)
                {
                    *cur_card.at(1).as<int*>() = 1;
                    *script_local(blackjack_thread, m_local.blackjack.unk_1).at(3).as<int*>() = 1;
                    *cur_card.at(2).as<int*>() = 0;
                    *script_local(blackjack_thread, m_local.blackjack.unk_1).at(4).as<int*>() = 0;
                    *cur_card.at(3).as<int*>() = 23;
                    *script_local(blackjack_thread, m_local.blackjack.unk_1).at(5).as<int*>() = 23;
                    *cur_card.at(4).as<int*>() = 0;
                    *script_local(blackjack_thread, m_local.blackjack.unk_1).at(6).as<int*>() = 0;
                    *script_local(blackjack_thread, m_local.blackjack.unk_1).at(244).as<int*>() = 0;
                    *script_local(blackjack_thread, m_local.blackjack.unk_1).at(246).as<int*>() = 0;
                    *script_local(blackjack_thread, m_local.blackjack.unk_2).at(14).as<int*>() = 2500000;
                    *script_local(blackjack_thread, m_local.blackjack.unk_3).at(1580).at(1).as<int*>() = 0;
                }
            }
        }
    }

}