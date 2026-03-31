#include "engine/Engine.h"




void Engine::Init(){
    InitWindow(800, 450, "Ulfr Engine");
    SetTargetFPS(60);
    m_running = true;
    rlImGuiSetup(true);
    m_renderer.Init();
    m_camera.Init();
    m_textureManager.Load("assets/pics/greystone.png");
    m_textureManager.Load("assets/pics/mossy.png");
    
    TraceLog(LOG_INFO, "Working directory: %s", GetWorkingDirectory());

    m_level[0] = {-5, -5,  5, -5, 0, 16};
    m_level[1] = { 5, -5,  5,  5, 0, 16};
    m_level[2] = { 5,  5, -5,  5, 0, 16};
    m_level[3] = {-5,  5, -5, -5, 0, 16};

    TraceLog(LOG_INFO, "Wall 0: %.1f %.1f %.1f %.1f", 
        m_level[0].x1, m_level[0].z1, 
        m_level[0].x2, m_level[0].z2);

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
    rlImGuiShutdown();
    CloseWindow();
}

void Engine::Update()
{
    UpdateCamera(&m_camera.GetCamera(), CAMERA_FREE);
}

void Engine::Render()
{
    Texture2D wallText = m_textureManager.Get("assets/pics/mossy.png");
        m_renderer.BeginFrame(m_camera.GetCamera()); 
            for(auto& wall : m_level)
            {
             
                m_renderer.DrawWall(wall, wallText);
            }
        m_renderer.EndFrame();
            rlImGuiBegin();

                ImGui::Begin("Debug");
                    ImGui::Text("FPS: %d", GetFPS());
                    ImGui::Text("Camera Pos: %.2f, %.2f, %.2f",
                            m_camera.GetCamera().position.x, 
                            m_camera.GetCamera().position.y, 
                            m_camera.GetCamera().position.z );
                ImGui::End();
            rlImGuiEnd();


        EndDrawing();
    


}