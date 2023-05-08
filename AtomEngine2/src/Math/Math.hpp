#pragma once

#include <cmath>

#define ToRadians(x) (float)(((x) * (float)M_PI / 180.0f))
#define ToDegrees(x) (float)(((x) * 180.0f / (float)M_PI))

namespace atom
{
    template<typename T>
    inline T Clamp(const T &a, const T &min, const T &max)
    {
        if (a < min) return min;
        else if (a > max) return max; 
        else return a;
    }
}
