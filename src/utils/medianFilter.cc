#include <thread>
#include <cstring>

#include "medianFilter.hh"

void ApplyMedianFilter(unsigned char* imageData, int width, int height, int kernelSize)
{
    unsigned char* tempImageData = new unsigned char[width * height * 3];

    // Calculate the border size based on the kernel size
    int borderSize = kernelSize / 2;

    auto processRegion = [&](int startY, int endY) {
    // Iterate over each pixel in the image
        for (int y = startY; y < endY; ++y)
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
    };

    // Determine the number of threads based on the available hardware concurrency
    unsigned int numThreads = std::thread::hardware_concurrency();

    // Determine the number of rows each thread will process
    int rowsPerThread = height / numThreads;

    // Create a vector to hold the thread objects
    std::vector<std::thread> threads;

    // Launch threads to process different regions of the image
    int startY = 0;
    int endY = rowsPerThread;
    for (unsigned int i = 0; i < numThreads - 1; ++i)
    {
        threads.emplace_back(processRegion, startY, endY);
        startY = endY;
        endY += rowsPerThread;
    }

    // The last thread will handle the remaining rows, including the remainder if height % numThreads != 0
    threads.emplace_back(processRegion, startY, height);

    for (auto& thread : threads)
    {
        thread.join();
    }

    // Copy the filtered image data back to the original image data array
    std::memcpy(imageData, tempImageData, width * height * 3);

    delete[] tempImageData;
}