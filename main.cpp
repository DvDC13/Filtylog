#include <iostream>
#include <string>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"
#include "ImGuiFileDialog.h"

#include "grayscale.h"
#include "negative.h"
#include "sepia.h"
#include "gaussianFilter.h"
#include "dilation.h"
#include "erosion.h"
#include "robertEdgeDetection.h"
#include "sobelEdgeDetection.h"
#include "threshold.h"
#include "solarisation.h"
#include "crossProcessing.h"

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return 1;
    }

    // Create a GLFW window
    GLFWwindow *window = glfwCreateWindow(1280, 720, "Filtylog", nullptr, nullptr);
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
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".png", ".");

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

            if (ImGui::Button("Apply Grayscale"))
            {
                ApplyGrayscale(data, width, height);
            }

            if (ImGui::Button("Apply Negative"))
            {
                ApplyNegative(data, width, height);
            }

            if (ImGui::Button("Apply Sepia"))
            {
                ApplySepia(data, width, height);
            }

            if (ImGui::Button("Apply Gaussian Filter"))
            {
                ApplyGaussianFilter(data, width, height);
            }

            if (ImGui::Button("Apply Robert Edge Detection"))
            {
                ApplyRobertEdgeDetection(data, width, height);
            }

            if (ImGui::Button("Apply Sobel Edge Detection"))
            {
                ApplySobelEdgeDetection(data, width, height);
            }

            if (ImGui::Button("Apply Dilation"))
            {
                ApplyDilation(data, width, height);
            }

            if (ImGui::Button("Apply Erosion"))
            {
                ApplyErosion(data, width, height);
            }

            if (ImGui::Button("Apply Solarisation"))
            {
                ApplySolarisation(data, width, height);
            }

            if (ImGui::Button("Apply Cross Processing"))
            {
                ApplyCrossProcessing(data, width, height);
            }

            if (ImGui::Button("Apply Threshold"))
            {
                ApplyThreshold(data, width, height);
            }

            if (ImGui::Button("Revert"))
            {
                stbi_image_free(data);
                data = stbi_load(filePathName.c_str(), &width, &height, &channels, 3);
            }
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