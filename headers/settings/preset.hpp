#pragma once

#include "utilities/types.hpp"

namespace UH {
    namespace Preset {
        enum class App: uint8 {
            DEV     = 0,
            RELEASE = 1
        };

        enum class Device: uint8 {
            DEFAULT = 0
        };
    }
}