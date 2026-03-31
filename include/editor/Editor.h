#pragma once
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include "editor/LogPanel.h"
#include "engine/Camera.h"
#include "engine/Logger.h"

class Editor
{
    public:
        void Draw();
        void Init();
    private:
        Camera m_editorCam;
        LogPanel m_logPanel;
};