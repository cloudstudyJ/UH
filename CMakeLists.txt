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

set(Glfw_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/libs/glfw)

find_package(Vulkan REQUIRED)

file(
    GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp
)

add_executable(
    ${PROJECT_NAME}

    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${SRC_FILES}
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
        ${Glfw_INCLUDE_DIRS}
        ${Vulkan_INCLUDE_DIRS}
)
target_link_libraries(
    ${PROJECT_NAME}

    PRIVATE
        ${Glfw_INCLUDE_DIRS}/libglfw3dll.a
        ${Vulkan_LIBRARIES}
)