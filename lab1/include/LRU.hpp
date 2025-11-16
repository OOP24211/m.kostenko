#ifndef LRU_HPP
#define LRU_HPP

#include "ICache.hpp"
#include<map>
#include <cstddef>

class LRUCache: public ICache{
private:
    struct Node;
    class LinkedList;

    size_t capacity;
    std::map<int, Node*> mapCache;
    LinkedList* list;
public:
    LRUCache(size_t capacity);
    ~LRUCache();

    int get(int key) override;
    void put(int key, int value) override;
    int operator[](int key) override;

};

#endif
