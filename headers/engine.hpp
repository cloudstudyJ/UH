#pragma once

namespace UH {
    class Engine {
        Engine(const Engine&) = delete;
        Engine(Engine&&) noexcept = delete;

        Engine& operator=(const Engine&) = delete;
        Engine& operator=(Engine&&) noexcept = delete;

        public:
            Engine();
            ~Engine() noexcept;

            void run();
            void shutdown();
    };
}