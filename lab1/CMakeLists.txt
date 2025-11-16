cmake_minimum_required(VERSION 3.10)
project(cache)

set(CMAKE_CXX_STANDARD 11)

# Указываем пути к заголовочным файлам
include_directories(include)

# Основное приложение
add_executable(cache_app
    src/main.cpp
    src/Fibonacci.cpp
    src/LFU.cpp
    src/LRU.cpp
)

# Google Test (опционально)
find_package(GTest QUIET)

if(GTest_FOUND)
    message("Google Test found - building tests")
    
    add_executable(tests
        tests/test_fibonacci.cpp
        tests/test_cache.cpp
        src/Fibonacci.cpp
        src/LFU.cpp
        src/LRU.cpp
    )
    
    target_include_directories(tests PRIVATE include)
    target_link_libraries(tests GTest::gtest GTest::gtest_main)
    
    enable_testing()
    add_test(NAME AllTests COMMAND tests)
else()
    message("Google Test not found - skipping tests")
endif()