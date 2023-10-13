//
//  Exception.h
//  Rutime
//
//  Created by 邓文博 on 2020/7/11.
//  Copyright © 2020 邓文博. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface Exception : NSObject

- (void)printException;

- (NSArray *)returnValue:(NSDictionary *)dic;

+ (void)printE;

@end

NS_ASSUME_NONNULL_END
