//
//  Teacher.h
//  Rutime
//
//  Created by 邓文博 on 2020/7/11.
//  Copyright © 2020 邓文博. All rights reserved.
//

#import "Person.h"

NS_ASSUME_NONNULL_BEGIN

@interface Teacher : Person

@property (nonatomic, copy) NSString *school;

- (void)teach;

@end

NS_ASSUME_NONNULL_END
