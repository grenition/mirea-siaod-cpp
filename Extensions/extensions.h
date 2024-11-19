#ifndef EXTENSIONS_H
#define EXTENSIONS_H
#include <random>
#include <string>
#include <unordered_map>
#include <__random/random_device.h>


class extensions {
public:
    static std::string get_binary(unsigned int num);
    static std::string get_binary(unsigned char num);

    template<typename T>
    static T get_random_element(const std::vector<T>& from_vector);

    template <typename K, typename V>
    static std::pair<K, V> get_random_element(const std::unordered_map<K, V>& from_map);

    static int get_random_number(int from, int to);
    static long long get_random_number(long long from, long long to);
};

template<typename T>
T extensions::get_random_element(const std::vector<T> &from_vector) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, from_vector.size() - 1);

    return from_vector[dist(gen)];
}

template <typename K, typename V>
std::pair<K, V> extensions::get_random_element(const std::unordered_map<K, V>& from_map) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, from_map.size() - 1);

    auto it = from_map.begin();
    std::advance(it, dist(gen));

    return *it;
}

#endif //EXTENSIONS_H
