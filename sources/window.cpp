#include "window.hpp"
#include "core/instance.hpp"
#include "utilities/error.hpp"

#include "glfw/glfw3.h"

/* --------------------- Func ---------------------- */
void errCallback(int errCode, const char* errMessage) { UH_LOG(logType::ERROR, errMessage, errCode); }
/* ------------------------------------------------- */

/* ------------ Constructor & Destructor ----------- */
UH::Window::Window() { }
UH::Window::Window(uint32 width, uint32 height, const char* title) { create(width, height, title); }
UH::Window::~Window() noexcept { destroy(); }
/* ------------------------------------------------- */

/* ------------- Operator Overloading -------------- */
UH::Window::operator        bool() const noexcept { return mIsCreated;    }
UH::Window::operator GLFWwindow*() const noexcept { return mWindowHandle; }
/* ------------------------------------------------- */

/* ----------------- Member Func ------------------- */
bool UH::Window::create(uint32 width, uint32 height, const char* title) {
    if (!mIsCreated) {
        glfwSetErrorCallback(errCallback);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);     // TODO: window hints
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        mWindowHandle = glfwCreateWindow(width, height, title, nullptr, nullptr);
        UH_CHECK_THROW(!mWindowHandle, throwType::RUNTIME, "Failed to create window!");

        UH_CHECK_THROW(
            glfwCreateWindowSurface(UH::Instance::instance(), mWindowHandle, nullptr, &mSurfaceHandle),
            throwType::RUNTIME, "Failed to create window surface!"
        );

        mIsCreated = true;
    }

    return mIsCreated;
}
void UH::Window::destroy() {
    if (mIsCreated) {
        vkDestroySurfaceKHR(UH::Instance::instance(), mSurfaceHandle, nullptr);
        glfwDestroyWindow(mWindowHandle);

        mIsCreated = false;
    }
}
/* ------------------------------------------------- */