// Hoshi-Inori, 2026.1
// Algorithms\HelloWorld.cpp
// Testing algorithm.

#include "Interfaces/ISolution.h"
#include <iostream>

namespace HoshiInori::Algorithms {
    class HelloWorldSolution : public ISolution {
    public:
        void run() override {
            std::cout << "Hello World" << std::endl;
        }
    };

    REGISTER_SOLUTION(HelloWorldSolution, "HelloWorld");
};
