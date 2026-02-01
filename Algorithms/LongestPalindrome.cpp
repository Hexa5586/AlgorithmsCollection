// Hoshi-Inori, 2026.01
// Algorithms\LongestPalindrome.cpp

// Document: Documents/Comprehensive/Longest Palindrome.md

#include "Interfaces/ISolution.h"
#include <iostream>
#include <string>
#include <utility>

namespace HoshiInori::Algorithms {
    class LongestPalindromeSolution : public ISolution {

    private:
        int cached_size = 0, cached_now_left = 0, cached_now_size = 0;

        void centricExtendSearch(const std::string& s, int left, int right) {
            while (left >= 0 && right <= cached_size - 1 && s[left] == s[right]) {
                --left; ++right;
            }
            cached_now_left = left + 1;
            cached_now_size = right - left - 1;
        }

    public:
        std::string LongestPalindrome(std::string s) {
            cached_size = s.length();

            int max_size = 1, max_left = 0;

            for (int i = 0; i < cached_size; i++) {
                // Odd length palindrome
                centricExtendSearch(s, i - 1, i + 1);
                if (cached_now_size > max_size) {
                    max_size = cached_now_size;
                    max_left = cached_now_left;
                }

                // Even length palindrome
                if (i < cached_size - 1 && s[i] == s[i + 1]) {
                    centricExtendSearch(s, i - 1, i + 2);
                    if (cached_now_size > max_size) {
                        max_size = cached_now_size;
                        max_left = cached_now_left;
                    }
                }
            }

            return s.substr(max_left, max_size);
        }

        void run() override {
            std::string s;
            std::cin >> s;
            std::cout << LongestPalindrome(s) << std::endl;
        }
    };

    REGISTER_SOLUTION(LongestPalindromeSolution, "LongestPalindrome");
};