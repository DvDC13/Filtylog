#include "vintage.hh"

void ApplyVintageFilter(unsigned char* imageData, int width, int height)
{
    ApplyNoise(imageData, width, height);
    ApplySepia(imageData, width, height);
    ApplyVignetteEffect(imageData, width, height);
}