//
//  ViewController.m
//  Pratice
//
//  Created by Steven Deng on 2021/9/2.
//

#import "ViewController.h"
#import "WXAlgorithm.h"
#import "WXKVC.h"
#import "WXLock.h"
#import "WXRunloop.h"
#import "WXMonitor.h"
#import "WXGCD.h"
#import "Person.h"
#import "Student.h"
#import "Teacher.h"

#define CODE_LEN (500000000 * 4)

typedef enum {
    ADD,    // *sp += 2
    SUB,    // *sp -= 1
    MUL,    // *sp *= 2
    DIV,    // *sp /= 2
    END
} OpCode;

typedef void (*OpFunc)(long *);

void add(long *sp) { *sp += 2; }
void sub(long *sp) { *sp -= 1; }
void mul(long *sp) { *sp *= 2; }
void div(long *sp) { *sp /= 2; }

long test_call(char *code) {
    long ret = 0;
    long *sp = &ret;
    char *pc = &code[0];
    
    OpFunc funcs[] = {add, sub, mul, div};
    while (*pc != END) {
        funcs[*pc++](sp);
        printf("%ld \n", ret);
    }
    
    return ret;
}

@interface ViewController ()

@property (nonatomic, copy) NSArray *mArr;
@property (nonatomic, strong) NSMutableArray *mMArr;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
//    Person *p;
//    p = [Person alloc];
//    Teacher *t = [Teacher alloc];
//    Student *s = [Student alloc];
    
    // 算法类
//    WXAlgorithm *algorithm = [[WXAlgorithm alloc] init];
//    // LRU 缓存
//    [algorithm testLRUCache];
//    // 是否回文串
//    [algorithm testHuiwen];
//    // 链表中是否有环
//    [algorithm testCycleLinkList];
//    // 反转链表
//    [algorithm testReverseLinkList];
//    [algorithm testDeleteDuplicates];
//    [algorithm testAddTwoNumbers];
    
//    [algorithm tesStack];
//    [algorithm testTree];
//    [algorithm testIncreasingTriplet];
//    [algorithm testLengthOfLongestSubstring];
    
    // 🔒
//    WXLock *lock = [[WXLock alloc] init];
//    [lock testLock];
//    [lock testRecursiveLock];
    
    // runloop
//    WXRunloop *runloop = [[WXRunloop alloc] init];
//    [runloop startTimer];
    
    // gcd
    WXGCD *gcd = [[WXGCD alloc] init];
//    [gcd startGCDTimer];
    [gcd startGCDMultipleThread];
//    [gcd startSemphore];
    
//    [[WXMonitor sharedInstance] beginMonitor];
}


#pragma mark - Private
- (void)opCode {
    char *code = new char[CODE_LEN + 1];
    for (int i = 0; i < CODE_LEN / 4; i++) {
        code[i * 4 + 0] = ADD;
        code[i * 4 + 1] = SUB;
        code[i * 4 + 2] = MUL;
        code[i * 4 + 3] = DIV;
    }
    code[CODE_LEN] = END;
    test_call(code);
}

- (void)testStrongAndCopy
{
    NSArray *arr1 = [NSArray arrayWithObject:@"a"];
    self.mArr = arr1;
    NSLog(@"mArr = %@", _mArr);
    NSLog(@"arr1 = %p, mArr = %p", arr1, _mArr);
    
    NSMutableArray *marr = [NSMutableArray arrayWithObject:@"b"];
    self.mMArr = marr;
    NSLog(@"mMArr = %@", _mMArr);
    NSLog(@"marr = %p, mMArr = %p", marr, _mMArr);
}

- (void)testPerformSelector
{
    // performSelector
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        NSLog(@"1");
        NSLog(@"%@", [NSThread currentThread]);
        // 1. 正常
//        [self performSelector:@selector(test) withObject:nil];
        
        // 2. 会创建Timer
//        [self performSelector:@selector(test) withObject:nil afterDelay:0];
//        [[NSRunLoop currentRunLoop] run];
        
        // 3. mainThread waitUntilDone
//        [self performSelectorOnMainThread:@selector(test) withObject:nil waitUntilDone:NO];
        
        // 4. backgroundThread
        [self performSelectorInBackground:@selector(test) withObject:nil];
        NSLog(@"3");
//        NSLog(@"%@",[NSRunLoop currentRunLoop]);
        
        //
//        TestKVC *kvc = [[TestKVC alloc] init];
    });
}

- (void)test
{
    NSLog(@"%@", [NSThread currentThread]);
    sleep(3);
    NSLog(@"2");
}



@end
