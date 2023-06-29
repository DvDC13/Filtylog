#pragma once

#include <cmath>

#include "grayscale.hh"

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

void ApplyRobertEdgeDetection(unsigned char *imageData, int width, int height);