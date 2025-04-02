#pragma once

#include "settings/preset.hpp"
#include "window.hpp"
#include "core/device.hpp"

namespace UH {
    class Engine {
        Engine(const Engine&) = delete;
        Engine(Engine&&) noexcept = delete;

        Engine& operator=(const Engine&) = delete;
        Engine& operator=(Engine&&) noexcept = delete;

        public:
            Engine();
            ~Engine() noexcept;

            void run(UH::Preset::App appPreset);
            void shutdown();

        private:
            UH::Window mMainWindow;
            UH::Device mDevice;
    };
}