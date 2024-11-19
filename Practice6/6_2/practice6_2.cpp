//
// Created by 1111 on 03.11.2024.
//

#include "practice6_2.h"

#include <fstream>
#include <iostream>
#include <vector>

int task1_conditions = 0;
void appendWord(std::string& word, std::string& sentence) {
    if(sentence.empty() || word == "." || word == ",") {
        task1_conditions += 3;
        sentence += word;
    }
    else {
        sentence += " " + word;
    }
}
void practice6_2::task1() {
    task1_conditions = 0;
    std::ifstream fileInput("/Users/a1111/Documents/MIREA/Semester3/SiAOD/Practice6/6_2/task1/task1_input.txt");
    std::ofstream fileOutput("/Users/a1111/Documents/MIREA/Semester3/SiAOD/Practice6/6_2/task1/task1_output.txt");

    std::string sentence;
    std::string word;
    std::string line;

    while(std::getline(fileInput, line)) {
        task1_conditions++;
        word.clear();
        sentence.clear();
        line += ' ';
        for(int i = 0; i < line.size(); i++) {
            task1_conditions++;
            if(line[i] == ' ') {
                task1_conditions++;
                if(word.empty()) {
                    task1_conditions++;
                    continue;
                }
                if(word.back() == '.') {
                    task1_conditions++;
                    appendWord(word, sentence);
                    fileOutput << sentence << "  ";
                    sentence.clear();
                }
                else
                    appendWord(word, sentence);
                word.clear();
            }
            else {
                word += line[i];
            }
        }
    }

    fileInput.close();
    fileOutput.close();

    std::cout << "Task1 conditions count: " << task1_conditions << std::endl;
}

int task2_conditions = 0;
void get_prefix_function_in_file(const std::string& path, bool showContent) {
    std::ifstream fileInput(path);
    std::string line;
    std::getline(fileInput, line);

    std::vector<int> p(line.size(), 0);
    for(int i = 1; i < line.size(); i++) {
        task2_conditions++;
        int k = p[i - 1];
        while(k > 0 && line[k] != line[i]) {
            task2_conditions += 2;
            k = p[k - 1];
        }
        if(line[k] == line[i]) {
            task2_conditions++;
            k += 1;
        }
        p[i] = k;
    }

    std::cout << "Conditions count: " << task2_conditions << std::endl;

    if(showContent) {
        for(int i = 0; i < p.size(); i++) {
            std::cout << p[i];
        }
        std::cout << std::endl;
    }

    fileInput.close();
}

void practice6_2::task2() {
    std::string file_base = "/Users/a1111/Documents/MIREA/Semester3/SiAOD/Practice6/6_2/task2/task2_input.txt";
    std::string file_best = "/Users/a1111/Documents/MIREA/Semester3/SiAOD/Practice6/6_2/task2/task2_input_best.txt";
    std::string file_worst = "/Users/a1111/Documents/MIREA/Semester3/SiAOD/Practice6/6_2/task2/task2_input_worst.txt";
    std::string file_base_s = "/Users/a1111/Documents/MIREA/Semester3/SiAOD/Practice6/6_2/task2/task2_input_s.txt";
    std::string file_best_s = "/Users/a1111/Documents/MIREA/Semester3/SiAOD/Practice6/6_2/task2/task2_input_best_s.txt";
    std::string file_worst_s = "/Users/a1111/Documents/MIREA/Semester3/SiAOD/Practice6/6_2/task2/task2_input_worst_s.txt";

    std::cout << "Best case for small file" << std::endl;
    get_prefix_function_in_file(file_best_s, true);

    std::cout << "Average case for small file" << std::endl;
    get_prefix_function_in_file(file_worst_s, true);

    std::cout << "Worst case for small file" << std::endl;
    get_prefix_function_in_file(file_base_s, true);

    std::cout << "Best case for big file" << std::endl;
    get_prefix_function_in_file(file_best, false);

    std::cout << "Average case for big file" << std::endl;
    get_prefix_function_in_file(file_worst, false);

    std::cout << "Worst case for big file" << std::endl;
    get_prefix_function_in_file(file_base, false);
}


