#include "core/device.hpp"
#include "core/instance.hpp"
#include "settings/presetFactory.hpp"
#include "utilities/error.hpp"

#include <iostream>
#include <vector>
#include <cstring>          // strcmp
#include "vulkan/vulkan.h"

/* ---------------------- Func --------------------- */
/* Return
 *   physicalDevice가 모든 extension을 지원하면 true
 *   physicalDevice가 모든 extension을 지원하지 않으면 false
*/
bool isExtensionsSupport(VkPhysicalDevice_T* pDevice, const UH::Config::Device& deviceConfig) {
    uint32 extensionPropsCount = { };
    vkEnumerateDeviceExtensionProperties(pDevice, nullptr, &extensionPropsCount, nullptr);

    std::vector<VkExtensionProperties> extensionProperties(extensionPropsCount);
    vkEnumerateDeviceExtensionProperties(pDevice, nullptr, &extensionPropsCount, extensionProperties.data());

    for (uint64 i = 0; i < deviceConfig.extensionsCount; ++i) {
        const char* extension = deviceConfig.extensions[i];

        bool isSupport = { };
        for (const auto& support: extensionProperties) {
            if (strcmp(support.extensionName, extension) == 0) {
                isSupport = true;
                break;
            }
        }

        if (!isSupport) {
            VkPhysicalDeviceProperties deviceProperties;
            vkGetPhysicalDeviceProperties(pDevice, &deviceProperties);

            // TODO: debug message
            std::cout << "[DEBUG] " << deviceProperties.deviceName << "is not support " << extension << std::endl;
            return false;
        }
    }

    return true;
}
/* Return
 *   모든 extension을 지원하는 physical device들의 handle을 담은 벡터 반환
 *   만약 physical device를 찾을 수 없다면 runtime error throw
*/
std::vector<VkPhysicalDevice_T*> findPhysicalDevices(const UH::Config::Device& deviceConfig) {
    uint32 pDeviceCount{ };
    vkEnumeratePhysicalDevices(UH::Instance::instance(), &pDeviceCount, nullptr);

    std::vector<VkPhysicalDevice_T*> pDevices(pDeviceCount);
    vkEnumeratePhysicalDevices(UH::Instance::instance(), &pDeviceCount, pDevices.data());

    for (auto it = pDevices.begin(); it != pDevices.end();) {
        if (!isExtensionsSupport(*it, deviceConfig)) {
            it = pDevices.erase(it);
            continue;
        }

        ++it;
    }

    // runtime throw를 하는 이유: imgui를 통해 physical device 선택할 수 있도록 하기 위함
    UH_CHECK_THROW(pDevices.empty(), throwType::RUNTIME, "No physical device supports the required vulkan extensions.");
    return pDevices;
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
        UH::Config::Device deviceConfig = UH::Factory::deviceConfig(devicePreset);

        std::vector<VkPhysicalDevice_T*> physicalDeviceList = findPhysicalDevices(deviceConfig);
        // device list select from here

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