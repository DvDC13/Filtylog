#pragma once

#include <algorithm>
#include <cmath>

#include "grayscale.h"

const int sobelKernelSize = 3;
const int sobelKernelX[sobelKernelSize][sobelKernelSize] =
{
    { -1,  0,  1 },
    { -2,  0,  2 },
    { -1,  0,  1 }
};

const int sobelKernelY[sobelKernelSize][sobelKernelSize] =
{
    { -1, -2, -1 },
    {  0,  0,  0 },
    {  1,  2,  1 }
};

void ApplySobelEdgeDetection(unsigned char *imageData, int width, int height)
{
    ApplyGrayscale(imageData, width, height);

    unsigned char *tempImageData = new unsigned char[width * height * 3];

    for (int i = 0; i < width * height; ++i)
    {
        int rX = 0, gX = 0, bX = 0;
        int rY = 0, gY = 0, bY = 0;

        for (int j = 0; j < sobelKernelSize; ++j)
        {
            for (int k = 0; k < sobelKernelSize; ++k)
            {
                int x = i % width + j - sobelKernelSize / 2;
                int y = i / width + k - sobelKernelSize / 2;

                if (x < 0 || x >= width || y < 0 || y >= height) continue;

                rX += imageData[(y * width + x) * 3] * sobelKernelX[j][k];
                gX += imageData[(y * width + x) * 3 + 1] * sobelKernelX[j][k];
                bX += imageData[(y * width + x) * 3 + 2] * sobelKernelX[j][k];

                rY += imageData[(y * width + x) * 3] * sobelKernelY[j][k];
                gY += imageData[(y * width + x) * 3 + 1] * sobelKernelY[j][k];
                bY += imageData[(y * width + x) * 3 + 2] * sobelKernelY[j][k];
            }
        }

        int r = std::min(255, static_cast<int>(sqrt(rX * rX + rY * rY)));
        int g = std::min(255, static_cast<int>(sqrt(gX * gX + gY * gY)));
        int b = std::min(255, static_cast<int>(sqrt(bX * bX + bY * bY)));

        tempImageData[i * 3] = r;
        tempImageData[i * 3 + 1] = g;
        tempImageData[i * 3 + 2] = b;
    }

    for (int i = 0; i < width * height * 3; ++i) imageData[i] = tempImageData[i];

    delete[] tempImageData;
}