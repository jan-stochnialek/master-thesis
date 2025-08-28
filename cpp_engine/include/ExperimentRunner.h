#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <type_traits>
#include "RandomGenerators.h"
#include "OpenAddressingHashTable.h"

namespace detail {
    template<typename ProbingStrategy>
    std::string get_hash_name_from_probing_strategy(const ProbingStrategy& strategy);
}

template<typename ProbingStrategy>
void run_experiment(
    int table_size,
    std::vector<int> data,
    const ProbingStrategy& strategy,
    const DistributionType distribution_type,
    int run_number
);

#include "ExperimentRunner.tpp"