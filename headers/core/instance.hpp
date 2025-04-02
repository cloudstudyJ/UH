#pragma once

#include "settings/preset.hpp"

struct VkInstance_T;
#ifdef DEBUG
struct VkDebugUtilsMessengerEXT_T;
#endif

namespace UH {
    /**
     * Instance class is singleton
     */
    class Instance {
        Instance(const Instance&) = delete;
        Instance(Instance&&) noexcept = delete;

        Instance& operator=(const Instance&) = delete;
        Instance& operator=(Instance&&) noexcept = delete;

        public:
            static Instance& instance();

            explicit operator bool() const noexcept;
            operator VkInstance_T*() const noexcept;

            bool create(UH::Preset::App appPreset);
            void destroy();

        private:
            Instance();
            ~Instance() noexcept;

        private:
            bool mIsCreated = { };

            VkInstance_T* mHandle = { };
#ifdef DEBUG
            VkDebugUtilsMessengerEXT_T* mDebugMessenger = { };
#endif
    };
}