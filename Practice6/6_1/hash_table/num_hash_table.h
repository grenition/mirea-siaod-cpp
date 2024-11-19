#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <sstream>
#include <vector>


template<typename TValue>
class num_hash_table {
private:
    std::vector<std::pair<long long, TValue>> table;
    const int minTableSize = 10;
    int tableSize = 10;
    int elementsCount = 0;

    bool needExpand() const {
        return static_cast<float>(elementsCount) / tableSize > 0.75;
    }

    bool needCollaplse() const {
        if(tableSize <= minTableSize) return false;
        return static_cast<float>(elementsCount) / (static_cast<float>(tableSize) / 2) <= 0.75;
    }

    int hash(long long key) const {
        return ((key % tableSize) + tableSize) % tableSize;
    }

    int attemptHash(long long key, int attempt) {
        return (hash(key) + 5 * attempt + 3 * attempt * attempt) % tableSize;
    }

    void resize(int newSize) {
        int oldSize = tableSize;
        tableSize = newSize;

        std::vector<std::pair<long long, TValue>> oldTable(table);
        std::vector<std::pair<long long, TValue>> newTable(tableSize, std::make_pair(-1, TValue()));
        table = std::move(newTable);
        elementsCount = 0;

        for (int i = 0; i < oldSize; i++) {
            if(oldTable[i].first != -1)
                insert(oldTable[i].first, oldTable[i].second);
        }

    }

public:
    num_hash_table() {
        std::vector<std::pair<long long, TValue>> newTable(tableSize, std::make_pair(-1, TValue()));
        table = std::move(newTable);
    }

    ~num_hash_table() {
        table.clear();
    }

    void insert(long long key, TValue value) {
        if (needExpand())
            resize(tableSize * 2);

        int index = hash(key);
        int attempt = 0;
        std::pair<long long, TValue> newPair = std::make_pair(key, value);

        if (table[index].first == -1 || table[index].first == key) {
            if (table[index].first == -1)
                elementsCount++;
            table[index] = newPair;
            return;
        }

        do {
            attempt++;
            index = attemptHash(key, attempt);
        } while (table[index].first != -1 && table[index].first != key);

        if (table[index].first == -1)
            elementsCount++;
        table[index] = newPair;
    }

    void remove(long long key) {
        if (elementsCount == 0) return;

        int attempt = 0;
        int maxAttempts = tableSize;
        int index = attemptHash(key, attempt);

        while (table[index].first != key && attempt < maxAttempts) {
            attempt++;
            index = attemptHash(key, attempt);
        }

        if (table[index].first != key)
            return;

        table[index].first = -1;
        table[index].second = TValue();
        elementsCount--;


        if (needCollaplse())
            resize(tableSize / 2);
        else
            resize(tableSize);
    }

    TValue get(long long key) {
        if (elementsCount == 0) return TValue();

        int attempt = 0;
        int maxAttempts = tableSize;
        int index = attemptHash(key, attempt);

        while (table[index].first != key && attempt < maxAttempts) {
            attempt++;
            index = attemptHash(key, attempt);
        }

        if (table[index].first != key)
            return TValue();

        return table[index].second;
    }

    std::string to_string() {
        std::stringstream ss;
        ss << "Key" << '\t' << "Data" << std::endl;
        for (int i = 0; i < tableSize; i++) {
            if(table[i].first == -1)
                continue;
            ss << table[i].first << '\t' << table[i].second << std::endl;
        }
        return ss.str();
    }
};


#endif //HASH_TABLE_H
