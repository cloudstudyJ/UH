#pragma once

#include "utilities/types.hpp"

namespace UH {
    namespace Config {
        struct App {
            const char* appName    = { };
                uint32  appVer     = { };
            const char* engineName = { };
                uint32  engineVer  = { };
                uint32  vulkanAPI  = { };
        };

        struct Device {
            const char* const* extensions      = { };
                       uint64  extensionsCount = { };
        };
    }
}