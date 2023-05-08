#include "Bitmap.hpp"
#include <stb_image/stb_image.h>

namespace atom
{
    Bitmap::Bitmap(int width, int height)
    {
        this->width = width;
        this->height = height;
        pixels = new Pixel[width * height];
    }

    Bitmap::Bitmap(const char* filename)
    {
        int numComponents;
        pixels = (Pixel*)stbi_load(filename, &width, &height, &numComponents, 4);
    }

    Bitmap::~Bitmap()
    {
        delete pixels;
    }

    Pixel Bitmap::GetPixel(int x, int y) const
    {
        return pixels[x + y * width];
    }

    void Bitmap::SetPixel(int x, int y, Pixel val)
    {
        pixels[x + y * width] = val;
    }

    int Bitmap::GetWidth() const
    {
        return width;
    }
    
    int Bitmap::GetHeight() const
    {
        return height;
    }

    void Bitmap::FlipX()
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width / 2; x++)
            {
                Pixel prev = pixels[x + y * width];
                Pixel n = pixels[width - 1 - x + y * width];

                pixels[x + y * width] = n;
                pixels[width - 1 - x + y * width] = prev;
            }
        }
    }

    void Bitmap::FlipY()
    {
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height / 2; y++)
            {
                Pixel prev = pixels[x + y * width];
                Pixel n = pixels[x + (height - 1 - y) * width];

                pixels[x + y * width] = n;
                pixels[x + (height - 1 - y) * width] = prev;
            }
        }
    }
}
