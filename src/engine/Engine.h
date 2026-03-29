#pragma once
#include "raylib.h"
#include "rlgl.h"
#include "rlImGui.h"
#include "imgui.h"
#include "Renderer.h"
#include "Camera.h"
#include "TextureManager.h"
class Engine {
    public:
        void Init();
        void Run();
        void ShutDown();

    private:
        void Update();
        void Render();
        Renderer m_renderer;
        GameCamera m_camera;
        TextureManager m_textureManager;
        bool m_running = false;

};