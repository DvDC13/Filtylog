#pragma once

#include "grayscale.h"

void ApplyOtsuThreshold(unsigned char* imageData, int width, int height)
{
    ApplyGrayscale(imageData, width, height);

    // Calculate histogram
    int histogram[256] = { 0 };
    for (int i = 0; i < width * height; ++i)
    {
        ++histogram[imageData[i * 3]];
    }

    // Calculate total number of pixels
    int total = width * height;

    // Calculate sum of all pixel values
    float sum = 0;
    for (int i = 0; i < 256; ++i)
    {
        sum += i * histogram[i];
    }

    float sumB = 0;
    int wB = 0;
    int wF = 0;

    float varMax = 0;
    int threshold = 0;

    for (int i = 0; i < 256; ++i)
    {
        wB += histogram[i];
        if (wB == 0)
        {
            continue;
        }

        wF = total - wB;
        if (wF == 0)
        {
            break;
        }

        sumB += static_cast<float>(i * histogram[i]);

        float mB = sumB / wB;
        float mF = (sum - sumB) / wF;

        float varBetween = static_cast<float>(wB) * static_cast<float>(wF) * (mB - mF) * (mB - mF);

        if (varBetween > varMax)
        {
            varMax = varBetween;
            threshold = i;
        }
    }

    for (int i = 0; i < width * height; ++i)
    {
        if (imageData[i * 3] > threshold)
        {
            imageData[i * 3] = 255;
            imageData[i * 3 + 1] = 255;
            imageData[i * 3 + 2] = 255;
        }
        else
        {
            imageData[i * 3] = 0;
            imageData[i * 3 + 1] = 0;
            imageData[i * 3 + 2] = 0;
        }
    }
}