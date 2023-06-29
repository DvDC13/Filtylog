#include "medianCut.hh"

bool CompareColorsR(Color a, Color b)
{
    return a.r < b.r;
}

bool CompareColorsG(Color a, Color b)
{
    return a.g < b.g;
}

bool CompareColorsB(Color a, Color b)
{
    return a.b < b.b;
}

void medianCutQuantize(unsigned char* imageData, const std::vector<Color>& colorArray, int rAverage, int gAverage, int bAverage, int width)
{
    for (int i = 0; i < colorArray.size(); i++)
    {
        int index = (colorArray[i].rIndex * width + colorArray[i].cIndex) * 3;

        imageData[index] = rAverage;
        imageData[index + 1] = gAverage;
        imageData[index + 2] = bAverage;
    }
}

void splitIntoBuckets(unsigned char* imageData, std::vector<Color>& colorArray, int depth, int width)
{
    if (colorArray.empty()) return;

    if (depth == 0)
    {
        int rSum = 0;
        int gSum = 0;
        int bSum = 0;

        for (int i = 0; i < colorArray.size(); i++)
        {
            rSum += colorArray[i].r;
            gSum += colorArray[i].g;
            bSum += colorArray[i].b;
        }

        int rAverage = rSum / colorArray.size();
        int gAverage = gSum / colorArray.size();
        int bAverage = bSum / colorArray.size();

        medianCutQuantize(imageData, colorArray, rAverage, gAverage, bAverage, width);

        return;
    }

    int rMax = 0;
    int gMax = 0;
    int bMax = 0;

    for (int i = 0; i < colorArray.size(); i++)
    {
        rMax = std::max(rMax, colorArray[i].r);
        gMax = std::max(gMax, colorArray[i].g);
        bMax = std::max(bMax, colorArray[i].b);
    }

    if (rMax > gMax && rMax > bMax)
    {
        std::sort(colorArray.begin(), colorArray.end(), CompareColorsR);
    }
    else if (gMax > rMax && gMax > bMax)
    {
        std::sort(colorArray.begin(), colorArray.end(), CompareColorsG);
    }
    else
    {
        std::sort(colorArray.begin(), colorArray.end(), CompareColorsB);
    }

    int median = (colorArray.size() + 1) / 2;

    std::vector<Color> firstHalf(colorArray.begin(), colorArray.begin() + median);
    std::vector<Color> secondHalf(colorArray.begin() + median, colorArray.end());

    splitIntoBuckets(imageData, firstHalf, depth - 1, width);
    splitIntoBuckets(imageData, secondHalf, depth - 1, width);
}

void ApplyMedianCutRecursive(unsigned char *imageData, int width, int height, int depth)
{
    std::vector<Color> colorArray;
    for (int rIndex = 0; rIndex < height; rIndex++)
    {
        for (int cIndex = 0; cIndex < width; cIndex++)
        {
            int index = (rIndex * width + cIndex) * 3;

            Color color;
            color.r = imageData[index];
            color.g = imageData[index + 1];
            color.b = imageData[index + 2];
            color.rIndex = rIndex;
            color.cIndex = cIndex;
            colorArray.push_back(color);
        }
    }

    splitIntoBuckets(imageData, colorArray, depth, width);
}

void ApplyMedianCut(unsigned char *imageData, int width, int height)
{
    ApplyMedianCutRecursive(imageData, width, height, DEPTH);
}