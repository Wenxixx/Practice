//
//  LinkList.h
//  Practice
//
//  Created by Steven Deng on 2021/9/2.
//

#ifndef LinkList_h
#define LinkList_h
#include <stdio.h>
#include <string>

using namespace std;

class ListNode {
public:
    ListNode(char value) : val(value),
                           next(nullptr) {}
    ~ListNode() {
        printf("%p \n", this);
    }
    
    int val;
    ListNode* next;
}; // struct LinkNode


class SNode {
public:
    SNode(int value) : val(value),
                           next(nullptr), prev(nullptr) {}
    
    SNode(char value) : c_(value),
                           next(nullptr), prev(nullptr) {}
    ~SNode() {
        printf("%p \n", this);
    }
    
    int val;
    char c_;
    SNode* next;
    SNode* prev;
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

#pragma mark - algorithm
// leetcode#206 翻转链表
ListNode* reverseLinkList(ListNode* head);

// 判断链表是否有环
bool hasCircyle(ListNode* head);

// leetcode#82 删除排序链表中重复元素II
ListNode* deleteDuplicates(ListNode* head);

// leetcode#143 重排链表
void reorderList(ListNode* head);

// leetcode#61 旋转链表
ListNode* rotateRight(ListNode* head, int k);

// leetcode#2 两数相加
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);


#pragma mark - helper
ListNode* createLinkList(int n, bool needCycle, int pos);
ListNode* createLinkList(vector<int> vec, bool needCycle, int pos);
void printLinkList(ListNode* head, bool hasCycle = false);

#endif /* LinkList_h */
