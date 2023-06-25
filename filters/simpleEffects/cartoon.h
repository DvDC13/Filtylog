#pragma once

#include "grayscale.h"
#include "gaussianFilter.h"
#include "robertEdgeDetection.h"

void ApplyCartoon(unsigned char *imageData, int width, int height)
{
    ApplyGrayscale(imageData, width, height);
    ApplyGaussianFilter(imageData, width, height);
    ApplyRobertEdgeDetection(imageData, width, height);
}