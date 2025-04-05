#pragma once

#include "utilities/types.hpp"

struct GLFWwindow;
struct VkSurfaceKHR_T;

namespace UH {
    class Window {
        Window(const Window&) = delete;
        Window(Window&&) noexcept = delete;

        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) noexcept = delete;

        public:
            Window();
            Window(uint32 width, uint32 height, const char* title);
            ~Window() noexcept;

            explicit operator bool() const noexcept;
            operator   GLFWwindow*() const noexcept;

            bool create(uint32 width, uint32 height, const char* title);
            void destroy();

        private:
            bool mIsCreated = { };

            GLFWwindow*     mWindowHandle  = { };
            VkSurfaceKHR_T* mSurfaceHandle = { };
    };
}