#include "Engine/core/Engine.h"




void Engine::Init(){
     printf("Engine Init called\n"); 
    Logger::DebugPrintF("Engine Initialized");
    InitWindow(800, 450, "Engine Engine");
    SetTargetFPS(60);
    rlImGuiSetup(true);

    m_renderer.Init();
    m_textureManager.Init();
    m_editor.Init();
    m_camera.Init();
    Logger::DebugPrintF("camera Initialized");
    m_map.Build();
     Logger::DebugPrintF("Map built");
    m_textureManager.Load("assets/pics/greystone.png");
    m_textureManager.Load("assets/pics/mossy.png");

    SetMode(EngineMode::Editor);
    m_running = true;
    Logger::DebugPrintF("Engine initialized");
    

}

void Engine::Run(){
    Init();
    while(!WindowShouldClose() && m_running)
    {
       float dt = GetFrameTime();
        Update(dt);
        Render();
    }
    ShutDown();
}

void Engine::ShutDown(){
   m_textureManager.ShutDown();
    Logger::DebugPrintF("Engine Shutdown");
    m_renderer.ShutDown();
    Logger::DebugPrintF("Renderer shutting down");
    rlImGuiShutdown();
    Logger::DebugPrintF("rlglImGUi shutting down");
    CloseWindow();
    Logger::DebugPrintF("Closing Window...");
}


void Engine::SetMode(EngineMode mode) {
    m_mode = mode;
    if(m_mode == EngineMode::Game) {
        DisableCursor();
    } else {
        EnableCursor();
    }
}

void Engine::Update(float dt)
{

     if(IsKeyPressed(KEY_ONE)) {
        SetMode(m_mode == EngineMode::Game 
            ? EngineMode::Editor 
            : EngineMode::Game);
    }
    if(m_mode == EngineMode::Game){
        m_input.Update();
        m_player.Update(dt, m_input);
    }else{
        UpdateCamera(&m_camera.GetCamera(), CAMERA_FREE);
    }
}

void Engine::Render()
{
    Texture2D wallText = m_textureManager.Get("assets/pics/mossy.png");
        //m_renderer.BeginFrame(m_camera.GetCamera()); 
        if(m_mode == EngineMode::Editor){
            m_renderer.BeginFrame(m_camera.GetCamera()); 
        }
        if(m_mode == EngineMode::Game)
        {
            m_renderer.BeginFrame(m_player.GetCamera()); 
        } 
           for(auto& wall : m_map.GetWalls())
            {
                m_renderer.DrawWall(wall, wallText);
            }
            m_player.Draw();
           
        m_renderer.EndFrame();
            rlImGuiBegin();
                m_editor.Draw();
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