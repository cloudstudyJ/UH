#include "settings/presetFactory.hpp"
#include "settings/presetData.hpp"

template <typename T, uint64 Size>
uint64 arrSize(T (&arr)[Size]) { return Size; }

/**
 * Return
 *   지정한 preset에 맞게 App 생성에 필요한 정보 반환
 */
UH::Config::App UH::Factory::appConfig(UH::Preset::App appPreset) {
    using namespace UH;

    Config::App appConfig;
    switch (appPreset) {
        case Preset::App::DEV: {
            appConfig = {
                .appName    = PresetData::App::DEV.APP_NAME,
                .appVer     = PresetData::App::DEV.APP_VER,
                .engineName = PresetData::App::ENGINE_NAME,
                .engineVer  = PresetData::App::DEV.ENGINE_VER,
                .vulkanAPI  = PresetData::App::VULKAN_API_VER
            };
            break;
        }
        case Preset::App::RELEASE: {
            appConfig = {
                .appName    = PresetData::App::RELEASE.APP_NAME,
                .appVer     = PresetData::App::RELEASE.APP_VER,
                .engineName = PresetData::App::ENGINE_NAME,
                .engineVer  = PresetData::App::RELEASE.ENGINE_VER,
                .vulkanAPI  = PresetData::App::VULKAN_API_VER
            };
            break;
        }

        default: break;
    }

    return appConfig;
}
/**
 * Return
 *   지정한 preset에 맞게 device 생성에 필요한 정보 반환
 */
UH::Config::Device UH::Factory::deviceConfig(UH::Preset::Device devicePreset) {
    using namespace UH;

    Config::Device deviceConfig;
    switch (devicePreset) {
        case Preset::Device::DEFAULT: {
            deviceConfig = {
                .extensions      = PresetData::Extension::DEVICE_DEFAULT,
                .extensionsCount = arrSize(PresetData::Extension::DEVICE_DEFAULT)
            };
            break;
        }

        default: break;
    }

    return deviceConfig;
}