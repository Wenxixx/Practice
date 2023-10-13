//
//  SynthesizeAndDynamic.m
//  Practice001
//
//  Created by Rodin on 2022/10/27.
//

#import "SynthesizeAndDynamic.h"

@implementation SynthesizeAndDynamic

//@synthesize protocolVar = _protocolVar;

@dynamic dynamicName;

- (instancetype)init
{
    self = [super init];
    if (self) {
        self->_name = @"wenxi";
        self.name = @"wenxi2";
        
        self->_readOnlyName = @"only";
        self.readOnlyName = @"objjj";  // readOnly 不重写setter编译报错
        
        self.protocolVar = @"hehe";     // protocol里声明的属性，须自己实现setter/getter才能调用
//        self->_protocolVar = @"hehe";   // protocol里声明的属性，必须使用 @synthesize才能使用成员属性
        
        self.dynamicName = @"yaya";    // 使用dynamic之后，不重写setter/getter方法会闪退
    }
    return self;
}

- (NSString *)description
{
    return [NSString stringWithFormat:@"name = %@, readOnlyName = %@, dynamicName = %@, protocolVar = %@", self->_name, self->_readOnlyName, self.dynamicName, self.protocolVar];
}

#pragma mark - Setter/Getter

// 声明readonly, 也可以重写setter方法并在内部调用
- (void)setReadOnlyName:(NSString * _Nonnull)readOnlyName
{
    self->_readOnlyName = readOnlyName;
}

- (void)setProtocolVar:(NSString *)protocolVar
{
    // 同样protocol属性，不使用synthesize生成成员属性，要怎么实现setter
 }

- (NSString *)protocolVar
{
    return @"haha";
}

- (void)setDynamicName:(NSString *)dynamicName {
    // 思考：使用dynamic之后，系统不生成成员属性了要怎么实现setter方法
}

- (NSString *)dynamicName {
    return @"yaya";
}

@end
