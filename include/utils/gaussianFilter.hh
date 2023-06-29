#pragma once

#include <algorithm>
#include <numeric>
#include <cstring>
#include <vector>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

void ApplyGaussianFilter(unsigned char *imageData, int width, int height, int gaussianKernelSize, float *gaussianKernel);
void imguiGaussianFilter(unsigned char *data, int width, int height, std::vector<unsigned char*>& filtersStack);