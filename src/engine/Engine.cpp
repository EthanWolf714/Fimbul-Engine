#include "Engine.h"

void Engine::Init(){
    InitWindow(800, 450, "Ulfr Engine");
    SetTargetFPS(60);
    m_running = true;
    m_camera = { 0 };
    m_camera.position = (Vector3){ 0.0f, 0.0f, 5.0f }; // looking at the quad from 5 units back
    m_camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    m_camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    m_camera.fovy = 60.0f;
    m_camera.projection = CAMERA_PERSPECTIVE;
    m_renderer.Init();

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
    UpdateCamera(&m_camera, CAMERA_FREE);
}

void Engine::Render()
{
    Texture2D wallText = m_textureManager.Get("assets/pics/mossy.png");
    BeginDrawing();
        ClearBackground(BLACK);    
        m_renderer.Draw(m_camera, wallText);
    EndDrawing();


}