#pragma once

#include "MurmurHash3/MurmurHash3.h"

inline int simpleModuleHash(int key, int size) {
    int result = key % size;
    return result >= 0 ? result : (result+size);
}

inline std::string simpleModuleHashName() {
    return "Simple Module Hash";
}

inline int divisionHash(int key, int size) {
    int result = key % size;
    return result >= 0 ? result : (result + size);
}

inline std::string divisionHashName() {
    return "Division Method Hash";
}

inline int multiplicationHash(int key, int size) {
    static const double A = 0.6180339887;
    double frac = (key * A) - std::floor(key * A);
    int result = (int)std::floor(size * frac);
    return result >= 0 ? result : (result + size);
}

inline std::string multiplicationHashName() {
    return "Multiplication Method Hash";
}

inline int murmurHash3(int key, int size) {
    uint32_t output;
    MurmurHash3_x86_32(&key, sizeof(key), 42, &output);
    return output % size;
}

inline std::string murmurHash3Name() {
    return "MurmurHash3 Hash";
}