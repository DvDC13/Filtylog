#pragma once

#include <cmath>

void ApplyBilateralFilter(unsigned char* imageData, int width, int height)
{
    unsigned char* tempImageData = new unsigned char[width * height * 3];
    
    // Set the parameters for the bilateral filter
    float spatialSigma = 5.0f; // Spatial standard deviation
    float intensitySigma = 30.0f; // Intensity standard deviation
    
    // Iterate over each pixel in the image
    for (int i = 0; i < width * height; ++i)
    {
        int r = 0, g = 0, b = 0;
        float weightSum = 0.0f;
        
        // Get the coordinates of the current pixel
        int x = i % width;
        int y = i / width;
        
        // Iterate over the neighboring pixels
        for (int j = -1; j <= 1; ++j)
        {
            for (int k = -1; k <= 1; ++k)
            {
                // Calculate the coordinates of the neighboring pixel
                int nx = x + j;
                int ny = y + k;
                
                // Check if the neighboring pixel is within the image boundaries
                if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                {
                    // Calculate the spatial distance between pixels
                    float spatialDistance = sqrtf(static_cast<float>(j * j + k * k));
                    
                    // Calculate the intensity difference between pixels
                    float intensityDifference = static_cast<float>(imageData[i * 3]) - static_cast<float>(imageData[(ny * width + nx) * 3]);
                    
                    // Calculate the weight for the neighboring pixel
                    float spatialWeight = expf(-(spatialDistance * spatialDistance) / (2.0f * spatialSigma * spatialSigma));
                    float intensityWeight = expf(-(intensityDifference * intensityDifference) / (2.0f * intensitySigma * intensitySigma));
                    
                    // Calculate the weighted sum of pixel values
                    r += imageData[(ny * width + nx) * 3] * spatialWeight * intensityWeight;
                    g += imageData[(ny * width + nx) * 3 + 1] * spatialWeight * intensityWeight;
                    b += imageData[(ny * width + nx) * 3 + 2] * spatialWeight * intensityWeight;
                    
                    // Accumulate the weight sum
                    weightSum += spatialWeight * intensityWeight;
                }
            }
        }
        
        // Normalize the weighted sum and assign it to the filtered pixel
        tempImageData[i * 3] = static_cast<unsigned char>(r / weightSum);
        tempImageData[i * 3 + 1] = static_cast<unsigned char>(g / weightSum);
        tempImageData[i * 3 + 2] = static_cast<unsigned char>(b / weightSum);
    }
    
    // Copy the filtered image data back to the original image data array
    for (int i = 0; i < width * height * 3; ++i)
        imageData[i] = tempImageData[i];
    
    delete[] tempImageData;
}
