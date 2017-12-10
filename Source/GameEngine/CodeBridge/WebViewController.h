
#import <UIKit/UIKit.h>

@interface WebViewController : UIViewController <UIWebViewDelegate>

- (void)loadPageNamed:(NSString*)name inSubdirectory:(NSString*)subdirectory;
- (void)loadExternalPage:(NSString*)url;
- (UIWebView*)webView;

- (void)openSite:(NSString*)website inViewController:(UIViewController*)viewCtrl;
- (void)dismissSelf;
- (BOOL)isOpened;

@property (nonatomic, strong) NSString *currentPageName;
@property (nonatomic, strong) NSString *currentPageDirectory;
@property (nonatomic, strong) UIActivityIndicatorView* activityView;
@property (nonatomic, strong) UIBarButtonItem* activityIndicator;

@end
