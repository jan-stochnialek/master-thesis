#pragma once

#include "MurmurHash3.h"
#include <string>
#include <cmath>

int simpleModuleHash(int key, int size);
std::string simpleModuleHashName();
int divisionHash(int key, int size);
std::string divisionHashName();
int multiplicationHash(int key, int size);
std::string multiplicationHashName();
int murmurHash3(int key, int size);
std::string murmurHash3Name();