// Hoshi-Inori, 2026.1
// Interfaces/ISolution.h
// Provides an interface ISolution to regular the definition of Solutions.
// All Solutions should implement interface ISolution, and register the Solution using REGISTER_SOLUTION(DerivedClass, RegistrationName).

#pragma once

#include <map>
#include <string>
#include <memory>

namespace HoshiInori::Algorithms {
    class ISolution {
    public:
        virtual ~ISolution() = default;
        virtual void run() = 0;
    };

    class SolutionFactory {
    public:
        using Creator = std::unique_ptr<ISolution>(*)();
        static SolutionFactory& getInstance() {
            static SolutionFactory instance;
            return instance;
        }
        void registerSolution(const std::string& name, Creator creator) {
            storage[name] = creator;
        }
        std::unique_ptr<ISolution> create(const std::string& name) {
            if (storage.find(name) == storage.end()) return nullptr;
            return storage[name]();
        }
    private:
        std::map<std::string, Creator> storage;
    };
};

#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPL(a, b)

#define REGISTER_SOLUTION(DerivedClass, RegistrationName) \
static bool CONCAT(res_, __LINE__) = []() { \
    Algorithms::SolutionFactory::getInstance().registerSolution(RegistrationName, []() -> std::unique_ptr<ISolution> { \
        return std::make_unique<DerivedClass>(); \
    }); \
    return true; \
}()
