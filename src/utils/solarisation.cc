#include "solarisation.hh"

void ApplySolarisation(unsigned char *imageData, int width, int height)
{
    const int midIntensity = 128;
    const float intensityScale = 2.0;

    for (int i = 0; i < width * height; ++i)
    {
        unsigned char r = imageData[i * 3];
        unsigned char g = imageData[i * 3 + 1];
        unsigned char b = imageData[i * 3 + 2];

        // Calculate solarisation value using sine function
        unsigned char solarizedR = r < midIntensity ? r * intensityScale : (255 - r) * intensityScale;
        unsigned char solarizedG = g < midIntensity ? g * intensityScale : (255 - g) * intensityScale;
        unsigned char solarizedB = b < midIntensity ? b * intensityScale : (255 - b) * intensityScale;

        // Set solarisation value to all channels
        imageData[i * 3] = solarizedR;
        imageData[i * 3 + 1] = solarizedG;
        imageData[i * 3 + 2] = solarizedB;
    }
}