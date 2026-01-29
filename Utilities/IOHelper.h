// Hoshi-Inori, 2026.1
// IOHelper.h
// Provides convenient I/O function support for non-first-class types.

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <climits>

namespace HoshiInori::Utils::IO {

    template <class T>
    struct is_vector : std::false_type {};

    template <class T>
    struct is_vector<std::vector<T>> : std::true_type {};

    template <class T>
    T getSingle() {
        T temp;
        std::cin >> temp;
        return temp;
    }

    template <class T>
    void readSingle(T& var) {
        std::cin >> var;
    }

    template <class T>
    void writeSingle(const T& var, std::string endline = "\n") {
        std::cout << var << endline;
    }

    template <class T>
    void readVectorTillEOF(std::vector<T>& vct, bool appending = false) {
        if (!appending) {
            vct.clear();
        }

        T temp;
        while (std::cin >> temp) {
            vct.push_back(temp);
        }
    }

    template <class T>
    void readVectorTillN(std::vector<T>& vct, int n, bool appending = false) {
        if (!appending) {
            vct.clear();
        }

        T temp;
        for (int i = 0; i < n; ++i) {
            std::cin >> temp;
            vct.push_back(temp);
        }
    }

    template <class T>
    void writeVector(const T& val, int depth = 0) {
        if constexpr (is_vector<T>::value) {
            std::cout << "[";
            for (size_t i = 0; i < val.size(); ++i) {
                writeVector(val[i], depth + 1);
                if (i != val.size() - 1) std::cout << ", ";
            }
            std::cout << "]";
            if (depth == 0) std::cout << std::endl;
        } else {
            std::cout << val;
        }
    }
};