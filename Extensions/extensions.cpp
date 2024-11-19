#include "extensions.h"
#include <iostream>
#include <map>
#include <numeric>
#include <random>

std::string extensions::get_binary(unsigned int num) {
    std::string result;
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        result += std::to_string(((num >> i) & 1 ));
    }
    return result;
}

std::string extensions::get_binary(unsigned char num) {
    std::string result;
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        result += std::to_string(((num >> i) & 1 ));
    }
    return result;
}

int extensions::get_random_number(int from, int to) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(from, to - 1);

    return dist(gen);
}

long long extensions::get_random_number(long long from, long long to) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dist(from, to - 1);

    return dist(gen);
}