#include "engine.hpp"
#include "core/instance.hpp"
#include "utilities/error.hpp"

#include "glfw/glfw3.h"

/* ------------ Constructor & Destructor ----------- */
UH::Engine::Engine() { }
UH::Engine::~Engine() noexcept { }
/* ------------------------------------------------- */

/* ----------------- Member Func ------------------- */
void UH::Engine::init() {
    UH_CHECK_THROW(!glfwInit(), throwType::RUNTIME, "Failed to init glfw.");
    UH_CHECK_THROW(!glfwVulkanSupported(), throwType::RUNTIME, "Glfw does not support vulkan.");

    // TODO: init imgui
}
void UH::Engine::run(UH::Preset::App appPreset) {
    UH::Instance::instance().create(appPreset);
    mMainWindow.create(1280, 720, "test");          // TODO: set window preset
    mDevice.create(UH::Preset::Device::DEFAULT);

    // TODO: move this function to renderer and delete #include "glfw3.h"
    while (!glfwWindowShouldClose(mMainWindow)) {
        glfwPollEvents();
    }
}
void UH::Engine::shutdown() {
    mDevice.destroy();

    mMainWindow.destroy();
    UH::Instance::instance().destroy();
    glfwTerminate();
}
/* ------------------------------------------------- */