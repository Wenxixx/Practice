//
//  WXAlgorithm.m
//  Pratice
//
//  Created by Steven Deng on 2023/9/19.
//

#import "WXAlgorithm.h"
#include "LinkList.h"
#include "LRUCache.hpp"

@implementation WXAlgorithm

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
    Node* linkHead = createLinkList(10, false, 0);
    bool hasCycle = hasCircyle(linkHead);
    printf("hasCycle : %d \n", hasCycle);
    
    linkHead = createLinkList(10, true, 2);
    hasCycle = hasCircyle(linkHead);
    printf("hasCycle : %d \n", hasCycle);
}

- (void)testReverseLinkList {
    bool hasCycle = false;
    Node* linkHead = createLinkList(10, hasCycle, 3);
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
    Node* linkHead2 = createLinkList(10, hasCycle, 3);
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


@end
