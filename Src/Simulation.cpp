#include <GL/glut.h>
#include <sstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "Utils.h"

struct Point
{   
    float X    = 0;
    float Y    = 0;
    float VelX = 0;
    float VelY = 0;
};

class Simulation
{
public:
    const float RatioFactor = 1;
    std::vector<Point> Points;

    Simulation(float w = 100, float h = 100, float pointsCount = 10)
    {
        this->pointsCount = pointsCount;
        Points = std::vector<Point>(pointsCount);
        width = w; height = h;
        RandomInit();
    }

    void Display()
    {
        ConstrainPoints();
        for (int i = 0; i < pointsCount; i++)
            DisplayPoint(Points[i].X, Points[i].Y);
    }

    void SetDimention(float w, float h)
    {
        width = w * RatioFactor;
        height = h * RatioFactor;
    }

private:
    float width = 100;
    float height = 100;
    int pointsCount = 10;

    void DisplayPoint(float posX, float posY)
    {
        glLoadIdentity();
        glColor3f(0.0f, 0.0f, 1.0f);
        glPointSize(10);
        glBegin(GL_POINTS);
        glVertex2f(posX * 2 / width - 1, posY * 2 / height - 1);
        glEnd();
    }

    void ConstrainPoints()
    {
        for (int i = 0; i < pointsCount; i++)
        {
            Points[i].X = constraint(Points[i].X, 0, width);
            Points[i].Y = constraint(Points[i].Y, 0, width);
        }
    }

    void RandomInit()
    {
        for (int i = 0; i < pointsCount; i++)
        {
            Points[i].X = getRandom(0, width);
            Points[i].Y = getRandom(0, height);
        }
    }
};