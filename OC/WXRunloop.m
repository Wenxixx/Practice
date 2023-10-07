//
//  Runloop.m
//  Pratice
//
//  Created by Steven Deng on 2023/9/19.
//

#import "WXRunloop.h"

@interface WXRunloop() {
    NSInteger _index;
}

@property (nonatomic, strong) NSTimer *timer;

@end

@implementation WXRunloop

- (instancetype)init {
    self = [super init];
    if (self) {
        _index = 0;
    }
    return self;
}

#pragma mark - NSTimer
- (void)startTimer {
    NSTimer *timer = [NSTimer timerWithTimeInterval:1.0f repeats:YES block:^(NSTimer * _Nonnull timer) {
        self->_index++;
        NSLog(@"NSTimer index == %ld", self->_index);
        if (self->_index == 5) {
            [self stopTimer];
        }
    }];
    [timer fire];
    self.timer = timer;
    [[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
}

#pragma mark - Private
- (void)stopTimer {
    [self.timer invalidate];
    self.timer = nil;
}

@end
