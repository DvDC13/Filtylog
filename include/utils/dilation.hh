#pragma once

#include <algorithm>
#include <cmath>

const int structuringElementSize = 3;
const int structuringElement[structuringElementSize][structuringElementSize] =
    {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}};

void ApplyDilation(unsigned char *imageData, int width, int height);