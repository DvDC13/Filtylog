#include "oilPainting.hh"

void ApplyOilPainting(unsigned char* imageData, int width, int height, int brushSize, int intensity)
{
    // Create a temporary buffer to store the modified image
    unsigned char* modifiedData = new unsigned char[3 * width * height];
    std::memcpy(modifiedData, imageData, 3 * width * height);

    // Iterate over each pixel in the image
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // Calculate the color histogram for the pixels within the brush area
            int histogramR[256] = { 0 };
            int histogramG[256] = { 0 };
            int histogramB[256] = { 0 };

            for (int dy = -brushSize; dy <= brushSize; ++dy)
            {
                for (int dx = -brushSize; dx <= brushSize; ++dx)
                {
                    int offsetX = x + dx;
                    int offsetY = y + dy;

                    // Check if the offset pixel is within the image bounds
                    if (offsetX >= 0 && offsetX < width && offsetY >= 0 && offsetY < height)
                    {
                        // Get the color of the offset pixel
                        unsigned char r = imageData[3 * (offsetY * width + offsetX)];
                        unsigned char g = imageData[3 * (offsetY * width + offsetX) + 1];
                        unsigned char b = imageData[3 * (offsetY * width + offsetX) + 2];

                        // Increment the corresponding histogram bin
                        histogramR[r]++;
                        histogramG[g]++;
                        histogramB[b]++;
                    }
                }
            }

            // Find the most frequent color in the histogram
            int maxFrequency = 0;
            int dominantR = 0, dominantG = 0, dominantB = 0;

            for (int i = 0; i < 256; ++i)
            {
                if (histogramR[i] > maxFrequency)
                {
                    maxFrequency = histogramR[i];
                    dominantR = i;
                }

                if (histogramG[i] > maxFrequency)
                {
                    maxFrequency = histogramG[i];
                    dominantG = i;
                }

                if (histogramB[i] > maxFrequency)
                {
                    maxFrequency = histogramB[i];
                    dominantB = i;
                }
            }

            // Set the color of the current pixel to the dominant color
            modifiedData[3 * (y * width + x)] = dominantR;
            modifiedData[3 * (y * width + x) + 1] = dominantG;
            modifiedData[3 * (y * width + x) + 2] = dominantB;
        }
    }

    // Apply intensity to the modified image by blending it with the original image
    float blendFactor = intensity / 100.0f;

    for (int i = 0; i < 3 * width * height; ++i)
    {
        modifiedData[i] = static_cast<unsigned char>((blendFactor * modifiedData[i]) + ((1.0f - blendFactor) * imageData[i]));
    }

    // Copy the modified data back to the original image data
    std::memcpy(imageData, modifiedData, 3 * width * height);

    // Clean up the temporary buffer
    delete[] modifiedData;
}