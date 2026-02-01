// Hoshi-Inori, 2026.02
// Algorithms\MajorityElement.cpp

// Document: Documents/Maths/Majority Elements.md

#include "Interfaces/ISolution.h"
#include "Utilities/IOHelper.h"

#include <iostream>
#include <vector>

namespace HoshiInori::Algorithms {
    class MajorityElementSolution : public ISolution {
    public:

        int MajorityElement(const std::vector<int>& nums) {
            int candidate = nums[0], count = 1, nums_size = nums.size();

            for (int i = 1; i < nums_size; ++i) {
                if (count == 0) {
                    candidate = nums[i];
                }
                count += (candidate == nums[i] ? 1 : -1);
            }
            return candidate;
        }

        void run() override {
            using namespace HoshiInori::Utils::IO;

            std::vector<int> nums;
            readVectorTillEOF(nums);

            writeSingle(MajorityElement(nums));
        }
    };

    REGISTER_SOLUTION(MajorityElementSolution, "MajorityElement");
};