#pragma once

const int threshold = 128;

void ApplyThreshold(unsigned char *imageData, int width, int height)
{
    for (int i = 0; i < width * height; ++i)
    {
        unsigned char r = imageData[i * 3];
        unsigned char g = imageData[i * 3 + 1];
        unsigned char b = imageData[i * 3 + 2];

        if (r < threshold)
            r = 0;
        else
            r = 255;

        if (g < threshold)
            g = 0;
        else
            g = 255;

        if (b < threshold)
            b = 0;
        else
            b = 255;

        imageData[i * 3] = r;
        imageData[i * 3 + 1] = g;
        imageData[i * 3 + 2] = b;
    }
}