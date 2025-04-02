#include "core/device.hpp"
#include "core/instance.hpp"
#include "settings/presetFactory.hpp"

#include <vector>
#include "vulkan/vulkan.h"

/* ---------------------- Func --------------------- */
VkPhysicalDevice_T* findPhysicalDevice(const UH::Config::Device& deviceConfig) {
    // TODO
    return nullptr;
}
/* ------------------------------------------------- */

/* ------------ Constructor & Destructor ----------- */
UH::Device::Device() { }
UH::Device::~Device( ) noexcept { destroy(); }
/* ------------------------------------------------- */

/* -------------- Operator Overloading ------------- */
UH::Device::operator                bool() const noexcept { return mIsCreated;            }
UH::Device::operator VkPhysicalDevice_T*() const noexcept { return mPhysicalDeviceHandle; }
UH::Device::operator         VkDevice_T*() const noexcept { return mLogicalDeviceHandle;  }
/* ------------------------------------------------- */

/* ------------------ Member Func ------------------ */
/**
 * Return
 *   logical device 생성 성공 시 true  반환
 *   logical device 생성 실패 시 false 반환
 */
bool UH::Device::create(UH::Preset::Device devicePreset) {
    if (!mIsCreated) {
        UH::Config::Device deviceConfig = UH::Factory::Preset::device(devicePreset);

        // TODO
        mPhysicalDeviceHandle = findPhysicalDevice(deviceConfig);

        // mIsCreated = true;
        return true;
    }

    return false;
}
void UH::Device::destroy() {
    if (mIsCreated)
        vkDestroyDevice(mLogicalDeviceHandle, nullptr);
}
/* ------------------------------------------------- */