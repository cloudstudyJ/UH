#include "window.hpp"

#include <iostream>
#include "glfw3.h"

/* --------------------- Func ---------------------- */
void errCallback(int errCode, const char* desc) { std::cerr << "[ERROR " << errCode << "]: " << desc << std::endl; }
/* ------------------------------------------------- */

/* ---------------- Static Member ------------------ */
bool UH::Window::isGlfwInitialized = { };
/* ------------------------------------------------- */

/* ------------ Constructor & Destructor ----------- */
UH::Window::Window() { }
UH::Window::Window(uint32 width, uint32 height, const char* title) { create(width, height, title); }
UH::Window::~Window() noexcept { destroy(); }
/* ------------------------------------------------- */

/* ------------- Operator Overloading -------------- */
UH::Window::operator        bool() const noexcept { return mIsCreated; }
UH::Window::operator GLFWwindow*() const noexcept { return mHandle;    }
/* ------------------------------------------------- */

/* ----------------- Member Func ------------------- */
bool UH::Window::create(uint32 width, uint32 height, const char* title) {
    if (!isGlfwInitialized) {
        if (glfwInit() != GLFW_TRUE)
            throw std::runtime_error("Failed to init glfw!");

        isGlfwInitialized = true;
    }

    if (isGlfwInitialized and !mIsCreated) {
        glfwSetErrorCallback(errCallback);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        if ((mHandle = glfwCreateWindow(width, height, title, nullptr, nullptr)); mHandle == nullptr)
            throw std::runtime_error("Failed to create window!");

        mIsCreated = true;
    }

    return mIsCreated;
}
void UH::Window::destroy() {
    if (mIsCreated) {
        glfwDestroyWindow(mHandle);

        mIsCreated = false;
    }
}
/* ------------------------------------------------- */