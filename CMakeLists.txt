# glfw   3.4.0
# vulkan 1.4.304.0
#
# os      : windows 11
# compiler: mingw-w64 13.2.0 (x86_64-posix-seh-rev1)

cmake_minimum_required(VERSION 3.11)
project(UH)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(Libs_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/libs)
set(Glfw_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/libs/glfw)
set(Imgui_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/libs/imgui)

find_package(Vulkan REQUIRED)

file(
    GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp
)

add_executable(
    ${PROJECT_NAME}

    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${SRC_FILES}

    ${Imgui_INCLUDE_DIRS}/imgui.cpp
    ${Imgui_INCLUDE_DIRS}/imgui_demo.cpp
    ${Imgui_INCLUDE_DIRS}/imgui_draw.cpp
    ${Imgui_INCLUDE_DIRS}/imgui_tables.cpp
    ${Imgui_INCLUDE_DIRS}/imgui_widgets.cpp
    ${Imgui_INCLUDE_DIRS}/backends/imgui_impl_glfw.cpp
    ${Imgui_INCLUDE_DIRS}/backends/imgui_impl_vulkan.cpp
)

target_compile_definitions(
    ${PROJECT_NAME}

    PRIVATE
        DEBUG
        GLFW_INCLUDE_VULKAN
)
target_include_directories(
    ${PROJECT_NAME}

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
        ${Libs_INCLUDE_DIRS}
        ${Glfw_INCLUDE_DIRS}
        ${Imgui_INCLUDE_DIRS}
        ${Vulkan_INCLUDE_DIRS}
)
target_link_libraries(
    ${PROJECT_NAME}

    PRIVATE
        ${Glfw_INCLUDE_DIRS}/libglfw3dll.a
        ${Vulkan_LIBRARIES}
)