#include <cstring>
#include <cmath>
#include <iostream>

#include "morphe.hh"

// // Function to calculate the squared difference between two RGB colors
// double colorDifference(const unsigned char* color1, const unsigned char* color2) {
//     double diffR = color1[0] - color2[0];
//     double diffG = color1[1] - color2[1];
//     double diffB = color1[2] - color2[2];
//     return diffR * diffR + diffG * diffG + diffB * diffB;
// }

// void ApplyMorphe(unsigned char* imageData, int width, int height,
//                     unsigned char* styleImage, int width2, int height2)
// {
//     if (width != width2 || height != height2)
//     {
//         // call resize here
//         std::cout << "Error: Images must be the same size" << std::endl;
//         return;
//     }

//     // apply style transfer
//     unsigned char avgColor[3] = {0, 0, 0};
//     for (int i = 0; i < width * height; i++)
//     {
//         avgColor[0] += styleImage[i * 3];
//         avgColor[1] += styleImage[i * 3 + 1];
//         avgColor[2] += styleImage[i * 3 + 2];
//     }

//     avgColor[0] /= width * height;
//     avgColor[1] /= width * height;
//     avgColor[2] /= width * height;

//     // Transfer the texture from the style image to the content image
//     for (int i = 0; i < width * height; i++) {
//         double diffContent = colorDifference(imageData + i * 3, avgColor);
//         double diffStyle = colorDifference(styleImage + i * 3, avgColor);

//         // Adjust the pixel color based on the texture transfer
//         for (int c = 0; c < 3; c++) {
//             double transfer = (imageData[i * 3 + c] - avgColor[c]) * sqrt(diffStyle / diffContent);
//             imageData[i * 3 + c] = static_cast<unsigned char>(std::round(avgColor[c] + transfer));
//         }
//     }
// }

void ApplyMorphe(unsigned char* imageData, int width, int height,
                     unsigned char* styleImage, int width2, int height2)
{
    int numFrames = 10;
    float stepSize = 1.0f / numFrames;
    int bufferSize = width * height * 3;

    unsigned char* morphedImage = new unsigned char[bufferSize];

    for (int step = 0; step <= numFrames; step++)
    {
        float interpolationFactor = step * stepSize;

        for (int i = 0; i < bufferSize; i += 3)
        {
            int srcIndex = i;
            int targetIndex = i;

            unsigned char r = (1 - interpolationFactor) * imageData[srcIndex] + interpolationFactor * styleImage[targetIndex];
            unsigned char g = (1 - interpolationFactor) * imageData[srcIndex + 1] + interpolationFactor * styleImage[targetIndex + 1];
            unsigned char b = (1 - interpolationFactor) * imageData[srcIndex + 2] + interpolationFactor * styleImage[targetIndex + 2];

            morphedImage[i] = r;
            morphedImage[i + 1] = g;
            morphedImage[i + 2] = b;
        }

        std::memcpy(imageData, morphedImage, bufferSize);
    }

    delete[] morphedImage;
}