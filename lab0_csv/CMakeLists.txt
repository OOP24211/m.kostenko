cmake_minimum_required(VERSION 3.10)
project(lab0_parser)

add_executable(lab0_parser 
    src/main.cpp
    src/word_reader.cpp
    src/word_frequency.cpp
    src/text_utils.cpp
)

target_include_directories(lab0_parser PRIVATE src)
