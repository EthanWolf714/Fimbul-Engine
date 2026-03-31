#pragma once
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#define MAP_HEIGHT 10
#define MAP_WIDTH 10

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

struct Wall {
    float x1, z1;
    float x2, z2;
    float floorHeight;
    float ceilHeight;
};