#include "grayscale.hh"

void ApplyGrayscale(unsigned char *imageData, int width, int height)
{
    for (int i = 0; i < width * height; ++i)
    {
        unsigned char r = imageData[i * 3];
        unsigned char g = imageData[i * 3 + 1];
        unsigned char b = imageData[i * 3 + 2];

        // Calculate grayscale value
        unsigned char gray = static_cast<unsigned char>(0.2989 * r + 0.5870 * g + 0.1140 * b);

        // Set grayscale value to all channels
        imageData[i * 3] = gray;
        imageData[i * 3 + 1] = gray;
        imageData[i * 3 + 2] = gray;
    }
}