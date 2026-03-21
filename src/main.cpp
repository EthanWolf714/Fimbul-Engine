#include "raylib.h"
#include "raymath.h"
#include <cmath>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 800
#define screenHeight 450

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int worldMap[mapWidth][mapHeight] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


double posX = 22, posY = 12;
double dirX = -1, dirY = 0;
double planeX = 0, planeY = 0.66;
//speed modifiers
double moveSpeed;//the constant value is in squares/second
double rotSpeed; //the constant value is in radians/second

int main()
{

    // Initialization
    
    InitWindow(screenWidth, screenHeight, "Ulfr Engine (raycaster)");

   
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        moveSpeed = GetFrameTime() * 5.0;
        rotSpeed = GetFrameTime() * 3.0;
        
        // Update
        //move forware if no wall in front of you
        if(IsKeyDown(KEY_W)){
            if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == 0) posX += dirX * moveSpeed;
            if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
            
        }
        //movebackward if no wall behind you
        if(IsKeyDown(KEY_S)){
             if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == 0) posX -= dirX * moveSpeed;
            if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == 0) posY -= dirY * moveSpeed;
        }

        //rotate to the right
        if(IsKeyDown(KEY_D)){
            //both camera and direction and camera plane must be rotated
            double oldDirX = dirX;
            dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
            dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
            planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);

        }

        if(IsKeyDown(KEY_A)){
            //both camera and direction and camera plane must be rotated
            double oldDirX = dirX;
            dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
            dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
            planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);

        }
        // Draw
       
        BeginDrawing();
            ClearBackground(BLACK); 
            for(int x = 0; x < screenWidth; x++){
                //calculate ray position and direction
                double cameraX = 2 * x / double(screenWidth) - 1; //x-coordinate in camera space
                double rayDirX = dirX + planeX * cameraX;
                double rayDirY = dirY + planeY * cameraX;

                //which box of the map we're in
                int mapX = int(posX);
                int mapY = int(posY);

                //length of ray from current postiions to next x or y-side
                double sideDistX;
                double sideDistY;

                //length of ray from one x or y-side to the next
                double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1/rayDirX);
                double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1/rayDirY);
                double perpWallDist;

                //what direction to step in x or y direction (+1 or -1)
                int stepX;
                int stepY;

                int hit = 0; //was there a wall hit?
                int side; //was a NS or a EW wall hit?

                //calculate step and initial sideDist
                if(rayDirX < 0){
                    stepX = -1;
                    sideDistX = (posX - mapX) * deltaDistX;
                }
                else{
                    stepX = 1;
                    sideDistX = (mapX + 1.0 - posX) * deltaDistX;
                }

                if(rayDirY < 0){
                    stepY = -1;
                    sideDistY = (posY - mapY) * deltaDistY;

                }
                else{
                    stepY = 1;
                    sideDistY = (mapY + 1.0 - posY) * deltaDistY;
                }

                //start DDA
                while(hit == 0){
                    if(sideDistX < sideDistY){
                        sideDistX += deltaDistX;
                        mapX += stepX;
                        side = 0;
                    }
                    else{ 
                        sideDistY += deltaDistY;
                        mapY += stepY;
                        side = 1;
                    }

                    //check for ray hit
                    if(worldMap[mapX][mapY] > 0) hit = 1;
                }

                //calculate dist projected on camera direction (Euclidean distance would give the fish eye effect)
                if(side == 0) perpWallDist = (sideDistX - deltaDistX);
                else          perpWallDist = (sideDistY - deltaDistY);

                //calculate height of line to draw on screen
                int lineHeight = (int)(screenHeight / perpWallDist);

                //calculate lowest and highest pixel to fille in current stripe
                int drawStart = -lineHeight / 2 + screenHeight / 2;
                if(drawStart < 0) drawStart = 0;
                int drawEnd = lineHeight / 2 + screenHeight / 2;
                if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;

                //choose wall color
                Color color;
                switch (worldMap[mapX][mapY])
                {
                case 1: color = RED; break;
                case 2: color = GREEN; break;
                case 3: color = BLUE; break;
                case 4: color = WHITE; break;
                                
                default: color = YELLOW; break;
                }

                //give x and y sides different brightness
                if (side == 1) {color = ColorBrightness(color, -0.5f);}




                //draw the pixels of the stripe as a vertical line
                DrawLine(x, drawStart,x,  drawEnd, color);
            }
            

            //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }
    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}
