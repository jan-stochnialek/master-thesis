#include "HashFunctions.h"
#include "MurmurHash3.h"
#include <cmath>
#include <string>

int simpleModuleHash(int key, int size) {
    int result = key % size;
    return result >= 0 ? result : (result+size);
}

std::string simpleModuleHashName() {
    return "SimpleModuloHash";
}

int divisionHash(int key, int size) {
    int result = key % size;
    return result >= 0 ? result : (result + size);
}

std::string divisionHashName() {
    return "DivisionHash";
}

int multiplicationHash(int key, int size) {
    static const double A = 0.6180339887;
    double frac = (key * A) - std::floor(key * A);
    int result = (int)std::floor(size * frac);
    return result >= 0 ? result : (result + size);
}

std::string multiplicationHashName() {
    return "MultiplicationHash";
}

int murmurHash3(int key, int size) {
    uint32_t output;
    MurmurHash3_x86_32(&key, sizeof(key), 42, &output);
    return output % size;
}

std::string murmurHash3Name() {
    return "MurmurHash3";
}
