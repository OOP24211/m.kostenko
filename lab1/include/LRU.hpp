#ifndef LRU_HPP
#define LRU_HPP

#include "ICache.hpp"
#include <list>
#include <unordered_map>
#include <cstddef>

class LRUCache: public ICache {
private:
    size_t capacity;
    //начало-последний использованный элемент
    std::list<std::pair<int, int>> lruList;

    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> mapCache;
    
public:
    LRUCache(size_t capacity);
    ~LRUCache();
    
    int get(int key) override;
    void put(int key, int value) override;
    int operator[](int key) override;
};

#endif
