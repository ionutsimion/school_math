cmake_minimum_required(VERSION 3.23)
project(school_math)

set(CMAKE_CXX_STANDARD 17)

add_executable(school_math main.cpp ebnf_parser.cpp ebnf_parser.hpp)
