#include "core/instance.hpp"
#include "settings/presetFactory.hpp"

#include <iostream>
#include <vector>
#include "vulkan/vulkan.h"
#include "glfw3.h"          // glfwGetRequiredInstanceExtensions()

/* --------------------- Func ---------------------- */
/**
 * Return
 *   glfw가 지원하는 vulkan extension list 반환
 */
std::vector<const char*> loadGlfwExtensions() {
    uint32 glfwExtensionCount = { };
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    if ((glfwExtensionCount == 0) or (glfwExtensions == nullptr))
        throw std::runtime_error("Failed to get glfw vulkan extensions!");

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifdef DEBUG
    std::cout << "[DEBUG] glfw vulkan extension list" << std::endl;

    for (uint32 i = 0; i < extensions.size(); ++i)
        std::cout << "  " << i + 1 << ": " << extensions[i] << std::endl;
#endif

    return extensions;
}
#ifdef DEBUG
void destroyDebugMessenger(VkInstance_T* handle, VkDebugUtilsMessengerEXT_T* messenger) {
    ((PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(handle, "vkDestroyDebugUtilsMessengerEXT"))
    (handle, messenger, nullptr);
}
uint32 __attribute__((__stdcall__)) debugCallback(
          VkDebugUtilsMessageSeverityFlagBitsEXT severity    , uint32 type,
    const VkDebugUtilsMessengerCallbackDataEXT*  callbackData, void*  userData
) {
    const char* debugMsg  = { };
    std::vector<const char*> debugType;

    if      (severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) debugMsg = "[Verbose]";
    else if (severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)    debugMsg = "[Info]";
    else if (severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) debugMsg = "[Warning]";
    else if (severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)   debugMsg = "[Error]";
    else                                                                  debugMsg = "[Unknown]";

    if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)                debugType.push_back("[General]");
    if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)             debugType.push_back("[Validation]");
    if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)            debugType.push_back("[Performance]");

    if (debugType.empty())
        debugType.push_back("[Unknown]");

    std::cout << "[DEBUG]" << debugMsg;
    for (const auto& type: debugType)
        std::cout << type;
    std::cout << std::endl;
    std::cout << callbackData->pMessage << std::endl << std::endl;

    return 0U;
}
#endif
/* ------------------------------------------------- */

/* ------------------ Static Func ------------------ */
UH::Instance& UH::Instance::instance() {
    static Instance inst;

    return inst;
}
/* ------------------------------------------------- */

/* ------------ Constructor & Destructor ----------- */
UH::Instance::Instance() { }
UH::Instance::~Instance() noexcept { }
/* ------------------------------------------------- */

/* ------------- Operator Overloading -------------- */
UH::Instance::operator          bool() const noexcept { return mIsCreated; }
UH::Instance::operator VkInstance_T*() const noexcept { return mHandle;    }
/* ------------------------------------------------- */

/* ----------------- Member Func ------------------- */
/**
 * Return
 *   vulkan instance 생성 성공 시 true  반환
 *   vulkan instance 생성 실패 시 false 반환
 */
bool UH::Instance::create(UH::Preset::App appPreset) {
    if (!mIsCreated) {
        UH::Config::App appConfig = UH::Factory::Preset::app(appPreset);

#ifdef DEBUG
        std::cout << "[DEBUG] application settings" << std::endl;
        std::cout << "  App name:    " << appConfig.appName    << std::endl;
        std::cout << "  App ver:     " << appConfig.appVer     << std::endl;
        std::cout << "  Engine name: " << appConfig.engineName << std::endl;
        std::cout << "  Engine ver:  " << appConfig.engineVer  << std::endl;
#endif
        VkApplicationInfo appInfo {
            .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pApplicationName   = appConfig.appName,
            .applicationVersion = appConfig.appVer,
            .pEngineName        = appConfig.engineName,
            .engineVersion      = appConfig.engineVer,
            .apiVersion         = appConfig.vulkanAPI
        };

        std::vector<const char*> glfwExtensions = loadGlfwExtensions();
#ifdef DEBUG
        glfwExtensions.push_back("VK_EXT_debug_utils");
        std::cout << "  " << glfwExtensions.size() << ": VK_EXT_debug_utils" << std::endl;

        std::vector<const char*> layers = { "VK_LAYER_KHRONOS_validation" };

        VkDebugUtilsMessengerCreateInfoEXT debugInfo {
            .sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
            .messageSeverity = 0x0000'1100U,        // WARNING and ERROR
            .messageType     = 0x0000'0007U,        // GENERAL and VALIDATION and PERFORMANCE
            .pfnUserCallback = debugCallback
        };

        glfwExtensions.shrink_to_fit();
#endif

        VkInstanceCreateInfo instanceInfo {
            .sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
#ifdef DEBUG
            .pNext                   = &debugInfo,
#endif
            .pApplicationInfo        = &appInfo,
#ifdef DEBUG
            .enabledLayerCount       = static_cast<uint32>(layers.size()),
            .ppEnabledLayerNames     = layers.data(),
#endif
            .enabledExtensionCount   = static_cast<uint32>(glfwExtensions.size()),
            .ppEnabledExtensionNames = glfwExtensions.data()
        };

        if (vkCreateInstance(&instanceInfo, nullptr, &mHandle) != VK_SUCCESS)
            throw std::runtime_error("Failed to create vulkan instance!");

#ifdef DEBUG
        auto createDebugMessenger = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(mHandle, "vkCreateDebugUtilsMessengerEXT");

        if ((createDebugMessenger == nullptr) or (createDebugMessenger(mHandle, &debugInfo, nullptr, &mDebugMessenger) != VK_SUCCESS))
            throw std::runtime_error("Failed to create debug messenger!");
#endif

        mIsCreated = true;
        return true;
    }

#ifdef DEBUG
    std::cout << "[WARNING]: Vulkan instance is already created!" << std::endl;
#endif
    return false;
}
void UH::Instance::destroy() {
    if (mIsCreated) {
    #ifdef DEBUG
        destroyDebugMessenger(mHandle, mDebugMessenger);
    #endif
        vkDestroyInstance(mHandle, nullptr);

        mIsCreated = false;
    }
}
/* ------------------------------------------------- */
