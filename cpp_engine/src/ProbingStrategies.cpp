#include "ProbingStrategies.h"

#include <cmath>

LinearProbing::LinearProbing(std::function<int(int, int)> func, std::string func_name)
    : hash_function(std::move(func)), hash_function_name(std::move(func_name)) {}

int LinearProbing::operator()(int key, int i, int table_size) const {
    return (hash_function(key, table_size) + i) % table_size;
}

QuadraticProbing::QuadraticProbing(std::function<int(int, int)> func, std::string func_name, double c1_, double c2_)
    : hash_function(std::move(func)), hash_function_name(std::move(func_name)), c1(c1_), c2(c2_) {}

int QuadraticProbing::operator()(int key, int i, int table_size) const {
    int hash = hash_function(key, table_size);
    int idx = static_cast<int>((hash + c1 * i + c2 * i * i)) % table_size;
    return idx >= 0 ? idx : (idx + table_size);
}

DoubleHashing::DoubleHashing(std::function<int(int,int)> func1, std::string name1, std::function<int(int,int)> func2, std::string name2)
    : hash1(std::move(func1)), hash2(std::move(func2)), hash1_name(std::move(name1)), hash2_name(std::move(name2)) {}

int DoubleHashing::operator()(int key, int i, int table_size) const {
    return (hash1(key, table_size) + i * hash2(key, table_size)) % table_size;
}


