#pragma once

#include "utilities/types.hpp"

namespace UH {
    namespace PresetData {
        namespace App {
            /*
            * Vulkan SDK 1.4.304.0
            *     #define VK_API_VERSION_1_3 VK_MAKE_API_VERSION(0, 1, 3, 0)// Patch version should always be set to 0
            *     #define VK_MAKE_API_VERSION(variant, major, minor, patch) \
            *             ((((uint32_t)(variant)) << 29U) | (((uint32_t)(major)) << 22U) | (((uint32_t)(minor)) << 12U) | ((uint32_t)(patch)))
            */
            inline constexpr const uint32  VULKAN_API_VER = 4'206'592U;      // = VK_API_VERSION_1_3 ((1U << 22U) | (3U << 12U))
            inline constexpr const   char* ENGINE_NAME    = "UH";

            inline constexpr struct {
                const char* APP_NAME    = { };
                    uint32  APP_VER     = { };
                    uint32  ENGINE_VER  = { };
            }

            DEV = {
                .APP_NAME    = "UH_DEV",
                .APP_VER     = { },
                .ENGINE_VER  = { }
            },
            RELEASE = {
                .APP_NAME    = "UH_RELEASE",
                .APP_VER     = { },
                .ENGINE_VER  = { }
            };
        }
        namespace Extension {
            inline constexpr const char* DEVICE_DEFAULT[] = {
                "VK_KHR_swapchain"      // VK_KHR_SWAPCHAIN_EXTENSION_NAME
            };
        }
    }
}