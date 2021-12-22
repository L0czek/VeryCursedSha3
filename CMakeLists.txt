cmake_minimum_required(VERSION 3.3)

project (Keccak)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(sha3
    src/multi_array.hpp
    src/template_utils.hpp
    src/main.cc)


