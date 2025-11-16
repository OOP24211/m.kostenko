#ifndef FIBONACCI_HPP
#define FIBONACCI_HPP

#include "ICache.hpp"
#include <string>
#include <utility>

class Fibonacci {
    private:
    ICache* cache;
    int computerFibonacci(int n);
public:
    Fibonacci(ICache* cache);
    std::pair<long long, std::string> compute(int n);
    ~Fibonacci();

};

#endif
