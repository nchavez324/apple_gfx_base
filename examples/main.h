#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface AppDelegate : NSObject <NSApplicationDelegate>
@property(nullable, nonatomic, strong) NSWindow *window;
@end

@interface ViewController : NSViewController
- (instancetype)init;
@end

NS_ASSUME_NONNULL_END
