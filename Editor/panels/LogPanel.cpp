#include "editor/panels/LogPanel.h"

void LogPanel::Draw()
{
    ImGui::Begin("Log");
        for(const auto& message : Logger::GetLogBuffer())
        {
            ImGui::Text("%s", message.c_str());

        }
    ImGui::End();
}