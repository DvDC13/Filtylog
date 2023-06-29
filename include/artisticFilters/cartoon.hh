#pragma once

#include <cstring>

#include "utils/sobelEdgeDetection.hh"
#include "utils/medianFilter.hh"
#include "utils/bilateralFilter.hh"
#include "utils/quantization.hh"
#include "utils/negative.hh"
#include "utils/otsuThreshold.hh"

void Recombine(unsigned char* imageData, unsigned char* edgeData, int width, int height);

void ApplyCartoon(unsigned char* imageData, int width, int height);