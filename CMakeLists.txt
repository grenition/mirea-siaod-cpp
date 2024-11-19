cmake_minimum_required(VERSION 3.29)
project(SiAOD)

set(CMAKE_CXX_STANDARD 20)

add_executable(SiAOD main.cpp
        Practice5/practice5_1.cpp
        Practice5/practice5_1.h
        Extensions/Extensions.cpp
        Extensions/Extensions.h
        Practice5/practice5_2.cpp
        Practice5/practice5_2.h
        Practice6/6_1/hash_table/num_hash_table.h
        Practice6/6_1/practice6_1.cpp
        Practice6/6_1/practice6_1.h
        Practice6/6_2/practice6_2.cpp
        Practice6/6_2/practice6_2.h
)
