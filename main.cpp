#include <iostream>
#include <string>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"
#include "ImGuiFileDialog.h"

void ApplyGrayscale(unsigned char *imageData, int width, int height)
{
    for (int i = 0; i < width * height; ++i)
    {
        unsigned char r = imageData[i * 3];
        unsigned char g = imageData[i * 3 + 1];
        unsigned char b = imageData[i * 3 + 2];

        // Calculate grayscale value
        unsigned char gray = static_cast<unsigned char>(0.2989 * r + 0.5870 * g + 0.1140 * b);

        // Set grayscale value to all channels
        imageData[i * 3] = gray;
        imageData[i * 3 + 1] = gray;
        imageData[i * 3 + 2] = gray;
    }
}

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
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".png,.jpg", ".");

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
            GLuint texture;
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
        }

        ImGui::End();

        // Rendering
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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