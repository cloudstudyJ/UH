#include <iostream>
#include "engine.hpp"
#include "settings/preset.hpp"

int main() {
    UH::Engine engine;

    try {
        engine.init();
        engine.run(UH::Preset::App::DEV);
    }
    catch (const std::exception& e) { }

    engine.shutdown();
    return 0;
}