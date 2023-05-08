#pragma once

#include <Math/Matrix4.hpp>

namespace atom
{
    class ShadowInfo
    {
    public:
        ShadowInfo(bool castShadow = true) : castShadows(castShadow) {}

        bool castShadows;
        Matrix4 projection;
    };
}
