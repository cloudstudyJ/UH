#pragma once

#include "types.hpp"

struct GLFWwindow;

namespace UH {
    class Window {
        Window(const Window&) = delete;
        Window(Window&&) noexcept = delete;

        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) noexcept = delete;

        public:
            Window();
            ~Window() noexcept;

            explicit operator bool() const noexcept;
            operator GLFWwindow*() const noexcept;

            void create(uint32 width, uint32 height, const char* title);

        private:
            bool mIsCreated = { };

            GLFWwindow* mHandle = { };

            static bool isGlfwInitialized;
    };
}