#include "engine/Engine.h"




void Engine::Init(){
     printf("Engine Init called\n"); 
    Logger::DebugPrintF("Engine Initialized");
    InitWindow(800, 450, "Ulfr Engine");
    SetTargetFPS(60);
    m_running = true;
    rlImGuiSetup(true);
    m_renderer.Init();
     Logger::DebugPrintF("Renderer Initialized");
    m_editor.Init();
     Logger::DebugPrintF("Editor Initialized");
    m_camera.Init();
     Logger::DebugPrintF("camera Initialized");
    m_map.Build();
     Logger::DebugPrintF("Map built");
    m_textureManager.Load("assets/pics/greystone.png");
    m_textureManager.Load("assets/pics/mossy.png");
    
    

}

void Engine::Run(){
    
    while(!WindowShouldClose() && m_running)
    {
       
        Update();
        Render();
    }
}

void Engine::ShutDown(){
   
    Logger::DebugPrintF("Engine Shutdown");
    m_renderer.ShutDown();
    Logger::DebugPrintF("Renderer shutting down");
    rlImGuiShutdown();
    Logger::DebugPrintF("rlglImGUi shutting down");
    CloseWindow();
    Logger::DebugPrintF("Closing Window...");
}

void Engine::Update()
{

    if(IsKeyPressed(KEY_ONE))
    {
        if(m_mode == EngineMode::Game){
            m_mode = EngineMode::Editor;
            EnableCursor();
        }
        else{
            m_mode = EngineMode::Game;
            DisableCursor();
        } 
    } 
     if(m_mode == EngineMode::Game){
        m_player.Update();
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