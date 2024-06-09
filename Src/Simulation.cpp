#include <GL/glut.h>
#include <sstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "Utils.cpp"

class Simulation
{
public:
    const float RatioFactor = 1;

    std::vector<float> xs;
    std::vector<float> ys;

    Simulation(int pointsCount = 10)
    {
        this->pointsCount = pointsCount;
        xs = std::vector<float>(pointsCount);
        ys = std::vector<float>(pointsCount);
    }

    void Display()
    {
        ConstrainPoints();
        // glTranslatef(centerX, centerY, 0.0f);

        // glColor3f(1.0f, 0.0f, 0.0f); // Устанавливаем красный цвет
        // glutSolidSphere(radius, 30, 30);
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
        glTranslatef(posX, posX, 0.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glutSolidSphere(6, 30, 30);  
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
        
    }
};