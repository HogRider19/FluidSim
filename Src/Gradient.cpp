#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include "Utils.h"
#include "Point.h"


class Gradient
{
public:
    void Update(float w, float h, float sr, std::vector<Point>& points)
    {
        smoothingRadius = sr;
        this->points = points;
        this->width = w;
        this->height = h;
    }

    vec2 GetDensityGradient(float posX, float posY, float step = 10)
    {
        float currentDen = GetDensity(posX, posY);
        float dx = GetDensity(posX + step, posY) - currentDen;
        float dy = GetDensity(posX, posY + step) - currentDen;
        return vec2(dx / step, dy / step);
    }

    float GetDensity(float x, float y)
    {
        float den = 0;
        const float mass = 1;

        for (const Point& p : points)
        {
            float d = getDist(x, y, p.X, p.Y);
            float influen = SmoothingVoluem(smoothingRadius, d);
            den += mass * influen;
        }

        return den;
    }

    void DrawSpace(float step = 10, bool drawGradient = false)
    {
        for (float x = 0; x < width; x += step)
        {
            for (float y = 0; y < height; y += step)
            {
                float d = GetDensity(x, y);
                glColor3f(0, 0.0f, d * 1000);
                glPointSize(step);
                glBegin(GL_POINTS);
                glVertex2f(x * 2 / width - 1, y * 2 / height - 1);
                glEnd();

                if (drawGradient)
                {
                    float c = 1000000;
                    vec2 grad = GetDensityGradient(x, y, 0.1);
                    glBegin(GL_LINES);
                    glColor3f(0, 255, 0);
                    glVertex2f(x * 2 / width - 1, y * 2 / height - 1);
                    glColor3f(255, 0, 0);
                    glVertex2f((x + grad.X * c) * 2 / width - 1, (y + grad.Y * c) * 2 / height - 1);
                    glEnd();
                }
            }
        }
    }

private:
    std::vector<Point> points;
    float smoothingRadius = 10;
    float width = 100;
    float height = 100;

    float SmoothingVoluem(float radius, float dist)
    {
        float voluem = M_PI * pow(radius, 8) / 4;
        float val = std::max(0.0f, radius * radius - dist * dist);
        return val * val * val / voluem;
    }

    float SmoothingVoluemDeriv(float radius, float dist)
    {
        if (dist >= radius) return 0;
        float f = radius * radius - dist * dist;
        float scale = -24 / (M_PI * pow(radius, 8));
        return scale * dist * f * f;
    }
};