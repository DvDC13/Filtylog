#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

void ApplyMedianFilter(unsigned char* imageData, int width, int height, int kernelSize)
{
    unsigned char* tempImageData = new unsigned char[width * height * 3];

    // Calculate the border size based on the kernel size
    int borderSize = kernelSize / 2;

    // Iterate over each pixel in the image
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // Collect pixel values within the kernel for each color channel
            std::vector<unsigned char> redValues;
            std::vector<unsigned char> greenValues;
            std::vector<unsigned char> blueValues;

            // Iterate over the kernel area
            for (int ky = -borderSize; ky <= borderSize; ++ky)
            {
                for (int kx = -borderSize; kx <= borderSize; ++kx)
                {
                    // Calculate the coordinates of the neighboring pixel
                    int nx = x + kx;
                    int ny = y + ky;

                    // Check if the neighboring pixel is within the image boundaries
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                    {
                        // Get the pixel values for each color channel and add them to the collections
                        unsigned char redValue = imageData[(ny * width + nx) * 3];
                        unsigned char greenValue = imageData[(ny * width + nx) * 3 + 1];
                        unsigned char blueValue = imageData[(ny * width + nx) * 3 + 2];

                        redValues.push_back(redValue);
                        greenValues.push_back(greenValue);
                        blueValues.push_back(blueValue);
                    }
                }
            }

            // Sort the pixel values for each color channel
            std::sort(redValues.begin(), redValues.end());
            std::sort(greenValues.begin(), greenValues.end());
            std::sort(blueValues.begin(), blueValues.end());

            // Get the median values for each color channel
            unsigned char medianRedValue = redValues[redValues.size() / 2];
            unsigned char medianGreenValue = greenValues[greenValues.size() / 2];
            unsigned char medianBlueValue = blueValues[blueValues.size() / 2];

            // Assign the median values to the filtered pixel
            tempImageData[(y * width + x) * 3] = medianRedValue;
            tempImageData[(y * width + x) * 3 + 1] = medianGreenValue;
            tempImageData[(y * width + x) * 3 + 2] = medianBlueValue;
        }
    }

    // Copy the filtered image data back to the original image data array
    std::memcpy(imageData, tempImageData, width * height * 3);

    delete[] tempImageData;
}