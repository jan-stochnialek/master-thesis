#include "OpenAddressingHashTable.h"
#include <vector>
#include <optional>
#include <stdexcept>
#include <iostream>
#include <utility>


template <typename ProbingStrategy>
OpenAddressingHashTable<ProbingStrategy>::OpenAddressingHashTable(int size, ProbingStrategy strategy)
    : table_size(size), elements_count(0), probe_strategy(std::move(strategy)) {
    if (size <= 0) {
        throw std::invalid_argument("Table size must be positive");
    }
    table.resize(table_size);
}

template <typename ProbingStrategy>
int OpenAddressingHashTable<ProbingStrategy>::insert(int key) {
    if (elements_count >= table_size) {
        throw std::runtime_error("Hash table is full. Cannot insert key");
    }
    for (int i = 0; i < table_size; i++) {
        int index = probe_strategy(key, i, table_size);
        if (!table[index].has_value()) {
            table[index] = key;
            elements_count++;
            return i + 1;
        }
        if (table[index].value() == key) {
            return i + 1;
        }
    }
    return -1;
}

template <typename ProbingStrategy>
double OpenAddressingHashTable<ProbingStrategy>::getLoadFactor() {
    return std::round((static_cast<double>(elements_count) / table_size) * 100000.0) / 1000.0;
}
