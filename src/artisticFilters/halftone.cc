#include "halftone.hh"

void ApplyHalftone(unsigned char *imageData, int width, int height, int dotSize, int dotSpacing, unsigned char dotThreshold)
{
    // Iterate over each pixel in the image
    for (int y = 0; y < height; y += dotSpacing)
    {
        for (int x = 0; x < width; x += dotSpacing)
        {
            // Calculate the average RGB values within the dot region
            unsigned int totalR = 0, totalG = 0, totalB = 0;
            int count = 0;

            for (int dy = 0; dy < dotSize; ++dy)
            {
                for (int dx = 0; dx < dotSize; ++dx)
                {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx < width && ny < height)
                    {
                        totalR += imageData[(ny * width + nx) * 3];
                        totalG += imageData[(ny * width + nx) * 3 + 1];
                        totalB += imageData[(ny * width + nx) * 3 + 2];
                        ++count;
                    }
                }
            }

            unsigned char averageR = totalR / count;
            unsigned char averageG = totalG / count;
            unsigned char averageB = totalB / count;

            // Determine whether to draw a dot or not based on the average RGB values
            unsigned char dotValue = ((averageR + averageG + averageB) / 3 >= dotThreshold) ? 255 : 0;

            // Set the dot color for the dot region
            for (int dy = 0; dy < dotSize; ++dy)
            {
                for (int dx = 0; dx < dotSize; ++dx)
                {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx < width && ny < height)
                    {
                        imageData[(ny * width + nx) * 3] = dotValue;
                        imageData[(ny * width + nx) * 3 + 1] = dotValue;
                        imageData[(ny * width + nx) * 3 + 2] = dotValue;
                    }
                }
            }
        }
    }
}

void imguiHalftone(unsigned char *data, int width, int height, std::vector<unsigned char *> &filtersStack)
{
    if (ImGui::BeginPopupModal("Halftone", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        static int dotSize = 4;
        static int dotSpacing = 8;
        static int dotThreshold = 128;

        ImGui::SliderInt("Dot size", &dotSize, 1, 20);
        ImGui::SliderInt("Dot spacing", &dotSpacing, 1, 20);
        ImGui::SliderInt("Dot threshold", &dotThreshold, 0, 255);

        if (ImGui::Button("Apply"))
        {
            ApplyHalftone(data, width, height, dotSize, dotSpacing, dotThreshold);
            unsigned char *filteredData = new unsigned char[width * height * 3];
            std::memcpy(filteredData, data, width * height * 3);
            filtersStack.push_back(filteredData);
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}