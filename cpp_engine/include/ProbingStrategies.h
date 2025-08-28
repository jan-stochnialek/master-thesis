#pragma once

#include <functional>
#include <string>
#include "HashFunctions.h"

struct LinearProbing {
    const std::string name = "LinearProbing";
    std::function<int(int, int)> hash_function;
    std::string hash_function_name;

    explicit LinearProbing(std::function<int(int, int)> func, std::string func_name);
    int operator()(int key, int i, int table_size) const;
};

struct QuadraticProbing {
    const std::string name = "QuadraticProbing";
    std::function<int(int, int)> hash_function;
    std::string hash_function_name;
    double c1;
    double c2;

    QuadraticProbing(std::function<int(int, int)> func, std::string func_name, double c1_ = 0.5, double c2_ = 0.5);
    int operator()(int key, int i, int table_size) const;
};

struct DoubleHashing {
    const std::string name = "DoubleHashing";
    std::function<int(int,int)> hash1;
    std::function<int(int,int)> hash2;
    std::string hash1_name;
    std::string hash2_name;

    DoubleHashing(std::function<int(int,int)> func1, std::string name1, std::function<int(int,int)> func2, std::string name2);
    int operator()(int key, int i, int table_size) const;
};