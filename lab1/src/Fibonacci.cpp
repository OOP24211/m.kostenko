#include "../include/Fibonacci.hpp"
#include "../include/ICache.hpp"
#include <string>
#include <utility>

Fibonacci::Fibonacci(ICache* c): cache(c){}

int Fibonacci::computerFibonacci(int n){
    if(n <= 0) return -1;
    if(n == 0 || n == 1) return n;
    
    int a = 0, b = 1;
    for(int i = 2; i <= n; i++){
        int next = a + b;
        a = b;
        b = next;

    }        

    return b;
}

std::pair<long long, std::string> Fibonacci::compute(int n){

    int result = (*cache)[n];
    if (result != -1) {
        return {result, "(from cache)"};
    }
    else {
        int result_compute = computerFibonacci(n);
        cache->put(n, result_compute);
        return {result_compute, "calculated"};
    }
}

Fibonacci::~Fibonacci() {
}