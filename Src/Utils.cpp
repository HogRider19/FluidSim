#include<random>
#include "Utils.h"

float constraint(float val, float min, float max)
{
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

float getRandom(float from, float to)
{
    return (float)rand() / (float)RAND_MAX * (to - from) + from;
}

float getDist(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}