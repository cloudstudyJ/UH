#pragma once

#include "settings/preset.hpp"

struct VkPhysicalDevice_T;
struct VkDevice_T;

namespace UH {
    class Device {
        Device(const Device&) = delete;
        Device(Device&&) noexcept = delete;

        Device& operator=(const Device&) = delete;
        Device& operator=(Device&&) noexcept = delete;

        public:
            Device();
            ~Device() noexcept;

            explicit operator       bool() const noexcept;
            operator VkPhysicalDevice_T*() const noexcept;
            operator         VkDevice_T*() const noexcept;

            bool create(UH::Preset::Device devicePreset);
            void destroy();

        private:
            bool mIsCreated = { };

            VkPhysicalDevice_T* mPhysicalDeviceHandle = { };
            VkDevice_T*         mLogicalDeviceHandle  = { };
    };
}