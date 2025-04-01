#include "engine.hpp"
#include "window.hpp"

#include "glfw3.h"

/* ------------ Constructor & Destructor ----------- */
UH::Engine::Engine() { }
UH::Engine::~Engine() noexcept { }
/* ------------------------------------------------- */

/* ----------------- Member Func ------------------- */
void UH::Engine::run() {
    UH::Window window;
    window.create(1280, 720, "test");

    while (!glfwWindowShouldClose(window)) { glfwPollEvents(); }
}
void UH::Engine::shutdown() { glfwTerminate(); }
/* ------------------------------------------------- */