#include <iostream>
#include <fstream>
#include "OpenAddressingHashTable/OpenAddressingHashTable.h"
#include "HashFunctions/HashFunctions.h"
#include "RandomDataGenerator/RandomGenerators.h"
#include "ExperimentRunner/ExperimentRunner.h"

int main() {

    std::ofstream csv_file("hash_table_stats.csv");

    if(!csv_file.is_open()) {
        std:: cerr << "Error opening file for writing" << std::endl;
        return 1;
    }


    csv_file << "TableSize,ProbingStrategy,HashFunction,KeyDistribution,LoadFactor,ProbeCount\n";


    std::vector<int> table_sizes = {997, 4001, 16001, 1024, 4096, 16384};
    std::vector<DistributionType> distributions = {DistributionType::Uniform, DistributionType::Normal, DistributionType::CLUSTERED, DistributionType::SEQUENTIAL};
    std::vector<std::function<int(int,int)>> hashFunctions = {simpleModuleHash, murmurHash3, divisionHash, multiplicationHash};
    std::vector<std::string> hashFunctionsNames = {simpleModuleHashName(), murmurHash3Name(), divisionHashName(), multiplicationHashName()};


for (int i = 0; i < 10; i++)
{
        for (int size : table_sizes)
    {
        for(const auto& dist : distributions) {

            int i = 0;

            for(const auto hashFunction: hashFunctions) {
                LinearProbing linear_mod(hashFunction, hashFunctionsNames[i]);
                run_experiment(size, linear_mod, dist,csv_file);
                i++;
            }

        }
    }
}



    csv_file.close();
    std::cout << "\nCSV data generation complete. File: hash_table_stats.csv" << std::endl;
    
    
}