#include "Engine.h"

void Engine::Init(){
    InitWindow(800, 450, "Ulfr Engine");
    SetTargetFPS(60);
    m_running = true;
    
    m_renderer.Init();
    m_camera.Init();
    m_textureManager.Load("assets/pics/greystone.png");
    m_textureManager.Load("assets/pics/mossy.png");
    
    TraceLog(LOG_INFO, "Working directory: %s", GetWorkingDirectory());
}

void Engine::Run(){
    while(!WindowShouldClose() && m_running)
    {
       
        Update();
        Render();
    }
}

void Engine::ShutDown(){
    m_renderer.ShutDown();
    CloseWindow();
}

void Engine::Update()
{
    UpdateCamera(&m_camera.GetCamera(), CAMERA_FREE);
}

void Engine::Render()
{
    Texture2D wallText = m_textureManager.Get("assets/pics/mossy.png");
    BeginDrawing();
        ClearBackground(BLACK);    
        m_renderer.Draw(m_camera.GetCamera(), wallText);
    EndDrawing();


}