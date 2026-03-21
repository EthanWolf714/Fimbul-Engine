#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <cstdint>
#include <vector>
#include <cstring>

#define mapWidth 24
#define mapHeight 24
#define texWidth 64
#define texHeight 64
#define screenWidth 800
#define screenHeight 450

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int worldMap[mapWidth][mapHeight] =
{
  {8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
  {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
  {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
  {8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
  {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
  {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
  {8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
  {7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
  {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
  {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
  {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
  {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
  {7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
  {2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
  {2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
  {2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
  {1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
  {2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
  {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
  {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
  {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
  {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
  {2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
};


double posX = 22, posY = 12;
double dirX = -1, dirY = 0;
double planeX = 0, planeY = 0.66;
//speed modifiers
double moveSpeed;//the constant value is in squares/second
double rotSpeed; //the constant value is in radians/second


int main()
{
    InitWindow(screenWidth, screenHeight, "Ulfr Engine (raycaster)");
    TraceLog(LOG_INFO, "Window created");


    TraceLog(LOG_INFO, "Starting raycaster...");
    std::vector<int> texture[8];
    for(int i = 0; i < 8; i++)texture[i].resize(texWidth * texHeight);

    //create blank img on cpu and generate a blank image at screen resolution
    Image img = GenImageColor(screenWidth, screenHeight, BLACK);
    //uplaod image to the GPU as a texture
    Texture2D screen = LoadTextureFromImage(img);
    //create cpu side pixel buffer using raylib Color
    //malloc allocated a flay array of Colors, once per pixel
    Color* pixels = (Color*)malloc(screenWidth * screenHeight * sizeof(Color));
    if(pixels == NULL) {
        CloseWindow();
        return -1;
    }
    //unload image from CPU memory since we don't need it anymore.
    UnloadImage(img);
    TraceLog(LOG_INFO, "Buffer created");

    // Initialization
    
    

   
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    //generate textures
    Image  texImages[8];
    texImages[0] = LoadImage("src/assets/pics/eagle.png");
    texImages[1] = LoadImage("src/assets/pics/redbrick.png");
    texImages[2] = LoadImage("src/assets/pics/purplestone.png");
    texImages[3] = LoadImage("src/assets/pics/greystone.png");
    texImages[4] = LoadImage("src/assets/pics/bluestone.png");
    texImages[5] = LoadImage("src/assets/pics/mossy.png");
    texImages[6] = LoadImage("src/assets/pics/wood.png");
    texImages[7] = LoadImage("src/assets/pics/colorstone.png");

    //load the pixel data from each image into your texture array
    Color* texColors[8];
    for(int i = 0; i < 8; i++) {
        texColors[i] = LoadImageColors(texImages[i]);
        UnloadImage(texImages[i]);
    }   

    TraceLog(LOG_INFO, "Textures generated");

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

            //Floot casting
            for(int y = 0; y < screenHeight; y++){
                //rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
                float rayDirX0 = dirX - planeX;
                float rayDirY0 = dirY - planeY;
                float rayDirX1 = dirX + planeX;
                float rayDirY1 = dirY + planeY;

                //current y position compared to the center of the screen ( horizan)
                int p = y - screenHeight / 2;

                //vertical position of the camera
                float posZ = 0.5 * screenHeight;

                //Horizontal distance from the camera to the floor for the current row.
                //0.5 is the z position exactly in the middle betweeen floor and ceiling
                float rowDistance = posZ / p;

                //calculate real world step vector we have to add for each x (parallel to camera plane)
                //adding step by step avoids multiplications with a weight  in the inner loop
                float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / screenWidth;
                float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / screenWidth;

                //real world coordinates of the leftmost column this will be updated as we step to the right
                float floorX = posX + rowDistance * rayDirX0;
                float floorY = posY + rowDistance * rayDirY0;

                for(int x = 0; x < screenWidth; ++x){
                    //the cell coord is simply got from the integer parts of floorX and floorY
                    int cellX = (int)(floorX);
                    int cellY = (int)(floorY);

                    //get the texture coordinates from the fractional part
                    int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
                    int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

                    floorX += floorStepX;
                    floorY += floorStepY;

                    //choose texture and draw pixel
                    int floorTexture = 3;
                    int ceilingTexture  = 6;
                    Color floorTexColor = texColors[floorTexture][texWidth * ty + tx];
                    Color ceilingTexColor = texColors[ceilingTexture][texWidth * ty + tx];
                    //floor
                    pixels[(screenHeight - y - 1) * screenWidth + x] = floorTexColor;
                    //ceiling
                    pixels[y * screenWidth + x] = ceilingTexColor;

                }

            }



            //Wall casting
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

                //texturing calculations
                int textNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so texture 0 can be used

                //value of wallX
                double wallX;
                if(side == 0) wallX = posY + perpWallDist * rayDirY;
                else          wallX = posX + perpWallDist * rayDirX;
                wallX -= floor((wallX));
               
                //x coordinate on texture
                int texX = int(wallX * double(texWidth));
                if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
                if(side == 1 && rayDirX < 0) texX = texWidth - texX - 1;
                
                // how much to increase texture coordiate per screen pixel
                double step = 1.0 * texHeight / lineHeight;
                //start textureing coordinate
                double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
                for(int y = drawStart; y < drawEnd; y++)
                {
                    //cast texture coordinate to integer and mask with texHeight-1 in case of overflow
                    int texY = (int)texPos & (texHeight - 1);
                    texPos += step;

                    Color texColor = texColors[textNum][texY * texWidth + texX];
                    if(side == 1){
                        texColor.r /= 2;
                        texColor.g /= 2;
                        texColor.b /= 2;
                    }
                    pixels[y * screenWidth + x] = texColor;
                }



                
            }

        
            
            //update textures each frame;    
            UpdateTexture(screen, pixels);
            DrawTexture(screen, 0,0, WHITE);
            

            DrawText(TextFormat("FPS: %02i", GetFPS()), 0, 0, 20, BLUE);

        EndDrawing();
        //CLEAR PIXEL BUFFER EACH FRAME
        memset(pixels, 0, screenWidth * screenHeight * sizeof(Color));
        
    }
    // De-Initialization
   for(int i = 0; i < 8; i++){
    UnloadImageColors(texColors[i]);
   }
    CloseWindow();        // Close window and OpenGL context

    return 0;
}
