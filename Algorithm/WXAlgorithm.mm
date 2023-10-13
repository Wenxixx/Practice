//
//  WXAlgorithm.m
//  Pratice
//
//  Created by Steven Deng on 2023/9/19.
//

#import "WXAlgorithm.h"
#include "LinkList.h"
#include "LRUCache.hpp"
#include "String.hpp"
#include "Tree.hpp"
#include "DoublePointer.hpp"
#include <vector>

@implementation WXAlgorithm

#pragma mark - LinkList

- (void)testLRUCache {
    LRUCache *cache = new LRUCache(10);
    for (int i = 0; i < 10; i++) {
        cache->put(i+1, i+1);
    }
    cache->print();
    
    cache->put(11, 11);
    cache->print();
    
    cache->put(1, 100);
    cache->print();
    
    cache->get(2);
    cache->print();
    
    cache->get(8);
    cache->print();
    
    delete cache;
    cache = nullptr;
}

- (void)testHuiwen {
    Huiwen *h = new Huiwen("2");
    printf("isHuiwen: %d \n", h->isHuiwenString());
    
    Huiwen *hh = new Huiwen("22");
    printf("isHuiwen: %d \n", hh->isHuiwenString());
    
    Huiwen *hhg = new Huiwen("232");
    printf("isHuiwen: %d \n", hhg->isHuiwenString());
    
    Huiwen *hhgg = new Huiwen("122");
    printf("isHuiwen: %d \n", hhgg->isHuiwenString());
    
    Huiwen *hhggg = new Huiwen("1221");
    printf("isHuiwen: %d \n", hhggg->isHuiwenString());
    
    Huiwen *hhgggg = new Huiwen("12521");
    printf("isHuiwen: %d \n", hhgggg->isHuiwenString());
}

- (void)testCycleLinkList {
    // 构建链表 - 判断链表是否成环（快慢指针）
    ListNode* linkHead = createLinkList(10, false, 0);
    bool hasCycle = hasCircyle(linkHead);
    printf("hasCycle : %d \n", hasCycle);
    
    linkHead = createLinkList(10, true, 2);
    hasCycle = hasCircyle(linkHead);
    printf("hasCycle : %d \n", hasCycle);
}

- (void)testReverseLinkList {
    bool hasCycle = false;
    ListNode* linkHead = createLinkList(10, hasCycle, 3);
    // 打印链表
    if (!hasCycle) {
        // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, ...
        printLinkList(linkHead);
    }
    // 反转链表
    linkHead = reverseLinkList(linkHead);
    // 打印链表
    if (!hasCycle) {
        // 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 9, ...
        printLinkList(linkHead);
    }
    
    hasCycle = true;
    ListNode* linkHead2 = createLinkList(10, hasCycle, 3);
    // 打印链表
    if (!hasCycle) {
        // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 2, ...
        printLinkList(linkHead2);
    }
    // 反转链表
    linkHead2 = reverseLinkList(linkHead2);
    // 打印链表
    if (!hasCycle) {
        // 0, 1, 2, 9, 8, 7, 6, 5, 4, 3, 2, ...
        printLinkList(linkHead2);
    }
}

- (void)testDeleteDuplicates {
    
    std::vector<int> list({1,2,3,3,4,4,5});
    ListNode* linkHead = createLinkList(list, false, 3);
    
    printLinkList(linkHead);
    
    deleteDuplicates(linkHead);
}

- (void)testReorderLinklist
{
    
}

- (void)testAddTwoNumbers
{
    std::vector<int> list1({2,4,5});
    ListNode *l1 = createLinkList(list1, false, 0);
    
    std::vector<int> list2({5,6,4});
    ListNode *l2 = createLinkList(list2, false, 0);

    addTwoNumbers(l1, l2);
}

#pragma mark - String

- (void)tesStack {
    string path("/home/");
    string result = simplifyPath(path);
}

- (void)testReverseWords
{
    string str("  hello world  ");
    string result = reverseWords(str);
}

- (void)testLengthOfLongestSubstring {
    string s("tmmzuxt");
    int len = lengthOfLongestSubstring(s);
}

#pragma mark - Tree

- (void)testTree {
    TreeNode *root = new TreeNode(5);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    
    zigzagLevelOrder(root);
}


- (void)testIncreasingTriplet {
//    vector<int> vec({0,4,2,1,0,-1,-3});
//    increasingTriplet(vec);
}

@end
