#include "convolution.hh"

void ApplyConvolutionFilter(unsigned char *imageData, int width, int height, int KernelSize, float *Kernel)
{
    unsigned char *tempImageData = new unsigned char[width * height * 3];

    for (int i = 0; i < width * height; ++i)
    {
        int r = 0, g = 0, b = 0;

        for (int j = 0; j < KernelSize; ++j)
        {
            for (int k = 0; k < KernelSize; ++k)
            {
                int x = i % width + j - KernelSize / 2;
                int y = i / width + k - KernelSize / 2;

                if (x < 0 || x >= width || y < 0 || y >= height)
                    continue;

                r += imageData[(y * width + x) * 3] * Kernel[j * KernelSize + k];
                g += imageData[(y * width + x) * 3 + 1] * Kernel[j * KernelSize + k];
                b += imageData[(y * width + x) * 3 + 2] * Kernel[j * KernelSize + k];
            }
        }

        int rSum = std::accumulate(Kernel, Kernel + KernelSize * KernelSize, 0);
        int gSum = std::accumulate(Kernel, Kernel + KernelSize * KernelSize, 0);
        int bSum = std::accumulate(Kernel, Kernel + KernelSize * KernelSize, 0);

        tempImageData[i * 3] = r / rSum;
        tempImageData[i * 3 + 1] = g / gSum;
        tempImageData[i * 3 + 2] = b / bSum;
    }

    for (int i = 0; i < width * height * 3; ++i)
        imageData[i] = tempImageData[i];

    delete[] tempImageData;
}

void imguiConvolutionFilter(unsigned char *data, int width, int height, std::vector<unsigned char*>& filtersStack)
{
    //  Filter popup window
    if (ImGui::BeginPopupModal("Convolution Filter", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        static int kernelSize = 3;                                   // Default kernel size
        static float *kernel = new float[kernelSize * kernelSize]{}; // Default kernel matrix
        static int prevKernelSize = kernelSize;

        ImGui::Text("Enter Kernel Size:");
        ImGui::InputInt("##KernelSize", &kernelSize);

        // Adapt matrix size
        if (kernelSize != prevKernelSize)
        {
            float *newKernel = new float[kernelSize * kernelSize]{};
            int minSize = std::min(kernelSize, prevKernelSize);

            // Copy existing values
            std::memcpy(newKernel, kernel, minSize * minSize * sizeof(float));

            delete[] kernel;
            kernel = newKernel;
            prevKernelSize = kernelSize;
        }

        ImGui::Text("Enter Kernel Matrix:");

        for (int i = 0; i < kernelSize; i++)
        {
            for (int j = 0; j < kernelSize; j++)
            {
                ImGui::PushID(i * kernelSize + j);
                ImGui::InputFloat("##Value", &kernel[i * kernelSize + j]);
                ImGui::PopID();
                ImGui::SameLine();
            }
            ImGui::NewLine();
        }

        if (ImGui::Button("Apply"))
        {
            ApplyConvolutionFilter(data, width, height, kernelSize, kernel);
            unsigned char *filteredData = new unsigned char[width * height * 3];
            std::memcpy(filteredData, data, width * height * 3);
            filtersStack.push_back(filteredData);
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel"))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}