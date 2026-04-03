#pragma once

#include "raylib.h"

class InputHandler
{
    public:
    void Update();

    //movement keys
    bool MoveForward() const {return m_forward;}
    bool MoveBackward() const {return m_backward;}
    bool StrafeLeft() const {return m_left;}
    bool StrafeRight() const {return m_right;}
    //mouse

    Vector2 GetMouseDelta() const {return m_mouseDelta;}

    private:
        //booleans for controls, set to false
        bool m_forward = false;
        bool m_backward = false;
        bool m_left = false;
        bool m_right = false;

        Vector2 m_mouseDelta = {0};

};