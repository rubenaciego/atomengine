#pragma once

#include <cstdint>

namespace atom
{
    struct Pixel
    {
        union
        {
            struct { uint8_t r, g, b, a; };
            uint32_t c;
        };
    };
}
