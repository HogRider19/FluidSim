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