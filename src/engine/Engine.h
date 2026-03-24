#pragma once
#include "raylib.h"
#include "rlgl.h"
#include "Renderer.h"
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
        Camera3D m_camera;
        TextureManager m_textureManager;
        bool m_running = false;

};