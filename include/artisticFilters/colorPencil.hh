#pragma once

#include <iostream>

#include "utils/grayscale.hh"
#include "utils/medianFilter.hh"
#include "utils/sobelEdgeDetection.hh"
#include "utils/negative.hh"

void ApplyColorPencilSketch(unsigned char* imageData, int width, int height);