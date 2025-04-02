#include "engine.hpp"
#include "core/instance.hpp"

#include "vulkan/vulkan.h"
#include "glfw3.h"

/* ------------ Constructor & Destructor ----------- */
UH::Engine::Engine() { }
UH::Engine::~Engine() noexcept { }
/* ------------------------------------------------- */

/* ----------------- Member Func ------------------- */
void UH::Engine::run(UH::Preset::App appPreset) {
    mMainWindow.create(1280, 720, "test");          // TODO: set window preset
    UH::Instance::instance().create(appPreset);
    mDevice.create(UH::Preset::Device::DEFAULT);

    while (!glfwWindowShouldClose(mMainWindow)) { glfwPollEvents(); }
}
void UH::Engine::shutdown() {
    mDevice.destroy();
    UH::Instance::instance().destroy();

    mMainWindow.destroy();
    glfwTerminate();
}
/* ------------------------------------------------- */