#pragma once
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include "Editor/panels/LogPanel.h"
#include "Engine/renderer/Renderer.h"
#include "Engine/core/Logger.h"

class Editor
{
    public:
        void Draw();
        void Init();
    private:
        Camera m_editorCam;
        LogPanel m_logPanel;
};