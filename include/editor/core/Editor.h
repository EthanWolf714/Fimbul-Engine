#pragma once
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include "editor/panels/LogPanel.h"
#include "Ulfr/renderer/Renderer.h"
#include "Ulfr/core/Logger.h"

class Editor
{
    public:
        void Draw();
        void Init();
    private:
        Camera m_editorCam;
        LogPanel m_logPanel;
};