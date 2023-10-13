//
//  StrongAndCopy.h
//  Practice001
//
//  Created by Rodin on 2022/10/27.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface StrongAndCopy : NSObject

@property (nonatomic, copy) NSArray *list;

// mutable 使用copy，得到 immutable
// @property (nonatomic, copy) NSMutableArray *mutableList;
@property (nonatomic, strong) NSMutableArray *mutableList;

@end

NS_ASSUME_NONNULL_END
