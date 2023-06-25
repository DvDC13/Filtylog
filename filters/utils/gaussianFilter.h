#pragma once

#include <algorithm>

const int gaussianKernelSize = 5;
const int gaussianKernel[gaussianKernelSize][gaussianKernelSize] = 
{
    { 1,  4,  7,  4, 1 },
    { 4, 16, 26, 16, 4 },
    { 7, 26, 41, 26, 7 },
    { 4, 16, 26, 16, 4 },
    { 1,  4,  7,  4, 1 }
};

void ApplyGaussianFilter(unsigned char *imageData, int width, int height)
{
    unsigned char *tempImageData = new unsigned char[width * height * 3];

    for (int i = 0; i < width * height; ++i)
    {
        int r = 0, g = 0, b = 0;

        for (int j = 0; j < gaussianKernelSize; ++j)
        {
            for (int k = 0; k < gaussianKernelSize; ++k)
            {
                int x = i % width + j - gaussianKernelSize / 2;
                int y = i / width + k - gaussianKernelSize / 2;

                if (x < 0 || x >= width || y < 0 || y >= height) continue;

                r += imageData[(y * width + x) * 3] * gaussianKernel[j][k];
                g += imageData[(y * width + x) * 3 + 1] * gaussianKernel[j][k];
                b += imageData[(y * width + x) * 3 + 2] * gaussianKernel[j][k];
            }
        }

        tempImageData[i * 3] = r / 273;
        tempImageData[i * 3 + 1] = g / 273;
        tempImageData[i * 3 + 2] = b / 273;
    }

    for (int i = 0; i < width * height * 3; ++i) imageData[i] = tempImageData[i];

    delete[] tempImageData;
}