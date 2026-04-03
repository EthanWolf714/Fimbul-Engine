#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>
#define MAP_HEIGHT 10
#define MAP_WIDTH 10



struct Wall {
    float x1, z1;
    float x2, z2;
    float floorHeight;
    float ceilHeight;
};

class Map {
    public:
        void Build();
        const std::vector<Wall>& GetWalls() const {return m_walls;}

    private: 
        void AddWall(float x1, float z1, float x2, float z2);

        std::vector<Wall> m_walls;

        int worldMap[MAP_HEIGHT][MAP_WIDTH] =
        {
            {1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,0,0,1,1,0,0,0,0,1},
            {1,0,0,1,0,0,0,0,0,1},
            {1,0,0,0,0,0,1,0,0,1},
            {1,0,0,0,0,0,1,0,0,1},
            {1,0,0,0,0,0,1,0,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1}
        };
};
