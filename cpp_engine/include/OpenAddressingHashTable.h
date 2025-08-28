#pragma once

#include <vector>
#include <optional>
#include <stdexcept>
#include <iostream>
#include <utility>
#include "ProbingStrategies.h"

template <typename ProbingStrategy>
class OpenAddressingHashTable {
private:
    std::vector<std::optional<int>> table;
    int table_size;
    int elements_count;
    ProbingStrategy probe_strategy;

public:
    OpenAddressingHashTable(int size, ProbingStrategy strategy);
    int insert(int key);
    double getLoadFactor();
};

#include "OpenAddressingHashTable.tpp"