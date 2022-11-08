#import "test_app/entry/common/ARSSurfaceViewDelegate.h"

#import "test_app/entry/common/ARSDefines.h"

NS_ASSUME_NONNULL_BEGIN

@interface ARSTViewController : XPBaseViewController <ARSSurfaceViewDelegate>

- (instancetype)initWithBounds:(CGSize)bounds;

@end

NS_ASSUME_NONNULL_END
