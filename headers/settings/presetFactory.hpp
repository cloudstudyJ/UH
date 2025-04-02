#pragma once

#include "settings/config.hpp"
#include "settings/preset.hpp"

namespace UH {
    namespace Factory {
        namespace Preset {
            UH::Config::App    app   (UH::Preset::App    appPreset   );
            UH::Config::Device device(UH::Preset::Device devicePreset);
        }
    }
}