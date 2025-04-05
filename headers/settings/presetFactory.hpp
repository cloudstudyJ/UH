#pragma once

#include "settings/config.hpp"
#include "settings/preset.hpp"

namespace UH {
    namespace Factory {
        UH::Config::App       appConfig(UH::Preset::App       appPreset);
        UH::Config::Device deviceConfig(UH::Preset::Device devicePreset);
    }
}