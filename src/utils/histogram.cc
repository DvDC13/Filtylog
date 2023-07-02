#include "histogram.hh"

void CalculateHistogram(unsigned char *imageData, int width, int height, float *histogram, HistogramType type)
{
    std::memset(histogram, 0, 256 * sizeof(int));

    unsigned char *grayscaleData = new unsigned char[width * height * 3];
    std::memcpy(grayscaleData, imageData, width * height * 3);
    ApplyGrayscale(grayscaleData, width, height);

    for (int i = 0; i < width * height; i++)
    {
        switch (type)
        {
        case HistogramType::Red:
            histogram[imageData[i * 3]]++;
            break;
        case HistogramType::Green:
            histogram[imageData[i * 3 + 1]]++;
            break;
        case HistogramType::Blue:
            histogram[imageData[i * 3 + 2]]++;
            break;
        case HistogramType::Grayscale:
            histogram[grayscaleData[3 * i]]++;
            break;
        }
    }

    delete[] grayscaleData;
}

int CalculateHistogramMax(float *histogram)
{
    int max = 0;
    for (int i = 0; i < 256; i++)
    {
        if (histogram[i] > max)
        {
            max = histogram[i];
        }
    }
    return max;
}

void EqualizeHistogram(unsigned char *data, int width, int height, HistogramType type)
{
    float histogram[256];
    CalculateHistogram(data, width, height, histogram, type);
    float cumulativeHistogram[256];
    cumulativeHistogram[0] = histogram[0];
    for (int i = 1; i < 256; i++)
    {
        cumulativeHistogram[i] = cumulativeHistogram[i - 1] + histogram[i];
    }
    for (int i = 0; i < width * height; i++)
    {
        data[i] = (unsigned char)(cumulativeHistogram[data[i]] * 255.0 / (width * height));
    }
}