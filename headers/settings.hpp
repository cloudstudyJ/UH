#pragma once

namespace UH {
    namespace Settings {
        struct App {
            /*
            * Vulkan SDK 1.4.304.0
            *     #define VK_API_VERSION_1_3 VK_MAKE_API_VERSION(0, 1, 3, 0)// Patch version should always be set to 0
            *     #define VK_MAKE_API_VERSION(variant, major, minor, patch) \
            *             ((((uint32_t)(variant)) << 29U) | (((uint32_t)(major)) << 22U) | (((uint32_t)(minor)) << 12U) | ((uint32_t)(patch)))
            */
            static constexpr       uint32 VULKAN_API_VER  = 4'206'592U;     // = VK_API_VERSION_1_3 ((1U << 22U) | (3U << 12U))

            static constexpr const char*  APP_NAME = "UH";
            static constexpr       uint32 APP_VER  = 0U;

            static constexpr const char*  ENGINE_NAME = "UH";
            static constexpr       uint32 ENGINE_VER  = 0U;
        };
    }
}