cmake_minimum_required(VERSION 3.27)
project(labwork8-Engozdev
        VERSION 1.0
        DESCRIPTION "Containers for BST iterating in pre-, in- and postorder"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(bin)
add_subdirectory(lib)

enable_testing()
add_subdirectory(tests)