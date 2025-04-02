#include <iostream>
#include "engine.hpp"
#include "settings/preset.hpp"

int main() {
    UH::Engine engine;

    try { engine.run(UH::Preset::App::DEV); }
    catch (const std::exception& e) { std::cerr << "[ERROR]:" << e.what() << std::endl; }

    engine.shutdown();
    return 0;
}