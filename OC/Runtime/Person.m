//
//  Person.m
//  Rutime
//
//  Created by 邓文博 on 2020/7/11.
//  Copyright © 2020 邓文博. All rights reserved.
//

#import "Person.h"
#import "Exception.h"
#import <objc/runtime.h>
#import <objc/message.h>

@implementation Person

void swizzle_method(id self, SEL sel) {
    NSLog(@"swizzle %@", NSStringFromSelector(sel));
}


#pragma mark - Swizzle
/**
  +(void)load 与 +(void)initialize 区别：
   load 方法仅在程序启动加载一次，调用时机在load_images,早于main()入口函数
   initialize 则在对应类每次alloc的时候便会出发一次，会存在多次调用
 */
+ (void)load
{
    [self commonSwizzleMethod];
}

+ (void)initialize
{
//    [self commonSwizzleMethod];
}

+ (void)commonSwizzleMethod
{
    Method originMethod = class_getInstanceMethod([Person class], @selector(speak));
    Method newMethod = class_getInstanceMethod([Person class], @selector(swizzle_speak));
//    IMP originIMP = class_getMethodImplementation([Person class], @selector(speak));
//    IMP newIMP = class_getMethodImplementation([Person class], @selector(swizzle_speak));
    if (!newMethod) {
        // 动态添加了swizzle_speak方法，并且修改了SEL speak 的实现
//        class_addMethod([Person class], @selector(swizzle_speak), (IMP)swizzle_method, "v@:");
//        method_setImplementation(originMethod, (IMP)swizzle_method);

        // 直接替换SEL speak的实现
        class_replaceMethod([Person class], @selector(speak), (IMP)swizzle_method, "v@:");
    } else {
        // 两个方法都存在时，直接交换实现
        method_exchangeImplementations(originMethod, newMethod);
    }
}

#pragma mark - Public
- (void)speak
{
    NSLog(@"hello world");
}

//- (void)swizzle_speak
//{
//    NSLog(@"replaced with me");
//}

- (void)speakWithLanguage:(NSString *)language
{
    NSLog(@"speak %@", language);
}

#pragma mark - Three Method
// 三次补救机会
// 1. 动态解析
+ (BOOL)resolveInstanceMethod:(SEL)sel
{
    // 1. 此步不做补救处理
    return NO;
    
    // 2. 使用Exception类实例方法实现 + typeEncoding 给Person类动态添加实例方法
    BOOL success = [self dynamicAddInstanceMethodWithSelector:sel];
    if (success) {
        // 添加成功则直接调用 - [Exception printException]，不再触发后面
        return success;
    }
    return [super resolveInstanceMethod:sel];
}

+ (BOOL)resolveClassMethod:(SEL)aSelector
{
    // 1. 此步不做补救处理
//    return NO;
    
    // 2. 使用Exception类方法的实现 + typeEncoding 动态给Person类动态添加类方法
    BOOL success = [self dynamicAddClassMethodWithSelector:aSelector];
    if (success) {
        return YES;
    }
    return [super resolveClassMethod:aSelector];
}

// 2. 备用接收者处理
- (id)forwardingTargetForSelector:(SEL)aSelector
{
    // 1. 返回Exception实例，作为sel的接收者
    NSString *selString = NSStringFromSelector(aSelector);
    if([selString isEqualToString:@"xxx:"]) {
        // 会调用到Exception里的 xxx: 方法, 消息接收者为当前初始化实例e
        // 如果 Exception 没有 xxx: 方法，依然会闪退
        Exception *e = [Exception new];
        return e;
    }
    
    // 2. 此步不做处理
    return  [super forwardingTargetForSelector:aSelector];
}

// 3. 完整的消息转发
- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector
{
//    return [NSMethodSignature signatureWithObjCTypes:"v@:"];
    Method method;
    NSString *selString = NSStringFromSelector(aSelector);
    if([selString isEqualToString:@"xxx:"]) {
        method = class_getInstanceMethod([Exception class], @selector(returnValue:));

    } else {
        method = class_getInstanceMethod([Exception class], @selector(printException));
    }

    // 获取对应方法签名
    const char *signature = method_getTypeEncoding(method);
    return [NSMethodSignature signatureWithObjCTypes:signature];
}

- (void)forwardInvocation:(NSInvocation *)anInvocation
{
    [[self class] dynamicAddInstanceMethodWithSelector:anInvocation.selector];
    if ([self respondsToSelector:anInvocation.selector]) {
        // 虽然执行的代码为 [Exception printException], 但消息接收者仍是Person实例
        [anInvocation invokeWithTarget:self];
    }
}

#pragma mark - Helper
+ (BOOL)dynamicAddInstanceMethodWithSelector:(SEL)aSelector
{
    IMP replace_imp;
    Method method;
    NSString *selString = NSStringFromSelector(aSelector);
    
    if([selString isEqualToString:@"xxx:"]) {
        replace_imp = class_getMethodImplementation([Exception class], @selector(returnValue:));
        method = class_getInstanceMethod([Exception class], @selector(returnValue:));
    } else {
        replace_imp = class_getMethodImplementation([Exception class], @selector(printException));
        method = class_getInstanceMethod([Exception class], @selector(printException));
    }
    
    if (method && replace_imp) {
        const char * signature = method_getTypeEncoding(method);
        BOOL success = class_addMethod([Person class], aSelector, replace_imp, signature);
        if (success) {
            return YES;
        }
    }
    
    return NO;
}

void missMethod(id self, SEL sel) {
    NSLog(@"missMethod");
}

+ (BOOL)dynamicAddClassMethodWithSelector:(SEL)aSelector
{
    // 类方法列表存放在元类
    Class metaCls = objc_getMetaClass("Person");
    BOOL success;
    
    // 方式一
    success = class_addMethod(metaCls, aSelector, (IMP)missMethod, "v@:");
    
    // 方式二
//    Class exptionMetaCls = objc_getMetaClass("Exception");
//    IMP replace_imp = class_getMethodImplementation(exptionMetaCls, @selector(printE));
//    Method method = class_getClassMethod(exptionMetaCls, @selector(printE));
//    success = class_addMethod(metaCls, aSelector, replace_imp, method_getTypeEncoding(method));
    
    return success;;
}

@end
