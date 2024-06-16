#pragma once

struct Point
{   
    float X    = 0;
    float Y    = 0;
    float VelX = 0;
    float VelY = 0;
};

struct vec2
{
    float X;
    float Y;

    vec2()
    {
        this->X = 1;
        this->Y = 1;
    }

    vec2(float x, float y)
    {
        this->X = x;
        this->Y = y;
    }

    float Len()
    {
        return sqrt(X * X + Y * Y);
    }
};