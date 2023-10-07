//
//  WXMonitor.m
//  Pratice
//
//  Created by Steven Deng on 2023/9/19.
//

#import "WXMonitor.h"
#include <mach/mach.h>

@interface WXMonitor() {
    int timeoutCount;
    CFRunLoopObserverRef runLoopObserver;
    
    @public
    dispatch_semaphore_t dispatchSemaphore;
    CFRunLoopActivity runLoopActivity;
}

@property (nonatomic, strong) NSTimer *cpuMonitorTimer;

@end

@implementation WXMonitor

+ (instancetype) sharedInstance {
    static dispatch_once_t onceToken;
    static WXMonitor *s_instance = nil;
    dispatch_once(&onceToken, ^{
        s_instance = [[WXMonitor alloc] init];
    });
    return s_instance;
}

- (void)beginMonitor {
    // 监测cpu 消耗
    self.cpuMonitorTimer = [NSTimer scheduledTimerWithTimeInterval:3.0f
                                                            target:self
                                                          selector:@selector(updateCPUInfo)
                                                          userInfo:nil
                                                           repeats:YES];
    if (runLoopObserver) {
        return;
    }
    
    dispatchSemaphore = dispatch_semaphore_create(0);
    // 创建一个
    CFRunLoopObserverContext context = {0, (__bridge void*)self, NULL, NULL};
    runLoopObserver = CFRunLoopObserverCreate(kCFAllocatorDefault,
                                              kCFRunLoopAllActivities,
                                              YES,
                                              0,
                                              &runLoopObserverCallBack,
                                              &context);
    // 将观察者添加到主线程runloop
    CFRunLoopAddObserver(CFRunLoopGetMain(), runLoopObserver, kCFRunLoopCommonModes);
    //
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        while (1) {
            long semaphoreWait = dispatch_semaphore_wait(self->dispatchSemaphore, dispatch_time(DISPATCH_TIME_NOW, 5 * NSEC_PER_SEC));
            if (semaphoreWait != 0) {
                if (!self->runLoopObserver) {
                    self->timeoutCount = 0;
                    semaphoreWait = 0;
                    self->runLoopActivity = 0;
                    return;
                }
                
                if (self->runLoopActivity == kCFRunLoopBeforeSources || self->runLoopActivity == kCFRunLoopAfterWaiting) {
                    // 收集堆栈信息上报
                    if(++(self->timeoutCount) < 3) {
                        continue;
                    }
                    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
                        // 收集调用栈
                    });
                }
            }
            self->timeoutCount = 0;
        }
    });
}

- (void)endMonitor {
    [self.cpuMonitorTimer invalidate];
    if (!runLoopObserver) {
        return;
    }
    CFRunLoopRemoveObserver(CFRunLoopGetMain(), runLoopObserver, kCFRunLoopCommonModes);
    CFRelease(runLoopObserver);
    runLoopObserver = NULL;
}

static void runLoopObserverCallBack(CFRunLoopObserverRef observer, CFRunLoopActivity activity, void *info){
    WXMonitor *lagMonitor = (__bridge WXMonitor*)info;
    lagMonitor->runLoopActivity = activity;
    
    dispatch_semaphore_t semaphore = lagMonitor->dispatchSemaphore;
    dispatch_semaphore_signal(semaphore);
}

- (void)updateCPUInfo {
    thread_act_array_t threads;
    mach_msg_type_number_t threadCount = 0;
    const task_t thisTask = mach_task_self();
    kern_return_t kr = task_threads(thisTask, &threads, &threadCount);
    if (kr != KERN_SUCCESS) {
        return;
    }
    for (int i = 0; i < threadCount; i++) {
        thread_info_data_t threadInfo;
        thread_basic_info_t threadBaseInfo;
        mach_msg_type_number_t threadInfoCount = THREAD_INFO_MAX;
        if (thread_info((thread_act_t)threads[i], THREAD_BASIC_INFO, (thread_info_t)threadInfo, &threadInfoCount) == KERN_SUCCESS) {
            threadBaseInfo = (thread_basic_info_t)threadInfo;
            if (!(threadBaseInfo->flags & TH_FLAGS_IDLE)) {
                integer_t cpuUsage = threadBaseInfo->cpu_usage / 10;
                if (cpuUsage > 70) {
                    //cup 消耗大于 70 时打印和记录堆栈
//                    NSString *reStr = HCCStackOfThread(threads[i]);
                    //记录数据库中
//                    [[[HCCDB shareInstance] increaseWithStackString:reStr] subscribeNext:^(id x) {}];
//                    NSLog(@"CPU useage overload thread stack：\n%@",reStr);
                }
            }
        }
    }
}

@end
