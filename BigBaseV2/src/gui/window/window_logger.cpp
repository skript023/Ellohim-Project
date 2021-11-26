#include <imgui.h>
#include <renderer.hpp>
#include <logger.hpp>
#include "window_logger.hpp"
#include "game_window.hpp"

namespace big
{
    void window_log::logger(const char* window_name)
    {
        ImGui::SetNextWindowSize({ 500, 250 }, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos({ 50, 50 }, ImGuiCond_FirstUseEver);
        if (g_game_window->logger && ImGui::Begin(window_name))
        {
            ImGui::PushFont(g_renderer->m_monospace_font);

            std::lock_guard lock(g_logger->m_mutex);
            auto msgs = g_logger->get_messages();

            for (size_t i = 0; i < msgs.second; i++)
            {
                ImGui::TextUnformatted(msgs.first[i].get());
            }

            if (iLastLogCount != msgs.second)
            {
                iLastLogCount = msgs.second;
                ImGui::SetScrollHereY(1.f);
            }

            ImGui::PopFont();

            ImGui::End();
        }
    }
}