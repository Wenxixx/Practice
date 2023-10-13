//
//  WXKVC.m
//  Pratice
//
//  Created by Steven Deng on 2023/9/18.
//

#import "WXKVC.h"

@interface PersonOne : NSObject {
    NSString *_name;
    NSString *_isName;
    NSString *name;
    NSString *isName;
}

//@property (nonatomic, copy) NSString *name;
@property (nonatomic, assign) NSInteger age;

@end

@implementation PersonOne

- (instancetype) init {
    self = [super init];
    if (self) {
//        _name = @"wade";
//        _isName = @"kobe";
        name = @"Tracy";
        isName = @"Iverson";
    }
    return self;
}

+ (BOOL)accessInstanceVariablesDirectly
{
    // setter 查找成员变量顺序：_key > _isKey > key > isKey
    // getter 查找成员变量顺序：_key > _isKey > key > isKey
    return YES;
}

- (void)setValue:(id)value forUndefinedKey:(NSString *)key
{
    if ([key isEqualToString:@"isName"]) {
        [self setValue:value forKey:@"name"];
    }
}

- (id)valueForUndefinedKey:(NSString *)key
{
    if ([key isEqualToString:@"isName"]) {
        return [self valueForKey:@"name"];
    }
    return nil;
}

@end


@interface WXKVC()

@property (nonatomic, strong) PersonOne *son;

@end


@implementation WXKVC

- (instancetype)init {
    self = [super init];
    if (self) {
        _son = [PersonOne alloc];
        _son = [_son init];
//        [_son setValue:@"Kobe" forKey:@"isName"];
//        [_son setValue:@"Kobe" forKey:@"name"];
//        NSLog(@"name = %@", _son.name);
        NSLog(@"kvc name = %@", [_son valueForKey:@"name"]);
    }
    
    return self;
}

@end
