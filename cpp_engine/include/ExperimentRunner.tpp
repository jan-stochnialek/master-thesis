#include "ExperimentRunner.h"
#include <climits>

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
    std::vector<int> data,
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
        break;
    case DistributionType::SEQUENTIAL:
        dist_name = "Sequential";
        break;
    case DistributionType::Normal:
        dist_name = "Normal";
        break;
    case DistributionType::CLUSTERED:
        dist_name ="Clustered";
        break;
    default:
        break;
    }

    std::cout << "Running: Size= " << table_size << ", Strategy= " << strategy_name << ", Hash=" << hash_name << ", Distribution= " << dist_name << std::endl;

    OpenAddressingHashTable<ProbingStrategy> table(table_size, strategy);

    int i = 0;

    while (i < data.size()) {
        try {
            double loadFactorBefore = table.getLoadFactor();
            int probe_count = table.insert(data[i]);

            if (probe_count > 0) {
                file << table_size << "," << strategy_name << "," << hash_name << "," << dist_name << "," << loadFactorBefore << "," << probe_count << "\n";
            }
        } catch (const std::runtime_error& e) {
            std::cout << "      -> Info: Table is full.";
            break;
        }
        i++;
    }
}
