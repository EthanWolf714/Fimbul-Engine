#pragma once
#include "raylib.h"
class GameCamera {
    public:
        void Init();
        void ShutDown();
        Camera3D& GetCamera();

    private:
    Camera3D m_camera;

};