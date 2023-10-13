//
//  Exception.m
//  Rutime
//
//  Created by 邓文博 on 2020/7/11.
//  Copyright © 2020 邓文博. All rights reserved.
//

#import "Exception.h"

@implementation Exception

- (void)printException
{
    NSLog(@"oh, throw exception");
}

- (NSArray *)returnValue:(NSDictionary *)dic
{
    return [dic allValues];
}

+ (void)printE
{
    NSLog(@"oh, throw e");
}

- (NSArray *)xxx:(NSDictionary *)dic
{
    NSLog(@"oh, is me!");
    return dic.allValues;
}

+ (void)ppp
{
    NSLog(@"oh, is class method");
}

@end
