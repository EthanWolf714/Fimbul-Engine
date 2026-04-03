#include "engine/core/InputHandler.h"
void InputHandler::Update()
{
    m_forward = IsKeyDown(KEY_W);
    m_backward = IsKeyDown(KEY_S);
    m_left = IsKeyDown(KEY_A);
    m_right = IsKeyDown(KEY_D);

    m_mouseDelta = ::GetMouseDelta();
}