#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <type_traits>
#include "../RandomDataGenerator/RandomGenerators.h"

namespace detail {
    template<typename ProbingStrategy>
    std::string get_hash_name_from_probing_strategy(const ProbingStrategy& strategy) {
        if constexpr (std::is_same_v<ProbingStrategy, DoubleHashing>){
            return strategy.hash1_name + "/" + strategy.hash2_name;
        }
        else {
            return strategy.hash_function_name;
        }
    }
}

template<typename ProbingStrategy>
void run_experiment(
    int table_size,
    const ProbingStrategy& strategy,
    const DistributionType distribution_type,
    std::ofstream& file    
) {
    const std::string& strategy_name = strategy.name;
    std::string hash_name = detail::get_hash_name_from_probing_strategy(strategy);
    std::string dist_name;
    double param1, param2;

    switch (distribution_type)
    {
    case DistributionType::Uniform:
        dist_name = "Uniform";
        param1 = INT_MIN;
        param2 = INT_MAX;
        break;
            case DistributionType::SEQUENTIAL:
        dist_name = "Sequential";
        param1 = INT_MIN;
        param2 = INT_MAX;
        break; 
        case DistributionType::Normal:
        dist_name = "Normal";
        param1 = INT_MIN;
        param2 = INT_MAX;
        break;
            case DistributionType::CLUSTERED:
        dist_name ="Clustered";
        param1 = INT_MIN;
        param2 = INT_MAX;
        break;

    default:
        break;
    }

    std::cout << "Running: Size= " << table_size << ", Strategy= " << strategy_name << ", Hash=" << hash_name << ", Distribution= " << dist_name << std::endl;

    OpenAddressingHashTable<ProbingStrategy> table(table_size, strategy);

    std::vector<int> data = generateRandomIntegers(table_size * 20, distribution_type, param1, param2);
    // std::ofstream outFile("" + std::to_string(table_size) + "_" + dist_name + "_output.csv"); // Open file


    // for (size_t i = 0; i < data.size(); ++i) {
    //     outFile << data[i] << "\n";
    // }

    // outFile << std::endl; // Optional: end line

    // outFile.close(); // Close file
    
    int i = 0;


    while (table.getLoadFactor() < 95) {
        try {
        double loadFactorBefore = table.getLoadFactor();
        int probe_count = table.insert(data[i]);

        if (probe_count > 0) {
            file << table_size << "," << strategy_name << "," << hash_name << "," << dist_name << "," << loadFactorBefore << "," << probe_count << "\n";
        } }
        catch (const std::runtime_error& e) {
            std::cout << "      -> Info: Table is full.";
            break;
        }
        i++;
    }
}