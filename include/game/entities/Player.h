#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Ulfr/renderer/Camera.h"
#include "Ulfr/core/Logger.h"
#include "Ulfr/core/InputHandler.h"


//modeled after froopy090 fps-game in ralyib 


class Player 
{
    

    public:
        Camera m_PlayerCam;
        int cameraMode;
        Player();
        void Update(float dt, const InputHandler& input);
        void Draw();

        Vector3 GetPosition();
        Camera& GetCamera();
        Vector3 GetSize();
        BoundingBox GetBoundingBox();
        Vector3 GetVelocity();
        Vector3 GetPreviousPosition();
        void SavePosition();
        void SetXPos(float x);
        void SetYPos(float y);
        void SetZPos(float z);
        void setPlaneCollision(bool b);
        void Gravity(bool b);
        void setVelocity(Vector3 velocity);
        

    private:
        Vector3 size;
        Vector3 velocity;
        float speed;
        float mouseSensitivity;

        BoundingBox boundingBox;
        Vector3 previousPosition;

        float gravity;
        bool planeCollision;
     
        

};





