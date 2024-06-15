#include <GL/glut.h>
#include <stdio.h>
#include <vector>
#include <cmath>
#include "Utils.h"
#include "Point.h"


class Gradient
{
public:
    void Update(float w, float h, std::vector<Point>& points)
    {
        smoothingRadius = std::min(w, h) / 5;
        this->points = points;
        this->width = w;
        this->height = h;
    }

    void GetAt(float posX, float posY, float& resX, float& resY)
    {
        float step = 10;
        float currentDen = GetDensity(posX, posY);
        resX = currentDen - GetDensity(posX + step, posY);
        resY = currentDen - GetDensity(posX, posY + step);
    }

    float GetDensity(float x, float y)
    {
        float den = 0;
        for (Point p : points)
        {
            float d = getDist(x, y, p.X, p.Y);
            if (d <= 3) continue;
            if (d <= smoothingRadius)
                den += 1 / d;
        }
        return den;
    }

    void DrawSpace(float step = 10)
    {
        for (float x = 0; x < width; x += step)
        {
            for (float y = 0; y < height; y += step)
            {
                float d = GetDensity(x, y);
                glColor3f(0, 0.0f, d);
                glPointSize(step);
                glBegin(GL_POINTS);
                glVertex2f(x * 2 / width - 1, y * 2 / height - 1);
                glEnd();

                float gx; float gy;
                GetAt(x, y, gx, gy);
                float c = 200;
                gx *= c; gy *= c;

                // glColor3f(255, 0.0f, 0);
                // glBegin(GL_LINES);
                // glVertex2f(x * 2 / width - 1, y * 2 / height - 1);
                // glVertex2f((x + gx) * 2 / width - 1, (y + gy) * 2 / height - 1);
                // glEnd();
            }
        }
    }

private:
    float smoothingRadius = 10;
    std::vector<Point> points;
    float width = 100;
    float height = 100;
};