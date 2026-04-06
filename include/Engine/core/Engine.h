#pragma once
#include "raylib.h"
#include "rlgl.h"
#include "rlImGui.h"
#include "imgui.h"
#include "Engine/renderer/Renderer.h"
#include "Engine/renderer/Camera.h"
#include "Engine/resources/TextureManager.h"
#include "Game/map/Map.h"
#include "Game/entities/Player.h"
#include "Logger.h"
#include "Editor/core/Editor.h"
#include "InputHandler.h"


enum class EngineMode
{
    Game,
    Editor
};
class Engine {
    public:
        
        void Run();
        
    
    private:
        void Update(float dt);
        void Render();
        void SetMode(EngineMode mode);
        void ShutDown();
        void Init();

        //subsystems
        Editor m_editor;
        EngineMode m_mode = EngineMode::Editor;
        Renderer m_renderer;
        GameCamera m_camera;
        InputHandler    m_input;
        TextureManager m_textureManager;
        bool m_running = false;
        Map m_map;
        Player m_player;
        
        
        
       

      

};

