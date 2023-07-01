#include "vignette.hh"

void ApplyVignetteEffect(unsigned char* imageData, int width, int height)
{
    for (int i = 0; i < width * height * 3; i++)
    {
        double radius = sqrt(pow(width / 2, 2) + pow(height / 2, 2));
        double distance = sqrt(pow((i % (width * 3) / 3) - width / 2, 2) + pow((i / (width * 3)) - height / 2, 2));
        double vignette_factor = 1.0 - (distance / radius);
        imageData[i] *= vignette_factor;

        imageData[i] = imageData[i] < 0 ? 0 : (imageData[i] > 255 ? 255 : imageData[i]);
    }
}