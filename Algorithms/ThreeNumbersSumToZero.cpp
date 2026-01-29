// Hoshi-Inori, 2026.01
// Algorithms\TheSumOfThreeNumbers.cpp
// <Description Here>

#include "Interfaces/ISolution.h"
#include "Utilities/IOHelper.h"

#include <iostream>
#include <vector>
#include <algorithm>

namespace HoshiInori::Algorithms {
    class ThreeNumbersSumToZeroSolution : public ISolution {
    public:

        std::vector<std::vector<int>> TheSumOfThreeNumbers(std::vector<int> data) {
            std::vector<std::vector<int>> result;

            int length = data.size();
            std::sort(data.begin(), data.end(), std::less<int>());

            for (int i = 0; i < length - 2; ++i) {
                if (i > 0 && data[i] == data[i - 1])    continue;

                int pivot = data[i];
                int left = i + 1, right = length - 1;

                while (left < right) {
                    int s = pivot + data[left] + data[right];
                    if (s < 0)  ++left;               
                    else if (s > 0) --right;
                    else {
                        result.push_back({pivot, data[left], data[right]});
                        ++left; --right;

                        while (left < right && data[left] == data[left - 1])    ++left;
                        while (left < right && data[right] == data[right + 1])  --right;
                    }
                }
            }
            return result;
        }
        
        void run() override {
            using namespace HoshiInori::Utils::IO;

            std::vector<int> data;
            readVectorTillEOF(data);

            auto result = TheSumOfThreeNumbers(data);
            writeVector(result);
        }
    };

    REGISTER_SOLUTION(ThreeNumbersSumToZeroSolution, "ThreeNumbersSumToZero");
};