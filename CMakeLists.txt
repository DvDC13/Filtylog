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

add_executable(filtylog main.cpp)

target_link_libraries(filtylog imgui glfw GL dl)