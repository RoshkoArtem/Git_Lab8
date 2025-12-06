cmake_minimum_required(VERSION 3.10)

project(My3DViewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пакети з vcpkg
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(My3DViewer
    src/main.cpp
    src/ViewerWindow.cpp
    src/ViewerWindow.h
    src/OpenglRenderSystem.cpp
    src/OpenglRenderSystem.h
    src/Vertex.h
    src/GeometryPrimitives.cpp
    src/GeometryPrimitives.h
)

target_link_libraries(My3DViewer PRIVATE
    glfw
    glad::glad
    glm::glm
    OpenGL::GL
)

target_include_directories(My3DViewer PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

# Щоб GLFW не тягнув свій OpenGL (ми використовуємо glad)
target_compile_definitions(My3DViewer PRIVATE GLFW_INCLUDE_NONE)
