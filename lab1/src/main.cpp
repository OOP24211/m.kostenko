#include "../include/ICache.hpp"
#include "../include/LRU.hpp"
#include "../include/LFU.hpp"
#include "../include/Fibonacci.hpp"
#include <cstddef>
#include<iostream>
#include <stdexcept>
#include <string>
#include <utility>

int main(){
    // УБИРАЕМ setlocale - используем английский
    // setlocale(LC_ALL, "Russian");

    size_t capacity;
    std::cout << "Enter cache size: ";
    std::cin >> capacity;

    int choice;
    std::cout << "Choose strategy (1-LRU, 2-LFU): ";
    std::cin >> choice;

    ICache* cache;
    if (choice == 1) {
        cache = new LRUCache(capacity);
    } else {
        cache = new LFUCache(capacity);
    }

    Fibonacci fib(cache);
    std::string input;

    while(true){
        std::cout << "Enter number (or 'quit' to exit): ";
        std::cin >> input;

        if (input == "quit" || input == "q") break;

        try {
            int n = std::stoi(input);

            if (n < 0) {
                std::cout << "ERROR! Number must be non-negative!" << std::endl;
                continue;
            }         
            
            if (n > 35) {
                std::cout << "ERROR! For n > 35 (currently limited to 35)" << std::endl;
                continue;
            }

            std::pair<long long, std::string> result_pair = fib.compute(n);
            long long result = result_pair.first;
            std::string source = result_pair.second;

            std::cout << "F(" << n << ") = " << result << " " << source << std::endl;
                
        } catch (const std::invalid_argument& e){
            std::cout << "ERROR! Enter an INTEGER!" << std::endl;
        } catch (const std::out_of_range& e) {
            std::cout << "ERROR! Number is too large!" << std::endl;
        }
    }
    
    delete cache;
    return 0;
}