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

class Gradient
{
public:
    void Update(float w, float h, std::vector<Point>& points)
    {

    }

    void GetAt(float posX, float posY, float& resX, float& resY)
    {
        resX = 0;
        resY = 0;
    }
};

class Simulation
{
public:
    const float RatioFactor = 1;
    const float Viscosity = 0.003;
    const float Gravity = 0.00;
    std::vector<Point> Points;
    Gradient gradient;

    Simulation(float w = 100, float h = 100, float pointsCount = 10)
    {
        this->pointsCount = pointsCount;
        Points = std::vector<Point>(pointsCount);
        width = w; height = h;
        RandomInit();
    }

    void Display()
    {
        gradient.Update(width, height, Points);
        for (Point& p : Points)
        {
            Move(p);
            DisplayPoint(p.X, p.Y);
        }
        ConstrainPoints();
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

    void Move(Point& point)
    {
        point.X += point.VelX;
        point.Y += point.VelY;

        point.VelX *= point.X >= width || point.X <= 0 ? -1 : 1;
        point.VelY *= point.Y >= height || point.Y <= 0 ? -1 : 1;

        point.VelX *= (1 - Viscosity);
        point.VelY *= (1 - Viscosity);

        point.VelY -= Gravity;

        float gX; float gY;
        gradient.GetAt(point.X, point.Y, gX, gY);
        point.VelX += gX; point.VelY += gY; 
    }

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
            Points[i].Y = constraint(Points[i].Y, 0, height);
        }
    }

    void RandomInit()
    {
        for (int i = 0; i < pointsCount; i++)
        {
            Points[i].X = getRandom(0, width);
            Points[i].Y = getRandom(0, height);
            Points[i].VelX = getRandom(-4, 4);
            Points[i].VelY = getRandom(-4, 4);
        }
    }
};