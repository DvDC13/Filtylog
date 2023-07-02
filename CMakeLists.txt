cmake_minimum_required(VERSION 3.22.1)
project(Filtylog)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
add_library(stb_image STATIC stb_image/stb_image.cpp
                             stb_image/stb_image_write.cpp)

include_directories(imGuiFileDialog)
add_library(imGuiFileDialog STATIC imGuiFileDialog/ImGuiFileDialog.cpp)

include_directories(include/artisticFilters)
include_directories(include/utils)

add_library("${PROJECT_NAME}_lib" STATIC)
target_include_directories("${PROJECT_NAME}_lib" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(src)

include_directories(glad)

add_executable(filtylog main.cc)

target_link_libraries(filtylog imgui imGuiFileDialog stb_image glfw GL dl "${PROJECT_NAME}_lib")