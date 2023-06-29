#include "dilation.hh"

void ApplyDilation(unsigned char *imageData, int width, int height)
{
    unsigned char *tempImageData = new unsigned char[width * height * 3];

    for (int i = 0; i < width * height; ++i)
    {
        int r = 0, g = 0, b = 0;

        for (int j = 0; j < structuringElementSize; ++j)
        {
            for (int k = 0; k < structuringElementSize; ++k)
            {
                int x = i % width + j - structuringElementSize / 2;
                int y = i / width + k - structuringElementSize / 2;

                if (x < 0 || x >= width || y < 0 || y >= height)
                    continue;

                r = std::max(r, imageData[(y * width + x) * 3] * structuringElement[j][k]);
                g = std::max(g, imageData[(y * width + x) * 3 + 1] * structuringElement[j][k]);
                b = std::max(b, imageData[(y * width + x) * 3 + 2] * structuringElement[j][k]);
            }
        }

        tempImageData[i * 3] = r;
        tempImageData[i * 3 + 1] = g;
        tempImageData[i * 3 + 2] = b;
    }

    for (int i = 0; i < width * height * 3; ++i)
        imageData[i] = tempImageData[i];

    delete[] tempImageData;
}