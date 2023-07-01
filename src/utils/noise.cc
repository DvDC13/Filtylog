#include <random>

#include "noise.hh"

void ApplyNoise(unsigned char* imageData, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width * 3; j += 3)
        {
            int noise = rand() % 20;
            imageData[i * width * 3 + j] = imageData[i * width * 3 + j] * 0.7 + noise;
            imageData[i * width * 3 + j + 1] = imageData[i * width * 3 + j + 1] * 0.7 + noise;
            imageData[i * width * 3 + j + 2] = imageData[i * width * 3 + j + 2] * 0.7 + noise;
        }
    }
}