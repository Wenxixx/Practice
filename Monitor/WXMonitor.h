//
//  WXMonitor.h
//  Pratice
//
//  Created by Steven Deng on 2023/9/19.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface WXMonitor : NSObject

+ (instancetype) sharedInstance;
- (void)beginMonitor;
- (void)endMonitor;

@end

NS_ASSUME_NONNULL_END
