#include "dither.hh"

void ApplyDither(unsigned char* imageData, int width, int height)
{
    // Convert the image to grayscale
    ApplyGrayscale(imageData, width, height);

    // Iterate over each pixel in the image
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int index = 3 * (y * width + x);

            unsigned char oldR = imageData[index];
            unsigned char oldG = imageData[index + 1];
            unsigned char oldB = imageData[index + 2];

            int factor = 4;
            unsigned char newR = static_cast<unsigned char>(std::round(factor * oldR / 255.0) * (255.0 / factor));
            unsigned char newG = static_cast<unsigned char>(std::round(factor * oldG / 255.0) * (255.0 / factor));
            unsigned char newB = static_cast<unsigned char>(std::round(factor * oldB / 255.0) * (255.0 / factor));

            imageData[index] = newR;
            imageData[index + 1] = newG;
            imageData[index + 2] = newB;

            int errorR = oldR - newR;
            int errorG = oldG - newG;
            int errorB = oldB - newB;

            // Distribute the error to the neighboring pixels
            if (x + 1 < width)
            {
                imageData[index + 3] += static_cast<unsigned char>(errorR * 7.0 / 16.0);
                imageData[index + 4] += static_cast<unsigned char>(errorG * 7.0 / 16.0);
                imageData[index + 5] += static_cast<unsigned char>(errorB * 7.0 / 16.0);
            }

            if (x - 1 >= 0 && y + 1 < height)
            {
                imageData[index + 3 * width - 3] += static_cast<unsigned char>(errorR * 3.0 / 16.0);
                imageData[index + 3 * width - 2] += static_cast<unsigned char>(errorG * 3.0 / 16.0);
                imageData[index + 3 * width - 1] += static_cast<unsigned char>(errorB * 3.0 / 16.0);
            }

            if (y + 1 < height)
            {
                imageData[index + 3 * width] += static_cast<unsigned char>(errorR * 5.0 / 16.0);
                imageData[index + 3 * width + 1] += static_cast<unsigned char>(errorG * 5.0 / 16.0);
                imageData[index + 3 * width + 2] += static_cast<unsigned char>(errorB * 5.0 / 16.0);
            }

            if (x + 1 < width && y + 1 < height)
            {
                imageData[index + 3 * width + 3] += static_cast<unsigned char>(errorR * 1.0 / 16.0);
                imageData[index + 3 * width + 4] += static_cast<unsigned char>(errorG * 1.0 / 16.0);
                imageData[index + 3 * width + 5] += static_cast<unsigned char>(errorB * 1.0 / 16.0);
            }
        }
    }
}