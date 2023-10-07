//
//  WXLock.m
//  Pratice
//
//  Created by Steven Deng on 2023/9/19.
//

#import "WXLock.h"

@interface WXLock() {
    NSInteger _index;
}

// 互斥锁
@property (nonatomic, strong) NSLock *lock;

// 递归锁
@property (nonatomic, strong) NSRecursiveLock *recursiveLock;


@end


@implementation WXLock

- (instancetype)init
{
    self = [super init];
    if (self) {
        _lock = [[NSLock alloc] init];
        _recursiveLock = [[NSRecursiveLock alloc] init];
        _index = 0;
    }
    
    return self;
}

- (void)testLock {
    // 死锁
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        [self->_lock lock];
        [self lockPrint];
        [self->_lock unlock];
        
    });
}

- (void)testRecursiveLock {
    // 正常打印
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        [self->_recursiveLock lock];
        [self recursiveLockPrint];
        [self->_recursiveLock unlock];
        
    });
}

#pragma mark - Private

- (void)lockPrint {
    [_lock lock];
    _index ++;
    NSLog(@"[lock] index = %ld", _index);
    [_lock unlock];
}

- (void)recursiveLockPrint {
    [_recursiveLock lock];
    _index ++;
    NSLog(@"[recursiveLock] index = %ld", _index);
    [_recursiveLock unlock];
}


@end
