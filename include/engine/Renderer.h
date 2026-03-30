#pragma once
#include "raylib.h"
#include "rlgl.h"
#include <string>

class Renderer
{
    public:
        void Init();
        void Update();
        void ShutDown();
        void Draw(Camera& camera, Texture m_testTexture);
        void DrawTestQuad(Texture m_testTexture);
        void BeginFrame(Camera3D& camera);
        void EndFrame();
    private:
        Texture2D m_testTexture;
        Texture2D m_Texture;
        
};