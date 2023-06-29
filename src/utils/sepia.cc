#include "sepia.hh"

void ApplySepia(unsigned char *imageData, int width, int height)
{
    for (int i = 0; i < width * height; ++i)
    {
        unsigned char r = imageData[i * 3];
        unsigned char g = imageData[i * 3 + 1];
        unsigned char b = imageData[i * 3 + 2];

        float sepiaR = 0.393 * r + 0.769 * g + 0.189 * b;
        float sepiaG = 0.349 * r + 0.686 * g + 0.168 * b;
        float sepiaB = 0.272 * r + 0.534 * g + 0.131 * b;

        // Calculate sepia value
        unsigned char R = static_cast<unsigned char>(std::min(255.0f, sepiaR));
        unsigned char G = static_cast<unsigned char>(std::min(255.0f, sepiaG));
        unsigned char B = static_cast<unsigned char>(std::min(255.0f, sepiaB));

        // Set sepia value to all channels
        imageData[i * 3] = R;
        imageData[i * 3 + 1] = G;
        imageData[i * 3 + 2] = B;
    }
}