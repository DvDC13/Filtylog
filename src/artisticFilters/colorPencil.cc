#include "colorPencil.hh"

void ApplyColorPencilSketch(unsigned char* imageData, int width, int height)
{
    unsigned char* originalImageData = new unsigned char[width * height * 3];
    std::memcpy(originalImageData, imageData, width * height * 3);

    unsigned char* sketchedImageData = new unsigned char[width * height * 3];
    std::memcpy(sketchedImageData, imageData, width * height * 3);

    ApplyGrayscale(sketchedImageData, width, height);
    ApplyMedianFilter(sketchedImageData, width, height, 3);
    ApplySobelEdgeDetection(sketchedImageData, width, height);
    ApplyNegative(sketchedImageData, width, height);

    unsigned char* resultImageData = new unsigned char[width * height * 3];

    for (int i = 0; i < width * height * 3; i++)
    {
        resultImageData[i] = originalImageData[i] * 0.5 + sketchedImageData[i] * 0.5;
    }

    std::memcpy(imageData, resultImageData, width * height * 3);

    delete[] originalImageData;
    delete[] resultImageData;
}