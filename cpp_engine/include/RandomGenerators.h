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
    std::vector<int> generateUniform(std::mt19937& engine, int count, double min, double max);
    std::vector<int> generate_normal(std::mt19937& engine, int count, double min, double max);
    std::vector<int> generate_clustered(std::mt19937& engine, int count, double min, double max);
    std::vector<int> generate_sequential(std::mt19937& engine, int count, double min, double max);
}

std::vector<int> generateRandomIntegers(
    int count,
    DistributionType distribution_type,
    double param1,
    double param2 = 0.0
);
