//
//  WXBlock.m
//  Pratice
//
//  Created by Steven Deng on 2023/9/13.
//

#import "WXBlock.h"

@interface WXBlock ()

@end

@implementation WXBlock

- (void)testMethods {
    void (^blockA)(int a) = ^(int a) {
        NSLog(@"%d",a);
    };
    if (blockA) {
        blockA(1990);
    }
}

@end
