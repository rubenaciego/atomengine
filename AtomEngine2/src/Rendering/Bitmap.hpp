#pragma once

#include <Rendering/Pixel.hpp>

namespace atom
{
    class Bitmap
    {
    private:
        int width;
        int height;
        Pixel* pixels;

    public:
        Bitmap(int width, int height);
        Bitmap(const char* filename);
        ~Bitmap();

        Pixel GetPixel(int x, int y) const;
        void SetPixel(int x, int y, Pixel val);

        int GetWidth() const;
        int GetHeight() const;

        void FlipX();
        void FlipY();
    };
}
