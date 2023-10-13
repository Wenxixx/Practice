//
//  SynthesizeAndDynamic.h
//  Practice001
//
//  Created by Rodin on 2022/10/27.
//

#import <Foundation/Foundation.h>

@protocol TestSynthesize <NSObject>

@property (nonatomic, copy) NSString *protocolVar;

@end


NS_ASSUME_NONNULL_BEGIN

@interface SynthesizeAndDynamic : NSObject <TestSynthesize>


@property (nonatomic, copy) NSString *name;

@property (nonatomic, copy, readonly) NSString *readOnlyName;

@property (nonatomic, copy) NSString *dynamicName;


@end

NS_ASSUME_NONNULL_END
