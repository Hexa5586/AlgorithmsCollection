// Hoshi-Inori, 2026.1
// TestAlgorithms.cpp
// The testing platform for Algorithms.

#include "Interfaces/ISolution.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string arg = argv[1];

        if (arg == "--list") {

            auto keys = HoshiInori::Algorithms::SolutionFactory::getInstance().listSolutions();
            
            std::cout << "Available solutions:" << std::endl;
            for (const auto& name : keys) {
                std::cout << "  - " << name << std::endl;
            }
            return 0;
        }

        auto solution = HoshiInori::Algorithms::SolutionFactory::getInstance().create(arg);
        if (solution) {
            solution->run();
        } else {
            std::cerr << "[ERR] Testing solution '" << arg << "' hasn't been registered." << std::endl;
            return 1;
        }
    } else {
        std::cout << "Usage: ./TestAlgorithms <SolutionName> or --list" << std::endl;
    }

    return 0;
}