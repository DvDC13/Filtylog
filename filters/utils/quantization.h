#pragma once

#include <iostream>
#include <cmath>

void ApplyQuantization(unsigned char* imageData, int width, int height)
{
    const int factor = 24; // Scale factor for reducing the number of colors
    
    // Iterate over each pixel in the image
    for (int i = 0; i < width * height * 3; ++i)
    {
        // Apply the quantization formula to each color channel
        imageData[i] = static_cast<unsigned char>(std::floor(imageData[i] / factor) * factor);
    }
}
