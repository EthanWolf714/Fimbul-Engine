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
    private:
        Texture2D m_testTexture;
};