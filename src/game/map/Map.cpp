#include "game/map/Map.h"

//takes in coordinate values and adds them to wall list
void Map::AddWall(float x1, float z1, float x2, float z2)
{
    m_walls.push_back({x1,z1,x2,z2, 0.0f, 2.0f});
}

void Map::Build(){
    m_walls.clear();

    //loop through every cell in the map
    for(int z = 0; z < MAP_HEIGHT; z++)
    {
        for(int x = 0; x < MAP_WIDTH; x++)
        {
            //if cell is empty continue
            if(worldMap[z][x] == 0) continue;

            //if cell is a wall, check all four neighbors
            //each wall thats empty 
            if(z > 0 && worldMap[z-1][x] == 0)
            {
                AddWall(x,z,x+1,z);
            }

            if(z < MAP_HEIGHT-1 && worldMap[z+1][x] == 0)
            {
                AddWall(x+1, z+1, x, z+1);
            }

            if(x < MAP_WIDTH-1 && worldMap[z][x+1] == 0)
            {
                AddWall(x+1, z, x+1, z+1);
            
            }

            if(x > 0 && worldMap[z][x-1] == 0)
            {
                AddWall(x, z+1, x,z);
            }
        }
    }
}