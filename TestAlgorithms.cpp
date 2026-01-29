// Hoshi-Inori, 2026.1
// TestAlgorithms.cpp
// The testing platform for Algorithms.

#include "Interfaces/ISolution.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::string target = (argc > 1) ? argv[1] : "HelloWorld";

    auto solution = HoshiInori::Algorithms::SolutionFactory::getInstance().create(target);

    if (solution) {
        std::cout << "=== Executing " << target << " ===" << std::endl;
        solution->run();
        std::cout << "=== Execution Completed ===" << std::endl;
    } else {
        std::cerr << "ERR: Testing solution '" << target << "' hasn't been registered." << std::endl;
    }

    return 0;
}