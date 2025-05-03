#pragma once 
#include <inttypes.h>

namespace ShadowPlay
{
    struct SPRect
    {
        int32_t x, y, width, height;
        SPRect(int32_t x, int32_t y, int32_t width, int32_t height) : x(x), y(y), width(width), height(height) {}
        SPRect() : x(0), y(0), width(0), height(0) {}
        SPRect(const SPRect& other) : x(other.x), y(other.y), width(other.width), height(other.height) {}
        SPRect& operator=(const SPRect& other)
        {
            if (this != &other)
            {
                x = other.x;
                y = other.y;
                width = other.width;
                height = other.height;
            }
            return *this;
        }
    };
}