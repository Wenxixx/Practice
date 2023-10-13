//
//  Person.h
//  Rutime
//
//  Created by 邓文博 on 2020/7/11.
//  Copyright © 2020 邓文博. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface Person : NSObject

@property (nonatomic, copy) NSString *name;
@property (nonatomic, assign) NSUInteger age;

- (void)speak;

+ (void)ppp;

- (NSArray *)xxx:(NSDictionary *)dic;

@end

NS_ASSUME_NONNULL_END
