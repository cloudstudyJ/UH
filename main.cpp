#include <iostream>
#include "engine.hpp"

int main() {
    UH::Engine engine;

    try { engine.run(); }
    catch (const std::exception& e) { std::cerr << "[ERROR]:" << e.what() << std::endl; }

    engine.shutdown();
    return 0;
}