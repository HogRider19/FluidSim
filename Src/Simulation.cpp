#include <GL/glut.h>
#include <sstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>
#include "Utils.h"
#include "Point.h"
#include "Gradient.cpp"


class Simulation
{
public:
    const float RatioFactor = 1;
    const float Viscosity = 0.001;
    const float Gravity = 0.01;
    std::vector<Point> Points;
    Gradient gradient = Gradient();

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
        //gradient.DrawSpace(10);
        for (Point& p : Points)
        {
            Move(p);
            HandleBorders(p);
            HandleSpace(p);
            //HandleGradient(p);
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
    }

    void HandleBorders(Point& point)
    {
        point.VelX *= point.X >= width || point.X <= 0 ? -1 : 1;
        point.VelY *= point.Y >= height || point.Y <= 0 ? -1 : 1; 
    }

    void HandleSpace(Point& point)
    {
        point.VelX *= (1 - Viscosity);
        point.VelY *= (1 - Viscosity);
        point.VelY -= Gravity;
    }

    void HandleGradient(Point& point)
    {
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
            Points[i].VelX = getRandom(-2, 2);
            Points[i].VelY = getRandom(-2, 2);
        }
    }
};
