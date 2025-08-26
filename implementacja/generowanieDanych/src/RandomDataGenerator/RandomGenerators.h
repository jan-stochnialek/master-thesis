#pragma once

#include <vector>
#include <random>
#include <stdexcept>

enum class DistributionType {
    Uniform,
    Normal,
    CLUSTERED,
    SEQUENTIAL
};


namespace details {

    inline std::vector<int> generateUniform(std::mt19937& engine, int count, double min, double max) {
        if (min > max) {
            throw std::invalid_argument("For Uniform distribution param 1 (min) cannot be greater than param 2 (max)");
        }

        std::uniform_int_distribution<int> distribution(static_cast<int>(min), static_cast<int>(max));

        std::vector<int> random_numbers;
        random_numbers.reserve(count);

        for (int i = 0; i < count; ++i)
        {
            random_numbers.push_back(distribution(engine));
        }
        return random_numbers;
        
    }

        inline std::vector<int> generate_normal(std::mt19937& engine, int count, double min, double max) {
        double mean = min + (max - min) / 2.0;
        double stddev = (max - min) / 6.0;
        std::normal_distribution<double> dist(mean, stddev);

        std::vector<int> numbers;
        numbers.reserve(count);

        while(numbers.size() < count) {
            int num = static_cast<int>(round(dist(engine)));
            if( num >= min && num <= max) {
                numbers.push_back(num);
            }
        }
        return numbers;
        
    }

        inline std::vector<int> generate_clustered(std::mt19937& engine, int count, double min, double max) {
        double range = static_cast<double>(max-min);

        std::vector<double> means = {
            min + range * 0.1,
            min + range * 0.5,
            min + range * 0.9
        };
        double stddev = range / 50.0;

        std::vector<std::normal_distribution<double>> distributions;
        for (double mean: means){
            distributions.emplace_back(mean, stddev);
        }

        std::uniform_int_distribution<size_t> cluster_picker(0, distributions.size() -1);
        std::vector<int> numbers;
        numbers.reserve(count);

        while (numbers.size() < count) 
        {
            size_t cluster_index = cluster_picker(engine);
            int num = static_cast<int>(round(distributions[cluster_index](engine)));

            if(num >= min && num <= max) {
                numbers.push_back(num);
            }
        }
        return numbers;
        
    }


        inline std::vector<int> generate_sequential(std::mt19937& engine, int count, double min, double max) {
            std::vector<int> numbers;
            numbers.reserve(count);

            for(size_t i = 0; i < count; i++) {
                long long current_val = static_cast<long long>(min) + i;
                if(current_val > max) {
                    current_val = min + (current_val - max - 1);
                }
                numbers.push_back(static_cast<int>(current_val));
            }

            return numbers;
        
    }

}

inline std::vector<int> generateRandomIntegers(
    int count,
    DistributionType distribution_type,
    double param1,
    double param2 = 0.0
) {
    static std::random_device rd;
    static std::mt19937 engine(rd());



    switch (distribution_type) {
        case DistributionType::Uniform: {
            return details::generateUniform(engine,count,param1,param2);
            break;
        }
        case DistributionType::Normal: {
            return details::generate_normal(engine,count,param1,param2);
            break;
        }
        case DistributionType:: CLUSTERED: {
                        return details::generate_clustered(engine,count,param1,param2);
            break;
        }
         case DistributionType::SEQUENTIAL: {
                        return details::generate_sequential(engine,count,param1,param2);
            break;
        }

    }
}
