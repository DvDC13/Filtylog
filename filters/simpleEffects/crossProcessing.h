#pragma once

void ApplyCrossProcessing(unsigned char* imageData, int width, int height)
{
    for (int i = 0; i < width * height; ++i)
    {
        unsigned char r = imageData[i * 3];
        unsigned char g = imageData[i * 3 + 1];
        unsigned char b = imageData[i * 3 + 2];

        // Adjust color channels
        unsigned char adjustedR = r < 128 ? r * 0.8 : r * 1.2;
        unsigned char adjustedG = g < 128 ? g * 0.9 : g * 1.1;
        unsigned char adjustedB = b < 128 ? b * 1.2 : b * 0.8;

        // Clamp channel values to 0-255 range
        adjustedR = adjustedR > 255 ? 255 : adjustedR;
        adjustedG = adjustedG > 255 ? 255 : adjustedG;
        adjustedB = adjustedB > 255 ? 255 : adjustedB;

        // Set adjusted values to image data
        imageData[i * 3] = adjustedR;
        imageData[i * 3 + 1] = adjustedG;
        imageData[i * 3 + 2] = adjustedB;
    }
}