//
//  LRUCache.cpp
//  Pratice
//
//  Created by Steven Deng on 2022/11/10.
//

#include "LRUCache.hpp"


LRUCache::LRUCache() : capacity(0), size(0) {
    head = new ListNode();
    tail = new ListNode();
                            
    head->next = tail;
    head->pre = nullptr;
                            
    tail->pre = head;
    tail->next = nullptr;
}

LRUCache::LRUCache(int capacity) : capacity(capacity), size(0) {
    head = new ListNode();
    tail = new ListNode();
    head->next = tail;
    head->pre = nullptr;
    
    tail->pre = head;
    tail->next = nullptr;
}

LRUCache::~LRUCache() {
    ListNode *pre = head->next;
    while (head) {
        delete head;
        head = pre;
        if (pre) {
            pre = pre->next;
        }
    }
}

int LRUCache::get(int key) {
    if (!cache_map.count(key)) {
        return -1;
    }
    
    // 查找节点
    ListNode *temp = find(key);
    
    (temp->pre)->next = temp->next;
    (temp->next)->pre = temp->pre;
    
    temp->next = head->next;
    head->next->pre = temp;
    
    temp->pre = head;
    head->next = temp;
    
    return cache_map[key];
}

void LRUCache::put(int key, int value) {

    if (!cache_map.count(key)) {
        if (size == capacity) {
            removelast();
        }
        
        ListNode *newNode = new ListNode();
        newNode->key = key;
        newNode->value = value;
        
        size ++;
        
        // 新节点 关联 原来头节点
        newNode->next = head->next;
        head->next->pre = newNode;
        
        // 设置新节点为头节点
        newNode->pre = head;
        head->next = newNode;
        
    } else {
        ListNode *temp = find(key);
        
        temp->pre->next = temp->next;
        temp->next->pre = temp->pre;
        
        temp->next = head->next;
        head->next->pre = temp;
        
        temp->pre = head;
        head->next = temp;
    }
    
    cache_map[key] = value;
}

ListNode* LRUCache::find(int key) {
    ListNode *temp = head->next;
    while (temp) {
        if (temp->key == key) {
            break;
        }
        temp = temp->next;
    }
    return temp;
}


void LRUCache::removelast() {
    if (size <= 0) {
        return;
    }
    
    ListNode* temp = tail->pre;
    
    // hashMap中删除k-v
    auto iter = cache_map.find(temp->key);
    if (iter != cache_map.end()) {
        cache_map.erase(iter);
    }
    
    // 链表中删除
    temp->pre->next = temp->next;
    temp->next->pre = temp->pre;
    temp->next = nullptr;
    temp->pre = nullptr;
    delete temp;
    temp = nullptr;
    
    size--;
}

void LRUCache::print() {
    ListNode *p = head->next;
    printf("list = [head->");
    while (p->next) {
        printf("%d->", p->key);
        p = p->next;
    }
    printf("tail] \n");
}
