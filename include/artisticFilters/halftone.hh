#pragma once

#include <iostream>
#include <cstring>
#include <vector>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "utils/otsuThreshold.hh"

void ApplyHalftone(unsigned char *imageData, int width, int height, int dotSize, int dotSpacing, unsigned char dotThreshold);
void imguiHalftone(unsigned char *data, int width, int height, std::vector<unsigned char *> &filtersStack);