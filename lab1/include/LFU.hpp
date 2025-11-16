#ifndef LFU_HPP
#define LFU_HPP

#include "ICache.hpp"
#include <cstddef>
#include <map>

class LFUCache: public ICache{
private:
    struct Node;
    class FrequencyList;

    size_t capacity;
    size_t minFrequency;
    std::map<int, Node*> mapKey;
    std::map<int, FrequencyList*> mapFreq;
public:
    LFUCache(size_t cap);
    
    int get(int key) override; 
    void put(int key,int value)override;
    int operator[](int key) override;

    ~LFUCache();


};

#endif
