#include "sharpen.hh"

void ApplySharpen(unsigned char *imageData, int width, int height)
{
    float smoothKernel[9] = {
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    };

    unsigned char *originalImageData = new unsigned char[width * height * 3];
    std::memcpy(originalImageData, imageData, width * height * 3);

    unsigned char* smoothImageData = new unsigned char[width * height * 3];
    std::memcpy(smoothImageData, imageData, width * height * 3);

    ApplyConvolutionFilter(smoothImageData, width, height, 3, smoothKernel);

    unsigned char* detailImageData = new unsigned char[width * height * 3];

    for (int i = 0; i < width * height * 3; ++i)
    {
        int diff = originalImageData[i] - smoothImageData[i];
        detailImageData[i] = diff < 0 ? 0 : (diff > 255 ? 255 : diff);
    }

    for (int i = 0; i < width * height * 3; ++i)
    {
        int sum = originalImageData[i] + detailImageData[i];
        imageData[i] = sum < 0 ? 0 : (sum > 255 ? 255 : sum);
    }

    delete[] smoothImageData;
    delete[] detailImageData;
    delete[] originalImageData;
}