//
//  LinkList.cpp
//  Practice
//
//  Created by Steven Deng on 2021/9/2.
//

#include "LinkList.h"
#include <stdio.h>
#include <string>

Huiwen::Huiwen(const char* str) {
    for (int i = 0; i < strlen(str); i++) {
        char c = str[i];
        SNode* node = new SNode(c);
        if (!head_) {
            head_ = node;
            tail_ = node;
        } else {
            if (head_ == tail_) {
                head_->next_ = node;
                node->pre_ = head_;
                
                tail_ = node;
            } else {
                tail_->next_ = node;
                node->pre_ = tail_;
                
                tail_ = node;
            }
        }
    }
}


bool Huiwen::isHuiwenString() {
    SNode *head = head_;
    SNode *tail = tail_;
    bool isHuiwen = true;
    while (head != tail && head->next_ && tail->pre_) {
        if (head->c_ != tail->c_) {
            isHuiwen = false;
            break;
        }
        head = head->next_;
        tail = tail->pre_;
    }
    return isHuiwen;
}

Node* createLinkList(int n, bool needCycle, int pos) {
    Node* linkHead = nullptr;
    Node* p = nullptr;
    for (int i = 0; i < n; i++) {
        Node* newNode = new Node(i);
        if (linkHead == nullptr) {
            linkHead = newNode;
        } else {
            p->next_ = newNode;
        }
        p = newNode;
    }
    
    if (needCycle) {
        Node *temp = linkHead;
        while (pos > 0) {
            temp = temp->next_;
            pos--;
        }
        p->next_ = temp;
    }
    return linkHead;
}

Node* reverseLinkList(Node* head) {
    Node* newHead = nullptr;
    Node* temp = nullptr;
    while (head) {
        temp = head->next_;
        head->next_ = newHead;
        
        newHead = head;
        head = temp;
    }
    return newHead;
}

bool hasCircyle(Node* head) {
    Node* current = head;
    Node* next = head->next_;
    while (current && next) {
        if (current == next) {
            return true;
        }
        current = current->next_;
        if (!next->next_) {
            return false;
        }
        next = next->next_->next_;
    }
    
    return false;
}

void printLinkList(Node* head, bool hasCycle) {
    Node* cur = head;
    while (cur) {
        if (cur->next_ != nullptr) {
            printf("%d, ", cur->value_);
        } else {
            printf("%d \n", cur->value_);
        }
        cur = cur->next_;
    }
}

