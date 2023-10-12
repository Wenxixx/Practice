//
//  LinkList.cpp
//  Practice
//
//  Created by Steven Deng on 2021/9/2.
//

#include "LinkList.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>

#pragma mark - class Huiwen
Huiwen::Huiwen(const char* str) {
    for (int i = 0; i < strlen(str); i++) {
        char c = str[i];
        SNode* node = new SNode(c);
        if (!head_) {
            head_ = node;
            tail_ = node;
        } else {
            if (head_ == tail_) {
                head_->next = node;
                node->prev = head_;
                
                tail_ = node;
            } else {
                tail_->next = node;
                node->prev = tail_;
                
                tail_ = node;
            }
        }
    }
}

bool Huiwen::isHuiwenString() {
    SNode *head = head_;
    SNode *tail = tail_;
    bool isHuiwen = true;
    while (head != tail && head->next && tail->prev) {
        if (head->c_ != tail->c_) {
            isHuiwen = false;
            break;
        }
        head = head->next;
        tail = tail->prev;
    }
    return isHuiwen;
}

ListNode* reverseLinkList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* cur = head;
    while (cur) {
        ListNode *next = cur->next;
        cur->next = prev;
        
        prev = cur;
        cur = next;
    }
    return prev;
}

bool hasCircyle(ListNode* head) {
    ListNode* current = head;
    ListNode* next = head->next;
    while (current && next) {
        if (current == next) {
            return true;
        }
        current = current->next;
        if (!next->next) {
            return false;
        }
        next = next->next->next;
    }
    
    return false;
}

ListNode* deleteDuplicates(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
   
    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    
    ListNode* cur = dummy;
    while (cur->next && cur->next->next) {
        if (cur->next->val == cur->next->next->val) {
            ListNode *next = cur->next->next;
            cur->next = next->next;
            
        } else {
            cur = cur->next;
        }
    }
    return dummy->next;
}

void reorderList(ListNode* head) {
    
    if (!head) return;
    
    // 将链表所有节点放到数组
    vector<ListNode *> list;
    ListNode *cur = head;
    while (cur) {
        list.emplace_back(cur);
        cur = cur->next;
    }
    
    // 操作双指针
    int left = 0, right = (int)list.size() -  1;
    while (left < right) {
        list[left]->next = list[right];
        left++;

        if (left == right) {
            break;
        }
        list[right]->next = list[left];
        right--;
    }
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if (!l1 && !l2) {
        return nullptr;
    }
    
    ListNode *dummy = new ListNode(0);
    ListNode *cur = dummy;
    int add = 0;
    while(l1 || l2 || add == 1) {
        int sum = add;
        if (l1) {
            sum += l1->val;
            l1 = l1->next;
        }
        
        if (l2) {
            sum += l2->val;
            l2 = l2->next;
        }
        
        cur->val = sum % 10;
        add = sum / 10;
        
        if (l1 || l2 || add == 1) {
            ListNode *newNode = new ListNode(0);
            cur->next = newNode;
            cur = cur->next;
        }
    }
    
    printLinkList(dummy);
    return dummy;
}



#pragma mark - helper
ListNode* createLinkList(vector<int> vec, bool needCycle, int pos) {
    ListNode* linkHead = nullptr;
    ListNode* p = nullptr;
    long size = vec.size();
    for (int i = 0; i < size; i++) {
        ListNode* newNode = new ListNode(vec[i]);
        if (linkHead == nullptr) {
            linkHead = newNode;
        } else {
            p->next = newNode;
        }
        p = newNode;
    }
    
    if (needCycle) {
        ListNode *temp = linkHead;
        while (pos > 0) {
            temp = temp->next;
            pos--;
        }
        p->next = temp;
    }
    return linkHead;
    
}

ListNode* createLinkList(int n, bool needCycle, int pos) {
    ListNode* linkHead = nullptr;
    ListNode* p = nullptr;
    for (int i = 0; i < n; i++) {
        ListNode* newNode = new ListNode(i);
        if (linkHead == nullptr) {
            linkHead = newNode;
        } else {
            p->next = newNode;
        }
        p = newNode;
    }
    
    if (needCycle) {
        ListNode *temp = linkHead;
        while (pos > 0) {
            temp = temp->next;
            pos--;
        }
        p->next = temp;
    }
    return linkHead;
}

void printLinkList(ListNode* head, bool hasCycle) {
    ListNode* cur = head;
    while (cur) {
        if (cur->next != nullptr) {
            printf("%d, ", cur->val);
        } else {
            printf("%d \n", cur->val);
        }
        cur = cur->next;
    }
}
