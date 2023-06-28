#pragma once

#include <cstring>

#include "sobelEdgeDetection.h"
#include "medianFilter.h"
#include "bilateralFilter.h"
#include "quantization.h"
#include "negative.h"
#include "otsuThreshold.h"

void Recombine(unsigned char* imageData, unsigned char* edgeData, int width, int height)
{
    // Iterate over each pixel in the image
    for (int i = 0; i < width * height * 3; ++i)
    {
        // If the pixel belongs to an edge, set it to black (0)
        if (edgeData[i] == 255 && edgeData[i + 1] == 255 && edgeData[i + 2] == 255)
        {
            edgeData[i] = imageData[i];
            edgeData[i + 1] = imageData[i + 1];
            edgeData[i + 2] = imageData[i + 2];
        }
    }
}

void ApplyCartoon(unsigned char* imageData, int width, int height)
{
    unsigned char* copyImageData = new unsigned char[width * height * 3];
    std::memcpy(copyImageData, imageData, width * height * 3);

    ApplyMedianFilter(imageData, width, height, 7);
    ApplySobelEdgeDetection(imageData, width, height);
    ApplyOtsuThreshold(imageData, width, height);
    ApplyNegative(imageData, width, height);

    ApplyBilateralFilter(copyImageData, width, height);
    ApplyMedianFilter(copyImageData, width, height, 7);
    ApplyQuantization(copyImageData, width, height);

    Recombine(copyImageData, imageData, width, height);

    delete[] copyImageData;
}