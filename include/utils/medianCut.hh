#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#define DEPTH 2

struct Color
{
    int r;
    int g;
    int b;
    int rIndex;
    int cIndex;
};

bool CompareColorsR(Color a, Color b);

bool CompareColorsG(Color a, Color b);
bool CompareColorsB(Color a, Color b);

void medianCutQuantize(unsigned char* imageData, const std::vector<Color>& colorArray, int rAverage, int gAverage, int bAverage, int width);
void splitIntoBuckets(unsigned char* imageData, std::vector<Color>& colorArray, int depth, int width);

void ApplyMedianCutRecursive(unsigned char *imageData, int width, int height, int depth);
void ApplyMedianCut(unsigned char *imageData, int width, int height);