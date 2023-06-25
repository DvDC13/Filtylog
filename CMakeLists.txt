cmake_minimum_required(VERSION 3.22.1)
project(Filtylog)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

find_package(glfw3 3.3 REQUIRED)

include_directories(imgui)
add_library(imgui STATIC 
            imgui/imgui.cpp 
            imgui/imgui_demo.cpp
            imgui/imgui_draw.cpp 
            imgui/imgui_tables.cpp
            imgui/imgui_widgets.cpp 
            imgui/backends/imgui_impl_glfw.cpp 
            imgui/backends/imgui_impl_opengl3.cpp)

include_directories(stb_image)
add_library(stb_image STATIC stb_image/stb_image.cpp)

include_directories(imGuiFileDialog)
add_library(imGuiFileDialog STATIC imGuiFileDialog/ImGuiFileDialog.cpp)

include_directories(filters/simpleEffects)
include_directories(filters/utils)

include_directories(glad)

add_executable(filtylog main.cpp)

target_link_libraries(filtylog imgui imGuiFileDialog stb_image glfw GL dl ${OpenCV_LIBS})