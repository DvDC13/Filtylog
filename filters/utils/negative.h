#pragma once

void ApplyNegative(unsigned char *imageData, int width, int height)
{
    for (int i = 0; i < width * height; ++i)
    {
        unsigned char r = imageData[i * 3];
        unsigned char g = imageData[i * 3 + 1];
        unsigned char b = imageData[i * 3 + 2];

        // Calculate negative value
        unsigned char negativeR = 255 - r;
        unsigned char negativeG = 255 - g;
        unsigned char negativeB = 255 - b;

        // Set negative value to all channels
        imageData[i * 3] = negativeR;
        imageData[i * 3 + 1] = negativeG;
        imageData[i * 3 + 2] = negativeB;
    }
}