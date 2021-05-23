
#ifdef __APPLE__
#import "WebViewController.h"
#import <QuartzCore/QuartzCore.h>

@interface WebViewController ()
{
	BOOL _webviewOpened;
	UIWebView* _webView;
}
@end

@implementation WebViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    if (self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])
	{
		_webviewOpened = NO;
		_activityView = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhite];
		[_activityView setFrame:CGRectMake(0,0,20,20)];
		_activityIndicator = [[UIBarButtonItem alloc] initWithCustomView:_activityView];
		
		self.view.autoresizesSubviews = YES;
		self.view.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
		
		UINavigationBar* navBar = [[UINavigationBar alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, 44)];
		UIBarButtonItem* doneButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(dismissSelf)];
		[self.navigationItem setLeftBarButtonItem:doneButton];
		
		[navBar pushNavigationItem:self.navigationItem animated:NO];
		navBar.autoresizesSubviews = YES;
		navBar.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
		[self.view addSubview:navBar];
		
		
		_webView = [[UIWebView alloc] initWithFrame:CGRectMake(0, 44, self.view.frame.size.width, self.view.frame.size.height-44)];
		_webView.delegate = self;
		_webView.autoresizesSubviews = YES;
		_webView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
		[self.view addSubview:_webView];
    }
    return self;
}

- (id)init
{
	if(self = [super init])
	{
		_webviewOpened = NO;
		_activityView = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhite];
		[_activityView setFrame:CGRectMake(0,0,20,20)];
		_activityIndicator = [[UIBarButtonItem alloc] initWithCustomView:_activityView];
		
		self.view.autoresizesSubviews = YES;
		self.view.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
		
		UINavigationBar* navBar = [[UINavigationBar alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, 44)];
		UIBarButtonItem* doneButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(dismissSelf)];
		[self.navigationItem setLeftBarButtonItem:doneButton];
		
		[navBar pushNavigationItem:self.navigationItem animated:NO];
		navBar.autoresizesSubviews = YES;
		navBar.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
		[self.view addSubview:navBar];
		
		
		_webView = [[UIWebView alloc] initWithFrame:CGRectMake(0, 44, self.view.frame.size.width, self.view.frame.size.height-44)];
		_webView.delegate = self;
		_webView.autoresizesSubviews = YES;
		_webView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
		[self.view addSubview:_webView];
	}
	return self;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
	return YES;
}

- (void)openSite:(NSString*)website inViewController:(UIViewController*)viewCtrl
{
	_webviewOpened = YES;
	[self loadExternalPage:website];
	[viewCtrl presentViewController:self animated:YES completion:nil];
}

- (void)dismissSelf
{
	[self dismissViewControllerAnimated:YES completion:nil];
	_webviewOpened = NO;
}

- (BOOL)isOpened
{
	return _webviewOpened;
}

#pragma mark -
#pragma mark Get&Set
- (UIWebView*)webView
{
    return _webView;
}

#pragma mark -
#pragma mark Actions
- (void)loadPageNamed:(NSString*)name inSubdirectory:(NSString*)subdirectory
{
#ifdef DEBUG
    NSLog(@"[%@] Loading page named: '%@' in directory: '%@'", NSStringFromClass([self class]), name, subdirectory);
#endif	
    self.currentPageName = name;
    self.currentPageDirectory = subdirectory;
    
    NSString *path = [[NSBundle mainBundle] pathForResource:name 
                                                     ofType:@"html" 
                                                inDirectory:subdirectory];
    
    [[self webView] loadRequest:[NSURLRequest requestWithURL:[NSURL fileURLWithPath:path]]];
}


- (void)loadExternalPage:(NSString*)urlAddress
{
    NSURL *url = [NSURL URLWithString:urlAddress];
    NSURLRequest *requestObj = [NSURLRequest requestWithURL:url];
	
    [[self webView] loadRequest:requestObj];
}


#pragma mark -
#pragma UIWebView Delegate
- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
#ifdef DEBUG
	NSLog(@"[UIWebViewController] Load failed: %@", error);
#endif
	if([_activityView isAnimating])
	{
		[_activityView stopAnimating];
	}
	[self.navigationItem setRightBarButtonItem:nil];
}

- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
#ifdef DEBUG
	NSLog(@"[UIWebViewController] Loading %@", [request URL]);
#endif
	return YES;
    
}

- (void)webViewDidFinishLoad:(UIWebView *)view
{
	if([_activityView isAnimating])
	{
		[_activityView stopAnimating];
	}
	[self.navigationItem setRightBarButtonItem:nil];
}

- (void)webViewDidStartLoad:(UIWebView *)webView
{
	if(![_activityView isAnimating])
	{
		[_activityView startAnimating];
	}
	[self.navigationItem setRightBarButtonItem:_activityIndicator];
}

@end
#endif
