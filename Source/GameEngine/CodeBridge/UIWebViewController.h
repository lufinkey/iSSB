
#import <UIKit/UIKit.h>

@interface UIWebViewController : UIViewController <UIWebViewDelegate>
{
    NSString *_currentPageName, *_currentPageDirectory; 
    UIWebView *webView;
	
	@private
	BOOL webviewOpened;
	UIActivityIndicatorView* activityView;
	UIBarButtonItem* activityIndicator;
}

- (void)loadPageNamed:(NSString*)name inSubdirectory:(NSString*)subdirectory;
- (void)loadExternalPage:(NSString*)url;
- (UIWebView*)webView;

- (void)openSite:(NSString*)website inViewController:(UIViewController*)viewCtrl;
- (void)dismissSelf;
- (BOOL)isOpened;
@end
