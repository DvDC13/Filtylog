#pragma once

#include <cmath>

#include "grayscale.h"

const int robertKernelSize = 2;
const int robertKernel1[robertKernelSize][robertKernelSize] = 
{
    { 1,  0 },
    { 0, -1 }
};

const int robertKernel2[robertKernelSize][robertKernelSize] = 
{
    { 0,  1 },
    { -1, 0 }
};

void ApplyRobertEdgeDetection(unsigned char *imageData, int width, int height)
{
    ApplyGrayscale(imageData, width, height);

    unsigned char *tempImageData = new unsigned char[width * height * 3];

    for (int i = 0; i < width * height; ++i)
    {
        int r1 = 0, g1 = 0, b1 = 0;
        int r2 = 0, g2 = 0, b2 = 0;

        for (int j = 0; j < robertKernelSize; ++j)
        {
            for (int k = 0; k < robertKernelSize; ++k)
            {
                int x = i % width + j - robertKernelSize / 2;
                int y = i / width + k - robertKernelSize / 2;

                if (x < 0 || x >= width || y < 0 || y >= height) continue;

                r1 += imageData[(y * width + x) * 3] * robertKernel1[j][k];
                g1 += imageData[(y * width + x) * 3 + 1] * robertKernel1[j][k];
                b1 += imageData[(y * width + x) * 3 + 2] * robertKernel1[j][k];

                r2 += imageData[(y * width + x) * 3] * robertKernel2[j][k];
                g2 += imageData[(y * width + x) * 3 + 1] * robertKernel2[j][k];
                b2 += imageData[(y * width + x) * 3 + 2] * robertKernel2[j][k];
            }
        }

        int r = std::sqrt(r1 * r1 + r2 * r2);
        int g = std::sqrt(g1 * g1 + g2 * g2);
        int b = std::sqrt(b1 * b1 + b2 * b2);

        tempImageData[i * 3] = r > 255 ? 255 : r;
        tempImageData[i * 3 + 1] = g > 255 ? 255 : g;
        tempImageData[i * 3 + 2] = b > 255 ? 255 : b;
    }

    for (int i = 0; i < width * height * 3; ++i) imageData[i] = tempImageData[i];

    delete[] tempImageData;
}