// Hoshi-Inori, 2026.01
// Algorithms\SlidingWindowMaximum.cpp

// Document: Documents/Comprehensive/Sliding Window Maximum.md

#include "Interfaces/ISolution.h"
#include "Utilities/IOHelper.h"

#include <iostream>
#include <vector>
#include <deque>

namespace HoshiInori::Algorithms {
    class SlidingWindowMaximumSolution : public ISolution {
    public:

        std::vector<int> slidingWindowMaximum(const std::vector<int>& data, int windowLength) {
            int data_length = data.size();

            std::deque<int> monoQueue;
            std::vector<int> result;

            // Forming sliding window
            for (int i = 0; i < windowLength; ++i) {
                while (!monoQueue.empty() && data[monoQueue.back()] < data[i]) {
                    monoQueue.pop_back();
                }
                monoQueue.push_back(i);
            }
            result.push_back(data[monoQueue.front()]);

            // Start sliding
            for (int i = windowLength; i < data_length; ++i) {
                while (!monoQueue.empty() && data[monoQueue.back()] < data[i]) {
                    monoQueue.pop_back();
                }
                monoQueue.push_back(i);

                // Check if the front element is still in the window
                if (monoQueue.front() < i - windowLength + 1) {
                    monoQueue.pop_front();
                }

                result.push_back(data[monoQueue.front()]);
            }

            return result;
        }

        void run() override {
            using namespace HoshiInori::Utils::IO;

            int window_length;
            std::vector<int> data, result;

            readSingle(window_length);
            readVectorTillEOF(data);

            result = slidingWindowMaximum(data, window_length);

            writeVector(result);
        }
    };

    REGISTER_SOLUTION(SlidingWindowMaximumSolution, "SlidingWindowMaximum");
};
