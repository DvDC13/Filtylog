#pragma once

#include <cstring>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "grayscale.hh"

enum class HistogramType
{
    Red,
    Green,
    Blue,
    Grayscale
};

void CalculateHistogram(unsigned char* imageData, int width, int height, float* histogram, HistogramType type);

int CalculateHistogramMax(float* histogram);

void EqualizeHistogram(unsigned char* imageData, int width, int height);