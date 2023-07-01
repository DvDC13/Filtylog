#include <iostream>
#include <string>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"
#include "ImGuiFileDialog.h"

#include "grayscale.hh"
#include "negative.hh"
#include "sepia.hh"
#include "convolution.hh"
#include "dilation.hh"
#include "erosion.hh"
#include "robertEdgeDetection.hh"
#include "sobelEdgeDetection.hh"
#include "solarisation.hh"
#include "medianCut.hh"
#include "bilateralFilter.hh"
#include "medianFilter.hh"
#include "quantization.hh"
#include "otsuThreshold.hh"
#include "cartoon.hh"
#include "halftone.hh"
#include "colorPencil.hh"
#include "vintage.hh"
#include "vignette.hh"
#include "noise.hh"
#include "sharpen.hh"
#include "crossHatch.hh"
#include "dither.hh"
#include "oilPainting.hh"

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return 1;
    }

    // Create a GLFW window
    GLFWwindow *window = glfwCreateWindow(1400, 800, "Filtylog", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

    // Set the current context to the created window
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    // Setup ImGui for GLFW and OpenGL3
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    std::string filePathName;
    int width, height, channels;
    unsigned char *data = nullptr;
    GLuint texture;

    std::vector<unsigned char *> filtersStack;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start a new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create ImGui window
        ImGui::Begin("Image Processing");

        // open Dialog Simple
        if (ImGui::Button("Choose Image"))
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".jpg", ".");

        // display
        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
        {
            // action if OK
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
                // action
            }

            stbi_image_free(data);

            // close
            ImGuiFileDialog::Instance()->Close();

            data = stbi_load(filePathName.c_str(), &width, &height, &channels, 3);

            filtersStack.clear();
        }

        if (data != nullptr)
        {
            if (texture != 0)
            {
                glDeleteTextures(1, &texture);
                texture = 0;
            }

            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

            ImGui::Image(reinterpret_cast<void *>(static_cast<intptr_t>(texture)), ImVec2(width, height));

            // Create ImGui window
            ImGui::Begin("Filters");

            if (ImGui::Button("Apply Grayscale"))
            {
                ApplyGrayscale(data, width, height);
                unsigned char *filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            if (ImGui::Button("Apply Negative"))
            {
                ApplyNegative(data, width, height);
                unsigned char *filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            if (ImGui::Button("Apply Sepia"))
            {
                ApplySepia(data, width, height);
                unsigned char *filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            if (ImGui::Button("Apply Convolution Filter"))
            {
                ImGui::OpenPopup("Convolution Filter");
            }

            imguiConvolutionFilter(data, width, height, filtersStack);

            if (ImGui::Button("Apply Dilation"))
            {
                ApplyDilation(data, width, height);
                unsigned char *filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            if (ImGui::Button("Apply Erosion"))
            {
                ApplyErosion(data, width, height);
                unsigned char *filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            if (ImGui::Button("Apply Sharpen"))
            {
                ApplySharpen(data, width, height);
                unsigned char *filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            if (ImGui::Button("Apply Solarisation"))
            {
                ApplySolarisation(data, width, height);
                unsigned char *filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            if (ImGui::Button("Apply Median Cut"))
            {
                ApplyMedianCut(data, width, height);
                unsigned char *filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            if (ImGui::Button("Apply Mean Filter"))
            {
                ApplyMedianFilter(data, width, height, 7);
                unsigned char *filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            if (ImGui::Button("Apply Bilateral Filter"))
            {
                ApplyBilateralFilter(data, width, height);
                unsigned char *filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            if (ImGui::Button("Apply Quantization"))
            {
                ApplyQuantization(data, width, height);
                unsigned char *filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            if (ImGui::Button("Apply Otsu Threshold"))
            {
                ApplyOtsuThreshold(data, width, height);
                unsigned char *filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            if (ImGui::Button("Apply Vignette"))
            {
                ApplyVignetteEffect(data, width, height);
                unsigned char* filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            if (ImGui::Button("Apply Noise"))
            {
                ApplyNoise(data, width, height);
                unsigned char* filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);

            }

            // START EDGE DETECTION WINDOW
            // Create ImGui window
            ImGui::Begin("Edge Detection");

            if (ImGui::Button("Apply Robert Edge Detection"))
            {
                ApplyRobertEdgeDetection(data, width, height);
                unsigned char *filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            if (ImGui::Button("Apply Sobel Edge Detection"))
            {
                ApplySobelEdgeDetection(data, width, height);
                unsigned char *filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            ImGui::End();
            // END EDGE DETECTION WINDOW

            // START ARTISTIC FILTERS WINDOW
            // Create ImGui window
            ImGui::Begin("Artistic Filters");

            if (ImGui::Button("Apply Cartoon"))
            {
                ApplyCartoon(data, width, height);
                unsigned char *filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            if (ImGui::Button("Apply Halftone"))
            {
                ImGui::OpenPopup("Halftone");
            }

            imguiHalftone(data, width, height, filtersStack);

            if (ImGui::Button("Apply Pencil Sketch"))
            {
                ApplyColorPencilSketch(data, width, height);
                unsigned char *filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            if (ImGui::Button("Apply Vintage"))
            {
                ApplyVintageFilter(data, width, height);
            if (ImGui::Button("Apply Crosshatch"))
            {
                ApplyCrossHatch(data, width, height);
                unsigned char *filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            if (ImGui::Button("Apply Dither"))
            {
                ApplyDither(data, width, height);
                unsigned char *filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            if (ImGui::Button("Apply Oil Painting"))
            {
                ApplyOilPainting(data, width, height, 3, 5);
                unsigned char *filteredData = new unsigned char[width * height * 3];
                std::memcpy(filteredData, data, width * height * 3);
                filtersStack.push_back(filteredData);
            }

            ImGui::End();
            // END ARTISTIC FILTERS WINDOW

            // START STATE WINDOW
            // Create ImGui window
            ImGui::Begin("State");

            if (ImGui::Button("Undo") && filtersStack.size() > 0)
            {
                stbi_image_free(data);
                if (filtersStack.size() > 1)
                    data = filtersStack[filtersStack.size() - 2];
                else
                    data = stbi_load(filePathName.c_str(), &width, &height, &channels, 3);
                filtersStack.pop_back();
            }

            if (ImGui::Button("Revert"))
            {
                stbi_image_free(data);
                data = stbi_load(filePathName.c_str(), &width, &height, &channels, 3);
                filtersStack.clear();
            }

            ImGui::End();
            // END STATE WINDOW

            ImGui::End();
        }

        ImGui::End();

        // Rendering
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (texture != 0)
        {
            glDeleteTextures(1, &texture);
            texture = 0;
        }

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}