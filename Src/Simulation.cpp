#include <GL/glut.h>
#include <sstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "Utils.h"

class Simulation
{
public:
    const float RatioFactor = 1;

    std::vector<float> xs;
    std::vector<float> ys;

    Simulation(float w = 100, float h = 100, float pointsCount = 10)
    {
        this->pointsCount = pointsCount;
        xs = std::vector<float>(pointsCount);
        ys = std::vector<float>(pointsCount);
        width = w;
        height = h;
        RandomInit();
    }

    void Display()
    {
        ConstrainPoints();
        for (int i = 0; i < pointsCount; i++)
        {
            DisplayPoint(xs[i], ys[i]);
        }
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
        //glTranslatef(posX * 2 / width - 1, posY * 2 / height - 1, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glPointSize(10);
        glBegin(GL_POINTS);
        glVertex2f(posX * 2 / width - 1, posY * 2 / height - 1);
        glEnd();
        //glutSolidSphere(0.01, 5, 5);  
    }

    void ConstrainPoints()
    {
        for (int i = 0; i < pointsCount; i++)
        {
            xs[i] = constraint(xs[i], 0, width);
            ys[i] = constraint(ys[i], 0, height);
        }
    }

    void RandomInit()
    {
        for (int i = 0; i < pointsCount; i++)
        {
            xs[i] = getRandom(0, width);
            ys[i] = getRandom(0, height);
        }
    }
};