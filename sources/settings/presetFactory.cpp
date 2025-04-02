#include "settings/presetFactory.hpp"
#include "settings/presetData.hpp"

/**
 * Return
 *   지정한 preset에 맞게 App 생성에 필요한 정보 반환
 */
UH::Config::App UH::Factory::Preset::app(UH::Preset::App appPreset) {
    UH::Config::App appConfig;

    switch (appPreset) {
        case UH::Preset::App::DEV: {
            appConfig = {
                .appName    = UH::PresetData::App::DEV.APP_NAME,
                .appVer     = UH::PresetData::App::DEV.APP_VER,
                .engineName = UH::PresetData::App::ENGINE_NAME,
                .engineVer  = UH::PresetData::App::DEV.ENGINE_VER,
                .vulkanAPI  = UH::PresetData::App::VULKAN_API_VER
            };

            break;
        }
        case UH::Preset::App::RELEASE: {
            appConfig = {
                .appName    = UH::PresetData::App::RELEASE.APP_NAME,
                .appVer     = UH::PresetData::App::RELEASE.APP_VER,
                .engineName = UH::PresetData::App::ENGINE_NAME,
                .engineVer  = UH::PresetData::App::RELEASE.ENGINE_VER,
                .vulkanAPI  = UH::PresetData::App::VULKAN_API_VER
            };

            break;
        }

        default:
            break;
    }

    return appConfig;
}
/**
 * Return
 *   지정한 preset에 맞게 device 생성에 필요한 정보 반환
 */
UH::Config::Device UH::Factory::Preset::device(UH::Preset::Device devicePreset) {
    UH::Config::Device deviceConfig;

    switch (devicePreset) {
        case UH::Preset::Device::DEFAULT: {
            deviceConfig = {
                .extensions = UH::PresetData::Extension::DEVICE_DEFAULT
            };

            break;
        }

        default:
            break;
    }

    return deviceConfig;
}