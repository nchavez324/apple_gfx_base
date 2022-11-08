#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <TargetConditionals.h>
#import <UIKit/UIKit.h>

#import "test_app/entry/common/ARSSurfaceViewDelegate.h"

NS_ASSUME_NONNULL_BEGIN

@interface ARSSurfaceView : UIView

@property(nonatomic, weak, nullable) id<ARSSurfaceViewDelegate> delegate;

- (instancetype)initWithFrame:(CGRect)frame;

@end

NS_ASSUME_NONNULL_END
