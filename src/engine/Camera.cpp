#include "Camera.h"

void GameCamera::Init()
{
    m_camera = { 0 };
    m_camera.position = (Vector3){  5.0f, 5.0f, 5.0f }; // looking at the quad from 5 units back
    m_camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    m_camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    m_camera.fovy = 60.0f;
    m_camera.projection = CAMERA_PERSPECTIVE;
    DisableCursor();
}

Camera3D& GameCamera::GetCamera()
{
    return m_camera;
}