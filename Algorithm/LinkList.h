//
//  LinkList.h
//  Practice
//
//  Created by Steven Deng on 2021/9/2.
//

#ifndef LinkList_h
#define LinkList_h
#include <stdio.h>

class Node {
public:
    Node(char value) : value_(value),
                           next_(nullptr) {}
    ~Node() {
        printf("%p \n", this);
    }
    
    int value_;
    Node* next_;
}; // struct LinkNode


class SNode {
public:
    SNode(int value) : value_(value),
                           next_(nullptr), pre_(nullptr) {}
    
    SNode(char value) : c_(value),
                           next_(nullptr), pre_(nullptr) {}
    ~SNode() {
        printf("%p \n", this);
    }
    
    int value_;
    char c_;
    SNode* next_;
    SNode* pre_;
}; // struct LinkNode


class Huiwen {
    
public:
    
    Huiwen();
    
    Huiwen(const char* str);
    
    ~Huiwen() {
        
    }

    bool isHuiwenString();
    
private:
    SNode* head_;
    SNode* tail_;
};

Node* createLinkList(int n, bool needCycle, int pos);
void printLinkList(Node* head, bool hasCycle = false);


Node* reverseLinkList(Node* head);
bool hasCircyle(Node* head);


#endif /* LinkList_h */
