//
//  MAKVONotificationCenter.h
//  MAKVONotificationCenter
//
//  Created by Michael Ash on 10/15/08.
//

#import <Cocoa/Cocoa.h>


@interface MAKVONotificationCenter : NSObject
{
	NSMutableDictionary*	_observerHelpers;
}

+ (id)defaultCenter;

// selector should have the following signature:
// - (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)target change:(NSDictionary *)change userInfo:(id)userInfo;
- (void)addObserver:(id)observer object:(id)target keyPath:(NSString *)keyPath selector:(SEL)selector userInfo:(id)userInfo options:(NSKeyValueObservingOptions)options;
- (void)removeObserver:(id)observer object:(id)target keyPath:(NSString *)keyPath selector:(SEL)selector;

@end

#if NS_BLOCKS_AVAILABLE

typedef void (^MAKVONotificationBlock)(NSString *, NSDictionary *, id);

@interface MAKVONotificationBlockObserver : NSObject {
  MAKVONotificationBlock block;
  NSString *keyPath;
}
@property (nonatomic, readonly) NSString *keyPath;
@property (nonatomic, readonly) SEL selectorForObserving;

- (id)initWithBlock:(MAKVONotificationBlock)aBlock keyPath:(NSString *)aKeyPath;
@end

#endif

@interface NSObject (MAKVONotification)

- (void)addObserver:(id)observer forKeyPath:(NSString *)keyPath selector:(SEL)selector userInfo:(id)userInfo options:(NSKeyValueObservingOptions)options;
- (void)removeObserver:(id)observer keyPath:(NSString *)keyPath selector:(SEL)selector;

#if NS_BLOCKS_AVAILABLE

#pragma mark - Block support

- (MAKVONotificationBlockObserver *)addObserverForKeyPath:(NSString *)keyPath userInfo:(id)userInfo options:(NSKeyValueObservingOptions)options handleWithBlock:(MAKVONotificationBlock)block;

- (void)removeBlockObserver:(MAKVONotificationBlockObserver *)observer;

#endif

@end
