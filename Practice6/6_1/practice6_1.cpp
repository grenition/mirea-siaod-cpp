//
// Created by 1111 on 30.10.2024.
//

#include "practice6_1.h"

#include <iostream>

#include "../../Extensions/extensions.h"

#include <map>
#include <ostream>

#include "hash_table/num_hash_table.h"

const std::vector<std::string> authors = {
    "Ivanov",
    "Pavlov",
    "Sechenov"
};

const std::vector<std::string> titles = {
    "Anna Karenina",
    "To Kill a Mockingbird",
    "The Great Gatsby",
    "One Hundred Years of Solitude",
    "A Passage to India",
    "Invisible Man"
};

struct book {
    long long isbn;
    std::string author;
    std::string title;

    book(const long long isbn, const std::string& author, const std::string& title) {
        this->isbn = isbn;
        this->author = author;
        this->title = title;
    }
    book(const std::string& author, const std::string& title) {
        this->isbn = extensions::get_random_number(100000000000LL, 1000000000000LL);
        this->author = author;
        this->title = title;
    }
    book() {
        this->isbn = extensions::get_random_number(100000000000LL, 1000000000000LL);
        this->author = extensions::get_random_element(authors);
        this->title = extensions::get_random_element(titles);
    }

    friend std::ostream& operator<<(std::ostream& os, const book& book) {
        os << "ISBN: " << book.isbn << "; Author: " << book.author << "; Title: " << book.title;
        return os;
    }
};


void practice6_1::run_task() {
    num_hash_table<book> hash_table;
    int count;

    std::cout << "Please enter a command: insert; remove; print; exit" << std::endl;
    while (true) {
        std::string command;
        std::cin >> command;

        if(command == "insert") {
            std::string subCommand;
            std::cin >> subCommand;

            std::vector<book> books;
            if(subCommand == "random") {
                std::cin >> count;
                for(int i = 0; i < count; i++) {
                    books.emplace_back();
                }
            }
            else {
                long long key;
                std::string author;
                std::string title;
                std::cin >> key;
                std::cin >> author;
                std::cin >> title;
                std::cin >> count;

                for(int i = 0; i < count; i++) {
                    books.emplace_back(key, author, title);
                }
            }

            for(int i = 0; i < books.size(); i++) {
                hash_table.insert(books[i].isbn, books[i]);
            }
        }
        else if(command == "remove") {
            long long key;
            std::cin >> key;
            hash_table.remove(key);
        }
        else if (command == "print") {
            std::cout << hash_table.to_string();
        }
        else if (command == "exit") {
            return;
        }
        else {
            std::cout << "Invalid command" << std::endl;
        }

        std::cin.clear();
    }
}
