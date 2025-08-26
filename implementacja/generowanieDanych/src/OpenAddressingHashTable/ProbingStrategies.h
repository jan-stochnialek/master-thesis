#pragma once

#include <functional>
#include "../HashFunctions/HashFunctions.h"

struct LinearProbing {
    const std::string name = "Linear Probing";
    std::function<int(int, int)> hash_function;
    std::string hash_function_name;

    explicit LinearProbing(std::function<int(int, int)> func, std::string func_name) : hash_function(std::move(func)), hash_function_name(std::move(func_name)) {}

    int operator()(int key, int i, int table_size) const {
        return (hash_function(key, table_size) + i) % table_size;
    }
};

struct DoubleHashing {
    const std::string name = "Double Hashing";
    std::function<int(int,int)> hash1;
    std::function<int(int,int)> hash2;
    std::string hash1_name;
    std::string hash2_name;

    DoubleHashing(std::function<int(int,int)> func1, std::string name1, std::function<int(int,int)> func2, std::string name2) :
        hash1(std::move(func1)), hash2(std::move(func2)), hash1_name(std::move(name1)), hash2_name(std::move(name2)) {}

    int operator()(int key, int i, int table_size) const {
        return (hash1(key, table_size) + i * hash2(key, table_size)) % table_size;
    }
};