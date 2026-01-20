#include <gtest/gtest.h>
#include "LRU.hpp"
#include "LFU.hpp"

TEST(LRUCacheTest, BasicOperations) {
    LRUCache cache(2);
    
    cache.put(1, 100);
    cache.put(2, 200);
    
    EXPECT_EQ(cache.get(1), 100);
    EXPECT_EQ(cache.get(2), 200);
    EXPECT_EQ(cache.get(3), -1);
}

TEST(LRUCacheTest, Eviction) {
    LRUCache cache(2);
    
    cache.put(1, 100);
    cache.put(2, 200);
    cache.put(3, 300); // Должен вытеснить 1
    
    EXPECT_EQ(cache.get(1), -1);
    EXPECT_EQ(cache.get(2), 200);
    EXPECT_EQ(cache.get(3), 300);
}

TEST(LFUCacheTest, BasicOperations) {
    LFUCache cache(2);
    
    cache.put(1, 100);
    cache.put(2, 200);
    
    EXPECT_EQ(cache.get(1), 100);
    EXPECT_EQ(cache.get(2), 200);
}