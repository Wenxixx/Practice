//
//  WXGCD.m
//  Pratice
//
//  Created by Steven Deng on 2023/9/20.
//

#import "WXGCD.h"

@interface WXGCD() {
    NSInteger _index;
    NSInteger _ticketCount;
    dispatch_semaphore_t _sem;
}

@property (nonatomic, strong) dispatch_source_t gcdTimer;

@end

@implementation WXGCD

- (instancetype)init {
    self = [super init];
    if (self) {
        _index = 0;
    }
    return self;
}

#pragma mark - GCD Timer
- (void)startGCDTimer {
    dispatch_queue_t queue = dispatch_queue_create("timerQueue", DISPATCH_QUEUE_SERIAL);
    dispatch_source_t timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, queue);
    
    uint64_t start = 2.0;
    uint64_t interval = 1.0;
    
    dispatch_source_set_timer(timer, dispatch_time(DISPATCH_TIME_NOW, start * NSEC_PER_SEC), interval * NSEC_PER_SEC, 0);
    
    dispatch_source_set_event_handler(timer, ^{
        self->_index++;
        NSLog(@"[GCDTimer] index == %ld", self->_index);
        if (self->_index == 2) {
            [self stopGCDTimer];
        }
    });
    
    dispatch_resume(timer);
    self.gcdTimer = timer;
}

#pragma mark - gcd thread
 
- (void)startGCDMultipleThread {
//    dispatch_queue_t queue = dispatch_queue_create("gcd.thread.wxTest", DISPATCH_QUEUE_SERIAL);
    dispatch_queue_t queue = dispatch_queue_create("gcd.thread.wxTest", DISPATCH_QUEUE_CONCURRENT);
//    dispatch_queue_t queue = dispatch_get_global_queue(0, 0);
    // async + 串型队列 ： 顺序执行，会开启一条新线程
    // async + 并型对别 ： 并发执行，会开启多条新线程
    // sync + 串型队列 : 顺序执行，不开启新线程
    // sync + 并发队列 : 顺序执行，不开启新线程
//    for (int i = 0; i < 5; i++) {
//        dispatch_sync(queue, ^{
//            NSLog(@"[GCDThread] thread-%i %@", i, [NSThread currentThread]);
//        });
//    }
    //
    
    // barrier
    dispatch_async(queue, ^{
        NSLog(@"[GCDThread] thread-1 %@", [NSThread currentThread]);
    });
    dispatch_async(queue, ^{
        NSLog(@"[GCDThread] thread-2 %@", [NSThread currentThread]);
    });

    /* dispatch_barrier_sync：同步卡线程 / dispatch_barrier_async：异步不阻塞 */
    dispatch_barrier_sync(queue, ^{
        NSLog(@"[GCDThread] thread-3 %@", [NSThread currentThread]);
    });
    dispatch_async(queue, ^{
        NSLog(@"[GCDThread] thread-4 %@", [NSThread currentThread]);
    });
    NSLog(@"xxxxxxx");
    
    // group
//    dispatch_group_t group = dispatch_group_create();
//    dispatch_group_async(group, queue, ^{
//        sleep(2);
//        NSLog(@"[GCDThread] thread-1 %@", [NSThread currentThread]);
//    });
//    dispatch_group_async(group, queue, ^{
//        sleep(1);
//        NSLog(@"[GCDThread] thread-2 %@", [NSThread currentThread]);
//    });
//    dispatch_group_notify(group, queue, ^{
//        NSLog(@"[GCDThread] thread-3 %@", [NSThread currentThread]);
//    });
//    dispatch_group_async(group, queue, ^{
//        NSLog(@"[GCDThread] thread-4 %@", [NSThread currentThread]);
//    });
//    NSLog(@"xxxxxxx");
    
    // 信号量
//    dispatch_semaphore_t sem = dispatch_semaphore_create(0);
//    dispatch_async(queue, ^{
//        NSLog(@"before signal...");
//        dispatch_semaphore_signal(sem);
//        NSLog(@"after signal...");
//    });
//    NSLog(@"before wait...");
//    dispatch_semaphore_wait(sem, DISPATCH_TIME_FOREVER);
//    NSLog(@"after wait...");
}

- (void)startSemphore {
    _ticketCount = 50;
    dispatch_queue_t queue1 = dispatch_queue_create("sem.thread.wxTest-1", DISPATCH_QUEUE_CONCURRENT);
    dispatch_queue_t queue2 = dispatch_queue_create("sem.thread.wxTest-2", DISPATCH_QUEUE_CONCURRENT);
    _sem = dispatch_semaphore_create(1);
    
    dispatch_async(queue1, ^{
        [self saleTicketSafe];
    });
    
    dispatch_async(queue2, ^{
        [self saleTicketSafe];
    });
    
}

#pragma mark - Private
- (void)stopGCDTimer {
    dispatch_source_cancel(self.gcdTimer);
}

- (void)saleTicketSafe {
    while (1) {
        dispatch_semaphore_wait(_sem, DISPATCH_TIME_FOREVER);
        if (_ticketCount > 0) {
            _ticketCount --;
            NSLog(@"剩余票数：%ld thread:%@", _ticketCount, [NSThread currentThread]);
//            [NSThread sleepForTimeInterval:0.2];
        } else {
            NSLog(@"票卖完了！！！");
            dispatch_semaphore_signal(_sem);
            break;
        }
        NSLog(@"befaore signal, thread:%@", [NSThread currentThread]);
        dispatch_semaphore_signal(_sem);
    }
}

@end
