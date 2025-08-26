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
    OpenAddressingHashTable(int size, ProbingStrategy strategy): table_size(size), elements_count(0), probe_strategy(std::move(strategy)) {
        if (size <= 0) {
            throw std::invalid_argument("Table size must be positive");
        }
        table.resize(table_size);
    }

    int insert(int key) {
        if (elements_count >= table_size) {
            throw std::runtime_error("Hash table is full. Cannot insert key");
        }

        for (int i = 0; i < table_size; i++)
        {
            int index = probe_strategy(key, i ,table_size);


        if(!table[index].has_value()) {
            table[index] = key;
            elements_count++;
            // std::cout << "Key " << key << " inserted at index: " << index << " after tries:" << index +1 <<  std::endl;

            return i+1;
        }

        if (table[index].value() == key) {
            // std::cout << "Key " << key << " already exists. Skipping insertion" << std::endl;
            return i+1;
        }
            
        }
        return -1;

        
    }

     double getLoadFactor() {
        return (static_cast<double>(elements_count) / table_size) * 100;
    }
};