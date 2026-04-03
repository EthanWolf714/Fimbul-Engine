#include "engine/renderer/Renderer.h"

void Renderer::Init()
{
   Logger::DebugPrintF("Initializing renderer");

   Logger::DebugPrintF("Renderer Initialized");
}

void Renderer::Update()
{

}

void Renderer::ShutDown()
{
    UnloadTexture(m_Texture);
}

void Renderer::Draw(Camera& camera, Texture m_Texture)
{
    
   
    rlDisableBackfaceCulling();
        DrawGrid(10,1.0f);
        rlSetTexture(m_Texture.id);
        rlBegin(RL_QUADS);
            // front face of a wall quad
            // x is left/right, y is up/down, z is depth
            
            rlTexCoord2f(0.0f, 0.0f);
            rlVertex3f(-1.0f,  1.0f, 0.0f); // top left
                
            rlTexCoord2f(0.0f, 1.0f);
            rlVertex3f(-1.0f, -1.0f, 0.0f); // bottom left

            rlTexCoord2f(1.0f, 1.0f);
            rlVertex3f( 1.0f, -1.0f, 0.0f); // bottom right

            rlTexCoord2f(1.0f, 0.0f);
            rlVertex3f( 1.0f,  1.0f, 0.0f); // top right

            
        rlEnd();
        rlSetTexture(0);
}

void Renderer::DrawWall(const Wall& wall, Texture2D m_texture)
{
        rlSetTexture(m_texture.id);
        rlBegin(RL_QUADS);
            // front face of a wall quad
            // x is left/right, y is up/down, z is depth
            
            rlTexCoord2f(0.0f, 0.0f);
            rlVertex3f(wall.x1, wall.ceilHeight, wall.z1); // top left
                
            rlTexCoord2f(0.0f, 1.0f);
            rlVertex3f(wall.x1, wall.floorHeight, wall.z1); // bottom left

            rlTexCoord2f(1.0f, 1.0f);
            rlVertex3f( wall.x2, wall.floorHeight, wall.z2); // bottom right

            rlTexCoord2f(1.0f, 0.0f);
            rlVertex3f(wall.x2, wall.ceilHeight, wall.z2); // top right

            
        rlEnd();
    rlSetTexture(0);
}

void Renderer::DrawFloor()
{
    const int floorExtent = 25;
    const float tileSize = 0.5f;
    const Color tileColor1 = (Color){150, 200, 200, 255};

    for(int y = -floorExtent; y < floorExtent; y++)
    {
        for(int x = -floorExtent; x < floorExtent; x++)
        {
            if((y & 1) && (x & 1))
            {
                DrawPlane((Vector3){ x*tileSize, 0.0f, y*tileSize}, (Vector2){tileSize, tileSize}, tileColor1);

            }
            else if (!(y & 1) && !(x & 1))
            {
                DrawPlane((Vector3){ x*tileSize, 0.0f, y*tileSize}, (Vector2){ tileSize, tileSize }, LIGHTGRAY);
            }
        }
    }

}

void Renderer::BeginFrame(Camera3D& camera)
{
    BeginDrawing();
        ClearBackground(BLACK);
        
        BeginMode3D(camera);
            rlDisableBackfaceCulling();

}

void Renderer::EndFrame()
{
             
        EndMode3D();
       
   

}

