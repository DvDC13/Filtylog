#pragma once

#include <algorithm>
#include <cmath>

#include "grayscale.hh"

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

void ApplySobelEdgeDetection(unsigned char *imageData, int width, int height);