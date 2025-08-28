#include <iostream>
#include <fstream>
#include "OpenAddressingHashTable.h"
#include "HashFunctions.h"
#include "RandomGenerators.h"
#include "ExperimentRunner.h"

int main() {
 
    std::ofstream csv_file("hash_table_stats.csv");

    if(!csv_file.is_open()) {
        std:: cerr << "Error opening file for writing" << std::endl;
        return 1;
    }


    csv_file << "TableSize,ProbingStrategy,HashFunction,KeyDistribution,LoadFactor,ProbeCount\n";


    std::vector<int> table_sizes = {16001, 16384, 16000};
    // std::vector<int> table_sizes = {997, 1024,1000};
    std::vector<DistributionType> distributions = {DistributionType::Uniform, DistributionType::Normal, DistributionType::CLUSTERED, DistributionType::SEQUENTIAL};
    std::vector<std::function<int(int,int)>> hashFunctions = {simpleModuleHash, divisionHash, multiplicationHash, murmurHash3};
    std::vector<std::string> hashFunctionsNames = {simpleModuleHashName(), divisionHashName(), multiplicationHashName(), murmurHash3Name()};

for (int i = 0; i < 5; i++)
{
    for(const auto& dist : distributions) {
        for (int size : table_sizes)
        {
            std::vector<int> data = generateRandomIntegers(size, dist, INT_MIN, INT_MAX);

            // Save generated data to CSV file
            // std::string dist_name;
            // switch(dist) {
            //     case DistributionType::Uniform: dist_name = "Uniform"; break;
            //     case DistributionType::Normal: dist_name = "Normal"; break;
            //     case DistributionType::CLUSTERED: dist_name = "Clustered"; break;
            //     case DistributionType::SEQUENTIAL: dist_name = "Sequential"; break;
            //     default: dist_name = "Unknown";
            // }
            // std::string data_filename = std::to_string(size) + "_" + dist_name + "_data.csv";
            // std::ofstream data_file(data_filename);
            // if(data_file.is_open()) {
            //     for(const auto& val : data) {
            //         data_file << val << "\n";
            //     }
            //     data_file.close();
            // } else {
            //     std::cerr << "Error opening file " << data_filename << " for writing" << std::endl;
            // }

            int j = 0;
            for(const auto& hashFunction1 : hashFunctions) {
                LinearProbing linear_probing(hashFunction1, hashFunctionsNames[j]);
                run_experiment(size, data, linear_probing, dist, csv_file);
                QuadraticProbing quadratic_probing(hashFunction1, hashFunctionsNames[j]);
                run_experiment(size, data, quadratic_probing, dist, csv_file);
                int k = 0;
                for(const auto& hashFunction2 : hashFunctions) {
                    if(hashFunctionsNames[j] != hashFunctionsNames[k]) {
                        DoubleHashing double_hash(hashFunction1, hashFunctionsNames[j], hashFunction2, hashFunctionsNames[k]);
                        run_experiment(size, data, double_hash, dist, csv_file);
                    }
                    k++;
                }
                j++;
            }

        }
    }
}



    csv_file.close();
    std::cout << "\nCSV data generation complete. File: hash_table_stats.csv" << std::endl;
    
    
}