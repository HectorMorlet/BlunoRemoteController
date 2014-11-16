//
//  TouchView.h
//  RemoteController
//
//  Created by Jason Chu on 10/21/14.
//  Copyright (c) 2014 HamLann. All rights reserved.
//

#import <UIKit/UIKit.h>

@class TouchView;

@protocol TouchViewDelegate <NSObject>

- (void)touchDownView:(TouchView*)view;
- (void)touchUpView:(TouchView*)view;

@end

@interface TouchView : UIView

@property (nonatomic,weak) id<TouchViewDelegate> delegate;

- (void)colorsForView:(UIColor*)inactiveColor activeColor:(UIColor*)activeColor;

@end