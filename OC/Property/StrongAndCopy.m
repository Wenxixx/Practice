//
//  StrongAndCopy.m
//  Practice001
//
//  Created by Rodin on 2022/10/27.
//

#import "StrongAndCopy.h"

@implementation StrongAndCopy

- (instancetype)init {
    self = [super init];
    if (self) {
        NSArray *arr = [[NSArray alloc] initWithObjects:@"string", @"array", nil];
        self.list = arr;
        NSMutableArray *mArr = [[NSMutableArray alloc] init];
        
        self.mutableList = mArr;
        [_mutableList addObject:@"obj1"];
    }
    return self;
}

@end
