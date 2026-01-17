#include "../include/LRU.hpp"
#include <list>
#include <unordered_map>
#include <iostream>

LRUCache::LRUCache(size_t cap): capacity(cap) {
    if (capacity == 0) {
        std::cout << "CACHE DISABLED" << std::endl;
    }
}

int LRUCache::get(int key) {
    if (capacity == 0) return -1;
    
    auto it = mapCache.find(key);
    if (it == mapCache.end()) {
        return -1;
    }
    
    lruList.splice(lruList.begin(), lruList, it->second);
    return it->second->second;
}

void LRUCache::put(int key, int value) {
    if (capacity == 0) return;
    
    auto it = mapCache.find(key);
    
    if (it != mapCache.end()) {
        // Ключ уже существует - обновляем значение и перемещаем в начало
        it->second->second = value;
        lruList.splice(lruList.begin(), lruList, it->second);
    } else {
        // Новый ключ
        if (mapCache.size() >= capacity) {
            auto last = lruList.end();
            last--;
            mapCache.erase(last->first);
            lruList.pop_back();
        }
        
        lruList.push_front({key, value});
        mapCache[key] = lruList.begin();
    }
}

int LRUCache::operator[](int key) {
    return get(key);
}

LRUCache::~LRUCache() {
}
