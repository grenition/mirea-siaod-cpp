#include "practice5_1.h"

#include <fstream>
#include <iostream>

#include "../Extensions/extensions.h"

void practice5_1::task_1_a() {
    std::cout << "Задание 1.а" << std::endl;
    unsigned char mask = 1;

    std::cout << "Исходная маска " << extensions::get_binary(mask) << std::endl;
    for (unsigned short int i = 0; i < 255; i += 50) {
        unsigned char x = i;
        unsigned char saved_x = x;

        x = x & (~(mask<<4));

        std::cout << "x = " << static_cast<int>(saved_x) << "; new x = " << static_cast<int>(x) << " = " << extensions::get_binary(x) << std::endl;
    }
}

void practice5_1::task_1_b() {
    std::cout << "Задание 1.б" << std::endl;
    unsigned char mask = 1;

    std::cout << "Исходная маска " << extensions::get_binary(mask) << std::endl;
    for (unsigned short int i = 0; i < 255; i += 50) {
        unsigned char x = i;
        unsigned char saved_x = x;

        x = x | (mask<<6);

        std::cout << "x = " << static_cast<int>(saved_x) << "; new x = " << static_cast<int>(x) << " = " << extensions::get_binary(x) << std::endl;
    }
}

void practice5_1::task_1_c() {
    std::cout << "Задание 1.в" << std::endl;

    unsigned int x = 25;
    const int n = sizeof(int)*8; //кол-вл разрядов (32) в int
    unsigned int mask = 1 << n - 1; //1 в старшем бите

    std::cout << "Исходная маска " << extensions::get_binary(mask) << std::endl;
    std::cout << "Результат: ";

    for(int i = 1; i <= n; i++) {
        std::cout << ((x & mask) >> n - i);
        mask = mask >> 1;
    }

    std::cout << std::endl;

    // вывод - исходное число в бинарном формате
}

void practice5_1::task_2_a() {
    std::cout << "Задание 2.а" << std::endl;

    std::cout << "Введите кол-во чисел: ";
    int count;
    std::cin >> count;
    unsigned char arrayBit = 0;

    std::cout << "Вводите числа через пробел: ";
    int num;
    for(int i = 0; i < count; i++) {
        std::cin >> num;
        arrayBit |= 1 << (7 - num);
    }
    for(int i = 0; i < 8; i++) {
        if((arrayBit & (1 << 7 - i)) != 0) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

void practice5_1::task_2_b() {
    std::cout << "Задание 2.б" << std::endl;

    std::cout << "Введите кол-во чисел: ";
    int count;
    std::cin >> count;
    unsigned long long arrayBit = 0;

    std::cout << "Вводите числа через пробел: ";
    int num;
    for(int i = 0; i < count; i++) {
        std::cin >> num;
        arrayBit |= 1ULL << (63 - num);
    }
    for(int i = 0; i < 64; i++) {
        if((arrayBit & (1ULL << 63 - i)) != 0) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

void practice5_1::task_2_c() {
    std::cout << "Задание 2.в" << std::endl;

    std::cout << "Введите кол-во чисел: ";
    int count;
    std::cin >> count;
    unsigned char arrayBit[8] = { };

    std::cout << "Вводите числа через пробел: ";
    int num;
    for(int i = 0; i < count; i++) {
        std::cin >> num;
        arrayBit[num / 8] |= 1 << (7 - (num % 8));
    }
    for(int i = 0; i < 64; i++) {
        if((arrayBit[i / 8] & (1 << 7 - (i % 8))) != 0) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

void practice5_1::task_3(){
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream fileInput("/Users/a1111/Documents/MIREA/Semester 3/SiAOD/Practice5/5_1_task3/to_sort.txt");
    unsigned char arrayBit[1250000] = { };
    std::string line;
    unsigned int num;

    while(std::getline(fileInput, line)) {
        num = stoi(line);
        arrayBit[num / 8] |= 1 << (7 - (num % 8));
    }
    fileInput.close();

    std::ofstream fileOutput("/Users/a1111/Documents/MIREA/Semester 3/SiAOD/Practice5/5_1_task3/sorted.txt");
    for(int i = 0; i < 1250000; i++) {
        for(int j = 0; j < 8; j++) {
            if((arrayBit[i / 8] & (1 << (7 - (i % 8)))) != 0) {
                fileOutput << i * 8 + j << "\n";
            }
        }
    }
    fileOutput.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Время работы сортировки: " << elapsed_seconds.count() << std::endl;

    std::cout << "Объем памяти, занимаемой программой: " << sizeof(arrayBit) / 1024.0 / 1024.0 << " МБ" << std::endl;
}


