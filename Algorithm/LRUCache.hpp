//
//  LRUCache.hpp
//  Pratice
//
//  Created by Steven Deng on 2022/11/10.
//

#ifndef LRUCache_hpp
#define LRUCache_hpp

#include <stdio.h>
#include <unordered_map>

struct DListNode {
    DListNode() {
        value = -1;
        key = -1;
        next = nullptr;
        pre = nullptr;
    }

    ~DListNode() {
        next = nullptr;
        pre = nullptr;
    }

    int value;
    int key;
    DListNode *next;
    DListNode *pre;
};

class LRUCache {
    
public:
    LRUCache();
    LRUCache(int capacity);
    ~LRUCache();
    int get(int key);
    void put(int key, int value);
    void print();
    
private:
    DListNode* find(int key);
    void removelast();

private:
    std::unordered_map<int, int> cache_map;
    DListNode *head;
    DListNode *tail;
    
    int capacity;
    int size;
};


#endif /* LRUCache_hpp */
