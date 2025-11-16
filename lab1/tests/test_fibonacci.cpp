#include <gtest/gtest.h>
#include "Fibonacci.hpp"
#include "LFU.hpp"

TEST(FibonacciTest, BasicValues) {
    LFUCache cache(10);
    Fibonacci fib(&cache);
    
    auto [result1, source1] = fib.compute(0);
    EXPECT_EQ(result1, 0);
    
    auto [result2, source2] = fib.compute(1);
    EXPECT_EQ(result2, 1);
    
    auto [result3, source3] = fib.compute(5);
    EXPECT_EQ(result3, 5);
}

TEST(FibonacciTest, CacheUsage) {
    LFUCache cache(3);
    Fibonacci fib(&cache);
    
    // Первый вызов - вычисление
    auto [result1, source1] = fib.compute(5);
    EXPECT_EQ(source1, "вычислен");
    
    // Второй вызов - из кэша
    auto [result2, source2] = fib.compute(5);
    EXPECT_EQ(source2, "(из кэша)");
}