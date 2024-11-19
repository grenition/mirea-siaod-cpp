//
// Created by 1111 on 03.10.2024.
//

#include "practice5_2.h"

#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include "../Extensions/extensions.h"


constexpr int patientsCount = 10000;
const std::unordered_map<int, std::string> chronic_disease_codes = {
    {001, "Atrial fibrillation"},
    {002, "Cardiac arrest"},
    {003, "Heart failure"},
    {004, "Hypertension"},
    {005, "Pericarditis"}
};
const std::vector<std::string> authors = {
    "Ivanov",
    "Pavlov",
    "Sechenov"
};

const std::string task_1_file_path = "/Users/a1111/Documents/MIREA/Semester 3/SiAOD/Practice5/5_2/task1.bin";

struct patient {
    int card_number;
    int chronic_disease_code;
    char doctor_last_name[50];
};

void print_patient(patient &pat) {
    std::cout << pat.card_number << "; " << pat.chronic_disease_code << "; " << pat.doctor_last_name << std::endl;
}

void read_file(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary);

    file.seekg(0, std::ios::end);
    const int file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    while(file.tellg() < file_size) {
        patient pat;
        file.read(reinterpret_cast<char*>(&pat), sizeof(patient));
        print_patient(pat);
    }

    file.close();
}

int search_target = 80766;

void practice5_2::task1() {
    std::unordered_map<int, patient> patients;
    while (patients.size() < patientsCount) {
        patient pat = {
            extensions::get_random_number(10000, 100000),
            extensions::get_random_element(chronic_disease_codes).first
        };
        std::strcpy(pat.doctor_last_name, extensions::get_random_element(authors).c_str());
        patients[pat.card_number] = pat;
    }

    std::ofstream outFile(task_1_file_path, std::ios::binary);
    for (auto [card_num, pat] : patients) {
        outFile.write(reinterpret_cast<char*>(&pat), sizeof(patient));
        search_target = pat.card_number;
    }

    outFile.close();
    //read_file(task_1_file_path);
}

void practice5_2::task2() {
    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream file(task_1_file_path, std::ios::binary);

    file.seekg(0, std::ios::end);
    const int file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    while(file.tellg() < file_size) {
        patient pat;
        file.read(reinterpret_cast<char*>(&pat), sizeof(patient));

        if(pat.card_number == search_target) {
            print_patient(pat);
            break;
        }
    }

    file.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Время работы: " << elapsed_seconds.count() * 1000.0  << " мс" << std::endl;
}

std::vector<std::pair<int, int>> links;
void fill_links(const std::string& file_path) {
    std::ifstream file(task_1_file_path, std::ios::binary);

    file.seekg(0, std::ios::end);
    const int file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    while(file.tellg() < file_size) {
        int id;
        file.read(reinterpret_cast<char*>(&id), sizeof(int));
        file.seekg(-sizeof(int), std::ios::cur);
        links.push_back({id, file.tellg()});
        file.seekg(sizeof(patient), std::ios::cur);
    }

    file.close();
    std::sort(links.begin(), links.end());
}

int interpolation_search(const std::vector<std::pair<int, int>>& vec, int key) {
    int low = 0;
    int high = vec.size() - 1;

    while (low <= high && key >= vec[low].first && key <= vec[high].first) {
        if (low == high) {
            if (vec[low].first == key) {
                return low;
            }
            return -1;
        }

        int pos = low + ((key - vec[low].first) * (high - low)) / (vec[high].first - vec[low].first);

        if (vec[pos].first == key) {
            return pos;
        }

        if (vec[pos].first < key) {
            low = pos + 1;
        }
        else {
            high = pos - 1;
        }
    }

    return -1;
}

patient get_patient_from_file(int position, const std::string& file_path) {
    std::ifstream file(task_1_file_path, std::ios::binary);

    patient pat;
    file.seekg(position, std::ios::beg);
    file.read(reinterpret_cast<char*>(&pat), sizeof(patient));

    file.close();
    return pat;
}

void practice5_2::task3() {
    auto start = std::chrono::high_resolution_clock::now();

    fill_links(task_1_file_path);

    int search_result = interpolation_search(links, search_target);
    int position_in_file = links[search_result].second;

    patient pat = get_patient_from_file(position_in_file, task_1_file_path);
    print_patient(pat);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Время работы: " << elapsed_seconds.count() * 1000.0  << " мс" << std::endl;
}
