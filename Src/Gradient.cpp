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

private:
    float smoothingRadius = 10;
    std::vector<Point> points;
};