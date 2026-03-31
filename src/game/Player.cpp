#include "game/player.h"
#include <iostream>

Player::Player()
{
    Logger::DebugPrintF("Player created!");
    //player size init
    size.x = 0.5;
    size.y = 1.0f;
    size.z = 0.5;

    //init speed and sense
    speed = 0.05f;
    velocity = Vector3Zero();
    mouseSensitivity = 0.3f;

    //player camera
    m_PlayerCam = {0};
    m_PlayerCam.position = (Vector3){5.0,size.y, 5.0f};
    m_PlayerCam.target = Vector3Zero(); // camera looking at point
    m_PlayerCam.up = (Vector3){0.0f, 1.0f, 0.0f}; // camera up vector
    m_PlayerCam.fovy = 90.0f;
    m_PlayerCam.projection = CAMERA_PERSPECTIVE;
    cameraMode = CAMERA_FIRST_PERSON;
    DisableCursor(); // limit cursor movement to window

    previousPosition = m_PlayerCam.position;

    //gravity physics
    gravity = -10.0f;
    planeCollision = true;


}



void Player::Update()
{
    this->SavePosition();


    //update camera position
    if(cameraMode == CAMERA_FREE)
    {
        UpdateCamera(&m_PlayerCam, cameraMode);
    }

    if(cameraMode != CAMERA_FREE)
    {
        Vector3 forward = Vector3Normalize(Vector3Subtract(m_PlayerCam.target, m_PlayerCam.position));
        m_PlayerCam.target = Vector3Add(m_PlayerCam.position, Vector3Scale(forward, 100.0f));

        float floorHeight = size.y;
        if(m_PlayerCam.position.y < floorHeight)
        {
            m_PlayerCam.position.y = previousPosition.y;
            
        }

        UpdateCameraPro(&m_PlayerCam,
                    (Vector3){(IsKeyDown(KEY_W) - IsKeyDown(KEY_S)) * speed,
                              (IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * speed,
                              0.0f},
                    (Vector3){GetMouseDelta().x * mouseSensitivity,
                              GetMouseDelta().y * mouseSensitivity, 0.0f},
                    0.0f);
        
        //velocity vecotr update
        velocity = Vector3Subtract(m_PlayerCam.position, previousPosition);

        //update position
        boundingBox.min =
            (Vector3){m_PlayerCam.position.x - size.z / 2.0f, m_PlayerCam.position.y - size.y,
                  m_PlayerCam.position.z - size.x / 2.0f};
        boundingBox.max =
            (Vector3){m_PlayerCam.position.x + size.z / 2.0f, m_PlayerCam.position.y,
                  m_PlayerCam.position.z + size.x / 2.0f};
    }
    
    // if player falls through map, reset position
  if (GetBoundingBox().min.y <= -30) {
    std::cerr << "PLAYER FELL through map" << std::endl;
    m_PlayerCam.position.y = size.y + 20;
  }

}

void Player::Draw()
{
    DrawBoundingBox(boundingBox, LIME);
}
Camera& Player::GetCamera()
{
 return m_PlayerCam;   
}
Vector3 Player::GetPosition() {
  return Vector3Subtract(m_PlayerCam.position, (Vector3){0.0f, size.y / 2.0f, 0.0f});
}

Vector3 Player::GetSize() { return size; }

Vector3 Player::GetVelocity() { return velocity; }

BoundingBox Player::GetBoundingBox() { return boundingBox; }

void Player::SavePosition() { previousPosition = m_PlayerCam.position; }


void Player::SetXPos(float x) { m_PlayerCam.position.x = x; }
void Player::SetYPos(float y) { m_PlayerCam.position.y = y; }
void Player::SetZPos(float z) { m_PlayerCam.position.z = z; }

void Player::setPlaneCollision(bool b) { planeCollision = b; }

void Player::setVelocity(Vector3 velocity) { this->velocity = velocity; }