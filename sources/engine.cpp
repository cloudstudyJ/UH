#include "engine.hpp"
#include "settings.hpp"
#include "core/instance.hpp"

#include "vulkan/vulkan.h"
#include "glfw3.h"

/* ------------ Constructor & Destructor ----------- */
UH::Engine::Engine() { }
UH::Engine::~Engine() noexcept { }
/* ------------------------------------------------- */

/* ----------------- Member Func ------------------- */
void UH::Engine::run() {
    mMainWindow.create(1280, 720, "test");
    UH::Instance::instance().create(UH::Settings::App{});

    while (!glfwWindowShouldClose(mMainWindow)) { glfwPollEvents(); }
}
void UH::Engine::shutdown() {
    UH::Instance::instance().destroy();

    mMainWindow.destroy();
    glfwTerminate();
}
/* ------------------------------------------------- */